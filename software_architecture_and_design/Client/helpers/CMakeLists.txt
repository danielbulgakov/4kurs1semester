# Set the source files for the helper library
set(HELPER_SOURCES
    Socket.cpp
    SocketClient.cpp
)

# Set the header files for the helper library
set(HELPER_HEADERS
    Socket.h
    SocketClient.h
)

# Create the helper library target
add_library(helpers_client ${HELPER_SOURCES} ${HELPER_HEADERS})

if(MINGW)
    target_link_libraries(helpers_client ws2_32)
endif()

# Add the include directories for the helper library
target_include_directories(helpers_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})