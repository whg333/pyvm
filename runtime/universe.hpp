//
// Created by whg on 2022/10/29.
//

#ifndef PYVM_UNIVERSE_HPP
#define PYVM_UNIVERSE_HPP

#include "object/pyInteger.hpp"

class Universe{
public:
    static PyInteger* PyTrue;
    static PyInteger* PyFalse;

    static PyObject* PyNone;

    static void genesis();
    static void destroy();
};

#endif //PYVM_UNIVERSE_HPP
