#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <chrono>
#include <omp.h>
 
using namespace std;
using namespace chrono;
 
struct Pengguna {
    int id;
    string nama;
    vector<string> hobi;
};
 
struct Jurusan {
    string nama;
    map<string, int> bobot_hobi; // hobi -> skor bobot
};
 
struct Rekomendasi {
    string jurusan;
    int skor;
};
 
vector<Jurusan> buatDatabaseJurusan() {
    return {
        { "Teknik Informatika", {
            {"coding", 30}, {"pemrograman", 30}, {"logika", 25},
            {"matematika", 20}, {"games", 15}, {"teknologi", 20},
            {"komputer", 25}, {"algoritma", 25}
        }},
        { "Desain Komunikasi Visual", {
            {"menggambar", 30}, {"desain", 30}, {"seni", 25},
            {"fotografi", 20}, {"kreatif", 25}, {"warna", 20},
            {"ilustrasi", 25}, {"animasi", 20}
        }},
        { "Teknik Elektro", {
            {"elektronika", 30}, {"robotika", 30}, {"fisika", 25},
            {"matematika", 20}, {"teknologi", 20}, {"komputer", 15},
            {"mesin", 15}, {"listrik", 25}
        }},
        { "Psikologi", {
            {"sosial", 25}, {"menulis", 20}, {"membaca", 20},
            {"membantu", 30}, {"komunikasi", 25}, {"musik", 10},
            {"seni", 10}, {"konseling", 30}
        }},
        { "Manajemen Bisnis", {
            {"bisnis", 30}, {"komunikasi", 25}, {"sosial", 20},
            {"kepemimpinan", 30}, {"ekonomi", 25}, {"organisasi", 20},
            {"presentasi", 20}, {"negosiasi", 25}
        }},
        { "Kedokteran", {
            {"biologi", 30}, {"kimia", 25}, {"membantu", 25},
            {"membaca", 20}, {"penelitian", 25}, {"sains", 25},
            {"kesehatan", 30}, {"anatomi", 30}
        }},
        { "Ilmu Komunikasi", {
            {"menulis", 30}, {"komunikasi", 30}, {"sosial", 25},
            {"fotografi", 20}, {"presentasi", 25}, {"jurnalisme", 30},
            {"media", 25}, {"berbicara", 25}
        }},
        { "Sistem Informasi", {
            {"komputer", 25}, {"bisnis", 20}, {"coding", 20},
            {"logika", 20}, {"teknologi", 25}, {"data", 30},
            {"analisis", 25}, {"database", 30}
        }},
    };
}
