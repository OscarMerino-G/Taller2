#ifndef MUSIC_LIBRERY_HPP
#define MUSIC_LIBRERY_HPP

#include "../estructura_datos/LinkedList.hpp"
#include "Song.hpp"
#include "../estructura_datos/Trie.hpp"
#include "../estructura_datos/AVL.hpp"
#include <string>
#include <vector>
#include <iostream>

class MusicLibrery {
private:
    LinkedList<Song*> songs;
    AVLTree A_artistas;
    Trie A_trie;

public:
    MusicLibrery();
    ~MusicLibrery();

    void loadFromFile(const std::string& filename);
    void loadRankingFromFile(const std::string& filename);
    void saveRankingToFile(const std::string& filename);

    LinkedList<Song*>& getSongsList();

    void incrementPlayCount(Song* song);
    std::vector<Song*> searchSongs(const std::string& query);
    std::vector<Song*> getArtistaSongs(const std::string& artista);

    void displayAllSongs() const;
};

#endif