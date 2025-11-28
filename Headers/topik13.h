#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

// Pointer Declaration
typedef struct elmPengacara *adrPengacara;
typedef struct elmKlien *adrKlien;

// 1. STRUKTUR DATA CHILD (KLIEN)
// Sesuai Topik 13: Klien dilayani oleh Pengacara [cite: 316]
struct infotypeKlien {
    string namaKlien;
    string idKlien;
    string kasus; // Contoh: "Perdata", "Pidana"
};

struct elmKlien {
    infotypeKlien info;
    adrKlien next; // Pointer ke klien berikutnya dalam daftar milik satu pengacara
};

// 2. STRUKTUR DATA PARENT (PENGACARA)
// Sesuai Topik 13: Pengacara melayani banyak Klien [cite: 317]
struct infotypePengacara {
    string namaPengacara;
    string idPengacara;
    string firma; // Nama firma hukum
    int pengalaman; // Lama pengalaman (tahun)
};

struct elmPengacara {
    infotypePengacara info;
    adrPengacara next;      // Pointer ke Pengacara berikutnya
    adrKlien nextKlien;     // RELASI: Menunjuk ke Klien pertama yang ditangani (Head of Child List)
};

// 3. LIST UTAMA
struct List {
    adrPengacara first; // Head dari List Pengacara
};

// ==========================================
// PRIMITIF (Function & Procedure Headers)
// ==========================================

// --- CREATE ---
void createList(List &L);
adrPengacara createElmPengacara(infotypePengacara data);
adrKlien createElmKlien(infotypeKlien data);

// --- INSERT PARENT (PENGACARA) ---
// Mencakup poin penilaian "Insert element parent" [cite: 119]
void insertFirstPengacara(List &L, adrPengacara P);
void insertLastPengacara(List &L, adrPengacara P);
void insertAfterPengacara(List &L, adrPengacara Prec, adrPengacara P);

// --- INSERT CHILD (RELASI) ---
// Mencakup poin penilaian "Insert element child" & "Insert element relation" [cite: 121, 123]
// Karena model 1-N (Nested List), insert child otomatis membuat relasi.
void insertKlien(List &L, adrPengacara P, adrKlien C);

// --- DELETE PARENT ---
// Mencakup poin penilaian "Delete element parent" [cite: 125]
// Hati-hati: Menghapus pengacara berarti menghapus semua kliennya juga.
void deleteFirstPengacara(List &L, adrPengacara &P);
void deleteLastPengacara(List &L, adrPengacara &P);
void deleteAfterPengacara(List &L, adrPengacara Prec, adrPengacara &P);
void deletePengacaraTertentu(List &L, string idPengacara); // Gabungan search & delete

// --- DELETE CHILD ---
// Mencakup poin penilaian "Delete element child" [cite: 127]
void deleteKlien(List &L, string idPengacara, string idKlien);

// --- FIND / SEARCH ---
// Mencakup poin penilaian "Find element Parent" & "Find element child" [cite: 131, 134]
adrPengacara findPengacara(List L, string idPengacara);
adrKlien findKlien(List L, string idPengacara, string idKlien);
// Mencari apakah Pengacara X menangani Klien Y [cite: 135]
bool isRelasi(List L, string idPengacara, string idKlien);

// --- SHOW / VIEW ---
// Mencakup poin "Show all data" parent & child [cite: 136, 138]
void showAllPengacara(List L);
void showAllKlien(List L); // Menampilkan semua klien dari semua pengacara
void showKlienByPengacara(List L, string idPengacara); // Child dari parent tertentu [cite: 139]
void showPengacaraByKlien(List L, string idKlien); // Parent dari child tertentu [cite: 140]

// --- COUNT / STATISTIK ---
// Mencakup poin "Count relation" [cite: 144-146]
int countKlienByPengacara(List L, string idPengacara); // Jumlah child element parent tertentu
int countPengacaraTanpaKlien(List L); // Count element parent yang tidak memiliki child
int countKlienTanpaPengacara(List L); // Opsional (biasanya 0 karena nested list)

// --- EDIT ---
// Mencakup poin "Edit relasi" [cite: 147]
// Memindahkan klien dari Pengacara A ke Pengacara B
void pindahPengacara(List &L, string idKlien, string idPengacaraLama, string idPengacaraBaru);

#endif // TUBES_H_INCLUDED
