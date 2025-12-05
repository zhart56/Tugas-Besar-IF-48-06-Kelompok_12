#include "pengacara.h"

void createList(List &L) {
    L.first = NULL;
    L.last = NULL;
}

adrPengacara createElmPengacara(infotypePengacara data) {
    adrPengacara P = new elmPengacara;
    P->info = data;
    P->next = NULL;
    P->prev = NULL;
    P->nextKlien = NULL;
    return P;
}

void insertLastPengacara(List &L, adrPengacara P) {
    if (L.first == NULL) {
        L.first = P;
        L.last = P;
    } else {
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
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
    if (P == L.first && P == L.last) {
        L.first = NULL;
        L.last = NULL;
    }
    else if (P == L.first) {
        L.first = P->next;
        L.first->prev = NULL;
    }
    else if (P == L.last) {
        L.last = P->prev;
        L.last->next = NULL;
    }
    else {
        adrPengacara Predecessor = P->prev;
        adrPengacara Successor = P->next;
        Predecessor->next = Successor;
        Successor->prev = Predecessor;
    }
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
