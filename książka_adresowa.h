#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <cstdio>

using namespace std;

class Uzytkownik
{
    int id;
    string nazwa, haslo;

public:
    Uzytkownik(int = 0, string = "none", string h = "000");
    ~Uzytkownik();

    vector <Uzytkownik> rejestracja(vector <Uzytkownik> uzytkownicy);
    int logowanie (vector <Uzytkownik> uzytkownicy);

    friend int przydzielanieNumeruIDUzytkownikowi (int potencjalnyNumerID, vector <Uzytkownik> dane);
    friend vector <Uzytkownik> zmianaHasla(vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika);
    friend vector <Uzytkownik> daneZPilkuDoWektora(vector <Uzytkownik> uzytkownicy);
};
