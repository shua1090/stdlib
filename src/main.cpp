#include <iostream>

#include "Container.h"

void testAdd() {
    ArrayList<int> a;
    for (int i = 0; i < 100; i++) {
        if (i < 5 || i > 20) a.add(i);
    }
    for (container_size i = 0; i < a.length(); i++) {
        printf("|%i|,", a.get(i));
    }
    printf("\n");
    for (int i = 5; i <= 20; i++)
        a.insert(i, i);
    for (container_size i = 0; i < a.length(); i++) {
        printf("|%i|,", a.get(i));
    }
}

void testRemove() {
    ArrayList<int> a;
    a.add(5);
    a.add(6);
    a.add(7);
    for (container_size i = 0; i < a.length(); i++) {
        printf("|%i|,", a.get(i));
    }
    printf("\n");
    printf("%i\n", a.remove(3));
    for (container_size i = 0; i < a.length(); i++) {
        printf("|%i|,", a.get(i));
    }
}

unsigned int hashFunc(std::string a) {
    unsigned int val = 0;
    for (int i = 0; i < a.length(); i++) {
        val += val ^ a.at(i);
    }
    return val;
}

#include <string>

int main() {
    HashTable<std::string, int> dictionary;
    dictionary.addHashFunction(&hashFunc);
    std::cout << hashFunc("two") << std::endl;
    dictionary.add("one", 1);
    dictionary.add("two", 2);
    dictionary.add("three", 3);
    dictionary.add("four", 4);
    dictionary.print();
    printf("%i-%i\n", dictionary.get("four"), dictionary.get("three"));
    return 0;
}
