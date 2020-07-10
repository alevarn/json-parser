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

#ifndef JSON_DOCUMENT_HPP
#define JSON_DOCUMENT_HPP

#include "JsonNode.hpp"

#include <memory>

namespace json
{
    /**
     * Represents a JSON document and stores the root node.
    */
    class JsonDocument
    {
    public:
        /**
         * Creates a new empty JsonDocument.
        */
        JsonDocument();

        /**
         * Creates a new JsonDocument with a root node.
        */
        JsonDocument(std::unique_ptr<JsonNode> root);

        /**
         * Will set a JsonArray object as root replacing the previous root node if necessary. 
        */
        JsonArray &setArrayAsRoot();

        /**
         * Will set an object of type JsonObject as root replacing the previous root node if necessary. 
        */
        JsonObject &setObjectAsRoot();

        /**
         * Will set a JsonBool object as root replacing the previous root node if necessary. 
        */
        JsonBool &setBoolAsRoot(bool value);

        /**
         * Will set a JsonNull object as root replacing the previous root node if necessary. 
        */
        JsonNull &setNullAsRoot();

        /**
         * Will set a JsonNumber object as root replacing the previous root node if necessary. 
        */
        JsonNumber &setNumberAsRoot(double value);

        /**
         * Will set a JsonString object as root replacing the previous root node if necessary. 
        */
        JsonString &setStringAsRoot(const std::string &value);

        /**
         * Will set a JsonString object as root replacing the previous root node if necessary. 
        */
        JsonString &setStringAsRoot(std::string &&value);

        /**
         * Returns true if a root is set, otherwise false.
        */
        bool hasRoot() const noexcept;

        /**
         * Returns a reference to the current root node.
        */
        JsonNode &getRoot();

        /**
         * Will write the contents of this document to an output stream with a desirable tab size.
        */
        void writeToStream(std::ostream &output, size_t tabSize = 4) const;

        /**
         * Will write the contents of this document to a file.
        */
        void saveToFile(const std::string &filePath, size_t tabSize = 4) const;

        /**
         * Will return the contents of this document as a string. 
        */
        std::string toString(size_t tabSize = 4) const;

        /**
         * Creates a new empty JsonDocument.
        */
        static JsonDocument create();

        /**
         * Creates a new JsonDocument from an input stream.
        */
        static JsonDocument createFromStream(std::istream &input);

        /**
         * Creates a new JsonDocument from a file.
        */
        static JsonDocument createFromFile(const std::string &filePath);

        /**
         * Creates a new JsonDocument from a string.
        */
        static JsonDocument createFromString(const std::string &jsonText);

    private:
        // Recursive method that writes a node and all its child nodes to an output stream.
        static void writeNode(std::ostream &output, const JsonNode &node, std::string indent, size_t tabSize);

        std::unique_ptr<JsonNode> root;
    };
} // namespace json

#endif