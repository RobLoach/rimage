# rimage-test
add_executable(rimage-test rimage-test.c)
target_compile_options(rimage-test PRIVATE -Wall -Wextra -Wconversion -Wsign-conversion)
target_link_libraries(rimage-test PUBLIC
    rimage
    m
)
set_property(TARGET rimage-test PROPERTY C_STANDARD 99)

# Copy the resources
file(GLOB resources resources/*)
set(test_resources)
list(APPEND test_resources ${resources})
file(COPY ${test_resources} DESTINATION "resources/")

# Set up the test
add_test(NAME rimage-test COMMAND rimage-test)
