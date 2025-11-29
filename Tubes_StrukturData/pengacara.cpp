#include "pengacara.h"

void createList(List &L) {
    L.first = NULL;
    L.last = NULL; // Inisialisasi last null untuk DLL
}

adrPengacara createElmPengacara(infotypePengacara data) {
    adrPengacara P = new elmPengacara;
    P->info = data;
    P->next = NULL;
    P->prev = NULL;      // DLL: Set prev null
    P->nextKlien = NULL;
    return P;
}

void insertLastPengacara(List &L, adrPengacara P) {
    if (L.first == NULL) {
        // List kosong, P jadi elemen satu-satunya
        L.first = P;
        L.last = P;
    } else {
        // Insert di belakang menggunakan pointer last (O(1))
        P->prev = L.last;  // Sambung balik
        L.last->next = P;  // Sambung depan
        L.last = P;        // Update last
    }
}

adrPengacara findPengacara(List L, string idPengacara) {
    adrPengacara P = L.first;
    while (P != NULL) {
        if (P->info.idPengacara == idPengacara) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void deletePengacara(List &L, string idPengacara) {
    adrPengacara P = findPengacara(L, idPengacara);

    if (P == NULL) {
        cout << "Gagal Hapus: Pengacara " << idPengacara << " tidak ditemukan." << endl;
        return;
    }

    // LOGIKA HAPUS DLL
    if (P == L.first && P == L.last) {
        // Kasus 1: Satu-satunya elemen
        L.first = NULL;
        L.last = NULL;
    }
    else if (P == L.first) {
        // Kasus 2: Hapus depan
        L.first = P->next;
        L.first->prev = NULL;
    }
    else if (P == L.last) {
        // Kasus 3: Hapus belakang
        L.last = P->prev;
        L.last->next = NULL;
    }
    else {
        // Kasus 4: Hapus tengah
        adrPengacara Predecessor = P->prev;
        adrPengacara Successor = P->next;
        Predecessor->next = Successor;
        Successor->prev = Predecessor;
    }

    // Putus pointer P sebelum dealokasi
    P->next = NULL;
    P->prev = NULL;
    delete P;

    cout << "Berhasil menghapus Pengacara ID: " << idPengacara << endl;
}

void showListPengacara(List L) {
    adrPengacara P = L.first;
    cout << "--- Daftar Pengacara (Parent DLL) ---" << endl;
    while (P != NULL) {
        cout << "- " << P->info.namaPengacara << " (" << P->info.idPengacara << ")" << endl;
        P = P->next;
    }
}
