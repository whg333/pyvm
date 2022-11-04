//
// Created by whg on 2022/11/1.
//

#ifndef PYVM_FUNCTIONOBJECT_HPP
#define PYVM_FUNCTIONOBJECT_HPP

#include "pyObject.hpp"
#include "code/codeObject.hpp"
#include "util/map.hpp"

// 下面是函数声明，方可以正常链接到
PyObject* len(ObjList args);
PyObject* upper(ObjList args);

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

class MethodClass: public Klass{
private:
    static MethodClass* instance;
    MethodClass();
public:
    static MethodClass* getInst();
};

class MethodObject: public PyObject{
private:
    FunctionObject* _func;
    PyObject* _owner;
public:
    MethodObject(FunctionObject* func): _func(func), _owner(nullptr){
        setClass(MethodClass::getInst());
    }
    MethodObject(FunctionObject* func, PyObject* owner): _func(func), _owner(owner){
        setClass(MethodClass::getInst());
    }

    FunctionObject* func(){
        return _func;
    }
    void setOwner(PyObject* owner){
        _owner = owner;
    }
    PyObject* owner(){
        return _owner;
    }

    static bool isFunction(PyObject* obj);
};

#endif //PYVM_FUNCTIONOBJECT_HPP
