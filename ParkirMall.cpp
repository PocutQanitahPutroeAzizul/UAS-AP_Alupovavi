#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstdlib> // untuk system("cls")
using namespace std;

#define MAKS_PARKIR 20

struct Mobil {
    string plat;
    string merk;
    string warna;
    time_t waktuMasuk;
};

vector<Mobil> daftarMobil;

void header() {
    cout << "==================================================" << endl;
    cout << "                SELAMAT DATANG                    " << endl;
    cout << "         DI PORTAL PARKIR KHUSUS MOBIL            " << endl;
    cout << "                MALL PRIENAL                      " << endl;
    cout << "==================================================" << endl;
}

void tampilkanMenu() {
    cout << "\n=============== MENU UTAMA ===============" << endl;
    cout << "1. Tambahkan Daftar Kendaraan" << endl;
    cout << "2. Tampilkan Daftar Kendaraan" << endl;
    cout << "3. Pembayaran" << endl;
    cout << "4. Keluar Program" << endl;
    cout << "==========================================" << endl;
    cout << "Masukkan opsi : ";
}

void tambahKendaraan() {
    if (daftarMobil.size() >= MAKS_PARKIR) {
        cout << "\nParkiran sudah penuh!" << endl;
        return;
    }

    int jumlah;
    cout << "\nMasukkan jumlah mobil yang akan diparkirkan : ";
    cin >> jumlah;
    cin.ignore();

    if (daftarMobil.size() + jumlah > MAKS_PARKIR) {
        cout << "Maaf, hanya tersedia " << MAKS_PARKIR - daftarMobil.size() << " slot parkir." << endl;
        jumlah = MAKS_PARKIR - daftarMobil.size();
    }

    for (int i = 0; i < jumlah; i++) {
        Mobil m;
        Mobil* ptr = &m;

        cout << "\n-- Input Mobil ke-" << daftarMobil.size() + 1 << " --" << endl;
        cout << "Plat mobil   : "; getline(cin, (*ptr).plat);
        cout << "Merk mobil   : "; getline(cin, (*ptr).merk);
        cout << "Warna mobil  : "; getline(cin, (*ptr).warna);
        (*ptr).waktuMasuk = time(0);

        daftarMobil.push_back(*ptr);
    }

    cout << "\nData mobil berhasil ditambahkan ke daftar parkir." << endl;
}

void tampilkanDaftar() {
    cout << "\n=========== DAFTAR MOBIL TERPARKIR ===========" << endl;

    if (daftarMobil.empty()) {
        cout << "Belum ada mobil yang parkir saat ini." << endl;
        return;
    }

    for (size_t i = 0; i < daftarMobil.size(); ++i) {
        time_t now = time(0);
        double durasi = difftime(now, daftarMobil[i].waktuMasuk);
        int jam = durasi / 3600;
        int menit = ((int)durasi % 3600) / 60;
        int detik = (int)durasi % 60;

        cout << "\nMobil ke-" << i + 1 << endl;
        cout << "Plat   : " << daftarMobil[i].plat << endl;
        cout << "Merk   : " << daftarMobil[i].merk << endl;
        cout << "Warna  : " << daftarMobil[i].warna << endl;
        cout << "Durasi : " << jam << " jam " << menit << " menit " << detik << " detik" << endl;
    }

    cout << "\n==============================================" << endl;
}

void pembayaran() {
    cout << "\n=========== PEMBAYARAN PARKIR =============" << endl;

    string plat;
    cout << "Masukkan plat mobil yang ingin dibayar : ";
    getline(cin, plat);

    bool ditemukan = false;

    for (auto it = daftarMobil.begin(); it != daftarMobil.end(); ++it) {
        if (it->plat == plat) {
            ditemukan = true;

            time_t now = time(0);
            double durasi = difftime(now, it->waktuMasuk);
            int jam = (durasi / 3600) + 1;
            int tarifPerJam = 5000;
            int total = jam * tarifPerJam;

            cout << "\nBiaya parkir selama " << jam << " jam." << endl;
            cout << "TOTAL YANG HARUS DIBAYAR: Rp" << total << endl;

            daftarMobil.erase(it);
            cout << "Mobil dengan plat " << plat << " telah keluar dari parkiran." << endl;
            break;
        }
    }

    if (!ditemukan) {
        cout << "PLAT TIDAK DITEMUKAN di daftar parkir!" << endl;
    }

    cout << "===========================================" << endl;
}

int main() {
    string nama, id;

    system("cls"); // Clear screen pertama
    header();
    cout << "\nSebelum mulai, silakan masukkan data petugas." << endl;
    cout << "Nama Petugas : "; getline(cin, nama);
    cout << "ID Petugas   : "; getline(cin, id);

    int opsi;

    do {
        system("cls"); // Clear screen sebelum menu tampil
        cout << "\n==========================================" << endl;
        cout << "Petugas Saat Ini : " << nama << " (ID: " << id << ")" << endl;
        cout << "==========================================" << endl;

        tampilkanMenu();
        cin >> opsi;
        cin.ignore();

        switch (opsi) {
            case 1:
                tambahKendaraan();
                break;
            case 2:
                tampilkanDaftar();
                break;
            case 3:
                pembayaran();
                break;
            case 4:
                cout << "\nTerima kasih telah menggunakan sistem parkir ini." << endl;
                break;
            default:
                cout << "Opsi tidak valid. Silakan pilih antara 1 sampai 4." << endl;
        }

        if (opsi != 4) {
            cout << "\nTekan Enter untuk kembali ke menu..."; cin.get();
        }

    } while (opsi != 4);

    return 0;
}
