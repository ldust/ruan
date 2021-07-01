#import <Cocoa/Cocoa.h>
#import "../ruan/types.h"
#import "../ruan/platform.h"

@interface RAppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>
@property (strong) NSWindow *window;
@end


@implementation RAppDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    app_launch_finished();
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {

}

- (void)windowWillClose:(NSNotification *)notif {
    [NSApp terminate:self];
}

@end

int main() {
    [[NSApplication sharedApplication] setDelegate:[[RAppDelegate alloc] init]];
    [NSApp run];
    return 0;
}

void app_create_win(vector2i size) {
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
}