#include "klien.h"

adrKlien createElmKlien(infotypeKlien data) {
    adrKlien C = new elmKlien;
    C->info = data;
    C->next = NULL;
    return C;
}

void showInfoKlien(adrKlien C) {
    cout << "   -> [KLIEN] ID: " << C->info.idKlien
         << " | Nama: " << C->info.namaKlien
         << " | Kasus: " << C->info.kasus << endl;
}
