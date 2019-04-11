#pragma once

#include <limits>
#include <vector>

struct ID {
    unsigned int index;
    unsigned int inner_id;
};

class FreeListElement {
    public:
        unsigned int _next;
};

template <typename T>
class FreeList {
   public:
    unsigned int _next_inner_id;
    unsigned int _free_list;
    std::vector<T> _objects;

    FreeList() {
        _next_inner_id = 0;
        _free_list = std::numeric_limits<unsigned int>::max();
    }

    inline bool has(ID id) {
        return _objects[id.index].id.inner_id == id.inner_id;
    }

    inline T& lookup(ID id) { return _objects[id.index]; }

    inline ID add() {
        ID id;
        id.inner_id = _next_inner_id++;
        if (_free_list == std::numeric_limits<unsigned int>::max()) {
            T obj;
            id.index = _objects.size();
            obj.id = id;
            _objects.push_back(obj);
        } else {
            id.index = _free_list;
            _free_list = _objects[_free_list]._next;
        }
        return id;
    }

    inline void remove(ID id) {
        T& obj = lookup(id);
        obj.id.inner_id = std::numeric_limits<unsigned int>::max();
        obj.next = _free_list;
        _free_list = id.index;
    }
};
