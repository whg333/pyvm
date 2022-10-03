//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_BYTECODE_HPP
#define PYVM_BYTECODE_HPP

class ByteCode{
public:
    static const unsigned char BINARY_ADD = 23;

    static const unsigned char PRINT_ITEM = 71;
    static const unsigned char PRINT_NEWLINE = 72;
    static const unsigned char RETURN_VALUE = 83;

    static const unsigned char HAS_ARGUMENT = 90;

    static const unsigned char LOAD_CONST = 100;
};

#endif //PYVM_BYTECODE_HPP
