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

#include <stdexcept>
#include <sstream>
#include <fstream>

using namespace json;

int main(int argc, char **argv)
{
    if (argc < 2)
        throw std::runtime_error("Provide sufficient arguments");

    // The file to parse.
    std::string sourcePath = argv[1];

    // The file we want to write to.
    std::string targetPath = argv[2];

    // Parse the source file and save it to the target file.
    JsonDocument::createFromFile(sourcePath).saveToFile(targetPath);

    std::ifstream inSource(sourcePath);

    if (!inSource.is_open())
        throw std::runtime_error("Could not open file: " + sourcePath);

    std::ifstream inTarget(targetPath);

    if (!inTarget.is_open())
        throw std::runtime_error("Could not open file: " + targetPath);

    std::stringstream sourceContent;
    std::stringstream targetContent;

    // Read the two files.
    sourceContent << inSource.rdbuf();
    targetContent << inTarget.rdbuf();

    // Compare the two files, if the parser works they should be equal.
    if (sourceContent.str() != targetContent.str())
        throw std::runtime_error("The two files were not equal");

    inSource.close();
    inTarget.close();
}