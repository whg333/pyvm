//
// Created by whg on 2022/10/29.
//

#ifndef PYVM_UNIVERSE_HPP
#define PYVM_UNIVERSE_HPP

#include "object/pyInteger.hpp"
#include "object/pyString.hpp"

class Universe{
public:
    static PyObject* PyTrue;
    static PyObject* PyFalse;

    static PyObject* PyNone;

    static void genesis();
    static void destroy();
};

#endif //PYVM_UNIVERSE_HPP
