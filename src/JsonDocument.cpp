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

#include "JsonDocument.hpp"
#include "JsonArray.hpp"
#include "JsonObject.hpp"
#include "JsonBool.hpp"
#include "JsonNull.hpp"
#include "JsonNumber.hpp"
#include "JsonString.hpp"
#include "JsonParser.hpp"

#include <fstream>
#include <sstream>

namespace json
{
    JsonDocument::JsonDocument() : root(nullptr)
    {
    }

    JsonDocument::JsonDocument(std::unique_ptr<JsonNode> root) : root(std::move(root))
    {
    }

    JsonArray &JsonDocument::setArrayAsRoot()
    {
        root = std::unique_ptr<JsonArray>(new JsonArray());
        return *root;
    }

    JsonObject &JsonDocument::setObjectAsRoot()
    {
        root = std::unique_ptr<JsonObject>(new JsonObject());
        return *root;
    }

    JsonBool &JsonDocument::setBoolAsRoot(bool value)
    {
        root = std::unique_ptr<JsonBool>(new JsonBool(value));
        return *root;
    }

    JsonNull &JsonDocument::setNullAsRoot()
    {
        root = std::unique_ptr<JsonNull>(new JsonNull());
        return *root;
    }

    JsonNumber &JsonDocument::setNumberAsRoot(double value)
    {
        root = std::unique_ptr<JsonNumber>(new JsonNumber(value));
        return *root;
    }

    JsonString &JsonDocument::setStringAsRoot(const std::string &value)
    {
        root = std::unique_ptr<JsonString>(new JsonString(value));
        return *root;
    }

    JsonString &JsonDocument::setStringAsRoot(std::string &&value)
    {
        root = std::unique_ptr<JsonString>(new JsonString(std::move(value)));
        return *root;
    }

    bool JsonDocument::hasRoot() const noexcept
    {
        return root != nullptr;
    }

    JsonNode &JsonDocument::getRoot()
    {
        return *root;
    }

    void JsonDocument::writeToStream(std::ostream &output, size_t tabSize) const
    {
        if (hasRoot())
        {
            writeNode(output, *root, "", tabSize);
        }
    }

    void JsonDocument::saveToFile(const std::string &filePath, size_t tabSize) const
    {
        std::ofstream output(filePath);

        if (!output.is_open())
            throw std::runtime_error("Could not open file: " + filePath);

        writeToStream(output, tabSize);

        output.close();
    }

    std::string JsonDocument::toString(size_t tabSize) const
    {
        std::ostringstream output;
        writeToStream(output, tabSize);
        return output.str();
    }

    JsonDocument JsonDocument::create()
    {
        return JsonDocument();
    }

    JsonDocument JsonDocument::createFromStream(std::istream &input)
    {
        if (!input.good())
            throw std::runtime_error("The input stream was bad");
        std::unique_ptr<JsonNode> root = JsonParser::parse(input);
        return JsonDocument(std::move(root));
    }

    JsonDocument JsonDocument::createFromFile(const std::string &filePath)
    {
        std::ifstream input(filePath);

        if (!input.is_open())
            throw std::runtime_error("Could not open file: " + filePath);

        JsonDocument doc = createFromStream(input);
        input.close();
        return doc;
    }

    JsonDocument JsonDocument::createFromString(const std::string &jsonText)
    {
        std::istringstream input(jsonText);
        return createFromStream(input);
    }

    void JsonDocument::writeNode(std::ostream &output, const JsonNode &node, std::string indent, size_t tabSize)
    {
        switch (node.getType())
        {
        case JsonNodeType::Array:
        {
            const JsonArray &array = node;

            output << '[';

            // If the array is empty we would like to print [] without a newline in the middle.
            if (!array.empty())
                output << '\n';

            // Calculate new indent for child nodes.
            std::string newIndent = indent + std::string(tabSize, ' ');

            for (const JsonNode &child : array)
            {
                output << newIndent;
                writeNode(output, child, newIndent, tabSize);
                if (&child != &array[array.getChildCount() - 1])    // If last child don't print ','.
                    output << ',';
                output << '\n';
            }

            // Same reasoning as previous array.empty() check, we don't want spaces in the middle of [].
            if (!array.empty())
                output << indent;

            output << ']';
        }
        break;
        case JsonNodeType::Object:
        {
            const JsonObject &object = node;
            output << '{';

            if (!object.empty())
                output << '\n';

            std::string newIndent = indent + std::string(tabSize, ' ');

            // We want the pairs to be printed based on the insertion order therefore we sort the object first.
            // This is not necessary and will have a performance cost, but it's pretty and therefore we do it.
            std::vector<std::pair<const std::string &, const JsonNode &>> children = object.sort();
            for (const auto &pair : children)
            {
                output << newIndent << '\"' << pair.first << '\"' << ": ";
                writeNode(output, pair.second, newIndent, tabSize);
                if (&pair.second != &children[children.size() - 1].second)
                    output << ',';
                output << '\n';
            }

            if (!object.empty())
                output << indent;

            output << '}';
        }
        break;
        case JsonNodeType::Bool:
            output << (node.toBool() ? "true" : "false");
            break;
        case JsonNodeType::Null:
            output << "null";
            break;
        case JsonNodeType::Number:
            output << node.toNumber();
            break;
        case JsonNodeType::String:
            output << '\"' << node.toString().escaped() << '\"';
            break;
        }
    }

} // namespace json