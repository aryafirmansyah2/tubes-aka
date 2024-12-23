package main

import (
	"fmt"
	"math/rand"
	"time"
)

// Struktur data untuk slip gaji
type SlipGaji struct {
	ID           string
	NamaPegawai  string
	GajiPokok    float64
	Potongan     float64
	Tunjangan    float64
}

// Iteratif: Menghitung total gaji
func hitungTotalGajiIterative(slips []SlipGaji) float64 {
	total := 0.0
	for _, slip := range slips {
		total += slip.GajiPokok - slip.Potongan + slip.Tunjangan
	}
	return total
}

// Rekursif: Menghitung total gaji
func hitungTotalGajiRecursive(slips []SlipGaji, index int) float64 {
	if index >= len(slips) {
		return 0.0 // Base case: tidak ada slip lagi
	}
	currentGaji := slips[index].GajiPokok - slips[index].Potongan + slips[index].Tunjangan
	return currentGaji + hitungTotalGajiRecursive(slips, index+1)
}

// Fungsi untuk membuat data slip gaji secara acak
func generateSlipGaji(size int) []SlipGaji {
	slips := make([]SlipGaji, size)
	for i := 0; i < size; i++ {
		slips[i] = SlipGaji{
			ID:          fmt.Sprintf("SLIP-%d", rand.Intn(1000000)),
			NamaPegawai: fmt.Sprintf("Pegawai-%d", i+1),
			GajiPokok:   float64(rand.Intn(5000000) + 3000000), // Gaji pokok antara 3 juta - 8 juta
			Potongan:    float64(rand.Intn(1000000)),           // Potongan hingga 1 juta
			Tunjangan:   float64(rand.Intn(2000000)),           // Tunjangan hingga 2 juta
		}
	}
	return slips
}

func main() {
	// Ukuran input yang ingin diukur
	sizes := []int{1, 10, 100, 1000, 10000, 100000}

	const iterations = 10 // Jumlah iterasi untuk rata-rata waktu

	// Cetak header tabel
	fmt.Printf("%-15s %-25s %-25s\n", "Ukuran Input", "Iteratif (s)", "Rekursif (s)")
	fmt.Println("-------------------------------------------------------------")

	for _, size := range sizes {
		slips := generateSlipGaji(size)

		// Iteratif
		var totalIterativeTime int64
		for i := 0; i < iterations; i++ {
			start := time.Now()
			hitungTotalGajiIterative(slips)
			duration := time.Since(start).Nanoseconds()
			totalIterativeTime += duration
		}
		avgIterativeTime := float64(totalIterativeTime) / 1_000_000_000 // Konversi ke detik

		// Rekursif
		var totalRecursiveTime int64
		for i := 0; i < iterations; i++ {
			start := time.Now()
			hitungTotalGajiRecursive(slips, 0)
			duration := time.Since(start).Nanoseconds()
			totalRecursiveTime += duration
		}
		avgRecursiveTime := float64(totalRecursiveTime) / 1_000_000_000 // Konversi ke detik

		// Cetak hasil
		fmt.Printf("%-15d %-25.8f %-25.8f\n", size, avgIterativeTime, avgRecursiveTime)
	}
}
