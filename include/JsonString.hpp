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

#ifndef JSON_STRING_HPP
#define JSON_STRING_HPP

#include "JsonNode.hpp"

namespace json
{
    /**
     * Represents a node that can store a string value.
    */
    class JsonString : public JsonNode
    {
    public:
        /**
         * Creates a new JsonString without a parent.
        */
        JsonString(const std::string &value);

        /**
         * Creates a new JsonString without a parent.
        */
        JsonString(std::string &&value);

        /**
         * Creates a new JsonString with a parent.
        */
        JsonString(JsonNode *parent, const std::string &value);

        /**
         * Creates a new JsonString with a parent.
        */
        JsonString(JsonNode *parent, std::string &&value);

        /**
         * Returns JsonNodeType::String.
        */
        JsonNodeType getType() const noexcept override;

        /**
         * Returns a reference to this JsonString.
        */
        JsonString &toString() override;

        /**
         * Returns a const reference to this JsonString.
        */
        const JsonString &toString() const override;

        /**
         * Returns a reference to the string value this JsonString is storing.
        */
        std::string &data();

        /**
         * Returns a const reference to the string value this JsonString is storing.
        */
        const std::string &data() const;

        /**
         * Will escape the string and return it. So for example a newline will be replaced with \n.
        */
        std::string escaped() const noexcept;

        /**
         * Implicit conversion to a string reference.
        */
        operator std::string &();

        /**
         * Implicit conversion to a const string reference.
        */
        operator const std::string &() const;

        /**
         * Implicit conversion to a const char pointer.
        */
        operator const char *() const;

    private:
        std::string value;
    };
} // namespace json

#endif