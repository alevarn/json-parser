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

#ifndef JSON_BOOL_HPP
#define JSON_BOOL_HPP

#include "JsonNode.hpp"

namespace json
{
    /**
     * Represents a node that can store a boolean value.
    */
    class JsonBool : public JsonNode
    {
    public:
        /**
         * Creates a new JsonBool without a parent.
        */
        JsonBool(bool value);

        /**
         * Creates a new JsonBool with a parent.
        */
        JsonBool(JsonNode *parent, bool value);

        /**
         * Returns JsonNodeType::Bool.
        */
        JsonNodeType getType() const noexcept override;

        /**
         * Returns a reference to this JsonBool.
        */
        JsonBool &toBool() override;

        /**
         * Returns a const reference to this JsonBool.
        */
        const JsonBool &toBool() const override;

        /**
         * Returns a reference to the boolean value this JsonBool is storing.
        */
        bool &data() noexcept;

        /**
         * Returns a const reference to the boolean value this JsonBool is storing.
        */
        const bool &data() const noexcept;

        /**
         * Implicit conversion to a boolean reference.
        */
        operator bool &();

        /**
         * Implicit conversion to a boolean const reference.
        */
        operator const bool &() const;

    private:
        bool value;
    };
} // namespace json

#endif