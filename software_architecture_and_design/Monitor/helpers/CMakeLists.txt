# Set the source files for the helper library
set(HELPER_SOURCES
    Console.cpp
    Process.cpp
)

# Set the header files for the helper library
set(HELPER_HEADERS
    Console.h
    Process.h
)

# Create the helper library target
add_library(helpers_monitor ${HELPER_SOURCES} ${HELPER_HEADERS})

# Add the include directories for the helper library
target_include_directories(helpers_monitor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})