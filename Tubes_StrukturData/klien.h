#ifndef KLIEN_H_INCLUDED
#define KLIEN_H_INCLUDED

#include <iostream>
using namespace std;

// Definisi Pointer Child
typedef struct elmKlien *adrKlien;

struct infotypeKlien {
    string namaKlien;
    string idKlien;
    string kasus;
};

struct elmKlien {
    infotypeKlien info;
    adrKlien next; // Pointer ke sesama klien
};

adrKlien createElmKlien(infotypeKlien data);
void showInfoKlien(adrKlien C); // Menampilkan info 1 klien saja

#endif // KLIEN_H_INCLUDED
