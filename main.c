#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
int ID_K, ID_P;
int amount_Item = 0;
int amount_Customer = 0;
int ID_Klient;
int ID_Przedmiot;
int ilosc_Przedmiotow_Klient = 0;
//czyszczenie ekranu
void Clear() {
	system("cls");
}
//czyszczenie bufora do podawania danych
void Flush() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}
//napisy do menu
void MenuOptions()
{
	printf("\nWybierz opcje.\nPamietaj ze do opuszczenia programu sluzy klawisz \'q\'\n");
	printf("------------------------------------------\n");
	printf("Klienci:\n");
	printf("a)Dodanie osoby do bazy danych\n");
	printf("b)Usuniecie osoby z bazy danych\n");
	printf("c)Edycja danych osoby w bazie danych\n");
	printf("d)Wyswietlenie klientow w bazie danych posortowanych wg ID\n");
	printf("e)Wyswietlenie klientow w bazie danych posortowanych wg nazwiska\n");
	printf("f)Wyswietlenie klientow w bazie danych posortowanych wg kwoty zakupow\n");
	printf("g)Wyswietlenie klientow w bazie danych przy pomocy wpisanego nazwiska\n");
	printf("h)Wyswietlenie klientow w bazie danych przy pomocy wpisanej kwoty zakupow\n");
	printf("------------------------------------------\n");
	printf("Przedmioty:\n");
	printf("i)Dodanie przedmiotu do bazy danych\n");
	printf("j)Usuniecie przedmiotu z bazy danych\n");
	printf("k)Edycja danych przedmiotu z bazy danych\n");
	printf("l)Wyswietlenie przedmiotow z bazy danych posortowanych wg ID\n");
	printf("m)Wyswietlenie przedmiotow z bazy danych posortowanych wg nazwy\n");
	printf("n)Wyswietlenie przedmiotow z bazy danych posortowanych wg daty wystawienia\n");
	printf("o)Wyswietlenie przedmiotow z bazy danych przy pomocy wpisanego statusu\n");
	printf("p)Wyswietlenie przedmiotow z bazy danych przy pomocy wpisanego wpisanego przedzialu cenowego\n");
	printf("r)Wyswietlenie przedmiotow z bazy danych przy pomocy wpisanego roku(data wstawienia)\n");
	printf("-------------------------------------------\n");
	printf("y)Ponowne przypisanie ID dla przedmiotow i klientow(gdy ID juz sa za duze)\n");
	printf("x)Press X to pay honor\n");
	printf("z)Zapis danych do pliku\n");
	printf("q)Wyjscie z programu\n");
	printf("Twoj wybor:");
}
//napisy do menu edycji przedmiotów
void MenuOptions_Function_Item() {
	printf("1.Zmiana nazwy.\n");
	printf("2.Zmiana stanu(kupiony lub wystawiony na sprzedaz).\n");
	printf("3.Zmiana ceny zastawienia.\n");
	printf("4.Zmiana ceny sprzedazy.\n");
	printf("5.Zmiana daty.\n");
}
//napisy do menu edycji klientów
void MenuOptions_Function_Customer() {
	printf("1.Zmiana imienia.\n");
	printf("2.Zmiana nazwiska.\n");
	printf("3.Zmiana elementow na liscie.\n");
}

typedef struct Klient {
	int ID;
	char Imie[30];
	char Nazwisko[50];
	int Kwota_wydana;
	char(*Lista)[51];
	struct Klient* next;
	int ILOSC;
}Klient;
typedef Klient* Lista_K;

typedef struct Przedmiot
{
	int ID;
	char Nazwa[51];
	int Stan;
	int Kwota_zastawy;
	int Cena;
	int Dzien;
	int Miesiac;
	int Rok;
	struct Przedmiot* next;
}Przedmiot;
typedef Przedmiot* Lista_P;
//nadanie pamięci na nowy element na liście przedmiotów
void Space_P(Lista_P a)
{
	for (; a->next != NULL; a = a->next) {}
	a->next = (Lista_P)malloc(sizeof(Przedmiot));
	a = a->next;
	a->next = NULL;
}
//nadanie pamięci na nowy element na liście klientów
void Space_K(Lista_K d)
{
	for (; d->next != NULL; d = d->next) {}
	d->next = (Lista_K)malloc(sizeof(Klient));
	d->next->next = NULL;
}
//funkcja do nadawania kwoty wydanej w lombardzie
void Refill(Lista_K K, Lista_P P) {
	Lista_P head;
	for (; K->next != NULL; K = K->next)
	{
		K->Kwota_wydana = 0;
		for (head = P; head->next != NULL; head = head->next)
		{
			int i;
			if (K->ILOSC > 0)
			{
				for (i = 0; i < K->ILOSC; ++i)
				{
					if (strcmp(K->Lista[i], head->Nazwa) == 0)
					{
						K->Kwota_wydana += head->Cena;
					}
				}
			}
		}
	}
}
//ciekawosta ASCII Art
void Pressx()
{
	puts("\t\t+------------------+ \n"
		"\t\t|       ___        |\n"
		"\t\t|   _  (,~ |   _   |\n"
		"\t\t|  (____/  |____)  |\n"
		"\t\t|  |||||    |||||  |\n"
		"\t\t|  |||||    |||||  |\n"
		"\t\t|  |||||\\  /|||||  |\n"
		"\t\t|  |||'//\\/\\\\`|||  |\n"
		"\t\t|  |' m' /\\ `m `|  |\n"
		"\t\t|       /||\\       |\n"
		"\t\t \\_              _/ \n"
		"\t\t   -------------- \n");

	printf("\t\tOrzelek uwu");
}
//funkcja pomocnicza do podawania daty do dodawania klientów i edycji listy klientów
void Data_Insert_Item(Lista_P head) {
	SYSTEMTIME st;
	GetLocalTime(&st);
	int pomoc;
Wybor5:
	printf("\n\nPodaj dzien miesiaca\n");
	pomoc = scanf("%d", &head->Dzien);
	if (pomoc != 1)
	{
		printf("\nPodaj liczbe, nie slowo.\n");
		Flush();
		goto Wybor5;
	}
	printf("\nPodaj miesiac\n");
	pomoc = scanf("%d", &(head)->Miesiac);
	if (pomoc != 1)
	{
		printf("\nPodaj liczbe, nie slowo.\n");
		Flush();
		goto Wybor5;
	}
	printf("\nPodaj rok\n");
	pomoc = scanf("%d", &(head)->Rok);
	if (pomoc != 1)
	{
		printf("\nPodaj liczbe, nie slowo.\n");
		Flush();
		goto Wybor5;
	}
	if ((head)->Rok > st.wYear)
	{
		printf("\nRok jest za duzy\n");
		Flush();
		goto Wybor5;
	}
	if ((head)->Rok < 0)
	{
		printf("\nCzemu podales ujemny rok? \n\n");
		Flush();
		goto Wybor5;
	}
	if (((head)->Rok == st.wYear) && (head)->Miesiac > st.wMonth)
	{
		printf("\nPodaj date przed dzisiejszym dniem\n");
		Flush();
		goto Wybor5;
	}
	if (((head)->Rok == st.wYear) && (head)->Miesiac == st.wMonth && (head)->Dzien > st.wDay)
	{
		printf("\nPodaj date przed dzisiejszym dniem.\n");
		Flush();
		goto Wybor5;
	}
	if ((head)->Miesiac > 12 || (head)->Miesiac < 1)
	{
		printf("\nMiesiac poza granicami\n\n");
		Flush();
		goto Wybor5;
	}
	if (((head)->Miesiac == 1
		|| (head)->Miesiac == 3
		|| (head)->Miesiac == 5
		|| (head)->Miesiac == 7
		|| (head)->Miesiac == 8
		|| (head)->Miesiac == 10
		|| (head)->Miesiac == 12) && ((head)->Dzien > 31 || (head)->Dzien < 1))
	{
		printf("\nPodales nieistniejacy dzien w 31-dniowych miesiacach\n\n");
		Flush();
		goto Wybor5;
	}
	if (((head)->Miesiac == 4
		|| (head)->Miesiac == 6
		|| (head)->Miesiac == 9
		|| (head)->Miesiac == 11) && ((head)->Dzien > 30 || (head)->Dzien < 1))
	{
		printf("\nPodales nieistniejacy dzien w 30-dniowych miesiacach\n\n");
		Flush();
		goto Wybor5;
	}
	if (((head)->Miesiac == 2) && (((head)->Rok % 4 == 0 && (head)->Rok % 100 == 0) || (head)->Rok % 4 != 0)
		&& ((head)->Dzien > 28 || (head)->Dzien < 1))
	{
		printf("\nPodales nieistniejacy dzien w nieprzestepnym lutym\n\n");
		Flush();
		goto Wybor5;
	}
	if (((head)->Miesiac == 2) && ((head)->Rok % 4 == 0 && (head)->Rok % 100 != 0)
		&& ((head)->Dzien > 29 || (head)->Dzien < 1))
	{
		printf("\nPodales nieistniejacy dzien w przestepnym lutym\n\n");
		Flush();
		goto Wybor5;
	}
	printf("%d.%d.%d", (head)->Dzien, (head)->Miesiac, (head)->Rok);
}
//wczytanie z pliku
int Wczytanie_z_pliku(Lista_P P, Lista_K K) {
	FILE* K1, * P1;
	int i = 0;
	if ((P1 = fopen("Przedmioty.txt", "r")) == NULL)
	{
		printf("Nie moge odczytac pliku Przedmioty.txt");
		return 1;
	}
	P1 = fopen("Przedmioty.txt", "r");
	fscanf(P1, "%d", &amount_Item);
	if (amount_Item <= 0)
		printf("Plik nie ma zadnych list");
	else
	{
		while (i < amount_Item)
		{
			fscanf(P1, "%d %s %d %d %d %d %d %d", &P->ID, P->Nazwa, &P->Stan,
				&P->Kwota_zastawy, &P->Cena, &P->Dzien, &P->Miesiac, &P->Rok);
			++i;
			ID_P = P->ID;
			Space_P(P);
			P = P->next;
		}
	}
	fclose(P1);
	i = 0;
	int j = 0;
	if ((K1 = fopen("Klienci.txt", "r")) == NULL)
	{
		printf("Nie moge odczytac pliku Klienci.txt");
		return 1;
	}
	K1 = fopen("Klienci.txt", "r");
	fscanf(K1, "%d", &amount_Customer);
	if (amount_Customer == 0)
		printf("Plik Klient.txt nie ma zadnych list");
	else
	{
		while (i < amount_Customer)
		{
			fscanf(K1, "%d%s%s%d%d", &K->ID, K->Imie, K->Nazwisko, &K->Kwota_wydana, &K->ILOSC);
			if (K->ILOSC == 0) { ; }
			else
			{
				j = 0;
				K->Lista = calloc(K->ILOSC, sizeof(char[51]));
				while (j < K->ILOSC)
				{
					fscanf(K1, "%s", K->Lista[j]);
					++j;
				}
			}
			++i;
			ID_K = K->ID;
			Space_K(K);
			K = K->next;
		}
	}
	fclose(K1);
}
//zapisanie do pliku
void Zapisanie_do_pliku(Lista_K K, Lista_P P) {
	FILE* K1, * P1;
	int i = 0;
	K1 = fopen("Klienci.txt", "w");
	fprintf(K1, "%d\n", amount_Customer);
	for (; K->next != NULL; K = K->next)
	{
		fprintf(K1, "%d %s %s %d %d ", K->ID, K->Imie, K->Nazwisko, K->Kwota_wydana, K->ILOSC);
		if (K->ILOSC == 0) {}
		else
			for (i = 0; i < K->ILOSC; ++i)
				fprintf(K1, "%s ", K->Lista[i]);
		fprintf(K1, "\n");
	}
	fclose(K1);
	P1 = fopen("Przedmioty.txt", "w");
	fprintf(P1, "%d\n", amount_Item);
	for (; P->next != NULL; P = P->next)
	{
		fprintf(P1, "%d %s %d %d %d %d %d %d\n", P->ID, P->Nazwa, P->Stan,
			P->Kwota_zastawy, P->Cena, P->Dzien, P->Miesiac, P->Rok);
	}
	fclose(P1);
}
//wypisanie elementów do listy klientów
void Wypisz_K(Lista_K head)
{
	if (amount_Customer == 0)
		printf("\n\nBrak elementow do wyswietlenia\n\n");
	else
	{
		int i = 0;
		for (; head->next != NULL; head = head->next)
		{
			printf("ID Klienta:%d\n", head->ID);
			printf("Imie Klienta:%s\n", head->Imie);
			printf("Nazwisko Klienta:%s\n", head->Nazwisko);
			printf("Kwota wydana w lombardzie:%d\n", head->Kwota_wydana);
			if (head->ILOSC == 0)
				printf("\tBrak przedmiotow do wyswietlenia\n");
			else
			{
				for (i = 0; i < head->ILOSC; ++i)
				{
					printf("\tPrzedmiot %d:%s\n", (i + 1), head->Lista[i]);
				}
				i = 0;
			}
		}
	}
}
//wypisanie elementów listy przedmiotów
void Wypisz_P(Lista_P head) {
	if (amount_Item == 0) printf("Brak elementow do wyswietlenia\n\n");
	else {
		for (; (head->next) != NULL; head = head->next)
		{
			printf("ID Przedmiotu:%d\n", head->ID);
			printf("Nazwa Przedmiotu:%s\n", head->Nazwa);
			printf("Stan przedmiotu:");
			if (head->Stan == 0)printf("Zastawiony\n");
			if (head->Stan == 1) printf("Kupiony\n");
			printf("Cena zastawienia:%d\n", head->Kwota_zastawy);
			printf("Cena przedmiotu na sprzedaz:%d\n", head->Cena);
			printf("Data wstawienia do Bazy Danych: %d.%d.%d\n", head->Dzien, head->Miesiac, head->Rok);
		}
	}
}
//wypisanie klientów po jego części lub całości
void Find_Nazwisko(Lista_K head) {
	int length1;
	int length2;
	int i;
	int j;
	int t;
	char help[51];
Wybor1:
	printf("Podaj nazwisko albo jego czesc:");
	scanf("%s", help);
	length1 = strlen(help);
	if (length1 >= 50)
	{
		printf("\nPodaj nazwisko o max 50 znakow\n");
		Flush();
		goto Wybor1;
	}
	Clear();
	for (; head->next != NULL; head = head->next)
	{
		j = 0;
		length2 = strlen(head->Nazwisko);
		if (length1 > length2)
			continue;
		else
		{
			for (i = 0; i < length1; ++i)
			{
				if (help[i] != head->Nazwisko[i])
				{
					j = 1;
					break;
				}
			}
			if (j == 0)
			{
				printf("ID Klienta:%d\n", head->ID);
				printf("Imie Klienta:%s\n", head->Imie);
				printf("Nazwisko Klienta:%s\n", head->Nazwisko);
				printf("Kwota wydana w lombardzie:%d\n", head->Kwota_wydana);
				if (head->ILOSC == 0)
					printf("Brak przedmiotow do wyswietlenia\n");
				else
				{
					for (t = 0; t < head->ILOSC; ++t)
					{
						printf("\tPrzedmiot %d:%s\n", (t + 1), head->Lista[t]);
					}
					t = 0;
				}
			}
		}
	}
}
//wypisanie klientów po kwocie wydanej zawartej w przedziale
void Find_Kwota_wydana(Lista_K* a) {
	int choice1, choice2, help;
	int i;
	Lista_K head = *a;
Wybor1:
	printf("\nPodaj przedzial cenowy z ktorego mam wyszukac dane:");
	help = scanf("%d %d", &choice1, &choice2);
	if (help == 0)
	{
		printf("\nPodales zle dane\n\n");
		Flush();
		goto Wybor1;
	}
	if (choice1 > choice2)
	{
		printf("\nPierwszy argument jest za duzy\n\n");
		Flush();
		goto Wybor1;
	}
	Clear();
	for (; head->next != NULL; head = head->next)
	{
		if (head->Kwota_wydana >= choice1 && head->Kwota_wydana <= choice2)
		{
			printf("ID Klienta:%d\n", head->ID);
			printf("Imie Klienta:%s\n", head->Imie);
			printf("Nazwisko Klienta:%s\n", head->Nazwisko);
			printf("Kwota wydana w lombardzie:%d\n", head->Kwota_wydana);
			if (head->ILOSC == 0)
				printf("Brak przedmiotow do wyswietlenia\n");
			else
			{
				for (i = 0; i < head->ILOSC; ++i)
				{
					printf("\tPrzedmiot %d:%s\n", (i + 1), head->Lista[i]);
				}
				i = 0;
			}
		}
	}
}
//wypisanie przedmiotu po stanie przedmiotu (kupiony lub zastawiony)
void Find_Stan(Lista_P* a) {
	Lista_P head = *a;
	int help;
	int choice;
Wybor1:
	printf("Podaj stan przedmiotow, ktory chcesz wyswietlic(0 dla zastawionego, 1 dla kupionego):");
	help = scanf("%d", &choice);
	if (help == 0)
	{
		printf("\nPodaj liczbe, nie slowo\n\n");
		Flush();
		goto Wybor1;
	}
	if (choice != 0 && choice != 1)
	{
		printf("\nMiales podac 1 albo 0\n\n");
		Flush();
		goto Wybor1;
	}
	Clear();
	if (choice == 0)
	{
		for (; head->next != NULL; head = head->next)
		{
			if (head->Stan == 0)
			{
				printf("ID Przedmiotu:%d\n", head->ID);
				printf("Nazwa Przedmiotu:%s\n", head->Nazwa);
				printf("Stan przedmiotu:");
				printf("Zastawiony\n");
				printf("Cena zastawienia:%d\n", head->Kwota_zastawy);
				printf("Cena przedmiotu na sprzedaz:%d\n", head->Cena);
				printf("Data wstawienia do Bazy Danych: %d.%d.%d\n", head->Dzien, head->Miesiac, head->Rok);
			}
		}
	}
	else
	{
		for (; head->next != NULL; head = head->next)
		{
			if (head->Stan == 1)
			{
				printf("ID Przedmiotu:%d\n", head->ID);
				printf("Nazwa Przedmiotu:%s\n", head->Nazwa);
				printf("Stan przedmiotu:");
				printf("Kupiony\n");
				printf("Cena zastawienia:%d\n", head->Kwota_zastawy);
				printf("Cena przedmiotu na sprzedaz:%d\n", head->Cena);
				printf("Data wstawienia do Bazy Danych: %d.%d.%d\n", head->Dzien, head->Miesiac, head->Rok);
			}
		}
	}
}
//wypisanie przedmiotu po cenie zawartej w przedziale
void Find_Cena(Lista_P* a) {
	int choice1, choice2, help;
	Lista_P head = *a;
Wybor1:
	printf("\nPodaj przedzial cenowy z ktorego mam wyszukac dane:");
	help = scanf("%d %d", &choice1, &choice2);
	if (help == 0)
	{
		printf("\nPodales zle dane\n\n");
		Flush();
		goto Wybor1;
	}
	if (choice1 > choice2)
	{
		printf("Pierwszy argument jest za duzy\n\n");
		Flush();
		goto Wybor1;
	}
	Clear();
	for (; head->next != NULL; head = head->next)
	{
		if (head->Cena >= choice1 && head->Cena <= choice2)
		{
			printf("ID Przedmiotu:%d\n", head->ID);
			printf("Nazwa Przedmiotu:%s\n", head->Nazwa);
			printf("Stan przedmiotu:");
			if (head->Stan == 0)
				printf("Zastawiony\n");
			if (head->Stan == 1)
				printf("Kupiony\n");
			printf("Cena zastawienia:%d\n", head->Kwota_zastawy);
			printf("Cena przedmiotu na sprzedaz:%d\n", head->Cena);
			printf("Data wstawienia do Bazy Danych: %d.%d.%d\n", head->Dzien, head->Miesiac, head->Rok);
		}
	}
}
//funkcja pomocnicza do funkcji Find_Date()
bool check_Date(Lista_P a, int d1, int m1, int r1, int d2, int m2, int r2) {
	if (r1 < a->Rok && r2 > a->Rok)
		return true;
	else if (r1 <= a->Rok && r2 >= a->Rok)
	{
		if (m1< a->Miesiac && m2 > a->Miesiac)
			return true;
		else if (m1 <= a->Miesiac && m2 >= a->Miesiac)
		{
			if (d1 <= a->Dzien && d2 >= a->Dzien)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}
//wypisanie przedmiotów w których daty są zawarte w przedziale
void Find_Date(Lista_P* a) {
	int help;
	int d1, d2, m1, m2, r1, r2;
	Lista_P head = *a;
Wybor1:
	printf("Podaj dzien, miesiac i rok dolnego zakresu:");
	help = scanf("%d %d %d", &d1, &m1, &r1);
	if (help == 0)
	{
		printf("Podaj liczbe, nie slowo");
		Flush();
		goto Wybor1;
	}
Wybor2:
	printf("\n\nPodaj dzien, miesiac i rok gornego zakresu:");
	help = scanf("%d %d %d", &d2, &m2, &r2);
	if (help == 0)
	{
		printf("Podaj liczbe, nie slowo");
		Flush();
		goto Wybor2;
	}
	Clear();
	for (; head->next != NULL; head = head->next)
	{
		if (check_Date(head, d1, m1, r1, d2, m2, r2) == true)
		{
			printf("ID Przedmiotu:%d\n", head->ID);
			printf("Nazwa Przedmiotu:%s\n", head->Nazwa);
			printf("Stan przedmiotu:");
			if (head->Stan == 0)
				printf("Zastawiony\n");
			if (head->Stan == 1)
				printf("Kupiony\n");
			printf("Cena zastawienia:%d\n", head->Kwota_zastawy);
			printf("Cena przedmiotu na sprzedaz:%d\n", head->Cena);
			printf("Data wstawienia do Bazy Danych: %d.%d.%d\n", head->Dzien, head->Miesiac, head->Rok);
		}
	}
}
//edytowanie przedmiotu
void Edit_Item(Lista_P* Przedmiot) {
	if (amount_Item == 0)
		printf("Brak danych do usuniecia\n\n");
	else
	{
		Lista_P head = *Przedmiot;
		int pomoc;
		char choice;
		int wybor;
	Wybor0a:
		printf("Podaj ID przedmiotu, ktory chcesz usunac:\n");
		printf("\tJezeli sie rozmysliles, podaj \"0\":");
		pomoc = scanf("%d", &wybor);
		if (pomoc == 0)
		{
			printf("Podaj liczbe, nie slowo\n\n\n");
			Flush();
			goto Wybor0a;
		}
		for (; (head)->next != NULL; head = (head)->next)
		{
			if (wybor == (head)->ID)
			{
			Wybor0b:
				MenuOptions_Function_Item();
				Flush();
				printf("Wybierz opcje:");
				pomoc = scanf("%c", &choice);
				if (pomoc == 0)
				{
					printf("Podaj liczbe, nie slowo\n\n\n");
					Flush();
					goto Wybor0b;
				}
				switch (choice)
				{
				case '1':
				Wybor1:
					printf("Podaj Nazwe przedmiotu (do 50 znakow)\n");
					scanf("%s", (head)->Nazwa);
					if (strlen((head)->Nazwa) >= 50)
					{
						printf("Podaj max 50 znakow\n");
						goto Wybor1;
					}
					pomoc = 2;
					break;
				case '2':
				Wybor2:
					printf("\n\nPodaj stan przedmiotu. Zastawiony(0) lub kupiony(1)\n");
					pomoc = scanf("%d", &(head)->Stan);
					if (pomoc != 1)
					{
						printf("Podaj liczbe, nie slowo.\n");
						Flush();
						goto Wybor2;
					}
					if ((head)->Stan != 1 && (head)->Stan != 0)
					{
						printf("Liczba to 1 lub 0. Podaj prawidlowe.\n");
						Flush();
						goto Wybor2;
					}
					pomoc = 2;
					break;
				case '3':
				Wybor3:
					printf("\n\nPodaj cene zastawienia.\n");
					pomoc = scanf("%d", &(head)->Kwota_zastawy);
					if (pomoc != 1)
					{
						printf("Podaj liczbe, nie slowo.\n");
						Flush();
						goto Wybor3;
					}
					if ((head)->Kwota_zastawy < 0)
					{
						printf("Nie podawaj ujemnej ceny\n");
						Flush();
						goto Wybor3;
					}

					break;
				case '4':
				Wybor4:
					printf("Podaj cene przedmiotu, jesli dlug nie zostal splacony.\n");
					pomoc = scanf("%d", &(head)->Cena);
					if (pomoc != 1)
					{
						printf("Podaj liczbe, nie slowo.\n");
						Flush();
						goto Wybor4;
					}
					if ((head)->Cena < 0)
					{
						printf("Nie podawaj ujemnej ceny\n");
						Flush();
						goto Wybor4;
					}
					break;
				case '5':
					Data_Insert_Item(head);
					break;
				default: printf("Podales zla opcje. Podaj jeszcze raz.\n\n"); goto Wybor0b;
				}
				break;
			}
		}
	}
}
//edytowanie klienta
void Edit_Customer(Lista_K* Klient) {
	if (amount_Customer == 0)
		printf("Brak danych do edytowania");
	else
	{
		int choice;
		int wybor;
		Lista_K head = *Klient;
		int pomoc;
	Wybor0a:
		printf("Podaj ID Klienta, ktore chcesz zedytowac:\n");
		printf("\tJezeli sie rozmysliles, podaj \"0\":");
		pomoc = scanf("%d", &wybor);
		if (pomoc == 0)
		{
			printf("Podaj liczbe, nie slowo\n\n\n");
			Flush();
			goto Wybor0a;
		}
		for (; (head)->next != NULL; head = (head)->next)
		{
			if (wybor == (head)->ID)
			{
			Wybor0b:
				MenuOptions_Function_Customer();
				Flush();
				printf("Wybierz opcje:");
				pomoc = scanf("%c", &choice);
				if (choice == 0)
				{
					printf("Podaj liczbe, nie slowo\n\n\n");
					Flush();
					goto Wybor0b;
				}
				switch (choice)
				{
				case '1':
				Wybor1:
					printf("Podaj imie (max 30 znakow):");
					scanf("%s", (head->Imie));
					if (strlen(head->Imie) >= 30)
					{
						printf("Twoje imie jest za dlugie");
						Flush();
						goto Wybor1;
					}
					wybor = 2;
					break;
				case '2':
				Wybor2:
					printf("Podaj nazwisko(max 50 znakow):");
					scanf("%s", head->Nazwisko);
					if (strlen(head->Nazwisko) >= 50)
					{
						printf("Twoje nazwisko jest za dlugie");
						Flush();
						goto Wybor2;
					}
					wybor = 2;
					break;
				case '3':
					Flush();
					int liczba;
					liczba = head->ILOSC;
					head->ILOSC = 0;
					char r;
					int i = 0;
					printf("\n1.\nJezeli chcesz dodac przedmiot, nacisnij \"t\". Jezeli nie chcesz dodawac nacisnij \"n\" :");
					do
					{
						scanf("%c", &r);
						switch (r)
						{
						case 't':
						Wybor3:
							if (i == 0)
							{
								if (liczba == 0)
									head->Lista = calloc(head->ILOSC, sizeof(char[51]));
								else if (liczba != 1)
									head->Lista = realloc(head->Lista, 1 * sizeof(char[51]));
							}
							else
								head->Lista = realloc(head->Lista, (i + 1) * sizeof(char[51]));
							printf("\nPodaj nazwe przedmiotu:");
							scanf("%s", head->Lista[i]);
							if (strlen(head->Lista[i]) >= 50)
							{
								printf("Za duzo znakow\n\n");
								Flush();
								goto Wybor3;
							}
							++i;
							++(head->ILOSC);
							printf("\n\tNacisnij enter, aby przejsc dalej");
							break;
						case 'n':
							break;
						default:
							if (r != 't')
								Flush();
							printf("\n%d\nJezeli chcesz dodac przedmiot, nacisnij \"t\". Jezeli nie chcesz dodawac nacisnij \"n\":", (i + 1));
							break;
						}

					} while (r != 'n' && r != 'N');
					wybor = 2;
					break;
				}
			}
		}
		if (wybor != 2) printf("\nNie znaleziono ID.\n\n");
	}

}
//usuwanie przedmiotu z listy
int Delete_Item(Lista_P* Przedmiot) {
	if (amount_Item == 0)
		printf("\nBrak danych do usuniecia.\n\n");
	else
	{
		int choice;
		int i = 1;
		int pomoc;
		Lista_P head = *Przedmiot;
		Lista_P help;
		Lista_P Pomoc_P = (*Przedmiot);
		Lista_P Pomoc_P2 = (*Przedmiot);
	Wybor1:
		printf("\nPodaj ID przedmiotu, ktory chcesz usunac:\n");
		printf("\tJezeli sie rozmysliles, podaj \"0\":");
		pomoc = scanf("%d", &choice);
		if (pomoc == 0)
		{
			printf("\nPodaj liczbe, nie slowo\n\n");
			Flush();
			goto Wybor1;
		}
		for (; (head)->next != NULL; head = (head)->next)
		{
			if (i != 1)
			{
				Pomoc_P = (Pomoc_P)->next;
				if (i != 2)
					Pomoc_P2 = (Pomoc_P2)->next;
			}
			if (choice == (head)->ID)
			{
				if (head->Stan == 1)
				{
					printf("\nDany przedmiot jest kupiony. Nie mozna go usunac\n\n");
					return 1;
				}
				//pierwszy
				if (i == 1)
				{
					if (amount_Item != 1)
						*Przedmiot = (*Przedmiot)->next;
					free(head);
					--amount_Item;
					pomoc = 2;
					break;
				}
				//ostatni
				else if (i == amount_Item)
				{
					Pomoc_P->next = NULL;
					free(Pomoc_P->next);
					--amount_Item;
					pomoc = 2;
					break;
				}
				//kazdy inny
				else
				{
					help = (Pomoc_P->next);
					free(Pomoc_P2->next);
					Pomoc_P2->next = help;
					--amount_Item;
					pomoc = 2;
					break;
				}
			}
			++i;
		}
		if (pomoc != 2)printf("Nie ma takiego ID.\n\n");
	}
}
//usuwanie klienta z listy
void Delete_Customer(Lista_K* Customer) {
	if (amount_Customer == 0)
		printf("\nBrak danych do usuniecia.\n\n");
	else
	{
		int pomoc;
		int wybor;
		int i = 1;
		Lista_K Pomoc_K = *Customer;
		Lista_K Pomoc_K2 = *Customer;
		Lista_K head = *Customer;
		Lista_K help;
	Wybor1:
		printf("\nPodaj ID Klienta do usuniecia:\n");
		printf("\t\nJezeli sie rozmysliles, podaj \"0\":");
		pomoc = scanf("%d", &wybor);
		if (pomoc == 0)
		{
			printf("\nPodaj liczbe, nie slowo\n\n");
			Flush();
			goto Wybor1;
		}
		for (; (head)->next != NULL; head = (head)->next)
		{
			if (i != 1)
			{
				Pomoc_K = (Pomoc_K)->next;
				if (i != 2)
					Pomoc_K2 = (Pomoc_K2)->next;
			}
			if (wybor == (head)->ID)
			{
				//pierwszy
				if (i == 1)
				{
					if (amount_Customer != 1)
						*Customer = (*Customer)->next;
					free(head);
					--amount_Customer;
					pomoc = 2;
					break;
				}
				//ostatni
				else if (i == amount_Customer)
				{
					Pomoc_K->next = NULL;

					free(Pomoc_K->next);
					--amount_Customer;
					pomoc = 2;
					break;
				}
				//kazdy inny
				else
				{
					help = (Pomoc_K->next);
					free(Pomoc_K2->next);
					Pomoc_K2->next = help;
					--amount_Customer;
					pomoc = 2;
					break;
				}
			}
			++i;
		}
		if (pomoc != 2)
			printf("Nie ma takiego ID.");
	}
}
//dodawanie przedmiotu do listy 
void Add_Item(Lista_P head) {

	int i = 0;


	int pomoc;
	if (amount_Item != 0)
		for (; (head)->next != NULL; head = (head)->next) {}

	(head)->ID = (ID_P + 1);
	++ID_P;


Wybor1:
	printf("Podaj Nazwe przedmiotu(do 50 znakow)\n");
	scanf("%s", (head)->Nazwa);
	if (strlen((head)->Nazwa) >= 50)
	{
		printf("Podaj max 50 znakow\n");
		goto Wybor1;
	}
Wybor2:
	printf("\n\nPodaj stan przedmiotu. Zastawiony(0) lub kupiony(1):");
	pomoc = scanf("%d", &(head)->Stan);
	if (pomoc != 1)
	{
		printf("Podaj liczbe, nie slowo.\n");
		Flush();
		goto Wybor2;
	}
	if ((head)->Stan != 1 && (head)->Stan != 0)
	{
		printf("Liczba to 1 lub 0. Podaj prawidlowe.\n");
		Flush();
		goto Wybor2;
	}
Wybor3:
	printf("\n\nPodaj cene zastawienia.\n");
	pomoc = scanf("%d", &(head)->Kwota_zastawy);
	if (pomoc != 1)
	{
		printf("Podaj liczbe, nie slowo.\n");
		Flush();
		goto Wybor3;
	}
	if ((head)->Kwota_zastawy < 0)
	{
		printf("Nie podawaj ujemnej ceny\n");
		Flush();
		goto Wybor3;
	}
Wybor4:

	printf("Podaj cene przedmiotu, jesli dlug nie zostal splacony.\n");
	pomoc = scanf("%d", &(head)->Cena);
	if (pomoc != 1)
	{
		printf("Podaj liczbe, nie slowo.\n");
		Flush();
		goto Wybor4;
	}
	if ((head)->Cena < 0)
	{
		printf("Nie podawaj ujemnej ceny\n");
		Flush();
		goto Wybor4;
	}
	Data_Insert_Item(head);
	++amount_Item;
}
//dodawanie klienta do listy
void Add_Customer(Lista_K Klient)
{
	int i = 0;
	char r;
	if (amount_Customer != 0)
		for (; Klient->next != NULL; Klient = Klient->next) {}

	Klient->ID = (ID_K + 1);
	++ID_K;
Wybor1:
	printf("Podaj imie(max 30 znakow):");
	scanf("%s", ((Klient)->Imie));
	if (strlen((Klient)->Imie) > 30)
	{
		printf("\nTwoje imie jest za dlugie.\n\n");
		Flush();
		goto Wybor1;
	}
Wybor2:

	printf("Podaj nazwisko(max 50):");
	scanf("%s", (Klient)->Nazwisko);
	if (strlen((Klient)->Nazwisko) > 50)
	{
		printf("\nTwoje nazwisko jest za dlugie\n\n");
		Flush();
		goto Wybor2;
	}
	Flush();

	Klient->ILOSC = 0;
	printf("\n1.\nJezeli chcesz dodac przedmiot, nacisnij \"t\". Jezeli nie chcesz dodawac nacisnij \"n\":");
	do
	{
		scanf("%c", &r);
		switch (r)
		{
		case 't':
			if (i == 0)
				Klient->Lista = calloc(1, sizeof(char[51]));
			else
				Klient->Lista = realloc(Klient->Lista, sizeof(char[51]) * (i + 1));
		Wybor3:
			printf("\nPodaj nazwe przedmiotu\n");
			scanf("%s", Klient->Lista[i]);
			if (strlen(Klient->Lista[i]) >= 50)
			{
				printf("\nZa duzo znakow\n");
				Flush();
				goto Wybor3;
			}
			++i;
			++(Klient->ILOSC);
			printf("\n\tNacisnij enter, by przejsc dalej\n");
			break;
		case 'n':
			break;
		default:
			if (r != 't')
				Flush();
			printf("\n%d\nJezeli chcesz dodac przedmiot, nacisnij \"t\". Jezeli nie chcesz dodawac nacisnij \"n\":", (i + 1));
			break;
		}
	} while (r != 'n' && r != 'N');
	++amount_Customer;
}
//funkcja pomocnicza do funkcji BubbleSort_Nazwisko_Customer()
bool Check_Nazwisko(Lista_K head, Lista_K nexthead) {
	int i;
	int dlugosc_head = strlen(head->Nazwisko);
	int dlugosc_nexthead = strlen(nexthead->Nazwisko);
	int dlugosc;
	if (dlugosc_head > dlugosc_nexthead)
		dlugosc = dlugosc_nexthead;
	else
		dlugosc = dlugosc_head;
	char slowo1[51], slowo2[51];
	strcpy(slowo1, head->Nazwisko);
	strcpy(slowo2, nexthead->Nazwisko);
	for (i = 0; i < dlugosc_head; ++i)
	{
		if (slowo1[i] >= 'A' && slowo1[i] <= 'Z')
			slowo1[i] += 32;
	}
	for (i = 0; i < dlugosc_nexthead; ++i)
	{
		if (slowo2[i] >= 'A' && slowo2[i] <= 'Z')
			slowo2[i] += 32;
	}
	if (strcmp(slowo1, slowo2) == 0)
		return false;
	for (i = 0; i < dlugosc; ++i)
	{
		if (slowo1[i] > slowo2[i])
		{
			return true;
		}
		if (slowo1[i] < slowo2[i])
			return false;
	}
	return false;
}
//sortowanie bąbelkowe po nazwisku klientów
void BubbleSort_Nazwisko_Customer(Lista_K* a) {
	Lista_K head = *a;
	int i, j;

	for (i = 0; i < amount_Customer - 1; i++)
	{
		head = *a;
		Lista_K prevhead = NULL;
		for (j = 0; j < amount_Customer - i - 1; j++)
		{
			Lista_K    nexthead = head->next;

			if (Check_Nazwisko(head, nexthead) == true)
			{
				if (j == 0)
				{
					head->next = nexthead->next;
					nexthead->next = head;
					*a = nexthead;
					prevhead = *a;
				}
				else
				{
					prevhead->next = nexthead;
					head->next = nexthead->next;
					nexthead->next = head;
					prevhead = nexthead;
				}
			}
			else
			{
				prevhead = head;
				head = head->next;
			}
		}
	}
}
//sortowanie babelkowe po ID klienta
void BubbleSort_ID_Customer(Lista_K* a) {
	Lista_K head = *a;
	int i, j;
	for (i = 0; i < amount_Customer - 1; i++) {
		head = *a;
		Lista_K prevhead = NULL;
		for (j = 0; j < amount_Customer - i - 1; j++) {
			Lista_K    nexthead = head->next;
			if (head->ID > nexthead->ID)
			{
				if (j == 0)
				{
					head->next = nexthead->next;
					nexthead->next = head;
					*a = nexthead;
					prevhead = *a;
				}
				else
				{
					prevhead->next = nexthead;
					head->next = nexthead->next;
					nexthead->next = head;
					prevhead = nexthead;
				}
			}
			else {
				prevhead = head;
				head = head->next;
			}
		}
	}
}
//sortowanie babelkowe kwoty wydanej w liście Klienci
void BubbleSort_Kwota_wydana_Customer(Lista_K* a) {
	Lista_K head = *a;
	int i, j;

	for (i = 0; i < amount_Customer - 1; i++) {
		head = *a;
		Lista_K prevhead = NULL;
		for (j = 0; j < amount_Customer - i - 1; j++) {
			Lista_K    nexthead = head->next;
			if (head->Kwota_wydana > nexthead->Kwota_wydana)
			{
				if (j == 0)
				{
					head->next = nexthead->next;
					nexthead->next = head;
					*a = nexthead;
					prevhead = *a;
				}
				else
				{
					prevhead->next = nexthead;
					head->next = nexthead->next;
					nexthead->next = head;
					prevhead = nexthead;
				}
			}
			else
			{
				prevhead = head;
				head = head->next;
			}
		}
	}
}
//sortowanie babelkowe po ID przedmiotu
void BubbleSort_ID_Item(Lista_P* a) {
	Lista_P head = *a;
	int i, j;
	for (i = 0; i < amount_Item - 1; i++) {
		head = *a;
		Lista_P prevhead = NULL;
		for (j = 0; j < amount_Item - i - 1; j++) {
			Lista_P   nexthead = head->next;
			if (head->ID > nexthead->ID)
			{
				if (j == 0)
				{
					head->next = nexthead->next;
					nexthead->next = head;
					*a = nexthead;
					prevhead = *a;
				}
				else
				{
					prevhead->next = nexthead;
					head->next = nexthead->next;
					nexthead->next = head;
					prevhead = nexthead;
				}
			}
			else {
				prevhead = head;
				head = head->next;
			}
		}
	}
}
//funkcja pomocnicza do funkcji BubbleSort_Nazwa_Item
bool Check_Nazwa(Lista_P head, Lista_P nexthead) {
	int i;
	int dlugosc_head = strlen(head->Nazwa);
	int dlugosc_nexthead = strlen(nexthead->Nazwa);
	int dlugosc;
	if (dlugosc_head > dlugosc_nexthead)
		dlugosc = dlugosc_nexthead;
	else
		dlugosc = dlugosc_head;
	char slowo1[51], slowo2[51];
	strcpy(slowo1, head->Nazwa);
	strcpy(slowo2, nexthead->Nazwa);
	for (i = 0; i < dlugosc_head; ++i)
	{
		if (slowo1[i] >= 'A' && slowo1[i] <= 'Z')
			slowo1[i] += 32;
	}
	for (i = 0; i < dlugosc_nexthead; ++i)
	{
		if (slowo2[i] >= 'A' && slowo2[i] <= 'Z')
			slowo2[i] += 32;
	}
	if (strcmp(slowo1, slowo2) == 0)
		return false;
	for (i = 0; i < dlugosc; ++i)
	{
		if (slowo1[i] > slowo2[i])
		{
			return true;
		}
		if (slowo1[i] < slowo2[i])
			return false;
	}
	return false;
}
//sortowanie bąbelkowe po nazwie przedmiotu
void BubbleSort_Nazwa_Item(Lista_P* a) {
	Lista_P head = *a;
	int i, j;

	for (i = 0; i < amount_Item - 1; i++) {
		head = *a;
		Lista_P prevhead = NULL;
		for (j = 0; j < amount_Item - i - 1; j++) {
			Lista_P    nexthead = head->next;
			if (Check_Nazwa(head, nexthead) == true)
			{
				if (j == 0)
				{
					head->next = nexthead->next;
					nexthead->next = head;
					*a = nexthead;
					prevhead = *a;
				}
				else
				{
					prevhead->next = nexthead;
					head->next = nexthead->next;
					nexthead->next = head;
					prevhead = nexthead;
				}
			}
			else
			{
				prevhead = head;
				head = head->next;
			}
		}
	}
}
//funkcja pomocnicza do funkcji BubbleSort_Date_Item()
bool dateCheck(Lista_P head, Lista_P nexthead) {
	if (head->Rok > nexthead->Rok) return true;
	else if (nexthead->Rok < nexthead->Rok) return false;
	else {
		if (head->Miesiac > nexthead->Miesiac) return true;
		else if (head->Miesiac < nexthead->Miesiac) return false;
		else {
			if (head->Dzien > nexthead->Dzien) return true;
			else return false;
		}
	}
}
//sortowanie bąbelkowe po dacie wystawienia
void BubbleSort_Date_Item(Lista_P* a) {
	Lista_P head = *a;
	int i, j;
	for (i = 0; i < amount_Item - 1; i++) {
		head = *a;
		Lista_P prevhead = NULL;
		for (j = 0; j < amount_Item - i - 1; j++) {
			Lista_P   nexthead = head->next;
			if (dateCheck(head, nexthead) == true)
			{
				if (j == 0)
				{
					head->next = nexthead->next;
					nexthead->next = head;
					*a = nexthead;
					prevhead = *a;
				}
				else
				{
					prevhead->next = nexthead;
					head->next = nexthead->next;
					nexthead->next = head;
					prevhead = nexthead;
				}
			}
			else {
				prevhead = head;
				head = head->next;
			}
		}
	}
}
//ponowne zapelnienie ID przedmiotow(do stosowania przy duzej ilosci ID)
void Refill_ID_Item(Lista_P head) {
	ID_P = 0;
	for (; head->next != NULL; head = head->next)
	{
		++ID_P;
		head->ID = ID_P;
	}
}
//ponowne zapelnienie ID klientow(do stosowania przy duzej ilosci ID) 
void Refill_ID_Customer(Lista_K head) {
	ID_K = 0;
	for (; head->next != NULL; head = head->next)
	{
		++ID_K;
		head->ID = ID_K;
	}
}

int main()
{
	//zadeklarowanie Listy Klientow
	Lista_K Customer;
	Customer = (Lista_K)malloc(sizeof(Klient));
	Customer->next = NULL;
	//zadeklarowanie Listy Przedmiotow
	Lista_P Item;
	Item = (Lista_P)malloc(sizeof(Przedmiot));
	Item->next = NULL;
	Lista_K pocz = Customer;
	//wczytanie plikow i ewentualne wyjscie, gdy pliki nie isnieja                            
	if (Wczytanie_z_pliku(Item, Customer) == 1)
		return 0;
	char ch;
	Clear();
	MenuOptions();
	do
	{
		scanf("%c", &ch);
		printf("\n\n\n\n");
		switch (ch)
		{
		case 'a':
			Clear();
			Add_Customer(Customer);
			Space_K(Customer);
			Refill(Customer, Item);
			Clear();
			Wypisz_K(Customer);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'b':
			Clear();
			BubbleSort_ID_Customer(&Customer);
			Wypisz_K(Customer);
			printf("\n\n");
			Delete_Customer(&Customer);
			Clear();
			Wypisz_K(Customer);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'c':
			Clear();
			BubbleSort_ID_Customer(&Customer);
			Wypisz_K(Customer);
			printf("\n\n");
			Edit_Customer(&Customer);
			Clear();
			Refill(Customer, Item);
			Wypisz_K(Customer);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'd':
			Clear();
			BubbleSort_ID_Customer(&Customer);
			Wypisz_K(Customer);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'e':
			Clear();
			BubbleSort_Nazwisko_Customer(&Customer);
			Wypisz_K(Customer);
			Flush(); printf("\n\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'f':
			Clear();
			BubbleSort_Kwota_wydana_Customer(&Customer);
			Wypisz_K(Customer);
			Flush(); printf("\n\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'g':
			Clear();
			BubbleSort_ID_Customer(&Customer);
			Wypisz_K(Customer);
			printf("\n\n");
			Find_Nazwisko(Customer);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'h':
			Clear();
			BubbleSort_ID_Customer(&Customer);
			Wypisz_K(Customer);
			printf("\n\n");
			Find_Kwota_wydana(&Customer);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'i':
			Clear();
			Add_Item(Item);
			Space_P(Item);
			Clear();
			Wypisz_P(Item);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'j':
			Clear();
			BubbleSort_ID_Item(&Item);
			Wypisz_P(Item);
			if (Delete_Item(&Item) != 1)
			{
				Clear();
				Wypisz_P(Item);
			}
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'k':
			Clear();
			BubbleSort_ID_Item(&Item);
			Wypisz_P(Item);
			Edit_Item(&Item);
			Clear();
			Wypisz_P(Item);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'l':
			Clear();
			BubbleSort_ID_Item(&Item);
			Wypisz_P(Item);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'm':
			Clear();
			BubbleSort_Nazwa_Item(&Item);
			Wypisz_P(Item);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'n':
			Clear();
			BubbleSort_Date_Item(&Item);
			Wypisz_P(Item);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'o':
			Clear();
			BubbleSort_ID_Item(&Item);
			Wypisz_P(Item);
			printf("\n\n");
			Find_Stan(&Item);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'p':
			Clear();
			BubbleSort_ID_Item(&Item);
			Wypisz_P(Item);
			printf("\n\n");
			Find_Cena(&Item);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'r':
			Clear();
			BubbleSort_ID_Item(&Item);
			Wypisz_P(Item);
			printf("\n\n");
			Find_Date(&Item);
			Flush(); printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 's':
			Clear();
			break;
		case 'x':
			Clear();
			Pressx();
			printf("\n");
			Flush();
			printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'y':
			Refill_ID_Item(Item);
			Refill_ID_Customer(Customer);
			Clear();
			printf("ID pomyslnie przypisane");
			Flush();
			printf("\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'z':
			Clear();
			BubbleSort_ID_Customer(&Customer);
			BubbleSort_ID_Item(&Item);
			Zapisanie_do_pliku(Customer, Item);
			printf("Zapisano pomyslnie\n");
			Flush(); printf("\n\n\tWcisnij enter, by przejsc dalej\n\n");
			break;
		case 'q':
			break;
		default:
			Clear();
			MenuOptions();
		}
		Refill(Customer, Item);
	} while (ch != 'q');
	Clear();
}