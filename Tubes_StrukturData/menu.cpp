#include "menu.h"

/* ======================= MENU ADMIN ======================= */

void menuAdmin(List &L) {
    int pilihan = -1;

    while (pilihan != 0) {
        cout << "\n========================================" << endl;
        cout << "         DASHBOARD ADMIN FIRMA          " << endl;
        cout << "========================================" << endl;
        cout << "1. Tambah Pengacara" << endl;
        cout << "2. Tambah Klien" << endl;
        cout << "3. Hubungkan Klien ke Pengacara" << endl;
        cout << "4. Tampilkan Semua Data" << endl;
        cout << "5. Cari Pengacara (ID)" << endl;
        cout << "6. Cari Pengacara dari Klien" << endl;
        cout << "7. Hapus Pengacara" << endl;
        cout << "8. Hapus Klien dari Pengacara" << endl;
        cout << "9. Pindah Pengacara" << endl;
        cout << "0. Kembali" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        /* 1. TAMBAH PENGACARA */
        if (pilihan == 1) {
            infotypePengacara P;
            cout << "ID Pengacara   : ";
            getline(cin, P.idPengacara);

            if (findPengacara(L, P.idPengacara) != NULL) {
                cout << "ID sudah ada!" << endl;
            } else {
                cout << "Nama Pengacara : ";
                getline(cin, P.namaPengacara);
                cout << "Firma          : ";
                getline(cin, P.firma);
                insertLastPengacara(L, createElmPengacara(P));
                cout << "Pengacara berhasil ditambahkan." << endl;
            }
        }

        /* 2. TAMBAH KLIEN (BELUM TERHUBUNG) */
        else if (pilihan == 2) {
            infotypeKlien K;
            cout << "ID Klien   : ";
            getline(cin, K.idKlien);

            if (findParentOfKlien(L, K.idKlien) != NULL) {
                cout << "Klien sudah terdaftar!" << endl;
            } else {
                cout << "Nama Klien : ";
                getline(cin, K.namaKlien);
                cout << "Kasus      : ";
                getline(cin, K.kasus);
                cout << "Klien berhasil dibuat (belum terhubung)." << endl;
            }
        }

        /* 3. HUBUNGKAN KLIEN */
        else if (pilihan == 3) {
            string idKlien, idPengacara;
            cout << "ID Klien      : ";
            getline(cin, idKlien);
            cout << "ID Pengacara  : ";
            getline(cin, idPengacara);

            adrPengacara P = findPengacara(L, idPengacara);
            if (P != NULL) {
                infotypeKlien K;
                K.idKlien = idKlien;
                connectKlienToPengacara(L, idPengacara, createElmKlien(K));
            } else {
                cout << "Pengacara tidak ditemukan." << endl;
            }
        }

        /* 4. SHOW ALL */
        else if (pilihan == 4) {
            showAllData(L);
        }

        /* 5. CARI PENGACARA */
        else if (pilihan == 5) {
            string id;
            cout << "ID Pengacara: ";
            getline(cin, id);
            adrPengacara P = findPengacara(L, id);
            if (P != NULL)
                cout << "Nama: " << P->info.namaPengacara << endl;
            else
                cout << "Tidak ditemukan." << endl;
        }

        /* 6. CARI PENGACARA DARI KLIEN */
        else if (pilihan == 6) {
            string id;
            cout << "ID Klien: ";
            getline(cin, id);
            adrPengacara P = findParentOfKlien(L, id);
            if (P != NULL)
                cout << "Pengacara: " << P->info.namaPengacara << endl;
            else
                cout << "Tidak ditemukan." << endl;
        }

        /* 7. HAPUS PENGACARA */
        else if (pilihan == 7) {
            string id;
            cout << "ID Pengacara: ";
            getline(cin, id);
            deletePengacara(L, id);
        }

        /* 8. HAPUS KLIEN */
        else if (pilihan == 8) {
            string idP, idK;
            cout << "ID Pengacara: ";
            getline(cin, idP);
            cout << "ID Klien    : ";
            getline(cin, idK);
            deleteKlienFromPengacara(L, idP, idK);
        }

        /* 9. PINDAH */
        else if (pilihan == 9) {
            string idK, lama, baru;
            cout << "ID Klien        : ";
            getline(cin, idK);
            cout << "Pengacara Lama  : ";
            getline(cin, lama);
            cout << "Pengacara Baru  : ";
            getline(cin, baru);
            pindahPengacara(L, idK, lama, baru);
        }

        if (pilihan != 0) {
            cout << "Tekan Enter...";
            cin.get();
        }
    }
}

void menuUserPengacara(List &L) {
    string myID;
    bool loginValid = true;

    cout << "\n--- LOGIN PENGACARA ---" << endl;
    cout << "Masukkan ID Pengacara Anda: ";
    getline(cin, myID);

    if (myID == "") {
        cout << ">> ERROR: ID tidak boleh kosong!" << endl;
        loginValid = false;
    }

    adrPengacara P = NULL;
    if (loginValid) {
        P = findPengacara(L, myID);
        if (P == NULL) {
            cout << ">> Error: ID Pengacara tidak ditemukan!" << endl;
            loginValid = false;
        }
    }

    int pilihan = -1;
    while (loginValid && pilihan != 0) {
        cout << "\n========================================" << endl;
        cout << "Halo, " << P->info.namaPengacara
             << " (" << P->info.firma << ")" << endl;
        cout << "========================================" << endl;
        cout << "1. Lihat Daftar Klien Saya" << endl;
        cout << "2. Terima Klien Baru" << endl;
        cout << "3. Hapus Klien" << endl;
        cout << "4. Cek Total Klien" << endl;
        cout << "0. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            adrKlien K = P->nextKlien;
            if (K == NULL) {
                cout << "(Belum ada klien)" << endl;
            }
            while (K != NULL) {
                cout << "- " << K->info.namaKlien
                     << " (ID: " << K->info.idKlien << ")"
                     << " | Kasus: " << K->info.kasus << endl;
                K = K->next;
            }

        } else if (pilihan == 2) {
            infotypeKlien dataK;
            cout << "ID Klien   : ";
            getline(cin, dataK.idKlien);

            if (dataK.idKlien == "") {
                cout << ">> ERROR: ID Klien tidak boleh kosong!" << endl;
            } else if (findParentOfKlien(L, dataK.idKlien) != NULL) {
                cout << ">> ERROR: Klien sudah memiliki pengacara!" << endl;
            } else {
                cout << "Nama Klien : ";
                getline(cin, dataK.namaKlien);
                cout << "Kasus      : ";
                getline(cin, dataK.kasus);
                connectKlienToPengacara(L, myID, createElmKlien(dataK));
                cout << ">> Klien berhasil ditambahkan." << endl;
            }

        } else if (pilihan == 3) {
            string idK;
            cout << "ID Klien yg dihapus: ";
            getline(cin, idK);

            if (idK == "") {
                cout << ">> ERROR: ID tidak boleh kosong!" << endl;
            } else {
                deleteKlienFromPengacara(L, myID, idK);
            }

        } else if (pilihan == 4) {
            cout << "Total Klien: "
                 << countKlienByPengacara(L, myID)
                 << " orang" << endl;
        }

        if (pilihan != 0) {
            cout << "Tekan Enter...";
            cin.get();
        }
    }
}

void menuUserKlien(List &L) {
    string myID;
    bool loginValid = true;

    cout << "\n--- LOGIN KLIEN ---" << endl;
    cout << "Masukkan ID Klien Anda: ";
    getline(cin, myID);

    if (myID == "") {
        cout << ">> ERROR: ID tidak boleh kosong!" << endl;
        loginValid = false;
    }

    adrPengacara P = NULL;
    adrKlien K = NULL;

    if (loginValid) {
        P = findParentOfKlien(L, myID);
        if (P != NULL) {
            K = findKlienInPengacara(P, myID);
        }
        if (P == NULL || K == NULL) {
            cout << ">> Error: Klien tidak terdaftar!" << endl;
            loginValid = false;
        }
    }

    int pilihan = -1;
    while (loginValid && pilihan != 0) {
        cout << "\n========================================" << endl;
        cout << "Halo, " << K->info.namaKlien
             << " (ID: " << K->info.idKlien << ")" << endl;
        cout << "========================================" << endl;
        cout << "1. Lihat Profil Pengacara" << endl;
        cout << "2. Lihat Kasus Saya" << endl;
        cout << "3. Pindah Pengacara" << endl;
        cout << "0. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "Nama  : " << P->info.namaPengacara << endl;
            cout << "ID    : " << P->info.idPengacara << endl;
            cout << "Firma : " << P->info.firma << endl;

        } else if (pilihan == 2) {
            cout << "Kasus: " << K->info.kasus << endl;

        } else if (pilihan == 3) {
            string idBaru;
            showListPengacara(L);
            cout << "ID Pengacara Baru: ";
            getline(cin, idBaru);

            if (idBaru == "") {
                cout << ">> ERROR: ID tidak boleh kosong!" << endl;
            } else if (findPengacara(L, idBaru) == NULL) {
                cout << ">> ERROR: Pengacara tidak ditemukan!" << endl;
            } else {
                pindahPengacara(L, myID, P->info.idPengacara, idBaru);
                P = findParentOfKlien(L, myID);
                K = findKlienInPengacara(P, myID);
                cout << ">> Berhasil pindah pengacara." << endl;
            }
        }

        if (pilihan != 0) {
            cout << "Tekan Enter...";
            cin.get();
        }
    }
}

void runMenu(List &L) {
    int pilih = -1;

    while (pilih != 0) {
        cout << "\n========================================" << endl;
        cout << "    APLIKASI MANAJEMEN FIRMA HUKUM      " << endl;
        cout << "========================================" << endl;
        cout << "1. ADMIN" << endl;
        cout << "2. USER" << endl;
        cout << "0. KELUAR" << endl;
        cout << "Pilihan: ";
        cin >> pilih;
        cin.ignore();

        if (pilih == 1) menuAdmin(L);
        else if (pilih == 2) {
            int u;
            cout << "1. Pengacara\n2. Klien\nPilihan: ";
            cin >> u;
            cin.ignore();
            if (u == 1) menuUserPengacara(L);
            if (u == 2) menuUserKlien(L);
        }
    }
}
