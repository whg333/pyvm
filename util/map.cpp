//
// Created by whg on 2022/10/29.
//

#include "map.hpp"
#include "runtime/universe.hpp"

template<typename K, typename V>
MapEntry<K, V>::MapEntry(const MapEntry<K, V> &entry) {
    _k = entry._k;
    _v = entry._v;
}

template<typename K, typename V>
Map<K, V>::Map(){
    _entries = new MapEntry<K, V>[8];
    _size = 0;
    _length = 8;
}

template<typename K, typename V>
void Map<K, V>::put(K k, V v) {
    for(int i=0;i<_size;i++){
        // 依赖PyObject子类的equal具体实现
        if(_entries[i]._k->equal(k) == Universe::PyTrue){
            _entries[i]._v = v;
            return;
        }
    }
    expand();
    _entries[_size++] = MapEntry<K, V>(k, v);
}

template<typename K, typename V>
bool Map<K, V>::hasKey(K k) {
    return index(k) >= 0;
}

template<typename K, typename V>
V Map<K, V>::get(K k) {
    int i = index(k);
    return i >= 0 ? _entries[i]._v : Universe::PyNone;
}

template<typename K, typename V>
int Map<K, V>::index(K k) {
    for(int i=0;i<_size;i++){
        // 依赖PyObject子类的equal具体实现
        if(_entries[i]._k->equal(k) == Universe::PyTrue){
            return i;
        }
    }
    return -1;
}

template<typename K, typename V>
void Map<K, V>::expand() {
    if(_size >= _length){
        MapEntry<K, V>* new_entries = new MapEntry<K, V>[_length << 1];
        for(int i=0;i<_size;i++){
            _entries[i] = new_entries[i];
        }
        _length <<= 1;
        delete[] _entries;
        _entries = new_entries;
    }
}

template<typename K, typename V>
V Map<K, V>::remote(K k) {
    int i = index(k);
    if(i < 0){
        return Universe::PyNone;
    }
    V v = _entries[i]._v;
    // 最后一个元素与当前删除的元素交换位置
    _entries[i] = _entries[--_size];
    return v;
}

template<typename K, typename V>
K Map<K, V>::getKey(int index) {
    return _entries[index]._k;
}

class PyObject;
template class Map<PyObject*, PyObject*>;