#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <cstdio>

using namespace std;

struct DaneZnajomego
{
    string imie, nazwisko, nrTel, email, adres;
    int id, idUzytkownika;
};

int przydzielanieNumeruID (int potencjalnyNumerID, vector <DaneZnajomego> dane)
{
    for (int i = 0; i < dane.size(); i++)
    {
        if (potencjalnyNumerID == dane[i].id)
        {
            potencjalnyNumerID++;
            i = 0;
        }
    }

    return potencjalnyNumerID;
}

void dodawanie (vector <DaneZnajomego> dane, int idZalogowanegoUzytkownika, int liczbaAdresatowWPliku)
{
    DaneZnajomego zestawDanych;

    zestawDanych.id = przydzielanieNumeruID(liczbaAdresatowWPliku, dane);

    cout << "Wprowadz dane znajomego" << endl;
    cout << "-----------------------" << endl;
    cout << "Imie: ";
    cin >> zestawDanych.imie;
    cout << "Nazwisko: ";
    cin >> zestawDanych.nazwisko;
    cout << "Numer telefonu: ";
    cin.sync();
    getline(cin,zestawDanych.nrTel);
    cout << "Email: ";
    cin >> zestawDanych.email;
    cout << "Adres: ";
    cin.sync();
    getline(cin,zestawDanych.adres);

    dane.insert(dane.begin() + dane.size(), zestawDanych);

    fstream plik;
    plik.open("Adresaci.txt", ios::out | ios::app);

    plik << zestawDanych.id << "|" << idZalogowanegoUzytkownika << "|" << zestawDanych.imie << "|";
    plik << zestawDanych.nazwisko << "|" << zestawDanych.nrTel << "|";
    plik << zestawDanych.email << "|" << zestawDanych.adres << "|" << endl;

    plik.close();

    cout << endl;
    cout << "SUKCES! Wlasnie dodano nowego znajomego!" << endl;

    system("pause");
}

void wyswietl_liste(vector <DaneZnajomego> dane)
{
    if (dane.size() != 0)
    {
        cout << "Oto wszystkie kontakty znajdujace sie w Twojej ksiazce:" << endl;

        for (int i = 0; i < dane.size(); i++)
        {
            cout << dane[i].id << "|" << dane[i].idUzytkownika << "|" << dane[i].imie << "|";
            cout << dane[i].nazwisko << "|" << dane[i].nrTel << "|";
            cout << dane[i].email << "|" << dane[i].adres << "|" << endl;
        }
    }

    else if (dane.size() == 0)
    {
        cout << "Brak kontaktow w ksiazce." << endl;
    }

    system("pause");
}


void wyszukajImie (vector <DaneZnajomego> dane)
{
    string imieZnajomego;
    int wskaznik = 0;

    cout << "Podaj imie: ";
    cin >> imieZnajomego;


    for (int i = 0; i < dane.size(); i++)
    {
        if (dane[i].imie == imieZnajomego)
        {
            wskaznik = 1;
        }
    }

    if (wskaznik == 1)
    {
        cout << "Oto osoby o takim imieniu w Twojej ksiazce:" << endl;

        for (int i = 0; i < dane.size(); i++)
        {
            if (dane[i].imie == imieZnajomego)
            {
                cout << dane[i].id << "|" << dane[i].idUzytkownika << "|" << dane[i].imie << "|";
                cout << dane[i].nazwisko << "|" << dane[i].nrTel << "|";
                cout << dane[i].email << "|" << dane[i].adres << "|" << endl;
            }
        }
    }

    if (wskaznik == 0)
    {
        cout << "Brak osoby o takim imieniu na liscie." << endl;
    }

    system("pause");
}

void wyszukajNazwisko (vector <DaneZnajomego> dane)
{
    string nazwiskoZnajomego;
    int wskaznik = 0;

    cout << "Podaj nazwisko: ";
    cin >> nazwiskoZnajomego;


    for (int i = 0; i < dane.size(); i++)
    {
        if (dane[i].nazwisko == nazwiskoZnajomego)
        {
            wskaznik = 1;
        }
    }

    if (wskaznik == 1)
    {
        cout << "Oto osoby o takim nazwisku w Twojej ksiazce:" << endl;

        for (int i = 0; i < dane.size(); i++)
        {
            if (dane[i].nazwisko == nazwiskoZnajomego)
            {
                cout << dane[i].id << "|" << dane[i].idUzytkownika << "|" << dane[i].imie << "|";
                cout << dane[i].nazwisko << "|" << dane[i].nrTel << "|";
                cout << dane[i].email << "|" << dane[i].adres << "|" << endl;
            }
        }
    }

    if (wskaznik == 0)
    {
        cout << "Brak osoby o takim nazwisku na liscie." << endl;
    }

    system("pause");
}


vector <DaneZnajomego> daneZPilkuDoWektora(vector <DaneZnajomego> dane, int idZalogowanegoUzytkownika, int *liczbaAdresatowWPliku)
{
    DaneZnajomego zestawDanych;

    string linia, informacje[7], idZalogowanegoUzytkownikaJakoString = to_string(idZalogowanegoUzytkownika);
    int nr_linii = 1;

    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    while (getline(plik, linia))
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < linia.length(); j++)
            {
                if (linia[j] == '|')
                {
                    informacje[i] = linia.substr(0, j);
                    linia = linia.erase(0, informacje[i].length() + 1);
                    break;
                }
            }
        }

        if (informacje[1] == idZalogowanegoUzytkownikaJakoString)
        {
            zestawDanych.id = atoi(informacje[0].c_str());
            zestawDanych.idUzytkownika = atoi(informacje[1].c_str());
            zestawDanych.imie = informacje[2];
            zestawDanych.nazwisko = informacje[3];
            zestawDanych.nrTel = informacje[4];
            zestawDanych.email = informacje[5];
            zestawDanych.adres = informacje[6];

            dane.insert(dane.begin() + dane.size(), zestawDanych);
        }

        nr_linii++;
    }

    *liczbaAdresatowWPliku = nr_linii;

    plik.close();

    return dane;
}

void przepisywanieDanychZPlikuDoPliku (vector <DaneZnajomego> dane, int nrID, int wskaznikCzyUsuwac)
{
    string linia, nrIDOdczytanyZPliku, nrIDJakoString = to_string(nrID);
    int i = 0;

    fstream plik, plik_tymczasowy;
    plik.open("Adresaci.txt", ios::in);
    plik_tymczasowy.open("Adresaci_tymczasowy.txt", ios::out);

    while (getline(plik, linia))
    {
        for (int i = 0; i < 2; i++)
        {
            if (linia[i] == '|')
            {
                nrIDOdczytanyZPliku = linia.substr(0, i);
                break;
            }
        }


        if (nrIDOdczytanyZPliku == nrIDJakoString && wskaznikCzyUsuwac == 0)
        {
            plik_tymczasowy << dane[nrID - 1].id << "|" << dane[nrID - 1].idUzytkownika << "|" << dane[nrID - 1].imie << "|";
            plik_tymczasowy << dane[nrID - 1].nazwisko << "|" << dane[nrID - 1].nrTel << "|";
            plik_tymczasowy << dane[nrID - 1].email << "|" << dane[nrID - 1].adres << "|" << endl;
        }
        else if (nrIDOdczytanyZPliku == nrIDJakoString && wskaznikCzyUsuwac == 1)
        {
            ;
        }
        else
        {
            plik_tymczasowy << linia << endl;
        }

        i++;
    }

    plik.close();
    plik_tymczasowy.close();

    remove("Adresaci.txt") == 0;

    rename("Adresaci_tymczasowy.txt", "Adresaci.txt");
}

void edycjaDanychZnajomego (vector <DaneZnajomego> dane, char wybor)
{
    DaneZnajomego zestawDanych;

    int nrID, wskaznik = 0;

    cout << "Podaj ID znajomego: ";
    cin >> nrID;


    for (int i = 0; i < dane.size(); i++)
    {
        if (dane[i].id == nrID)
        {
            zestawDanych = dane[i];

            if (wybor == '1')
            {
                cout << "Jakim imieniem zastapic obecne?" << endl;
                cin >> zestawDanych.imie;
            }
            else if (wybor == '2')
            {
                cout << "Jakim nazwiskiem zastapic obecne?" << endl;
                cin >> zestawDanych.nazwisko;
            }
            else if (wybor == '3')
            {
                cout << "Jakim numerem telefonu zastapic obecny?" << endl;
                getline(cin, zestawDanych.nrTel);
            }
            else if (wybor == '4')
            {
                cout << "Jakim emailem zastapic obecny?" << endl;
                cin >> zestawDanych.email;
            }
            else if (wybor == '5')
            {
                cout << "Jakim adresem zastapic obecny?" << endl;
                getline(cin, zestawDanych.adres);
            }

            cout << endl << "Pomyslnie zapisano zmiany." << endl;

            wskaznik = 1;
            dane[i] = zestawDanych;
        }
    }

    if (wskaznik == 0)
    {
        cout << "Nie ma osoby o takim ID w Twojej ksiazce."<< endl;

        system("pause");
    }
    else if(wskaznik == 1)
    {
        przepisywanieDanychZPlikuDoPliku(dane, nrID, 0);
    }
}


void usunZapis (vector <DaneZnajomego> dane)
{
    int wskaznik = 0, idZnajomegoDoUsuniecia;
    char wybor;

    cout << "Podaj ID znajomego: ";
    cin >> idZnajomegoDoUsuniecia;
    cout << endl;

    cout << "Potwierdz swoj wybor naciskajac 't'" << endl;
    cout << "                LUB" << endl;
    cout << "Nacisnij dowolny inny klawisz, aby wrocic do menu." << endl;
    cout << endl;
    cout << "Twoj wybor: ";
    cin >> wybor;

    if(wybor == 't')
    {
        for (int i = 0; i < dane.size(); i++)
        {
            if (dane[i].id == idZnajomegoDoUsuniecia)
            {
                auto iteracja = dane.begin() + i;
                dane.erase(iteracja);
                wskaznik = 1;
                i--;
            }
        }

        przepisywanieDanychZPlikuDoPliku(dane, idZnajomegoDoUsuniecia, 1);

        if (wskaznik == 0)
        {
            cout << "Nie ma osoby o takim ID w Twojej ksiazce." << endl;

            system("pause");
        }
        else
        {
            cout << "Pomyslnie usunieto zapis." << endl;

            system("pause");
        }
    }
    else
    {
        ;
    }
}


struct Uzytkownik
{
    int id;
    string nazwa, haslo;
};

int przydzielanieNumeruIDUzytkownikowi (int potencjalnyNumerID, vector <Uzytkownik> dane)
{
    for (int i = 0; i < dane.size(); i++)
    {
        if (potencjalnyNumerID == dane[i].id)
        {
            potencjalnyNumerID++;
            i = 0;
        }
    }

    return potencjalnyNumerID;
}


vector <Uzytkownik> rejestracja (vector <Uzytkownik> uzytkownicy)
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

int logowanie (vector <Uzytkownik> uzytkownicy)
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

vector <Uzytkownik> zmianaHasla(vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;
    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);


    for (int i = 0; i < uzytkownicy.size(); i++)
    {
        plik << uzytkownicy[i].id << "|" << uzytkownicy[i].nazwa << "|" << uzytkownicy[i].haslo << endl;
    }

    plik.close();

    return uzytkownicy;
}

vector <Uzytkownik> daneZPilkuDoWektora(vector <Uzytkownik> uzytkownicy)
{
    Uzytkownik daneUzytkownika;

    string linia, informacje[3];
    int nr_linii = 1;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    while (getline(plik, linia))
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < linia.length(); j++)
            {
                if (linia[j] == '|')
                {
                    informacje[i] = linia.substr(0, j);
                    linia = linia.erase(0, informacje[i].length() + 1);
                    break;
                }
                else if (j == linia.length() - 1)
                {
                    informacje[i] = linia;
                }
            }
        }

        daneUzytkownika.id = atoi(informacje[0].c_str());
        daneUzytkownika.nazwa = informacje[1];
        daneUzytkownika.haslo = informacje[2];

        uzytkownicy.insert(uzytkownicy.begin() + uzytkownicy.size(), daneUzytkownika);

        nr_linii++;
    }

    plik.close();

    return uzytkownicy;
}


int main()
{

    vector <Uzytkownik> uzytkownicy;
    uzytkownicy = daneZPilkuDoWektora(uzytkownicy);
    int idZalogowanegoUzytkownika = 0;

    char wybor;

    while(1)
    {
        if (idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if (wybor == '1')
            {
                uzytkownicy = rejestracja(uzytkownicy);
            }
            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
            }
            else if (wybor == '9')
            {
                exit(0);
            }
        }
        else
        {
            int liczbaAdresatowWPliku;
            vector <DaneZnajomego> dane;
            dane = daneZPilkuDoWektora(dane, idZalogowanegoUzytkownika, &liczbaAdresatowWPliku);

            system("cls");
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmiana hasla" << endl;
            cout << "8. Wyloguj sie" << endl;
            cout << "Twoj wybor: ";

            cin >> wybor;

            if (wybor == '1')
            {
                dodawanie(dane, idZalogowanegoUzytkownika, liczbaAdresatowWPliku);
            }
            else if (wybor == '2')
            {
                wyszukajImie(dane);
            }
            else if (wybor == '3')
            {
                wyszukajNazwisko(dane);
            }
            else if (wybor == '4')
            {
                wyswietl_liste(dane);
            }
            else if (wybor == '5')
            {
                usunZapis(dane);
            }
            else if (wybor == '6')
            {
                while(1)
                {
                    system("cls");
                    cout << "1 - imie" << endl;
                    cout << "2 - nazwisko" << endl;
                    cout << "3 - numer telefonu" << endl;
                    cout << "4 - email" << endl;
                    cout << "5 - adres" << endl;
                    cout << "6 - powrot do menu" << endl;
                    cout << "Twoj wybor: ";

                    cin >> wybor;

                    cout << endl;

                    if (wybor == '1' || wybor == '2' || wybor == '3' || wybor == '4' || wybor == '5')
                    {
                        edycjaDanychZnajomego(dane, wybor);
                    }
                    else if (wybor == '6')
                    {
                        break;
                    }
                }
            }
            if (wybor == '7')
            {
                uzytkownicy = zmianaHasla(uzytkownicy, idZalogowanegoUzytkownika);
            }
            else if (wybor == '8')
            {
                idZalogowanegoUzytkownika = 0;
            }
        }
    }


    return 0;
}
