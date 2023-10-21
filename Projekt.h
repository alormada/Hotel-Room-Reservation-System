#pragma once

#include <iostream>
#include <string>



/*
Struktura formatu daty:
	- miesiac
	- dzien
	- rok
*/
struct Data
{
	int miesiac;
	int dzien;
	int rok;
};

/*
Struktura zawierajaca dane rezerwacji:
	- numer pokoju - liczba naturalna z podanego zakresu < 1 - 999 >
	- maksymalna liczba osob - liczba naturalna z podanego zakresu < 1 - 6 >
	- lazienka - informacja czy w pokoju jest lazienka < prawda/falsz >
	- cena pokoju - cena za jedna dobe hotelowa w pokoju 
	- imie i nazwisko - dane osoby, ktora rezerwuje pokoj - max 256 znakow
	- numer telefonu - liczba naturalna oznaczajaca numer telefonu osoby rezerwujacej pokoj < 100000000 - 999999999 >
	- data zameldowanie - data przyjazdu
	- data wymeldowania - data odjazdu
	- posilki - informacja czy posilki sa wykupione przez osoby rezerwujace < prawda/falsz >
*/
struct DaneRezerwacji
{
	int numer_pokoju;
	int max_liczba_osob;
	bool lazienka;
	float cena_pokoju;
	std::string imie_nazwisko;
	int nr_telefonu;
	Data data_zameldowania;
	Data data_wymeldowania;
	bool posilki;

};
void rozpoczecie_programu(DaneRezerwacji*, int);

void wprowadzanie_daty_zameldowania(DaneRezerwacji*);

void wprowadzanie_daty_wymeldowania(DaneRezerwacji*);

DaneRezerwacji* powiekszanie_liczby_pokoi(DaneRezerwacji*, int*, int*);

void dodanie_pokoju(DaneRezerwacji*, int*, int);

void usuniecie_pokoju(DaneRezerwacji*, int, int);

DaneRezerwacji* wynajecie_pokoju(DaneRezerwacji*);

void anulowanie_wynajecia_pokoju(DaneRezerwacji*);

DaneRezerwacji* zmiana_danych(DaneRezerwacji*, int, int*);

void wyswietlanie_pojedynczego_pokoju(DaneRezerwacji*);

void wyswietlanie_wszystkich_pokoi(DaneRezerwacji*, int);

DaneRezerwacji* wyszukiwanie_pokoju_po_nazwisku(DaneRezerwacji*, int);

DaneRezerwacji* wyszukiwanie_pokoju_po_nazwisku_regex(DaneRezerwacji*, int);

DaneRezerwacji* wyszukiwanie_pokoju_po_numerze(DaneRezerwacji*, int, int*);

DaneRezerwacji* wyszukiwanie_pokoju_po_numerze_regex(DaneRezerwacji*, int, int*);

void zapis_do_pliku(DaneRezerwacji*, int, int, std::string);

DaneRezerwacji* odczyt_z_pliku(DaneRezerwacji*, int*, int*, int*, int*, std::string);