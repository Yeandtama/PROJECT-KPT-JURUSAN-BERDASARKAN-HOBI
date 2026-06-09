/*
 * ============================================================
 *  ParallelRec v2.0 - Sistem Rekomendasi Jurusan
 *  Kelompok 10: Muhammad Nazril, Yeand Saltama,
 *               Ian Grizeld Turang, Mikael Andiwijayaliano
 *  Mata Kuliah: Komputasi Paralel dan Terdistribusi
 * ============================================================
 *
 * Cara compile:
 *   g++ -fopenmp -O2 -o parallelrec parallelrec_v2.cpp
 *
 * Cara jalankan:
 *   ./parallelrec
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <omp.h>

using namespace std;
using namespace chrono;

// ===================== STRUKTUR DATA =====================

struct Pengguna {
    int id;
    string nama;
    vector<string> hobi;
};

struct Jurusan {
    string nama;
    map<string, int> bobot_hobi;
};

struct Rekomendasi {
    string jurusan;
    int skor;
};

// ===================== DATABASE JURUSAN (20 jurusan) =====================

vector<Jurusan> buatDatabaseJurusan() {
    return {
        { "Teknik Informatika", {
            {"coding",30},{"pemrograman",30},{"logika",25},{"matematika",20},
            {"games",15},{"teknologi",20},{"komputer",25},{"algoritma",25},
            {"hacking",20},{"programming",30},{"software",25},{"debugging",20},
            {"python",25},{"java",25},{"web",20}
        }},
        { "Desain Komunikasi Visual", {
            {"menggambar",30},{"desain",30},{"seni",25},{"fotografi",20},
            {"kreatif",25},{"warna",20},{"ilustrasi",25},{"animasi",20},
            {"lukis",25},{"sketsa",20},{"grafis",25},{"tipografi",20},
            {"branding",25},{"poster",20},{"visual",25}
        }},
        { "Teknik Elektro", {
            {"elektronika",30},{"robotika",30},{"fisika",25},{"matematika",20},
            {"teknologi",20},{"listrik",25},{"arduino",30},{"sensor",20},
            {"rangkaian",25},{"mikrokontroler",30},{"iot",25},{"tegangan",20},
            {"motor",15},{"pcb",25},{"embedded",25}
        }},
        { "Psikologi", {
            {"sosial",25},{"menulis",20},{"membaca",20},{"membantu",30},
            {"komunikasi",25},{"konseling",30},{"empati",30},{"observasi",20},
            {"analisis",15},{"perilaku",25},{"terapi",25},{"manusia",20},
            {"komunitas",20},{"riset",20},{"pendidikan",15}
        }},
        { "Manajemen Bisnis", {
            {"bisnis",30},{"komunikasi",25},{"sosial",20},{"kepemimpinan",30},
            {"ekonomi",25},{"organisasi",20},{"presentasi",20},{"negosiasi",25},
            {"marketing",30},{"wirausaha",30},{"keuangan",25},{"strategi",25},
            {"manajemen",25},{"pemasaran",25},{"penjualan",20}
        }},
        { "Kedokteran", {
            {"biologi",30},{"kimia",25},{"membantu",25},{"membaca",20},
            {"penelitian",25},{"sains",25},{"kesehatan",30},{"anatomi",30},
            {"medis",30},{"farmasi",25},{"olahraga",15},{"patologi",25},
            {"bedah",20},{"diagnosis",25},{"pasien",20}
        }},
        { "Ilmu Komunikasi", {
            {"menulis",30},{"komunikasi",30},{"sosial",25},{"fotografi",20},
            {"presentasi",25},{"jurnalisme",30},{"media",25},{"berbicara",25},
            {"broadcast",30},{"konten",20},{"berita",25},{"wawancara",20},
            {"radio",20},{"televisi",20},{"podcast",20}
        }},
        { "Sistem Informasi", {
            {"komputer",25},{"bisnis",20},{"coding",20},{"logika",20},
            {"teknologi",25},{"data",30},{"analisis",25},{"database",30},
            {"excel",20},{"sistem",25},{"manajemen",20},{"erp",25},
            {"sql",25},{"jaringan",20},{"it",25}
        }},
        { "Teknik Sipil", {
            {"matematika",25},{"fisika",25},{"menggambar",20},{"bangunan",30},
            {"konstruksi",30},{"lingkungan",20},{"struktur",30},{"arsitektur",25},
            {"proyek",20},{"lapangan",20},{"jembatan",25},{"beton",20},
            {"surveying",20},{"autocad",25},{"infrastruktur",25}
        }},
        { "Hukum", {
            {"membaca",25},{"menulis",25},{"logika",20},{"debat",30},
            {"sosial",20},{"analisis",25},{"berbicara",25},{"argumentasi",30},
            {"politik",25},{"keadilan",30},{"negosiasi",20},{"undang-undang",30},
            {"advokat",25},{"pidana",20},{"perdata",20}
        }},
        { "Akuntansi", {
            {"matematika",25},{"keuangan",30},{"ekonomi",25},{"analisis",25},
            {"bisnis",20},{"teliti",30},{"excel",25},{"laporan",25},
            {"pajak",30},{"audit",30},{"neraca",25},{"manajemen",20},
            {"akuntansi",30},{"pembukuan",25},{"investasi",20}
        }},
        { "Farmasi", {
            {"kimia",30},{"biologi",25},{"sains",25},{"kesehatan",25},
            {"penelitian",25},{"farmasi",30},{"obat",30},{"medis",20},
            {"laboratorium",25},{"analisis",20},{"molekul",25},{"klinis",20},
            {"apotek",25},{"toksikologi",20},{"fitokimia",20}
        }},
        { "Pendidikan", {
            {"mengajar",30},{"sosial",20},{"komunikasi",25},{"sabar",25},
            {"membaca",20},{"menulis",20},{"anak",25},{"pendidikan",30},
            {"kurikulum",25},{"belajar",25},{"kreatif",20},{"bahasa",20},
            {"psikologi",15},{"komunitas",20},{"bermain",15}
        }},
        { "Teknik Mesin", {
            {"fisika",25},{"matematika",25},{"mesin",30},{"otomotif",25},
            {"konstruksi",20},{"desain",20},{"manufaktur",30},{"material",25},
            {"teknologi",20},{"robotika",20},{"autocad",25},{"thermodinamika",25},
            {"hidrolik",20},{"produksi",25},{"las",20}
        }},
        { "Arsitektur", {
            {"menggambar",30},{"desain",30},{"seni",20},{"matematika",20},
            {"bangunan",30},{"kreatif",25},{"arsitektur",30},{"ruang",25},
            {"estetika",25},{"struktur",20},{"interior",25},{"autocad",25},
            {"sketchup",20},{"urban",20},{"lingkungan",20}
        }},
        { "Pertanian", {
            {"biologi",25},{"kimia",20},{"alam",30},{"lingkungan",25},
            {"penelitian",20},{"pertanian",30},{"tanaman",30},{"tanah",25},
            {"agro",30},{"peternakan",20},{"pangan",25},{"ekologi",20},
            {"lapangan",20},{"benih",20},{"pupuk",20}
        }},
        { "Keperawatan", {
            {"membantu",30},{"kesehatan",30},{"sosial",20},{"empati",25},
            {"medis",25},{"sabar",30},{"komunikasi",20},{"pasien",30},
            {"biologi",20},{"kimia",15},{"perawatan",30},{"rumah sakit",25},
            {"klinis",20},{"farmasi",15},{"komunitas",20}
        }},
        { "Ekonomi", {
            {"matematika",25},{"ekonomi",30},{"analisis",25},{"bisnis",20},
            {"keuangan",25},{"statistik",30},{"riset",25},{"data",20},
            {"investasi",25},{"pasar",25},{"kebijakan",20},{"makro",25},
            {"mikro",25},{"perdagangan",20},{"pembangunan",20}
        }},
        { "Biologi", {
            {"biologi",30},{"alam",25},{"penelitian",25},{"kimia",20},
            {"lingkungan",20},{"ekologi",25},{"sains",25},{"laboratorium",25},
            {"genetika",25},{"evolusi",20},{"mikrobiologi",25},{"botani",20},
            {"zoologi",20},{"konservasi",25},{"taksonomi",20}
        }},
        { "Teknik Kimia", {
            {"kimia",30},{"fisika",25},{"matematika",20},{"penelitian",25},
            {"laboratorium",25},{"industri",25},{"proses",25},{"material",20},
            {"termodinamika",25},{"reaktor",25},{"petroleum",20},{"polimer",20},
            {"lingkungan",15},{"energi",20},{"katalis",20}
        }},
    };
}

// ===================== GENERATE 500+ DATA PENGGUNA =====================

vector<Pengguna> generateDataPengguna(int jumlah) {
    // Pool nama lengkap (50 nama)
    vector<string> nama_pool = {
        "Andi Pratama","Budi Santoso","Citra Dewi","Doni Kusuma","Eka Putri",
        "Fajar Nugroho","Gita Sari","Hendra Wijaya","Indah Lestari","Joko Widodo",
        "Kevin Hartono","Lisa Permata","Mega Wulandari","Naufal Rizki","Olivia Tan",
        "Pandu Setiawan","Qori Amelia","Reza Firmansyah","Sinta Maharani","Taufik Hidayat",
        "Umar Hakim","Vina Claudia","Wahyu Ramadhan","Xena Pratiwi","Yoga Saputra",
        "Zahra Nadia","Aditya Kurniawan","Bella Anastasia","Cahyo Wibowo","Diana Safitri",
        "Eko Prasetyo","Fira Rahmawati","Gilang Ramadhan","Hana Permatasari","Ilham Maulana",
        "Jasmine Putri","Krisna Bayu","Layla Andriani","Miko Santana","Nina Agustina",
        "Oscar Firmanto","Putri Rahayu","Quincy Halim","Rina Susanti","Surya Dharma",
        "Tika Novitasari","Udin Sedunia","Veri Gunawan","Wanda Cantika","Yusuf Abdillah"
    };

    // Pool hobi per kategori (mapping ke jurusan)
    vector<vector<string>> pool_hobi = {
        // TI
        {"coding","pemrograman","logika","algoritma","software","python","java","web","debugging","komputer"},
        // DKV
        {"menggambar","desain","seni","ilustrasi","animasi","grafis","lukis","warna","kreatif","sketsa"},
        // Elektro
        {"elektronika","robotika","arduino","sensor","listrik","rangkaian","mikrokontroler","iot","embedded","pcb"},
        // Psikologi
        {"empati","konseling","membantu","observasi","perilaku","terapi","sosial","komunikasi","membaca","komunitas"},
        // Bisnis
        {"bisnis","marketing","wirausaha","kepemimpinan","negosiasi","keuangan","strategi","ekonomi","presentasi","penjualan"},
        // Kedokteran
        {"biologi","kimia","anatomi","medis","kesehatan","farmasi","penelitian","sains","patologi","klinis"},
        // Ilkom
        {"jurnalisme","broadcast","media","menulis","berbicara","konten","berita","podcast","televisi","wawancara"},
        // Sistem Informasi
        {"data","database","sql","erp","jaringan","it","sistem","excel","analisis","teknologi"},
        // Sipil
        {"bangunan","konstruksi","struktur","jembatan","beton","autocad","infrastruktur","arsitektur","surveying","lapangan"},
        // Hukum
        {"debat","argumentasi","keadilan","undang-undang","advokat","politik","analisis","negosiasi","pidana","perdata"},
        // Akuntansi
        {"akuntansi","pajak","audit","neraca","pembukuan","laporan","keuangan","teliti","investasi","excel"},
        // Farmasi
        {"farmasi","obat","laboratorium","molekul","fitokimia","apotek","toksikologi","kimia","klinis","biologi"},
        // Pendidikan
        {"mengajar","anak","pendidikan","kurikulum","belajar","bahasa","kreatif","sabar","komunitas","bermain"},
        // Teknik Mesin
        {"mesin","otomotif","manufaktur","material","thermodinamika","hidrolik","produksi","las","robotika","autocad"},
        // Arsitektur
        {"arsitektur","interior","estetika","ruang","urban","sketchup","desain","menggambar","bangunan","kreatif"},
        // Pertanian
        {"pertanian","tanaman","agro","tanah","benih","pupuk","ekologi","lingkungan","peternakan","pangan"},
        // Keperawatan
        {"perawatan","pasien","sabar","empati","rumah sakit","keperawatan","medis","komunikasi","klinis","kesehatan"},
        // Ekonomi
        {"statistik","makro","mikro","investasi","pasar","kebijakan","perdagangan","pembangunan","riset","data"},
        // Biologi
        {"genetika","evolusi","mikrobiologi","botani","zoologi","konservasi","taksonomi","ekologi","laboratorium","sains"},
        // Teknik Kimia
        {"reaktor","petroleum","polimer","katalis","termodinamika","proses","industri","energi","material","kimia"},
    };

    vector<Pengguna> list;
    list.reserve(jumlah);

    for (int i = 0; i < jumlah; i++) {
        Pengguna p;
        p.id   = i + 1;

        // Nama: ambil dari pool, tambah angka jika habis
        string base_nama = nama_pool[i % nama_pool.size()];
        int siklus = i / (int)nama_pool.size();
        p.nama = (siklus == 0) ? base_nama : base_nama + " " + to_string(siklus + 1);

        // Tentukan kategori utama hobi (berputar di 20 jurusan)
        int kategori_utama  = i % (int)pool_hobi.size();
        int kategori_kedua  = (i + 3) % (int)pool_hobi.size();

        // Pilih 3-5 hobi dari kategori utama + 1-2 dari kategori lain
        vector<string> hobi_terpilih;
        int jml_utama = 3 + (i % 3); // 3, 4, atau 5
        for (int j = 0; j < jml_utama && j < (int)pool_hobi[kategori_utama].size(); j++) {
            hobi_terpilih.push_back(pool_hobi[kategori_utama][j]);
        }
        // Tambah 1-2 hobi dari kategori lain (campuran)
        int extra = i % 2;
        for (int j = 0; j <= extra && j < (int)pool_hobi[kategori_kedua].size(); j++) {
            hobi_terpilih.push_back(pool_hobi[kategori_kedua][j]);
        }

        p.hobi = hobi_terpilih;
        list.push_back(p);
    }

    return list;
}

// ===================== FUNGSI REKOMENDASI =====================

vector<Rekomendasi> hitungRekomendasi(
    const Pengguna& pengguna,
    const vector<Jurusan>& jurusan_list
) {
    vector<Rekomendasi> hasil;
    for (const auto& j : jurusan_list) {
        int skor = 0;
        for (const auto& hobi : pengguna.hobi) {
            auto it = j.bobot_hobi.find(hobi);
            if (it != j.bobot_hobi.end()) skor += it->second;
        }
        hasil.push_back({j.nama, skor});
    }
    sort(hasil.begin(), hasil.end(), [](const Rekomendasi& a, const Rekomendasi& b) {
        return a.skor > b.skor;
    });
    if (hasil.size() > 3) hasil.resize(3);
    return hasil;
}

// ===================== BENCHMARK MULTI-SKENARIO =====================

struct HasilBenchmark {
    int n_pengguna;
    int n_thread;
    double waktu_seq_ms;
    double waktu_par_ms;
    double speedup;
    double efisiensi;
};

HasilBenchmark jalankanBenchmark(
    const vector<Pengguna>& pengguna_list,
    const vector<Jurusan>& jurusan_list,
    int n_thread,
    int runs = 5
) {
    int n = pengguna_list.size();
    omp_set_num_threads(n_thread);

    // --- Ukur PARALEL (median dari 5 run) ---
    vector<double> waktu_par_runs;
    for (int r = 0; r < runs; r++) {
        vector<vector<Rekomendasi>> hasil(n);
        auto t1 = high_resolution_clock::now();
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < n; i++) {
            hasil[i] = hitungRekomendasi(pengguna_list[i], jurusan_list);
        }
        auto t2 = high_resolution_clock::now();
        waktu_par_runs.push_back(duration<double, milli>(t2 - t1).count());
    }
    sort(waktu_par_runs.begin(), waktu_par_runs.end());
    double median_par = waktu_par_runs[runs / 2];

    // --- Ukur SEKUENSIAL (median dari 5 run) ---
    vector<double> waktu_seq_runs;
    for (int r = 0; r < runs; r++) {
        vector<vector<Rekomendasi>> hasil(n);
        auto t3 = high_resolution_clock::now();
        for (int i = 0; i < n; i++) {
            hasil[i] = hitungRekomendasi(pengguna_list[i], jurusan_list);
        }
        auto t4 = high_resolution_clock::now();
        waktu_seq_runs.push_back(duration<double, milli>(t4 - t3).count());
    }
    sort(waktu_seq_runs.begin(), waktu_seq_runs.end());
    double median_seq = waktu_seq_runs[runs / 2];

    double speedup    = (median_par > 0) ? median_seq / median_par : 1.0;
    double efisiensi  = speedup / n_thread * 100.0;

    return { n, n_thread, median_seq, median_par, speedup, efisiensi };
}

// ===================== TAMPILKAN SAMPEL HASIL =====================

void tampilkanSampel(
    const vector<Pengguna>& pengguna_list,
    const vector<vector<Rekomendasi>>& hasil,
    int jumlah_sampel = 100
) {
    cout << "\n===== SAMPEL HASIL (100 PERTAMA) =====" << endl;
    for (int i = 0; i < min(jumlah_sampel, (int)pengguna_list.size()); i++) {
        cout << "\n  [" << pengguna_list[i].id << "] " << pengguna_list[i].nama << endl;
        cout << "  Hobi: ";
        for (int h = 0; h < (int)pengguna_list[i].hobi.size(); h++) {
            cout << pengguna_list[i].hobi[h];
            if (h < (int)pengguna_list[i].hobi.size()-1) cout << ", ";
        }
        cout << endl;
        for (int j = 0; j < (int)hasil[i].size(); j++) {
            cout << "    " << (j+1) << ". " << hasil[i][j].jurusan
                 << " [Skor: " << hasil[i][j].skor << "]" << endl;
        }
    }
}

// ===================== MAIN =====================

int main() {
    cout << "==============================================" << endl;
    cout << "  PARALLELREC v2.0 - Sistem Rekomendasi      " << endl;
    cout << "  Kelompok 10 | Komputasi Paralel C++/OpenMP " << endl;
    cout << "==============================================" << endl;

    auto jurusan_list = buatDatabaseJurusan();
    int max_threads   = omp_get_max_threads();

    cout << "\n  Jumlah jurusan   : " << jurusan_list.size() << endl;
    cout << "  Max thread CPU   : " << max_threads << endl;

    // ============ GENERATE 500 DATA ============
    int TOTAL_DATA = 10000;
    cout << "\n  Generating " << TOTAL_DATA << " data pengguna..." << endl;
    auto pengguna_list = generateDataPengguna(TOTAL_DATA);
    cout << "  Data berhasil di-generate!" << endl;

    // ============ JALANKAN PARALEL (semua thread) ============
    omp_set_num_threads(max_threads);
    vector<vector<Rekomendasi>> hasil_paralel(TOTAL_DATA);
    vector<int> thread_ids(TOTAL_DATA);

    auto t1 = high_resolution_clock::now();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < TOTAL_DATA; i++) {
        thread_ids[i]    = omp_get_thread_num();
        hasil_paralel[i] = hitungRekomendasi(pengguna_list[i], jurusan_list);
    }
    auto t2 = high_resolution_clock::now();
    double waktu_utama = duration<double, milli>(t2 - t1).count();

    // Tampilkan 5 sampel
    tampilkanSampel(pengguna_list, hasil_paralel, 100);

    // ============ BENCHMARK MULTI-SKENARIO ============
    cout << "\n\n==============================================" << endl;
    cout << "  BENCHMARK MULTI-SKENARIO (5 run/config)    " << endl;
    cout << "  Skenario: N=100, 500, 1000 x Thread=1,2,4  " << endl;
    cout << "==============================================" << endl;

    vector<int> skenario_n       = {100, 500, 1000};
    vector<int> skenario_thread  = {1, 2, 4};

    // Header tabel
    cout << "\n"
         << left  << setw(8)  << "N"
         << setw(9)  << "Thread"
         << setw(14) << "T_seq(ms)"
         << setw(14) << "T_par(ms)"
         << setw(12) << "Speedup"
         << setw(12) << "Efisiensi"
         << endl;
    cout << string(69, '-') << endl;

    vector<HasilBenchmark> semua_hasil;

    for (int n_data : skenario_n) {
        auto data_bench = generateDataPengguna(n_data);
        for (int n_th : skenario_thread) {
            auto h = jalankanBenchmark(data_bench, jurusan_list, n_th, 5);
            semua_hasil.push_back(h);

            cout << left
                 << setw(8)  << h.n_pengguna
                 << setw(9)  << h.n_thread
                 << setw(14) << fixed << setprecision(3) << h.waktu_seq_ms
                 << setw(14) << fixed << setprecision(3) << h.waktu_par_ms
                 << setw(12) << fixed << setprecision(3) << h.speedup
                 << setw(11) << fixed << setprecision(1) << h.efisiensi << "%"
                 << endl;
        }
        cout << string(69, '-') << endl;
    }

    // ============ RINGKASAN AKHIR ============
    cout << "\n==============================================" << endl;
    cout << "  RINGKASAN EKSEKUSI UTAMA (500 pengguna)    " << endl;
    cout << "==============================================" << endl;
    cout << "  Total data diproses : " << TOTAL_DATA << " pengguna" << endl;
    cout << "  Jumlah jurusan      : " << jurusan_list.size() << " jurusan" << endl;
    cout << "  Thread digunakan    : " << max_threads << endl;
    cout << "  Waktu paralel       : " << fixed << setprecision(3)
         << waktu_utama << " ms" << endl;
    cout << "==============================================" << endl;

    return 0;
}
