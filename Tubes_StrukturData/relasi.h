#ifndef RELASI_H_INCLUDED
#define RELASI_H_INCLUDED

#include "pengacara.h"
#include "klien.h"

// Menghubungkan Pengacara dan Klien
void connectKlienToPengacara(List &L, string idPengacara, adrKlien C);

// Menghapus Klien dari Pengacara tertentu
void deleteKlienFromPengacara(List &L, string idPengacara, string idKlien);

// Menampilkan Pengacara BESERTA Kliennya (Hierarki)
void showAllData(List L);

// --- SEARCHING (FIND) ---
adrPengacara findParentOfKlien(List L, string idKlien);
adrKlien findKlienInPengacara(adrPengacara P, string idKlien);

// --- COUNTING (STATISTIK) ---
int countKlienByPengacara(List L, string idPengacara);
int countPengacaraTanpaKlien(List L);

// --- EDIT RELASI ---
void pindahPengacara(List &L, string idKlien, string idPengacaraLama, string idPengacaraBaru);

#endif // RELASI_H_INCLUDED
