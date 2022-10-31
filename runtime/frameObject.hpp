//
// Created by whg on 2022/10/31.
//

#ifndef PYVM_FRAMEOBJECT_HPP
#define PYVM_FRAMEOBJECT_HPP


#include "code/codeObject.hpp"
#include "util/map.hpp"

class Block{
public:
    unsigned char _type;
    unsigned int _target;
    int _level;

    Block(){
        _type = 0;
        _target = 0;
        _level = 0;
    }

    Block(unsigned char type, unsigned char target, int level)
            :_type(type),_target(target),_level(level){

    }

    Block(const Block& b){
        _type = b._type;
        _target = b._target;
        _level = b._level;
    }
};

class FrameObject {
public:
    FrameObject(CodeObject* codes);
    ~FrameObject();

    CodeObject* _codes;
    int _pc;

    ArrayList<PyObject*>* _stack;
    ArrayList<Block*>* _loopStack;

    ArrayList<PyObject*>* _consts;
    ArrayList<PyObject*>* _names;
    Map<PyObject*, PyObject*>* _locals;

public:
    void setPc(int pc){
        _pc = pc;
    }
    int pc(){
        return _pc;
    }
    ArrayList<PyObject*>* stack(){
        return _stack;
    }
    ArrayList<Block*>* loopStack(){
        return _loopStack;
    }
    ArrayList<PyObject*>* consts(){
        return _consts;
    }
    ArrayList<PyObject*>* names(){
        return _names;
    }
    Map<PyObject*, PyObject*>* locals(){
        return _locals;
    }

    bool hasMoreCodes();
    unsigned char getOpCode();
    bool hasOpArg(unsigned char);
    int getOpArg();
};


#endif //PYVM_FRAMEOBJECT_HPP
