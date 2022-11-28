#pragma once
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <windows.h>
#include <iomanip>
#define getch() _getch();

using namespace std;

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

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
            FOREGROUND_GREEN | FOREGROUND_INTENSITY);
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
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }

            cout << spac.substr(0, (max - List[i].Name.size()) / 2)
                << List[i].Name
                << spac.substr(0, (max - (List[i].Name.size()) - (max - List[i].Name.size()) / 2));

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                FOREGROUND_GREEN | FOREGROUND_INTENSITY);

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