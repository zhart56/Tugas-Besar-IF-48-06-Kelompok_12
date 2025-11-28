#ifndef PENGACARA_H_INCLUDED
#define PENGACARA_H_INCLUDED

#include "klien.h"
#include <iostream>
using namespace std;

#include "klien.h"
#include <iostream>
using namespace std;

// --- DEFINISI TYPE ---
typedef struct elmPengacara *adrPengacara;

struct infotypePengacara {
    string namaPengacara;
    string idPengacara;
    string firma;
};

struct elmPengacara {
    infotypePengacara info;
    adrPengacara next;
    adrPengacara prev;
    adrKlien nextKlien;
};

struct List {
    adrPengacara first;
    adrPengacara last;
};

// --- PRIMITIF PARENT (DLL) ---
void createList(List &L);
adrPengacara createElmPengacara(infotypePengacara data);

// Insert & Delete (Logika DLL)
void insertLastPengacara(List &L, adrPengacara P);
void deletePengacara(List &L, string idPengacara);

// Utility
adrPengacara findPengacara(List L, string idPengacara);
void showListPengacara(List L);

#endif // PENGACARA_H_INCLUDED
