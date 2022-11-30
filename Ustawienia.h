#pragma once
#include <iostream>
#include <conio.h>
#include "Function.h"
#include "Klasy.h"


int szerokosc, wysokosc;
int gora, dol, lewo, prawo, gora2, dol2, lewo2, prawo2;
char wieloosobowa, mapa[31][31], przenikanie = 'n';
int wynik1, wynik2;


void idzdoxy(int x, int y)//funkcja przenoszaca kursor w wybrane pozycje
{
    HANDLE pozycja;
    COORD poz;

    poz.X = x;
    poz.Y = y;

    pozycja = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(pozycja, poz);
}

void losowy_wymiar(int& x) // generowanie losowego rozmiaru mapy
{
    cout << "\tWpisales wartosc poza zakresem, sproboj jeszcze raz";
    cin >> x;
    if (x < 10 || x > 30)
    {
        srand(time(nullptr));
        x = rand() % (30 - 11) + 11;
        cout << "\tZnow zle, zrobilem to za ciebie\n";
    }
}

void wymiar_planszy() // podajemy wymiary mapy
{
    cout << "\n\n\tPodaj szerokosc planszy w zakresie od 10 do 30 ";
    cin >> szerokosc;
    if (szerokosc < 10 || szerokosc > 30) losowy_wymiar(szerokosc);

    cout << "\tPodaj wysokosc mapy w zaksesie od 10 do 30 ";
    cin >> wysokosc;
    if (wysokosc < 10 || wysokosc > 30)
    {
        losowy_wymiar(wysokosc);
        Sleep(1000);
    }
    zapisano_dane_mapy();
}

void zapisano_dane_mapy()
{
    system("cls");
    cout << "\n\n\tTwoje dane zosta³y zapisane\n";
    cout << "\tSzerokosc mapy wynosi " << szerokosc << endl;
    cout << "\tWysokosc mapy wynosi " << wysokosc << endl;
    pustamapa();
    Sleep(1500);
    if (wieloosobowa == 'n') jedno_osobowa();
    if (wieloosobowa == 't') wielo_osobowa();
}

void pustamapa() // mapa jako pusta tablica
{
    for (int i = 0; i < szerokosc; i++)
    {
        for (int j = 0; j <= wysokosc; j++)
            mapa[j][i] = 'p';
    }
}

void food()
{
    int wspxfood, wspyfood;
    do {
        srand(time(nullptr));
        wspxfood = rand() % szerokosc;
        wspyfood = rand() % wysokosc;
    } while (mapa[wspxfood][wspyfood] != 'p');
    mapa[wspxfood][wspyfood] = 'j';
}

void wall_penetrate()
{
    char response;
    cout << "\n\tCzy chcesz w³¹czyc przenikanie przez sciany? t/n? " << endl;
    cin >> response;
    if (response == 't') przenikanie = 't';
    if (response == 'n') przenikanie = 'n';
    ustawienia();
}

void lose()
{
    if (wieloosobowa == 't') cout << "\n\tWygrywa gracz 2 z wynikiem " << wynik2 << endl;
    else cout << "\n\tPrzegrales, twoj wynik to " << wynik1 << endl;
    Sleep(2000);
    pustamapa();
    main_menu();
}
void lose2()
{
    cout << "\n\tWygrywa gracz 1 z wynikiem " << wynik1 << endl;
    Sleep(2000);
    pustamapa();
    main_menu();
}

void score()
{
    if (wieloosobowa == 't')
    {
        cout << "\t Aktualny wynik Gracza 1 - " << wynik1 << endl;
        cout << "\t Aktualny wynik Gracza 2 - " << wynik2 << endl;
    }
    else cout << "\tTwoj aktualny wynik to - " << wynik1 << endl;
}

void sterowanie() // sterowanie
{
    system("cls");
    cout << "\n\n\tPodaj klawisze którymi chces sterowac\n";

    cout << "\tGORA\n";
    gora = getch();
    if (gora == 224) gora = gora + getch();
    if (gora == 0) gora = gora - getch();

    cout << "\tDOL\n";
    dol = getch();
    if (dol == 224) dol = dol + getch();
    if (dol == 0) dol = dol - getch();

    cout << "\tLEWO\n";
    lewo = getch();
    if (lewo == 224) lewo = lewo + getch();
    if (lewo == 0) lewo = lewo + getch();

    cout << "\tPRAWO\n";
    prawo = getch();
    if (prawo == 224) prawo = prawo + getch();
    if (prawo == 0) prawo = prawo - getch();

    cout << "\tTwoje klawisze zostaly zapisane\n";
    Sleep(1000);
    if (wieloosobowa == 'n') jedno_osobowa();
    if (wieloosobowa == 't') wielo_osobowa();
}

void sterowanie2()
{
    system("cls");
    cout << "\n\n\tPodaj klawisze gtorymi bedzie sterowac gracz 2\n";

    cout << "\tGORA\n";
    gora2 = getch();
    if (gora2 == 224) gora2 = gora2 + getch();
    if (gora2 == 0) gora2 = gora2 - getch();

    cout << "\tDOL\n";
    dol2 = getch();
    if (dol2 == 224) dol2 = dol2 + getch();
    if (dol2 == 0) dol2 = dol2 - getch();

    cout << "\tLEWO\n";
    lewo2 = getch();
    if (lewo2 == 224) lewo2 = lewo2 + getch();
    if (lewo2 == 0) lewo2 = lewo2 + getch();

    cout << "\tPRAWO\n";
    prawo2 = getch();
    if (prawo2 == 224) prawo2 = prawo2 + getch();
    if (prawo2 == 0) prawo2 = prawo2 - getch();

    cout << "\tTwoje klawisze zostaly zapisane\n";
    Sleep(1000);
    wielo_osobowa();
}

void show_settings()
{
    cout << "\n\tRozmiar planszy wynosi " << wysokosc << " x " << szerokosc << endl;
    if (wieloosobowa == 't') cout << "\n\tUstawiono tryb wieloosobowy" << endl;
    else cout << "\n\tUstawiono tryb jednoosobowy" << endl;

    if (gora == 0 && (dol == 0)) cout << "\n\tNie ustawiono klawiszy sterowania gracza 1" << endl;
    else cout << "\n\tKlawisze sterowania gracza 1 s¹ ustawione" << endl;

    if (gora2 == 0 && (dol2 == 0)) cout << "\n\tNie ustawiono klawiszy sterowania gracza 2" << endl;
    else cout << "\n\tKlawisze sterowania gracza 2" << endl;
    Sleep(2000);
    ustawienia();
}

bool check_value()
{
    if (gora == 0 && (dol == 0))
    {
        cout << "\n\tNie wybrales klawiszy sterowania gracza 1" << endl;
        Sleep(2000);
        main_menu();
    }
    if (wieloosobowa == 't' && (gora2 == 0 && dol2 == 0))
    {
        cout << "\n\tNie wybrales kawiszy sterowania gracza 2" << endl;
        Sleep(2000);
        main_menu();
    }
    return 0;
}

bool check_map()
{
    if (mapa[2][2] == 'p')
    {
        cout << "\n\tWszystkie wartosci sa prawidlowe" << endl;
        Sleep(800);
    }
    else {
        cout << "\n\tNie podales rozmiaru mapy" << endl;
        f_exit();
    }
    return 0;
}