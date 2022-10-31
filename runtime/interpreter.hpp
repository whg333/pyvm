//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_INTERPRETER_HPP
#define PYVM_INTERPRETER_HPP

#include "code/codeObject.hpp"
#include "frameObject.hpp"

class Interpreter {
private:
    FrameObject* _frame;
    PyObject* _retVal;
public:
    Interpreter();
    void run(CodeObject* codeObj);
private:
    void runFrame();
    void destroyFrame();
    void leaveFrame();
    void callFunc(PyObject* callable);
};


#endif //PYVM_INTERPRETER_HPP
