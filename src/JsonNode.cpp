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

#include "JsonNode.hpp"

#include <stdexcept>

namespace json
{
    JsonNode::JsonNode() : parent(nullptr)
    {
    }

    JsonNode::JsonNode(JsonNode *parent) : parent(parent)
    {
    }

    JsonNode::~JsonNode()
    {
    }

    bool JsonNode::hasParent() const noexcept
    {
        return parent != nullptr;
    }

    JsonNode &JsonNode::getParent() noexcept
    {
        return *parent;
    }

    const JsonNode &JsonNode::getParent() const noexcept
    {
        return *parent;
    }

    JsonArray &JsonNode::toArray()
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonArray");
    }

    const JsonArray &JsonNode::toArray() const
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonArray");
    }

    JsonObject &JsonNode::toObject()
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonObject");
    }

    const JsonObject &JsonNode::toObject() const
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonObject");
    }

    JsonBool &JsonNode::toBool()
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonBool");
    }

    const JsonBool &JsonNode::toBool() const
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonBool");
    }

    JsonNull &JsonNode::toNull()
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonNull");
    }

    const JsonNull &JsonNode::toNull() const
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonNull");
    }

    JsonNumber &JsonNode::toNumber()
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonNumber");
    }

    const JsonNumber &JsonNode::toNumber() const
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonNumber");
    }

    JsonString &JsonNode::toString()
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonString");
    }

    const JsonString &JsonNode::toString() const
    {
        throw std::runtime_error("Could not convert this object to an object of type JsonString");
    }

    JsonNode::operator JsonArray &()
    {
        return toArray();
    }

    JsonNode::operator const JsonArray &() const
    {
        return toArray();
    }

    JsonNode::operator JsonObject &()
    {
        return toObject();
    }

    JsonNode::operator const JsonObject &() const
    {
        return toObject();
    }

    JsonNode::operator JsonBool &()
    {
        return toBool();
    }

    JsonNode::operator const JsonBool &() const
    {
        return toBool();
    }

    JsonNode::operator JsonNull &()
    {
        return toNull();
    }

    JsonNode::operator const JsonNull &() const
    {
        return toNull();
    }

    JsonNode::operator JsonNumber &()
    {
        return toNumber();
    }

    JsonNode::operator const JsonNumber &() const
    {
        return toNumber();
    }

    JsonNode::operator JsonString &()
    {
        return toString();
    }

    JsonNode::operator const JsonString &() const
    {
        return toString();
    }

    JsonNode &JsonNode::operator[](size_t)
    {
        throw std::runtime_error("The object is not of type JsonArray and therefore you cannot use the subscript operator to access child elements");
    }

    const JsonNode &JsonNode::operator[](size_t) const
    {
        throw std::runtime_error("The object is not of type JsonArray and therefore you cannot use the subscript operator to access child elements");
    }

    JsonNode &JsonNode::operator[](const std::string &)
    {
        throw std::runtime_error("The object is not of type JsonObject and therefore you cannot use the subscript operator to access child elements");
    }

    const JsonNode &JsonNode::operator[](const std::string &) const
    {
        throw std::runtime_error("The object is not of type JsonObject and therefore you cannot use the subscript operator to access child elements");
    }
} // namespace json