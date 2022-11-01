//
// Created by whg on 2022/10/31.
//

#include "frameObject.hpp"

FrameObject::FrameObject(CodeObject *codes) {
    _codes = codes;
    _pc = 0;

    _stack = new ArrayList<PyObject*>(_codes->_stack_size);
    _loopStack = new ArrayList<Block*>();

    _consts = _codes->_consts;
    _names = _codes->_names;

    _locals = new Map<PyObject*, PyObject*>();
    _globals = _locals;

    _next = nullptr;
}

FrameObject::FrameObject(FunctionObject *func) {
    _codes = func->code();
    _pc = 0;

    _stack = new ArrayList<PyObject*>(_codes->_stack_size);
    _loopStack = new ArrayList<Block*>();

    _consts = _codes->_consts;
    _names = _codes->_names;

    _locals = new Map<PyObject*, PyObject*>();
    _globals = func->globals();

    _next = nullptr;
}

FrameObject::~FrameObject() {

}

bool FrameObject::hasMoreCodes() {
    return _pc < _codes->_bytecodes->length();
}

unsigned char FrameObject::getOpCode() {
    return _codes->_bytecodes->value()[_pc++];
}

int FrameObject::getOpArg() {
    int byte1 = _codes->_bytecodes->value()[_pc++] & 0xFF;
    int byte2 = _codes->_bytecodes->value()[_pc++] & 0xFF;
    return byte2 << 8 | byte1;
}