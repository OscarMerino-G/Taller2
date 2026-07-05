#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP
// Reproductor.hpp
#include "../clases/MusicLibrery.hpp"
#include "../clases/Playlist.hpp"
#include "../estructura_datos/Heap.hpp"
#include <string>

class Reproductor{
private:
    MusicLibrery libreria;
    Playlist playlist;
    // Heap<Song*> songHeap;    // Para Top 10 canciones
    // Heap<std::pair<int, std::string>> artistHeap; // Para Top 10 arTistas
    
    bool isPlaying;
    Song* currentSong;
    
    void initializeDataStructures();
    //void updateHeaps();
    void displayMenu();

public:
    Reproductor();
    ~Reproductor();
    
    void run();
    void playSong(Song* song);
    void playSongAtIndex(int index);
    void addSongToPlaylist(Song* song);
    void addSongToPlaylistAtIndex(int index);
    
    // Funciones
    void searchSongs();
    //void showTopSongs();
    //void showTopArtistas();
    //void showArtistasongs(const std::string& artist);
    
    // Control de reproducción
    void togglePlayPause();
    void nextSong();
    void previousSong();
    void toggleShuffle();
    void toggleRepeat();
    void showPlaylist();
    void showAllSongs();
};
#endif