//
// Created by whg on 2022/10/3.
//

#include <stdio.h>
#include "interpreter.hpp"
#include "code/bytecode.hpp"
#include "object/pyInteger.hpp"
#include "runtime/universe.hpp"

#define PUSH(x) _stack->add((x))
#define POP()   _stack->pop()

Interpreter::Interpreter() {
    Universe::genesis();
}

void Interpreter::run(CodeObject *codeObj) {
    int pc = 0;
    PyString* bytecodes = codeObj->_bytecodes;
    int code_length = bytecodes->length();
    _stack = new ArrayList<PyObject*>(code_length);
    _consts = codeObj->_consts;

    ArrayList<PyObject*>* names = codeObj->_names;
    Map<PyObject*, PyObject*>* locals = new Map<PyObject*, PyObject*>(); // 局部变量表

    char* bytecodeArr = const_cast<char *>(bytecodes->value());
    while(pc < code_length){
        unsigned char op_code = bytecodeArr[pc++];
        bool has_argument = (op_code & 0xFF) >= ByteCode::HAS_ARGUMENT;

        int op_arg = -1;
        if(has_argument){
            int byte1 = bytecodeArr[pc++] & 0xFF;
            op_arg = (bytecodeArr[pc++] & 0xFF) << 8 | byte1;
        }

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

            case ByteCode::COMPARE_OP:
                w = POP();
                v = POP();
                switch (op_arg) {
                    case ByteCode::LESS:
                        PUSH(v->less(w));
                        break;
                    case ByteCode::LESS_EQUAL:
                        PUSH(v->le(w));
                        break;
                    case ByteCode::EQUAL:
                        PUSH(v->equal(w));
                        break;
                    case ByteCode::NOT_EQUAL:
                        PUSH(v->not_equal(w));
                        break;
                    case ByteCode::GREATER:
                        PUSH(v->greater(w));
                        break;
                    case ByteCode::GREATER_EQUAL:
                        PUSH(v->ge(w));
                        break;
                }
                break;

            case ByteCode::POP_JUMP_IF_FALSE:
                v = POP();
                // if(((PyInteger*)v)->value() == 0){
                if(v == Universe::PyFalse){
                    pc = op_arg;
                }
                break;
            case ByteCode::JUMP_FORWARD:
                pc += op_arg;
                break;

            case ByteCode::JUMP_ABSOLUTE:
                pc = op_arg;
                break;

            case ByteCode::SETUP_LOOP:
                break;
            case ByteCode::POP_BLOCK:
                break;

            case ByteCode::STORE_NAME:
                v = names->get(op_arg);
                w = POP();
                locals->put(v, w);
                break;
            case ByteCode::LOAD_NAME:
                v = names->get(op_arg);
                w = locals->get(v);
                PUSH(w);
                break;

            default:
                printf("Error: Unknown op code %d\n", op_code);
        }
    }
}