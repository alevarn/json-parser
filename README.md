# A JSON parser for C++17
This is a simplistic and lightweight JSON parser for C++17. 
It works with JSON documents that follow the format specified in [RFC 8259](https://tools.ietf.org/html/rfc8259).

## How to use this library with CMake
Clone this repository into a subdirectory of your project folder and add the following to your project's CMakeLists.txt:
```cmake
# If you have testing enabled and don't want to run the json-parser library's tests 
# you can set JSON_PARSER_TEST_ENABLED to FALSE.
set(JSON_PARSER_TEST_ENABLED FALSE)

# You should replace "deps/json-parser" with the path you are using.
add_subdirectory(deps/json-parser)

# The final step is to link the static library called "json-parser" into your executable.
# You should replace "your-exe" with the name you are using.
target_link_libraries(your_exe PRIVATE json-parser)
```

## Example code
To make it easy to use this library, we show code examples of how this library works.
In this quick tutorial we will go through the following:
1. How to read a JSON file (of known structure) and print its contents.
2. How to read a JSON file (of unknown structure) and print its contents.
3. How to modify a value in a JSON file and save it.
4. How to create a JSON document in a program and save it to a file.

### Read a JSON file (of known structure) and print its contents
Let's say we have a JSON file called **customers.json** that stores information about all our customers. 
Down below you can see that the file contains information about two people James and John.
```json
[
    {
        "firstName": "James",
        "lastName": "Smith",
        "age": 40,
        "married": true,
        "hobbies": ["Golf", "football"]
    },
    {
        "firstName": "John",
        "lastName": "Wilson",
        "age": 32,
        "married": false,
        "hobbies": ["Basketball", "Skiing", "Surfing"]
    }
]
```

Now we know how the JSON file looks and is structured. The next step is to write a program that goes through each customer in this file and prints everything we know about that customer.
```c++
#include <iostream>

#include "Json.hpp"

using namespace json;

int main()
{
    JsonDocument doc = JsonDocument::createFromFile("customers.json");

    JsonArray &customers = doc.getRoot();

    for (JsonObject &customer : customers)
    {
        JsonString &firstName = customer["firstName"];
        JsonString &lastName = customer["lastName"];
        JsonNumber &age = customer["age"];
        JsonBool &married = customer["married"];

        std::cout << firstName << std::endl;
        std::cout << lastName << std::endl;
        std::cout << age << std::endl;
        std::cout << (married ? "Married" : "Not married") << std::endl;

        JsonArray &hobbies = customer["hobbies"];

        for(JsonString &hobby : hobbies)
        {
            std::cout << hobby << std::endl;
        }
    }

    return 0;
}
```
Everything in the json-parser library is declared within the **json** namespace. So to save some typing we can put it into the global namespace by writing: ``using namespace json;``

The ``JsonDocument`` class will load the file **customers.json** into memory. We get the root node by using the ``getRoot()`` method on our JsonDocument object.

We know that the root node will be of type JsonArray (because we saw the structure of the json file). 
If we had made a mistake and written: ``JsonObject &customers = doc.getRoot();`` a ``std::runtime_error`` exception would be thrown. 

The classes: ``JsonArray``, ``JsonObject``, ``JsonBool``, ``JsonNull``, ``JsonNumber`` and ``JsonString`` are all derived from the abstract base class ``JsonNode``.
The json-parser library will allow implicit conversions between these types (so no cast is needed).

### Read a JSON file (of unknown structure) and print its contents
Now to a problem that is a bit more difficult. In the previous task we knew the structure of the JSON file meaning we didn't have to guess the type of anything, we knew that the file had an array of objects and that every object represented a customer. We knew that the keys *"firstName"* and *"lastName"* both were associated with values of ``JsonString``. In addition that the key *"age"* was associated with a ``JsonNumber`` and that the key *"married"* was associated with a ``JsonBool``, we also knew that the key *"hobbies"* was associated with a ``JsonArray`` that stored every hobby as a ``JsonString`` value.

If we have never seen the JSON file but still want to print all its contents, we can do so by using the abstract base class ``JsonNode`` and the method ``getType()``. 
With the help of the ``getType()`` method we can determine if the node is an array, object, bool, number, string or null value at runtime.
```c++
#include <iostream>

#include "Json.hpp"

using namespace json;

void printNode(JsonNode &node)
{
    switch (node.getType())
    {
    case JsonNodeType::Array:
        for (auto &child : node.toArray())
            printNode(child);
        break;
    case JsonNodeType::Object:
        // This will print all children of the object in seemingly random order.
        // If you want the children sorted based on insertion order
        // you can write for(auto &pair : node.toObject().sort()) instead.
        for (auto pair : node.toObject())
            printNode(pair.second);
        break;
    case JsonNodeType::Bool:
        std::cout << (node.toBool() ? "true" : "false") << std::endl;
        break;
    case JsonNodeType::Null:
        std::cout << "null" << std::endl;
        break;
    case JsonNodeType::Number:
        std::cout << node.toNumber() << std::endl;
        break;
    case JsonNodeType::String:
        std::cout << node.toString() << std::endl;
        break;
    }
}

int main()
{
    JsonDocument doc = JsonDocument::createFromFile("unknown.json");

    JsonNode &root = doc.getRoot();

    printNode(root);

    return 0;
}
```
Note that ``printNode`` is a recursive function. If the node is of type ``JsonArray`` or ``JsonObject`` 
we iterate over each child and call printNode with the child as argument. If the node is of type
``JsonBool``, ``JsonNull``, ``JsonNumber`` or ``JsonString`` we print the value.
