//
// Created by whg on 2022/11/1.
//

#ifndef PYVM_FUNCTIONOBJECT_HPP
#define PYVM_FUNCTIONOBJECT_HPP

#include "pyObject.hpp"
#include "code/codeObject.hpp"
#include "util/map.hpp"

PyObject* len(ObjList args);

typedef PyObject* (*NativeFuncPointer)(ObjList args);

class NativeFunctionClass:public Klass{
private:
    static NativeFunctionClass* instance;
    NativeFunctionClass();
public:
    static NativeFunctionClass* getInst();
};

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
    Map<PyObject*, PyObject*>* _globals;
    ObjList _defaults; // 函数调用参数默认值
    NativeFuncPointer _nativeFunc; // Native函数指针
public:
    FunctionObject(NativeFuncPointer nfp);
    FunctionObject(PyObject* code);
    FunctionObject(Klass* klass){
        _code = nullptr;
        _name = nullptr;
        _flags = 0;
        setClass(klass);
    }

    PyObject* callNative(ObjList args);

    CodeObject* code(){
        return _code;
    }
    PyString* name(){
        return _name;
    }
    int flags(){
        return _flags;
    }

    Map<PyObject*, PyObject*>* globals(){
        return _globals;
    }
    void setGlobals(Map<PyObject*, PyObject*>* globals){
        _globals = globals;
    }

    ObjList defaults(){
        return _defaults;
    }
    void setDefaults(ObjList defaults);
};


#endif //PYVM_FUNCTIONOBJECT_HPP
