//
// Created by whg on 2022/10/31.
//

#include "pyObject.hpp"
#include "functionObject.hpp"
#include "runtime/universe.hpp"

void PyObject::print() {
    getClass()->print(this);
}

PyObject *PyObject::add(PyObject *other) {
    return getClass()->add(this, other);
}

PyObject *PyObject::less(PyObject *other) {
    return getClass()->less(this, other);
}

PyObject *PyObject::le(PyObject *other) {
    return getClass()->le(this, other);
}

PyObject *PyObject::equal(PyObject *other) {
    return getClass()->equal(this, other);
}

PyObject *PyObject::not_equal(PyObject *other) {
    return getClass()->not_equal(this, other);
}

PyObject *PyObject::greater(PyObject *other) {
    return getClass()->greater(this, other);
}

PyObject *PyObject::ge(PyObject *other) {
    return getClass()->ge(this, other);
}

PyObject *PyObject::getAttr(PyObject *attr) {
    PyObject* result = getClass()->attrMap()->get(attr);
    if(result == Universe::PyNone){
        return result;
    }

    // 从attrMap里面获取到的如果是一个FunctionObject，则包装成MethodObject把this当成隐含参数传递进去
    if(MethodObject::isFunction(result)){
        result = new MethodObject((FunctionObject*)result, this);
    }
    return result;
}