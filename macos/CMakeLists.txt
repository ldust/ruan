cmake_minimum_required(VERSION 3.19)
project(ruan_macos)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa")
set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.ldust.ruan")
set(MACOSX_BUNDLE_BUNDLE_NAME "ruan")

add_executable(
        ruan
        MACOSX_BUNDLE
        macos.m
)

target_link_libraries(ruan ruan_core)

set_target_properties(
        ruan
        PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_LIST_DIR}/Info.plist
)
