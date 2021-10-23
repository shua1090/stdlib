//
// Created by shynn on 10/18/2021.
//

#ifndef STDLIB_CONTAINER_H
#define STDLIB_CONTAINER_H

#include <iostream>

#define container_size unsigned long long

enum ReturnCode {
    OK = 0,  // OK (there is a reason for it to be 0)
    KO = -1,      // An error occurred, wait for next message
    FATAL = -2    // A critical error occurred, reboot
};

template<class T>
class ArrayList {
protected:
    container_size capacity{};
    container_size size{};
    T *beginning;

    void doubleSize() {
        T *temp = (T *) calloc(this->capacity * 2, sizeof(T));
        for (int i = 0; i < this->size; i++) {
            temp[i] = this->beginning[i];
        }
        this->capacity *= 2;
        free(this->beginning);
        this->beginning = temp;
    };

public:
    ArrayList<T>() {
        beginning = (T *) calloc(10, sizeof(T));
        this->capacity = 10;
        this->size = 0;
    };

    // ArrayList<T> (container_size initSize){
    //     if (!(initSize >= 0)){
    //         printf("Invalid initial capacity.");
    //         exit(-1);
    //     }
    //     beginning = (T *) calloc(initSize, sizeof(T));
    //     this->capacity = initSize;
    //     this->size = 0;
    // }

    void add(T value) {
        if (this->size + 1 > this->capacity) {
            T *temp = (T *) calloc(this->capacity*2, sizeof(T));
            for (int i = 0; i < this->size; i++) {
                temp[i] = this->beginning[i];
            }
            temp[this->size] = value;
            this->size++;
            this->capacity *= 2;
            free(this->beginning);
            this->beginning = temp;
        } else {
            this->beginning[this->size] = value;
            this->size++;
        }
    }

    T get(container_size index) {
        if (index >= this->size || index < 0) {
            return 0;
        } else {
            return this->beginning[index];
        }
    }

    ReturnCode insert(container_size index, T value) {
        if (index > this->size || index < 0) { return FATAL; }
        else {

            if (this->size + 1 > this->capacity) {
                this->doubleSize();
            }
            for (container_size val = this->size; val >= index; val--) {
                this->beginning[val + 1] = this->beginning[val];
            }
            this->size++;
            this->beginning[index] = value;
            return OK;
        }
    }

    T remove(container_size index) {
        if (index >= this->size || index < 0) { return FATAL; }
        else {
            T value = this->beginning[index];
            for (container_size a = index + 1; a < this->size; a++) {
                this->beginning[a - 1] = this->beginning[a];
            }
            this->beginning[this->size] = 0;
            this->size--;
            return value;

        }
    }

    void enqueue(T value) {
        this->add(value);
    }

    T deque() {
        return this->remove(this->size - 1);
    }

    T pop() {
        return this->remove(0);
    }

    void push(T value) {
        this->add(value);
    }

    container_size length() {
        return this->size;
    }

    T& operator[](container_size index){
        if (index >= this->size || index < 0) {
            printf("IndexOutOfRange");
            exit(-1);
        } else {
            return this->beginning[index];
        }
    }

    ~ArrayList() {
        free(this->beginning);
    }
};

template<class T>
struct ListNode {
    T value;
    ListNode<T> *next;
};

template<class T>
class LinkedList_s {
private:
    container_size size = 0;
    ListNode<T> *head = nullptr;
    ListNode<T> *tail = nullptr;
public:
    LinkedList_s() {};
    ~LinkedList_s() {
        ListNode<T> *current = head;
        ListNode<T> *next = current->next;
        while (true) {
            
            if (next == nullptr){delete current; return;}
            else {
                delete current;
            }
            current = next;
            next = current->next;
        }
    }

    void add(T value) {
        if (head == nullptr) {
            head = new ListNode<T>{value};
            tail = head;
            size++;
        } else {
            ListNode<T> *current;
            current = new ListNode<T>{value};
            tail->next = current;
            tail = current;
            size++;
        }
    };

    T remove(container_size index){
        if (index >= this->size || index < 0) {
            printf("Index Out of Bounds Error");
            return NULL;
        }
        container_size i = 0;
        ListNode<T> *result = this->head;
        while (i < index-1 && result->next != nullptr) {
            result = result->next;
            i++;
        }
        T val = result->next->value;
        if (index == 0){
            auto l = result->next;
            delete head;
            if (l == nullptr) tail = nullptr;
            else head = l;
        }
        else if (result->next->next == nullptr){
            tail = result;
            delete result->next;
        } else {
            auto l = result->next->next;
            delete result->next;
            result->next = l;
        }
        return val;
    }

    T get(container_size index) {
        if (index >= this->size || index < 0) {
            printf("Index Out of Bounds Error");
            return NULL;
        }
        container_size i = 0;
        ListNode<T> *result = this->head;
        while (i < index && result->next != nullptr) {
            result = result->next;
            i++;
        }
        return result->value;
    }

    container_size length() {
        return this->size;
    }
};

template<class V, class K>
struct Pair{
    V key;
    K value;
};

template <class V, class K>
struct Bucket{
    ArrayList<Pair<V, K>> values;
    void add(Pair<V, K> val){
        values.add(val);
    }

    K get(V key){
        for (container_size i = 0; i < values.length; i++){
            if (values[i].key == key){
                return values[i].value;
            }
        }
        printf("Key DNE");
        exit(-1);
    }
};

template<class V, class K>
class HashTable {
private:
    Bucket<V, K> * buckets[100];
    unsigned int (*hashFunction)(V);

    unsigned int size = 0;

public:
    HashTable(){size = 100;};

    void addHashFunction(unsigned int (*userDefinedHashFunction)(V)){
        this->hashFunction = userDefinedHashFunction;
    }

    unsigned int hash(V key){
        return hashFunction(key);
    }

    void add(V key, K value){
        unsigned int bucketVal = hash(key) % size;
        // buckets[bucketVal].values = ArrayList<Pair<V, K>>();
        buckets[bucketVal]->add(Pair<V, K>{key, value});
    }

    K get (V key){
        unsigned int bucketVal = hash(key) % size;
        buckets[bucketVal].get(key);
    }
};

#endif //STDLIB_CONTAINER_H
