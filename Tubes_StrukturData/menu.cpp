#include "menu.h"

void runMenu(List &L) {
    int pilihan = -1;
    string idParent, idChild, idBaru;
    adrPengacara P;

    while (pilihan != 0) {
        cout << "\n\n";
        cout << "========================================" << endl;
        cout << "    APLIKASI MANAJEMEN FIRMA HUKUM      " << endl;
        cout << "    (Kelompok Null Objective Law)       " << endl;
        cout << "========================================" << endl;
        cout << "1.  Tambah Pengacara (Parent)" << endl;
        cout << "2.  Tambah Klien & Hubungkan (Child)" << endl;
        cout << "3.  Tampilkan Semua Data" << endl;
        cout << "4.  Cari Pengacara (Berdasarkan ID)" << endl;
        cout << "5.  Cari Pengacara dari Klien Tertentu" << endl;
        cout << "6.  Hapus Pengacara" << endl;
        cout << "7.  Hapus Klien dari Pengacara" << endl;
        cout << "8.  Statistik & Laporan (TOP 1 & UNUSED)" << endl;
        cout << "9.  Pindah Pengacara (Edit Relasi)" << endl;
        cout << "0.  KELUAR" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan Anda [0-9]: ";
        cin >> pilihan;
        cin.ignore();
        cout << endl;

        if (pilihan == 1) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: INSERT ELEMENT PARENT" << endl;
            cout << "--- TAMBAH PENGACARA ---" << endl;

            infotypePengacara dataP;
            cout << "ID Pengacara   : "; getline(cin, dataP.idPengacara);

            if (findPengacara(L, dataP.idPengacara) != NULL) {
                cout << ">> ERROR: ID Pengacara '" << dataP.idPengacara << "' SUDAH ADA! Gagal Insert." << endl;
            } else {
                cout << "Nama Pengacara : "; getline(cin, dataP.namaPengacara);
                cout << "Nama Firma     : "; getline(cin, dataP.firma);

                insertLastPengacara(L, createElmPengacara(dataP));
                cout << ">> Sukses menambahkan pengacara." << endl;
            }

        } else if (pilihan == 2) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: INSERT ELEMENT CHILD & RELASI" << endl;
            cout << "--- TAMBAH KLIEN ---" << endl;
            showListPengacara(L);
            cout << "\nID Pengacara Tujuan: "; getline(cin, idParent);

            P = findPengacara(L, idParent);
            if (P != NULL) {
                infotypeKlien dataK;
                cout << "ID Klien    : "; getline(cin, dataK.idKlien);

                if (findKlienInPengacara(P, dataK.idKlien) != NULL) {
                     cout << ">> ERROR: ID Klien '" << dataK.idKlien << "' SUDAH ADA di pengacara ini! Gagal Insert." << endl;
                } else {
                    cout << "Nama Klien  : "; getline(cin, dataK.namaKlien);
                    cout << "Kasus       : "; getline(cin, dataK.kasus);
                    connectKlienToPengacara(L, idParent, createElmKlien(dataK));
                    cout << ">> Sukses menambahkan klien." << endl;
                }
            } else {
                cout << ">> Pengacara tidak ditemukan." << endl;
            }

        } else if (pilihan == 3) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: SHOW ALL DATA (PARENT & CHILD)" << endl;
            showAllData(L);

        } else if (pilihan == 4) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: FIND ELEMENT PARENT" << endl;
            cout << "ID Pengacara: "; getline(cin, idParent);
            P = findPengacara(L, idParent);
            if (P) cout << "Ditemukan: " << P->info.namaPengacara << " (" << P->info.idPengacara << ")" << endl;
            else cout << "Tidak ditemukan." << endl;

        } else if (pilihan == 5) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: FIND PARENT DARI CHILD TERTENTU" << endl;
            cout << "ID Klien: "; getline(cin, idChild);
            P = findParentOfKlien(L, idChild);
            if (P) cout << "Pengacara: " << P->info.namaPengacara << " (" << P->info.idPengacara << ")" << endl;
            else cout << "Tidak ditemukan." << endl;

        } else if (pilihan == 6) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: DELETE ELEMENT PARENT" << endl;
            showListPengacara(L);
            cout << "\nID Pengacara yg dihapus: "; getline(cin, idParent);
            deletePengacara(L, idParent);

        } else if (pilihan == 7) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: DELETE ELEMENT CHILD & RELASI" << endl;
            cout << "--- HAPUS KLIEN ---" << endl;
            showListPengacara(L);
            cout << "\nPilih ID Pengacara: "; getline(cin, idParent);
            P = findPengacara(L, idParent);
            if (P) {
                cout << "Daftar Klien " << P->info.namaPengacara << ":" << endl;
                adrKlien K = P->nextKlien;
                while(K){ cout << "- " << K->info.namaKlien << " (" << K->info.idKlien << ")" << endl; K=K->next; }

                cout << "\nID Klien yg dihapus: "; getline(cin, idChild);
                deleteKlienFromPengacara(L, idParent, idChild);
            } else {
                cout << "Pengacara tidak valid." << endl;
            }

        } else if (pilihan == 8) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: STATISTIK & LAPORAN" << endl;
            int totalPengacara = 0;
            int totalKlien = 0;
            int totalNganggur = 0;
            adrPengacara P = L.first;
            adrPengacara TopP = NULL;
            int maxKlien = -1;

            while (P != NULL) {
                totalPengacara++;
                int jumlahAnak = countKlienByPengacara(L, P->info.idPengacara);
                totalKlien += jumlahAnak;
                if (jumlahAnak == 0) {
                    totalNganggur++;
                }
                if (jumlahAnak > maxKlien) {
                    maxKlien = jumlahAnak;
                    TopP = P;
                }
                P = P->next;
            }

            cout << "----------------------------------------" << endl;
            cout << "LAPORAN FIRMA HUKUM" << endl;
            cout << "----------------------------------------" << endl;
            cout << "1. Total Pengacara Terdaftar : " << totalPengacara << " orang" << endl;
            cout << "2. Total Klien yang Ditangani: " << totalKlien << " orang" << endl;
            cout << "3. Pengacara 'Nganggur'      : " << totalNganggur << " orang" << endl;
            cout << "----------------------------------------" << endl;

            if (TopP != NULL && maxKlien > 0) {
                cout << "PENGACARA TERSIBUK (Most Clients): " << endl;
                cout << ">> Nama: " << TopP->info.namaPengacara << endl;
                cout << ">> Jml : " << maxKlien << " Klien" << endl;
            } else {
                cout << "Belum ada pengacara yang memiliki klien." << endl;
            }
            cout << "----------------------------------------" << endl;

        } else if (pilihan == 9) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: EDIT RELASI (PINDAH PARENT)" << endl;
            cout << "ID Klien           : "; getline(cin, idChild);
            cout << "ID Pengacara LAMA  : "; getline(cin, idParent);
            cout << "ID Pengacara BARU  : "; getline(cin, idBaru);
            pindahPengacara(L, idChild, idParent, idBaru);

        } else if (pilihan == 0) {
            cout << "Keluar..." << endl;
        } else {
            cout << "Pilihan salah." << endl;
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter untuk lanjut...";
            cin.get();
        }
    }
}
