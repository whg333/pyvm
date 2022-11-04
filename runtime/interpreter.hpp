//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_INTERPRETER_HPP
#define PYVM_INTERPRETER_HPP

#include "code/codeObject.hpp"
#include "frameObject.hpp"

class Interpreter {
private:
    bool _log;
    FrameObject* _frame; // 当前执行帧，即栈顶top的帧
    PyObject* _retVal; // 函数调用返回值
    Map<PyObject*, PyObject*>* _builtins; // 内建变量表
public:
    Interpreter();
    void run(CodeObject* codeObj);
private:
    void runFrame();
    void destroyFrame();
    void leaveFrame();
    void callFunc(PyObject* callable, ObjList args);
};


#endif //PYVM_INTERPRETER_HPP
