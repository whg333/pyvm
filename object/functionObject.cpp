//
// Created by whg on 2022/11/1.
//

#include "functionObject.hpp"
#include "pyInteger.hpp"

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

PyObject *FunctionObject::callNative(ObjList args) {
    return (* _nativeFunc)(args); // 调用函数指针
}

PyObject* len(ObjList args){
    PyObject* arg0 = args->get(0);
    assert(arg0->getClass() == StringClass::getInst());
    return new PyInteger(((PyString*)arg0)->length());
}

FunctionObject::FunctionObject(PyObject* codeObj) {
    CodeObject* code = (CodeObject*)codeObj;
    _code = code;
    _name = code->_co_name;
    _flags = code->_flag;
    _globals = nullptr;
    setClass(FunctionClass::getInst());
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