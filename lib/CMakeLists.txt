# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library(Lib "")

target_sources(Lib
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/gui.cpp
        ${CMAKE_CURRENT_LIST_DIR}/gui.h
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/hack.cpp
        ${CMAKE_CURRENT_LIST_DIR}/hack.h
        ${CMAKE_CURRENT_LIST_DIR}/mem.cpp
        ${CMAKE_CURRENT_LIST_DIR}/mem.h
        ${CMAKE_CURRENT_LIST_DIR}/offset.cpp
        ${CMAKE_CURRENT_LIST_DIR}/offset.h
        ${CMAKE_CURRENT_LIST_DIR}/proc.cpp
        ${CMAKE_CURRENT_LIST_DIR}/proc.h
        ${CMAKE_CURRENT_LIST_DIR}/stdafx.h
        ${CMAKE_CURRENT_LIST_DIR}/stdafx.cpp
        ${CMAKE_CURRENT_LIST_DIR}/targetver.h
        )


# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        # Specify a GIT_TAG here.
        )

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------

target_link_libraries(Lib
        PUBLIC ftxui::screen
        PUBLIC ftxui::dom
        PUBLIC ftxui::component # Not needed for this example.
        )

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Lib PUBLIC ${CMAKE_CURRENT_LIST_DIR})