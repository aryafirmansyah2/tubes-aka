#include <iostream>
#include <chrono> // Untuk pengukuran waktu

using namespace std;

struct Karyawan
{
  double gajiPokok;
  double tunjangan;
  double potongan;
  double pajak;
};

// Fungsi Rekursif
double hitungGajiRekursif(Karyawan *karyawanList, int index, int totalKaryawan)
{
  if (index == totalKaryawan)
  {
    return 0;
  }
  else
  {
    double gajiKaryawan = karyawanList[index].gajiPokok + karyawanList[index].tunjangan - karyawanList[index].potongan - karyawanList[index].pajak;
    return gajiKaryawan + hitungGajiRekursif(karyawanList, index + 1, totalKaryawan);
  }
}

// Fungsi Iteratif
double hitungGajiIteratif(Karyawan *karyawanList, int totalKaryawan)
{
  double totalGaji = 0;
  for (int i = 0; i < totalKaryawan; ++i)
  {
    totalGaji += karyawanList[i].gajiPokok + karyawanList[i].tunjangan - karyawanList[i].potongan - karyawanList[i].pajak;
  }
  return totalGaji;
}

int main()
{
  // Ukuran data yang berbeda untuk menguji performa
  const int jumlahKaryawan = 1000;                       // Menentukan jumlah karyawan
  Karyawan *karyawanList = new Karyawan[jumlahKaryawan]; // Alokasi array dinamis

  // Mengisi data karyawan
  for (int i = 0; i < jumlahKaryawan; i++)
  {
    // Menghasilkan nilai acak dalam rentang yang diinginkan
    double gajiPokok = 20000; // Rentang 2.000.000 - 10.000.000
    double tunjangan = 5000;  // Rentang 500.000 - 5.500.000
    double potongan = 1000;   // Rentang 100.000 - 2.100.000
    double pajak = 1000;      // Rentang 100.000 - 1.100.000

    // Menyimpan data yang sudah diacak ke dalam array karyawan
    karyawanList[i].gajiPokok = gajiPokok;
    karyawanList[i].tunjangan = tunjangan;
    karyawanList[i].potongan = potongan;
    karyawanList[i].pajak = pajak;
  }

  // Pengukuran waktu untuk fungsi rekursif
  auto start = chrono::high_resolution_clock::now();
  double totalGajiRekursif = hitungGajiRekursif(karyawanList, 0, jumlahKaryawan);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> rekursifDuration = end - start;
  cout << "Total Gaji Semua Karyawan (Rekursif): Rp " << totalGajiRekursif << endl;
  cout << "Waktu Eksekusi Rekursif untuk " << jumlahKaryawan << " karyawan: " << rekursifDuration.count() << " detik" << endl;

  // Pengukuran waktu untuk fungsi iteratif
  start = chrono::high_resolution_clock::now();
  double totalGajiIteratif = hitungGajiIteratif(karyawanList, jumlahKaryawan);
  end = chrono::high_resolution_clock::now();
  chrono::duration<double> iteratifDuration = end - start;
  cout << "Total Gaji Semua Karyawan (Iteratif): Rp " << totalGajiIteratif << endl;
  cout << "Waktu Eksekusi Iteratif untuk " << jumlahKaryawan << " karyawan: " << iteratifDuration.count() << " detik" << endl;

  delete[] karyawanList; // Jangan lupa untuk membebaskan memori yang dialokasikan

  return 0;
}
