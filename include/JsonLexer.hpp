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

#ifndef JSON_LEXER_HPP
#define JSON_LEXER_HPP

#include <string>

namespace json
{
    /**
     * A list of all valid token types that can be found in JSON text.
    */
    enum class JsonTokenType
    {
        BeginArray,     // [
        BeginObject,    // {
        EndArray,       // ]
        EndObject,      // }
        NameSeparator,  // :
        ValueSeparator, // ,
        False,          // false
        True,           // true
        Null,           // null
        Number,
        String,
        EndOfFile
    };

    /**
     * A JsonToken object will store the token type and a string value.
    */
    struct JsonToken
    {
        JsonTokenType type;

        // This field is used when we find a number or string in the JSON text.
        std::string value;

        JsonToken(JsonTokenType type);
        JsonToken(JsonTokenType type, std::string &&value);
    };

    /**
     * A class for doing lexical analysis on JSON text.
    */
    class JsonLexer
    {
    public:
        /**
         * Returns the next token from the input stream. 
        */
        static JsonToken nextToken(std::istream &input);

    private:
        /**
         * Will read characters from the stream and make sure they match the desired string that was passed in with this method.
         * If they don't match a std::runtime_error expection will be thrown.
        */
        static void read(std::istream &input, const std::string &str);

        /**
         * Will read a number from the stream and return it as a string.
         * The number must satisfy the following ABNF rules (taken from RFC 8259):
         * 
         * number = [ minus ] int [ frac ] [ exp ]
         * decimal-point = %x2E       ; .
         * digit1-9 = %x31-39         ; 1-9
         * e = %x65 / %x45            ; e E
         * exp = e [ minus / plus ] 1*DIGIT
         * frac = decimal-point 1*DIGIT 
         * int = zero / ( digit1-9 *DIGIT )
         * minus = %x2D               ; -
         * plus = %x2B                ; +
         * zero = %x30                ; 0
         * 
         * Upon violation a std::runtime_error will be thrown.
        */
        static std::string readNumber(std::istream &input, char previous);

        /**
         * Will read digits from the input stream and returns them as a string.
        */
        static std::string readDigits(std::istream &input);

        /**
         * Will read a fraction.
        */
        static std::string readFraction(std::istream &input);

        /**
         * Will read an exponent.
        */
        static std::string readExponent(std::istream &input);

        /**
         * Will read a "json-string" from the stream and return it as a string.
         * The "json-string" must satisfy the following ABNF rules (taken from RFC 8259):
         * 
         * string = quotation-mark *char quotation-mark
         * char = unescaped /
         * escape (
         *     %x22 /          ; "    quotation mark  U+0022
         *     %x5C /          ; \    reverse solidus U+005C
         *     %x2F /          ; /    solidus         U+002F
         *     %x62 /          ; b    backspace       U+0008
         *     %x66 /          ; f    form feed       U+000C
         *     %x6E /          ; n    line feed       U+000A
         *     %x72 /          ; r    carriage return U+000D
         *     %x74 /          ; t    tab             U+0009
         *     %x75 4HEXDIG )  ; uXXXX                U+XXXX
         * 
         * escape = %x5C              ; \
         * quotation-mark = %x22      ; "
         * unescaped = %x20-21 / %x23-5B / %x5D-10FFFF
         * 
         * Upon violation a std::runtime_error will be thrown.
        */
        static std::string readString(std::istream &input);

        /**
         * Will read an escape sequence and unescape it.
        */
        static std::string readEscapeSequence(std::istream &input);

        /**
         * Will read an unicode escape sequence for exampe \u2661.
        */
        static std::string readUnicodeEscapeSequence(std::istream &input);
    };
} // namespace json

#endif