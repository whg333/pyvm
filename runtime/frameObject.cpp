//
// Created by whg on 2022/10/31.
//

#include "frameObject.hpp"

FrameObject::FrameObject(CodeObject *codes) {
    _codes = codes;
    _pc = 0;
    _next = nullptr;

    _stack = new ArrayList<PyObject*>(_codes->_stack_size);
    _loopStack = new ArrayList<Block*>();

    _consts = _codes->_consts;
    _names = _codes->_names;

    _locals = new Map<PyObject*, PyObject*>();
    _globals = _locals;

    _fastLocals = nullptr;
}

FrameObject::FrameObject(FunctionObject *func, ObjList args) {
    _codes = func->code();
    _pc = 0;
    _next = nullptr;

    _stack = new ArrayList<PyObject*>(_codes->_stack_size);
    _loopStack = new ArrayList<Block*>();

    _consts = _codes->_consts;
    _names = _codes->_names;

    _locals = new Map<PyObject*, PyObject*>();
    _globals = func->globals();

    int argCnt = _codes->_arg_count;
    _fastLocals = new ArrayList<PyObject*>(argCnt);
    if(func->defaults()){
        int dftCnt = func->defaults()->length();
        while(dftCnt--){
            _fastLocals->set(--argCnt, func->defaults()->get(dftCnt));
        }
    }
    if(args){
        for(int i=0;i<args->length();i++){
            _fastLocals->set(i, args->get(i));
        }
    }
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