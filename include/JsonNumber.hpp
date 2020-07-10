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

#ifndef JSON_NUMBER_HPP
#define JSON_NUMBER_HPP

#include "JsonNode.hpp"

namespace json
{
    /**
     * Represents a node that can store a decimal value.
    */
    class JsonNumber : public JsonNode
    {
    public:
        /**
         * Creates a new JsonNumber without a parent.
        */
        JsonNumber(double value);

        /**
         * Creates a new JsonNumber with a parent.
        */
        JsonNumber(JsonNode *parent, double value);

        /**
         * Returns JsonNodeType::Number.
        */
        JsonNodeType getType() const noexcept override;

        /**
         * Returns a reference to this JsonNumber.
        */
        JsonNumber &toNumber() override;

        /**
         * Returns a const reference to this JsonNumber.
        */
        const JsonNumber &toNumber() const override;

        /**
         * Returns a reference to the double value this JsonNumber is storing.
        */
        double &data();

        /**
         * Implicit conversion to a double reference.
        */
        operator double &();

    private:
        double value;
    };
} // namespace json

#endif