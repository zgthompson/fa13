#ifndef CLOSED_HASH_H
#define CLOSED_HASH_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <algorithm>
#include "PrimeUtils.h"

class ClosedHash {
    public:
        //constants
        static const int EMPTY;
        static const int ACTIVE;
        static const int DEL;
        //constructors
        ClosedHash();
        ClosedHash(int startSize);
        // public functions
        void insert(std::string key);
        bool contains(std::string key);
        void remove(std::string key);
    private:
        std::vector<std::pair<int,std::string> > H;
        int keys;
        void resize();
        int hash(std::string key);
        int hash2(std::string key);
};

const int ClosedHash::EMPTY = 0;
const int ClosedHash::ACTIVE = 1;
const int ClosedHash::DEL = 2;

ClosedHash::ClosedHash() {
    keys = 0;
    H.resize(1337);
}

ClosedHash::ClosedHash(int startSize) {
    keys = 0;
    H.resize(next_prime(startSize - 1));
}

void ClosedHash::insert(std::string key) {
    if (keys * 2 > H.capacity() ) resize();
    int i = hash(key);
    while (H[i].first == ACTIVE) {
        if (H[i].second == key) return;
        i = ( (i + hash2(key)) % H.capacity() );
    }
    H[i].first = ACTIVE;
    H[i].second = key;
    keys++;
}

bool ClosedHash::contains(std::string key) {
    int i = hash(key);
    while (H[i].first != EMPTY) {
        if (H[i].first == ACTIVE) {
            if (H[i].second == key) return true;
        }
        i = ( (i + hash2(key)) % H.capacity() );
    }
    return false;
}

void ClosedHash::remove(std::string key) {
    int i = hash(key);
    while (H[i].first != EMPTY) {
        if (H[i].first == ACTIVE) {
            if (H[i].second == key) {
                H[i].first = DEL;
                keys--;
                return;
            }
        }
        i = ( (i + hash2(key)) % H.capacity() );
    }
}

void ClosedHash::resize() {
    int oldSize = H.capacity();
    std::vector<std::pair<int, std::string> > oldH(H);
    H.clear();
    H.resize( next_prime(oldSize * 2 + 1) );
    keys = 0;

    std::pair<int, std::string> curKey;
    for (int i = 0; i < oldSize; ++i) {
        curKey = oldH[i];
        if (curKey.first == ACTIVE) {
            insert(curKey.second);
        }
    }
}

int ClosedHash::hash(std::string key) {
    int result = 0;
    for (int i = 0; i < key.length(); ++i) {
        result = (256 * result + key[i]) % H.capacity();
    }
    return result;
}

int ClosedHash::hash2(std::string key) {
    int result = 0;
    for (int i = key.length() - 1; i >= 0; --i) {
        result = (256 * result + key[i]) % (H.capacity() - 1);
    }
    return result + 1;
}

#endif
