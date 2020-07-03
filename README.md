# A JSON parser for C++17
This is a simplistic and lightweight JSON parser for C++17. 
It works with JSON documents that follow the format specified in [RFC 8259](https://tools.ietf.org/html/rfc8259).
## How to use this library with CMake
Clone this repository into a subdirectory of your project folder and add the following to your project's CMakeLists.txt:
```cmake
# If you have testing enabled and don't want to run the json-parser library's tests 
# you can set JSON_PARSER_TEST_ENABLED to FALSE.
set(JSON_PARSER_TEST_ENABLED FALSE)

# You should replace "deps/json-parser" with the path you are using.
add_subdirectory(deps/json-parser)

# The final step is to link the static library called "json-parser" into your executable.
# You should replace "your-exe" with the name you are using.
target_link_libraries(your_exe PRIVATE json-parser)
```
