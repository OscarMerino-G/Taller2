#include <iostream>
#include <cstdlib>
#include "core/Player.hpp"
#include "core/SearchEngine.hpp"
#include "core/RankingEngine.hpp"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void displayMenu(Player& player) {
    Song current = player.getCurrentSong();
    std::cout << "\n========================================\n";
    if (current.getTitle()[0] != '\0') {
        std::cout << "Reproduciendo: " << current.getTitle() << "\n";
        std::cout << "Artista: " << current.getArtist() << "\n";
        std::cout << "Album: " << current.getAlbum() << "\n";
    } else {
        std::cout << "No hay cancion reproduciendose\n";
    }
    std::cout << "========================================\n";
    std::cout << "Opciones:\n";
    std::cout << "W - Reproducir/Pausar\n";
    std::cout << "Q - Pista Anterior\n";
    std::cout << "E - Pista Siguiente\n";
    std::cout << "S - Activar/Desactivar modo aleatorio\n";
    std::cout << "R - Repeticion (Desactivado/Repetir una/Repetir todas)\n";
    std::cout << "A - Ver lista de reproduccion actual\n";
    std::cout << "L - Listado de canciones\n";
    std::cout << "F - Buscar canciones\n";
    std::cout << "T - TOP 10 Artistas y Canciones\n";
    std::cout << "X - Salir\n";
    std::cout << "Ingrese Opcion: ";
}

void showPlaylist(Playlist& playlist) {
    std::cout << "\n=== Lista de Reproduccion Actual ===\n";
    if (playlist.isEmpty()) {
        std::cout << "La lista de reproduccion esta vacia.\n";
        return;
    }
    for (int i = 0; i < playlist.getSize(); i++) {
        Song& s = playlist.getSong(i);
        std::cout << i + 1 << ". " << s.getTitle() << " - " << s.getArtist() << "\n";
    }
    std::cout << "Presione Enter para continuar...";
    std::cin.get();
}

void showSongList(Library& library) {
    std::cout << "\n=== Listado de Canciones ===\n";
    List<Song>* songs = library.getAllSongs();
    for (int i = 0; i < songs->getSize(); i++) {
        Song& s = songs->get(i);
        std::cout << i + 1 << ". " << s.getTitle() << " - " << s.getArtist() 
                  << " [" << s.getPlayCount() << " reproducciones]\n";
    }
    delete songs;
    std::cout << "\nPresione Enter para continuar...";
    std::cin.get();
}

int main() {
    Player player;
    SearchEngine searchEngine(&player);
    RankingEngine rankingEngine(&player);
    
    // Cargar libreria y ranking
    player.loadLibrary("music_source.txt");
    player.loadRanking("song_ranking.txt");
    
    char option;
    while (true) {
        clearScreen();
        displayMenu(player);
        std::cin >> option;
        std::cin.ignore(); // Clear
        
        switch (option) {
            case 'W':
            case 'w':
                if (player.isSongPaused()) {
                    player.resume();
                    std::cout << "Reanudando reproduccion...\n";
                } else if (player.isSongPlaying()) {
                    player.pause();
                    std::cout << "Pausando...\n";
                } else {
                    player.playCurrent();
                }
                break;
                
            case 'Q':
            case 'q':
                player.previous();
                std::cout << "Pista anterior\n";
                break;
                
            case 'E':
            case 'e':
                player.next();
                std::cout << "Pista siguiente\n";
                break;
                
            case 'S':
            case 's':
                player.toggleShuffle();
                std::cout << (player.getPlaylist()->isShuffle() ? "Modo aleatorio activado\n" : "Modo aleatorio desactivado\n");
                break;
                
            case 'R':
            case 'r':
                player.toggleRepeat();
                int repeat = player.getPlaylist()->getRepeat();
                std::cout << "Repeticion: ";
                switch (repeat) {
                    case 0: std::cout << "Desactivado\n"; break;
                    case 1: std::cout << "Repetir una\n"; break;
                    case 2: std::cout << "Repetir todas\n"; break;
                }
                break;
                
            case 'A':
            case 'a':
                showPlaylist(*player.getPlaylist());
                break;
                
            case 'L':
            case 'l':
                showSongList(*player.getLibrary());
                break;
                
            case 'F':
            case 'f':
                searchEngine.execute();
                break;
                
            case 'T':
            case 't':
                rankingEngine.execute();
                break;
                
            case 'X':
            case 'x':
                player.saveRanking("song_ranking.txt");
                std::cout << "Saliendo del reproductor...\n";
                return 0;
                
            default:
                std::cout << "Opcion invalida. Intente de nuevo.\n";
                break;
        }
        
        if (option != 'A' && option != 'a' && option != 'L' && option != 'l' &&
            option != 'F' && option != 'f' && option != 'T' && option != 't') {
            std::cout << "Presione Enter para continuar...";
            std::cin.get();
        }
    }
    
    return 0;
}