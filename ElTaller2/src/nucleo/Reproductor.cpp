#include "../../include/nucleo/Reproductor.hpp"
#include <iostream>
#include <cctype>
#include <vector>
#include <map>
// Reproductor.cpp
// ALGORITHM ES PARTE DE STL 
// TO-DO 
// CORREGIR


// Limpia la consola
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

Reproductor::Reproductor() : isPlaying(false), currentSong(nullptr) {
    // Cargar libreria canciones 
    libreria.loadFromFile("music_source.txt");
    libreria.loadRankingFromFile("song_ranking.txt");
    
    // Inicializar estructuras
    initializeDataStructures();
    
    // Si hay canciones, agregar todas a la playlist
    LinkedList<Song*>& songs = libreria.getSongsList();
    for (int i = 0; i < songs.size(); i++) {
        playlist.addSong(songs.at(i));
    }
    
    // Actualizar heaps
    //updateHeaps();
}

Reproductor::~Reproductor() {
    libreria.saveRankingToFile("song_ranking.txt");
}

void Reproductor::initializeDataStructures() {
    // Inicializar heaps
    //songHeap = Heap<Song*>(false); // Max heap
    //artistasHeap = Heap<std::pair<int, std::string>>(false); // Max heap
}

/*
void Reproductor::updateHeaps() {
    // Limpiar heaps
    songHeap.clear();
    artistasHeap.clear();
    
    // Actualizar heap de canciones
    LinkedList<Song*>& songs = libreria.getSongsList();
    for (int i = 0; i < songs.size(); i++) {
        Song* song = songs.at(i);
        if (song->getPlayCount() > 0) {
            songHeap.push(song);
        }
    }
    
    // Actualizar heap de artistas
    std::map<std::string, int> artistasCounts;
    for (int i = 0; i < songs.size(); i++) {
        Song* song = songs.at(i);
        if (song->getPlayCount() > 0) {
            artistasCounts[song->getArtista()] += song->getPlayCount();
        }
    }
    
    for (auto& pair : artistasCounts) {
        artistasHeap.push(std::make_pair(pair.second, pair.first));
    }
}
*/
void Reproductor::playSong(Song* song) {
    if (song == nullptr) return;
    
    currentSong = song;
    isPlaying = true;
    libreria.incrementPlayCount(song);
    //updateHeaps();
    
    std::cout << "Reproduciendo: " << song->toString() << std::endl;
}

void Reproductor::playSongAtIndex(int index) {
    Song* song = playlist.getSongAt(index);
    if (song != nullptr) {
        playSong(song);
    }
}

void Reproductor::addSongToPlaylist(Song* song) {
    if (song != nullptr) {
        playlist.addSongAtEnd(song);
        std::cout << "Canción agregada a la playlist: " << song->toString() << std::endl;
    }
}

void Reproductor::addSongToPlaylistAtIndex(int index) {
    // En el contexto de búsqueda o top, index es la posición en el listado mostrado
    // Buscar la canción correspondiente en el listado actual
    // Esta funcionalidad se maneja en los métodos específicos
}

void Reproductor::searchSongs() {
    clearScreen();
    std::string query;
    
    while (true) {
        std::cout << "\n=== BÚSQUEDA DE CANCIONES ===" << std::endl;
        std::cout << "Buscar canciones que contengan: ";
        std::getline(std::cin, query);
        
        if (query.empty()) {
            return; // Volver al menú principal
        }
        
        std::vector<Song*> results = libreria.searchSongs(query);
        
        clearScreen();
        if (results.empty()) {
            std::cout << "No se encontraron canciones que coincidan con: " << query << std::endl;
            continue;
        }
        
        std::cout << "\n=== Resultados para: " << query << " ===" << std::endl;
        for (int i = 0; i < results.size(); i++) {
            std::cout << i + 1 << ". " << results[i]->toString() << std::endl;
        }
        
        std::cout << "\nOpciones:" << std::endl;
        std::cout << "R<num> - Reproducir canción seleccionada" << std::endl;
        std::cout << "A<num> - Agregar canción seleccionada al final de la playlist actual" << std::endl;
        std::cout << "F - Repetir búsqueda con un texto diferente" << std::endl;
        std::cout << "V - Volver al menú principal" << std::endl;
        std::cout << "Ingrese Opción: ";
        
        std::string option;
        std::getline(std::cin, option);
        
        if (option == "V" || option == "v") {
            return;
        } else if (option == "F" || option == "f") {
            clearScreen();
            continue;
        } else if (option.length() > 1) {
            char action = option[0];
            std::string numStr = option.substr(1);
            
            try {
                int index = std::stoi(numStr) - 1;
                if (index >= 0 && index < results.size()) {
                    if (action == 'R' || action == 'r') {
                        playSong(results[index]);
                    } else if (action == 'A' || action == 'a') {
                        addSongToPlaylist(results[index]);
                    } else {
                        std::cout << "Opción inválida" << std::endl;
                    }
                } else {
                    std::cout << "Índice fuera de rango" << std::endl;
                }
            } catch (...) {
                std::cout << "Opción inválida" << std::endl;
            }
        } else {
            std::cout << "Opción inválida" << std::endl;
        }
    }
}
/*
void Reproductor::showTopSongs() {
    clearScreen();
    
    std::vector<Song*> topSongs = songHeap.getTopN(10);
    
    if (topSongs.empty()) {
        std::cout << "No hay canciones reproducidas para mostrar." << std::endl;
        std::cout << "Presione Enter para continuar...";
        std::cin.get();
        return;
    }
    
    std::cout << "\n=== TOP 10 Canciones más escuchadas ===" << std::endl;
    for (int i = 0; i < topSongs.size(); i++) {
        std::cout << i + 1 << ". [" << topSongs[i]->getPlayCount() << "] " 
                  << topSongs[i]->toString() << std::endl;
    }
    
    std::cout << "\nOpciones:" << std::endl;
    std::cout << "R<num> - Reproducir canción seleccionada" << std::endl;
    std::cout << "A<num> - Agregar canción seleccionada al final de la playlist actual" << std::endl;
    std::cout << "A - Top 10 artistas más escuchados" << std::endl;
    std::cout << "V - Volver al menú principal" << std::endl;
    std::cout << "Ingrese Opción: ";
    
    std::string option;
    std::getline(std::cin, option);
    
    if (option == "V" || option == "v") {
        return;
    } else if (option == "A" || option == "a") {
        showTopartistass();
        return;
    } else if (option.length() > 1) {
        char action = option[0];
        std::string numStr = option.substr(1);
        
        try {
            int index = std::stoi(numStr) - 1;
            if (index >= 0 && index < topSongs.size()) {
                if (action == 'R' || action == 'r') {
                    playSong(topSongs[index]);
                } else if (action == 'A' || action == 'a') {
                    addSongToPlaylist(topSongs[index]);
                } else {
                    std::cout << "Opción inválida" << std::endl;
                }
            } else {
                std::cout << "Índice fuera de rango" << std::endl;
            }
        } catch (...) {
            std::cout << "Opción inválida" << std::endl;
        }
    } else {
        std::cout << "Opción inválida" << std::endl;
    }
}

void Reproductor::showTopartistass() {
    clearScreen();
    
    std::vector<std::pair<int, std::string>> topartistass = artistHeap.getTopN(10);
    
    if (topartistass.empty()) {
        std::cout << "No hay artistas reproducidos para mostrar." << std::endl;
        std::cout << "Presione Enter para continuar...";
        std::cin.get();
        return;
    }
    
    std::cout << "\n=== TOP 10 artistas más escuchados ===" << std::endl;
    for (int i = 0; i < topartistass.size(); i++) {
        std::cout << i + 1 << ". [" << topartistass[i].first << "] " 
                  << topartistass[i].second << std::endl;
    }
    
    std::cout << "\nOpciones:" << std::endl;
    std::cout << "S<num> - Mostrar canciones del artistasa" << std::endl;
    std::cout << "C - Top 10 canciones más escuchadas" << std::endl;
    std::cout << "V - Volver al menú principal" << std::endl;
    std::cout << "Ingrese Opción: ";
    
    std::string option;
    std::getline(std::cin, option);
    
    if (option == "V" || option == "v") {
        return;
    } else if (option == "C" || option == "c") {
        showTopSongs();
        return;
    } else if (option.length() > 1) {
        char action = option[0];
        std::string numStr = option.substr(1);
        
        try {
            int index = std::stoi(numStr) - 1;
            if (index >= 0 && index < topartistass.size()) {
                if (action == 'S' || action == 's') {
                    showartistasSongs(topartistass[index].second);
                } else {
                    std::cout << "Opción inválida" << std::endl;
                }
            } else {
                std::cout << "Índice fuera de rango" << std::endl;
            }
        } catch (...) {
            std::cout << "Opción inválida" << std::endl;
        }
    } else {
        std::cout << "Opción inválida" << std::endl;
    }
}

void Reproductor::showartistasSongs(const std::string& artistas) {
    clearScreen();
    
    std::vector<Song*> songs = libreria.getartistasSongs(artistas);
    
    if (songs.empty()) {
        std::cout << "No se encontraron canciones para: " << artistas << std::endl;
        std::cout << "Presione Enter para continuar...";
        std::cin.get();
        return;
    }
    
    std::cout << "\n=== Canciones de " << artistas << " ===" << std::endl;
    for (int i = 0; i < songs.size(); i++) {
        std::cout << i + 1 << ". " << songs[i]->getTitulo() << std::endl;
    }
    
    std::cout << "\nOpciones:" << std::endl;
    std::cout << "R<num> - Reproducir canción seleccionada" << std::endl;
    std::cout << "A<num> - Agregar canción seleccionada al final de la playlist actual" << std::endl;
    std::cout << "V - Volver al listado de TOP 10 artistas" << std::endl;
    std::cout << "X - Volver al menú principal" << std::endl;
    std::cout << "Ingrese Opción: ";
    
    std::string option;
    std::getline(std::cin, option);
    
    if (option == "V" || option == "v") {
        showTopartistass();
        return;
    } else if (option == "X" || option == "x") {
        return;
    } else if (option.length() > 1) {
        char action = option[0];
        std::string numStr = option.substr(1);
        
        try {
            int index = std::stoi(numStr) - 1;
            if (index >= 0 && index < songs.size()) {
                if (action == 'R' || action == 'r') {
                    playSong(songs[index]);
                } else if (action == 'A' || action == 'a') {
                    addSongToPlaylist(songs[index]);
                } else {
                    std::cout << "Opción inválida" << std::endl;
                }
            } else {
                std::cout << "Índice fuera de rango" << std::endl;
            }
        } catch (...) {
            std::cout << "Opción inválida" << std::endl;
        }
    } else {
        std::cout << "Opción inválida" << std::endl;
    }
}
*/
void Reproductor::togglePlayPause() {
    if (currentSong == nullptr) {
        // Seleccionar primera canción de la playlist
        Song* firstSong = playlist.getCurrentSong();
        if (firstSong != nullptr) {
            playSong(firstSong);
        } else {
            std::cout << "La playlist está vacía" << std::endl;
        }
        return;
    }
    
    isPlaying = !isPlaying;
    if (isPlaying) {
        std::cout << "▶ Reproduciendo: " << currentSong->toString() << std::endl;
    } else {
        std::cout << "⏸ Pausado: " << currentSong->toString() << std::endl;
    }
}

void Reproductor::nextSong() {
    Song* next = playlist.getNextSong();
    if (next != nullptr) {
        playSong(next);
    } else {
        std::cout << "Fin de la playlist" << std::endl;
    }
}

void Reproductor::previousSong() {
    Song* prev = playlist.getPrevSong();
    if (prev != nullptr) {
        playSong(prev);
    }
}

void Reproductor::toggleShuffle() {
    bool newMode = !playlist.getShuffleMode();
    playlist.setShuffleMode(newMode);
    std::cout << "Modo aleatorio: " << (newMode ? "Activado" : "Desactivado") << std::endl;
}

void Reproductor::toggleRepeat() {
    int currentMode = playlist.getRepeatMode();
    currentMode = (currentMode + 1) % 3;
    playlist.setRepeatMode(currentMode);
    
    std::string modeStr;
    switch(currentMode) {
        case 0: modeStr = "Desactivado"; break;
        case 1: modeStr = "Repetir una"; break;
        case 2: modeStr = "Repetir todas"; break;
    }
    std::cout << "Repetición: " << modeStr << std::endl;
}

void Reproductor::showPlaylist() {
    clearScreen();
    playlist.displayPlaylist();
    std::cout << "\nPresione Enter para continuar...";
    std::cin.get();
}

void Reproductor::showAllSongs() {
    clearScreen();
    libreria.displayAllSongs();
    std::cout << "\nPresione Enter para continuar...";
    std::cin.get();
}

void Reproductor::displayMenu() {
    std::cout << "\n";
    if (currentSong != nullptr) {
        std::cout << "Reproduciendo: " << currentSong->toString() << std::endl;
        std::cout << "artistasa: " << currentSong->getArtista() << std::endl;
        std::cout << "Album: " << currentSong->getAlbum() << " [" << currentSong->getYear() << "]" << std::endl;
        std::cout << "Estado: " << (isPlaying ? "▶ Reproduciendo" : "⏸ Pausado") << std::endl;
    } else {
        std::cout << "No hay canción reproduciéndose" << std::endl;
    }
    
    std::cout << "\nOpciones:" << std::endl;
    std::cout << "W - Reproducir/Pausar" << std::endl;
    std::cout << "Q - Pista Anterior" << std::endl;
    std::cout << "E - Pista Siguiente" << std::endl;
    std::cout << "S - Activar/Desactivar modo aleatorio" << std::endl;
    std::cout << "R - Repetición (Desactivado/Repetir una/Repetir todas)" << std::endl;
    std::cout << "A - Ver lista de reproducción actual" << std::endl;
    std::cout << "L - Listado de canciones" << std::endl;
    std::cout << "F - Buscar canciones" << std::endl;
    std::cout << "T - TOP 10 artistas y Canciones" << std::endl;
    std::cout << "X - Salir" << std::endl;
    std::cout << "Ingrese Opción: ";
}

void Reproductor::run() {
    while (true) {
        clearScreen();
        displayMenu();
        
        std::string option;
        std::getline(std::cin, option);
        
        if (option.empty()) continue;
        
        char choice = std::toupper(option[0]);
        
        switch (choice) {
            case 'W':
                togglePlayPause();
                break;
            case 'Q':
                previousSong();
                break;
            case 'E':
                nextSong();
                break;
            case 'S':
                toggleShuffle();
                break;
            case 'R':
                toggleRepeat();
                break;
            case 'A':
                showPlaylist();
                break;
            case 'L':
                showAllSongs();
                break;
            case 'F':
                searchSongs();
                break;
            case 'T':
                //showTopSongs();
                break;
            case 'X':
                std::cout << "Saliendo del reproductor..." << std::endl;
                return;
            default:
                std::cout << "Opción inválida" << std::endl;
                std::cout << "Presione Enter para continuar...";
                std::cin.get();
                break;
        }
    }
}
