#ifndef REFCOUNT_H
#define REFCOUNT_H

class RefCount {
private:
    int count; //Contador de referencias

public:
    RefCount() : count(0) {}

    void addRef() {
        ++count;
    }

    bool release() {
        if (--count == 0) {
            return true; //Devuelve verdadero si se debe liberar la memoria
        }
        return false;
    }

    int getCount() const {
        return count;
    }
};

#endif //REFCOUNT_H