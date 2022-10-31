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
public:
    Interpreter();
    void run(CodeObject* codeObj);
};


#endif //PYVM_INTERPRETER_HPP
