#ifndef NODE_HPP
#define NODE_HPP
#include "../../src/Estructura_Datos/Node.cpp"
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;
    
    Node();
    Node(const T& data);
    Node(const T& data, Node<T>* next, Node<T>* prev);
    ~Node();
};

template <typename T>
Node<T>::Node() : next(nullptr), prev(nullptr) {}

template <typename T>
Node<T>::Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}

template <typename T>
Node<T>::Node(const T& data, Node<T>* next, Node<T>* prev) 
    : data(data), next(next), prev(prev) {}

template <typename T>
Node<T>::~Node() {
    next = nullptr;
    prev = nullptr;
}

#endif