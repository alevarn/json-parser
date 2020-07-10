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

#include "JsonObject.hpp"
#include "JsonArray.hpp"
#include "JsonBool.hpp"
#include "JsonNull.hpp"
#include "JsonNumber.hpp"
#include "JsonString.hpp"

#include <algorithm>

namespace json
{
    JsonObject::JsonObject() : JsonNode(), childCounter(0)
    {
    }

    JsonObject::JsonObject(JsonNode *parent) : JsonNode(parent), childCounter(0)
    {
    }

    JsonNodeType JsonObject::getType() const noexcept
    {
        return JsonNodeType::Object;
    }

    JsonObject &JsonObject::toObject()
    {
        return *this;
    }

    const JsonObject &JsonObject::toObject() const
    {
        return *this;
    }

    JsonNode &JsonObject::operator[](const std::string &name)
    {
        // Can throw out_of_range exception.
        return *children.at(name).node;
    }

    const JsonNode &JsonObject::operator[](const std::string &name) const
    {
        // Can throw out_of_range exception.
        return *children.at(name).node;
    }

    template <typename ChildType>
    ChildType &JsonObject::setChild(const std::string &name)
    {
        std::unique_ptr<JsonNode> child(new ChildType(this));
        ChildType &ref = *child; // We take a reference to the child before we move it into the unordered_map.
        children[name] = {std::move(child), childCounter++};
        return ref;
    }

    template <typename ChildType>
    ChildType &JsonObject::setChild(std::string &&name)
    {
        std::unique_ptr<JsonNode> child(new ChildType(this));
        ChildType &ref = *child;
        children[std::move(name)] = {std::move(child), childCounter++};
        return ref;
    }

    template <typename ChildType, typename ArgType>
    ChildType &JsonObject::setChild(const std::string &name, ArgType arg)
    {
        std::unique_ptr<JsonNode> child(new ChildType(this, arg));
        ChildType &ref = *child;
        children[name] = {std::move(child), childCounter++};
        return ref;
    }

    template <typename ChildType, typename ArgType>
    ChildType &JsonObject::setChild(std::string &&name, ArgType arg)
    {
        std::unique_ptr<JsonNode> child(new ChildType(this, arg));
        ChildType &ref = *child;
        children[std::move(name)] = {std::move(child), childCounter++};
        return ref;
    }

    JsonArray &JsonObject::setArray(const std::string &name)
    {
        return setChild<JsonArray>(name);
    }

    JsonArray &JsonObject::setArray(std::string &&name)
    {
        return setChild<JsonArray>(std::move(name));
    }

    JsonObject &JsonObject::setObject(const std::string &name)
    {
        return setChild<JsonObject>(name);
    }

    JsonObject &JsonObject::setObject(std::string &&name)
    {
        return setChild<JsonObject>(std::move(name));
    }

    JsonBool &JsonObject::setBool(const std::string &name, bool value)
    {
        return setChild<JsonBool, bool>(name, value);
    }

    JsonBool &JsonObject::setBool(std::string &&name, bool value)
    {
        return setChild<JsonBool, bool>(std::move(name), value);
    }

    JsonNull &JsonObject::setNull(const std::string &name)
    {
        return setChild<JsonNull>(name);
    }

    JsonNull &JsonObject::setNull(std::string &&name)
    {
        return setChild<JsonNull>(std::move(name));
    }

    JsonNumber &JsonObject::setNumber(const std::string &name, double value)
    {
        return setChild<JsonNumber, double>(name, value);
    }

    JsonNumber &JsonObject::setNumber(std::string &&name, double value)
    {
        return setChild<JsonNumber, double>(std::move(name), value);
    }

    JsonString &JsonObject::setString(const std::string &name, const std::string &value)
    {
        return setChild<JsonString, const std::string &>(name, value);
    }

    JsonString &JsonObject::setString(std::string &&name, const std::string &value)
    {
        return setChild<JsonString, const std::string &>(std::move(name), value);
    }

    JsonString &JsonObject::setString(const std::string &name, std::string &&value)
    {
        std::unique_ptr<JsonNode> child(new JsonString(this, std::move(value)));
        JsonString &ref = *child;
        children[name] = {std::move(child), childCounter++};
        return ref;
    }

    JsonString &JsonObject::setString(std::string &&name, std::string &&value)
    {
        std::unique_ptr<JsonNode> child(new JsonString(this, std::move(value)));
        JsonString &ref = *child;
        children[std::move(name)] = {std::move(child), childCounter++};
        return ref;
    }

    bool JsonObject::empty() const noexcept
    {
        return children.empty();
    }

    size_t JsonObject::getChildCount() const noexcept
    {
        return children.size();
    }

    bool JsonObject::hasChild(const std::string &name) const noexcept
    {
        return children.find(name) != children.end();
    }

    JsonNode &JsonObject::getChild(const std::string &name)
    {
        return *children.at(name).node;
    }

    const JsonNode &JsonObject::getChild(const std::string &name) const
    {
        return *children.at(name).node;
    }

    void JsonObject::removeChild(const std::string &name)
    {
        children.erase(name);
    }

    using iterator = JsonObject::iterator;

    iterator::iterator(std::unordered_map<std::string, Value>::iterator it) : it(it)
    {
    }

    iterator iterator::operator++()
    {
        return ++it;
    }

    iterator iterator::operator++(int)
    {
        return it++;
    }

    bool iterator::operator!=(const iterator &rhs)
    {
        return it != rhs.it;
    }

    bool iterator::operator==(const iterator &rhs)
    {
        return it == rhs.it;
    }

    std::pair<const std::string &, JsonNode &> iterator::operator*()
    {
        return {it->first, *it->second.node};
    }

    using const_iterator = JsonObject::const_iterator;

    const_iterator::const_iterator(std::unordered_map<std::string, Value>::const_iterator it) : it(it)
    {
    }

    const_iterator const_iterator::operator++()
    {
        return ++it;
    }

    const_iterator const_iterator::operator++(int)
    {
        return it++;
    }

    bool const_iterator::operator!=(const const_iterator &rhs)
    {
        return it != rhs.it;
    }

    bool const_iterator::operator==(const const_iterator &rhs)
    {
        return it == rhs.it;
    }

    std::pair<const std::string &, const JsonNode &> const_iterator::operator*() const
    {
        return {it->first, *it->second.node};
    }

    iterator JsonObject::begin()
    {
        return iterator(children.begin());
    }

    iterator JsonObject::end()
    {
        return iterator(children.end());
    }

    const_iterator JsonObject::begin() const
    {
        return const_iterator(children.begin());
    }

    const_iterator JsonObject::end() const
    {
        return const_iterator(children.end());
    }

    std::vector<std::pair<const std::string &, JsonNode &>> JsonObject::sort()
    {
        // Create a new vector and reserve enough space.
        std::vector<std::pair<const std::string *, Value *>> temp;
        temp.reserve(children.size());

        // Fill up the array.
        for (auto &pair : children)
            temp.emplace_back(&pair.first, &pair.second);

        // Sort the array based on the insertion order.
        std::sort(temp.begin(), temp.end(), [](const std::pair<const std::string *, Value *> &left, const std::pair<const std::string *, Value *> &right) {
            return left.second->orderIndex < right.second->orderIndex;
        });

        // We don't want to return a vector of std::pair<const std::string *, Value*>
        // therefore we create a new vector of the type we want to return.
        std::vector<std::pair<const std::string &, JsonNode &>> result;
        result.reserve(children.size());

        for (auto &pair : temp)
            result.emplace_back(*pair.first, *pair.second->node);

        return result;
    }

    std::vector<std::pair<const std::string &, const JsonNode &>> JsonObject::sort() const
    {
        // Create a new vector and reserve enough space.
        std::vector<std::pair<const std::string *, const Value *>> temp;
        temp.reserve(children.size());

        // Fill up the array.
        for (const auto &pair : children)
            temp.emplace_back(&pair.first, &pair.second);

        // Sort the array based on the insertion order.
        std::sort(temp.begin(), temp.end(), [](const std::pair<const std::string *, const Value *> &left, const std::pair<const std::string *, const Value *> &right) {
            return left.second->orderIndex < right.second->orderIndex;
        });

        // We don't want to return a vector of std::pair<const std::string *, Value*>
        // therefore we create a new vector of the type we want to return.
        std::vector<std::pair<const std::string &, const JsonNode &>> result;
        result.reserve(children.size());

        for (const auto &pair : temp)
            result.emplace_back(*pair.first, *pair.second->node);

        return result;
    }
} // namespace json