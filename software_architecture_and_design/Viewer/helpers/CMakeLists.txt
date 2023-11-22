# Set the source files for the helper library
set(HELPER_SOURCES
        Socket.cpp
        SocketClient.cpp
        Console.cpp
        Process.cpp
)

# Set the header files for the helper library
set(HELPER_HEADERS
        Socket.h
        SocketClient.h
        Process.h
        Console.h
)

# Create the helper library target
add_library(helpers_viewer ${HELPER_SOURCES} ${HELPER_HEADERS})

if(MINGW)
    target_link_libraries(helpers_viewer ws2_32)
endif()

# Add the include directories for the helper library
target_include_directories(helpers_viewer PUBLIC Viewer)