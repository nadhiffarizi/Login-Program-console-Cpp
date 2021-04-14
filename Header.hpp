//Engineer : Muhammad Nadhif Farizi
//Date start/end : 21 Mei 2020/28 Mei 2020
//Deskripsi : Berisi inisialisasi subprograms

#ifndef HEADER_hpp
#define HEADER_hpp
#include <fstream>
#include <iostream>
#include <string>
#include <Cstring>
using namespace std;

//initialize untuk validasi.cpp
bool Validasi(const char *i_U, const char *i_P, fstream &dataBase); //i_U input uname dan i_P input password

bool Register(); //Return True berhasil buat account return false tidak berhasil

bool ForgotPassword(const char *i_U, fstream &dataBase); //Prints Forgot Password di file external lain

void UbahPassword(fstream &dataBase);

#endif