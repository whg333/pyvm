//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_PY_STRING_HPP
#define PYVM_PY_STRING_HPP

#include "pyObject.hpp"

class PyString:public PyObject{
private:
    char* _value;
    int _length;

public:
    PyString(const char* c);
    PyString(const char* c, const int length);

    const char* value(){
        return _value;
    }
    int length(){
        return _length;
    }
};

#endif //PYVM_PY_STRING_HPP