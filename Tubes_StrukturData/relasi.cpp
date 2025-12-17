#include "relasi.h"

void connectKlienToPengacara(List &L, string idPengacara, adrKlien C) {
    if (C == NULL) {
        cout << "Klien tidak valid." << endl;
    } else if (findParentOfKlien(L, C->info.idKlien) != NULL) {
        cout << "Gagal Connect: Klien sudah memiliki pengacara." << endl;
    } else {
        adrPengacara P = findPengacara(L, idPengacara);
        if (P != NULL) {
            C->next = P->nextKlien;
            P->nextKlien = C;
            cout << "Berhasil menghubungkan klien ke pengacara." << endl;
        } else {
            cout << "Gagal Connect: Pengacara tidak ditemukan." << endl;
        }
    }
}


void showAllData(List L) {
    adrPengacara P = L.first;

    while (P != NULL) {
        cout << "[PENGACARA] ID: " << P->info.idPengacara
             << " | Nama: " << P->info.namaPengacara
             << " | Firma: " << P->info.firma << endl;

        adrKlien K = P->nextKlien;

        if (K == NULL) {
            cout << "   (Belum mempunyai klien)" << endl;
        } else {
            while (K != NULL) {
                cout << " [KLIEN] ID: " << K->info.idKlien
                     << " | Nama: " << K->info.namaKlien
                     << " | Kasus: " << K->info.kasus << endl;
                K = K->next;
            }
        }

        cout << "========================================" << endl;
        P = P->next;
    }
}

adrKlien findKlienInPengacara(adrPengacara P, string idKlien) {
    if (P == NULL) return NULL;
    adrKlien C = P->nextKlien;
    while (C != NULL) {
        if (C->info.idKlien == idKlien) {
            return C;   // langsung berhenti
        }
        C = C->next;
    }
    return NULL;
}

void deleteKlienFromPengacara(List &L, string idPengacara, string idKlien) {
    adrPengacara P = findPengacara(L, idPengacara);

    if (P == NULL) {
        cout << "Pengacara tidak ditemukan." << endl;
    } else {
        adrKlien C = P->nextKlien;
        adrKlien Prev = NULL;

        while (C != NULL && C->info.idKlien != idKlien) {
            Prev = C;
            C = C->next;
        }

        if (C == NULL) {
            cout << "Klien tidak ditemukan." << endl;
        } else {
            if (Prev == NULL) {
                P->nextKlien = C->next;
            } else {
                Prev->next = C->next;
            }
            C->next = NULL;
            delete C;
            cout << "Berhasil menghapus Klien " << idKlien << endl;
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
    } else {
        adrKlien C = P_Lama->nextKlien;
        adrKlien Prev = NULL;

        while (C != NULL && C->info.idKlien != idKlien) {
            Prev = C;
            C = C->next;
        }

        if (C == NULL) {
            cout << "Gagal Pindah: Klien tidak ditemukan." << endl;
        } else {
            if (Prev == NULL) {
                P_Lama->nextKlien = C->next;
            } else {
                Prev->next = C->next;
            }

            C->next = P_Baru->nextKlien;
            P_Baru->nextKlien = C;

            cout << "Sukses memindahkan Klien "
                 << C->info.namaKlien
                 << " ke "
                 << P_Baru->info.namaPengacara << endl;
        }
    }
}
