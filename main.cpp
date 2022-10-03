#include <iostream>
#include "util/bufferedInputStream.hpp"
#include "code/binaryFileParser.hpp"

int main(int argc, char** argv) {
    std::cout << "Hello, PyVM!" << std::endl;
    if(argc <= 1){
        printf("PyVM need a parameter[filename]\n");
        return 0;
    }
    BufferedInputStream stream(argv[1]);
    BinaryFileParser parser(&stream);
    CodeObject* code = parser.parse();
    return 0;
}
