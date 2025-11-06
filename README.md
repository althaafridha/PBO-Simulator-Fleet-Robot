# PBO Simulator Fleet Robot

**Studi Kasus 2:** Simulator Fleet Robot Polymorfik  
_Mata Kuliah: SIR201 - Pemrograman Berorientasi Objek RK - A2_   
_Program Studi: Teknik Robotika dan Kecerdasan Buatan - Universitas Airlangga_

Proyek ini mensimulasikan beberapa jenis kendaraan robotik (GroundRobot, AerialDrone, Amphibious) yang dapat bergerak dan berinteraksi menggunakan konsep *inheritance*, *overriding*, dan *polymorphism*.

---

## Cara Kompilasi dan Menjalankan

### Kompilasi Program
Gunakan terminal atau CMD:
```bash
g++ -std=c++17 robot.cpp -o fleet_sim
```

### Jalankan Program
```bash
./fleet_sim
```

### Jalankan Skenario Uji (opsional)
Pastikan file `scenarios.txt` berada dalam folder yang sama.
```bash
cat scenarios.txt
```

---

## Pembagian Peran Anggota

| Anggota | NIM | Peran | Deskripsi |
|----------|-----|--------|-----------|
| **Aulia Rizky Arief Wicaksono** | 163241017 | **Desain dan `Vehicle` base class (`Position`, `clone()`)** | Mendesain struktur utama kelas Vehicle (atribut ID, posisi, baterai, dan method virtual). |
| **Muhammad Iqbal Alfaqih** | 163241051 | **`GroundRobot` dan sistem *obstacle detection*** dan **Testing** | Implementasi `move()` dan `obstacleAhead()` dengan logika pembatalan gerak jika rintangan terdeteksi |
| **Khanza Audriec Alva Javier** | 163241053 | **`AerialDrone` dan status reporting** | Membuat *overloaded* `move(targetPosition)` serta menambahkan detail status drone (koordinat & baterai), Membuat file `scenarios.txt`, dan laporan akhir, menjalankan pengujian output. |
| **Althaaf Ridha Muhammad Zaydaan Batubara** | 163241054 | **`Amphibious` (integrasi) dan *fleet manager*** dan ***scenario scripts* & dokumentasi** | Menangani mode darat/udara, logika perpindahan otomatis jika ada rintangan, serta fungsi `executeMove()`, Membuat file `scenarios.txt`, dokumentasi `README`, dan menulis dokumentasi proyek. |
---


## Struktur Proyek

```
PBO-Simulator-Fleet-Robot/
│
├── robot.cpp           → Source utama berisi implementasi seluruh kelas
├── scenarios.txt       → Daftar skenario waypoint dan expected logs
├── README.md           → Dokumentasi proyek dan petunjuk penggunaan
└── demo_run.sh         → Skrip otomatis untuk kompilasi dan menjalankan simulasi
```

---

## Run Script / Sample Commands

### Linux/Mac (`run_demo.sh`)
```bash
#!/bin/bash
echo "=== Running Fleet Robot Simulation ==="
g++ -std=c++17 robot.cpp -o fleet_sim

if [ $? -eq 0 ]; then
    echo ">> Compile sukses, menjalankan simulasi..."
    ./fleet_sim > demo_output.txt
    echo ">> Output simulasi tersimpan di demo_output.txt"
else
    echo "!! Compile gagal, periksa syntax."
fi

echo ""
echo "=== Skenario Expected Logs ==="
cat scenarios.txt
```

### Windows (PowerShell)
```powershell
g++ -std=c++17 robot.cpp -o fleet_sim.exe
.leet_sim.exe > demo_output.txt
Get-Content scenarios.txt
```

---

## Contoh Output Ringkas

```
=== Simulator Fleet Robot Polymorfik ===
[GR1] Bergerak ke (1.00,0.00,0.00)
[GR1] Ada rintangan di depan! Gerak dibatalkan.
[AD1] Drone ke (5.00,5.00,10.00)
[AM1] Mode udara aktif. Pos(8.00,0.00,0.00)
=== Semua Case Selesai Diuji ===
```

---

## Catatan Tambahan
- Semua hasil menggunakan `setprecision(2)` untuk presisi dua desimal.  
- Perhitungan baterai bergantung pada jarak dan mode operasi.  
- Polymorfisme diuji melalui array `Vehicle* fleet[3]` di fungsi `main()`.
