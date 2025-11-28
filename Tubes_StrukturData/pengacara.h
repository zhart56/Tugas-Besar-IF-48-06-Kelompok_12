#ifndef PENGACARA_H_INCLUDED
#define PENGACARA_H_INCLUDED

#include "klien.h"
#include <iostream>
using namespace std;

// Definisi Pointer Parent
typedef struct elmPengacara *adrPengacara;

struct infotypePengacara {
    string namaPengacara;
    string idPengacara;
    string firma;
};

struct elmPengacara {
    infotypePengacara info;
    adrPengacara next;      // Next sesama pengacara
    adrKlien nextKlien;     // RELASI: Menunjuk ke Klien pertama (Head of Child)
};

struct List {
    adrPengacara first;
};

// Primitif Pengacara
void createList(List &L);
adrPengacara createElmPengacara(infotypePengacara data);
void insertLastPengacara(List &L, adrPengacara P);
void deletePengacara(List &L, string idPengacara); // Hapus parent
adrPengacara findPengacara(List L, string idPengacara);
void showListPengacara(List L); // Hanya menampilkan data pengacara (tanpa klien)

#endif // PENGACARA_H_INCLUDED
