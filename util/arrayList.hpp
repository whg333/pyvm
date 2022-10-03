//
// Created by whg on 2022/10/3.
//

#ifndef PYVM_ARRAY_LIST_HPP
#define PYVM_ARRAY_LIST_HPP

template <typename T>
class ArrayList {
private:
    int _length;
    int _size;
    T* _array;

    void expand();

public:
    ArrayList(int length = 8);

    void add(T t);
    void insert(int index, T t);
    T get(int index);
    void set(int index, T t);
    int size();
    int length();

    void push(T t);
    T pop();
};


#endif //PYVM_ARRAY_LIST_HPP
