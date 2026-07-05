#ifndef AVL_HPP
#define AVL_HPP

#include <string>
#include "../clases/Song.hpp"
#include "LinkedList.hpp"

class AVLNodo {
public:
    std::string artista;
    LinkedList<Song*> canciones;

    AVLNodo* left;
    AVLNodo* right;
    int height;

    AVLNodo(Song* song);
};

class AVLTree {
private:
    AVLNodo* root;

    int height(AVLNodo* node);
    int getBalance(AVLNodo* node);
    int max(int a, int b);

    AVLNodo* rotateRight(AVLNodo* y);
    AVLNodo* rotateLeft(AVLNodo* x);

    AVLNodo* insert(AVLNodo* node, Song* song);
    AVLNodo* search(AVLNodo* node, const std::string& artista);

    void destroy(AVLNodo* node);
    void inorder(AVLNodo* node);

public:
    AVLTree();
    ~AVLTree();

    void insert(Song* song);
    AVLNodo* search(const std::string& artista);

    void displayInOrder();
};

#endif