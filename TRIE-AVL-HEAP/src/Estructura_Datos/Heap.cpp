#include "../../include/Estructura_Datos/Heap.hpp"
#include <cstdlib>
// Healp.cpp
// Constructor h
Heap::Heap(bool minHeap) : capacity(100), size(0), isMinHeap(minHeap) {
    heapArray = new Song*[capacity];
    for (int i = 0; i < capacity; i++) {
        heapArray[i] = nullptr;
    }
}

// destructor p
Heap::~Heap() {
    if (heapArray != nullptr) {
        delete[] heapArray;
        heapArray = nullptr;
    }
}

int Heap::parent(int index) {
    return (index - 1) / 2;
}

int Heap::leftChild(int index) {
    return 2 * index + 1;
}

int Heap::rightChild(int index) {
    return 2 * index + 2;
}

void Heap::swap(Song*& a, Song*& b) {
    Song* temp = a;
    a = b;
    b = temp;
}

void Heap::resize() {
    int newCapacity = capacity * 2;
    Song** newArray = new Song*[newCapacity];
    
    for (int i = 0; i < capacity; i++) {
        newArray[i] = heapArray[i];
    }
    for (int i = capacity; i < newCapacity; i++) {
        newArray[i] = nullptr;
    }
    
    delete[] heapArray;
    heapArray = newArray;
    capacity = newCapacity;
}

void Heap::heapifyUp(int index) {
    if (index <= 0) return;
    
    int parentIdx = parent(index);
    
    bool shouldSwap;
    if (isMinHeap) {
        // Para min-heap, el padre debe ser menor o igual
        shouldSwap = (heapArray[parentIdx]->getPlayCount() > heapArray[index]->getPlayCount()) ||
                     (heapArray[parentIdx]->getPlayCount() == heapArray[index]->getPlayCount() &&
                      heapArray[parentIdx]->getNombre() > heapArray[index]->getNombre());
    } else {
        // Para max-heap, el padre debe ser mayor o igual
        shouldSwap = (heapArray[parentIdx]->getPlayCount() < heapArray[index]->getPlayCount()) ||
                     (heapArray[parentIdx]->getPlayCount() == heapArray[index]->getPlayCount() &&
                      heapArray[parentIdx]->getNombre() > heapArray[index]->getNombre());
    }
    
    if (shouldSwap) {
        swap(heapArray[parentIdx], heapArray[index]);
        heapifyUp(parentIdx);
    }
}

void Heap::heapifyDown(int index) {
    int left = leftChild(index);
    int right = rightChild(index);
    int target = index;
    
    if (left < size) {
        bool shouldSwap;
        if (isMinHeap) {
            shouldSwap = (heapArray[left]->getPlayCount() < heapArray[target]->getPlayCount()) ||
                         (heapArray[left]->getPlayCount() == heapArray[target]->getPlayCount() &&
                          heapArray[left]->getNombre() < heapArray[target]->getNombre());
        } else {
            shouldSwap = (heapArray[left]->getPlayCount() > heapArray[target]->getPlayCount()) ||
                         (heapArray[left]->getPlayCount() == heapArray[target]->getPlayCount() &&
                          heapArray[left]->getNombre() < heapArray[target]->getNombre());
        }
        if (shouldSwap) {
            target = left;
        }
    }
    
    if (right < size) {
        bool shouldSwap;
        if (isMinHeap) {
            shouldSwap = (heapArray[right]->getPlayCount() < heapArray[target]->getPlayCount()) ||
                         (heapArray[right]->getPlayCount() == heapArray[target]->getPlayCount() &&
                          heapArray[right]->getNombre() < heapArray[target]->getNombre());
        } else {
            shouldSwap = (heapArray[right]->getPlayCount() > heapArray[target]->getPlayCount()) ||
                         (heapArray[right]->getPlayCount() == heapArray[target]->getPlayCount() &&
                          heapArray[right]->getNombre() < heapArray[target]->getNombre());
        }
        if (shouldSwap) {
            target = right;
        }
    }
    
    if (target != index) {
        swap(heapArray[index], heapArray[target]);
        heapifyDown(target);
    }
}

void Heap::insert(Song* song) {
    if (song == nullptr) return;
    
    if (size >= capacity) {
        resize();
    }
    
    heapArray[size] = song;
    heapifyUp(size);
    size++;
}

LinkedList<Song*> Heap::getTopN(int n) {
    LinkedList<Song*> result;

    if (size == 0 || n <= 0) {
        return result;
    }

    Heap tempHeap(isMinHeap);

    for (int i = 0; i < size; i++) {
        tempHeap.insert(heapArray[i]);
    }

    int count = (n < size) ? n : size;

    for (int i = 0; i < count; i++) {
        Song* top = tempHeap.heapArray[0];
        result.pushBack(top);

        tempHeap.heapArray[0] = tempHeap.heapArray[tempHeap.size - 1];
        tempHeap.heapArray[tempHeap.size - 1] = nullptr;
        tempHeap.size--;

        if (tempHeap.size > 0) {
            tempHeap.heapifyDown(0);
        }
    }

    return result;
}

// obtener top artistas
LinkedList<std::pair<int, std::string>> Heap::getTopArtists(int n) {
    LinkedList<std::pair<int, std::string>> result;
    
    if (size == 0) return result;
    
    // Recorrer todas las canciones para acumular reproducciones por artista
    struct ArtistCount {
        std::string name;
        int count;
    };
    
    // Arreglo temporal para almacenar artistas
    ArtistCount* artists = new ArtistCount[size];
    int artistCount = 0;
    
    for (int i = 0; i < size; i++) {
        if (heapArray[i] == nullptr) continue;
        
        std::string artistName = heapArray[i]->getArtista();
        bool found = false;
        
        for (int j = 0; j < artistCount; j++) {
            if (artists[j].name == artistName) {
                artists[j].count += heapArray[i]->getPlayCount();
                found = true;
                break;
            }
        }
        
        if (!found) {
            artists[artistCount].name = artistName;
            artists[artistCount].count = heapArray[i]->getPlayCount();
            artistCount++;
        }
    }
    
    // Ordenar artistas por count (descendente) y alfabéticamente
    for (int i = 0; i < artistCount - 1; i++) {
        for (int j = i + 1; j < artistCount; j++) {
            bool shouldSwap = (artists[i].count < artists[j].count) ||
                              (artists[i].count == artists[j].count &&
                               artists[i].name > artists[j].name);
            if (shouldSwap) {
                ArtistCount temp = artists[i];
                artists[i] = artists[j];
                artists[j] = temp;
            }
        }
    }
    
    int count = (n < artistCount) ? n : artistCount;
    for (int i = 0; i < count; i++) {
        result.pushBack(std::pair<int, std::string>(artists[i].count, artists[i].name));
    }
    
    delete[] artists;
    return result;
}
bool Heap::isEmpty() const {
    return size == 0;
}

int Heap::getSize() const {
    return size;
}

void Heap::clear() {
    for (int i = 0; i < capacity; i++) {
        heapArray[i] = nullptr;
    }
    size = 0;
}