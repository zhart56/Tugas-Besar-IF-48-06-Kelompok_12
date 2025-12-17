#ifndef KLIEN_H_INCLUDED
#define KLIEN_H_INCLUDED

#include <iostream>
using namespace std;

typedef struct elmKlien *adrKlien;

struct infotypeKlien {
    string namaKlien;
    string idKlien;
    string kasus;
};

struct elmKlien {
    infotypeKlien info;
    adrKlien next;
};

adrKlien createElmKlien(infotypeKlien data);
void showInfoKlien(adrKlien C);

adrKlien findKlien(adrKlien first, string idKlien);

#endif // KLIEN_H_INCLUDED
