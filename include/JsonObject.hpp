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

#ifndef JSON_OBJECT_HPP
#define JSON_OBJECT_HPP

#include "JsonNode.hpp"

#include <unordered_map>
#include <memory>
#include <vector>

namespace json
{
    /**
     * Represents a node that holds a collection of child nodes. Every child is associated with a name.
    */
    class JsonObject : public JsonNode
    {
    public:
        struct Value
        {
            // The child node.
            std::unique_ptr<JsonNode> node;

            // An index indicating when this node was added.
            // We need this if we want to be able to sort based on insertion order.
            size_t orderIndex;
        };

        /**
         * An iterator that lets the user iterate over all children.
         * The main purpose of this class is to make sure 
         * the JsonObject can work with the range-based for loop.
        */
        class iterator
        {
        public:
            /**
             * Creates a new iterator object.
            */
            iterator(std::unordered_map<std::string, Value>::iterator it);

            /**
             * The prefix operator will return an iterator object referring to the next pair in the map.
            */
            iterator operator++();

            /**
             * The postfix operator will return an iterator object referring to the current pair and increment itself.
            */
            iterator operator++(int);

            /**
             * Returns true if two iterator objects are referring to different pairs.
            */
            bool operator!=(const iterator &rhs);

            /**
             * Returns true if two iterator objects are referring to the same pair.
            */
            bool operator==(const iterator &rhs);

            /**
             * Returns the pair that the iterator object is referring to.
            */
            std::pair<const std::string &, JsonNode &> operator*();

        private:
            std::unordered_map<std::string, Value>::iterator it;
        };

        /**
         * Creates a new JsonObject without a parent.
        */
        JsonObject();

        /**
         * Creates a new JsonObject with a parent.
        */
        JsonObject(JsonNode *parent);

        /**
         * Returns JsonNodeType::Object.
        */
        JsonNodeType getType() const noexcept override;

        /**
         * Returns a reference to this JsonObject.
        */
        JsonObject &toObject() override;

        /**
         * Returns a const reference to this JsonObject.
        */
        const JsonObject &toObject() const override;

        /**
         * Returns the child node with a specific name.
         * If no child has the specified name then an error will be thrown.
        */
        JsonNode &operator[](const std::string &name) override;

        /**
         * Returns the immutable child node with a specific name.
         * If no child has the specified name then an error will be thrown.
        */
        const JsonNode &operator[](const std::string &name) const override;

        /**
         * Will set a new JsonArray object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonArray.
        */
        JsonArray &setArray(const std::string &name);

        /**
         * Will set a new JsonArray object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonArray.
        */
        JsonArray &setArray(std::string &&name);

        /**
         * Will set a new object of type JsonObject with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonObject.
        */
        JsonObject &setObject(const std::string &name);

        /**
         * Will set a new object of type JsonObject with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonObject.
        */
        JsonObject &setObject(std::string &&name);

        /**
         * Will set a new JsonBool object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonBool.
        */
        JsonBool &setBool(const std::string &name, bool value);

        /**
         * Will set a new JsonBool object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonBool.
        */
        JsonBool &setBool(std::string &&name, bool value);

        /**
         * Will set a new JsonNull object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonNull.
        */
        JsonNull &setNull(const std::string &name);

        /**
         * Will set a new JsonNull object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonNull.
        */
        JsonNull &setNull(std::string &&name);

        /**
         * Will set a new JsonNumber object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonNumber.
        */
        JsonNumber &setNumber(const std::string &name, double value);

        /**
         * Will set a new JsonNumber object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonNumber.
        */
        JsonNumber &setNumber(std::string &&name, double value);

        /**
         * Will set a new JsonString object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonString.
        */
        JsonString &setString(const std::string &name, const std::string &value);

        /**
         * Will set a new JsonString object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonString.
        */
        JsonString &setString(std::string &&name, const std::string &value);

        /**
         * Will set a new JsonString object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonString.
        */
        JsonString &setString(const std::string &name, std::string &&value);

        /**
         * Will set a new JsonString object with a specific name.
         * If the name is already taken then the old node will be replaced with the new JsonString.
        */
        JsonString &setString(std::string &&name, std::string &&value);

        /**
         * Returns true if this JsonObject has no children.
        */
        bool empty() const noexcept;

        /**
         * Returns the number of children in this JsonObject.
        */
        size_t getChildCount() const noexcept;

        /**
         * Returns true if a child in this JsonObject is associated with the specified name.
        */
        bool hasChild(const std::string &name) const noexcept;

        /**
         * Returns the child node with a specific name.
         * If no child has the specified name then an error will be thrown.
         * This method is equivalent to the subscript operator.
        */
        JsonNode &getChild(const std::string &name);

        /**
         * Returns the immutable child node with a specific name.
         * If no child has the specified name then an error will be thrown.
         * This method is equivalent to the subscript operator.
        */
        const JsonNode &getChild(const std::string &name) const;

        /**
         * Removes a child node with a specific name. 
        */
        void removeChild(const std::string &name);

        /**
         * Returns an iterator referring to the beginning.
         * The begin() and end() methods are needed for the range-based for loop.
         * Note that the iterator will iterate through the pairs in seemingly random order.
         * Consider the sort() method if you would like to iterate through the pairs based on the insertion order.
        */
        iterator begin();

        /**
         * Returns an iterator referring to the end.
         * The begin() and end() methods are needed for the range-based for loop.
         * Note that the iterator will iterate through the pairs in seemingly random order.
         * Consider the sort() method if you would like to iterate through the pairs based on the insertion order.
        */
        iterator end();

        /**
         * Will move the pairs into a vector and sort the vector based on the insertion order of each pair.
         * The vector is then returned.
        */
        std::vector<std::pair<const std::string &, JsonNode &>> sort();

    private:
        // In order to keep track of the insertion order we have a counter
        // that is incremented every time we add a new child.
        size_t childCounter;
        std::unordered_map<std::string, Value> children;

        // Private helper methods that can be used to set a new child.
        template <typename ChildType>
        ChildType &setChild(const std::string &name);

        template <typename ChildType>
        ChildType &setChild(std::string &&name);

        template <typename ChildType, typename ArgType>
        ChildType &setChild(const std::string &name, ArgType arg);

        template <typename ChildType, typename ArgType>
        ChildType &setChild(std::string &&name, ArgType arg);
    };
} // namespace json

#endif