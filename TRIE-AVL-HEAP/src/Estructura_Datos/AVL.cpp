#include "../../include/estructura_datos/AVL.hpp"
#include <iostream>
// AVL.cpp
AVLNodo::AVLNodo(Song* song) {
    artista = song->getArtista();
    canciones.pushBack(song);
    left = nullptr;
    right = nullptr;
    height = 1;
}

AVLTree::AVLTree() {
    root = nullptr;
}

AVLTree::~AVLTree() {
    destroy(root);
}

int AVLTree::max(int a, int b) {
    return (a > b) ? a : b;
}

int AVLTree::height(AVLNodo* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::getBalance(AVLNodo* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLNodo* AVLTree::rotateRight(AVLNodo* y) {
    AVLNodo* x = y->left;
    AVLNodo* temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

AVLNodo* AVLTree::rotateLeft(AVLNodo* x) {
    AVLNodo* y = x->right;
    AVLNodo* temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

AVLNodo* AVLTree::insert(AVLNodo* node, Song* song) {
    if (node == nullptr) {
        return new AVLNodo(song);
    }

    std::string artistaSong = song->getArtista();

    if (artistaSong < node->artista) {
        node->left = insert(node->left, song);
    }
    else if (artistaSong > node->artista) {
        node->right = insert(node->right, song);
    }
    else {
        node->canciones.pushBack(song);
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && artistaSong < node->left->artista) {
        return rotateRight(node);
    }
    if (balance < -1 && artistaSong > node->right->artista) {
        return rotateLeft(node);
    }
    if (balance > 1 && artistaSong > node->left->artista) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && artistaSong < node->right->artista) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

void AVLTree::insert(Song* song) {
    if (song == nullptr) {
        return;
    }
    root = insert(root, song);
}

AVLNodo* AVLTree::search(AVLNodo* node, const std::string& artista) {
    if (node == nullptr) {
        return nullptr;
    }

    if (artista == node->artista) {
        return node;
    }

    if (artista < node->artista) {
        return search(node->left, artista);
    }

    return search(node->right, artista);
}

AVLNodo* AVLTree::search(const std::string& artista) {
    return search(root, artista);
}

void AVLTree::inorder(AVLNodo* node) {
    if (node == nullptr) {
        return;
    }

    inorder(node->left);

    std::cout << "Artista: " << node->artista << std::endl;
    std::cout << "Canciones:" << std::endl;

    for (size_t i = 0; i < node->canciones.size(); i++) {
        Song* song = node->canciones.at(i);
        if (song != nullptr) {
            std::cout << "  - " << song->toString() << std::endl;
        }
    }

    std::cout << std::endl;

    inorder(node->right);
}

void AVLTree::displayInOrder() {
    inorder(root);
}

void AVLTree::destroy(AVLNodo* node) {
    if (node == nullptr) {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
}