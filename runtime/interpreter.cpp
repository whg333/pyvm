//
// Created by whg on 2022/10/3.
//

#include <stdio.h>
#include "interpreter.hpp"
#include "code/bytecode.hpp"
#include "object/pyInteger.hpp"

Interpreter::Interpreter() {

}

void Interpreter::run(CodeObject *codeObj) {
    int pc = 0;
    PyString* bytecodes = codeObj->_bytecodes;
    int code_length = bytecodes->length();
    _stack = new ArrayList<PyObject*>(code_length);
    _consts = codeObj->_consts;

    while(pc < code_length){
        unsigned char op_code = bytecodes->value()[pc++];
        bool has_argument = (op_code & 0xFF) >= ByteCode::HAS_ARGUMENT;

        int op_arg = -1;
        if(has_argument){
            int byte1 = bytecodes->value()[pc++] & 0xFF;
            op_arg = (bytecodes->value()[pc++] & 0xFF) << 8 | byte1;
        }

        PyInteger* lhs, * rhs;
        PyObject* v, * w, * u, * attr, * const_val;

        switch (op_code) {
            case ByteCode::LOAD_CONST:
                const_val = _consts->get(op_arg);
                _stack->push(const_val);
                break;
            case ByteCode::PRINT_ITEM:
                v = _stack->pop();
                v->print();
                break;
            case ByteCode::PRINT_NEWLINE:
                printf("\n");
                break;
            case ByteCode::BINARY_ADD:
                v = _stack->pop();
                w = _stack->pop();
                _stack->push(w->add(v));
                break;
            case ByteCode::RETURN_VALUE:
                _stack->pop();
                break;
            default:
                printf("Error: Unknown op code %d\n", op_code);
        }
    }
}