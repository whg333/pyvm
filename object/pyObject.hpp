//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_PY_OBJECT_HPP
#define PYVM_PY_OBJECT_HPP

#include <assert.h>
#include <stdio.h>
#include "klass.hpp"

class PyObject{
private:
    Klass* _class = nullptr;
public:
    Klass* getClass(){
        // assert(_class != nullptr);
        if(_class == nullptr){
            printf("Not Set Class!!!");
        }
        return _class;
    }
    void setClass(Klass* c){
        _class = c;
    }

    void print();
    
    PyObject* add(PyObject* other);

    PyObject* less(PyObject* other);
    PyObject* le(PyObject* other);
    PyObject* equal(PyObject* other);
    PyObject* not_equal(PyObject* other);
    PyObject* greater(PyObject* other);
    PyObject* ge(PyObject* other);
};

#endif //PYVM_PY_OBJECT_HPP
