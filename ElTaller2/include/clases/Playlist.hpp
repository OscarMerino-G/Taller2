#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP
#include "../../include/estructura_datos/LinkedList.hpp"
// Playlist.h
#include "Song.hpp"

class Playlist {
private:
    LinkedList<Song*> songs;
    int currentIndex;
    bool shuffleMode;
    bool repeatMode; // 0: apagado, 1: repetir uno, 2: repetir todo
    
public:
    Playlist();
    ~Playlist();
    
    void addSong(Song* song);
    void addSongAtEnd(Song* song);
    void removeSong(int index);
    void clear();
    
    Song* getCurrentSong();
    Song* getNextSong();
    Song* getPrevSong();
    void shuffle();
    
    void setShuffleMode(bool enabled);
    bool getShuffleMode() const;
    void setRepeatMode(int mode);
    int getRepeatMode() const;
    
    int size() const;
    bool isEmpty() const;
    Song* getSongAt(int index);
    std::vector<Song*> getAllSongs();
    
    void displayPlaylist() const;
};

#endif