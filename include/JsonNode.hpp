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

#ifndef JSON_NODE_HPP
#define JSON_NODE_HPP

#include <string>

namespace json
{
    /**
     * In order to identify the node type during runtime we have a list of all possible node types.
    */
    enum class JsonNodeType
    {
        Array,
        Object,
        Bool,
        Null,
        Number,
        String
    };

    // Forward-declare classes that are derived from JsonNode.
    // This way we can return references to them from the base class.
    class JsonArray;
    class JsonObject;
    class JsonBool;
    class JsonNull;
    class JsonNumber;
    class JsonString;

    /**
     * This is an abstract base class for all different types of values that can exist in JSON text.
    */
    class JsonNode
    {
    public:
        /**
         * Creates a new JsonNode without a parent.
        */
        JsonNode();

        /**
         * Creates a new JsonNode with a parent.
        */
        JsonNode(JsonNode *parent);

        /**
         * Destroys the JsonNode.
        */
        virtual ~JsonNode();

        /**
         * Returns true if the node has a parent, otherwise false.
        */
        bool hasParent() const noexcept;

        /**
         * Returns a reference to the parent.
        */
        JsonNode &getParent() noexcept;

        /**
         * Returns a const reference to the parent.
        */
        const JsonNode &getParent() const noexcept;

        /**
         * Returns the type of the node.
         * This is always one of the derived classes: JsonArray, JsonObject, JsonBool, JsonNumber or JsonString.
        */
        virtual JsonNodeType getType() const noexcept = 0;

        /**
         * Converts this object to a JsonArray reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual JsonArray &toArray();

        /**
         * Converts this object to a const JsonArray reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual const JsonArray &toArray() const;

        /**
         * Converts this object to a JsonObject reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual JsonObject &toObject();

        /**
         * Converts this object to a const JsonObject reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual const JsonObject &toObject() const;

        /**
         * Converts this object to a JsonBool reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual JsonBool &toBool();

        /**
         * Converts this object to a const JsonBool reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual const JsonBool &toBool() const;

        /**
         * Converts this object to a JsonNull reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual JsonNull &toNull();

        /**
         * Converts this object to a const JsonNull reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual const JsonNull &toNull() const;

        /**
         * Converts this object to a JsonNumber reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual JsonNumber &toNumber();

        /**
         * Converts this object to a const JsonNumber reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual const JsonNumber &toNumber() const;

        /**
         * Converts this object to a JsonString reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual JsonString &toString();

        /**
         * Converts this object to a const JsonString reference. If that is not possible then this method will throw a runtime_error.
        */
        virtual const JsonString &toString() const;

        /**
         * Implicit conversion to a JsonArray reference if this fails then a runtime_error will be thrown. 
        */
        operator JsonArray &();

        /**
         * Implicit conversion to a const JsonArray reference if this fails then a runtime_error will be thrown. 
        */
        operator const JsonArray &() const;

        /**
         * Implicit conversion to a JsonObject reference if this fails then a runtime_error will be thrown. 
        */
        operator JsonObject &();

        /**
         * Implicit conversion to a const JsonObject reference if this fails then a runtime_error will be thrown. 
        */
        operator const JsonObject &() const;

        /**
         * Implicit conversion to a JsonBool reference if this fails then a runtime_error will be thrown. 
        */
        operator JsonBool &();

        /**
         * Implicit conversion to a const JsonBool reference if this fails then a runtime_error will be thrown. 
        */
        operator const JsonBool &() const;

        /**
         * Implicit conversion to a JsonNull reference if this fails then a runtime_error will be thrown. 
        */
        operator JsonNull &();

        /**
         * Implicit conversion to a const JsonNull reference if this fails then a runtime_error will be thrown. 
        */
        operator const JsonNull &() const;

        /**
         * Implicit conversion to a JsonNumber reference if this fails then a runtime_error will be thrown. 
        */
        operator JsonNumber &();

        /**
         * Implicit conversion to a const JsonNumber reference if this fails then a runtime_error will be thrown. 
        */
        operator const JsonNumber &() const;

        /**
         * Implicit conversion to a JsonString reference if this fails then a runtime_error will be thrown. 
        */
        operator JsonString &();

        /**
         * Implicit conversion to a const JsonString reference if this fails then a runtime_error will be thrown. 
        */
        operator const JsonString &() const;

        /**
         * Returns a child at a specific index. This only works if the object is of type JsonArray. 
        */
        virtual JsonNode &operator[](size_t);

        /**
         * Returns an immutable child at a specific index. This only works if the object is of type JsonArray. 
        */
        virtual const JsonNode &operator[](size_t) const;

        /**
         * Returns a child with a specific name. This only works if the object is of type JsonObject. 
        */
        virtual JsonNode &operator[](const std::string &);

        /**
         * Returns an immutable child with a specific name. This only works if the object is of type JsonObject. 
        */
        virtual const JsonNode &operator[](const std::string &) const;

    private:
        JsonNode *parent;
    };

} // namespace json

#endif