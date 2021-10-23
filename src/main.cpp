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

unsigned int hashFunc(char a){
    return (unsigned int) a;
}

int main() {
    HashTable<char, int> tab;
    tab.addHashFunction(&hashFunc);
    tab.add('a', 5);
    // printf("%i\n", )
    return 0;
}
