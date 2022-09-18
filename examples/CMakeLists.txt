# rimage-example
add_executable(rimage-example rimage-example.c)
target_link_libraries(rimage-example PUBLIC
    rimage
    m
)
set_property(TARGET rimage-example PROPERTY C_STANDARD 99)

# Copy the resources
file(GLOB resources resources/*)
set(test_resources)
list(APPEND test_resources ${resources})
file(COPY ${test_resources} DESTINATION "resources/")
