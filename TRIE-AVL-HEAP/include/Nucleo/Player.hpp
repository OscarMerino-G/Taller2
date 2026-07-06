#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Clases/MusicLibrary.hpp"
#include "../Clases/Playlist.hpp"
#include "../Estructura_Datos/Stack.hpp"
#include "../Estructura_Datos/Trie.hpp"
#include "../Estructura_Datos/Heap.hpp"
#include "FileManager.hpp"

class Player {
private:
    
    Playlist playlist;
    Stack<Song> history;  // Historial de canciones
	Trie searchTrie;
    Heap* songHeap;      // Max-heap para top canciones
    Heap* artistHeap;    // Min-heap para top artistas
    
    PlayerStatus status;
    
    bool needsSave;  // para saber si hay cambios que guardar
    
    void updateStatusFromPlaylist();
    void saveIfNeeded();
    void clearScreen() const;
    void updateHeapWithSong(Song* song);
    void playSong(Song* song);  // Método auxiliar
    void incrementSongPlayCount(Song* song);
	
	void initializeDataStructures();
	
	void showTopArtists();
	void addSongToPlaylist(Song* song);
	void addSongToPlaylist(int index);
    void showTopSongs();
	
    void displayMainMenu() const;
    void displayNowPlaying() const;
    void handleMainMenuInput(char option);
    
    void togglePlayPause();
    void previousTrack();
    void nextTrack();
    void toggleShuffle();
    void toggleRepeat();
    void showPlaylistMenu();
    void showSongListMenu();
    
    void generateRandomPlaylist();
    void updatePlaylistAfterShuffle();
    void handleRepeatMode();
    
	
	
    // submenu de canciones
    void displaySongList() const;
    void handleSongListMenu();
    void playSpecificSong(int index);
    void addNewSong();
    void deleteSong(int index);
    
    // utiles
    int getInputNumber(const std::string& prefix) const;
    std::string getInputString(const std::string& prompt) const;
    int getInputInt(const std::string& prompt) const;
	
public:
	MusicLibrary library;
    Player();
    ~Player();
	
    //void showTopSongs();        // Top 10 canciones
    //void showTopArtists();      // Top 10 artistas
    void showArtistSongs(const std::string& artistName);
    void searchSongs();         // Búsqueda con Trie
    
    bool initialize();
    void run();
    void updateSearchStructures();  // Reconstruye Trie y Heap
	
};

#endif