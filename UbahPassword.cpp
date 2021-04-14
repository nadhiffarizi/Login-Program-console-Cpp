//Engineer : Muhammad Nadhif Farizi
//Date start/end : 21 Mei 2020/28 Mei 2020
//Deskripsi : mengubah password (using tellg and seekg)

#include "Header.hpp"

void UbahPassword(fstream &dataBase)
{

    //variables
    string inputPassword;
    char c;
    int i, j;
    bool check;

    //Baca tellg() sampe abis file dataBase
    streampos akhirDataBase;
    dataBase.open("Data Base.txt", ios::in | ios::binary);
    while (dataBase.get() != EOF)
    {
        akhirDataBase = dataBase.tellg();
    }
    dataBase.close();

//Baca password
input_password:
    cout << "Masukan Password Lama" << endl;
    cin >> inputPassword;
    //check for Overload
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

    //Panjang Username dan Password
    size_t sizePassword = strlen(inputPassword.c_str());

    //BUKA FILE EXTERNAL DATA BASE
    i = 0;
    j = 0;
    streampos awal;
    streampos akhir;
    check = true;
    bool decision = false;
    dataBase.open("Data Base.txt", ios::in | ios::binary);
    while (!dataBase.eof())
    {
        dataBase.get(c);
        if (c == '|')
        {
            i = i + 1;

            if (i == 1)
            {
                awal = dataBase.tellg();
            }
            if (i == 2 && check == true)
            {
                if (j < sizePassword)
                {
                    check = false;
                }
                else
                {
                    akhir = dataBase.tellg();
                    decision = true;
                    break;
                }
            }

            j = 0;
        }

        if (i == 1 && check == true && c != '|' && c != '\n')
        {
            if (c == inputPassword[j])
            {
                check = true;
                j = j + 1;
            }
            else
            {
                check = false;
                j = 0;
            }
        }

        if (i >= 2)
        {
            i = 0;
            if (check == false)
            {
                check = true;
            }
        }
    }
    dataBase.close();

    if (decision == true)
    {
        //Bikin File baru untuk menampung
        fstream newFile;
        newFile.open("Temp.txt", ios::out | ios::binary);
        newFile.seekp(0, ios_base::beg);
        //Buka file DATA BASE
        dataBase.open("Data Base.txt", ios::in | ios::binary);
        dataBase.seekg(0, ios_base::beg);

        //Tuangkan ke new file dari DATA BASE.txt
        const streamsize length = awal;
        char *buffer = new char[length];
        dataBase.read(buffer, length);
        i = 0;
        for (i = 0; i < awal; i++)
        {
            newFile << buffer[i];
        }
        delete[] buffer;
        newFile.close();

    //input user password baru
    input_password_baru:
        cout << "Masukan Password Baru" << endl;
        cin >> inputPassword;
        //check for Overload
        i = 0;
        while (inputPassword[i] != '\0')
        {
            i = i + 1;
            if (i > 8)
            {
                cout << "Password Overload" << endl;
                cout << "\n";
                goto input_password_baru;
            }
        }

        //Masukin password baru ke file external
        newFile.open("Temp.txt", ios::out | ios::app);
        newFile << inputPassword;
        newFile << "|";
        newFile.close();

        //Tuangkan sisa dari Data Base ke newFile
        newFile.open("Temp.txt", ios::app | ios::binary);
        dataBase.seekg(akhir, ios_base::beg);
        const streamsize length1 = akhirDataBase - akhir - 1;
        buffer = new char[length1];
        dataBase.read(buffer, length1);
        for (i = 0; i < (akhirDataBase - akhir - 1); i++)
        {
            newFile.put(buffer[i]);
            //cout<<buffer[i];
        }
        delete[] buffer;
        newFile.close();
        dataBase.close();

        //Rename file dan delete file
        remove("Data Base.txt");
        rename("Temp.txt", "Data Base.txt");
    }

    else
    {
        goto input_password;
    }
}

//prototypr rename file
//int rename( const char *oldname, const char *newname );