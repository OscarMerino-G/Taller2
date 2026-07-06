#ifndef HEAP_HPP
#define HEAP_HPP
#include "../Clases/Song.hpp"
#include "LinkedList.hpp"
// Heap.hpp
class Heap {
private:
    Song** heapArray;// arreglo punteros a canciones
    int capacity;	// Capacidad máxima del heap
    int size;		// Tamaño actual del heap
    bool isMinHeap; // false para max-heap (top) | | true para min-heap
    
    // Funciones auxiliares del heap
    int parent(int index);
    int leftChild(int index);
    int rightChild(int index);
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(Song*& a, Song*& b);
    void resize();
    
public:
    Heap(bool minHeap = false);
    ~Heap();
    
    // Inserta una canción en el heap
    void insert(Song* song);
    
    // Obtiene el top N de canciones
    LinkedList<Song*> getTopN(int n);
    
    // Obtiene el top N de artistas
    LinkedList<std::pair<int, std::string>> getTopArtists(int n);
    
    // Verifica si el heap está vacío
    bool isEmpty() const;
    
    // Obtiene el tamaño del heap
    int getSize() const;
    
    // Limpia el heap
    void clear();
};

#endif