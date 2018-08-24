#include <iostream>

#define VALUE_SZ 10

class Hash {
public:
    Hash();
    ~Hash() {makeNull();}
    Hash &insertValue(const char *val);
    Hash &deleteValue(const char *val);
    int member(const char *val);
    void makeNull();
    void print();
private:
    static const int SZ = 10;
    char *arr[SZ];
    int calculateHash(int sum);
    int sumValue(const char *val);
    int searchCollision(const char *val, int _hash);
    int searchEmpty(const char *val, int _hash);
};

Hash::Hash() {
    for (int i = 0; i < SZ; i++)
        arr[i] = NULL;
}

Hash &Hash::insertValue(const char *val) {
    int _hash = calculateHash(sumValue(val)),
        empty;
    
    if (arr[_hash] == NULL) {
        arr[_hash] = new char[VALUE_SZ];
        strcpy(arr[_hash], val);
        return *this;
    }
    
    if (!strcmp(arr[_hash], val))
        return *this;
    
    if ((empty = searchEmpty(val, _hash)) != -1) {
        if (arr[empty] == NULL)
            arr[empty] = new char[VALUE_SZ];
        strcpy(arr[empty], val);
        
        return *this;
    }
    
    return *this;
}

Hash &Hash::deleteValue(const char *val) {
    int _hash = calculateHash(sumValue(val)),
        del;
    
    if (arr[_hash] == NULL)
        return *this;
    
    if (!strcmp(arr[_hash], val)) {
        arr[_hash][0] = '\0';
        return *this;
    }
    
    del = searchCollision(val, _hash);
    if (del != -1)
        arr[del][0] = '\0';
    
    return *this;
}

int Hash::member(const char *val) {
    int _hash = calculateHash(sumValue(val));
    
    if (arr[_hash] == NULL)
        return 0;
    
    if (!strcmp(arr[_hash], val))
        return 1;
    
    return searchCollision(val, _hash) != -1;
}

void Hash::makeNull() {
    for (int i = 0; i < SZ; i++)
        if (arr[i])
            delete [] arr[i];
}

int Hash::sumValue(const char *val) {
    int size = 0;
    
    for (int i = 0; i < VALUE_SZ && val[i] != '\0'; i++)
        size += (int)val[i];
    
    return size;
}

int Hash::calculateHash(int sum) {
    return sum % SZ;
}

int Hash::searchCollision(const char *val, int _hash) {
    int i = 1, __hash = calculateHash(_hash + i++);
    
    while (arr[__hash] != NULL && __hash != _hash) {
        if (!strcmp(arr[__hash], val))
            return __hash;
        
        __hash = calculateHash(__hash + i++);
    }
    
    return -1;
}

int Hash::searchEmpty(const char *val, int _hash) {
    int __hash = calculateHash(_hash), free = -1;
    
    do {
        if (!strcmp(arr[__hash], val))
            return -1;
            
        if (free == -1 && arr[__hash][0] == '\0')
            free = __hash;
        
        __hash = calculateHash(__hash + 1);
    } while (arr[__hash] && __hash != _hash);
    
    if (free != -1 && !arr[__hash])
        return free;
    
    if (!arr[__hash])
        return __hash;
    
    return -1;
}

void Hash::print() {
    for (int i = 0; i < SZ; i++)
        if (arr[i] && arr[i][0] != '\0')
            std::cout << arr[i] << std::endl;
}

int main(){
    Hash T;
    
    T = T.insertValue("George");
    T = T.insertValue("Alex");
    T = T.insertValue("Alfx");
    T = T.insertValue("Alfz");
    T = T.insertValue("Blfy");
    T = T.insertValue("Vova");
    T = T.insertValue("Anya");
    T.print();
    
    std::cout << "member?" << T.member("George");
    T.deleteValue("George");
    T.deleteValue("Blfy");
    
    std::cout << std::endl << std::endl;
    T.print();
    
    T = T.insertValue("Gosha");
    T = T.insertValue("Misha");
    std::cout << std::endl;
    T.print();
}



