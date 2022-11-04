//
// Created by whg on 2022/10/29.
//

#ifndef PYVM_MAP_HPP
#define PYVM_MAP_HPP

template<typename K, typename V>
class MapEntry {
public:
    K _k;
    V _v;

    MapEntry(const MapEntry<K, V>& entry);
    MapEntry(K k, V v): _k(k), _v(v){};
    MapEntry(): _k(0), _v(0){};
};

template<typename K, typename V>
class Map{
private:
    MapEntry<K, V>* _entries;
    int _size;
    int _length;

    void expand();

public:
    Map();

    int size(){
        return _size;
    }
    void put(K k, V v);
    V get(K k);
    K getKey(int index);
    bool hasKey(K k);
    V remote(K k);
    int index(K k);
    MapEntry<K, V>* entries(){
        return _entries;
    };
};

class PyObject;
typedef Map<PyObject*, PyObject*> ObjMap;

#endif //PYVM_MAP_HPP
