//============================================================================
// Name        : Snake
// Author      : Marek L.
// Version     : v3
// Copyright   : Personal
// IDE         : Microsoft Visual Studio 2022
// Description : Simple, easy game
//============================================================================
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>
#include "Tmenu.h"
#include "Ustawienia.h"
#include "Klasy.h"
#include "Function.h"

using namespace std;

int iloscruchuw = 0, klawisz;

//------------------------------------- Początek Menu------------------------------------------------------
void jedno_osobowa()
{
    wieloosobowa = 'n';
    TMenu Menu("Gra jednoosobowa");
    Menu.add("Rozmiar planszy", wymiar_planszy);
    Menu.add("Sterowanie", sterowanie);
    Menu.add("Start", start_gry);
    Menu.add("Cofnij", main_menu);
    Menu.view();
}

void wielo_osobowa()
{
    wieloosobowa = 't';
    TMenu Menu("Gra wieloosobowa");
    Menu.add("Rozmiar planszy", wymiar_planszy);
    Menu.add("Sterowanie Gracza 1", sterowanie);
    Menu.add("Sterowanie Gracza 2", sterowanie2);
    Menu.add("Start", start_gry);
    Menu.add("Cofnij", main_menu);
    Menu.view();
}

void menu_color()
{
    TMenu Menu("Wybierz kolor menu");
    Menu.add("Zielony", green);
    Menu.add("Niebieski", blue);
    Menu.add("Fioletowy", violet);
    Menu.add("Czerwony", red);
    Menu.add("Żółty", yellow);
    Menu.add("Cofnij", ustawienia);
    Menu.view();
}
void ustawienia()
{
    TMenu Menu("Opcje");
    Menu.add("Kolor menu", menu_color);
    Menu.add("Wyświetl ustawienia", show_settings);
    Menu.add("Przechodzenie przez ściany", wall_penetrate);
    Menu.add("cofnij", main_menu);
    Menu.view();
}

void f_exit()
{
    cout << "Program zostanie zamknięty" << endl;
    Sleep(2000);
    system("cls");
    system("color f");
    exit(0);
}

void main_menu()
{
    TMenu Menu("Snake Created by Marek.L ");
    Menu.add("Gra jednoosobowa", jedno_osobowa);
    Menu.add("Gra wieloosobowa", wielo_osobowa);
    Menu.add("Opcje", ustawienia);
    Menu.add("Zamknij program", f_exit);
    Menu.view();
}

//-------------------------start gry----------------
void start_gry()
{
    check_map();
    check_value();
    system("cls");
    snake waz1, waz2;

    do {
        srand(time(nullptr));
        waz1.wspxweza = rand() % szerokosc;
        waz1.wspyweza = rand() % wysokosc;
    } while (mapa[waz1.wspxweza][waz1.wspyweza] != 'p');
    mapa[waz1.wspxweza][waz1.wspyweza] = 'w';
    waz1.kierunek = 'p';
    waz1.dlugoscweza = 4;
    waz1.wynik = wynik1;
    wynik1 = 0;

    if (wieloosobowa == 't')
    {
        do {
            srand(time(nullptr));
            waz2.wspxweza = rand() % szerokosc;
            waz2.wspyweza = rand() % wysokosc;
        } while (mapa[waz2.wspxweza][waz2.wspyweza] != 'p');
        mapa[waz2.wspxweza][waz2.wspyweza] = 'e';
        waz2.kierunek = 'l';
        waz2.dlugoscweza = 4;
        waz2.wynik = wynik2;
        wynik2 = 0;
    }

    food();

    while (true) // silnik gry
    {
        iloscruchuw++;
        waz1.historiaxweza[iloscruchuw] = waz1.wspxweza;
        waz1.historiayweza[iloscruchuw] = waz1.wspyweza;
        mapa[waz1.wspxweza][waz1.wspyweza] = 'w';
        mapa[waz1.historiaxweza[iloscruchuw - waz1.dlugoscweza]][waz1.historiayweza[iloscruchuw - waz1.dlugoscweza]] = 'p';

        if (wieloosobowa == 't')
        {
            waz2.historiaxweza[iloscruchuw] = waz2.wspxweza;
            waz2.historiayweza[iloscruchuw] = waz2.wspyweza;
            mapa[waz2.wspxweza][waz2.wspyweza] = 'e';
            mapa[waz2.historiaxweza[iloscruchuw - waz2.dlugoscweza]][waz2.historiayweza[iloscruchuw - waz2.dlugoscweza]] = 'p';
        }


        //rysowanie mapy
        idzdoxy(0, 0);
        score();
        for (int i = 0; i <= szerokosc; i++)
        {
            cout << "--";
        }

        for (int i = 0; i < wysokosc; i++)
        {
            cout << endl << "|";
            for (int j = 0; j < szerokosc; j++)
            {
                if (mapa[j][i] == 'p') cout << "  ";
                if (mapa[j][i] == 'w') cout << "xx";
                if (mapa[j][i] == 'j') cout << " j";
                if (mapa[j][i] == 'e') cout << "ee";
            }
            cout << "|";
        }
        cout << endl;
        for (int i = 0; i <= szerokosc; i++)
        {
            cout << "--";
        }
        cout << endl;

        //wartości sterowania
        if (_kbhit())
        {
            klawisz = getch();
            if (klawisz == 224) klawisz = klawisz + getch();
            if (klawisz == 0) klawisz = klawisz - getch();

            if (klawisz == gora && (waz1.kierunek == 'l' || waz1.kierunek == 'p')) waz1.kierunek = 'g';
            if (klawisz == dol && (waz1.kierunek == 'l' || waz1.kierunek == 'p')) waz1.kierunek = 'd';
            if (klawisz == lewo && (waz1.kierunek == 'g' || waz1.kierunek == 'd')) waz1.kierunek = 'l';
            if (klawisz == prawo && (waz1.kierunek == 'g' || waz1.kierunek == 'd')) waz1.kierunek = 'p';

            if (wieloosobowa == 't')
            {
                if (klawisz == gora2 && (waz2.kierunek == 'l' || waz2.kierunek == 'p')) waz2.kierunek = 'g';
                if (klawisz == dol2 && (waz2.kierunek == 'l' || waz2.kierunek == 'p')) waz2.kierunek = 'd';
                if (klawisz == lewo2 && (waz2.kierunek == 'g' || waz2.kierunek == 'd')) waz2.kierunek = 'l';
                if (klawisz == prawo2 && (waz2.kierunek == 'g' || waz2.kierunek == 'd')) waz2.kierunek = 'p';
            }
        }

        //ruch węża
        if (waz1.kierunek == 'p') waz1.wspxweza++;
        if (waz1.kierunek == 'l') waz1.wspxweza--;
        if (waz1.kierunek == 'd') waz1.wspyweza++;
        if (waz1.kierunek == 'g') waz1.wspyweza--;

        if (wieloosobowa == 't')
        {
            if (waz2.kierunek == 'p') waz2.wspxweza++;
            if (waz2.kierunek == 'l') waz2.wspxweza--;
            if (waz2.kierunek == 'd') waz2.wspyweza++;
            if (waz2.kierunek == 'g') waz2.wspyweza--;
        }

        //jedzenie wezy
        if (mapa[waz1.wspxweza][waz1.wspyweza] == 'j')
        {
            wynik1++;
            waz1.dlugoscweza++;
            food();
        }
        if (mapa[waz2.wspxweza][waz2.wspyweza] == 'j')
        {
            wynik2++;
            waz2.dlugoscweza++;
            food();
        }

        //przechodzenie wezy przez sciane i warunki przegranych
        if (przenikanie == 't')
        {
            if (waz1.wspxweza == szerokosc) waz1.wspxweza = 0;
            if (waz1.wspxweza == -1) waz1.wspxweza = szerokosc;
            if (waz1.wspyweza == wysokosc) waz1.wspyweza = 0;
            if (waz1.wspyweza == -1) waz1.wspyweza = wysokosc;
            if (wieloosobowa == 't')
            {
                if (waz2.wspxweza == szerokosc) waz2.wspxweza = 0;
                if (waz2.wspxweza == -1) waz2.wspxweza = szerokosc;
                if (waz2.wspyweza == wysokosc) waz2.wspyweza = 0;
                if (waz2.wspyweza == -1) waz2.wspyweza = wysokosc;
            }
        }
        else
        {
            if (waz1.wspxweza == szerokosc + 1) lose();
            if (waz1.wspxweza == -2) lose();
            if (waz1.wspyweza == wysokosc + 1) lose();
            if (waz1.wspyweza == -2) lose();
            if (wieloosobowa == 't')
            {
                if (waz2.wspxweza == szerokosc + 1) lose2();
                if (waz2.wspxweza == -2) lose2();
                if (waz2.wspyweza == wysokosc + 1) lose2();
                if (waz2.wspyweza == -2) lose2();
            }
        }
        if (mapa[waz1.wspxweza][waz1.wspyweza] == 'w' || mapa[waz1.wspxweza][waz1.wspyweza] == 'e') lose();
        if (mapa[waz2.wspxweza][waz2.wspyweza] == 'w' || mapa[waz2.wspxweza][waz2.wspyweza] == 'e') lose2();

        Sleep(300);
    }
}

int main()
{
    setlocale(LC_ALL, "");
    main_menu();
}
