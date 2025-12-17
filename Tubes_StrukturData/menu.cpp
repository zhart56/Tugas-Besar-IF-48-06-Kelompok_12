#include "menu.h"

void menuAdmin(List &L) {
    int pilihan = -1;
    string idParent, idChild, idBaru;
    adrPengacara P;

    while (pilihan != 0) {
        cout << "\n\n";
        cout << "========================================" << endl;
        cout << "         DASHBOARD ADMIN FIRMA          " << endl;
        cout << "========================================" << endl;
        cout << "1.  Tambah Pengacara (Parent)" << endl;
        cout << "2.  Tambah Klien & Hubungkan (Child)" << endl;
        cout << "3.  Tampilkan Semua Data" << endl;
        cout << "4.  Cari Pengacara (Berdasarkan ID)" << endl;
        cout << "5.  Cari Pengacara dari Klien Tertentu" << endl;
        cout << "6.  Hapus Pengacara" << endl;
        cout << "7.  Hapus Klien dari Pengacara" << endl;
        cout << "8.  Statistik & Laporan" << endl;
        cout << "9.  Pindah Pengacara (Edit Relasi)" << endl;
        cout << "0.  KEMBALI KE MENU UTAMA" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan Admin [0-9]: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            infotypePengacara dataP;
            cout << "\nID Pengacara   : ";
            getline(cin, dataP.idPengacara);

            if (dataP.idPengacara == "") {
                cout << ">> ERROR: ID tidak boleh kosong!" << endl;
            } else if (findPengacara(L, dataP.idPengacara) != NULL) {
                cout << ">> ERROR: ID Pengacara sudah ada!" << endl;
            } else {
                cout << "Nama Pengacara : ";
                getline(cin, dataP.namaPengacara);
                cout << "Nama Firma     : ";
                getline(cin, dataP.firma);
                insertLastPengacara(L, createElmPengacara(dataP));
                cout << ">> Sukses menambahkan pengacara." << endl;
            }

        } else if (pilihan == 2) {
            showListPengacara(L);
            cout << "\nID Pengacara Tujuan: ";
            getline(cin, idParent);

            P = findPengacara(L, idParent);
            if (P != NULL) {
                infotypeKlien dataK;
                cout << "ID Klien    : ";
                getline(cin, dataK.idKlien);

                if (dataK.idKlien == "") {
                    cout << ">> ERROR: ID Klien tidak boleh kosong!" << endl;
                } else if (findParentOfKlien(L, dataK.idKlien) != NULL) {
                    cout << ">> ERROR: Klien sudah punya pengacara!" << endl;
                } else {
                    cout << "Nama Klien  : ";
                    getline(cin, dataK.namaKlien);
                    cout << "Kasus       : ";
                    getline(cin, dataK.kasus);
                    connectKlienToPengacara(L, idParent, createElmKlien(dataK));
                }
            } else {
                cout << ">> Pengacara tidak ditemukan." << endl;
            }

        } else if (pilihan == 3) {
            showAllData(L);

        } else if (pilihan == 4) {
            cout << "\nID Pengacara: ";
            getline(cin, idParent);
            P = findPengacara(L, idParent);
            if (P != NULL)
                cout << "Ditemukan: " << P->info.namaPengacara << endl;
            else
                cout << "Tidak ditemukan." << endl;

        } else if (pilihan == 5) {
            cout << "\nID Klien: ";
            getline(cin, idChild);
            P = findParentOfKlien(L, idChild);
            if (P != NULL)
                cout << "Pengacara: " << P->info.namaPengacara << endl;
            else
                cout << "Tidak ditemukan." << endl;

        } else if (pilihan == 6) {
            showListPengacara(L);
            cout << "\nID Pengacara yg dihapus: ";
            getline(cin, idParent);
            deletePengacara(L, idParent);

        } else if (pilihan == 7) {
            showListPengacara(L);
            cout << "\nPilih ID Pengacara: ";
            getline(cin, idParent);
            P = findPengacara(L, idParent);

            if (P != NULL) {
                adrKlien K = P->nextKlien;
                while (K != NULL) {
                    cout << "- " << K->info.namaKlien << endl;
                    K = K->next;
                }
                cout << "ID Klien yg dihapus: ";
                getline(cin, idChild);
                deleteKlienFromPengacara(L, idParent, idChild);
            } else {
                cout << "Pengacara tidak valid." << endl;
            }

        } else if (pilihan == 8) {
            int totalPengacara = 0, totalKlien = 0;
            adrPengacara cur = L.first, TopP = NULL;
            int maxKlien = -1;

            while (cur != NULL) {
                totalPengacara++;
                int j = countKlienByPengacara(L, cur->info.idPengacara);
                totalKlien += j;
                if (j > maxKlien) {
                    maxKlien = j;
                    TopP = cur;
                }
                cur = cur->next;
            }

            cout << "\nTotal Pengacara : " << totalPengacara << endl;
            cout << "Total Klien     : " << totalKlien << endl;
            if (TopP != NULL)
                cout << "TERSIBUK        : " << TopP->info.namaPengacara
                     << " (" << maxKlien << " klien)" << endl;

        } else if (pilihan == 9) {
            cout << "\nID Klien          : ";
            getline(cin, idChild);
            cout << "ID Pengacara Lama : ";
            getline(cin, idParent);
            cout << "ID Pengacara Baru : ";
            getline(cin, idBaru);
            pindahPengacara(L, idChild, idParent, idBaru);
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter lanjut...";
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

    adrPengacara P = findPengacara(L, myID);
    if (P == NULL) {
        cout << ">> Error: ID Pengacara tidak ditemukan!" << endl;
        cout << "Tekan Enter kembali...";
        cin.get();
        loginValid = false;
    }

    int pilihan = -1;
    while (loginValid && pilihan != 0) {
        cout << "\n\n";
        cout << "========================================" << endl;
        cout << "Halo, " << P->info.namaPengacara << " (" << P->info.firma << ")" << endl;
        cout << "========================================" << endl;
        cout << "1. Lihat Daftar Klien Saya" << endl;
        cout << "2. Terima Klien Baru (Insert)" << endl;
        cout << "3. Hapus Klien (Putus Kontrak)" << endl;
        cout << "4. Cek Total Klien Saya" << endl;
        cout << "0. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "\nDAFTAR KLIEN ANDA:" << endl;
            adrKlien K = P->nextKlien;
            if (K == NULL) cout << "(Anda belum memiliki klien)" << endl;
            while (K != NULL) {
                cout << "- " << K->info.namaKlien
                     << " (ID: " << K->info.idKlien
                     << ") | Kasus: " << K->info.kasus << endl;
                K = K->next;
            }

        } else if (pilihan == 2) {
            infotypeKlien dataK;
            cout << "\n--- TERIMA KLIEN BARU ---" << endl;
            cout << "ID Klien    : ";
            getline(cin, dataK.idKlien);

            if (findParentOfKlien(L, dataK.idKlien) != NULL) {
                cout << ">> ERROR: Klien sudah memiliki pengacara!" << endl;
            } else {
                cout << "Nama Klien  : ";
                getline(cin, dataK.namaKlien);
                cout << "Kasus       : ";
                getline(cin, dataK.kasus);
                connectKlienToPengacara(L, myID, createElmKlien(dataK));
                cout << ">> Sukses menerima klien baru." << endl;
            }

        } else if (pilihan == 3) {
            string idK;
            cout << "\n--- HAPUS KLIEN ---" << endl;
            cout << "Masukkan ID Klien yg akan dihapus: ";
            getline(cin, idK);
            deleteKlienFromPengacara(L, myID, idK);

        } else if (pilihan == 4) {
            int jml = countKlienByPengacara(L, myID);
            cout << "\nTotal Klien yang Anda tangani: "
                 << jml << " orang." << endl;

        } else if (pilihan == 0) {
            cout << "Logout..." << endl;
        } else {
            cout << "Pilihan salah." << endl;
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter lanjut...";
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

    adrPengacara P = findParentOfKlien(L, myID);
    adrKlien K = NULL;

    if (P != NULL) {
        K = findKlienInPengacara(P, myID);
    }

    if (P == NULL || K == NULL) {
        cout << ">> Error: ID Klien tidak ditemukan atau belum terdaftar!" << endl;
        cout << "Tekan Enter kembali...";
        cin.get();
        loginValid = false;
    }

    int pilihan = -1;
    while (loginValid && pilihan != 0) {
        cout << "\n\n";
        cout << "========================================" << endl;
        cout << "Halo, " << K->info.namaKlien
             << " (ID: " << K->info.idKlien << ")" << endl;
        cout << "========================================" << endl;
        cout << "1. Lihat Profil Pengacara Saya" << endl;
        cout << "2. Lihat Detail Kasus Saya" << endl;
        cout << "3. Pindah Pengacara (Cari Pengacara Baru)" << endl;
        cout << "0. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            cout << "\nPENGACARA ANDA:" << endl;
            cout << "Nama  : " << P->info.namaPengacara << endl;
            cout << "ID    : " << P->info.idPengacara << endl;
            cout << "Firma : " << P->info.firma << endl;

        } else if (pilihan == 2) {
            cout << "\nDETAIL KASUS:" << endl;
            cout << "Jenis Kasus: " << K->info.kasus << endl;

        } else if (pilihan == 3) {
            cout << "\n--- PINDAH PENGACARA ---" << endl;
            cout << "Daftar Pengacara Tersedia:" << endl;
            showListPengacara(L);

            string idBaru;
            cout << "\nMasukkan ID Pengacara Baru yang diinginkan: ";
            getline(cin, idBaru);

            if (findPengacara(L, idBaru) != NULL) {
                pindahPengacara(L, myID, P->info.idPengacara, idBaru);
                P = findParentOfKlien(L, myID);
                K = findKlienInPengacara(P, myID);
            } else {
                cout << ">> Error: ID Pengacara Baru tidak ditemukan." << endl;
            }

        } else if (pilihan == 0) {
            cout << "Logout..." << endl;

        } else {
            cout << "Pilihan salah." << endl;
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter lanjut...";
            cin.get();
        }
    }
}
