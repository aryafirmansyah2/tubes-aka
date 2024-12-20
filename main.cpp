#include <iostream>
#include <chrono>

using namespace std;

struct Karyawan
{
  double gajiPokok;
  double tunjangan;
  double potongan;
  double pajak;
};

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

  const int jumlahKaryawan = 1000;
  Karyawan *karyawanList = new Karyawan[jumlahKaryawan];

  for (int i = 0; i < jumlahKaryawan; i++)
  {

    double gajiPokok = 20000;
    double tunjangan = 5000;
    double potongan = 1000;
    double pajak = 1000;

    karyawanList[i].gajiPokok = gajiPokok;
    karyawanList[i].tunjangan = tunjangan;
    karyawanList[i].potongan = potongan;
    karyawanList[i].pajak = pajak;
  }

  auto start = chrono::high_resolution_clock::now();
  double totalGajiRekursif = hitungGajiRekursif(karyawanList, 0, jumlahKaryawan);
  auto end = chrono::high_resolution_clock::now();
  chrono::duration<double> rekursifDuration = end - start;
  cout << "Total Gaji Semua Karyawan (Rekursif): Rp " << totalGajiRekursif << endl;
  cout << "Waktu Eksekusi Rekursif untuk " << jumlahKaryawan << " karyawan: " << rekursifDuration.count() << " detik" << endl;

  start = chrono::high_resolution_clock::now();
  double totalGajiIteratif = hitungGajiIteratif(karyawanList, jumlahKaryawan);
  end = chrono::high_resolution_clock::now();
  chrono::duration<double> iteratifDuration = end - start;
  cout << "Total Gaji Semua Karyawan (Iteratif): Rp " << totalGajiIteratif << endl;
  cout << "Waktu Eksekusi Iteratif untuk " << jumlahKaryawan << " karyawan: " << iteratifDuration.count() << " detik" << endl;

  delete[] karyawanList;

  return 0;
}
