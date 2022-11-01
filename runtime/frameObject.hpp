//
// Created by whg on 2022/10/31.
//

#ifndef PYVM_FRAMEOBJECT_HPP
#define PYVM_FRAMEOBJECT_HPP


#include "code/codeObject.hpp"
#include "util/map.hpp"
#include "object/functionObject.hpp"

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
    FrameObject(CodeObject* codes); // 模块调用时使用
    FrameObject(FunctionObject* func, ObjList args); // 函数调用时使用
    ~FrameObject();

    CodeObject* _codes;
    int _pc;
    FrameObject* _next;

    ArrayList<PyObject*>* _stack; // 操作数栈
    ArrayList<Block*>* _loopStack;

    ArrayList<PyObject*>* _consts;
    ArrayList<PyObject*>* _names;
    Map<PyObject*, PyObject*>* _locals; // 局部变量表
    Map<PyObject*, PyObject*>* _globals; // 全局变量表

    ObjList _fastLocals; // 函数调用参数列表

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
    Map<PyObject*, PyObject*>* globals(){
        return _globals;
    }
    ObjList fastLocals(){
        return _fastLocals;
    }

    void setNext(FrameObject* next){
        _next = next;
    }
    FrameObject* next(){
        return _next;
    }
    /** 是否是栈顶 */
    bool isTop(){
        return _next == nullptr;
    }

    bool hasMoreCodes();
    unsigned char getOpCode();
    int getOpArg();
};


#endif //PYVM_FRAMEOBJECT_HPP
