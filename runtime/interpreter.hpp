//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_INTERPRETER_HPP
#define PYVM_INTERPRETER_HPP

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

class Interpreter {
private:
    ArrayList<PyObject*>* _stack;
    ArrayList<PyObject*>* _consts;

    ArrayList<Block*>* _loop_stack;
public:
    Interpreter();
    void run(CodeObject* codeObj);
};


#endif //PYVM_INTERPRETER_HPP
