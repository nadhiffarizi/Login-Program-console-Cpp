//Engineer : Muhammad Nadhif Farizi
//Date start/end : 21 Mei 2020/28 Mei 2020
//Deskripsi : Validasi username dan menulis password ke "email.txt"

#include "Header.hpp"

bool ForgotPassword(const char *i_U, fstream &dataBase)
{

    bool check;
    bool decision;
    int i, j;              //i buat pencacah jumlah '|' dan j pencacah buat index array of const(masukan username)
    streampos awal, akhir; //untuk posisi yang diambil pada dataBase.tellg()
    char c;

    //size username
    size_t sizeUsername = strlen(i_U);

    //open data dataBase
    dataBase.open("Data Base.txt", ios::in | ios::binary);
    check = true;
    decision = false;
    i = 0;
    j = 0;
    int k = 0;
    while (!dataBase.eof())
    {
        dataBase.get(c);
        //cout<<c;
        if (c == '|')
        {
            i = i + 1;
            if (i == 1 && j < sizeUsername)
            {
                check = false;
            }
            j = 0;
        }
        if (i == 0 && check == true && c != '|')
        {
            if (c == *(i_U + j))
            {
                check = true;
                j = j + 1;
            }
            else
            {
                check = false;
            }
        }

        if (i == 1 && check == true && c == '|')
        {
            awal = dataBase.tellg();
            decision = true;
        }

        if (i == 2 && check == true && c == '|' && c != '\n')
        {
            akhir = dataBase.tellg();
        }

        if (i >= 2 && c == '\n')
        {
            i = 0;
            check = true;
        }
        k = k + 1;
    }
    dataBase.close();

    if (decision == true)
    {

        //Writes password to mail.txt
        fstream mail;
        string x;
        mail.open("Mail.txt", ios::out);
        mail << "Here's Your password"
             << "\n";
        mail.close();

        //untuk membaca dari point yang ditentukan sebelumnya dan menulis di Mail.txt
        dataBase.open("Data Base.txt", ios::in | ios::binary);
        mail.open("Mail.txt", ios::app | ios::binary);
        dataBase.seekg(awal, ios::beg);

        const streamsize length = akhir - awal - 1;
        char *buffer = new char[length];
        dataBase.read(buffer, length);

        for (i = 0; i < (akhir - awal - 1); i++)
        {
            //cout<<buffer[i];
            mail << buffer[i];
        }

        mail.close();
        dataBase.close();
        delete[] buffer;
    }

    return decision;
}
