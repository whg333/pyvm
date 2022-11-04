//
// Created by whg on 2022/11/1.
//

#include "functionObject.hpp"
#include "pyInteger.hpp"
#include "runtime/universe.hpp"

NativeFunctionClass* NativeFunctionClass::instance = nullptr;
NativeFunctionClass *NativeFunctionClass::getInst() {
    if(instance == nullptr){
        instance = new NativeFunctionClass();
    }
    return instance;
}
NativeFunctionClass::NativeFunctionClass() {
    setSuper(FunctionClass::getInst());
}

PyObject* len(ObjList args){
    PyObject* arg0 = args->get(0);
    assert(arg0->getClass() == StringClass::getInst());
    PyString* str = (PyString*)arg0;
    return new PyInteger(str->length());
}

PyObject* upper(ObjList args){
    PyObject* arg0 = args->get(0);
    assert(arg0->getClass() == StringClass::getInst());
    PyString* str = (PyString*)arg0;
    int len = str->length();
    if(len <= 0){
        return Universe::PyNone;
    }

    char* v = new char[len];
    char c;
    for(int i=0;i<len;i++){
        c = str->value()[i];
        if(c >= 'a' && c <= 'z'){
            v[i] = c - 32;
        }else{
            v[i] = c;
        }
    }

    PyString* upper = new PyString(v);
    delete[] v;
    return upper;
}

FunctionClass* FunctionClass::instance = nullptr;
FunctionClass *FunctionClass::getInst() {
    if(instance == nullptr){
        instance = new FunctionClass();
    }
    return instance;
}
FunctionClass::FunctionClass() {

}

void FunctionClass::print(PyObject *self) {
    FunctionObject* selfFun = (FunctionObject*)self;
    assert(selfFun && (selfFun->getClass() == (Klass*)this));
    printf("<function : ");
    selfFun->name()->print();
    printf(">\n");
}

FunctionObject::FunctionObject(NativeFuncPointer nfp) {
    _code = nullptr;
    _name = nullptr;
    _flags = 0;
    _globals = nullptr;
    _nativeFunc = nfp;
    setClass(NativeFunctionClass::getInst());
}

FunctionObject::FunctionObject(PyObject* codeObj) {
    CodeObject* code = (CodeObject*)codeObj;
    _code = code;
    _name = code->_co_name;
    _flags = code->_flag;
    _globals = nullptr;
    setClass(FunctionClass::getInst());
}

PyObject *FunctionObject::callNative(ObjList args) {
    return (* _nativeFunc)(args); // 调用函数指针
}

void FunctionObject::setDefaults(ObjList defaults) {
    if(defaults == nullptr){
        _defaults = nullptr;
        return;
    }

    _defaults = new ArrayList<PyObject*>(defaults->length());
    for(int i=0;i<defaults->length();i++){
        _defaults->set(i, defaults->get(i));
    }
}

MethodClass* MethodClass::instance = nullptr;
MethodClass *MethodClass::getInst() {
    if(instance == nullptr){
        instance = new MethodClass();
    }
    return instance;
}
MethodClass::MethodClass() {
    setAttrMap(new ObjMap());
}

bool MethodObject::isFunction(PyObject *obj) {
    Klass* cls = obj->getClass();
    if(cls == FunctionClass::getInst()){
        return true;
    }
    cls = cls->super();
    while(cls != nullptr){
        if(cls == FunctionClass::getInst()){
            return true;
        }
    }
    return false;
}