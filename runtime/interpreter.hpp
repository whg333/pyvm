//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_INTERPRETER_HPP
#define PYVM_INTERPRETER_HPP

#include "code/codeObject.hpp"
#include "util/map.hpp"

class Interpreter {
private:
    ArrayList<PyObject*>* _stack;
    ArrayList<PyObject*>* _consts;
public:
    Interpreter();
    void run(CodeObject* codeObj);
};


#endif //PYVM_INTERPRETER_HPP
