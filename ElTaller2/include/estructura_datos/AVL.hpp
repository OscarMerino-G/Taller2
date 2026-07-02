#ifndef AVL_HPP
#define AVL_HPP
// AVL.hpp
#include "../clases/Song.hpp"

class AVLNodo {
    Song* song;
    AVLNodo* left;
    AVLNodo* right;
    int height;
    
    AVLNodo(Song* song);
    ~AVLNodo();
};
class AVLTree {
};
#endif