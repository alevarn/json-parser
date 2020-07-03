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

#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "JsonNode.hpp"
#include "JsonLexer.hpp"

#include <memory>

namespace json
{
    /**
     * A class for parsing the JSON text. This class will use the JsonLexer to get the next token from the stream.
    */
    class JsonParser
    {
    public:
        /**
         * Will parse the JSON text and return the root node.
        */
        static std::unique_ptr<JsonNode> parse(std::istream &input);

    private:
        /**
         * Recursive method that parses a JsonArray and all its child nodes.
        */
        static void parseArray(std::istream &input, JsonArray &parent);

        /**
         * Recursive method that will parse one child to a JsonArray node.
        */
        static void parseArrayValue(std::istream &input, JsonToken &current, JsonArray &parent);

        /**
         * Recursive method that parses a JsonObject and all its child nodes.
        */
        static void parseObject(std::istream &input, JsonObject &parent);

        /**
         * Recursive method that will parse one child to a JsonObject node.
        */
        static void parseObjectMember(std::istream &input, JsonToken &current, JsonObject &parent);
    };
} // namespace json

#endif