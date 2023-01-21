cmake_minimum_required(VERSION 3.11)
project (rimage
    VERSION 0.0.1
    DESCRIPTION "rimage: "
    HOMEPAGE_URL "https://github.com/robloach/rimage"
    LANGUAGES C)

# Options
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(RIMAGE_IS_MAIN TRUE)
else()
    set(RIMAGE_IS_MAIN FALSE)
endif()
option(RIMAGE_BUILD_EXAMPLES "Examples" ${RIMAGE_IS_MAIN})

# Library
add_library(rimage INTERFACE)

# Include Directory
target_include_directories(rimage INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/)

# Examples
if(RIMAGE_BUILD_EXAMPLES)
    add_subdirectory(examples)

    # Testing
    include(CTest)
    enable_testing()
    if(BUILD_TESTING)
        # set(CTEST_CUSTOM_TESTS_IGNORE
        #     pkg-config--static
        # )

        # Always print verbose output when tests fail if run using `make test`.
        list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")

        add_subdirectory(test)
    endif()
endif()
