#pragma once

using namespace std;

//----------definicja klas
class snake
{
public:
	int wspxweza, wspyweza;
	int  dlugoscweza, wynik;
	int historiaxweza[10000], historiayweza[10000];
	char kierunek;
};

class jedzenie
{
public:
	int wspxjedzenia, wspyjedzenia;
	char jedzenie;
};