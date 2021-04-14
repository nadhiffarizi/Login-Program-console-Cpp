//Engineer : Muhammad Nadhif Farizi
//Date start/end : 21 Mei 2020/28 Mei 2020
//Deskripsi : Validasi password dan uname

#include "Header.hpp"

using namespace std;

bool Validasi(const char *i_U, const char *i_P, fstream &dataBase)
{ //i_U input uname dan i_P input password
    //variables
    int i;  //pencacah buat username atau password?
    int j;  //buat pencacah member of the array
    char c; //baca character
    bool check;
    bool decision;

    size_t sizeUsername = strlen(i_U);
    size_t sizePassword = strlen(i_P);

    //Cheking. Is the password and usename match with data Base
    i = 0;
    j = 0;
    decision = false;
    check = true;
    dataBase.open("Data Base.txt", ios::in);
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
            if (i == 2 && j < sizePassword)
            {
                check = false;
            }
            j = 0;
        }
        if (c == '\n')
        {

            j = 0;
        }

        if (i == 0 && check == true && c != '|' && c != '\n')
        {
            //cout<<"Masuk";
            if (c == *(i_U + j))
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

        if (i == 1 && check == true && c != '|' && c != '\n')
        {
            if (c == *(i_P + j))
            {
                check = true;
                //cout<<b;
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
            else
            {
                decision = true;
            }
        }
    }
    dataBase.close();
    return decision;
}