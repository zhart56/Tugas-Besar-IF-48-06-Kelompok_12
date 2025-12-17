#ifndef RELASI_H_INCLUDED
#define RELASI_H_INCLUDED

#include "pengacara.h"
#include "klien.h"

void connectKlienToPengacara(List &L, string idPengacara, adrKlien C);

void deleteKlienFromPengacara(List &L, string idPengacara, string idKlien);

void showAllData(List L);

adrPengacara findParentOfKlien(List L, string idKlien);

adrKlien findKlienInPengacara(adrPengacara P, string idKlien);

int countKlienByPengacara(List L, string idPengacara);
int countPengacaraTanpaKlien(List L);

void pindahPengacara(List &L, string idKlien, string idPengacaraLama, string idPengacaraBaru);

#endif // RELASI_H_INCLUDED
