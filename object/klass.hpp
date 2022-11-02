//
// Created by whg on 2022/10/31.
//

#ifndef PYVM_KLASS_HPP
#define PYVM_KLASS_HPP

class PyObject; // TODO 这里声明（还是定义）PyObject之后再链接？
class PyString; // TODO 必须在这里声明，而不能include进来，导致循环依赖？
// #include "object/pyString.hpp"

class Klass{
private:
    PyString* _name;
    Klass* _super;

public:
    Klass(){

    }

    void setName(PyString* name){
        _name = name;
    }
    PyString* name(){
        return _name;
    }

    void setSuper(Klass* super){
        _super = super;
    }
    Klass* super(){
        return _super;
    }

    virtual void print(PyObject* self){

    }

    virtual PyObject* add(PyObject* self, PyObject* other){
        return nullptr;
    }

    virtual PyObject* less(PyObject* self, PyObject* other){
        return nullptr;
    }
    virtual PyObject* le(PyObject* self, PyObject* other){
        return nullptr;
    }
    virtual PyObject* equal(PyObject* self, PyObject* other){
        return nullptr;
    }
    virtual PyObject* not_equal(PyObject* self, PyObject* other){
        return nullptr;
    }
    virtual PyObject* greater(PyObject* self, PyObject* other){
        return nullptr;
    }
    virtual PyObject* ge(PyObject* self, PyObject* other){
        return nullptr;
    }
};

#endif //PYVM_KLASS_HPP
