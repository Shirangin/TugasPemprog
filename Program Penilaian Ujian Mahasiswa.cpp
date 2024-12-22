#include <iostream>
#include <fstream>
#include <iomanip>
#include <string> // Untuk string dan getline

using namespace std;

class NilaiAkhir {
private:
    string nama; // Menambahkan nama siswa
    float KuisTotal;
    float Kuis1;
    float Kuis2;
    float UTS;
    float UAS;
    float persentasi;

public:
    void inputnilai();
    void kalkTotal();
    void showGrade(ofstream &outfile);
};

void NilaiAkhir::inputnilai() {
    cout << "Masukkan Nama Siswa: ";
    cin.ignore(); // Membersihkan newline dari buffer input sebelumnya
    getline(cin, nama); // Membaca nama dengan spasi

    cout << "Masukkan Nilai KUIS 1 = ";
    cin >> Kuis1;
    cout << "Masukkan Nilai KUIS 2 = ";
    cin >> Kuis2;
    cout << "Masukkan Nilai UTS = ";
    cin >> UTS;
    cout << "Masukkan Nilai UAS = ";
    cin >> UAS;
}

void NilaiAkhir::kalkTotal() {
    KuisTotal = Kuis1 + Kuis2;
    persentasi = (25.0 / 100.0) * KuisTotal + (25.0 / 100.0) * UTS + (50.0 / 100.0) * UAS;
}

void NilaiAkhir::showGrade(ofstream &outfile) {
    outfile << fixed << setprecision(2);
    outfile << nama << "," << Kuis1 << "," << Kuis2 << "," << UTS << "," << UAS << "," << persentasi << ","; // Output data ke file dengan format CSV

    if (persentasi > 90.0) {
        outfile << "A" << endl;
    } else if (persentasi > 80.0 && persentasi <= 90.0) {
        outfile << "AB" << endl;
    } else if (persentasi > 70.0 && persentasi <= 80.0) {
        outfile << "B" << endl;
    } else if (persentasi > 60.0 && persentasi <= 70.0) {
        outfile << "BC" << endl;
    } else if (persentasi > 50.0 && persentasi <= 60.0) {
        outfile << "C" << endl;
    } else if (persentasi > 40.0 && persentasi <= 50.0) {
        outfile << "CD" << endl;
    } else {
        outfile << "D" << endl;
    }
}

int main() {
    int jumlahSiswa;

    cout << "Masukkan Jumlah Siswa: ";
    cin >> jumlahSiswa;

    NilaiAkhir siswa[jumlahSiswa]; // Array objek untuk menampung data banyak siswa

    ofstream outfile("nilai_siswa.csv");
    if (!outfile.is_open()) {
        cerr << "Error membuka file!" << endl;
        return 1;
    }

    outfile << "Nama,Kuis 1,Kuis 2,UTS,UAS,Persentase,Grade" << endl; // Header CSV

    for (int i = 0; i < jumlahSiswa; i++) {
        cout << "\nData Siswa ke-" << i + 1 << endl;
        siswa[i].inputnilai();
        siswa[i].kalkTotal();
        siswa[i].showGrade(outfile);
    }

    outfile.close();
    cout << "\nData telah disimpan ke nilai_siswa.csv" << endl;

    return 0;
}
