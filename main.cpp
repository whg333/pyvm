#include <iostream>
#include "util/bufferedInputStream.hpp"

int main(int argc, char** argv) {
    std::cout << "Hello, PyVM!" << std::endl;
    if(argc <= 1){
        printf("PyVM need a parameter[filename]\n");
        return 0;
    }
    BufferedInputStream stream(argv[1]);
    printf("magic number is 0x%x\n", stream.read_int());
    return 0;
}
