//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_PY_INTEGER_HPP
#define PYVM_PY_INTEGER_HPP

#include "pyObject.hpp"

class PyInteger:public PyObject {
private:
    int _value;
public:
    PyInteger(int i);
    int value(){
        return _value;
    }
    PyObject * add(PyObject *other) override;
    void print() override;
};


#endif //PYVM_PY_INTEGER_HPP
