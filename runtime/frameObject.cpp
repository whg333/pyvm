//
// Created by whg on 2022/10/31.
//

#include "frameObject.hpp"
#include "code/bytecode.hpp"

FrameObject::FrameObject(CodeObject *codes) {
    _codes = codes;
    _pc = 0;

    _stack = new ArrayList<PyObject*>(codes->_stack_size);
    _loopStack = new ArrayList<Block*>();

    _consts = codes->_consts;
    _names = codes->_names;
    _locals = new Map<PyObject*, PyObject*>();
}

bool FrameObject::hasMoreCodes() {
    return _pc < _codes->_bytecodes->length();
}

unsigned char FrameObject::getOpCode() {
    return _codes->_bytecodes->value()[_pc++];
}

bool FrameObject::hasOpArg(unsigned char opCode) {
    return (opCode & 0xFF) >= ByteCode::HAS_ARGUMENT;
}

int FrameObject::getOpArg() {
    int byte1 = _codes->_bytecodes->value()[_pc++] * 0xFF;
    int byte2 = _codes->_bytecodes->value()[_pc++] * 0xFF;
    return byte2 << 8 | byte1;
}