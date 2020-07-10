/*
The MIT License (MIT)

Copyright (c) 2020 Marcus Alevärn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "JsonString.hpp"

namespace json
{
    JsonString::JsonString(const std::string &value) : JsonNode(), value(value)
    {
    }

    JsonString::JsonString(std::string &&value) : JsonNode(), value(std::move(value))
    {
    }

    JsonString::JsonString(JsonNode *parent, const std::string &value) : JsonNode(parent), value(value)
    {
    }

    JsonString::JsonString(JsonNode *parent, std::string &&value) : JsonNode(parent), value(std::move(value))
    {
    }

    JsonNodeType JsonString::getType() const noexcept
    {
        return JsonNodeType::String;
    }

    JsonString &JsonString::toString()
    {
        return *this;
    }

    const JsonString &JsonString::toString() const
    {
        return *this;
    }

    std::string &JsonString::data()
    {
        return value;
    }

    JsonString::operator std::string &()
    {
        return value;
    }

    JsonString::operator const char *()
    {
        return value.c_str();
    }

    std::string JsonString::escaped() const noexcept
    {
        std::string result;

        // Go through each character and check if one of them need to be escaped.
        for (size_t i = 0; i < value.length(); i++)
        {
            switch (value[i])
            {
            case '\"':
                result += "\\\"";
                break;
            case '\\':
                result += "\\\\";
                break;
            case '\b':
                result += "\\b";
                break;
            case '\f':
                result += "\\f";
                break;
            case '\n':
                result += "\\n";
                break;
            case '\r':
                result += "\\r";
                break;
            case '\t':
                result += "\\t";
                break;
            default:
                result += value[i];
                break;
            }
        }

        return result;
    }
} // namespace json