#include "../../include/clases/MusicLibrery.hpp"

MusicLibrery::MusicLibrery() {}

MusicLibrery::~MusicLibrery() {
    for (size_t i = 0; i < songs.size(); i++) {
        delete songs.at(i);
    }
    songs.clear();
}

void MusicLibrery::loadFromFile(const std::string& filename) {
    // STUB temporal.
    // Tu compañero implementará la lectura real del archivo.

    Song* s1 = new Song("1", "Fire Dance", "Vivid BAD Squad", "Fire Dance (Single)", "2025");
    Song* s2 = new Song("2", "World is Mine", "Ryo feat. Hatsune Miku", "World is Mine", "2008");
    Song* s3 = new Song("3", "Crossing Field", "LiSA", "Crossing Field", "2012");

    songs.pushBack(s1);
    songs.pushBack(s2);
    songs.pushBack(s3);

    A_artistas.insert(s1);
    A_artistas.insert(s2);
    A_artistas.insert(s3);
}

void MusicLibrery::loadRankingFromFile(const std::string& filename) {
    // STUB temporal.
}

void MusicLibrery::saveRankingToFile(const std::string& filename) {
    // STUB temporal.
}

LinkedList<Song*>& MusicLibrery::getSongsList() {
    return songs;
}

void MusicLibrery::incrementPlayCount(Song* song) {
    if (song != nullptr) {
        song->incrementarPlayCount();
    }
}

std::vector<Song*> MusicLibrery::searchSongs(const std::string& query) {
    std::vector<Song*> result;
    return result;
}

std::vector<Song*> MusicLibrery::getArtistaSongs(const std::string& artista) {
    std::vector<Song*> result;

    AVLNodo* node = A_artistas.search(artista);

    if (node == nullptr) {
        return result;
    }

    for (size_t i = 0; i < node->canciones.size(); i++) {
        result.push_back(node->canciones.at(i));
    }

    return result;
}

void MusicLibrery::displayAllSongs() const {
    std::cout << "\n=== Biblioteca de canciones ===" << std::endl;

    for (size_t i = 0; i < songs.size(); i++) {
        Song* song = songs.at(i);
        if (song != nullptr) {
            std::cout << i + 1 << ". " << song->toString() << std::endl;
        }
    }
}