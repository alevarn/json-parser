/*
The MIT License (MIT)

Copyright (c) 2020 Marcus Alevärn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <queue>
#include <sstream>

#include "JsonLexer.hpp"

using namespace json;

int main(int argc, char **argv)
{
    if (argc < 3)
        throw std::runtime_error("Provide sufficient arguments");

    std::istringstream test(argv[1]);
    std::queue<JsonTokenType> types;
    std::queue<std::string> values;

    // Read the correct types and values the lexer should generate when reading the JSON text.
    for (int i = 2; i < argc; i += 2)
    {
        std::string arg = argv[i];
        if (arg == "TYPE")
        {
            types.push(static_cast<JsonTokenType>(std::stoi(argv[i + 1])));
        }
        else if (arg == "VALUE")
        {
            values.push(argv[i + 1]);
        }
        else
        {
            throw std::runtime_error("Invalid test arguments");
        }
    }

    while (true)
    {
        JsonToken current = JsonLexer::nextToken(test);

        // Check that the lexer generated the correct type.
        if (types.empty() || types.front() != current.type)
            throw std::runtime_error("Wrong token type");
        types.pop();

        if (current.type == JsonTokenType::EndOfFile)
            break;

        if (current.type == JsonTokenType::Number)
        {
            // Check that the lexer generated the correct number.
            if (values.empty() || std::stod(values.front()) != std::stod(current.value))
                throw std::runtime_error("Wrong number value");
            values.pop();
        }

        if (current.type == JsonTokenType::String)
        {
            // Check that the lexer generated the correct string.
            if (values.empty() || values.front() != current.value)
                throw std::runtime_error("Wrong string value");
            values.pop();
        }
    }

    return 0;
}