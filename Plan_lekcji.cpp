#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <stdlib.h>
using namespace std;


void day() {

    cout << "Wybierz dzien tygodnia:\n";
    cout << "1. Poniedzialek\n";
    cout << "2. Wtorek\n";
    cout << "3. Sroda\n";
    cout << "4. Czwartek\n";
    cout << "5. Piatek\n";
    cout << "Wybierz opcje (1-5): ";


}

string Read(string tab[], int day, int i) {
    
    //Wybrano return ze względu na możliwość wypisania tylko wybranych danych, nie wszystkich
    
    switch (day) {
    case 1:
        return tab[i]; //zwraca wiersz w zależności od wyboru godziny (i  = godzina lekcyjna)
        break;
    case 2:
        return tab[10 + i]; //dodajemy 10 bo tablica zawiera cały plik txt, wtorek zaczyna się od 10 wiersza
        break;
    case 3:
        return tab[20 + i]; 
        break;
    case 4:
        return tab[30 + i];
        break;
    case 5:
        return tab[40 + i];
        break;
    }
}

void NumericRead(string tab[],int dayResult) {
    
    cout << Read(tab, dayResult, 0) << endl; //wypisuję dzień tygodnia, ponieważ jedyny nie jest numerowany
    for (int i = 0; i <= 9; i++) {
        if (i > 0) { //warunek, dzięki któremu lekcja nie będzie się zaczynać od 0
            cout << i << ". " << Read(tab, dayResult, i) << endl; //wypisuje lekcje z numerem
        }
    }
}

void ReadFile(string tab[]) {

    int i = 0; //zawiera numer wiersza w tabeli
    string wiersz;
    ifstream plan;

    plan.open("data.txt");
    if (plan.is_open()) { //jeżeli plan jest otwarty to ma do tabeli dodać wszystkie wiersze z pliku txt, dopóki znajdzie linię do wypisania z pliku
        while (getline(plan, wiersz)) {
            tab[i] = wiersz; i++;
        }
        plan.close();
    }
    else {
        cout << "Nie udalo sie otworzyc pliku\n";
    }
}

void Edit(string tab[], int dayResult, int hour, string newLesson) {
    int startPosition = 12; //liczba znaków od którego zaczyna się nazwa przedmiotu w wierszu
    string DefaultLesson = Read(tab, dayResult, hour); //cała linia z wybranej lekcji w danym dniu
    string toChange = DefaultLesson.substr(startPosition, DefaultLesson.back()); //lekcja która będzie zmieniona
    string hourLesson = DefaultLesson.substr(0,11);//sama godzina lekcji
    dayResult--; //dekrementacja, aby przy wyborze dnia tygodnia nie podmieniło następnego dnia tygodnia, zamiast wymaganego
    tab[(10 * dayResult) + hour] = hourLesson + " " + newLesson; //do tablicy wrzucamy nowy wiersz 
}

void Save(string tab[]) {
    int i = 0; //zawiera numer wiersza w tabeli
    string wiersz;
    ofstream plan;

    plan.open("data.txt");
    if (plan.is_open()) {
        while (plan) {
            plan << tab[i] << endl; i++; //zapisuje wiersz po wierszu dane z tabeli do pliku txt, wliczając odstęp
        }
        plan.close();
        cout << "Zapisano!\n";
    }
    else {
        cout << "Nie udalo sie otworzyc pliku\n";
    }

}

void Help() {
    cout << "Odczytaj - odczytuje plan zajec z podanego dnia tygodnia\n";
    cout << "Edytuj - pozwala na dokonanie korekty istniejacego planu\n";
    cout << "Zapisz - pozwala wprowadzic nowe dane do planu\n";
    cout << "Pomoc - pozwala uzyskac informacje na temat dzialania programu\n";
    cout << "Zakoncz - konczy dzialanie programu\n";
    cout << endl;
}

void drop(string tab[], int dayResult, int hour) {
    //wyjaśnienie: linijka 73
    int startPosition = 12;
    string DefaultLesson = Read(tab, dayResult, hour); 
    string toChange = DefaultLesson.substr(startPosition, DefaultLesson.back()); 
    string hourLesson = DefaultLesson.substr(0, 11);
    dayResult--; 
    tab[(10 * dayResult) + hour] = hourLesson + " " + "---------------";
}
void menu(string tab[]) {
    int choise, dayResult,hour;
    int stop = 0; //zmienna zatrzymująca działanie pętli
    string newLesson;
    

    while (true) {
        
        cout << "Moj plan zajec szkolnych - menu\n";
        cout << "1. Odczytaj plan\n";
        cout << "2. Edytuj plan\n";
        cout << "3. Zapisz plan\n";
        cout << "4. Pomoc\n";
        cout << "5. Usun\n";
        cout << "6. Zakoncz\n";
        cout << "Wybierz opcje (1-5): ";
        cin >> choise;
        if (cin) { //jeżeli wprowadzone dane są prawdziwe to przechodzi dalej
            switch (choise) {
            case 1:
                system("cls"); //wyczyszcza cmd
                day(); //funkcja wypisująca możliwe dni tygodnia do wyboru
                while (stop == 0) {

                    cin >> dayResult;

                    if (!cin || dayResult <= 0 || dayResult > 6) { //warunek sprawdzający czy wprowadzone dane są prawidłowe
                        system("cls");
                        cout << "Blad: Wybrano niepoprawna liczbe\n";
                        exit(0);//kończy działanie programu
                    }
                    else {
                        system("cls");
                        stop++;
                    }
                }
                for (int i = 0; i <= 9; i++) { //pętla wypisująca wiersz po wierszu z tabeli
                    cout << Read(tab, dayResult, i);
                    cout << endl;
                }
                stop = 0;
                break;
            case 2:

                system("cls");
                day();
                while (stop == 0) {

                    cin >> dayResult;
                    if (!cin || dayResult <= 0 || dayResult > 5) {
                        system("cls");
                        cout << "Blad: Wybrano niepoprawna liczbe\n";
                        exit(0);
                    }
                    else {
                        system("cls");
                        stop++;
                    }
                }
                NumericRead(tab, dayResult); //funkcja która wypisuję, ale z numeracją
                cout << "Wybierz liczbe podana przed pozycja: ";
                cin >> hour;
                if (!cin || hour > 9 || hour < 1) {
                    system("cls");
                    cout << "Blad: Wybrano niepoprawna liczbe\n";
                    exit(0);//kończy działanie programu
                }
                cout << Read(tab, dayResult, hour) << endl;
                cout << "Podaj nazwe przedmiotu: ";
                cin >> newLesson;
                Edit(tab, dayResult, hour, newLesson); //funkcja zmieniająca wiersz, który użytkownik chcę zmienić w tabeli
                stop = 0;
                break;
            case 3:
                system("cls");
                Save(tab); //funkcja zapisująca zawartośc tabeli do pliku txt
                break;
            case 4:
                system("cls");
                Help();
                menu(tab);//wywołuję funkcję menu aby użytkownik mógł dalej korzystać z programu
                break;
            case 5:
//wyjaśnienie: linijka 138
                system("cls");
                day();
                while (stop == 0) {

                    cin >> dayResult;
                    if (dayResult <= 0 || dayResult > 5) {
                        system("cls");
                        cout << "Blad: Wybrano niepoprawna liczbe\n";
                        day();
                    }
                    else {
                        system("cls");
                        stop++;
                    }
                }
                NumericRead(tab, dayResult);
                cout << "Wybierz liczbe podana przed pozycja: ";
                cin >> hour;
                cout << Read(tab, dayResult, hour) << endl;
                drop(tab, dayResult, hour);//funkcja zastępująca nazwę przedmiotu na myślniki
                stop = 0;
                break;

            case 6:
                exit(0);
                break;
            default:
                system("cls");
                cout << "Blad: Wybrano niepoprawna liczbe\n";
                menu(tab);

            }
        }
        else {
            system("cls");
            cout << "Blad: Wybrano niepoprawne dane\n";
            break;
        }
       
    }
}
int main()
{
    system("Color 03");//zmiana koloru znaków na niebieski
    string tab[99] = {}; //tablica przechowująca zawartość pliku txt, przechowuję dane tymczasowe
    ReadFile(tab); //wywołuję funkcję dodającą dane z pliku txt do tabliicy
    system("cls");
    menu(tab);


    

}

