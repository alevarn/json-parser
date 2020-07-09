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

#include "JsonArray.hpp"
#include "JsonObject.hpp"
#include "JsonBool.hpp"
#include "JsonNull.hpp"
#include "JsonNumber.hpp"
#include "JsonString.hpp"

namespace json
{
    JsonArray::JsonArray() : JsonNode()
    {
    }

    JsonArray::JsonArray(JsonNode *parent) : JsonNode(parent)
    {
    }

    JsonNodeType JsonArray::getType() const noexcept
    {
        return JsonNodeType::Array;
    }

    JsonArray &JsonArray::toArray()
    {
        return *this;
    }

    JsonNode &JsonArray::operator[](size_t index)
    {
        return *children[index];
    }

    JsonArray &JsonArray::addArray()
    {
        children.emplace_back(new JsonArray(this));
        return *children.back();
    }

    JsonObject &JsonArray::addObject()
    {
        children.emplace_back(new JsonObject(this));
        return *children.back();
    }

    JsonBool &JsonArray::addBool(bool value)
    {
        children.emplace_back(new JsonBool(this, value));
        return *children.back();
    }

    JsonNull &JsonArray::addNull()
    {
        children.emplace_back(new JsonNull(this));
        return *children.back();
    }

    JsonNumber &JsonArray::addNumber(double value)
    {
        children.emplace_back(new JsonNumber(this, value));
        return *children.back();
    }

    JsonString &JsonArray::addString(const std::string &value)
    {
        children.emplace_back(new JsonString(this, value));
        return *children.back();
    }

    JsonString &JsonArray::addString(std::string &&value)
    {
        children.emplace_back(new JsonString(this, std::move(value)));
        return *children.back();
    }

    JsonArray &JsonArray::setArray(size_t index)
    {
        children[index] = std::unique_ptr<JsonArray>(new JsonArray(this));
        return *children[index];
    }

    JsonObject &JsonArray::setObject(size_t index)
    {
        children[index] = std::unique_ptr<JsonObject>(new JsonObject(this));
        return *children[index];
    }

    JsonBool &JsonArray::setBool(size_t index, bool value)
    {
        children[index] = std::unique_ptr<JsonBool>(new JsonBool(this, value));
        return *children[index];
    }

    JsonNull &JsonArray::setNull(size_t index)
    {
        children[index] = std::unique_ptr<JsonNull>(new JsonNull(this));
        return *children[index];
    }

    JsonNumber &JsonArray::setNumber(size_t index, double value)
    {
        children[index] = std::unique_ptr<JsonNumber>(new JsonNumber(this, value));
        return *children[index];
    }

    JsonString &JsonArray::setString(size_t index, const std::string &value)
    {
        children[index] = std::unique_ptr<JsonString>(new JsonString(this, value));
        return *children[index];
    }

    JsonString &JsonArray::setString(size_t index, std::string &&value)
    {
        children[index] = std::unique_ptr<JsonString>(new JsonString(this, std::move(value)));
        return *children[index];
    }

    bool JsonArray::empty() const noexcept
    {
        return children.empty();
    }

    size_t JsonArray::getChildCount() const noexcept
    {
        return children.size();
    }

    JsonNode &JsonArray::getChild(size_t index)
    {
        return *children[index];
    }

    void JsonArray::removeChild(size_t index)
    {
        children.erase(children.begin() + index);
    }

    JsonArray::iterator::iterator(std::vector<std::unique_ptr<JsonNode>>::iterator it) : it(it)
    {
    }

    JsonArray::iterator JsonArray::iterator::operator++()
    {
        return ++it;
    }

    JsonArray::iterator JsonArray::iterator::operator++(int)
    {
        return it++;
    }

    JsonArray::iterator JsonArray::iterator::operator+(int value)
    {
        return it + value;
    }

    JsonArray::iterator JsonArray::iterator::operator-(int value)
    {
        return it - value;
    }

    bool JsonArray::iterator::operator!=(const iterator &rhs)
    {
        return it != rhs.it;
    }

    bool JsonArray::iterator::operator==(const iterator &rhs)
    {
        return it == rhs.it;
    }

    bool JsonArray::iterator::operator<(const iterator &rhs)
    {
        return it < rhs.it;
    }

    bool JsonArray::iterator::operator<=(const iterator &rhs)
    {
        return it <= rhs.it;
    }

    bool JsonArray::iterator::operator>(const iterator &rhs)
    {
        return it > rhs.it;
    }

    bool JsonArray::iterator::operator>=(const iterator &rhs)
    {
        return it >= rhs.it;
    }

    JsonNode &JsonArray::iterator::operator*()
    {
        return **it;
    }

    JsonArray::iterator JsonArray::begin()
    {
        return iterator(children.begin());
    }

    JsonArray::iterator JsonArray::end()
    {
        return iterator(children.end());
    }

} // namespace json