#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <cstdio>
#include "ksi¹¿ka_adresowa.h"

using namespace std;


vector <Uzytkownik> Uzytkownik::rejestracja (vector <Uzytkownik> uzytkownicy)
{
    string nazwa, haslo;
    Uzytkownik daneUzytkownika;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;

    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik juz istnieje niestety. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;

    daneUzytkownika.nazwa = nazwa;
    daneUzytkownika.haslo = haslo;
    daneUzytkownika.id = przydzielanieNumeruIDUzytkownikowi(uzytkownicy.size() + 1, uzytkownicy);

    uzytkownicy.insert(uzytkownicy.begin() + uzytkownicy.size(), daneUzytkownika);

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    plik << daneUzytkownika.id << "|" << daneUzytkownika.nazwa << "|" << daneUzytkownika.haslo << endl;

    plik.close();

    cout << "Konto zostalo zalozone." << endl;
    Sleep(2000);

    return uzytkownicy;
}


int Uzytkownik::logowanie (vector <Uzytkownik> uzytkownicy)
{
    string nazwa, haslo;
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;


    int i = 0;

    while (i < uzytkownicy.size())
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for (int proby = 0; proby < 3; proby++)
            {
                cout << "Podaj haslo: ";
                cin >> haslo;

                if (uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie, dzien dobry." << endl;
                    Sleep(1500);
                    return uzytkownicy[i].id;
                }
                else if (uzytkownicy[i].haslo != haslo&&proby<=1)
                {
                    cout << "Ups. Masz jeszcze " << 2-proby << " proby. ";
                }
                else if (uzytkownicy[i].haslo != haslo&&proby==2)
                {
                    break;
                }
            }
            cout << "Ajajaj! Podales 3 razy bledne haslo ;( Musisz chwile poczekac na kolejna szanse." << endl;
            Sleep(5000);
            return 0;
        }
        i++;
    }
    cout << "Oj, nie ma uzytkownika o takiej nazwie. Musisz sie zarejestrowac!" << endl;
    Sleep(1500);
    return 0;
}

Uzytkownik::Uzytkownik (int identyfikator, string imie, string pass)
{
    id = identyfikator;
    nazwa = imie;
    haslo = pass;
}

Uzytkownik::~Uzytkownik()
{
    ;
}
