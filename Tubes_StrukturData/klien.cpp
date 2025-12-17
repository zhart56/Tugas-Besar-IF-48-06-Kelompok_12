#include "klien.h"

adrKlien createElmKlien(infotypeKlien data) {
    adrKlien C = new elmKlien;
    C->info = data;
    C->next = NULL;
    return C;
}

adrKlien findKlien(adrKlien first, string idKlien) {
    adrKlien C = first;
    while (C != NULL) {
        if (C->info.idKlien == idKlien) {
            return C;
        }
        C = C->next;
    }
    return NULL;
}
