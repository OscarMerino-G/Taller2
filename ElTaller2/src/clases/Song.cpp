#include "../../include/clases/Song.hpp"
// Song.cpp
Song::Song() : playCount(0) {}

Song::Song(const std::string& id, const std::string& titulo, const std::string& artista,
           const std::string& album, const std::string& year)
    : id(id), titulo(titulo), artista(artista), album(album), year(year), playCount(0) {}

Song::~Song() {}

std::string Song::getId() const { return id; }
std::string Song::getTitulo() const { return titulo; }
std::string Song::getArtista() const { return artista; }
std::string Song::getAlbum() const { return album; }
std::string Song::getYear() const { return year; }
int Song::getPlayCount() const { return playCount; }

void Song::setTitulo(const std::string& titulo) { this->titulo = titulo; }
void Song::setArtista(const std::string& artista) { this->artista = artista; }
void Song::setAlbum(const std::string& album) { this->album = album; }
void Song::setYear(const std::string& year) { this->year = year; }

void Song::incrementarPlayCount() { playCount++; }
void Song::setPlayCount(int count) { playCount = count; }

bool Song::operator<(const Song& other) const {
    if (playCount != other.playCount) {
        return playCount < other.playCount;
    }
    if (titulo != other.titulo) {
        return titulo < other.titulo;
    }
    return artista < other.artista;
}

bool Song::operator>(const Song& other) const {
    if (playCount != other.playCount) {
        return playCount > other.playCount;
    }
    if (titulo != other.titulo) {
        return titulo > other.titulo;
    }
    return artista > other.artista;
}

bool Song::operator==(const Song& other) const {
    return id == other.id;
}

std::string Song::toString() const {
    return titulo + " - " + artista;
}