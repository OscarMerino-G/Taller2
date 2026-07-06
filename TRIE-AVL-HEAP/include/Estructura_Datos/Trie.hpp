#ifndef TRIE_HPP
#define TRIE_HPP

#include "../Clases/Song.hpp"
#include "LinkedList.hpp"
// Nodo del Trie
class TrieNode {
public:
    TrieNode* children[62]; // 52 letras y 10 digitos
    bool isEndOfWord; // final
    LinkedList<Song*> songs; // Canciones que coinciden con esta palabra
    
    TrieNode();
    ~TrieNode();
};

// Clase Trie para búsqueda texto
class Trie {
private:
    TrieNode* root;
    
    // cnvierte caracter a indice
    int charToIndex(char c);
    
    // Inserta una palabra en el trie
    void insertWord(const std::string& word, Song* song);
    
    // Busca un nodo que coincida con el prefijo
    TrieNode* searchPrefix(const std::string& prefix);
    
    // Recorre el trie para obtener todas las canciones
    void collectSongs(TrieNode* node, LinkedList<Song*>& result);
    
    // Destruye el trie recursivamente F
    void destroy(TrieNode* node);
    
public:
    Trie();
    ~Trie();
    
    // Inserta una canción en el trie (por nombre y artista)
    void insertSong(Song* song);
    
    // Busca canciones que contengan el texto en nombre o artista
    LinkedList<Song*> search(const std::string& text);
    
    // Limpia el trie
    void clear();
};

#endif