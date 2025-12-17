#include "menu.h"

// MENU UNTUK ADMIN (AKSES PENUH/FULL CONTROL)
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
            cout << ">>> [SYSTEM] Menjalankan Fungsi: SHOW ALL DATA" << endl;
            showAllData(L);

        } else if (pilihan == 4) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: FIND PARENT" << endl;
            cout << "ID Pengacara: "; getline(cin, idParent);
            P = findPengacara(L, idParent);
            if (P) cout << "Ditemukan: " << P->info.namaPengacara << " (" << P->info.idPengacara << ")" << endl;
            else cout << "Tidak ditemukan." << endl;

        } else if (pilihan == 5) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: FIND PARENT OF CHILD" << endl;
            cout << "ID Klien: "; getline(cin, idChild);
            P = findParentOfKlien(L, idChild);
            if (P) cout << "Pengacara: " << P->info.namaPengacara << " (" << P->info.idPengacara << ")" << endl;
            else cout << "Tidak ditemukan." << endl;

        } else if (pilihan == 6) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: DELETE PARENT" << endl;
            showListPengacara(L);
            cout << "\nID Pengacara yg dihapus: "; getline(cin, idParent);
            deletePengacara(L, idParent);

        } else if (pilihan == 7) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: DELETE CHILD" << endl;
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
            cout << ">>> [SYSTEM] Menjalankan Fungsi: STATISTIK" << endl;
            int totalPengacara = 0;
            int totalKlien = 0;
            int totalNganggur = 0;
            adrPengacara cur = L.first;
            adrPengacara TopP = NULL;
            int maxKlien = -1;

            while (cur != NULL) {
                totalPengacara++;
                int jumlahAnak = countKlienByPengacara(L, cur->info.idPengacara);
                totalKlien += jumlahAnak;
                if (jumlahAnak == 0) totalNganggur++;
                if (jumlahAnak > maxKlien) {
                    maxKlien = jumlahAnak;
                    TopP = cur;
                }
                cur = cur->next;
            }

            cout << "----------------------------------------" << endl;
            cout << "LAPORAN FIRMA HUKUM" << endl;
            cout << "1. Total Pengacara : " << totalPengacara << " orang" << endl;
            cout << "2. Total Klien     : " << totalKlien << " orang" << endl;
            cout << "3. Pengacara Kosong: " << totalNganggur << " orang" << endl;
            if (TopP != NULL && maxKlien > 0) {
                cout << "TERSIBUK: " << TopP->info.namaPengacara << " (" << maxKlien << " Klien)" << endl;
            }
            cout << "----------------------------------------" << endl;

        } else if (pilihan == 9) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: EDIT RELASI" << endl;
            cout << "ID Klien           : "; getline(cin, idChild);
            cout << "ID Pengacara LAMA  : "; getline(cin, idParent);
            cout << "ID Pengacara BARU  : "; getline(cin, idBaru);
            pindahPengacara(L, idChild, idParent, idBaru);

        } else if (pilihan == 0) {
            cout << "Logout Admin..." << endl;
        } else {
            cout << "Pilihan salah." << endl;
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter lanjut...";
            cin.get();
        }
    }
}

// MENU KHUSUS USER: PENGACARA
void menuUserPengacara(List &L) {
    string myID;
    cout << "\n--- LOGIN PENGACARA ---" << endl;
    cout << "Masukkan ID Pengacara Anda: "; getline(cin, myID);

    adrPengacara P = findPengacara(L, myID);
    if (P == NULL) {
        cout << ">> Error: ID Pengacara tidak ditemukan!" << endl;
        cout << "Tekan Enter kembali..."; cin.get();
        return;
    }

    int pilihan = -1;
    while (pilihan != 0) {
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
        cout << "Pilihan: "; cin >> pilihan; cin.ignore();

        if (pilihan == 1) {
            cout << "\nDAFTAR KLIEN ANDA:" << endl;
            adrKlien K = P->nextKlien;
            if (K == NULL) cout << "(Anda belum memiliki klien)" << endl;
            while (K != NULL) {
                cout << "- " << K->info.namaKlien << " (ID: " << K->info.idKlien << ") | Kasus: " << K->info.kasus << endl;
                K = K->next;
            }
        } else if (pilihan == 2) {
            infotypeKlien dataK;
            cout << "\n--- TERIMA KLIEN BARU ---" << endl;
            cout << "ID Klien    : "; getline(cin, dataK.idKlien);
            if (findKlienInPengacara(P, dataK.idKlien) != NULL) {
                 cout << ">> ERROR: ID Klien SUDAH ADA!" << endl;
            } else {
                cout << "Nama Klien  : "; getline(cin, dataK.namaKlien);
                cout << "Kasus       : "; getline(cin, dataK.kasus);
                connectKlienToPengacara(L, myID, createElmKlien(dataK));
                cout << ">> Sukses menerima klien baru." << endl;
            }
        } else if (pilihan == 3) {
            string idK;
            cout << "\n--- HAPUS KLIEN ---" << endl;
            cout << "Masukkan ID Klien yg akan dihapus: "; getline(cin, idK);
            deleteKlienFromPengacara(L, myID, idK);
        } else if (pilihan == 4) {
            int jml = countKlienByPengacara(L, myID);
            cout << "\nTotal Klien yang Anda tangani: " << jml << " orang." << endl;
        } else if (pilihan == 0) {
            cout << "Logout..." << endl;
        } else {
            cout << "Pilihan salah." << endl;
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter lanjut..."; cin.get();
        }
    }
}

// MENU KHUSUS USER: KLIEN
void menuUserKlien(List &L) {
    string myID;
    cout << "\n--- LOGIN KLIEN ---" << endl;
    cout << "Masukkan ID Klien Anda: "; getline(cin, myID);
    adrPengacara P = findParentOfKlien(L, myID);
    adrKlien K = NULL;
    if (P != NULL) {
        K = findKlienInPengacara(P, myID);
    } else {
        // Jika belum punya pengacara, kita tidak bisa login sebagai klien yang sudah terdaftar
        // Kecuali kita mau membuat fitur "Register Klien Baru" di sini.
        // Tapi untuk simplifikasi, asumsi klien harus sudah didaftarkan (oleh admin/pengacara).
        // Namun, jika P NULL tapi Klien ada (kasus ini tidak mungkin di model ini karena klien nempel di parent),
        // jadi validasi di bawah sudah cukup.
    }

    if (P == NULL || K == NULL) {
        cout << ">> Error: ID Klien tidak ditemukan atau belum terdaftar!" << endl;
        cout << "Tekan Enter kembali..."; cin.get();
        return;
    }

    int pilihan = -1;
    while (pilihan != 0) {
        cout << "\n\n";
        cout << "========================================" << endl;
        cout << "Halo, " << K->info.namaKlien << " (ID: " << K->info.idKlien << ")" << endl;
        cout << "========================================" << endl;
        cout << "1. Lihat Profil Pengacara Saya" << endl;
        cout << "2. Lihat Detail Kasus Saya" << endl;
        cout << "3. Pindah Pengacara (Cari Pengacara Baru)" << endl;
        cout << "0. Logout" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan: "; cin >> pilihan; cin.ignore();

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
            cout << "\nMasukkan ID Pengacara Baru yang diinginkan: "; getline(cin, idBaru);

            if (findPengacara(L, idBaru) != NULL) {
                pindahPengacara(L, myID, P->info.idPengacara, idBaru);
                P = findParentOfKlien(L, myID);
            } else {
                cout << ">> Error: ID Pengacara Baru tidak ditemukan." << endl;
            }
        } else if (pilihan == 0) {
            cout << "Logout..." << endl;
        } else {
            cout << "Pilihan salah." << endl;
        }

        if (pilihan != 0) {
            cout << "\nTekan Enter lanjut..."; cin.get();
        }
    }
}

// MAIN MENU (LOGIN SCREEN)

void runMenu(List &L) {
    int role = -1;
    while (role != 0) {
        cout << "\n\n";
        cout << "========================================" << endl;
        cout << "    APLIKASI MANAJEMEN FIRMA HUKUM      " << endl;
        cout << "    (Kelompok Null Objective Law)       " << endl;
        cout << "========================================" << endl;
        cout << "LOGIN SEBAGAI:" << endl;
        cout << "1. ADMIN (Full Access)" << endl;
        cout << "2. USER (Pengacara / Klien)" << endl;
        cout << "0. KELUAR APLIKASI" << endl;
        cout << "========================================" << endl;
        cout << "Pilihan: "; cin >> role; cin.ignore();

        if (role == 1) {
            // Masuk Menu Admin
            menuAdmin(L);
        } else if (role == 2) {
            // Sub-menu User
            int userType = -1;
            while (userType != 0) {
                cout << "\n--- PILIH TIPE USER ---" << endl;
                cout << "1. Saya Pengacara" << endl;
                cout << "2. Saya Klien" << endl;
                cout << "0. Kembali" << endl;
                cout << "Pilihan: "; cin >> userType; cin.ignore();

                if (userType == 1) {
                    menuUserPengacara(L);
                } else if (userType == 2) {
                    menuUserKlien(L);
                } else if (userType == 0) {
                    break;
                } else {
                    cout << "Pilihan salah." << endl;
                }
            }
        } else if (role == 0) {
            cout << "Terima kasih telah menggunakan aplikasi." << endl;
        } else {
            cout << "Pilihan tidak valid." << endl;
        }
    }
}
