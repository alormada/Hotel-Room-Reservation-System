#include <iostream>
#include <string>
#include "Projekt.h"
#include <fstream>
#include <regex>


using namespace std;

/*
Funkcja zamieniajaca pola elementow tablicy na puste (zerowe):
	- tablica - tablica przechowujaca elementy typu DaneRezerwacji
	- liczba_pokoi - aktualna liczba wszystkich pokoi
*/
void rozpoczecie_programu(DaneRezerwacji* tablica, int liczba_pokoi)
{
	for (int i = 0; i < liczba_pokoi; i++)
	{
		(tablica + i)->numer_pokoju = NULL;
		(tablica + i)->max_liczba_osob = NULL;
		(tablica + i)->lazienka = 0;
		(tablica + i)->cena_pokoju = NULL;
		(tablica + i)->imie_nazwisko.clear();
		(tablica + i)->nr_telefonu = NULL;
		(tablica + i)->data_zameldowania.miesiac = NULL;
		(tablica + i)->data_zameldowania.dzien = NULL;
		(tablica + i)->data_zameldowania.rok = NULL;
		(tablica + i)->data_wymeldowania.miesiac = NULL;
		(tablica + i)->data_wymeldowania.dzien = NULL;
		(tablica + i)->data_wymeldowania.rok = NULL;
		(tablica + i)->posilki = 0;
	}
}

// Funkcja do wprowadzania daty zameldowania i sprawdzajaca poprawnosc wpisywanych danych dla podanego w argumencie pokoju
void wprowadzanie_daty_zameldowania(DaneRezerwacji* pokoj)
{
	int petla = 1;
	int rok;
	int miesiac;
	int dzien;

	// Wprowadzanie prawidlowego roku w dacie zameldowania
	
	cout << "| Podaj date zameldowania:\n| -rok: ";
	while ((!(cin >> rok)) || rok < 2023)
	{
		cout << "!!! Nieprawidlowa wartosc !!! Podaj jescze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	

	pokoj->data_zameldowania.rok = rok;

	// Wprowadzanie prawidlowego miesiaca w dacie zameldowania

	cout << "| -miesiac: ";
	while ((!(cin >> miesiac)) || miesiac < 1 || miesiac > 12)
	{
		cout << "!!! Nieprawidlowa wartosc !!! Podaj jescze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	pokoj->data_zameldowania.miesiac = miesiac;
	
	// Wprowadzanie prawidlowego dnia w dacie zameldowania

	cout << "| -dzien: ";
	while (petla != 0)
	{
		while (!(cin >> dzien))
		{
			cout << "!!! Nieprawidlowa wartosc !!! Podaj jescze raz: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		// Poprawnosc dnia miesiecy liczacych 31 dni
		if (pokoj->data_zameldowania.miesiac == 1 || pokoj->data_zameldowania.miesiac == 3 || pokoj->data_zameldowania.miesiac == 5 || pokoj->data_zameldowania.miesiac == 7 || pokoj->data_zameldowania.miesiac == 8 || pokoj->data_zameldowania.miesiac == 10 || pokoj->data_zameldowania.miesiac == 12)
		{
			if (dzien >= 1 && dzien <= 31)
			{
				petla = 0;
			}
		}
		// Poprawnosc dnia miesiecy liczacych 30 dni
		else if (pokoj->data_zameldowania.miesiac == 4 || pokoj->data_zameldowania.miesiac == 6 || pokoj->data_zameldowania.miesiac == 9 || pokoj->data_zameldowania.miesiac == 11)
		{
			if (dzien >= 1 && dzien <= 30)
			{
				petla = 0;
			}
		}
		// Poprawnosc dnia lutego z uwzglednieniem lat przestepnych
		else if (pokoj->data_zameldowania.miesiac == 2)
		{
			if (pokoj->data_zameldowania.rok % 100 == 0)
			{
				if (pokoj->data_zameldowania.rok % 400 == 0)
				{
					if (dzien >= 1 && dzien <= 29)
					{
						petla = 0;
					}
				}
				else
				{
					if (dzien >= 1 && dzien <= 28)
					{
						petla = 0;
					}
				}
			}
			else
			{
				if (pokoj->data_zameldowania.rok % 4 == 0)
				{
					if (dzien >= 1 && dzien <= 29)
					{
						petla = 0;
					}
				}
				else
				{
					if (dzien >= 1 && dzien <= 28)
					{
						petla = 0;
					}
				}
			}
			
		}
		if (petla != 0)
			cout << "!!! Nieprawidlowa wartosc !!! Podaj jescze raz: ";
	}
	pokoj->data_zameldowania.dzien = dzien;

}

// Funkcja do wprowadzania daty wymeldowania i sprawdzajaca poprawnosc wpisywanych danych dla podanego w argumencie pokoju
void wprowadzanie_daty_wymeldowania(DaneRezerwacji* pokoj)
{
	int petla = 1;
	int rok;
	int miesiac;
	int dzien;

	// Wprowadzanie prawidlowego roku w dacie wymeldowania

	cout << "| Podaj date wymeldowania:\n| -rok: ";
	while ((!(cin >> rok)) || rok < 2023 || rok < pokoj->data_zameldowania.rok)
	{
		cout << "!!! Nieprawidlowa wartosc !!! Podaj jescze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}


	pokoj->data_wymeldowania.rok = rok;

	// Wprowadzanie prawidlowego miesiaca w dacie wymeldowania

	cout << "| -miesiac: ";
	while ((!(cin >> miesiac)) || miesiac < 1 || miesiac > 12 || ((pokoj->data_wymeldowania.rok == pokoj->data_zameldowania.rok) && miesiac < pokoj->data_zameldowania.miesiac))
	{
		cout << "!!! Nieprawidlowa wartosc !!! Podaj jescze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	pokoj->data_wymeldowania.miesiac = miesiac;

	// Wprowadzanie prawidlowego dnia w dacie wymeldowania

	cout << "| -dzien: ";
	while (petla != 0)
	{
		while (!(cin >> dzien))
		{
			cout << "!!! Nieprawidlowa wartosc !!! Podaj jescze raz: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		// Poprawnosc dnia miesiecy liczacych 31 dni
		if (pokoj->data_wymeldowania.miesiac == 1 || pokoj->data_wymeldowania.miesiac == 3 || pokoj->data_wymeldowania.miesiac == 5 || pokoj->data_wymeldowania.miesiac == 7 || pokoj->data_wymeldowania.miesiac == 8 || pokoj->data_wymeldowania.miesiac == 10 || pokoj->data_wymeldowania.miesiac == 12)
		{
			if (pokoj->data_zameldowania.rok == pokoj->data_wymeldowania.rok)
			{
				if (pokoj->data_zameldowania.miesiac == pokoj->data_wymeldowania.miesiac)
				{
					if (dzien < pokoj->data_zameldowania.dzien)
					{
						if (dzien >= 1 && dzien <= 31)
						{
							petla = 0;
						}
					}
					
				}
				else
				{
					if (dzien < pokoj->data_zameldowania.dzien)
					{
						if (dzien >= 1 && dzien <= 31)
						{
							petla = 0;
						}
					}
				}
			}
			else
			{
				if (dzien < pokoj->data_zameldowania.dzien)
				{
					if (dzien >= 1 && dzien <= 31)
					{
						petla = 0;
					}
				}
			}
			
		}
		// Poprawnosc dnia miesiecy liczacych 30 dni
		else if (pokoj->data_wymeldowania.miesiac == 4 || pokoj->data_wymeldowania.miesiac == 6 || pokoj->data_wymeldowania.miesiac == 9 || pokoj->data_wymeldowania.miesiac == 11)
		{
			if (pokoj->data_zameldowania.rok == pokoj->data_wymeldowania.rok)
			{
				if (pokoj->data_zameldowania.miesiac == pokoj->data_wymeldowania.miesiac)
				{
					if (dzien < pokoj->data_zameldowania.dzien)
					{
						if (dzien >= 1 && dzien <= 30)
						{
							petla = 0;
						}
					}

				}
				else
				{
					if (dzien < pokoj->data_zameldowania.dzien)
					{
						if (dzien >= 1 && dzien <= 30)
						{
							petla = 0;
						}
					}
				}
			}
			else
			{
				if (dzien < pokoj->data_zameldowania.dzien)
				{
					if (dzien >= 1 && dzien <= 30)
					{
						petla = 0;
					}
				}
			}
		}
		// Poprawnosc dnia lutego z uwzglednieniem lat przestepnych
		else if (pokoj->data_wymeldowania.miesiac == 2)
		{
			if (pokoj->data_wymeldowania.rok % 100 == 0)
			{
				if (pokoj->data_wymeldowania.rok % 400 == 0)
				{
					if (pokoj->data_zameldowania.rok == pokoj->data_wymeldowania.rok)
					{
						if (pokoj->data_zameldowania.miesiac == pokoj->data_wymeldowania.miesiac)
						{
							if (dzien < pokoj->data_zameldowania.dzien)
							{
								if (dzien >= 1 && dzien <= 29)
								{
									petla = 0;
								}
							}

						}
						else
						{
							if (dzien < pokoj->data_zameldowania.dzien)
							{
								if (dzien >= 1 && dzien <= 29)
								{
									petla = 0;
								}
							}
						}
					}
					else
					{
						if (dzien < pokoj->data_zameldowania.dzien)
						{
							if (dzien >= 1 && dzien <= 29)
							{
								petla = 0;
							}
						}
					}
				}
				else
				{
					if (pokoj->data_zameldowania.rok == pokoj->data_wymeldowania.rok)
					{
						if (pokoj->data_zameldowania.miesiac == pokoj->data_wymeldowania.miesiac)
						{
							if (dzien < pokoj->data_zameldowania.dzien)
							{
								if (dzien >= 1 && dzien <= 28)
								{
									petla = 0;
								}
							}

						}
						else
						{
							if (dzien < pokoj->data_zameldowania.dzien)
							{
								if (dzien >= 1 && dzien <= 28)
								{
									petla = 0;
								}
							}
						}
					}
					else
					{
						if (dzien < pokoj->data_zameldowania.dzien)
						{
							if (dzien >= 1 && dzien <= 28)
							{
								petla = 0;
							}
						}
					}
				}
			}
			else
			{
				if (pokoj->data_wymeldowania.rok % 4 == 0)
				{
					if (pokoj->data_zameldowania.rok == pokoj->data_wymeldowania.rok)
					{
						if (pokoj->data_zameldowania.miesiac == pokoj->data_wymeldowania.miesiac)
						{
							if (dzien < pokoj->data_zameldowania.dzien)
							{
								if (dzien >= 1 && dzien <= 29)
								{
									petla = 0;
								}
							}

						}
						else
						{
							if (dzien < pokoj->data_zameldowania.dzien)
							{
								if (dzien >= 1 && dzien <= 29)
								{
									petla = 0;
								}
							}
						}
					}
					else
					{
						if (dzien < pokoj->data_zameldowania.dzien)
						{
							if (dzien >= 1 && dzien <= 29)
							{
								petla = 0;
							}
						}
					}
				}
				else
				{
					if (pokoj->data_zameldowania.rok == pokoj->data_wymeldowania.rok)
					{
						if (pokoj->data_zameldowania.miesiac == pokoj->data_wymeldowania.miesiac)
						{
							if (dzien < pokoj->data_zameldowania.dzien)
							{
								if (dzien >= 1 && dzien <= 28)
								{
									petla = 0;
								}
							}

						}
						else
						{
							if (dzien < pokoj->data_zameldowania.dzien)
							{
								if (dzien >= 1 && dzien <= 28)
								{
									petla = 0;
								}
							}
						}
					}
					else
					{
						if (dzien < pokoj->data_zameldowania.dzien)
						{
							if (dzien >= 1 && dzien <= 28)
							{
								petla = 0;
							}
						}
					}
				}
			}
			
		}
		if (petla != 0)
			cout << "!!! Nieprawidlowa wartosc !!! Podaj jescze raz: ";
	}
	pokoj->data_wymeldowania.dzien = dzien;
	
}

/*
Funkcja powiekszajaca liczbe pokoi:
	- tablica - tablica zawierajaca obiekty struktury DaneRezerwacji
	- liczba_pokoi - rozmiar tablicy
	- wolne_miejsca - liczba pokoi, do ktorych nalezy wprowadzic dane
*/
DaneRezerwacji* powiekszanie_liczby_pokoi(DaneRezerwacji* tablica, int* liczba_pokoi, int* wolne_miejsca)
{
	// Utworzenie nowej tablicy pomocniczej oraz skopiowanie do niej wartosci elementow starej tablicy
	DaneRezerwacji* nowa_tab = new DaneRezerwacji[2 * (*liczba_pokoi)];
	
	for (int i = 0; i < *liczba_pokoi; i++)
	{
		*(nowa_tab + i) = *(tablica + i);
		
	}

	

	delete[]tablica;

	tablica = nowa_tab;
	// zwiekszenie rozmiaru tablicy
	*wolne_miejsca += *liczba_pokoi;
	*liczba_pokoi *= 2;

	for (int i = (*liczba_pokoi)/2; i < *liczba_pokoi; i++)
	{
		(tablica + i)->numer_pokoju = NULL;
		(tablica + i)->max_liczba_osob = NULL;
		(tablica + i)->lazienka = 0;
		(tablica + i)->cena_pokoju = NULL;
		(tablica + i)->imie_nazwisko.clear();
		(tablica + i)->nr_telefonu = NULL;
		(tablica + i)->data_zameldowania.miesiac = NULL;
		(tablica + i)->data_zameldowania.dzien = NULL;
		(tablica + i)->data_zameldowania.rok = NULL;
		(tablica + i)->data_wymeldowania.miesiac = NULL;
		(tablica + i)->data_wymeldowania.dzien = NULL;
		(tablica + i)->data_wymeldowania.rok = NULL;
		(tablica + i)->posilki = 0;
	}

	return nowa_tab;
}

/*
Funkcja dodajaca pokoje:
	- pokoj - pierwszy wolny element tablicy
	- wolne_pokoje - liczba pokoi, ktore nalezy uzupelnic danymi (dodac)
	- liczba pokoi - liczba wszystkich pokoi
*/
void dodanie_pokoju(DaneRezerwacji* pokoj, int* wolne_pokoje, int liczba_pokoi)
{
	int nr_pokoju;
	int liczba_osob;
	int petla = 1;

	// Wprowadzanie numeru pokoju z podanego zakresu
	while (petla != 0)
	{
		petla = 0;
		cout << "| Podaj numer pokoju < 1 - 999 >: ";
		while (!(cin >> nr_pokoju))
		{
			cout << "!!! Nieprawidlowa wartosc !!! Podaj wartosc jeszcze raz: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (nr_pokoju < 1 || nr_pokoju > 999)
		{
			cout << "!!! Podany numer pokoju jest nieprawidlowy. Wprowadz inny numer.\n";
			petla = 2;
		}
		else
		{
			for (int i = liczba_pokoi - *wolne_pokoje; i >= 0; i--)
			{
				if (nr_pokoju == (pokoj - i - 1)->numer_pokoju)
				{
					cout << "!!! Podany numer pokoju juz istnieje. Wprowadz inny numer.\n";
					petla = 2;
				}
			}
		}
		if (petla != 2)
		{
			pokoj->numer_pokoju = nr_pokoju;
			petla = 0;
		}
		
	}
	petla = 1;
	// Wprowadzanie maksymalnej liczby osob pokoju z podanego zakresu
	while (petla != 0)
	{
		petla = 1;
		cout << "| Podaj maksymalna liczbe osob w pokoju < 1 - 6 >: ";
		while (!(cin >> liczba_osob))
		{
			cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (liczba_osob < 1 || liczba_osob > 6)
		{
			cout << "!!! Podany numer pokoju jest nieprawidlowy. Wprowadz inny numer.\n";
			petla = 2;
		}

		if (petla != 2)
		{
			pokoj->max_liczba_osob = liczba_osob;
			petla = 0;
		}
	}
	
	// Wybranie czy w pokoju ma znajdowac sie lazienka
	cout << "| Czy w pokoju jest lazienka?\n| 0) - nie\n| 1) - tak\nWybor: ";
	while (!(cin >> pokoj->lazienka))
	{
		cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	// Wprowadzenie ceny noclegu w pokoju
	cout << "| Podaj cene pokoju za nocleg: ";
	while (!(cin >> pokoj->cena_pokoju))
	{
		cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	// "Uzupelnienie" pozostalych danych struktury pustymi wartosciami
	pokoj->imie_nazwisko.clear();
	pokoj->nr_telefonu = NULL;
	pokoj->data_zameldowania.miesiac = NULL;
	pokoj->data_zameldowania.dzien = NULL;
	pokoj->data_zameldowania.rok = NULL;
	pokoj->data_wymeldowania.miesiac = NULL;
	pokoj->data_wymeldowania.dzien = NULL;
	pokoj->data_wymeldowania.rok = NULL;
	pokoj->posilki = 0;

	*wolne_pokoje -= 1;
}

/*
Funkcja anulujaca wynajecie pokoj:
	- tablica - pokoj, ktorego wynajecie ma zostac anulowane
*/
void anulowanie_wynajecia_pokoju(DaneRezerwacji* tablica)
{
	

	(tablica)->imie_nazwisko.clear();
	(tablica)->nr_telefonu = NULL;
	(tablica)->data_zameldowania.miesiac = NULL;
	(tablica)->data_zameldowania.dzien = NULL;
	(tablica)->data_zameldowania.rok = NULL;
	(tablica)->data_wymeldowania.miesiac = NULL;
	(tablica)->data_wymeldowania.dzien = NULL;
	(tablica)->data_wymeldowania.rok = NULL;
	(tablica)->posilki = 0;


}

/*
Funkcja usuwajaca pokoje:
	- tablica - pokoj, ktory ma zostac usuniety
	- liczba_pokoi - aktualna liczba dostepnych pokoi
	- indeks - indeks wybranego pokoju
*/
void usuniecie_pokoju(DaneRezerwacji* tablica, int liczba_pokoi, int indeks)
{
	cout << "indeks: " << indeks << endl;
	// "Zsuwanie" elementow
	for (int i = 0; i < liczba_pokoi - indeks; i++)
	{
		*(tablica + i) = *(tablica + i + 1);
	}
	// "uzupelnienie" danych ostatniego pokoju wartosciami pustymi
	(tablica + liczba_pokoi - 1)->numer_pokoju = NULL;
	(tablica + liczba_pokoi - 1)->max_liczba_osob = NULL;
	(tablica + liczba_pokoi - 1)->lazienka = 0;
	(tablica + liczba_pokoi - 1)->cena_pokoju = NULL;
	(tablica + liczba_pokoi - 1)->imie_nazwisko.clear();
	(tablica + liczba_pokoi - 1)->nr_telefonu = NULL;
	(tablica + liczba_pokoi - 1)->data_zameldowania.miesiac = NULL;
	(tablica + liczba_pokoi - 1)->data_zameldowania.dzien = NULL;
	(tablica + liczba_pokoi - 1)->data_zameldowania.rok = NULL;
	(tablica + liczba_pokoi - 1)->data_wymeldowania.miesiac = NULL;
	(tablica + liczba_pokoi - 1)->data_wymeldowania.dzien = NULL;
	(tablica + liczba_pokoi - 1)->data_wymeldowania.rok = NULL;
	(tablica + liczba_pokoi - 1)->posilki = 0;
	
}

/*
Funkcja do wynajmowania pokoju:
	- pokoj, ktory ma zostac wynajety
*/
DaneRezerwacji* wynajecie_pokoju(DaneRezerwacji* pokoj)
{
	string imienazwisko;
	int numer_telefonu = 0;
	bool syn_elona_muska = 0;

	// Wybor co do zabezpieczen znakow w podanym imieniu i nazwisku
	cout << "Czy w twoim imieniu lub nazwisku wystepuja znaki inne niz litery?\n0) - nie\n1) - tak\nWybor: ";
	while (!(cin >> syn_elona_muska))
	{
		cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	// Imie i nazwisko skladajace sie z liter wpisane w okreslonym formacie
	if (syn_elona_muska == 0)
	{
		cin.ignore();
		cout << "| Podaj imie i nazwisko osoby rezerwujacej: ";
		getline(cin, imienazwisko);
		while (imienazwisko.length() > 256)
		{
			cout << "Za dlugi ciag znakow. Podaj imie i nazwisko jeszcze raz: ";
			getline(cin, imienazwisko);
		}


		while (true)
		{
			if (regex_match(imienazwisko, regex("[A-Z]([a-z]+) [A-Z]([a-z]+)")))
			{
				pokoj->imie_nazwisko = imienazwisko;
				break;
			}
			else
			{
				cout << "Nieprawidlowe dane. Podaj imie oraz nazwisko ponownie w formacie <Imie Nazwisko>:\n";
				getline(cin, imienazwisko);
			}
		}
		
	}
	// Brak zabezpieczen do sprowadzanego imienia i nazwiska
	else
	{
		cin.ignore();
		cout << "| Podaj imie i nazwisko osoby rezerwujacej: ";
		getline(cin, imienazwisko);
		while (imienazwisko.length() > 256)
		{
			cout << "Za dlugi ciag znakow. Podaj imie i nazwisko jeszcze raz: ";
			getline(cin, imienazwisko);
		}

		pokoj->imie_nazwisko = imienazwisko;
	}

	
	

	cout << "| Podaj numer telefonu: ";
	while (!(cin >> numer_telefonu))
	{
		cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	while (numer_telefonu < 100000000 || numer_telefonu > 999999999)
	{
		cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
		cin >> numer_telefonu;
	}
	pokoj->nr_telefonu = numer_telefonu;
	
	
	wprowadzanie_daty_zameldowania(pokoj);
	wprowadzanie_daty_wymeldowania(pokoj);
	
	cout << "| Czy posilki sa wykupione?\n| 0) - nie\n| 1) - tak\nWybor: ";
	while (!(cin >> pokoj->posilki))
	{
		cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	return pokoj;
	
}

/*
Funkcja do zmiany wybranych danych wybranego pokoju
*/
DaneRezerwacji* zmiana_danych(DaneRezerwacji* pokoj, int liczba_pokoi, int* wolne_pokoje)
{
	int nr_pokoju;
	int liczba_osob;
	int numer_telefonu = 0;
	string imienazwisko;
	int petla = 1;
	int jakie_dane = 1;

	// Wybor z menu, ktory element struktury chcemy edytowac oraz edytowanie go z uwzglednieniem zabezpieczen (wykorzystywane w poprzednich funkcjach)

	while (jakie_dane != 0)
	{
		cout << "Wybierz, ktore dane chcialbys zmienic:\n> 0) - powrot do menu\n> 1) - numer pokoju\n> 2) - maksymalna liczba osob w pokoju\n> 3) - lazienka w pokoju\n> 4) - cena za nocleg\n> 5) - imie i nazwisko osoby rezerwujacej\n> 6) - numer telefonu\n> 7) - data zameldowania\n> 8) - data wymeldowania\n> 9) - wykupione posilki\nWybor: ";
		while (!(cin >> jakie_dane))
		{
			cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (jakie_dane == 1)
		{
			while (petla != 0)
			{
				petla = 0;
				cout << "| Podaj numer pokoju < 1 - 999 >: ";
				while (!(cin >> nr_pokoju))
				{
					cout << "!!! Nieprawidlowa wartosc !!! Podaj wartosc jeszcze raz: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if (nr_pokoju < 1 || nr_pokoju > 999)
				{
					cout << "!!! Podany numer pokoju jest nieprawidlowy. Wprowadz inny numer.\n";
					petla = 2;
				}
				else
				{
					for (int i = liczba_pokoi - *wolne_pokoje; i >= 0; i--)
					{
						if (nr_pokoju == (pokoj - i - 1)->numer_pokoju)
						{
							cout << "!!! Podany numer pokoju juz istnieje. Wprowadz inny numer.\n";
							petla = 2;
						}
					}
				}
				if (petla != 2)
				{
					pokoj->numer_pokoju = nr_pokoju;
					petla = 0;
				}

			}
			petla = 1;
		}
		else if (jakie_dane == 2)
		{
			while (petla != 0)
			{
				petla = 1;
				cout << "| Podaj maksymalna liczbe osob w pokoju < 1 - 6 >: ";
				while (!(cin >> liczba_osob))
				{
					cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}

				if (liczba_osob < 1 || liczba_osob > 6)
				{
					cout << "!!! Podany numer pokoju jest nieprawidlowy. Wprowadz inny numer.\n";
					petla = 2;
				}

				if (petla != 2)
				{
					pokoj->max_liczba_osob = liczba_osob;
					petla = 0;
				}
			}
			petla = 1;
		}
		else if (jakie_dane == 3)
		{
			cout << "| Czy w pokoju jest lazienka?\n| 0) - nie\n| 1) - tak\nWybor: ";
			while (!(cin >> pokoj->lazienka))
			{
				cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		else if (jakie_dane == 4)
		{
			cout << "| Podaj cene pokoju za nocleg: ";
			while (!(cin >> pokoj->cena_pokoju))
			{
				cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
		else if (jakie_dane == 5)
		{
			bool syn_elona_muska = 0;
			cout << "Czy w imieniu lub nazwisku wystepuja znaki inne niz litery?\n0) - nie\n1) - tak\nWybor: ";
			while (!(cin >> syn_elona_muska))
			{
				cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			if (syn_elona_muska == 0)
			{
				cin.ignore();
				cout << "| Podaj imie i nazwisko osoby rezerwujacej: ";
				getline(cin, imienazwisko);
				while (imienazwisko.length() > 256)
				{
					cout << "Za dlugi ciag znakow. Podaj imie i nazwisko jeszcze raz: ";
					getline(cin, imienazwisko);
				}


				while (true)
				{
					if (regex_match(imienazwisko, regex("[A-Z]([a-z]+) [A-Z]([a-z]+)")))
					{
						pokoj->imie_nazwisko = imienazwisko;
						break;
					}
					else
					{
						cout << "Nieprawidlowe dane. Podaj imie oraz nazwisko ponownie w formacie <Imie Nazwisko>:\n";
						getline(cin, imienazwisko);
					}
				}

			}
			
		}
		else if (jakie_dane == 6)
		{
			cout << "| Podaj numer telefonu: ";
			while (!(cin >> numer_telefonu))
			{
				cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			while (numer_telefonu < 100000000 || numer_telefonu > 999999999)
			{
				cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
				cin >> numer_telefonu;
			}
			pokoj->nr_telefonu = numer_telefonu;
		}
		else if (jakie_dane == 7)
		{
			wprowadzanie_daty_zameldowania(pokoj);
		}
		else if (jakie_dane == 8)
		{
			wprowadzanie_daty_wymeldowania(pokoj);
		}
		else if (jakie_dane == 9)
		{
			cout << "| Czy posilki sa wykupione?\n| 0) - nie\n| 1) - tak\nWybor: ";
			while (!(cin >> pokoj->posilki))
			{
				cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}
	

	return pokoj;
}

/*
Funkcja do wyswietlania pojedynczego pokoju
*/
void wyswietlanie_pojedynczego_pokoju(DaneRezerwacji* pokoj)
{
	string czy_lazienka;
	if (pokoj->lazienka == false)
		czy_lazienka = "nie";
	else if (pokoj->lazienka == true)
		czy_lazienka = "tak";
	string czy_posilki;
	if (pokoj->posilki == false)
		czy_posilki = "nie";
	else if (pokoj->posilki == true)
		czy_posilki = "tak";

	cout << "\n-------------  " << pokoj->numer_pokoju << "  -------------\n";
	cout << "|    Numer pokoju: " << pokoj->numer_pokoju << endl;
	cout << "|    Liczba osob: " << pokoj->max_liczba_osob << endl;
	cout << "|    Lazienka w pokoju: " << czy_lazienka << endl;
	cout << "|    Cena za nocleg: " << pokoj->cena_pokoju << endl;
	cout << "|    Imie i nazwisko rezerwujacego: " << pokoj->imie_nazwisko << endl;
	cout << "|    Numer telefonu: " << pokoj->nr_telefonu << endl;
	cout << "|    Data zameldowania: " << pokoj->data_zameldowania.dzien << "-" << pokoj->data_zameldowania.miesiac << "-" << pokoj->data_zameldowania.rok << endl;
	cout << "|    Data wymeldowania: " << pokoj->data_wymeldowania.dzien << "-" << pokoj->data_wymeldowania.miesiac << "-" << pokoj->data_wymeldowania.rok << endl;
	cout << "|    Posilki: " << czy_posilki << endl;
}

/*
Funkcja do wyswietlania grupy pokoi
*/
void wyswietlanie_wszystkich_pokoi(DaneRezerwacji* tablica, int liczba_dostepnych_pokoi)
{
	for (int i = 0; i < liczba_dostepnych_pokoi; i++)
	{
		wyswietlanie_pojedynczego_pokoju(tablica + i);
	}
}

/*
Funkcja do wyszukiwania pokoju po nazwisku
	- tablica - tablica przechowujaca obiekty typu DaneRezerwacji
	- liczba_pokoi - liczba wynajetych pokoi
*/
DaneRezerwacji* wyszukiwanie_pokoju_po_nazwisku(DaneRezerwacji* tablica, int liczba_pokoi)
{
	string imie_nazwisko;
	cin.ignore();
	cout << "| Podaj imie i nazwisko osoby rezerwujacej pokoj: ";
	getline(cin, imie_nazwisko);
	int liczba_wyszukanych_pokoi = 0;

	
	for (int i = 0; i < liczba_pokoi; i++)
	{
		if (imie_nazwisko == (tablica + i)->imie_nazwisko)
		{
			cout << "\n| Oto twoj pokoj\n";
			wyswietlanie_pojedynczego_pokoju(tablica + i);
			return (tablica + i);
		}
		else
		{
			cout << "Brak rezerwacji na podane nazwisko.\n\n";
			break;
		}
			
		
	}
}

/*
Funkcja do wyszukiwania pokoju po nazwisku z wykorzystaniem wyrazen regularnych
	- tablica - tablica przechowujaca obiekty typu DaneRezerwacji
	- liczba_pokoi - liczba wynajetych pokoi
*/
DaneRezerwacji* wyszukiwanie_pokoju_po_nazwisku_regex(DaneRezerwacji* tablica, int liczba_pokoi)
{
	string imienazwisko;
	cin.ignore();
	cout << "| Podaj imie i nazwisko osoby rezerwujacej: ";
	getline(cin, imienazwisko);
	while (imienazwisko.length() > 256)
	{
		cout << "Za dlugi ciag znakow. Podaj imie i nazwisko jeszcze raz: ";
		getline(cin, imienazwisko);
	}


	while (true)
	{
		if (regex_match(imienazwisko, regex("[A-Z]+([a-z]+) [A-Z]+([a-z]+)")))
		{
			break;
		}
		else
		{
			cout << "Nieprawidlowe dane. Podaj imie oraz nazwisko ponownie w formacie <Imie Nazwisko>:\n";
			getline(cin, imienazwisko);
		}
	}


	for (int i = 0; i < liczba_pokoi; i++)
	{
		if (regex_match((tablica + i)->imie_nazwisko, regex(imienazwisko)))
		{
			cout << "\n| Oto twoj pokoj\n";
			wyswietlanie_pojedynczego_pokoju(tablica + i);
			return (tablica + i);
		}
	}
	cout << "Brak rezerwacji na podane nazwisko.\n\n";
}

/*
Funkcja do wyszukiwania pokoju po numerze pokoju
	- tablica - tablica przechowujaca obiekty typu DaneRezerwacji
	- liczba_pokoi - liczba dostepnych pokoi
	- indeks - indeks pokoju, ktory zostal znaleziony
*/
DaneRezerwacji* wyszukiwanie_pokoju_po_numerze(DaneRezerwacji* tablica, int liczba_pokoi, int* indeks)
{
	int nr_pokoju = 0;
	
	cout << "| Podaj numer pokoju: ";
	while (!(cin >> nr_pokoju))
	{
		cout << "!!! Nieprawidlowa wartosc! \n| Podaj jeszcze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}


	
	for (int i = 0; i < liczba_pokoi; i++)
	{
		if (nr_pokoju == (tablica + i)->numer_pokoju)
		{
			cout << "\n| Oto twoj pokoj\n";
			wyswietlanie_pojedynczego_pokoju(tablica + i);
			*indeks = i;
			return (tablica + i);
		}
	}
	cout << "!!! Nie ma pokoju o takim numerze. \n\n";
	
	
}

/*
Funkcja do wyszukiwania pokoju po numerze pokoju z wykorzystaniem wyrazen regularnych
	- tablica - tablica przechowujaca obiekty typu DaneRezerwacji
	- liczba_pokoi - liczba dostepnych pokoi
	- indeks - indeks pokoju, ktory zostal znaleziony
*/
DaneRezerwacji* wyszukiwanie_pokoju_po_numerze_regex(DaneRezerwacji* tablica, int liczba_pokoi, int* indeks)
{
	int nr_pokoju = 0;

	cout << "| Podaj numer pokoju: ";
	cin >> nr_pokoju;
	
	while (true)
	{

		if (regex_match(to_string(nr_pokoju), regex("[1-999]")))
		{
			break;
		}
		else
		{
			cout << "Nieprawidlowe dane. Podaj numer pokoju ponownie <1 - 999>:\n";
			cin >> nr_pokoju;
		}
	}

	


	for (int i = 0; i < liczba_pokoi; i++)
	{
		
		if (regex_match(to_string((tablica + i)->numer_pokoju), regex(to_string(nr_pokoju))))
		{
			cout << "\n| Oto twoj pokoj\n";
			wyswietlanie_pojedynczego_pokoju(tablica + i);
			*indeks = i;
			return (tablica + i);
		}
	}
	cout << "!!! Nie ma pokoju o takim numerze. \n\n";


}

/*
Funkcja do zapisywania w pliku aktualnej bazy danych
	- tablica - tablica przechowujaca obiekty typu DaneRezerwacji
	- liczba_dostepnych_pokoi - liczba dostepnych pokoi
	- liczba_wynajetych_pokoi - liczba wynajetych pokoi
	- nazwa_pliku - nazwa pod ktora ma zostac zapisany plik z danymi
*/
void zapis_do_pliku(DaneRezerwacji* tablica, int liczba_dostepnych_pokoi, int liczba_wynajetych_pokoi, string nazwa_pliku)
{
	int wybor_opcji = 1;
	

	fstream plik;

	// Wybor grupy pokoi, ktore maja zostac zapisane do pliku

	cout << "\nJaka baze danych chcesz zapisac?\n| 0) - wroc do menu\n| 1) - dostepne pokoje (wynajete oraz gotowe do wynajecia)\n| 2) - tylko wynajete pokoje\nWybor: ";
	while (!(cin >> wybor_opcji))
	{
		cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	while (wybor_opcji != 0)
	{
		if (wybor_opcji != 1 && wybor_opcji != 2)
		{
			cout << "Nieprawidlowy numer. Wybierz jeszcze raz: ";
			cin >> wybor_opcji;
			continue;
		}
		else if (liczba_dostepnych_pokoi != 0)
		{
			// Zapisanie w pliku pokoi dostepnych
			if (wybor_opcji == 1)
			{
				plik.open(nazwa_pliku, fstream::app);

				if (plik.is_open())
				{

					for (int i = 0; i < liczba_dostepnych_pokoi; i++)
					{
						plik << (tablica + i)->numer_pokoju << endl;
						plik << (tablica + i)->max_liczba_osob << endl;
						plik << (tablica + i)->lazienka << endl;
						plik << (tablica + i)->cena_pokoju << endl;
						plik << (tablica + i)->imie_nazwisko << endl;
						plik << (tablica + i)->nr_telefonu << endl;
						plik << (tablica + i)->data_zameldowania.rok << endl;
						plik << (tablica + i)->data_zameldowania.miesiac << endl;
						plik << (tablica + i)->data_zameldowania.dzien << endl;
						plik << (tablica + i)->data_wymeldowania.rok << endl;
						plik << (tablica + i)->data_wymeldowania.miesiac << endl;
						plik << (tablica + i)->data_wymeldowania.dzien << endl;
						plik << (tablica + i)->posilki << endl;
					}
				}
				else
				{
					cout << "!!! Blad przy otwieraniu pliku !!!\n";
				}
			}
			// Zapisanie w pliku pokoi wynajetych
			else if (wybor_opcji == 2 && liczba_wynajetych_pokoi != 0)
			{
				plik.open(nazwa_pliku, fstream::app);

				if (plik.is_open())
				{
					for (int i = 0; i < liczba_dostepnych_pokoi; i++)
					{
						if ((tablica + i)->data_zameldowania.rok != 0)
						{
							plik << (tablica + i)->numer_pokoju << endl;
							plik << (tablica + i)->max_liczba_osob << endl;
							plik << (tablica + i)->lazienka << endl;
							plik << (tablica + i)->cena_pokoju << endl;
							plik << (tablica + i)->imie_nazwisko << endl;
							plik << (tablica + i)->nr_telefonu << endl;
							plik << (tablica + i)->data_zameldowania.rok << endl;
							plik << (tablica + i)->data_zameldowania.miesiac << endl;
							plik << (tablica + i)->data_zameldowania.dzien << endl;
							plik << (tablica + i)->data_zameldowania.rok << endl;
							plik << (tablica + i)->data_zameldowania.miesiac << endl;
							plik << (tablica + i)->data_zameldowania.dzien << endl;
							plik << (tablica + i)->posilki << endl;
						}
					}
				}
				else
				{
					cout << "!!! Blad przy otwieraniu pliku !!!\n";
				}
				
			}
			else
			{
				cout << "Brak rekordow w bazie.\n";
			}
			
			
			wybor_opcji = 0;
			
			
		}
		else
		{
			cout << "Brak pokoi w bazie danych. Wybierz jeszcze raz: ";
			while (!(cin >> wybor_opcji))
			{
				cout << "!!! Nieprawidlowa wartosc !!! \n| Podaj jeszcze raz: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}
		plik.close();
	}
}

/*
Funkcja do odczytywania danych z pliku i umieszczania ich w bazie danych programu
	- tablica - tablica przechowujaca obiekty typu DaneRezerwacji
	- liczba_pokoi - liczba wszystkich pokoi w bazie
	- liczba_dostepnych_pokoi - liczba dostepnych pokoi
	- pokoje_wynajete - liczba wynajetych pokoi
	- wolne_pokoje - liczba pokoi, ktore nalezy uzupelnic danymi
	- nazwa_pliku - nazwa pod ktora ma zostac zapisany plik z danymi
*/
DaneRezerwacji* odczyt_z_pliku(DaneRezerwacji* tablica, int* liczba_pokoi, int* liczba_dostepnych_pokoi, int* pokoje_wynajete, int* wolne_pokoje, string nazwa_pliku)
{
	fstream plik2;

	// Zmienne pomocnicze wykorzystywane w ponizszych linijkach kodu
	string dane;
	int j = 0;
	int staloprzecinkowa;
	bool prawda_falsz;
	float zmiennoprzecinkowa;
	
	int licznik_pokoi = 0;
	int licznik_wynajetych_pokoi = 0;
	int liczba_wolnych_pokoi = *liczba_pokoi - licznik_pokoi;
	plik2.open(nazwa_pliku, fstream::in);

	if (plik2.is_open())
	{
		
		while (!plik2.eof())
		{
			// Petla odczytujaca 13 wartosci z pliku (liczba elementow jednego obiektu struktury typu DaneRezerwacji)
			for (int i = 0; i < 13; i++)
			{
				// Odczytywanie danych z pliku i przypisywanie ich do konkretnych elementow obiektu struktury wraz z konwersja typu danych jesli to potrzebne
				
				getline(plik2, dane);
				
				if (i == 0 || i == 1 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9 || i == 10 || i == 11)
				{
					staloprzecinkowa = stoi(dane);
					
					if (i == 0)
					{
						(tablica + j)->numer_pokoju = staloprzecinkowa;
						
					}
					else if (i == 1)
					{
						(tablica + j)->max_liczba_osob = staloprzecinkowa;
						

					}
					else if (i == 5)
					{
						(tablica + j)->nr_telefonu = staloprzecinkowa;
						
					}
					else if (i == 6)
					{
						(tablica + j)->data_zameldowania.rok = staloprzecinkowa;
						
						// Jesli rok daty zameldowania jest rozny od zera, wtedy pokoj, zawierajacy ta date, jest traktowany jako wynajety (rok daty zameldowania jest rozny od zera tylko w przypadku wynajecia tego pokoju)
						if (staloprzecinkowa != 0)
						{
							licznik_wynajetych_pokoi += 1;
						}
					}
					else if (i == 7)
					{
						(tablica + j)->data_zameldowania.miesiac = staloprzecinkowa;
						
					}
					else if (i == 8)
					{
						(tablica + j)->data_zameldowania.dzien = staloprzecinkowa;
						
					}
					else if (i == 9)
					{
						(tablica + j)->data_wymeldowania.rok = staloprzecinkowa;
						
					}
					else if (i == 10)
					{
						(tablica + j)->data_wymeldowania.miesiac = staloprzecinkowa;
						
					}
					else if (i == 11)
					{
						(tablica + j)->data_wymeldowania.dzien = staloprzecinkowa;
						
					}
					else
					{
						cout << "Blad.\n";
					}
				}
				else if (i == 2 || i == 12)
				{
					
					if (dane == "1")
					{
						prawda_falsz = 1;

					}
					else if (dane == "0")
					{
						prawda_falsz = 0;
					}
					else
					{
						cout << "Blad.\n";
					}

					if (i == 2)
					{
						(tablica + j)->lazienka = prawda_falsz;
						
					}
					else if (i == 12)
					{
						(tablica + j)->posilki = prawda_falsz;
						
					}
					else
					{
						cout << "Blad.\n";
					}
					
				}
				else if (i == 3)
				{
					zmiennoprzecinkowa = stof(dane);
					(tablica + j)->cena_pokoju = zmiennoprzecinkowa;
					
				}
				else if (i == 4)
				{
					
					(tablica + j)->imie_nazwisko = dane;
					
				}
				else
				{
					cout << "Blad.\n";
				}

				
				
			}
			// Zliczanie liczby pokoi w celu ustalenia odpowiedniego rozmiaru tablicy
			licznik_pokoi += 1;
			if (licznik_pokoi == *liczba_pokoi)
			{
				*wolne_pokoje = liczba_wolnych_pokoi;
				tablica = powiekszanie_liczby_pokoi(tablica, liczba_pokoi, &liczba_wolnych_pokoi);
			}
			
			j += 1;
			
			plik2.peek();
		}
		
		// Dzialania majace na celu prawidlowe okreslenie liczby pokoi w okreslonej grupie
		
		*pokoje_wynajete = licznik_wynajetych_pokoi;
		*liczba_dostepnych_pokoi = licznik_pokoi;
		licznik_pokoi = 0;
		licznik_wynajetych_pokoi = 0;
		
		
		return tablica;
	}
	else
	{
		cout << "!!! Blad przy otwieraniu pliku\n";
	}
	plik2.close();
	
}
