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

#ifndef JSON_ARRAY_HPP
#define JSON_ARRAY_HPP

#include "JsonNode.hpp"

#include <vector>
#include <memory>

namespace json
{
    /**
     * Represents a node that holds a collection of child nodes. Each child node can be accessed using a numeric index.
    */
    class JsonArray : public JsonNode
    {
    public:
        /**
         * An iterator that lets the user iterate over all children.
         * The main purpose of this class is to make sure 
         * the JsonArray can work with the range-based for loop.
        */
        class iterator
        {
        private:
            std::vector<std::unique_ptr<JsonNode>>::iterator it;

        public:
            /**
             * Creates a new iterator object.
            */
            iterator(std::vector<std::unique_ptr<JsonNode>>::iterator it);

            /**
             * The postfix operator will return an iterator object referring to the next element in the array.
            */
            iterator operator++();

            /**
             * Returns true if two iterator objects are referring to different elements.
            */
            bool operator!=(const iterator &other);

            /**
             * Returns the element that the iterator object is referring to.
            */
            JsonNode &operator*();
        };

        /**
         * Creates a new JsonArray without a parent.
        */
        JsonArray();

        /**
         * Creates a new JsonArray with a parent.
        */
        JsonArray(JsonNode *parent);

        /**
         * Returns JsonNodeType::Array.
        */
        JsonNodeType getType() const noexcept override;

        /**
         * Returns a reference to this JsonArray.
        */
        JsonArray &toArray() override;

        /**
         * Returns the child node at a specific index. 
         * No range checks are done so make sure the index is within the boundaries.
        */
        JsonNode &operator[](size_t index) override;

        /**
         * Will add a new JsonArray object to the child collection and return a reference to the new object.
        */
        JsonArray &addArray();

        /**
         * Will add a new object of type JsonObject to the child collection and return a reference to the new object.
        */
        JsonObject &addObject();

        /**
         * Will add a new JsonBool object to the child collection and return a reference to the new object.
        */
        JsonBool &addBool(bool value);

        /**
         * Will add a new JsonNull object to the child collection and return a reference to the new object.
        */
        JsonNull &addNull();

        /**
         * Will add a new JsonNumber object to the child collection and return a reference to the new object.
        */
        JsonNumber &addNumber(double value);

        /**
         * Will add a new JsonString object to the child collection and return a reference to the new object.
        */
        JsonString &addString(const std::string &value);

        /**
         * Will add a new JsonString object to the child collection and return a reference to the new object.
        */
        JsonString &addString(std::string &&value);

        /**
         * Replace the current node at a specific index with a new JsonArray object.
        */
        JsonArray &setArray(size_t index);

        /**
         * Replace the current node at a specific index with a new JsonArray object.
        */
        JsonObject &setObject(size_t index);

        /**
         * Replace the current node at a specific index with a new JsonBool object.
        */
        JsonBool &setBool(size_t index, bool value);

        /**
         * Replace the current node at a specific index with a new JsonNull object.
        */
        JsonNull &setNull(size_t index);

        /**
         * Replace the current node at a specific index with a new JsonNumber object.
        */
        JsonNumber &setNumber(size_t index, double value);

        /**
         * Replace the current node at a specific index with a new JsonString object.
        */
        JsonString &setString(size_t index, const std::string &value);

        /**
         * Replace the current node at a specific index with a new JsonString object.
        */
        JsonString &setString(size_t index, std::string &&value);

        /**
         * Returns true if this JsonArray has no children.
        */
        bool empty() const noexcept;

        /**
         * Returns the number of children in this JsonArray.
        */
        size_t getChildCount() const noexcept;

        /**
         * Returns a child node at a specific index. 
         * No range checks are done so make sure the index is within the boundaries.
         * This method is equivalent to the subscript operator.
        */
        JsonNode &getChild(size_t index);

        /**
         * Removes a child node at a specific index. 
        */
        void removeChild(size_t index);

        /**
         * Returns an iterator referring to the beginning.
         * The begin() and end() methods are needed for the range-based for loop.
        */
        iterator begin();

        /**
         * Returns an iterator referring to the end.
         * The begin() and end() methods are needed for the range-based for loop.
        */
        iterator end();

    private:
        std::vector<std::unique_ptr<JsonNode>> children;
    };
} // namespace json

#endif