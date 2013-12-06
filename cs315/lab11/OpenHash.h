#ifndef OPEN_HASH_H
#define OPEN_HASH_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>

class OpenHash {
    public:
        OpenHash();
        OpenHash(int startSize);
        void insert(std::string key);
        bool contains(std::string key);
        void remove(std::string key);
    private:
        std::vector<std::list<std::string> > H;
        int hash(std::string key);
};

OpenHash::OpenHash() {
    H.resize(1337);
}

OpenHash::OpenHash(int startSize) {
    H.resize(startSize);
}

void OpenHash::insert(std::string key) {
    int i = hash(key);
    if ( std::find(H[i].begin(), H[i].end(), key) == H[i].end()) {
        H[i].push_front(key);
    }
}
bool OpenHash::contains(std::string key) {
    int i = hash(key);
    return std::find(H[i].begin(), H[i].end(), key) != H[i].end();
}

void OpenHash::remove(std::string key) {
    int i = hash(key);
    H[i].remove(key);
}

int OpenHash::hash(std::string key) {
    int result = 0;
    for (int i = 0; i < key.length(); ++i) {
        result = (256 * result + key[i]) % H.capacity();
    }
    return result;
}

#endif
