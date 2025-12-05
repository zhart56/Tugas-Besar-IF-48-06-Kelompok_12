#include "menu.h"

void runMenu(List &L) {
    int pilihan = -1;
    string idParent, idChild, idBaru;
    adrPengacara P;

    while (pilihan != 0) {
        cout << "\n\n";
        cout << "========================================" << endl;
        cout << "    APLIKASI MANAJEMEN FIRMA HUKUM      " << endl;
        cout << "    (Kelompok Null Objective Law)          " << endl;
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
        cout << "0.  KELUAR" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan Anda [0-9]: ";
        cin >> pilihan;
        cin.ignore();
        cout << endl;

        if (pilihan == 1) {
            cout << "--- TAMBAH PENGACARA ---" << endl;
            infotypePengacara dataP;
            cout << "ID Pengacara   : "; getline(cin, dataP.idPengacara);
            cout << "Nama Pengacara : "; getline(cin, dataP.namaPengacara);
            cout << "Nama Firma     : "; getline(cin, dataP.firma);

            insertLastPengacara(L, createElmPengacara(dataP));
            cout << ">> Sukses menambahkan pengacara." << endl;

        } else if (pilihan == 2) {
            cout << "--- TAMBAH KLIEN ---" << endl;
            showListPengacara(L);
            cout << "\nID Pengacara Tujuan: "; getline(cin, idParent);

            P = findPengacara(L, idParent);
            if (P != NULL) {
                infotypeKlien dataK;
                cout << "ID Klien    : "; getline(cin, dataK.idKlien);
                cout << "Nama Klien  : "; getline(cin, dataK.namaKlien);
                cout << "Kasus       : "; getline(cin, dataK.kasus);
                connectKlienToPengacara(L, idParent, createElmKlien(dataK));
                cout << ">> Sukses menambahkan klien." << endl;
            } else {
                cout << ">> Pengacara tidak ditemukan." << endl;
            }

        } else if (pilihan == 3) {
            showAllData(L);

        } else if (pilihan == 4) {
            cout << "ID Pengacara: "; getline(cin, idParent);
            P = findPengacara(L, idParent);
            if (P) cout << "Ditemukan: " << P->info.namaPengacara << endl;
            else cout << "Tidak ditemukan." << endl;

        } else if (pilihan == 5) {
            cout << "ID Klien: "; getline(cin, idChild);
            P = findParentOfKlien(L, idChild);
            if (P) cout << "Pengacara: " << P->info.namaPengacara << endl;
            else cout << "Tidak ditemukan." << endl;

        } else if (pilihan == 6) {
            showListPengacara(L);
            cout << "\nID Pengacara yg dihapus: "; getline(cin, idParent);
            deletePengacara(L, idParent);

        } else if (pilihan == 7) {
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
            cout << "ID Pengacara (Isi '-' jika ingin cek global): "; getline(cin, idParent);
            if (idParent != "-") {
                cout << "Jumlah Klien: " << countKlienByPengacara(L, idParent) << endl;
            }
            cout << "Total Pengacara Nganggur: " << countPengacaraTanpaKlien(L) << endl;

        } else if (pilihan == 9) {
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
