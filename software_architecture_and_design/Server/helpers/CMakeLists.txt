# Set the source files for the helper library
set(HELPER_SOURCES
    Socket.cpp
    SocketServer.cpp
)

# Set the header files for the helper library
set(HELPER_HEADERS
    Socket.h
    SocketServer.h
    UtilFile.h
    UtilString.h
)

# Create the helper library target
add_library(helpers ${HELPER_SOURCES} ${HELPER_HEADERS})

# Add the include directories for the helper library
target_include_directories(helpers PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})