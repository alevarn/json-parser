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

#include "JsonParser.hpp"
#include "JsonArray.hpp"
#include "JsonObject.hpp"
#include "JsonBool.hpp"
#include "JsonNull.hpp"
#include "JsonNumber.hpp"
#include "JsonString.hpp"

#include <stdexcept>

namespace json
{
    std::unique_ptr<JsonNode> JsonParser::parse(std::istream &input)
    {
        std::unique_ptr<JsonNode> root = nullptr;
        JsonToken current = JsonLexer::nextToken(input);

        // Check if the the JSON text is empty.
        if (current.type == JsonTokenType::EndOfFile)
            return root;

        // Create the root node.
        switch (current.type)
        {
        case JsonTokenType::BeginArray:
            root = std::make_unique<JsonArray>();
            parseArray(input, *root);
            break;
        case JsonTokenType::BeginObject:
            root = std::make_unique<JsonObject>();
            parseObject(input, *root);
            break;
        case JsonTokenType::False:
            root = std::make_unique<JsonBool>(false);
            break;
        case JsonTokenType::True:
            root = std::make_unique<JsonBool>(true);
            break;
        case JsonTokenType::Null:
            root = std::make_unique<JsonNull>();
            break;
        case JsonTokenType::Number:
            root = std::make_unique<JsonBool>(std::stod(current.value));
            break;
        case JsonTokenType::String:
            root = std::make_unique<JsonString>(std::move(current.value));
            break;
        default:
            throw std::runtime_error("Illegal root value");
        }

        current = JsonLexer::nextToken(input);

        // Make sure there is only one root node.
        if (current.type != JsonTokenType::EndOfFile)
            throw std::runtime_error("Valid json text can only have one root value");

        return root;
    }

    void JsonParser::parseArray(std::istream &input, JsonArray &parent)
    {
        JsonToken current = JsonLexer::nextToken(input);

        // Check if the JsonArray is empty.
        if (current.type == JsonTokenType::EndArray)
            return;

        // If not empty then parse the first child.
        parseArrayValue(input, current, parent);
        current = JsonLexer::nextToken(input);

        // Parse all comma separated childs.
        while (current.type == JsonTokenType::ValueSeparator)
        {
            current = JsonLexer::nextToken(input);
            parseArrayValue(input, current, parent);
            current = JsonLexer::nextToken(input);
        }

        // Make sure the JsonArray ends with ']'.
        if (current.type != JsonTokenType::EndArray)
            throw std::runtime_error("Could not read the end of the array");
    }

    void JsonParser::parseArrayValue(std::istream &input, JsonToken &current, JsonArray &parent)
    {
        // Identify the child and add it to the JsonArray.
        switch (current.type)
        {
        case JsonTokenType::BeginArray:
            parseArray(input, parent.addArray());
            break;
        case JsonTokenType::BeginObject:
            parseObject(input, parent.addObject());
            break;
        case JsonTokenType::False:
            parent.addBool(false);
            break;
        case JsonTokenType::True:
            parent.addBool(true);
            break;
        case JsonTokenType::Null:
            parent.addNull();
            break;
        case JsonTokenType::Number:
            parent.addNumber(std::stod(current.value));
            break;
        case JsonTokenType::String:
            parent.addString(std::move(current.value));
            break;
        default:
            throw std::runtime_error("Could not read the next value");
        }
    }

    void JsonParser::parseObject(std::istream &input, JsonObject &parent)
    {
        JsonToken current = JsonLexer::nextToken(input);

        if (current.type == JsonTokenType::EndObject)
            return;

        parseObjectMember(input, current, parent);
        current = JsonLexer::nextToken(input);

        while (current.type == JsonTokenType::ValueSeparator)
        {
            current = JsonLexer::nextToken(input);
            parseObjectMember(input, current, parent);
            current = JsonLexer::nextToken(input);
        }

        if (current.type != JsonTokenType::EndObject)
            throw std::runtime_error("Could not read the end of the object");
    }

    void JsonParser::parseObjectMember(std::istream &input, JsonToken &current, JsonObject &parent)
    {
        if (current.type != JsonTokenType::String)
            throw std::runtime_error("Every object member must start with a string");

        // This is the name for the new child.
        std::string name = std::move(current.value);

        current = JsonLexer::nextToken(input);

        if (current.type != JsonTokenType::NameSeparator)
            throw std::runtime_error("After the string there must be a name separator");

        current = JsonLexer::nextToken(input);

        // Identify the child and add it to the JsonObject.
        switch (current.type)
        {
        case JsonTokenType::BeginArray:
            parseArray(input, parent.setArray(std::move(name)));
            break;
        case JsonTokenType::BeginObject:
            parseObject(input, parent.setObject(std::move(name)));
            break;
        case JsonTokenType::False:
            parent.setBool(std::move(name), false);
            break;
        case JsonTokenType::True:
            parent.setBool(std::move(name), true);
            break;
        case JsonTokenType::Null:
            parent.setNull(std::move(name));
            break;
        case JsonTokenType::Number:
            parent.setNumber(std::move(name), std::stod(current.value));
            break;
        case JsonTokenType::String:
            parent.setString(std::move(name), std::move(current.value));
            break;
        default:
            throw std::runtime_error("Could not read the next value");
        }
    }
} // namespace json