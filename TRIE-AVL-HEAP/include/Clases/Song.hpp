#ifndef SONG_HPP
#define SONG_HPP

#include <string>

class Song {
private:
    int id;
    std::string nombre;
    std::string artista;
    std::string album;
    int year;	// año lanzamiento
    int duracion;  // duracion en segundos
    std::string ruta;
	int playCount;
    
public:
    // Constructor
    Song();
    Song(int id, const std::string& nombre, const std::string& artista,
         const std::string& album, int year, int duracion, const std::string& ruta);
    
    // Getters
    int getId() const;
    std::string getNombre() const;
    std::string getArtista() const;
    std::string getAlbum() const;
    int getYear() const;
    int getDuracion() const;
    std::string getRuta() const;
	int getPlayCount() const;
	std::string getDuracionFormateada() const;
    
    // Setters
    void setId(int id);
    void setNombre(const std::string& nombre);
    void setArtista(const std::string& artista);
    void setAlbum(const std::string& album);
    void setYear(int year);
    void setDuracion(int duracion);
    void setRuta(const std::string& ruta);
	void setPlayCount(int count);
	void incrementPlayCount(); 
    
    // Operadores
    bool operator==(const Song& other) const;
    bool operator!=(const Song& other) const;
    
    // Mostrar informacion
    std::string toString() const;
    std::string getDisplayString() const;
};

#endif