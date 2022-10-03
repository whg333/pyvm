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
};

#endif //PYVM_PY_OBJECT_HPP
