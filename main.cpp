#include <iostream>
#include "util/bufferedInputStream.hpp"
#include "code/binaryFileParser.hpp"
#include "runtime/interpreter.hpp"

#include "object/pyInteger.hpp"

int main(int argc, char** argv) {
    std::cout << "Hello, PyVM!" << std::endl;
    if(argc <= 1){
        printf("PyVM need a parameter[filename]\n");
        return 0;
    }
    BufferedInputStream stream(argv[1]);
    BinaryFileParser parser(&stream);
    CodeObject* codeObj = parser.parse();
    Interpreter interpreter;
    interpreter.run(codeObj);

    // PyObject* int1 = new PyInteger(1);
    // PyObject* int2 = new PyInteger(2);
    // PyObject* ret = int1->add(int2);
    // ret->print();
    return 0;
}
