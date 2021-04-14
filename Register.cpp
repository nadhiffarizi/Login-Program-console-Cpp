//Engineer : Muhammad Nadhif Farizi
//Date start/end : 21 Mei 2020/28 Mei 2020
//Deskripsi : Berisi Fungsi untuk register username dan password, return false kalo tidak berhasil retuen true kalau berhasil

#include "Header.hpp"

bool Register()
{
    //variables
    string inputUsername;
    string inputPassword;
    ofstream dataBase; //buat menulis ke Data Base
    int i = 0;
    bool check = true; //check == false regiter tidak berhasil, check == true register berhasil

//MASUKAN USERNAME
input_username:
    cout << "Masukkan Maksimal 15 Karakter username" << endl;
    cin >> inputUsername;
    //check for error
    i = 0;
    while (inputUsername[i] != '\0')
    {
        i = i + 1;
        if (i >= 15)
        {
            cout << "Username Overload" << endl;
            cout << "\n";
            goto input_username;
        }
    }
    if (inputUsername == "exit")
    {
        //Register Tidak berhasil, keluar ke main menu
        cout << "Register Tidak Behasil" << endl;
        system("CLS");
        check = false;
        return check;
    }

//MASUKAN PASSWORD
input_password:
    cout << "Masukan Password 8 Karakter" << endl;
    cin >> inputPassword;
    //check for error
    i = 0;
    while (inputPassword[i] != '\0')
    {
        i = i + 1;
        if (i > 8)
        {
            cout << "Password Overload" << endl;
            cout << "\n";
            goto input_password;
        }
    }
    if (inputPassword == "exit")
    {
        //Register Tidak berhasil, keluar ke main menu
        cout << "Register Tidak Behasil" << endl;
        system("CLS");
        check = false;
        return check;
    }

    //Validasi apakah account udah ada sebelum register
    fstream checkAccount;
    if (Validasi(inputUsername.c_str(), inputPassword.c_str(), checkAccount) == true)
    {
        check = false;
        cout << "ACCOUNT SUDAH ADA" << endl;
        return check;
    }

    //INTERFACING KE DATA BASE
    dataBase.open("Data Base.txt", ios::out | ios::app);

    //Nulis Username
    i = 0;
    while (inputUsername[i] != '\0' && check == true)
    {
        dataBase << inputUsername[i];
        i = i + 1;
    }
    dataBase << "|";

    //Nulis Password
    i = 0;
    do
    {
        dataBase << inputPassword[i];
        i = i + 1;
    } while (inputPassword[i] != '\0' && check == true);
    dataBase << "|";
    dataBase << endl;
    dataBase.close();
    return check;
}
