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
// Mencari Klien ada di pengacara mana
adrKlien findKlienDiPengacara(adrPengacara P, string idKlien);

#endif // RELASI_H_INCLUDED
