#include "klien.h"

adrKlien createElmKlien(infotypeKlien data) {
    adrKlien C = new elmKlien;
    C->info = data;
    C->next = NULL;
    return C;
}

void showInfoKlien(adrKlien C) {
    if (C != NULL) {
        cout << "[KLIEN] ID: " << C->info.idKlien << " | Nama: " << C->info.namaKlien << " | Kasus: " << C->info.kasus << endl;
    }
}

void insertLastKlien(adrKlien &first, adrKlien P) {
    if (first == NULL) {
        first = P;
    } else {
        adrKlien q = first;
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = P;
    }
}

void deleteKlien(adrKlien &first, string idKlien, adrKlien &P) {
    P = NULL;
    if (first == NULL) return;

    if (first->info.idKlien == idKlien) {
        P = first;
        first = first->next;
        P->next = NULL;
    } else {
        adrKlien q = first;
        while (q->next != NULL && q->next->info.idKlien != idKlien) {
            q = q->next;
        }
        if (q->next != NULL) {
            P = q->next;
            q->next = P->next;
            P->next = NULL;
        }
    }
}

adrKlien findKlien(adrKlien first, string idKlien) {
    adrKlien q = first;
    while (q != NULL) {
        if (q->info.idKlien == idKlien) {
            return q;
        }
        q = q->next;
    }
    return NULL;
}

void showAllKlien(adrKlien first) {
    adrKlien q = first;
    while (q != NULL) {
        showInfoKlien(q);
        q = q->next;
    }
}

int countKlien(adrKlien first) {
    int jum = 0;
    adrKlien q = first;
    while (q != NULL) {
        jum++;
        q = q->next;
    }
    return jum;
}
