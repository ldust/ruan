#import <Cocoa/Cocoa.h>
#import "../ruan/types.h"
#import "../ruan/platform.h"

@class ContentView;

@interface RAppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>
@property (strong) NSWindow *window;
@property (strong) ContentView *view;
@end

@interface ContentView : NSView
@end

@implementation RAppDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    app_launch_finished();
    [NSTimer scheduledTimerWithTimeInterval:0
                                     target:self
                                   selector:@selector(timerTrigger)
                                   userInfo:nil
                                    repeats:YES];
}

- (void) timerTrigger {
    app_update();
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {

}

- (void)windowWillClose:(NSNotification *)notif {
    [NSApp terminate:self];
}

@end


@implementation ContentView {
    vector2i size;
    NSImage* image;
    NSBitmapImageRep *rep;
}

#define BYTES_PER_PIXEL 4

- (instancetype) initWithSize:(vector2i) sz {
    self = [super init];
    if (self != nil) {
        size = sz;
        rep = [[NSBitmapImageRep alloc]
                initWithBitmapDataPlanes:NULL
                              pixelsWide:size.x
                              pixelsHigh:size.y
                           bitsPerSample:8
                         samplesPerPixel:3
                                hasAlpha:NO
                                isPlanar:NO
                          colorSpaceName:NSCalibratedRGBColorSpace
                             bytesPerRow:size.x * 4
                            bitsPerPixel:32];
        image = [[NSImage alloc] init];
        [image addRepresentation:rep];
    }
    return self;
}

- (void) setPixel:(vector2i) pos color:(color32) clr {
    if (pos.x >= 0 && pos.x < size.x && pos.y >= 0 && pos.y < size.y) {
        int y = size.y - pos.y - 1;
        memcpy(rep.bitmapData + (size.x * y + pos.x) * BYTES_PER_PIXEL, &clr, BYTES_PER_PIXEL);
    }
}

- (void) clear {
    size_t sz = (unsigned int)(size.x * size.y * BYTES_PER_PIXEL);
    memset(rep.bitmapData, 0, sz);
}

- (void)dealloc {
    [rep release];
    [image release];
    [super dealloc];
}

- (BOOL)acceptsFirstResponder {
    return YES;  /* to receive key-down events */
}

- (void)drawRect:(NSRect)dirtyRect {
    [image drawInRect:dirtyRect];
}
@end

int main() {
    id delegate = NULL;
    @autoreleasepool {
        delegate = [[RAppDelegate alloc] init];
        [[NSApplication sharedApplication] setDelegate:delegate];
        [NSApp run];
    }
    [delegate release];
    return 0;
}

void set_pixel(void *ptr, vector2i pos, color32 c) {
    device* d = (device*)ptr;
    [(ContentView*)d->handle setPixel:pos color:c];
}

void flush(void *ptr) {
    device* d = (device*)ptr;
    [(ContentView*)d->handle setNeedsDisplay:YES];
}

void clear_depth(device* d) {
    for (int i = 0; i < d->win_size.x * d->win_size.y; ++i) {
        d->depth_buffer[i] = FLT_MAX * -1;
    }
}

void clear(void *ptr) {
    device* d = (device*)ptr;
    [(ContentView*)d->handle clear];
    clear_depth(d);
}


bool file_exists(const char* path){
    return access(path, F_OK) != -1;
}

FILE* app_open_file(const char* file_name, const char* mode) {
    if (file_exists(file_name)) {
        return fopen(file_name, mode);
    } else {
        NSString* path = [NSString stringWithFormat:@"%@/%s", [[NSBundle mainBundle] resourcePath], file_name];
        return fopen([path UTF8String], mode);
    }
}

void app_create_win(vector2i size, device* d) {
    RAppDelegate* delegate = (RAppDelegate*)[NSApplication sharedApplication].delegate;
    NSRect screenRect = [[NSScreen mainScreen] visibleFrame];

    float w = (float)size.x;
    float h = (float)size.y;

    NSRect appRect = CGRectMake(screenRect.size.width / 2 - w / 2,
                                screenRect.size.height / 2 - h / 2,
                                w, h);

    NSWindowStyleMask style = NSWindowStyleMaskClosable | NSWindowStyleMaskTitled | NSWindowStyleMaskMiniaturizable;

    delegate.window = [[NSWindow alloc] initWithContentRect:appRect
                                                  styleMask:style
                                                    backing:NSBackingStoreBuffered
                                                      defer:NO];
    [delegate.window setDelegate:delegate];

    [delegate.window makeKeyAndOrderFront:nil];

    delegate.view = [[ContentView alloc] initWithSize:size];

    [delegate.window setContentView:delegate.view];

    [delegate.window makeFirstResponder:delegate.view];

    d->win_size = size;
    d->handle = delegate.view;
    d->set_pixel = set_pixel;
    d->flush = flush;
    d->clear = clear;
    size_t ds = sizeof(float) * size.x * size.y;
    d->depth_buffer = malloc(ds);
    clear_depth(d);
}