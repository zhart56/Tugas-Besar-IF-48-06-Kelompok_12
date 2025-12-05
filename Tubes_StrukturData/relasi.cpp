#include "relasi.h"

void connectKlienToPengacara(List &L, string idPengacara, adrKlien C) {
    adrPengacara P = findPengacara(L, idPengacara);
    if (P != NULL) {

        C->next = P->nextKlien;
        P->nextKlien = C;
    } else {
        cout << "Gagal Connect: Pengacara tidak ditemukan." << endl;
    }
}

void showAllData(List L) {
    adrPengacara P = L.first;
    if (P == NULL) {
        cout << "List Kosong." << endl;
        return;
    }

    while (P != NULL) {
        cout << "========================================" << endl;
        cout << "[PENGACARA] " << P->info.namaPengacara
             << " (" << P->info.firma << ")" << endl;

        adrKlien C = P->nextKlien;
        if (C == NULL) {
            cout << "   (Tidak ada klien)" << endl;
        } else {
            while (C != NULL) {
                showInfoKlien(C);
                C = C->next;
            }
        }
        P = P->next;
    }
    cout << "========================================" << endl;
}

adrKlien findKlienInPengacara(adrPengacara P, string idKlien) {
    if (P == NULL) return NULL;
    adrKlien C = P->nextKlien;
    while (C != NULL) {
        if (C->info.idKlien == idKlien) {
            return C;
        }
        C = C->next;
    }
    return NULL;
}

void deleteKlienFromPengacara(List &L, string idPengacara, string idKlien) {
    adrPengacara P = findPengacara(L, idPengacara);
    if (P != NULL) {
        adrKlien C = P->nextKlien;
        adrKlien Prev = NULL;

        while (C != NULL && C->info.idKlien != idKlien) {
            Prev = C;
            C = C->next;
        }

        if (C != NULL) {
            if (Prev == NULL) {
                P->nextKlien = C->next;
            } else {
                Prev->next = C->next;
            }
            delete C;
            cout << "Berhasil menghapus Klien " << idKlien << endl;
        } else {
            cout << "Klien tidak ditemukan." << endl;
        }
    }
}

adrPengacara findParentOfKlien(List L, string idKlien) {
    adrPengacara P = L.first;
    while (P != NULL) {
        if (findKlienInPengacara(P, idKlien) != NULL) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

int countKlienByPengacara(List L, string idPengacara) {
    adrPengacara P = findPengacara(L, idPengacara);
    int count = 0;
    if (P != NULL) {
        adrKlien C = P->nextKlien;
        while (C != NULL) {
            count++;
            C = C->next;
        }
    }
    return count;
}

int countPengacaraTanpaKlien(List L) {
    int count = 0;
    adrPengacara P = L.first;
    while (P != NULL) {
        if (P->nextKlien == NULL) {
            count++;
        }
        P = P->next;
    }
    return count;
}

void pindahPengacara(List &L, string idKlien, string idPengacaraLama, string idPengacaraBaru) {
    adrPengacara P_Lama = findPengacara(L, idPengacaraLama);
    adrPengacara P_Baru = findPengacara(L, idPengacaraBaru);

    if (P_Lama == NULL || P_Baru == NULL) {
        cout << "Gagal Pindah: Data pengacara tidak valid." << endl;
        return;
    }
    adrKlien C = P_Lama->nextKlien;
    adrKlien Prev = NULL;

    while (C != NULL && C->info.idKlien != idKlien) {
        Prev = C;
        C = C->next;
    }

    if (C == NULL) {
        cout << "Gagal Pindah: Klien tidak ditemukan di pengacara lama." << endl;
        return;
    }

    if (Prev == NULL) {
        P_Lama->nextKlien = C->next;
    } else {
        Prev->next = C->next;
    }

    C->next = P_Baru->nextKlien;
    P_Baru->nextKlien = C;

    cout << "Sukses memindahkan Klien " << C->info.namaKlien << " ke " << P_Baru->info.namaPengacara << endl;
}
