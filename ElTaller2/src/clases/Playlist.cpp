#include "../../include/clases/Playlist.hpp"
#include <cstdlib>
#include <ctime>
// Playlist.cpp
Playlist::Playlist() : currentIndex(-1), shuffleMode(false), repeatMode(0) {
    srand(time(nullptr));
}

Playlist::~Playlist() {
    clear();
}

void Playlist::addSong(Song* song) {
    songs.add(song);
    if (currentIndex == -1) {
        currentIndex = 0;
    }
}

void Playlist::addSongAtEnd(Song* song) {
    songs.addAtEnd(song);
    if (currentIndex == -1) {
        currentIndex = 0;
    }
}

void Playlist::removeSong(int index) {
    if (index < 0 || index >= songs.size()) return;
    
    // Si se elimina la canción actual, ajustar el índice
    if (index == currentIndex) {
        if (songs.size() > 1) {
            currentIndex = (currentIndex + 1) % songs.size();
        } else {
            currentIndex = -1;
        }
    } else if (index < currentIndex) {
        currentIndex--;
    }
    
    songs.removeAt(index);
}

void Playlist::clear() {
    songs.clear();
    currentIndex = -1;
}

Song* Playlist::getCurrentSong() {
    if (isEmpty() || currentIndex < 0 || currentIndex >= songs.size()) {
        return nullptr;
    }
    return songs.get(currentIndex);
}

Song* Playlist::getNextSong() {
    if (isEmpty()) return nullptr;
    
    if (shuffleMode) {
        // Seleccionar aleatoriamente
        int newIndex = rand() % songs.size();
        while (newIndex == currentIndex && songs.size() > 1) {
            newIndex = rand() % songs.size();
        }
        currentIndex = newIndex;
    } else {
        if (repeatMode == 1) {
            // Repetir una canción
            // No se mueve
        } else if (repeatMode == 2) {
            // Repetir todas
            currentIndex = (currentIndex + 1) % songs.size();
        } else {
            // Repetición desactivada
            if (currentIndex < songs.size() - 1) {
                currentIndex++;
            } else {
                return nullptr; // Fin de la playlist
            }
        }
    }
    
    return getCurrentSong();
}

Song* Playlist::getPreviousSong() {
    if (isEmpty()) return nullptr;
    
    if (shuffleMode) {
        // Seleccionar aleatoriamente
        int newIndex = rand() % songs.size();
        while (newIndex == currentIndex && songs.size() > 1) {
            newIndex = rand() % songs.size();
        }
        currentIndex = newIndex;
    } else {
        if (currentIndex > 0) {
            currentIndex--;
        } else {
            if (repeatMode == 2) {
                currentIndex = songs.size() - 1;
            } else {
                return nullptr;
            }
        }
    }
    
    return getCurrentSong();
}

void Playlist::shuffle() {
    if (isEmpty() || songs.size() < 2) return;
    
    // Convertir a vector para mezclar
    std::vector<Song*> temp;
    for (int i = 0; i < songs.size(); i++) {
        temp.push_back(songs.get(i));
    }
    
    // Mezclar
    for (int i = temp.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Song* tempSong = temp[i];
        temp[i] = temp[j];
        temp[j] = tempSong;
    }
    
    // Reconstruir lista
    songs.clear();
    for (Song* song : temp) {
        songs.add(song);
    }
    
    currentIndex = 0;
}

void Playlist::setShuffleMode(bool enabled) {
    shuffleMode = enabled;
    if (enabled && !isEmpty()) {
        shuffle();
    }
}

bool Playlist::getShuffleMode() const {
    return shuffleMode;
}

void Playlist::setRepeatMode(int mode) {
    repeatMode = mode;
}

int Playlist::getRepeatMode() const {
    return repeatMode;
}

int Playlist::size() const {
    return songs.size();
}

bool Playlist::isEmpty() const {
    return songs.isEmpty();
}

Song* Playlist::getSongAt(int index) {
    if (index < 0 || index >= songs.size()) return nullptr;
    return songs.get(index);
}

std::vector<Song*> Playlist::getAllSongs() {
    std::vector<Song*> result;
    for (int i = 0; i < songs.size(); i++) {
        result.push_back(songs.get(i));
    }
    return result;
}

void Playlist::displayPlaylist() const {
    if (isEmpty()) {
        std::cout << "La lista de reproducción está vacía." << std::endl;
        return;
    }
    
    std::cout << "\n=== LISTA DE REPRODUCCIÓN ===" << std::endl;
    for (int i = 0; i < songs.size(); i++) {
        std::cout << i + 1 << ". " << songs.get(i)->toString();
        if (i == currentIndex) {
            std::cout << " (Reproduciendo)";
        }
        std::cout << std::endl;
    }
}