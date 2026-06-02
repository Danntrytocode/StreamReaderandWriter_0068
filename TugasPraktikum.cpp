/*Buatlah program C++ berbasis Object-Oriented Programming (OOP) untuk digitalisasi manajemen toko elektronik "Gibran Jaya" dengan ketentuan berikut:
​1. Struktur Kelas TokoElektronik
• ​Atribut Private: Buat sebuah array berkapasitas 3 elemen sebagai perwujudan prinsip enkapsulasi (merepresentasikan barang yang dipajang di etalase).
• ​Constructor: Buat constructor untuk mengisi data awal ke dalam array tersebut secara otomatis.
• ​Method Public: Buat fungsi untuk mengambil produk dengan parameter nomorRak (bertipe data size_t).
​2. Mekanisme Exception Handling (Penanganan Error)
• ​Di dalam method pengambilan produk pada etalase, wajib menggunakan fungsi .at() saat mengakses indeks array.
• ​Jika pencarian indeks melewati batas, tangkap error bawaan out_of_range.
• ​Setelah ditangkap, lemparkan kembali (throw) pesan error kustom berikut: ​"Gagal Mengambil Barang : Rak nomor [X] kosong atau tidak tersedia!" (Ganti [X] dengan nilai nomorRak).
​"Gagal Mengambil Barang : Rak nomor [X] kosong atau tidak tersedia!" (Ganti [X] dengan nilai nomorRak).
3. Fitur Manajemen Gudang Berbasis File (File I/O & CRUD)
• ​Gunakan library <fstream> (Stream Reader/Writer) untuk menyimpan dan membaca basis data barang menggunakan file berekstensi teks (misalnya gudang.txt).
• ​Buatlah sebuah Menu Utama interaktif berbasis Command Line (CLI) yang mengakomodasi operasi CRUD berikut yang terhubung langsung dengan file .txt: 
• ​Create: Menambahkan data barang baru ke dalam file .txt.
• ​Read: Membaca dan menampilkan daftar barang dari dalam file .txt ke layar secara otomatis saat menu dibuka.
• ​Update: Memperbarui/mengubah data barang tertentu di dalam file .txt.
• ​Delete: Menghapus data barang dari dalam file .txt.
​4. Pengujian pada Fungsi main()
• ​Jalankan sistem Menu Utama (menggunakan looping seperti while atau do-while) agar pengguna bisa memilih fitur CRUD gudang.
• ​Tambahkan satu opsi khusus di dalam menu untuk menjalankan Simulasi Etalase (menguji Exception Handling pada poin 2) dengan dua skenario: 
• ​Skenario 1: Pengambilan barang di rak indeks ke-1 (Harus sukses).
• ​Skenario 2: Pengambilan barang di rak indeks ke-5 (Harus gagal dan menampilkan pesan error kustom).
Pastikan sistem menu, operasi file (CRUD), dan penangkapan error array terintegrasi dengan baik sehingga program tetap berjalan aman (tidak crash atau berhenti mendadak) meskipun terjadi error logika.*/

#include <iostream>
#include <string>
#include <array>
#include <stdexcept>
#include <fstream>
#include <vector>

using namespace std;
//klaas induk/utaama
class TokoElektronik {
private:
    //Atribut Private: Array berkapasitas 3 elemen
    array<string, 3> etalase;

public:
    //Constructor Mengisi data awal secara otomatis
    TokoElektronik() {
        etalase = {"Laptop Ragnamok", "iPhone 13 Pro Maxxing", "Dumb TV Samsung"};
    }

    //Method Public dan exception Handling
    string ambilBarang(size_t nomorRak) {
        try {
            //out_of_range jika index melebihi kapasitas
            return etalase.at(nomorRak);
        } 
        catch (const out_of_range& e) {
            //catch error bawaan dan melempar ulang pesan error kustom
            string pesanError = "Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!";
            throw pesanError; 
        }
    }
};

//klass tambahan untuk membedakan logika Manajemen File Gudang
class GudangManager {
private:
    string namaFile = "gudang.txt";

    //fungsi private untuk membaca seluruh baris file ke dalam vector
    vector<string> bacaSemuaData() {
        vector<string> data;
        ifstream file(namaFile);
        string baris;
        if (file.is_open()) {
            while (getline(file, baris)) {
                data.push_back(baris);
            }
            file.close();
        }
        return data;
    }

    //fungsi private untuk menimpa file dengan data baru
    void tulisSemuaData(const vector<string>& data) {
        ofstream file(namaFile);
        if (file.is_open()) {
            for (const auto& item : data) {
                file << item << "\n";
            }
            file.close();
        }
    }

public:
    //Read > Menampilkan daftar barang dari file txt
    void tampilkanGudang() {
        cout << "\n=== Daftar Barang di Gudang (gudang.txt) ===\n";
        vector<string> data = bacaSemuaData();
        if (data.empty()) {
            cout << "(Gudang masih kosong)\n";
        } else {
            for (size_t i = 0; i < data.size(); ++i) {
                cout << i + 1 << ". " << data[i] << "\n";
            }
        }
        cout << "============================================\n";
    }

    //create > Menambahkan data baru
    void tambahBarang(const string& barangBaru) {
        ofstream file(namaFile, ios::app); // Mode append
        if (file.is_open()) {
            file << barangBaru << "\n";
            file.close();
            cout << "[INFO] Barang berhasil ditambahkan ke gudang!\n";
        } else {
            cout << "[ERROR] Gagal membuka file gudang!\n";
        }
    }

    //update > Mengubah data berdasarkan nomor urut
    void updateBarang(size_t nomor, const string& barangBaru) {
        vector<string> data = bacaSemuaData();
        if (nomor > 0 && nomor <= data.size()) {
            data[nomor - 1] = barangBaru;
            tulisSemuaData(data);
            cout << "[INFO] Data barang berhasil diperbarui!\n";
        } else {
            cout << "[ERROR] Nomor barang tidak valid!\n";
        }
    }

    //delete tuk Menghapus data berdasarkan nomor urut
    void hapusBarang(size_t nomor) {
        vector<string> data = bacaSemuaData();
        if (nomor > 0 && nomor <= data.size()) {
            data.erase(data.begin() + nomor - 1);
            tulisSemuaData(data);
            cout << "[INFO] Data barang berhasil dihapus!\n";
        } else {
            cout << "[ERROR] Nomor barang tidak valid!\n";
        }
    }
};

int main() {
    int pilihan;
    TokoElektronik toko;
    GudangManager gudang;
    string inputString;
    size_t nomorBarang;

    do {
        //menampilkan isi file gudang.txt saat menu dibuka
        gudang.tampilkanGudang();

        cout << "========Menu Utama Manajemen Gibran Jaya========";
        cout << "1. Tambah Barang Baru (Create)\n";
        cout << "2. Update Data Barang (Update)\n";
        cout << "3. Hapus Data Barang (Delete)\n";
        cout << "4. Simulasi Etalase (Test Exception Handling)\n";
        cout << "0. Exit\n";
        cout << "Pilih menu (0-4): ";
        cout << "=================================================" << endl;
        
        if (!(cin >> pilihan)) {
            cout << "Input  Invalid. Pilih masukkan angka.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (pilihan) {
            case 1:
                cout << "Masukkan nama barang baru: ";
                gudang.tambahBarang(inputString);
                break;
            case 2:
                cout << "Masukkan nomor urut barang yang ingin diubah: ";
                cin >> nomorBarang;
                cout << "Masukkan nama barang pengganti: ";
                gudang.updateBarang(nomorBarang, inputString);
                break;
            case 3:
                cout << "Masukkan nomor urut barang yang ingin dihapus: ";
                cin >> nomorBarang;
                gudang.hapusBarang(nomorBarang);
                break;
            case 4:
                cout << "\n--- Menjalankan Simulasi Etalase ---\n";
                //skenario 1: Rak indeks ke-1 (Harus sukses)
                try {
                    cout << "> Skenario 1 (Akses indeks 1)...\n";
                    string barang = toko.ambilBarang(1);
                    cout << "Sukses: Mendapatkan barang [" << barang << "]\n";
                } 
                catch (const string& errorMsg) {
                    //catch error kustom berupa tipe string
                    cout << "Error: " << errorMsg << "\n";
                }

                //soekarno 2: Rak indeks ke-5 (Harus gagal)
                try {
                    cout << "\n> soekarno 2 (Akses indeks 5)...\n";
                    string barang = toko.ambilBarang(5);
                    cout << "Sukses: Mendapatkan barang [" << barang << "]\n";
                } 
                catch (const string& errorMsg) {
                    //catch error kustom berupa tipe string
                    cout << errorMsg << "\n";
                }
                
                cout << "------------------------------------\n";
                cout << "Tekan Enter untuk melanjutkan...";
                cin.ignore();
                cin.get();
                break;
            case 0:
                cout << "Keluar dari program. Thankyou!\n";
                break;
            default:
                cout << "Pilihan tidak tersedia. Silakan Try lagi.\n";
        }
    } while (pilihan != 0);

    return 0;
}