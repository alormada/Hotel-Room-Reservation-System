#include <iostream>
#include <string>
#include "Projekt.h"

using namespace std;

int main()
{
	// Liczba wszystkich pokoi (gotowych oraz niegotowych do wynajecia)
	int liczba_pokoi = 4;
	// Liczba pokoi, ktore trzeba przygotowac do wynajecia (bez pokoi gotowych do wynajecia oraz pokoi wynajetych)
	int wolne_pokoje = liczba_pokoi;
	// Liczba pokoi gotowych do wynajecia (bez pokoi niegotowych do wynajecia oraz wynajetych)
	int pokoje_do_wynajecia = 0;
	// Liczba pokoi wynajetych
	int pokoje_wynajete = 0;
	// Liczba pokoi wynajetych i gotowych do wynajecia
	int dostepne_pokoje = pokoje_wynajete + pokoje_do_wynajecia;
	// Zmienna pomocnicza do wyboru pozycji z menu
	int wybor = 1;
	// Zmienna do wybrania pokoju
	int indeks = 0;
	// Zmienna pomocnicza do wyboru wewnatrz funkcji z menu
	int wybor_poboczny = 0;
	// Zmienna pomocnicza do zliczania liczb pokoi przy usuwaniu
	int licznik = 0;
	// Zmienna przechowujaca nazwe pliku
	string nazwa_pliku;

	// Utworzenie tablicy przechowujacej wszystkie pokoje
	DaneRezerwacji* tablica = new DaneRezerwacji[liczba_pokoi];

	// "Wypelnienie" elementow tablicy pustymi danymi
	rozpoczecie_programu(tablica, liczba_pokoi);
	
	// Menu

	while (wybor != 0)
	{
		cout << "----------------- MENU -----------------";
		cout << "\n0) - zakoncz dzialanie programu\n1) - dodaj pokoj\n2) - wynajmij pokoj\n3) - usun pokoj\n4) - anuluj wynajecie pokoju\n5) - wyszukaj pokoj\n6) - zmien dane pokoju\n7) - wyswietl pokoje\n8) - zapisz baze danych do pliku\n9) - odczytaj baze danych z pliku\nWybor: ";
		while (!(cin >> wybor))
		{
			cout << "\n!!! Nieprawidlowa wartosc! Podaj jeszcze raz: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "\n";

		// Dodawanie pokoju
		if (wybor == 1)
		{
			// W przypadku braku wolnych pokoi nastepuje powiekszenie rozmiaru tablicy dwa razy
			if (wolne_pokoje == 0)
			{
				tablica = powiekszanie_liczby_pokoi(tablica, &liczba_pokoi, &wolne_pokoje);
				cout << "\n\n";

				
				cout << "Podaj pokoj nr " << dostepne_pokoje + 1<< endl;
				dodanie_pokoju(tablica + dostepne_pokoje, &wolne_pokoje, liczba_pokoi);
				pokoje_do_wynajecia += 1;
				cout << "\n\n";
				
			}
			else
			{

				cout << "Podaj pokoj nr " << liczba_pokoi - wolne_pokoje + 1 << endl;
				dodanie_pokoju(tablica + dostepne_pokoje, &wolne_pokoje, liczba_pokoi);
				pokoje_do_wynajecia += 1;
			}
			dostepne_pokoje += 1;
			pokoje_do_wynajecia += 1;
			wolne_pokoje = liczba_pokoi - dostepne_pokoje;
			
		}
		// Wynajmowanie pokoju
		else if (wybor == 2)
		{
			// Wyswietlenie listy pokoi, ktore mozna wynajac oraz wynajecie pokoju o wybranym numerze
			if (pokoje_do_wynajecia != 0)
			{
				cout << "Lista pokoi do wynajecia:\n";
				for (int i = 0; i < dostepne_pokoje; i++)
				{
					if ((tablica + i)->data_zameldowania.rok == 0)
					{
						wyswietlanie_pojedynczego_pokoju(tablica + i);
					}
				}
				
				wynajecie_pokoju(wyszukiwanie_pokoju_po_numerze(tablica, dostepne_pokoje, &indeks));
				pokoje_do_wynajecia -= 1;
				pokoje_wynajete += 1;
			}
			// Komunikat w przypadku braku wolnych pokoi do wynajecia
			else
			{
				cout << "Brak pokoi do wynajecia. Zwolnij pokoj lub dodaj nowy.\n\n";
			}
			
		}
		// Usuwanie pokoju
		else if (wybor == 3)
		{
			// Wyswietlenie listy pokoi, ktore mozna usunac oraz usuniecie pokoju o wybranym numerze
			if (pokoje_do_wynajecia != 0)
			{
				cout << "Lista pokoi, ktore mozesz usunac:\n";
				wyswietlanie_wszystkich_pokoi(tablica, dostepne_pokoje);
				usuniecie_pokoju(wyszukiwanie_pokoju_po_numerze(tablica, liczba_pokoi, &indeks), dostepne_pokoje, indeks);
				for (int i = 0; i < dostepne_pokoje; i++)
				{
					if ((tablica + i)->data_zameldowania.rok != 0)
					{
						licznik += 1;
					}
				}
				pokoje_wynajete = licznik;
				licznik = 0;
				dostepne_pokoje -= 1;
				wolne_pokoje += 1;
				pokoje_do_wynajecia = dostepne_pokoje - pokoje_wynajete;
				
			}
			// Komunikat w przypadku braku wolnych pokoi do wynajecia
			else
			{
				cout << "Brak pokoi do usuniecia. Wynajmij pokoj lub dodaj nowy.\n\n";
			}
		}
		// Anulowanie wynajecia pokoju
		else if (wybor == 4)
		{
			// Wyswietlenie listy pokoi, ktorych wynajecie mozna anulowac oraz anulowanie wynajecia pokoju o wybranym numerze
			if (pokoje_wynajete != 0)
			{
				cout << "Lista pokoi wynajetych:\n";
				for (int i = 0; i < dostepne_pokoje; i++)
				{
					if ((tablica + i)->data_zameldowania.rok != 0)
					{
						wyswietlanie_pojedynczego_pokoju(tablica + i);
					}
				}

				anulowanie_wynajecia_pokoju(wyszukiwanie_pokoju_po_numerze(tablica, liczba_pokoi, &indeks));
				pokoje_do_wynajecia += 1;
				pokoje_wynajete -= 1;
			}
			// Komunikat w przypadku braku wynajetych pokoi
			else
			{
				cout << "Brak wynajetych pokoi.\n\n";
			}
		}
		// Wyszukiwanie pokoju
		else if (wybor == 5)
		{
			int wybierz;
			// Wybor wyszukiwania pokoju (po numerze pokoju lub po nazwisku osoby rezerwujacej)
			cout << "Za pomoca jakich danych chcesz wyszukac pokoj?\n| 1) - Imie i nazwisko\n| 2) - Numer pokoju\nWybor: ";
			while (!(cin >> wybor_poboczny))
			{
				cout << "\n!!! Nieprawidlowa wartosc! Podaj jeszcze raz: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << "\n";
			while (wybor_poboczny != 0)
			{
				// Wyszukiwanie pokoju po imieniu i nazwisku
				if (wybor_poboczny == 1)
				{
					// Komunikat w przypadku braku pokoi do wyszukania
					if (pokoje_wynajete == 0)
					{
						cout << "Brak wynajetych pokoi.\n\n";
						wybor_poboczny = 0;
					}
					else
					{
						// Wybor sposobu wyszukiwania pokoju
						cout << "Jak chcesz wyszukac pokoj?\n0) - powrot do menu\n1) - wyszukaj normalnie\n2) - wyszukaj za pomoca wyrazen regularnych\nWybor: ";
						while (!(cin >> wybierz))
						{
							cout << "\n!!! Nieprawidlowa wartosc! Podaj jeszcze raz: ";
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
						while (wybierz != 0)
						{
							if (wybierz == 1)
							{
								wyszukiwanie_pokoju_po_nazwisku(tablica, dostepne_pokoje);
								wybor_poboczny = 0;
								wybierz = 0;
							}
							else if (wybierz == 2)
							{
								wyszukiwanie_pokoju_po_nazwisku_regex(tablica, dostepne_pokoje);
								wybor_poboczny = 0;
								wybierz = 0;
							}
							// Wyswietlenie komunikatu w przypadku nieprawidlowych danych
							else
							{
								cout << "Nieprawidlowe dane. Wybierz jeszcze raz: ";
								while (!(cin >> wybierz))
								{
									cout << "\n!!! Nieprawidlowa wartosc! Podaj jeszcze raz: ";
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
								}
							}
							
						}
						
						
					}
				}
				// Wyszukiwanie po numerze pokoju
				else if (wybor_poboczny == 2)
				{
					// Komunikat w przypadku braku dostepnych pokoi
					if (dostepne_pokoje == 0)
					{
						cout << "Brak dodanych pokoi. \n\n";
						wybor_poboczny = 0;
					}
					else
					{
						// Wybor sposobu wyszukiwania pokoju
						cout << "Jak chcesz wyszukac pokoj?\n0) - powrot do menu\n1) - wyszukaj normalnie\n2) - wyszukaj za pomoca wyrazen regularnych\nWybor: ";
						while (!(cin >> wybierz))
						{
							cout << "\n!!! Nieprawidlowa wartosc! Podaj jeszcze raz: ";
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
						while (wybierz != 0)
						{
							if (wybierz == 1)
							{
								wyszukiwanie_pokoju_po_numerze(tablica, dostepne_pokoje, &indeks);
								wybor_poboczny = 0;
								wybierz = 0;
							}
							else if (wybierz == 2)
							{
								wyszukiwanie_pokoju_po_numerze_regex(tablica, dostepne_pokoje, &indeks);
								wybor_poboczny = 0;
								wybierz = 0;
							}
							// Wyswietlenie komunikatu w przypadku nieprawidlowych danych
							else
							{
								cout << "Nieprawidlowe dane. Wybierz jeszcze raz: ";
								while (!(cin >> wybierz))
								{
									cout << "\n!!! Nieprawidlowa wartosc! Podaj jeszcze raz: ";
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
								}
							}

						}
						
						wybor_poboczny = 0;
					}		
				}
				// Wyswietlenie komunikatu w przypadku nieprawidlowych danych
				else
				{
					cout << "Nieprawidlowa wartosc. Podaj jeszcze raz: ";
					cin >> wybor_poboczny;
				}
			}
				
		}
		// Edytowanie danych pokoju
		else if (wybor == 6)
		{
			// Wyswietlenie listy pokoi, ktorych dane mozna zmienic oraz zmiana danych wybranego pokoju
			if (dostepne_pokoje != 0)
			{
				cout << "Lista pokoi, ktorych dane mozesz zmienic:\n";
				wyswietlanie_wszystkich_pokoi(tablica, dostepne_pokoje);
				zmiana_danych(wyszukiwanie_pokoju_po_numerze(tablica, liczba_pokoi, &indeks), liczba_pokoi, &wolne_pokoje);
			}
			// Komunikat w przypadku braku pokoi dostepnych do zmiany
			else
			{
				cout << "Brak pokoi, ktorych dane mozna zmienic.\n\n";
			}
			
		}
		// Wyswietlanie pokoi
		else if (wybor == 7)
		{
			// Wybor pokoi, ktore chcemy wyswietlic
			cout << "Jakie pokoje chcesz wyswietlic?\n0) - anuluj\n1) - wszystkie\n2) - dostepne\n3) - wynajete\n4) - do wynajecia\nWybor: ";
			while (!(cin >> wybor_poboczny))
			{
				cout << "\n!!! Nieprawidlowa wartosc! Podaj jeszcze raz: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			while (wybor_poboczny != 0 && wybor_poboczny != 1 && wybor_poboczny != 2 && wybor_poboczny != 3 && wybor_poboczny != 4)
			{
				cout << "\n!!! Nieprawidlowa wartosc! Podaj jeszcze raz: ";
				cin >> wybor_poboczny;
			}
			
			if (wybor_poboczny != 0)
			{
				// Wszystkie pokoje
				if (wybor_poboczny == 1)
				{
					wyswietlanie_wszystkich_pokoi(tablica, liczba_pokoi);
				}
				// Dostepne pokoje
				else if (wybor_poboczny == 2)
				{
					if (dostepne_pokoje != 0)
					{
						wyswietlanie_wszystkich_pokoi(tablica, dostepne_pokoje);
					}
					else
					{
						cout << "Brak pokoi do wyswietlenia.\n\n";
					}
				}
				// Pokoje wynajete
				else if (wybor_poboczny == 3)
				{
					licznik = 0;
					for (int i = 0; i < dostepne_pokoje; i++)
					{
						if ((tablica + i)->data_zameldowania.rok != 0)
						{
							wyswietlanie_pojedynczego_pokoju(tablica + i);
							licznik += 1;
						}
					}
					if (licznik == 0)
					{
						cout << "Brak wynajetych pokoi.\n";
					}
					licznik = 0;
				}
				// Pokoje do wynajecia
				else if (wybor_poboczny == 4)
				{
					licznik = 0;
					for (int i = 0; i < dostepne_pokoje; i++)
					{
						if ((tablica + i)->data_zameldowania.rok == 0)
						{
							wyswietlanie_pojedynczego_pokoju(tablica + i);
							licznik += 1;
						}
					}
					if (licznik == 0)
					{
						cout << "Brak pokoi do wynajecia.\n";
					}
					licznik = 0;
				}
				else
				{
					cout << "Blad.\n";
				}
			}
		}
		// Zapisanie bazy danych do pliku
		else if (wybor == 8)
		{
			if (dostepne_pokoje == 0 && pokoje_wynajete == 0)
			{
				cout << "Brak rekordow w bazie.\n";
				continue;
			}
			else
			{
				cout << "Podaj pod jaka nazwa chcesz zapisac plik: ";
				cin >> nazwa_pliku;
				nazwa_pliku = nazwa_pliku + ".txt";
				zapis_do_pliku(tablica, dostepne_pokoje, pokoje_wynajete, nazwa_pliku);
			}
		}
		// Odczytanie bazy danych z pliku
		else if (wybor == 9)
		{
		cout << "Podaj nazwe pliku, z ktorego chcesz odczytac dane: ";
		cin >> nazwa_pliku;
		nazwa_pliku = nazwa_pliku + ".txt";
		
		
		tablica = odczyt_z_pliku(tablica, &liczba_pokoi, &dostepne_pokoje, &pokoje_wynajete, &wolne_pokoje, nazwa_pliku);
		
		wolne_pokoje = liczba_pokoi - dostepne_pokoje;
		pokoje_do_wynajecia = dostepne_pokoje - pokoje_wynajete;
		
		}
		// Wyswietlenie komunikatu w przypadku nieprawidlowej wartosci
		else
		{
		cout << "Nieprawidlowa wartosc. Wybierz ponownie.\n\n";
		}
		
	}



	delete[]tablica;

	return 0;
}