#pragma once
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <iomanip>
#include "Function.h"
#define getch() _getch();

using namespace std;
char color = 'g';
void color1(), color2(), green(), blue(), violet(), red(), yellow();

void green()
{
    color = 'g';
    main_menu();
}
void blue()
{
    color = 'b';
    main_menu();
}
void violet()
{
    color = 'v';
    main_menu();
}
void red()
{
    color = 'r';
    main_menu();
}
void yellow()
{
    color = 'y';
    main_menu();
}

void color1()
{
    if (color == 'g') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    if (color == 'b') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    if (color == 'v') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    if (color == 'r') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    if (color == 'y') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
}

void color2()
{
    if (color == 'g' || color == 'b') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
    if (color == 'v') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED);
    if (color == 'r') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    if (color == 'y') SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

class TMenu
{
public:
    TMenu(string _Title);
    TMenu(void);

    void add(string _Name, void (*procedure) ());
    void view();
    void SetTitle(string _Title);


private:
    struct TItem
    {
        string Name;
        void (*procedure)();
    };
    string Title;
    string Max;
    string spac;

    int max;
    int index;

    vector <TItem> List;
};

TMenu::TMenu(string _Title)
{
    Title = _Title;
    max = Title.size() + 4;

    index = 0;
}

void TMenu::add(string Name, void (*procedure) ())
{
    if (Name != "")
    {
        TItem item;
        item.Name = Name;
        item.procedure = procedure;

        List.push_back(item);

        max = (Name.size() + 4 > max) ? Name.size() + 4 : max;

        Max = "";
        spac = "";
        for (int i = 0; i < max; i++)
        {
            Max += '-';
            spac += ' ';
        }
    }
}

void TMenu::view()
{
    char c = '/0';
    do
    {
        system("cls");

        cout << endl;

        color1();
        cout << "  +" << Max << '+' << endl;

        cout << "  |"
            << spac.substr(0, (max - Title.size()) / 2)
            << Title
            << spac.substr(0, max - Title.size() - ((max - Title.size()) / 2))
            << '|' << endl;

        cout << "  +" << Max.substr(0, max) << '+' << endl;

        for (int i = 0; i < List.size(); i++)
        {
            cout << "  |";
            if (i == index)
            {
                color2();
            }
            else
            {
                color1();
            }

            cout << spac.substr(0, (max - List[i].Name.size()) / 2)
                << List[i].Name
                << spac.substr(0, (max - (List[i].Name.size()) - (max - List[i].Name.size()) / 2));

            color1();

            cout << '|' << endl;
        }

        cout << "  +" << Max << "+";

        c = getch();
        if (c == 72 && index > 0) //dol
        {
            index--;
        }

        if (c == 80 && index < List.size() - 1) //gura
        {
            index++;
        }
    } while (c != 13 && c != 27);

    if (c == 27)
    {
        system("exit");
    }

    if (c == 13)
    {
        //cout << index << endl; //80 dol
        system("cls");
        (*List[index].procedure)();
    }
}