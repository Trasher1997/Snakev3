#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <iomanip>
#include "Tmenu.h"
#include <time.h>
#include <stdlib.h>
#include "Ustawienia.h"
#include "Klasy.h"
#define sleep() _sleep();

using namespace std;

void main_menu(), jedno_osobowa(), wielo_osobowa();
void start_gry();
int iloscruchuw = 1;

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

void ustawienia()
{
    TMenu Menu("Opcje");
    Menu.add("Kolor manu (funkcja nie gotowa)", main_menu);
    Menu.add("cofnij", main_menu);
    Menu.view();
} 

void f_exit()
{
    cout << "Program zostanie zamknięty" << endl;
    _sleep(1000);
    system("cls");
    system("color f");
    exit(0);
}

void main_menu()
{
    TMenu Menu("Snake v3");
    Menu.add("Gra jednoosobowa", jedno_osobowa);
    Menu.add("Gra wieloosobowa", wielo_osobowa);
    Menu.add("Opcje", ustawienia);
    Menu.add("Zamknij program", f_exit);
    Menu.view();
} 

//-------------------------start gry----------------
void start_gry()
{
    snake waz1, waz2;
    jedzenie eat;

    do{
        srand(time(NULL));
        waz1.wspxweza = rand() % szerokosc;
        waz1.wspyweza = rand() % wysokosc;
    } while (mapa[waz1.wspxweza][waz1.wspyweza] != 'p');
    mapa[waz1.wspxweza][waz1.wspyweza] = 'w';
    waz1.kierunek = 'p';
    waz1.dlugoscweza = 4;
    waz1.wynik = 0;
    
    do{
         srand(time(NULL));
         eat.wspxjedzenia = rand() % szerokosc;
         eat.wspyjedzenia = rand() % wysokosc;
     } while (mapa[eat.wspxjedzenia][eat.wspyjedzenia] != 'p');
     mapa[eat.wspxjedzenia][eat.wspyjedzenia] = 'j';



    for (;;) // silnik gry
    {
        iloscruchuw++;
        waz1.historiaxweza[iloscruchuw] = waz1.wspxweza;
        waz1.historiayweza[iloscruchuw] = waz1.wspyweza;
        mapa[waz1.wspxweza][waz1.wspyweza] = 'w';

        mapa[waz1.historiaxweza[iloscruchuw - waz1.dlugoscweza]][waz1.historiayweza[iloscruchuw - waz1.dlugoscweza]] = 'p';


        //rysowanie mapy

        idzdoxy(0, 0);

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
            }
            cout << "|";
        }
        cout << endl;
        for (int i = 0; i <= szerokosc; i++)
        {
            cout << "--";
        }
        cout << endl;


        //kierowanie wezem
        if (waz1.kierunek == 'p') waz1.wspxweza++;
        /*if (waz1.kierunek == 'l') waz1.wspxweza--;
        if (waz1.kierunek == 'g') waz1.wspyweza++;
        if (waz1.kierunek == 'd') waz1.wspyweza--;*/

        Sleep(500);
    }
}

int main()
{
    setlocale(LC_ALL, "");
    main_menu();
}
