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

#include "JsonLexer.hpp"

#include <istream>

namespace json
{
    JsonToken::JsonToken(JsonTokenType type) : type(type)
    {
    }

    JsonToken::JsonToken(JsonTokenType type, std::string &&value) : type(type), value(std::move(value))
    {
    }

    JsonToken JsonLexer::nextToken(std::istream &input)
    {
        char c;

        if (input >> c)
        {
            switch (c)
            {
            case '[':
                return {JsonTokenType::BeginArray};
            case '{':
                return {JsonTokenType::BeginObject};
            case ']':
                return {JsonTokenType::EndArray};
            case '}':
                return {JsonTokenType::EndObject};
            case ':':
                return {JsonTokenType::NameSeparator};
            case ',':
                return {JsonTokenType::ValueSeparator};
            case 'f':
                read(input, "alse"); // Make sure that the next characters in the stream are 'a', 'l', 's' and 'e'.
                return {JsonTokenType::False};
            case 't':
                read(input, "rue");
                return {JsonTokenType::True};
            case 'n':
                read(input, "ull");
                return {JsonTokenType::Null};
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return {JsonTokenType::Number, readNumber(input, c)};
            case '\"':
                return {JsonTokenType::String, readString(input)};
            default:
                throw std::runtime_error("Found illegal character: '" + std::string(1, c) + "'");
            }
        }

        return {JsonTokenType::EndOfFile};
    }

    void JsonLexer::read(std::istream &input, const std::string &str)
    {
        char c;
        for (size_t i = 0; i < str.length(); i++)
        {
            if (input.get(c))
            {
                if (c != str[i])
                    throw std::runtime_error("Found illegal character: '" + std::string(1, c) + "'");
            }
            else
            {
                throw std::runtime_error("Could not read the next character");
            }
        }
    }

    std::string JsonLexer::readNumber(std::istream &input, char previous)
    {
        std::string number;
        char c = previous;

        // Check for optional minus.
        if (c == '-')
        {
            number += c;
            if (!(input.get(c)) || !isdigit(c))
                throw std::runtime_error("After a minus sign there must be at least one digit");
        }

        number += c;

        // We only want to continue to append digits if the number
        // doesn't start with zero. For example "0123" is not a valid number.
        if (c != '0')
        {
            number += readDigits(input);
        }

        // Check for optional fraction and exponent.
        if (!input.eof())
        {
            c = static_cast<char>(input.peek());
            if (c == '.')
            {
                number += readFraction(input);
                if (!input.eof())
                {
                    c = static_cast<char>(input.peek());
                    if (c == 'e' || c == 'E')
                    {
                        number += readExponent(input);
                    }
                }
            }
            else if (c == 'e' || c == 'E')
            {
                number += readExponent(input);
            }
        }

        return number;
    }

    std::string JsonLexer::readDigits(std::istream &input)
    {
        std::string digits;
        char c;
        while (input.get(c))
        {
            if (isdigit(c))
            {
                digits += c;
            }
            else
            {
                // If we get something that's not a digit put it back into the stream and break the loop.
                input.putback(c);
                break;
            }
        }
        return digits;
    }

    std::string JsonLexer::readFraction(std::istream &input)
    {
        std::string fraction = ".";
        char c;
        input.get(); // This will return a decimal point.

        if (!(input.get(c)) || !isdigit(c))
            throw std::runtime_error("After a decimal point there must be at least one digit");

        fraction += c;
        fraction += readDigits(input);
        return fraction;
    }

    std::string JsonLexer::readExponent(std::istream &input)
    {
        std::string exponent;
        char c;
        input.get(c);

        exponent += c; // We append 'e' or 'E'.

        if (!input.get(c))
            throw std::runtime_error("A number cannot end with 'e' or 'E'");

        if (c == '-' || c == '+')
        {
            exponent += c;
            if (!(input.get(c)) || !isdigit(c))
                throw std::runtime_error("After a minus or plus sign there must be at least one digit");
        }

        if (!isdigit(c))
            throw std::runtime_error("A valid exponent requires at least one digit");

        exponent += c;
        exponent += readDigits(input);
        return exponent;
    }

    std::string JsonLexer::readString(std::istream &input)
    {
        std::string string;
        char c;

        while (true)
        {
            if (input.get(c))
            {
                if (c == '\"') // We reached ending quotation mark, lets break the loop and return the string.
                    break;
                else if (c == '\\') // Escape sequence found.
                    string += readEscapeSequence(input);
                else
                    string += c;
            }
            else
            {
                throw std::runtime_error("Could not read the next character");
            }
        }

        return string;
    }

    std::string JsonLexer::readEscapeSequence(std::istream &input)
    {
        std::string escaped;
        char c;

        if (!input.get(c))
            throw std::runtime_error("There must be at least one more character after '\\'");

        switch (c)
        {
        case '\"':
            escaped += '\"';
            break;
        case '\\':
            escaped += '\\';
            break;
        case '/':
            escaped += '/';
            break;
        case 'b':
            escaped += '\b';
            break;
        case 'f':
            escaped += '\f';
            break;
        case 'n':
            escaped += '\n';
            break;
        case 'r':
            escaped += '\r';
            break;
        case 't':
            escaped += '\t';
            break;
        case 'u':
            escaped += readUnicodeEscapeSequence(input);
            break;
        default:
            throw std::runtime_error("Found illegal escape sequence: '\\" + std::string(1, c) + "'");
        }

        return escaped;
    }

    std::string JsonLexer::readUnicodeEscapeSequence(std::istream &input)
    {
        // We read four hexadecimal digits from the stream.
        std::string hex;
        char c;
        for (size_t i = 0; i < 4; i++)
        {
            if (input.get(c))
            {
                if (!isxdigit(c))
                    throw std::runtime_error("Found illegal character: '" + std::string(1, c) + "'");
                hex += c;
            }
            else
            {
                throw std::runtime_error("Could not read the next character");
            }
        }

        std::string result;

        int code = std::stoi(hex, nullptr, 16);

        //  We convert the UTF-16 code into UTF-8.
        //
        //  Interval                    UTF-16                          UTF-8
        //  U+0000 – U+007F             00000000 0xxxxxxx               0xxxxxxx
        //  U+0080 – U+07FF             00000xxx xxxxxxxx	            110xxxxx 10xxxxxx
        //  U+0800 – U+FFFF             xxxxxxxx xxxxxxxx               1110xxxx 10xxxxxx 10xxxxxx

        if (0 <= code && code <= 0x75)
        {
            result += static_cast<char>(code);
        }
        else if (0x80 <= code && code <= 0x7FF)
        {
            result += static_cast<char>(((0xC0 & code) >> 6) | ((0x700 & code) >> 6) | 0xC0);
            result += static_cast<char>((0x3F & code) | 0x80);
        }
        else if (0x800 <= code && code <= 0xFFFF)
        {
            result += static_cast<char>(((0xF000 & code) >> 12) | 0xE0);
            result += static_cast<char>(((0xC0 & code) >> 6) | ((0xF00 & code) >> 6) | 0x80);
            result += static_cast<char>((0x3F & code) | 0x80);
        }
        else
        {
            throw std::runtime_error("Unsupported unicode escape sequence");
        }

        return result;
    }

} // namespace json