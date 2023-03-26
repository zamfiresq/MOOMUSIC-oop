//
// Created by Alexandra Zamfirescu on 23.03.2023.
//

#include "../headers/Playlist.h"


Playlist::Playlist() {
    this -> title = "numeObisnuit";
    this -> nrSongs = 0;
    this -> songs = nullptr;
    this -> nrAlbums = 0;
    this -> albums = nullptr;
    this -> duration = 0;
}

Playlist::Playlist(const myString& title, Song *songs, const int& nrSongs, Album *albums, const int& nrAlbums, const int& duration){
    this -> title = title;
    this -> nrSongs = nrSongs;
    this -> nrAlbums = nrAlbums;
    this -> duration = duration;

    if (nrSongs > 0 && songs != nullptr) {
        this -> songs = new Song[nrSongs];

        for (int i = 0; i < nrSongs; i++)
            (this -> songs)[i] = songs[i];
    } else {
        this -> nrSongs = 0;
        this -> songs = nullptr;
    }

    if (nrAlbums > 0 && albums != nullptr) {
        this -> albums = new Album[nrAlbums];

        for (int i = 0; i < nrAlbums; i++)
            (this -> albums)[i] = albums[i];
    } else {
        this -> nrAlbums = 0;
        this -> albums = nullptr;
    }
}

//apeland constructorul de copiere, se apeleaza constructorul de copiere al clasei Song si Album
Playlist::Playlist(const Playlist &object){
    this -> title = object.title;
    this -> nrSongs = object.nrSongs;
    this -> nrAlbums = object.nrAlbums;
    this -> duration = object.duration;

    if (object.nrSongs > 0) {
        this -> songs = new Song[object.nrSongs];

        for (int i = 0; i < object.nrSongs; i++)
            this -> songs[i] = object.songs[i];
    } else {
        this -> nrSongs = 0;
        this -> songs = nullptr;
    }

    if (object.nrAlbums > 0) {
        this -> albums = new Album[object.nrAlbums];

        for (int i = 0; i < object.nrAlbums; i++)
            this -> albums[i] = object.albums[i];
    } else {
        this -> nrAlbums = 0;
        this -> albums = nullptr;
    }
}

//apelam destructorul pentru a nu avea probleme cu alocarea memoriei
Playlist::~Playlist() {
    if (songs != nullptr)
        delete []songs;
    if (albums != nullptr)
        delete []albums;
}

//afisam playlist-ul
void Playlist::afisare() const {
    std::cout << title << " " << nrSongs << " " << nrAlbums << " " << duration << "\n\n";

    if(nrSongs) {
        std::cout << "Melodii:\n";
        for (int i = 0; i < nrSongs; i++)
            std::cout << i + 1 << ". " << songs[i];
        std::cout << "\n";
    }

    if(nrAlbums) {
        std::cout << "Albume:\n";
        for (int i = 0; i < nrAlbums; i++)
            std::cout << i + 1 << ". " << albums[i];
        std::cout << "\n";
    }
    std::cout << "\n";
}

//supraincarcarea operatorului <<
std::ostream& operator << (std::ostream& out, const Playlist& playlist) {
    out << playlist.title << " " << playlist.nrSongs << " " << playlist.nrAlbums << " " << playlist.duration << "\n\n";

    if(playlist.nrSongs) {
        out << "Melodii:\n";
        for (int i = 0; i < playlist.nrSongs; i++)
            out << i + 1 << ". " << playlist.songs[i];
        out << "\n";
    }

    if(playlist.nrAlbums) {
        out << "Albume:\n";
        for (int i = 0; i < playlist.nrAlbums; i++)
            out << i + 1 << ". " << playlist.albums[i];
        out << "\n";
    }
    out << "\n";
    return out;
}


//adaugam o melodie in playlist
void Playlist::addSong(const Song& song) {
    Song *mel = new Song[nrSongs + 1]; //mel reprezinta un vector de melodii cu nrSongs +1 melodii
    for (int i = 0; i < nrSongs; i++)
        mel[i] = songs[i]; //copiem toate melodiile din vectorul songs in mel

    mel[nrSongs] = song; //adaugam melodia noua in vectorul mel
    nrSongs++;

    if (songs != nullptr) //daca vectorul songs nu este gol, il vom sterge
        delete []songs;

    songs = new Song[nrSongs];
    for (int i = 0; i < nrSongs; i++)
        songs[i] = mel[i];
}

//adaugam un album in playlist
void Playlist::addAlbum(const Album& album) {
    Album *album1 = new Album[nrAlbums + 1]; //album1 reprezinta un vector de albume cu nrAlbums +1 albume
    for (int i = 0; i < nrAlbums; i++)
        album1[i] = albums[i]; //copiem toate albumele din vectorul albums in album1

    album1[nrAlbums] = album; //adaugam albumul nou in vectorul album1
    nrAlbums++;

    if (albums != nullptr) //daca vectorul albums nu este gol, il vom sterge
        delete []albums;

    albums = new Album[nrAlbums];
    for(int i = 0; i < nrAlbums; i++)
        albums[i] = album1[i]; //daca melodia din vectorul songs nu este egala cu melodia pe care vrem sa o stergem, o copiem in album1
}


//stergem o melodie din playlist
void Playlist::removeSong(Song &song) {
    Song *mel = new Song[nrSongs - 1]; //mel reprezinta un vector de melodii cu nrSongs -1 melodii
    int j = 0;
    for (int i = 0; i < nrSongs; i++) //daca melodia din vectorul songs nu este egala cu melodia pe care vrem sa o stergem, o copiem in mel
        if (songs[i] != song)
            mel[j++] = songs[i];
    nrSongs--;

    if (songs != nullptr) //daca vectorul songs nu este gol, il vom sterge
        delete[]songs;

    songs = new Song[nrSongs];
    for(int i = 0; i < nrSongs; i++)
        songs[i] = mel[i];
}

//stergem un album din playlist
void Playlist::removeAlbum(Album &album) {
    Album *album1 = new Album[nrAlbums - 1]; //album1 reprezinta un vector de albume cu nrAlbums -1 albume
    int j = 0;
    for (int i = 0; i < nrAlbums; i++) //daca albumul din vectorul albums nu este egal cu albumul pe care vrem sa il stergem, il copiem in album1
        if ( albums[i] != album)
            album1[j++] = albums[i];
    nrAlbums--;


    if (albums != nullptr) //daca vectorul albums nu este gol, il vom sterge
        delete[]albums;
    albums = new Album[nrAlbums];
    for(int i = 0; i < nrAlbums; i++)
        albums[i] = album1[i];
}

//returnam numele playlist-ului
myString Playlist::getTitle() const {
    return title;
}

//returnam numarul de melodii din playlist
int Playlist::getNrSongs() const {
    return nrSongs;
}

//returnam numarul de albume din playlist
int Playlist::getNrAlbums() const {
    return nrAlbums;
}

//returnam durata playlist-ului
int Playlist::getDuration() const {
    return duration;
}

//returnam vectorul de melodii
Song* Playlist::getSongs() const {
    return songs;
}

//returnam vectorul de albume
Album* Playlist::getAlbums() const {
    return albums;
}

//retunam functia ce modifica numele playlist-ului
void Playlist::changeTitle(const myString &title) {
    this -> title = title;
}

//returnam functia pentru sortare
void Playlist::sort() {
    int i, j;
    Song aux; //aux reprezinta o melodie auxiliara
    for (i = 0; i < nrSongs; i++)
         for(j = i + 1; j < nrSongs; j++) {
             myString titluI =  songs[i].getTitle();
             myString titluJ =  songs[j].getTitle();
             if (titluI > titluJ) {
                 aux = songs[i];
                 songs[i] = songs[j];
                 songs[j] = aux;
             }
         }
    }

//functia pentru cautare
void Playlist::search(const myString &title) {
    for (int i = 0; i < nrSongs; i++)
        if (songs[i].getTitle() == title) //daca melodia cautata este egala cu melodia din vectorul songs, o afisam
            std::cout << songs[i] << "\n";
}


//functii pentru play, pause, next, previous, repeat, repeat one, shuffle
void Playlist::play(int i)const {
    std::cout << "Playing " << songs[i].getTitle() << "\n";
}

void Playlist::pause(int i)const {
    std::cout << "Paused " << songs[i].getTitle() << "\n";
}

int Playlist::next(int i)const {
    if(i + 1 > nrSongs)
        i = -1;
    std::cout << "Playing next " << songs[++i].getTitle() << "\n";
    return i;
}

int Playlist::previous(int i)const {
    if(i - 1 < 0)
        i = nrSongs;
    std::cout << "Playing previous " << songs[--i] << "\n";
    return i;
}


int Playlist::repeatOne(int i)const {
    std::cout << "Repeating " << songs[i].getTitle() << "\n";
    return i;
}

//void Playlist::repeat()const {
//    std::cout << "Repeat " << title << "\n";
//}

void Playlist::shuffleSongs() {
//    urmeaza un randomizer pentru a shuffle-ui melodiile din playlist
    int i, j;
    Song aux; //aux reprezinta o melodie auxiliara
    for (i = 0; i < nrSongs; i++)
        for(j = i + 1; j < nrSongs; j++) {
            int random = rand() % 2; //random va lua valori de la 0 la 1
            if (random == 1) {
                aux = songs[i];
                songs[i] = songs[j];
                songs[j] = aux;
            }
        }
}

void Playlist::shuffle() {
    std::cout << "Shuffling " << title << "\n";
    shuffleSongs();
}
