//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_PY_STRING_HPP
#define PYVM_PY_STRING_HPP

#include "pyObject.hpp"

class StringClass:public Klass{
private:
    StringClass(){

    }
    static StringClass* instance;
public:
    static StringClass* getInst();
    void print(PyObject *self) override;
    PyObject * equal(PyObject *self, PyObject *other) override;
    PyObject * subscr(PyObject *self, PyObject *index) override;
    PyObject * contains(PyObject *self, PyObject *element) override;
};

class PyString:public PyObject{
private:
    char* _value;
    int _length;

public:
    PyString(const char* c); // 自定义字面值时使用
    PyString(const char* c, const int length); // 从字节码文件解析时使用

    const char* value(){
        return _value;
    }
    int length(){
        return _length;
    }
};

#endif //PYVM_PY_STRING_HPP
