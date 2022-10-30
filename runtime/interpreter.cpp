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
#define STACK_LV() _stack->size()

Interpreter::Interpreter() {
    Universe::genesis();
}

void Interpreter::run(CodeObject *codeObj) {

    _stack = new ArrayList<PyObject*>(codeObj->_stack_size);
    _consts = codeObj->_consts;

    _loop_stack = new ArrayList<Block*>();
    Block* b;

    ArrayList<PyObject*>* names = codeObj->_names;
    Map<PyObject*, PyObject*>* locals = new Map<PyObject*, PyObject*>(); // 局部变量表

    int pc = 0;
    char* code = const_cast<char *>(codeObj->_bytecodes->value());
    int code_length = codeObj->_bytecodes->length();
    while(pc < code_length){
        unsigned char op_code = code[pc++];
        bool has_argument = (op_code & 0xFF) >= ByteCode::HAS_ARGUMENT;

        int op_arg = -1;
        if(has_argument){
            int byte1 = code[pc++] & 0xFF;
            op_arg = (code[pc++] & 0xFF) << 8 | byte1;
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
                _loop_stack->push(new Block(
                        op_code, pc + op_arg,
                        STACK_LV()));
                break;
            case ByteCode::POP_BLOCK:
                b = _loop_stack->pop();
                while (STACK_LV() > b->_level){
                    POP();
                }
                break;
            case ByteCode::BREAK_LOOP:
                b = _loop_stack->pop();
                while (STACK_LV() < b->_level){
                    POP();
                }
                pc = b->_target;
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