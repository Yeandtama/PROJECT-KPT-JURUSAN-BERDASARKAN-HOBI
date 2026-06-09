Judul Projek        : Implementasi Sistem Rekomendasi Jurusan Kuliah   Berbasis Hobi dengan Pendekatan Komputasi Paralel Menggunakan C++ dan OpenMP

Tanggal Mulai       : 6 Mei 2026

Tanggal Deadline    : 12 Juni 2026 

Dosen               : Septian Geges S.Kom., M.Kom.

Jenis Project       : Project Ujian AKhir Semester

Link Demo           : https://youtu.be/7WEM4GVg1JM

Deskripsi Project   : 
    ParallelRec adalah sistem rekomendasi jurusan kuliah berbasis hobi yang dibangun oleh Kelompok 10 menggunakan bahasa C++ dengan pendekatan komputasi paralel melalui library OpenMP. Project ini dikerjakan selama 5 minggu dalam mata kuliah Komputasi Paralel dan Terdistribusi.
    Program ini memiliki database berisi 20 jurusan kuliah, mulai dari Teknik Informatika, DKV, Teknik Elektro, Psikologi, Manajemen Bisnis, Kedokteran, sampai Teknik Kimia. Setiap jurusan memiliki daftar hobi yang relevan beserta bobotnya masing-masing. Misalnya untuk Teknik Informatika, hobi seperti coding dan pemrograman diberi bobot 30, sedangkan logika diberi bobot 25. Ketika program dijalankan, sistem akan men-generate 500 data pengguna secara otomatis di mana setiap pengguna memiliki nama dan daftar hobi yang berbeda-beda.
    Setelah data siap, program membagi seluruh 1000 pengguna tersebut ke beberapa thread menggunakan perintah #pragma omp parallel for. Setiap thread secara mandiri menghitung skor kecocokan antara hobi pengguna yang ditugaskan kepadanya dengan semua jurusan yang ada, lalu memilih 3 jurusan dengan skor tertinggi sebagai rekomendasi. Karena semua thread bekerja bersamaan, proses yang tadinya harus antri satu per satu menjadi jauh lebih efisien. Setelah semua thread selesai, program menampilkan sampel 5 hasil rekomendasi pertama lalu secara otomatis menjalankan benchmark untuk membandingkan performa paralel vs sekuensial pada 9 kombinasi konfigurasi.
    Untuk menjalankan program, buka terminal MinGW lalu pindah ke folder tempat file tersimpan. Seperti yang kita alami sebelumnya, kalau nama foldernya ada spasi harus pakai tanda kutip, contohnya cd "/c/Users/Axioo Pongo/Downloads". Setelah masuk ke folder yang benar, compile dengan perintah g++ -fopenmp -O2 -o parallelrec parallelrec_v2.cpp lalu jalankan dengan ./parallelrec. Program akan langsung berjalan otomatis, memproses 500 pengguna secara paralel, menampilkan hasil rekomendasi, lalu menampilkan tabel benchmark lengkap dengan kolom T_seq, T_par, Speedup, dan Efisiensi untuk semua 9 skenario pengujian.

Anggota Kelompok 10 :
    1. Ian Grizeld Turang
    2. Mikael Andiwijayaliano
    3. Muhammad Nazril Abdillah
    4. Yeand Saltama
