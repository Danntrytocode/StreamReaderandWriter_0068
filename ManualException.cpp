#include <iostream>

using namespace std;

int main(){
    //membuar isi dari try untuk pengujian error
    try{
        cout << "Selamat belajar di prodi TI UMY" << endl;
        throw 0.5; //jika melemparkan sebuah integer maka output :selamat,pengecualian dan pernyatan.
                    //jika melemparkan sebuah float maka output :selamat,default dan pernyataan.
        cout << "Pernyataan tidak akan di tampilkan" << endl;
    }
    //kondisi jika throw yang bertipe data integer
    catch (int a){
        cout << "Pengecualian akan di eksekusi" << endl;
    }
    //kondisi jika throw bertipe data selain integer
    catch (...){
        cout << "default pengecualian di eksekusi" << endl;
    }
    return 0;
}