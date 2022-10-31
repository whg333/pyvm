//
// Created by whg on 2022/10/3.
//

#include <stdio.h>
#include "interpreter.hpp"
#include "code/bytecode.hpp"
#include "object/pyInteger.hpp"
#include "runtime/universe.hpp"
#include "object/functionObject.hpp"

#define PUSH(x) _frame->stack()->add((x))
#define POP()   _frame->stack()->pop()
#define STACK_LV() _frame->stack()->size()

#define GET_CONST(x) _frame->consts()->get((x))

#define PUSH_LOOP(x) _frame->loopStack()->add((x))
#define POP_LOOP() _frame->loopStack()->pop()

Interpreter::Interpreter() {
    Universe::genesis();
}

void Interpreter::run(CodeObject *codeObj) {
    _frame = new FrameObject(codeObj);
    runFrame();
    destroyFrame();
}

void Interpreter::runFrame() {
    Block* b;
    PyObject* v, * w, * u, * attr, * const_val;
    FunctionObject* fo;
    while(_frame->hasMoreCodes()){
        unsigned char opCode = _frame->getOpCode();
        bool hasArg = (opCode & 0xFF) >= ByteCode::HAS_ARGUMENT;
        int opArg = -1;
        if(hasArg){
            opArg = _frame->getOpArg();
        }

        switch (opCode) {
            case ByteCode::LOAD_CONST:
                const_val = GET_CONST(opArg);
                PUSH(const_val);
                break;
            case ByteCode::PRINT_ITEM:
                v = POP();
                v->print();
                break;
            case ByteCode::PRINT_NEWLINE:
                printf("\n");
                break;
            case ByteCode::BINARY_ADD:
                v = POP();
                w = POP();
                PUSH(w->add(v));
                break;
            case ByteCode::RETURN_VALUE:
                _retVal = POP();
                if(_frame->isTop()){
                    return;
                }
                leaveFrame();
                break;

            case ByteCode::COMPARE_OP:
                w = POP();
                v = POP();
                switch (opArg) {
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
                    _frame->setPc(opArg);
                }
                break;
            case ByteCode::JUMP_FORWARD:
                _frame->setPc( _frame->pc() + opArg);
                break;
            case ByteCode::JUMP_ABSOLUTE:
                _frame->setPc(opArg);
                break;

            case ByteCode::SETUP_LOOP:
                PUSH_LOOP(new Block(
                        opCode,  _frame->pc() + opArg,
                        STACK_LV()));
                break;
            case ByteCode::POP_BLOCK:
                b = POP_LOOP();
                while (STACK_LV() > b->_level){
                    POP();
                }
                break;
            case ByteCode::BREAK_LOOP:
                b = POP_LOOP();
                while (STACK_LV() < b->_level){
                    POP();
                }
                _frame->setPc(b->_target);
                break;

            case ByteCode::STORE_NAME:
                v = _frame->names()->get(opArg);
                w = POP();
                _frame->locals()->put(v, w);
                break;
            case ByteCode::LOAD_NAME:
                v = _frame->names()->get(opArg);
                w = _frame->locals()->get(v);
                PUSH(w);
                break;

            case ByteCode::MAKE_FUNCTION:
                v = POP();
                fo = new FunctionObject(v);
                PUSH(fo);
                break;
            case ByteCode::CALL_FUNCTION:
                v = POP();
                callFunc(v);
                break;

            default:
                printf("Error: Unknown op code %d\n", opCode);
        }
    }
}

void Interpreter::callFunc(PyObject* callable){
    FrameObject* funcFrame = new FrameObject((FunctionObject*) callable);
    funcFrame->setNext(_frame);
    _frame = funcFrame;
}

void Interpreter::leaveFrame() {
    destroyFrame();
    PUSH(_retVal);
}

void Interpreter::destroyFrame() {
    FrameObject* temp = _frame;
    _frame = _frame->next();
    delete temp;
}