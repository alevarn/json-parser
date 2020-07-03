# The MIT License (MIT)
#
# Copyright (c) 2020 Marcus Alevärn
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

cmake_minimum_required(VERSION 3.15.0)

project(json-parser VERSION 1.0.0)

# Make sure that the user is not using anything lower than C++17.
if(DEFINED CMAKE_CXX_STANDARD)
    if(NOT ${CMAKE_CXX_STANDARD} GREATER_EQUAL 17)
        message(FATAL_ERROR "The json-parser library requires C++17")
    endif()
else()
    set(CMAKE_CXX_STANDARD 17)
endif()

set(SRC_FILES
    src/JsonNode.cpp
    src/JsonArray.cpp
    src/JsonObject.cpp
    src/JsonBool.cpp
    src/JsonNull.cpp
    src/JsonNumber.cpp
    src/JsonString.cpp
    src/JsonDocument.cpp
    src/JsonLexer.cpp
    src/JsonParser.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC include)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

# If JSON_PARSER_TEST_ENABLED has not been defined
# we will set it to TRUE and you can test the code with the ctest command.
if(NOT DEFINED JSON_PARSER_TEST_ENABLED)
    set(JSON_PARSER_TEST_ENABLED TRUE)
endif()

if(${JSON_PARSER_TEST_ENABLED})
    enable_testing()    
    
    add_executable(lexer-test test/LexerTest.cpp)
    target_link_libraries(lexer-test PRIVATE ${PROJECT_NAME})

    add_test(LexerTest-1 lexer-test "[" TYPE 0 TYPE 11)
    add_test(LexerTest-2 lexer-test "{" TYPE 1 TYPE 11)
    add_test(LexerTest-3 lexer-test "]" TYPE 2 TYPE 11)
    add_test(LexerTest-4 lexer-test "}" TYPE 3 TYPE 11)
    add_test(LexerTest-5 lexer-test ":" TYPE 4 TYPE 11)
    add_test(LexerTest-6 lexer-test "," TYPE 5 TYPE 11)
    add_test(LexerTest-7 lexer-test "false" TYPE 6 TYPE 11)
    add_test(LexerTest-8 lexer-test "true" TYPE 7 TYPE 11)
    add_test(LexerTest-9 lexer-test "null" TYPE 8 TYPE 11)
    add_test(LexerTest-10 lexer-test "" TYPE 11)

    add_test(LexerTest-11 lexer-test "0" TYPE 9 VALUE "0" TYPE 11) 
    add_test(LexerTest-12 lexer-test "0123" TYPE 9 VALUE "0" TYPE 9 VALUE "123" TYPE 11)
    add_test(LexerTest-13 lexer-test "0.123" TYPE 9 VALUE "0.123" TYPE 11)
    add_test(LexerTest-14 lexer-test "-0.123" TYPE 9 VALUE "-0.123" TYPE 11)
    add_test(LexerTest-15 lexer-test "0e123" TYPE 9 VALUE "0" TYPE 11)
    add_test(LexerTest-16 lexer-test "-0e123" TYPE 9 VALUE "0" TYPE 11)
    add_test(LexerTest-17 lexer-test "1e2" TYPE 9 VALUE "100" TYPE 11)
    add_test(LexerTest-18 lexer-test "1e+2" TYPE 9 VALUE "100" TYPE 11)
    add_test(LexerTest-19 lexer-test "-1e2" TYPE 9 VALUE "-100" TYPE 11)
    add_test(LexerTest-20 lexer-test "1e-2" TYPE 9 VALUE "0.01" TYPE 11)
    add_test(LexerTest-21 lexer-test "-1e-2" TYPE 9 VALUE "-0.01" TYPE 11)
    add_test(LexerTest-22 lexer-test "-1.123e-2" TYPE 9 VALUE "-0.01123" TYPE 11)
    add_test(LexerTest-23 lexer-test "-1.123e+2" TYPE 9 VALUE "-112.3" TYPE 11)
    add_test(LexerTest-24 lexer-test "1.123e+2" TYPE 9 VALUE "112.3" TYPE 11)
    add_test(LexerTest-25 lexer-test "1.123e2" TYPE 9 VALUE "112.3" TYPE 11)

    add_test(LexerTest-26 lexer-test "\"\"" TYPE 10 VALUE "" TYPE 11)
    add_test(LexerTest-27 lexer-test "\"abc\"" TYPE 10 VALUE "abc" TYPE 11)
    add_test(LexerTest-28 lexer-test "\"a b  c\"" TYPE 10 VALUE "a b  c" TYPE 11)
    add_test(LexerTest-29 lexer-test "\"def\n\t\rabc\"" TYPE 10 VALUE "def\n\t\rabc" TYPE 11)

    add_test(LexerTest-30 lexer-test "[{\"name\": \"John Doe\", \"age\": 45, \"alive\": true}, {\"name\": \"Unknown\", \"age\": null, \"alive\": false}]" 
    TYPE 0  
    TYPE 1 TYPE 10 VALUE "name" TYPE 4 TYPE 10 VALUE "John Doe" TYPE 5 TYPE 10 VALUE "age" TYPE 4 TYPE 9 VALUE 45 TYPE 5 TYPE 10 VALUE "alive" TYPE 4 TYPE 7 TYPE 3 TYPE 5
    TYPE 1 TYPE 10 VALUE "name" TYPE 4 TYPE 10 VALUE "Unknown" TYPE 5 TYPE 10 VALUE "age" TYPE 4 TYPE 8 TYPE 5 TYPE 10 VALUE "alive" TYPE 4 TYPE 6 TYPE 3
    TYPE 2 
    TYPE 11
    )

    add_executable(parser-test test/ParserTest.cpp)
    target_link_libraries(parser-test PRIVATE ${PROJECT_NAME})

    add_test(ParserTest-1 parser-test "${CMAKE_CURRENT_SOURCE_DIR}/test/parser-test-1.json" "${CMAKE_CURRENT_SOURCE_DIR}/test/parser-test-1-generated.json")
    add_test(ParserTest-2 parser-test "${CMAKE_CURRENT_SOURCE_DIR}/test/parser-test-2.json" "${CMAKE_CURRENT_SOURCE_DIR}/test/parser-test-2-generated.json")
    add_test(ParserTest-3 parser-test "${CMAKE_CURRENT_SOURCE_DIR}/test/parser-test-3.json" "${CMAKE_CURRENT_SOURCE_DIR}/test/parser-test-3-generated.json")
endif()