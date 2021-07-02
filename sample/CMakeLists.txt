cmake_minimum_required(VERSION 3.19)
project(ruan_macos)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa")
set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.ldust.ruan")
set(MACOSX_BUNDLE_BUNDLE_NAME "ruan_macos")
file(GLOB_RECURSE RES_LIST RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/res/*.*")

add_executable(
        ruan_macos
        MACOSX_BUNDLE
        macos.m
        sample.c
        ${RES_LIST}
)

target_link_libraries(ruan_macos ruan_core)

foreach(RES ${RES_LIST})
    set_source_files_properties(${RES} PROPERTIES HEADER_FILE_ONLY ON)
    get_filename_component(PATH ${RES} DIRECTORY)
    set_source_files_properties(
            ${RES}
            PROPERTIES
            MACOSX_PACKAGE_LOCATION
            Resources/${PATH}
    )
ENDFOREACH(RES)

set_target_properties(
        ruan_macos
        PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_LIST_DIR}/Info.plist
)
