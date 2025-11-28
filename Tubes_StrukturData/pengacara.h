#ifndef PENGACARA_H_INCLUDED
#define PENGACARA_H_INCLUDED

#include "klien.h"
#include <iostream>
using namespace std;
// Definisi Parent
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


void createList(List &L);
adrPengacara createElmPengacara(infotypePengacara data);

void insertLastPengacara(List &L, adrPengacara P);
void deletePengacara(List &L, string idPengacara);

adrPengacara findPengacara(List L, string idPengacara);
void showListPengacara(List L);

#endif // PENGACARA_H_INCLUDED
