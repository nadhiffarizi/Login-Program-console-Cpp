//Engineer : Muhammad Nadhif Farizi
//Date start/end : 21 Mei 2020/28 Mei 2020
//Deskripsi : Login Interface untuk masuk ke app dengan username dan password, bisa ubah dan forgot password

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring> //untuk mendapatkan syntax dari C style string such as strcmp, pada program ini ga digunain tp gapapa hehe
#include "Header.hpp"
using namespace std;

int main()
{
    //variables 1
    fstream dataBase;
    int i; //buat pencacah aja

    //open file dataBase
    dataBase.open("Data Base.txt", ios::in);

    //Cek apakah ada dataBase
    if (dataBase.fail())
    {
        cout << "MAAF SEDANG MAINTENANCE HUBUNGI ENGINEER" << endl;
        system("PAUSE");
        exit(1); //keluar dari program directly
    }
    else
    {
        char c;
        i = 0;
        while (!dataBase.eof())
        {
            dataBase.get(c);
            if (c == '|')
            {
                i = i + 1;
            }
        }
        if (i < 2)
        { //jumlah | kurang dari 2, tidak ada satupun pasangan password username
            cout << "Silahkan Register" << endl;
            if (Register() == true)
            {
                cout << "Account Baru Sukses dibuat" << endl;
                system("PAUSE");
                system("CLS");
            }
            else
            {
                system("PAUSE");
            }
        }
    }
    //TUTUP dataBase
    dataBase.close();

    //variables 2
    char mode;
    string inputUsername; //jika inputUsername == "exit" maka otomatis keluar program
    string inputPassword; //jika inputPassword == "exit"  maka otomatis keluar program

// MAIN MENU
MainMenu:
    system("CLS");
    cout << "                  MAIN MENU               \n";
    cout << "------------------------------------------\n";
    cout << "1.   Login                                \n";
    cout << "2.   Register                             \n";
    cout << "3.   Forgot Password                      \n";
    cout << "4.   Exit                                 \n";
    cout << "------------------------------------------\n";
    cout << "               Masukan Pilihan            \n";

    cin >> mode;

    if (mode == '1')
    {
    //masukan username dan password, uname maks 15 karakter dan pass maks 10
    //MASUKAN USERNAME
    input_username:
        cout << "Masukkan Maksimal 15 Karakter username" << endl;
        cout << "Silahkan ketik 'exit' untuk keluar dari Program" << endl;
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
            //Bilang makasih lalu keluar program
            cout << "Dank u, vaarwell" << endl;
            system("PAUSE");
            exit(1); //keluar directly dari program
        }

    //MASUKAN PASSWORD
    input_password:
        cout << "Masukan Password 8 Karakter" << endl;
        cout << "Silahkan ketik 'exit' untuk keluar dari Program" << endl;
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
            //Bilang makasih lalu keluar program
            cout << "Dank u, vaarwell" << endl;
            system("PAUSE");
            exit(1);
        }

        //convert string to const char* untuk passing arguments ke Validasi pake c_str()
        //masukan ke subprogram validasi
        if (Validasi(inputUsername.c_str(), inputPassword.c_str(), dataBase) == true)
        {

            cout << "Login Berhasil" << endl;
            system("PAUSE");
        App:
            system("CLS");
            cout << "Welcome" << endl;

            ifstream App;
            App.open("Aplikasi.txt");
            char c;

            while (!App.eof())
            {
                App.get(c);
                if (c == '\n')
                {
                    cout << endl;
                }
                cout << c;
            }

            //OPSI UNTUK NGUBAH PASSWORD
            char j;
            cout << endl;
            cout << endl;
            cout << "1. Untuk Ubah Password" << endl;
            cout << "0. Log Out" << endl;
            cin >> j;
            if (j == '1')
            {
                cout << "Masuk ke Ubah Password" << endl;
                UbahPassword(dataBase);
                system("PAUSE");
                goto App;
            }
            else if (j == '0')
            {
                goto MainMenu;
            }
            else
            {
                goto App;
            }
        }
        else
        {
            cout << "Username atau Password Salah" << endl;
            system("PAUSE");
            goto MainMenu;
        }
    }
    else if (mode == '2')
    { //REGISTER
        cout << "silahkan register" << endl;
        if (Register() == true)
        {
            cout << "berhasil" << endl;
            system("PAUSE");
            system("CLS");
            goto MainMenu;
        }
        else
        {
            cout << "Register Tidak Berhasil" << endl;
            system("PAUSE");
            system("CLS");
            goto MainMenu;
        }
    }

    else if (mode == '3')
    { //FORGOT PASSWORD
    //bACA USERNAME
    //MASUKAN USERNAME
    input_username_forgot:
        cout << "Masukkan Maksimal 15 Karakter username" << endl;
        cout << "Silahkan ketik 'exit' untuk keluar dari Program" << endl;
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
                goto input_username_forgot;
            }
        }
        if (inputUsername == "exit")
        {
            //Bilang makasih lalu keluar program
            cout << "Dank u, vaarwell" << endl;
            system("PAUSE");
            exit(1); //keluar directly dari program
        }

        if (ForgotPassword(inputUsername.c_str(), dataBase) == true)
        {
            cout << "Silahkan Cek Email Untuk Melihat Password Anda" << endl;
            system("PAUSE");
            goto MainMenu;
        }
        else
        {
            cout << "Maaf Tidak ada Account dengan username tersebut" << endl;
            system("PAUSE");
            goto MainMenu;
        }
    }
    else if (mode == '4')
    {
        cout << "Dank u, vaarwell" << endl;
        system("PAUSE");
        exit(1);
    }
    else
    {
        system("CLS");
        goto MainMenu;
    }

    return 0;
} //end

//catetan tentang strcmp
/*Strings are equal
  Value returned by strcmp() is:  0
  Strings are unequal
  Value returned by strcmp() is:  -5
  Strings are unequal
  Value returned by strcmp() is:  19*/
