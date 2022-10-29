//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_PY_OBJECT_HPP
#define PYVM_PY_OBJECT_HPP

class PyObject{
public:
    virtual PyObject* add(PyObject* other){
        return nullptr;
    }
    virtual void print(){

    }

    virtual PyObject* less(PyObject* other){
        return nullptr;
    }
    virtual PyObject* le(PyObject* other){
        return nullptr;
    }
    virtual PyObject* equal(PyObject* other){
        return nullptr;
    }
    virtual PyObject* not_equal(PyObject* other){
        return nullptr;
    }
    virtual PyObject* greater(PyObject* other){
        return nullptr;
    }
    virtual PyObject* ge(PyObject* other){
        return nullptr;
    }
};

#endif //PYVM_PY_OBJECT_HPP
