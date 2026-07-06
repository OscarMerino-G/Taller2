#include "../../include/Estructura_Datos/Trie.hpp"
#include <cctype>
// Trie.cpp
TrieNode::TrieNode() : isEndOfWord(false) {
    for (int i = 0; i < 62; i++) {
        children[i] = nullptr;
    }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < 62; i++) {
        if (children[i] != nullptr) {
            delete children[i];
            children[i] = nullptr;
        }
    }
}

Trie::Trie() {
    root = new TrieNode();
}

Trie::~Trie() {
    destroy(root);
}

void Trie::destroy(TrieNode* node) {
    if (node == nullptr) return;
    
    for (int i = 0; i < 62; i++) {
        if (node->children[i] != nullptr) {
            destroy(node->children[i]);
        }
    }
    delete node;
}

int Trie::charToIndex(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    } else if (c >= 'A' && c <= 'Z') {
        return 26 + (c - 'A');
    } else if (c >= '0' && c <= '9') {
        return 52 + (c - '0');
    }
    return -1;
}

void Trie::insertWord(const std::string& word, Song* song) {
    if (word.empty() || song == nullptr) return;
    
    TrieNode* current = root;
    
    for (char c : word) {
        int index = charToIndex(c);
        if (index == -1) continue; // ignorar caracteres no alfanum
        
        if (current->children[index] == nullptr) {
            current->children[index] = new TrieNode();
        }
        current = current->children[index];
    }
    
    current->isEndOfWord = true;
    // Agregar la canción al nodo final
    current->songs.pushBack(song);
}

void Trie::insertSong(Song* song) {
    if (song == nullptr) return;
    
    // IInsertar por nombre completo
    std::string nombre = song->getNombre();
    insertWord(nombre, song);
    
    // insertar por artista completo
    std::string artista = song->getArtista();
    insertWord(artista, song);
    
    // insertar por cada palabra del nombre
    std::string word;
    for (char c : nombre) {
        if (c == ' ' || c == '-' || c == '_' || c == '\'' || c == '(' || c == ')') {
            if (!word.empty()) {
                insertWord(word, song);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        insertWord(word, song);
    }
    
    // insertar por cada palabra del artista
    word.clear();
    for (char c : artista) {
        if (c == ' ' || c == '-' || c == '_' || c == '\'' || c == '(' || c == ')' || c == '.') {
            if (!word.empty()) {
                insertWord(word, song);
                word.clear();
            }
        } else {
            word += c;
        }
    }
    if (!word.empty()) {
        insertWord(word, song);
    }
}

TrieNode* Trie::searchPrefix(const std::string& prefix) {
    if (prefix.empty()) return nullptr;
    
    TrieNode* current = root;
    
    for (char c : prefix) {
        int index = charToIndex(c);
        if (index == -1) return nullptr;
        
        if (current->children[index] == nullptr) {
            return nullptr;
        }
        current = current->children[index];
    }
    
    return current;
}

void Trie::collectSongs(TrieNode* node, LinkedList<Song*>& result) {
    if (node == nullptr) return;
    
    // Agregar canciones del nodo actual
    Node<Song*>* current = node->songs.getHead();
    while (current != nullptr) {
        // Verificar que la canción no exista en resultado
        bool found = false;
        Node<Song*>* resultNode = result.getHead();
        while (resultNode != nullptr) {
            if (resultNode->data == current->data) {
                found = true;
                break;
            }
            resultNode = resultNode->next;
        }
        
        if (!found) {
            result.pushBack(current->data);
        }
        current = current->next;
    }
    
    // Recorrer hijos
    for (int i = 0; i < 62; i++) {
        if (node->children[i] != nullptr) {
            collectSongs(node->children[i], result);
        }
    }
}

LinkedList<Song*> Trie::search(const std::string& text) {
    LinkedList<Song*> result;
    
    if (text.empty()) {
        return result;
    }
    
    std::string searchText = text;
    
    // buscar el prefijo
    TrieNode* prefixNode = searchPrefix(searchText);
    if (prefixNode != nullptr) {
        collectSongs(prefixNode, result);
    }
    
    // si no encuentra resultado con el prefijo exacto, buscar por partes
    if (result.isEmpty()) {
        // bscar cada palabra del texto de búsqueda
        std::string word;
        for (char c : searchText) {
            if (c == ' ' || c == '-' || c == '_' || c == '\'') {
                if (!word.empty()) {
                    TrieNode* node = searchPrefix(word);
                    if (node != nullptr) {
                        collectSongs(node, result);
                    }
                    word.clear();
                }
            } else {
                word += c;
            }
        }
        if (!word.empty()) {
            TrieNode* node = searchPrefix(word);
            if (node != nullptr) {
                collectSongs(node, result);
            }
        }
    }
    
    return result;
}

void Trie::clear() {
    destroy(root);
    root = new TrieNode();
}