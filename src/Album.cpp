//
// Created by Alexandra Zamfirescu on 13.03.2023.
//

#include "../headers/Album.h"
#include <sstream>



Album::Album() {
    this->numeArtist = "Alexandra Zamfirescu";
    this -> year = 2023;
    this -> name = "Nume de album";
    this -> nrSongs = 15;
//    this -> duration = 10.24 ;
    this -> songs = {Song(), Song(), Song(), Song(), Song(),Song(), Song(), Song(), Song(), Song(), Song(), Song(), Song(), Song(), Song()};
}

Album::Album(const unsigned int& year, const std::string& name, const unsigned int& nrSongs, const std::vector<Song>&songs, std::string& numeArtist) {
    this -> year = year;
    this -> name = name;
    this -> nrSongs = nrSongs;
    this->numeArtist = numeArtist;
    this -> songs = songs;

    //comentez alocarile dinamice facute manual
//    if (nrSongs > 0 && songs != nullptr) {
//        this->songs = new Song[nrSongs];
//
//        for (int i = 0; i < nrSongs; i++)
//            (this -> songs)[i] = songs[i];
//    } else {
//        this -> nrSongs = 0;
//        this -> songs = nullptr;
//    }

    }
Album::Album(const Album &object){
    this -> year = object.year;
    this -> name = object.name;
    this -> nrSongs = object.nrSongs;
    this->numeArtist = object.numeArtist;
    this -> songs = object.songs;

    //comentez alocarile dinamice facute manual
//    if (object.nrSongs > 0) {
//        this -> songs = new Song[object.nrSongs];
//
//        for (int i = 0; i < object.nrSongs; i++)
//            this -> songs[i] = object.songs[i];
//    } else {
//        this -> nrSongs = 0;
//        this -> songs = nullptr;
//    }
}

Album::~Album() {}

////functie de adaugare a unei melodii in album
//void Album::addSong(const Song &song) {
//    this -> songs.push_back(song);
////    this -> nrSongs++;
//}


//calculez durata totala a albumului
std::string Album::getTotalDurationConverted()const {
    int nrSongs = songs.size(); // nr de melodii din album
    double totalDuration = 0.0;

    for (const Song& song : songs) {
        totalDuration += song.getDuration();
    }

    int hours = static_cast<int>(totalDuration) / 60; //ora
    int minutes = static_cast<int>(totalDuration) % 60; //minute

    std::ostringstream ss; // std::ostringstream pentru a converti double-ul in string
    if (hours > 0) { //daca durata e mai mare de o ora, afisez si ora
        ss << hours << " h ";
    }
    ss << minutes << " min";
    std::string totalDurationConverted = ss.str();

    return totalDurationConverted;

}


//operator <<
std::ostream &operator<<(std::ostream &os, const Album &album) {

    os <<album.name<<" - "<<album.numeArtist<<", "<< album.year << ", " << album.nrSongs<< " songs " << "\n";
    os << "\n";

    for(int i = 0; i < album.nrSongs; i++) {
        if (i < 9)
            os << " " << i + 1 << ". " << album.songs[i];
        else
            os << i + 1 << ". " << album.songs[i];
    }
    os << "\n";
    os << album.getTotalDurationConverted() << "\n\n";
    return os;
}


//operator >>
std::istream &operator>>(std::istream &is, Album &album) {
    std::cout << "Enter the name of the album: ";
    std::getline(is, album.name);
    std::cout << "Enter the name of the artist: ";
    std::getline(is, album.numeArtist);
    std::cout << "Type the year of the album: ";
    is >> album.year;
    std::cout << "Type the number of songs: ";
    is >> album.nrSongs;

    album.songs.clear();
    album.songs.resize(album.nrSongs);

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // citirea melodiilor
    for (int i = 0; i < album.nrSongs; i++){
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignorare newline din buffer
        is >> album.songs[i];
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return is;

}

//getters and setters
unsigned int Album::getYear() const {
    return year;
}
void Album::setYear(unsigned int year) {
    Album::year = year;
}
std::string Album::getName() const {
    return name;
}
void Album::setName(std::string& name) {
    Album::name = name;
}
unsigned int Album::getNrSongs() const {
    return nrSongs;
}
void Album::setNrSongs(unsigned int nrSongs) {
    Album::nrSongs = nrSongs;
}
std::vector<Song>Album::getSongs() const {
    return songs;
}
void Album::setSongs(std::vector<Song>&songs) {
    Album::songs = songs;
}


bool Album::operator==(const Album &rhs) const {
    if( year == rhs.year && name == rhs.name && nrSongs == rhs.nrSongs) {
        for(int i = 0; i < nrSongs; i++)
            if(songs[i] != (rhs.songs)[i])
                return false;
    }
    return true;
}

bool Album::operator!=(const Album &rhs) const {
    return !(rhs == *this);
}
