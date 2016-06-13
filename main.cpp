#include <stdio.h>
#include <string>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

void Game();
string Character(int, int*);
int Saves();
int ZmianaWartosci(int, int );
int LosowanieStatystyk(int);
int Wczytanie(int zakres);
void SaveCharacter(int*, string);
void Reading(int,int*, int*, string* , string*);
string Rozbijanie(string, int*);
int Ending(string*, int*, int*, string*);
void Scripting( string*, int);
void SprawdzTekst( int* );

int main(int argc, char **argv)
{
	srand(time(NULL));
	Game();
}

void Game()
{
	int n[15]; //0,4,7,10,20,25,35,40,45,47,55,63,67,69,71, ->77
	SprawdzTekst( n );
	string skrypt[ n[15] ];
	Scripting( skrypt, n[15] );
	string stats[] = {"Sila", "Zwinnosc", "Inteligencja", "Health Points", "Szacunek", "Przypal", "Twoj stopien przygotowania do lekcji", "Kasa", "Dzien"};
	int hero[9];
	string name;

	cout << "Czy chcesz wczytac stan gry? 1.Wczytaj / 2.Nowa Postac" << endl;
	if(Wczytanie(2) == 1)
	{
		cout << "Wybierz swoja postac z listy, wpisujac jej numer: " << endl;
		Character( Wczytanie( Saves() ), hero);
	}
	else
		Character( 0, hero);

	for( int end = 0; end == 0; hero[8]++)
	{
		for(int q = 0; q < 7; q++)
		{
			if( q == 6 ) hero[5] = 0;
			Reading( q, n, hero, stats, skrypt);
		}

		end = Ending(stats, hero, n, skrypt);
		cout << endl << Rozbijanie(skrypt[ n[11] ], hero);
		if( hero[8] == 5 ) cout << endl << Rozbijanie(skrypt[ n[12] ], hero);
		if( end == 0 )
		{
			cout << endl << "Czy chcesz zapisac postac? 1.Tak / 2.Nie : ";
			if(Wczytanie(2) == 1) SaveCharacter( hero, name);
		}
	}
}


string Character(int load, int hero[]) 
{	
	if(load == 0)
	{
		string name;
		hero[9] = 1;
		for(int i = 0; i < 2; i++) 			
			hero[i] = LosowanieStatystyk(1);
		cout << endl << "Podaj imie protagonisty: ";
		cin >> name;
		return name;
	}
	else 	
	{
		string namee;
		fstream plik;
		plik.open("save.txt", ios::in);
		/*	if(plik.good() == false)
		{
			cout << "nie udalo sie wczytac pliku 'save.txt'characters" << endl;
			plik.close();
		}

		if(plik.good() != false)
			cout << "udalo sie wczytac plik 'save.txt'characters" << endl; */
		for(int u = 0; u < load; u++ )
			getline( plik, namee );

															// usuniecie zmiennych ze string namea i przypisanie ich jako kolejne statystyki bohatera w hero[]
		return namee;
	}
}

int Saves() // zwraca ilosc zapisanych stanow rozgrywki dla zmiennej zakresu
{
		fstream plik;
		plik.open("save.txt", ios::in);
	/*	if(plik.good() == false)
	{
		cout << "nie udalo sie wczytac pliku 'save.txt'saves" << endl;
		text.close();
	}

	if(plik.good() != false)
		cout << "udalo sie wczytac plik 'save.txt'saves" << endl; */
		int ilosc = -1;
		string linia;
		do{
			ilosc++;
			getline( plik, linia );
			cout << endl << ilosc << ". " << linia;
		}while( linia.length() == 0);
		plik.close();
		return ilosc;
}

int ZmianaWartosci(int parametr, int wartosc)	// parametry nie moga przekroczyc wartosci maksymalnych i minimalnych, wiec ciagle sa kontrolowane
{
	parametr = parametr + wartosc;
	if(parametr > 100) parametr = 100;
	if(parametr < 0) parametr = 0;
	return parametr;
}

int LosowanieStatystyk(int lvl)	//zbedny komentarz
{
	int parametr = lvl * 10 + (rand()%50);
	return parametr;
}

int Wczytanie(int zakres) // wczytywanie liczby z klawiatury w zakresie od zera do podanej zmiennej
{
	int zmienna;
	while(1)
	{
		cin >> zmienna;
		if(zmienna <= zakres && zmienna > 0)
		{
			cout << endl;
			return zmienna;
		}
		else
			cout << " nie ma takiej opcji" << endl;
	}
}

void SaveCharacter(int hero[], string name)	// sprawdzanie czy istnieje postac o zadanym imieniu(jesli tak, to zmienia jej staty/ jesli nie to tworzy kolejny "slot" zapisu, o numer wiekszy od aktualnie najwiekszego(jesli brak slotow > 100, tworzy slot 101))
{											// zrob wzor pliku save.txt
	fstream plik;
	plik.open("save.txt", ios::app);	// ustawienie wskaznika na samym koncu pliku tekstowego - nie dziala?! ios::ate = at end
	plik << endl << name << ",";
	for(int i = 0; i < 9; i++)
		plik << hero[i] << ";";

	plik.close();
}

void Reading(int number,int n[], int hero[], string stats[], string skrypt[]) //jedynie wyciaganie i wypisywanie scenariusza z tabeli oraz edytowanie tablicy hero[] poprzez przekazanie odpowiedniego wiersza do Rozbijanie()
{
	if(number == 0 || number == 2 || number == 4)
	{
		if(number == 0) cout << skrypt[ n[0] + rand() % 4] << endl << skrypt[ n[1] + rand() % 2] << endl;
		else cout << "Podczas kolejnej lekcji postanawiasz: " << endl;
		for(int y = 0; (n[3] - n[2]) >  (y + 1); y++ )
			cout << skrypt[ n[2] + y ] << endl;
		int y = Wczytanie( n[3] - n[2] - 1);

		if( y == 1 )
		{
			int a = rand() % 13;
			cout << endl << Rozbijanie(skrypt[ n[3] + a], hero) << endl;
			if(a < 9 && (rand() % 5 )== 1);
			{
				cout << skrypt[ n[4] + a] << endl;
				if( hero[6] != 0) cout << Rozbijanie(skrypt[ n[11] ], hero) << endl;
				else cout << Rozbijanie(skrypt[ n[11]+1 ], hero) << endl;
			}
		}
		else cout << endl << "Postanawiasz odpoczac podczas tej lekcji" << endl;
	}
	if(number == 1 || number == 3)
	{
		cout << "Co masz zamiar robic podczas przerwy??" << endl;
		for(int y = 0; (n[6] - n[5]) >  (y + 1); y++ )
			cout << skrypt[ n[5] + y ] << endl;
		int y = Wczytanie( n[6] - n[5] - 1);
		cout << endl << Rozbijanie(skrypt[ n[5] + y - 1], hero) << endl;
		if(y == 4 && rand() % 5 == 1) cout << Rozbijanie(skrypt[ n[11]+2 ], hero) << endl;
	}
	if(number == 5 || number == 6)
	{
		cout << skrypt[ n[7] ] << endl;
		for(int y = 0; (n[9] - n[8] ) >  (y + 1); y++ )
			cout << skrypt[ n[2] + y ] << endl;
		int y = Wczytanie( n[9] - n[8] - 1);
		cout << endl << Rozbijanie(skrypt[ n[9] + y - 1], hero) << endl;
		if(y == 4 && rand() % 5 == 1) cout << Rozbijanie(skrypt[ n[11]+2 ], hero) << endl;
	}
}

string Rozbijanie(string tekst, int hero[]) 												// oddaje tekst do wypisania i zmodyfikowane parametry bohatera
{

	return tekst;
}

int Ending(string stats[], int hero[], int n[], string skrypt[]) // sprawdzanie czy nie zostal spelniony jeden z wymogow ukonczenia gry
{
	if( hero[7] >= 100 ){ cout << endl << Rozbijanie( skrypt[ n[14] ], hero ); return 1;}
	if( hero[4] >= 100 ){ cout << endl << Rozbijanie( skrypt[ n[14] + 1 ], hero ); return 1;}
	if( hero[4] <= 0 ){ cout << endl << Rozbijanie( skrypt[ n[14] + 2 ], hero ); return 1;}
	if( hero[5] >= 100 ){ cout << endl << Rozbijanie( skrypt[ n[14] + 3 ], hero ); return 1;}
	if( hero[2] >= 100 ){ cout << endl << Rozbijanie( skrypt[ n[14] + 4], hero ); return 1;}

	cout << "Chcesz zapisac stan rozgrywki? 1.Tak / 2.Nie";
	return 0;
}


void Scripting( string skrypt[], int n) // zamiana tekstu na tablice
{
	fstream text;
	text.open("data.txt", ios::in);
/*	if(text.good() == false)
	{
		cout << "nie udalo sie wczytac pliku 'data.txt'scripting" << endl;
		text.close();
	}

	if(text.good() != false)
		cout << "udalo sie wczytac plik 'data.txt'scripting" << endl; */

	int i = -1;
	do{
		i++;
		getline( text, skrypt[i] );
	}while(i < n);

	text.close();
}

void SprawdzTekst( int n[] ) // podzielenie tekstu na bloki, ktore odpowiadaja konkretnym czynnoscia w ciagu dnia
{
	fstream plik;
	plik.open("data.txt", ios::in);
	n[0] = 0;
	int j = 1;
	string linia[100]; //możnaby zrobic z tego dynamiczna
	/*	if(text.good() == false)
	{
		cout << "nie udalo sie wczytac pliku 'data.txt'sprawdztekst" << endl;
		text.close();
	}

	if(text.good() != false)
		cout << "udalo sie wczytac plik 'data.txt'sprawdztekst" << endl; */

	for(int i = 0; j < 15; i++)
	{
			getline( plik, linia[i] );
			if(linia[i].length() == 0)
			{
				n[j] = i;
				j++;
			}
	}

	plik.close();
}