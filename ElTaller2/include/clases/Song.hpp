#ifndef SONG_HPP
#define SONG_HPP
#include <string>
// Song.hpp
class Song {
private:
    std::string id;
    std::string titulo;
    std::string artista;
    std::string album;
    std::string year;
    int playCount;
    
public:
    Song();
    Song(const std::string& id, const std::string& titulo, const std::string& artista, 
         const std::string& album, const std::string& year);
    ~Song();
    
    // Getters
    std::string getId() const;
    std::string getTitulo() const;
    std::string getArtista() const;
    std::string getAlbum() const;
    std::string getYear() const;
    int getPlayCount() const;
    
    // Setters
    void setTitulo(const std::string& titulo);
    void setArtista(const std::string& artista);
    void setAlbum(const std::string& album);
    void setYear(const std::string& year);
    void incrementarPlayCount();
    void setPlayCount(int count);
    
	// para ordenamiento
    bool operator<(const Song& other) const;
    bool operator>(const Song& other) const;
    bool operator==(const Song& other) const;
    
    std::string toString() const;
};

#endif