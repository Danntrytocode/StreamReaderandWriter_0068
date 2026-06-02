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
}
