# Set the source files for the helper library
set(HELPER_SOURCES
    Socket.cpp
    SocketServer.cpp
)

# Set the header files for the helper library
set(HELPER_HEADERS
    Socket.h
    SocketServer.h
)

# Create the helper library target
add_library(helpers_server ${HELPER_SOURCES} ${HELPER_HEADERS})

# Add the include directories for the helper library
target_include_directories(helpers_server PUBLIC Server)