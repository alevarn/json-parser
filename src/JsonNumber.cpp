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

#include "JsonNumber.hpp"

namespace json
{
    JsonNumber::JsonNumber(double value) : JsonNode(), value(value)
    {
    }

    JsonNumber::JsonNumber(JsonNode *parent, double value) : JsonNode(parent), value(value)
    {
    }

    JsonNodeType JsonNumber::getType() const noexcept
    {
        return JsonNodeType::Number;
    }

    JsonNumber &JsonNumber::toNumber()
    {
        return *this;
    }

    const JsonNumber &JsonNumber::toNumber() const
    {
        return *this;
    }

    double &JsonNumber::data()
    {
        return value;
    }

    const double &JsonNumber::data() const
    {
        return value;
    }

    JsonNumber::operator double &()
    {
        return value;
    }

    JsonNumber::operator const double &() const
    {
        return value;
    }
} // namespace json