#include <iostream>
#include "pengacara.h"
#include "klien.h"
#include "relasi.h"

using namespace std;

int main() {

    List L;
    createList(L);


    int pilihan = -1;
    string idParent, idChild, nama, firma, kasus, idBaru;
    adrPengacara P;
    adrKlien C;

    cout << "=== APLIKASI MANAJEMEN FIRMA HUKUM (Null Objective Law ) ===" << endl;

    while (pilihan != 0) {
        cout << "\n================ MENU UTAMA ================" << endl;
        cout << "1. Tambah Pengacara (Parent)" << endl;
        cout << "2. Tambah Klien & Hubungkan (Child)" << endl;
        cout << "3. Tampilkan Semua Data" << endl;
        cout << "4. Cari Pengacara dari Klien Tertentu" << endl;
        cout << "5. Hapus Klien (Dari Pengacara Tertentu)" << endl;
        cout << "6. Hapus Pengacara (Beserta Kliennya)" << endl;
        cout << "7. Lihat Statistik (Count)" << endl;
        cout << "8. Pindahkan Klien (Edit Relasi)" << endl;
        cout << "0. Keluar" << endl;
        cout << "============================================" << endl;
        cout << "Pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();
        cout << endl;

        if (pilihan == 1) {
            cout << "--- TAMBAH PENGACARA ---" << endl;
            infotypePengacara dataP;
            cout << "ID Pengacara   : "; getline(cin, dataP.idPengacara);
            cout << "Nama Pengacara : "; getline(cin, dataP.namaPengacara);
            cout << "Nama Firma     : "; getline(cin, dataP.firma);

            P = createElmPengacara(dataP);
            insertLastPengacara(L, P);
            cout << ">> Sukses tambah pengacara." << endl;

        } else if (pilihan == 2) {
            cout << "--- TAMBAH KLIEN ---" << endl;
            showListPengacara(L);

            cout << "\nMasukkan ID Pengacara tujuan: ";
            getline(cin, idParent);

            P = findPengacara(L, idParent);
            if (P == NULL) {
                cout << ">> Error: Pengacara tidak ditemukan." << endl;
            } else {
                infotypeKlien dataK;
                cout << "ID Klien       : "; getline(cin, dataK.idKlien);
                cout << "Nama Klien     : "; getline(cin, dataK.namaKlien);
                cout << "Jenis Kasus    : "; getline(cin, dataK.kasus);

                C = createElmKlien(dataK);
                connectKlienToPengacara(L, idParent, C);
                cout << ">> Sukses tambah klien ke " << P->info.namaPengacara << "." << endl;
            }

        } else if (pilihan == 3) {
            cout << "--- DATA LENGKAP ---" << endl;
            showAllData(L);

        } else if (pilihan == 4) {
            cout << "--- CARI PENGACARA DARI KLIEN ---" << endl;
            cout << "Masukkan ID Klien: ";
            getline(cin, idChild);

            P = findParentOfKlien(L, idChild);
            if (P != NULL) {
                cout << ">> Klien tersebut ditangani oleh: " << P->info.namaPengacara << endl;
            } else {
                cout << ">> Klien tidak ditemukan/tidak punya pengacara." << endl;
            }

        } else if (pilihan == 5) {
            cout << "--- HAPUS KLIEN ---" << endl;

            cout << "[Langkah 1] Pilih Pengacara:" << endl;
            showListPengacara(L);
            cout << "\nMasukkan ID Pengacara : "; getline(cin, idParent);

            P = findPengacara(L, idParent);
            if (P != NULL) {
                cout << "\n[Langkah 2] Daftar Klien dari " << P->info.namaPengacara << ":" << endl;
                adrKlien K = P->nextKlien;
                if (K == NULL) {
                    cout << "   (Tidak ada klien untuk dihapus)" << endl;
                } else {

                    while (K != NULL) {
                        cout << "   -> ID: " << K->info.idKlien << " | Nama: " << K->info.namaKlien << endl;
                        K = K->next;
                    }

                    cout << "\nMasukkan ID Klien yang mau dihapus: "; getline(cin, idChild);
                    deleteKlienFromPengacara(L, idParent, idChild);
                }
            } else {
                cout << ">> ID Pengacara tidak ditemukan." << endl;
            }


        } else if (pilihan == 6) {
            cout << "--- HAPUS PENGACARA ---" << endl;
            cout << "Daftar Pengacara Saat Ini:" << endl;
            showListPengacara(L);

            cout << "\nMasukkan ID Pengacara yang akan dihapus: ";
            getline(cin, idParent);

            deletePengacara(L, idParent);

        } else if (pilihan == 7) {
            cout << "--- STATISTIK ---" << endl;
            showListPengacara(L);
            cout << "\nPilih ID Pengacara: "; getline(cin, idParent);
            cout << ">> Jumlah Klien: " << countKlienByPengacara(L, idParent) << endl;
            cout << ">> Total Pengacara Nganggur: " << countPengacaraTanpaKlien(L) << endl;

        } else if (pilihan == 8) {
            cout << "--- PINDAH PENGACARA ---" << endl;
            cout << "Masukkan ID Klien           : "; getline(cin, idChild);
            cout << "Masukkan ID Pengacara LAMA  : "; getline(cin, idParent);
            cout << "Masukkan ID Pengacara BARU  : "; getline(cin, idBaru);
            pindahPengacara(L, idChild, idParent, idBaru);

        } else if (pilihan == 0) {
            cout << "Keluar dari program..." << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }

        cout << "\n--------------------------------------------" << endl;
    }

    return 0;
}
