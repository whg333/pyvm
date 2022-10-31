//
// Created by whg on 2022/11/1.
//

#ifndef PYVM_FUNCTIONOBJECT_HPP
#define PYVM_FUNCTIONOBJECT_HPP

#include "pyObject.hpp"
#include "code/codeObject.hpp"

class FunctionClass: public Klass{
private:
    static FunctionClass* instance;
    FunctionClass();
public:
    static FunctionClass* getInst();
    void print(PyObject *self) override;
};

class FunctionObject: public PyObject{
private:
    CodeObject* _code;
    PyString* _name;
    unsigned int _flags;
public:
    FunctionObject(PyObject* code);
    FunctionObject(Klass* klass){
        _code = nullptr;
        _name = nullptr;
        _flags = 0;
        setClass(klass);
    }

    CodeObject* code(){
        return _code;
    }

    PyString* name(){
        return _name;
    }

    int flags(){
        return _flags;
    }
};


#endif //PYVM_FUNCTIONOBJECT_HPP
