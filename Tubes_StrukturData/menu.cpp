#include "menu.h"

// Fungsi bantuan untuk cek string kosong
bool isEmpty(string s) {
    return s.length() == 0;
}

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

            // VALIDASI ID
            cout << "ID Pengacara   : "; getline(cin, dataP.idPengacara);
            if (isEmpty(dataP.idPengacara)) {
                cout << ">> ERROR: ID tidak boleh kosong! Proses dibatalkan." << endl;
            }
            else if (findPengacara(L, dataP.idPengacara) != NULL) {
                cout << ">> ERROR: ID Pengacara '" << dataP.idPengacara << "' SUDAH ADA! Gagal Insert." << endl;
            } else {
                // VALIDASI NAMA
                cout << "Nama Pengacara : "; getline(cin, dataP.namaPengacara);
                if (isEmpty(dataP.namaPengacara)) {
                    cout << ">> ERROR: Nama tidak boleh kosong! Proses dibatalkan." << endl;
                } else {
                    cout << "Nama Firma     : "; getline(cin, dataP.firma);

                    // PILIHAN JENIS INSERT
                    int tipeInsert;
                    cout << "\nPilih Posisi Insert:" << endl;
                    cout << "1. Insert First (Depan)" << endl;
                    cout << "2. Insert Last (Belakang)" << endl;
                    cout << "3. Insert After (Setelah ID tertentu)" << endl;
                    cout << "Pilihan: "; cin >> tipeInsert; cin.ignore();

                    adrPengacara newNode = createElmPengacara(dataP);

                    if (tipeInsert == 1) {
                        insertFirstPengacara(L, newNode);
                        cout << ">> Sukses Insert First." << endl;
                    } else if (tipeInsert == 3) {
                        showListPengacara(L);
                        string idPrec;
                        cout << "Masukkan ID Pengacara Sebelumnya (Prec): "; getline(cin, idPrec);
                        adrPengacara Prec = findPengacara(L, idPrec);
                        if (Prec != NULL) {
                            insertAfterPengacara(L, Prec, newNode);
                            cout << ">> Sukses Insert After." << endl;
                        } else {
                            cout << ">> Gagal: ID Predecessor tidak ditemukan. Menggunakan Insert Last." << endl;
                            insertLastPengacara(L, newNode);
                        }
                    } else {
                        // Default Insert Last
                        insertLastPengacara(L, newNode);
                        cout << ">> Sukses Insert Last." << endl;
                    }
                }
            }

        } else if (pilihan == 2) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: INSERT ELEMENT CHILD & RELASI" << endl;
            cout << "--- TAMBAH KLIEN ---" << endl;
            showListPengacara(L);
            cout << "\nID Pengacara Tujuan: "; getline(cin, idParent);

            if (isEmpty(idParent)) {
                cout << ">> ERROR: ID Pengacara tidak boleh kosong!" << endl;
            } else {
                P = findPengacara(L, idParent);
                if (P != NULL) {
                    infotypeKlien dataK;
                    cout << "ID Klien    : "; getline(cin, dataK.idKlien);

                    // VALIDASI INPUT KLIEN (GLOBAL CHECK)
                    if (isEmpty(dataK.idKlien)) {
                        cout << ">> ERROR: ID Klien tidak boleh kosong!" << endl;
                    }
                    // [VALIDASI] Cek apakah ID sudah ada di Pengacara MANAPUN (Global)
                    else if (findParentOfKlien(L, dataK.idKlien) != NULL) {
                         adrPengacara ExistingP = findParentOfKlien(L, dataK.idKlien);
                         cout << ">> ERROR: ID Klien '" << dataK.idKlien
                              << "' SUDAH TERDAFTAR pada pengacara "
                              << ExistingP->info.namaPengacara << "!" << endl;
                    } else {
                        cout << "Nama Klien  : "; getline(cin, dataK.namaKlien);
                        if (isEmpty(dataK.namaKlien)) {
                            cout << ">> ERROR: Nama Klien tidak boleh kosong!" << endl;
                        } else {
                            cout << "Kasus       : "; getline(cin, dataK.kasus);

                            // LANGSUNG CONNECT
                            connectKlienToPengacara(L, idParent, createElmKlien(dataK));
                            cout << ">> Sukses menambahkan klien." << endl;
                        }
                    }
                } else {
                    cout << ">> Pengacara tidak ditemukan." << endl;
                }
            }

        } else if (pilihan == 3) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: SHOW ALL DATA" << endl;
            showAllData(L);

        } else if (pilihan == 4) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: FIND PARENT" << endl;
            cout << "ID Pengacara: "; getline(cin, idParent);
            if(isEmpty(idParent)) {
                cout << ">> ID tidak boleh kosong." << endl;
            } else {
                P = findPengacara(L, idParent);
                if (P) cout << "Ditemukan: " << P->info.namaPengacara << " (" << P->info.idPengacara << ")" << endl;
                else cout << "Tidak ditemukan." << endl;
            }

        } else if (pilihan == 5) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: FIND PARENT OF CHILD" << endl;
            cout << "ID Klien: "; getline(cin, idChild);
            if(isEmpty(idChild)) {
                cout << ">> ID tidak boleh kosong." << endl;
            } else {
                P = findParentOfKlien(L, idChild);
                if (P) cout << "Pengacara: " << P->info.namaPengacara << " (" << P->info.idPengacara << ")" << endl;
                else cout << "Tidak ditemukan." << endl;
            }

        } else if (pilihan == 6) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: DELETE PARENT" << endl;
            showListPengacara(L);
            cout << "\nID Pengacara yg dihapus: "; getline(cin, idParent);

            if(isEmpty(idParent)) {
                cout << ">> ID tidak boleh kosong." << endl;
            } else {
                char yakin;
                cout << "PERINGATAN: Menghapus Pengacara akan menghapus SEMUA Kliennya." << endl;
                cout << "Yakin hapus? (y/n): "; cin >> yakin; cin.ignore();
                if (yakin == 'y' || yakin == 'Y') {
                    deletePengacara(L, idParent);
                } else {
                    cout << ">> Batal hapus." << endl;
                }
            }

        } else if (pilihan == 7) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: DELETE CHILD" << endl;
            cout << "--- HAPUS KLIEN ---" << endl;
            showListPengacara(L);
            cout << "\nPilih ID Pengacara: "; getline(cin, idParent);

            if(isEmpty(idParent)) {
                cout << ">> ID Pengacara tidak boleh kosong." << endl;
            } else {
                P = findPengacara(L, idParent);
                if (P) {
                    cout << "Daftar Klien " << P->info.namaPengacara << ":" << endl;
                    adrKlien K = P->nextKlien;
                    while(K){ cout << "- " << K->info.namaKlien << " (" << K->info.idKlien << ")" << endl; K=K->next; }

                    cout << "\nID Klien yg dihapus: "; getline(cin, idChild);
                    if(isEmpty(idChild)) {
                        cout << ">> ID Klien tidak boleh kosong." << endl;
                    } else {
                        deleteKlienFromPengacara(L, idParent, idChild);
                    }
                } else {
                    cout << "Pengacara tidak valid." << endl;
                }
            }

        } else if (pilihan == 8) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: STATISTIK" << endl;
            int totalPengacara = 0;
            int totalKlien = 0;
            int totalNganggur = 0;
            int maxKlien = -1;

            // LOOP 1: Hitung Total & Cari Max
            adrPengacara cur = L.first;
            while (cur != NULL) {
                totalPengacara++;
                int jumlahAnak = countKlienByPengacara(L, cur->info.idPengacara);
                totalKlien += jumlahAnak;

                if (jumlahAnak == 0) {
                    totalNganggur++;
                }

                if (jumlahAnak > maxKlien) {
                    maxKlien = jumlahAnak;
                }
                cur = cur->next;
            }

            cout << "----------------------------------------" << endl;
            cout << "LAPORAN FIRMA HUKUM" << endl;
            cout << "1. Total Pengacara : " << totalPengacara << " orang" << endl;
            cout << "2. Total Klien     : " << totalKlien << " orang" << endl;
            cout << "3. Pengacara Kosong: " << totalNganggur << " orang" << endl;
            cout << "----------------------------------------" << endl;

            // LOOP 2: Tampilkan SEMUA Pengacara Tersibuk
            if (maxKlien > 0) {
                cout << "PENGACARA TERSIBUK (Menangani " << maxKlien << " Klien):" << endl;
                cur = L.first;
                int countTop = 0;
                while (cur != NULL) {
                    int jumlahAnak = countKlienByPengacara(L, cur->info.idPengacara);
                    if (jumlahAnak == maxKlien) {
                        countTop++;
                        cout << "   " << countTop << ". " << cur->info.namaPengacara
                             << " (ID: " << cur->info.idPengacara << ")" << endl;
                    }
                    cur = cur->next;
                }
            } else {
                cout << "Belum ada aktivitas klien yang signifikan." << endl;
            }
            cout << "----------------------------------------" << endl;

        } else if (pilihan == 9) {
            cout << ">>> [SYSTEM] Menjalankan Fungsi: EDIT RELASI" << endl;
            cout << "ID Klien           : "; getline(cin, idChild);
            cout << "ID Pengacara LAMA  : "; getline(cin, idParent);
            cout << "ID Pengacara BARU  : "; getline(cin, idBaru);

            if(isEmpty(idChild) || isEmpty(idParent) || isEmpty(idBaru)) {
                cout << ">> Semua ID harus diisi!" << endl;
            } else {
                pindahPengacara(L, idChild, idParent, idBaru);
            }

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

// ==========================================
// MENU KHUSUS USER: PENGACARA
// ==========================================
void menuUserPengacara(List &L) {
    string myID;
    cout << "\n--- LOGIN PENGACARA ---" << endl;
    cout << "Masukkan ID Pengacara Anda: "; getline(cin, myID);

    if (isEmpty(myID)) {
        cout << ">> ID tidak boleh kosong!" << endl;
        cout << "Tekan Enter kembali..."; cin.get();
        return;
    }

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
            // Pengacara insert klien sendiri
            infotypeKlien dataK;
            cout << "\n--- TERIMA KLIEN BARU ---" << endl;
            cout << "ID Klien    : "; getline(cin, dataK.idKlien);

            if (isEmpty(dataK.idKlien)) {
                cout << ">> ID tidak boleh kosong!" << endl;
            }
            // VALIDASI GLOBAL: Cek apakah ID Klien SUDAH ADA di SIAPAPUN
            else if (findParentOfKlien(L, dataK.idKlien) != NULL) {
                 adrPengacara ExistingP = findParentOfKlien(L, dataK.idKlien);
                 cout << ">> ERROR: ID Klien '" << dataK.idKlien
                      << "' SUDAH TERDAFTAR pada pengacara "
                      << ExistingP->info.namaPengacara << "!" << endl;
            } else {
                cout << "Nama Klien  : "; getline(cin, dataK.namaKlien);
                if (isEmpty(dataK.namaKlien)) {
                    cout << ">> Nama tidak boleh kosong!" << endl;
                } else {
                    cout << "Kasus       : "; getline(cin, dataK.kasus);

                    // LANGSUNG CONNECT
                    connectKlienToPengacara(L, myID, createElmKlien(dataK));
                    cout << ">> Sukses menerima klien baru." << endl;
                }
            }
        } else if (pilihan == 3) {
            string idK;
            cout << "\n--- HAPUS KLIEN ---" << endl;
            cout << "Masukkan ID Klien yg akan dihapus: "; getline(cin, idK);
            if (!isEmpty(idK)) {
                deleteKlienFromPengacara(L, myID, idK);
            }
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

// ==========================================
// MENU KHUSUS USER: KLIEN
// ==========================================
void menuUserKlien(List &L) {
    string myID;
    cout << "\n--- LOGIN KLIEN ---" << endl;
    cout << "Masukkan ID Klien Anda: "; getline(cin, myID);

    if (isEmpty(myID)) {
        cout << ">> ID tidak boleh kosong!" << endl;
        cout << "Tekan Enter kembali..."; cin.get();
        return;
    }

    // Cari Klien ini milik siapa
    adrPengacara P = findParentOfKlien(L, myID);

    adrKlien K = NULL;
    if (P != NULL) {
        K = findKlienInPengacara(P, myID);
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

            if(isEmpty(idBaru)) {
                cout << ">> ID tidak boleh kosong." << endl;
            }
            else if (findPengacara(L, idBaru) != NULL) {
                // CONFIRMATION
                char k;
                cout << "Yakin pindah ke pengacara baru? (y/n): "; cin >> k; cin.ignore();
                if (k == 'y' || k == 'Y') {
                    pindahPengacara(L, myID, P->info.idPengacara, idBaru);
                    P = findParentOfKlien(L, myID); // Update parent pointer
                } else {
                    cout << "Batal pindah." << endl;
                }
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

// ==========================================
// MAIN MENU (LOGIN SCREEN)
// ==========================================
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
            menuAdmin(L);
        } else if (role == 2) {
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
