# Set the header files for the helper library
set(HELPER_HEADERS
        UtilFile.h
        UtilString.h
)

# Create the helper library target
add_library(helpers_global INTERFACE)

# Add the include directories for the helper library
target_include_directories(helpers_global INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/helpers)