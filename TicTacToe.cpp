#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

void menu();
void opcje(char wybor);
void instrukcje();
void definiowana();
void kik(); /*kik - kolko i krzyzyk*/
void sekcja(char plansza[15][15], string gracz1[2], string gracz2[2], int tura); /*wypelnianie planszy*/
void decode(char ruch[3], char plansza[15][15], char miniplansza[6][6], int pole[2]); /*funkcja przekladajaca ruch na miejsce na planszy razem z kontrola danych*/
int warunek(int wygrana, char miniplansza[6][6], int pole[2]); /*ponizsze 3 funkcje sprawdzaja ilosc zetonow w odpowienio pionie, poziomie i diagonalnie*/
int pion(char miniplansza[6][6], int wygrana, int pole[2]);
int poziom(char miniplansza[6][6], int wygrana, int pole[2]);
int diagonal(char miniplansza[6][6], int wygrana, int pole[2]);

int main()
{
    menu();
}

void menu()
{
    char wybor = ' ';
    cout << "Wybierz jedna z ponizszych opcji" << endl << endl;
    cout << "k - zagraj w kolko i krzyzyk" << endl;
    cout << "o - wygeneruj plansze predefiniowana" << endl;
    cout << "h - wejdz w opis programu" << endl;
    cin >> wybor;
    opcje(wybor);
}

void opcje(char wybor)
{
    system("CLS");
    switch (wybor)
    {
    case 'k':
        kik();
        break;
    case 'o':
        definiowana();
        break;
    case 'h':
        instrukcje();
        break;
    }
}

void instrukcje()
{
    int wybor = 1;
    cout << "Kolko i krzyzyk" << endl;
    cout << "Warunek wygranej: ustawienie 5 zetonow w jednym rzedzie, kolumnie, badz diagonalnie" << endl;
    cout << "Ruch gracza: gracz wybiera wolne pole i ustawia tam swoj zeton" << endl;
    cout << "Opis ruchu:" << endl;
    cout << "q - lewa gorna cwiartka" << endl;
    cout << "w - prawa gorna cwiartka" << endl;
    cout << "a - lewa dolna cwiartka" << endl;
    cout << "s - prawa dolna cwiartka" << endl;
    cout << "1-9 - odpowiednie pola kazdej cwiartki (zaczynajac numeracje w lewym gornym rogu od 1)" << endl;
    cout << endl;
    while (wybor != 0)
    {
        cout << "Aby powrocic do menu startowego wybierz 0" << endl;
        cin >> wybor;
        if (wybor == 0)
        {
            system("CLS");
            menu();
        }
    }
}

void kik()
{
    string gracz1[2], gracz2[2];
    int tura = 0, wygrana = 0, pole[2];
    char ruch[3]{}, plansza[15][15]{}, miniplansza[6][6]{};
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if ((i == 1 || i == 3 || i == 5) && (j == 1 || j == 3 || j == 5)) plansza[i][j] = ' ';
            else if ((i == 1 || i == 3 || i == 5) && (j == 9 || j == 11 || j == 13)) plansza[i][j] = ' ';
            else if ((i == 9 || i == 11 || i == 13) && (j == 1 || j == 3 || j == 5)) plansza[i][j] = ' ';
            else if ((i == 9 || i == 11 || i == 13) && (j == 9 || j == 11 || j == 13)) plansza[i][j] = ' ';
        }
    }
    cout << "Podaj nazwe gracza 1: ";
    cin >> gracz1[0];
    cout << endl;
    cout << "Gracz 1 rozpocznie gre, jego zetony to 'x' " << endl << endl;
    gracz1[1] = "x";
    cout << "Podaj nazwe gracza 2: ";
    cin >> gracz2[0];
    cout << endl;
    cout << "Gracz 2 - jego zetony to 'o' " << endl << endl;
    gracz2[1] = "o";
    cout << "Gra wkrotce sie rozpocznie" << endl;
    chrono::seconds timespan(4);
    this_thread::sleep_for(timespan);
    system("CLS");
    while (wygrana == 0)
    {
        sekcja(plansza, gracz1, gracz2, tura);
        if (tura == 0)
        {
            cin >> ruch[0] >> ruch[1];

            ruch[2] = 'x';
            decode(ruch, plansza, miniplansza, pole);
            tura = 1;
        }
        else if (tura == 1)
        {
            cin >> ruch[0] >> ruch[1];
            ruch[2] = 'o';
            decode(ruch, plansza, miniplansza, pole);
            tura = 0;
        }
        wygrana = warunek(wygrana, miniplansza, pole);
    }
    system("CLS");
    if (wygrana == 1)
    {
        cout << "Gratuluje, gracz " << gracz1[0] << " wygral ta rozgrywe" << endl;
        cout << "Za chwile zostaniesz przeniesiony do menu" << endl;
        chrono::seconds timespan(4);
        this_thread::sleep_for(timespan);
        system("CLS");
        menu();
    }
    else if (wygrana == 2)
    {
        cout << "Gratuluje, gracz " << gracz2[0] << " wygral ta rozgrywe" << endl;
        cout << "Za chwile zostaniesz przeniesiony do menu" << endl;
        chrono::seconds timespan(4);
        this_thread::sleep_for(timespan);
        system("CLS");
        menu();
    }
}

void sekcja(char plansza[15][15], string gracz1[2], string gracz2[2], int tura)
{
    system("CLS");
    for (int i = 0; i < 15; i++)
    {
        for (int i = 0; i < 15; i++)
        {
            plansza[i][7] = '    ';
        }
    }
    for (int k = 0; k < 4; k++)
    {
        if (k == 0)
        {
            for (int i = 0; i < 7; i++)
            {
                for (int j = 0; j < 7; j++)
                {
                    if ((i == 1 || i == 3 || i == 5) && (j == 0 || j == 2 || j == 4 || j == 6)) plansza[i][j] = char(186);
                    else if ((i == 0 || i == 2 || i == 4 || i == 6) && (j == 1 || j == 3 || j == 5)) plansza[i][j] = char(205);
                    else if ((i == 2 || i == 4) && (j == 2 || j == 4)) plansza[i][j] = char(206);
                    else if (i == 0 && (j == 2 || j == 4)) plansza[i][j] = char(203);
                    else if (i == 6 && (j == 2 || j == 4)) plansza[i][j] = char(202);
                    else if ((i == 2 || i == 4) && j == 0) plansza[i][j] = char(204);
                    else if ((i == 2 || i == 4) && j == 6) plansza[i][j] = char(185);
                    else if (i == 0 && j == 0) plansza[i][j] = char(201);
                    else if (i == 0 && j == 6) plansza[i][j] = char(187);
                    else if (i == 6 && j == 0) plansza[i][j] = char(200);
                    else if (i == 6 && j == 6) plansza[i][j] = char(188);
                }
            }
        }
        else if (k == 1)
        {
            for (int i = 0; i < 7; i++)
            {
                for (int j = 8; j < 15; j++)
                {
                    if ((i == 1 || i == 3 || i == 5) && (j == 8 || j == 10 || j == 12 || j == 14)) plansza[i][j] = char(186);
                    else if ((i == 0 || i == 2 || i == 4 || i == 6) && (j == 9 || j == 11 || j == 13)) plansza[i][j] = char(205);
                    else if ((i == 2 || i == 4) && (j == 10 || j == 12)) plansza[i][j] = char(206);
                    else if (i == 0 && (j == 10 || j == 12)) plansza[i][j] = char(203);
                    else if (i == 6 && (j == 10 || j == 12)) plansza[i][j] = char(202);
                    else if ((i == 2 || i == 4) && j == 8) plansza[i][j] = char(204);
                    else if ((i == 2 || i == 4) && j == 14) plansza[i][j] = char(185);
                    else if (i == 0 && j == 8) plansza[i][j] = char(201);
                    else if (i == 0 && j == 14) plansza[i][j] = char(187);
                    else if (i == 6 && j == 8) plansza[i][j] = char(200);
                    else if (i == 6 && j == 14) plansza[i][j] = char(188);
                }
            }
        }
        else if (k == 2)
        {
            for (int i = 8; i < 15; i++)
            {
                for (int j = 0; j < 7; j++)
                {
                    if ((i == 9 || i == 11 || i == 13) && (j == 0 || j == 2 || j == 4 || j == 6)) plansza[i][j] = char(186);
                    else if ((i == 8 || i == 10 || i == 12 || i == 14) && (j == 1 || j == 3 || j == 5)) plansza[i][j] = char(205);
                    else if ((i == 10 || i == 12) && (j == 2 || j == 4)) plansza[i][j] = char(206);
                    else if (i == 8 && (j == 2 || j == 4)) plansza[i][j] = char(203);
                    else if (i == 14 && (j == 2 || j == 4)) plansza[i][j] = char(202);
                    else if ((i == 10 || i == 12) && j == 0) plansza[i][j] = char(204);
                    else if ((i == 10 || i == 12) && j == 6) plansza[i][j] = char(185);
                    else if (i == 8 && j == 0) plansza[i][j] = char(201);
                    else if (i == 8 && j == 6) plansza[i][j] = char(187);
                    else if (i == 14 && j == 0) plansza[i][j] = char(200);
                    else if (i == 14 && j == 6) plansza[i][j] = char(188);
                }
            }
        }

        else if (k == 3)
        {
            for (int i = 8; i < 15; i++)
            {
                for (int j = 8; j < 15; j++)
                {
                    if ((i == 9 || i == 11 || i == 13) && (j == 8 || j == 10 || j == 12 || j == 14)) plansza[i][j] = char(186);
                    else if ((i == 8 || i == 10 || i == 12 || i == 14) && (j == 9 || j == 11 || j == 13)) plansza[i][j] = char(205);
                    else if ((i == 10 || i == 12) && (j == 10 || j == 12)) plansza[i][j] = char(206);
                    else if (i == 8 && (j == 10 || j == 12)) plansza[i][j] = char(203);
                    else if (i == 14 && (j == 10 || j == 12)) plansza[i][j] = char(202);
                    else if ((i == 10 || i == 12) && j == 8) plansza[i][j] = char(204);
                    else if ((i == 10 || i == 12) && j == 14) plansza[i][j] = char(185);
                    else if (i == 8 && j == 8) plansza[i][j] = char(201);
                    else if (i == 8 && j == 14) plansza[i][j] = char(187);
                    else if (i == 14 && j == 8) plansza[i][j] = char(200);
                    else if (i == 14 && j == 14) plansza[i][j] = char(188);
                }
            }
        }
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            cout << plansza[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout << gracz1[0] << " - " << gracz1[1] << endl;
    cout << gracz2[0] << " - " << gracz2[1] << endl << endl;
    if (tura == 0)
    {
        cout << "Teraz tura gracza " << gracz1[0] << endl;
    }
    else if (tura == 1)
    {
        cout << "Teraz tura gracza " << gracz2[0] << endl;
    }
    cout << "Dokonaj ruchu, wpisz 'm' i dowolny znak aby powrocic do menu glownego, wpisz 'u' i dowolny znak aby cofnac ruch: ";
}

void decode(char ruch[3], char plansza[15][15], char miniplansza[6][6], int pole[2])
{
    int poprawny_ruch = 0;
    while (poprawny_ruch == 0)
    {
        if (ruch[0] == 'm')
        {
            system("CLS");
            menu();
        }
        else if (ruch[0] == 'q')
        {
            if (ruch[1] == '1')
            {
                if (plansza[1][1] == ' ')
                {
                    plansza[1][1] = ruch[2];
                    miniplansza[0][0] = ruch[2];
                    pole[0] = 0;
                    pole[1] = 0;
                }
                else;
            }
            if (ruch[1] == '2')
            {
                if (plansza[1][3] == ' ')
                {
                    plansza[1][3] = ruch[2];
                    miniplansza[0][1] = ruch[2];
                    pole[0] = 0;
                    pole[1] = 1;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '3')
            {
                if (plansza[1][5] == ' ')
                {
                    plansza[1][5] = ruch[2];
                    miniplansza[0][2] = ruch[2];
                    pole[0] = 0;
                    pole[1] = 2;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '4')
            {
                if (plansza[3][1] == ' ')
                {
                    plansza[3][1] = ruch[2];
                    miniplansza[1][0] = ruch[2];
                    pole[0] = 1;
                    pole[1] = 0;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '5')
            {
                if (plansza[3][3] == ' ')
                {
                    plansza[3][3] = ruch[2];
                    miniplansza[1][1] = ruch[2];
                    pole[0] = 1;
                    pole[1] = 1;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '6')
            {
                if (plansza[3][5] == ' ')
                {
                    plansza[3][5] = ruch[2];
                    miniplansza[1][2] = ruch[2];
                    pole[0] = 1;
                    pole[1] = 2;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '7')
            {
                if (plansza[5][1] == ' ')
                {
                    plansza[5][1] = ruch[2];
                    miniplansza[2][0] = ruch[2];
                    pole[0] = 2;
                    pole[1] = 0;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '8')
            {
                if (plansza[5][3] == ' ')
                {
                    plansza[5][3] = ruch[2];
                    miniplansza[2][1] = ruch[2];
                    pole[0] = 2;
                    pole[1] = 1;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '9')
            {
                if (plansza[5][5] == ' ')
                {
                    plansza[5][5] = ruch[2];
                    miniplansza[2][2] = ruch[2];
                    pole[0] = 2;
                    pole[1] = 2;
                    poprawny_ruch = 1;
                }
                else;
            }
        }
        else if (ruch[0] == 'w')
        {
            if (ruch[1] == '1')
            {
                if (plansza[1][9] == ' ')
                {
                    plansza[1][9] = ruch[2];
                    miniplansza[0][3] = ruch[2];
                    pole[0] = 0;
                    pole[1] = 3;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '2')
            {
                if (plansza[1][11] == ' ')
                {
                    plansza[1][11] = ruch[2];
                    miniplansza[0][4] = ruch[2];
                    pole[0] = 0;
                    pole[1] = 4;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '3')
            {
                if (plansza[1][13] == ' ')
                {
                    plansza[1][13] = ruch[2];
                    miniplansza[0][5] = ruch[2];
                    pole[0] = 0;
                    pole[1] = 5;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '4')
            {
                if (plansza[3][9] == ' ')
                {
                    plansza[3][9] = ruch[2];
                    miniplansza[1][3] = ruch[2];
                    pole[0] = 1;
                    pole[1] = 3;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '5')
            {
                if (plansza[3][11] == ' ')
                {
                    plansza[3][11] = ruch[2];
                    miniplansza[1][4] = ruch[2];
                    pole[0] = 1;
                    pole[1] = 4;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '6')
            {
                if (plansza[3][13] == ' ')
                {
                    plansza[3][13] = ruch[2];
                    miniplansza[1][5] = ruch[2];
                    pole[0] = 1;
                    pole[1] = 5;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '7')
            {
                if (plansza[5][9] == ' ')
                {
                    plansza[5][9] = ruch[2];
                    miniplansza[2][3] = ruch[2];
                    pole[0] = 2;
                    pole[1] = 3;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '8')
            {
                if (plansza[5][11] == ' ')
                {
                    plansza[5][11] = ruch[2];
                    miniplansza[2][4] = ruch[2];
                    pole[0] = 2;
                    pole[1] = 4;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '9')
            {
                if (plansza[5][13] == ' ')
                {
                    plansza[5][13] = ruch[2];
                    miniplansza[2][5] = ruch[2];
                    pole[0] = 2;
                    pole[1] = 5;
                    poprawny_ruch = 1;
                }
                else;
            }
        }
        else if (ruch[0] == 'a')
        {
            if (ruch[1] == '1')
            {
                if (plansza[9][1] == ' ')
                {
                    plansza[9][1] = ruch[2];
                    miniplansza[3][0] = ruch[2];
                    pole[0] = 3;
                    pole[1] = 0;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '2')
            {
                if (plansza[9][3] == ' ')
                {
                    plansza[9][3] = ruch[2];
                    miniplansza[3][1] = ruch[2];
                    pole[0] = 3;
                    pole[1] = 1;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '3')
            {
                if (plansza[9][5] == ' ')
                {
                    plansza[9][5] = ruch[2];
                    miniplansza[3][2] = ruch[2];
                    pole[0] = 3;
                    pole[1] = 2;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '4')
            {
                if (plansza[11][1] == ' ')
                {
                    plansza[11][1] = ruch[2];
                    miniplansza[4][0] = ruch[2];
                    pole[0] = 4;
                    pole[1] = 0;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '5')
            {
                if (plansza[11][3] == ' ')
                {
                    plansza[11][3] = ruch[2];
                    miniplansza[4][1] = ruch[2];
                    pole[0] = 4;
                    pole[1] = 1;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '6')
            {
                if (plansza[11][5] == ' ')
                {
                    plansza[11][5] = ruch[2];
                    miniplansza[4][2] = ruch[2];
                    pole[0] = 4;
                    pole[1] = 2;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '7')
            {
                if (plansza[13][1] == ' ')
                {
                    plansza[13][1] = ruch[2];
                    miniplansza[5][0] = ruch[2];
                    pole[0] = 5;
                    pole[1] = 0;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '8')
            {
                if (plansza[13][3] == ' ')
                {
                    plansza[13][3] = ruch[2];
                    miniplansza[5][1] = ruch[2];
                    pole[0] = 5;
                    pole[1] = 1;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '9')
            {
                if (plansza[13][5] == ' ')
                {
                    plansza[13][5] = ruch[2];
                    miniplansza[5][2] = ruch[2];
                    pole[0] = 5;
                    pole[1] = 2;
                    poprawny_ruch = 1;
                }
                else;
            }
        }
        else if (ruch[0] == 's')
        {
            if (ruch[1] == '1')
            {
                if (plansza[9][9] == ' ')
                {
                    plansza[9][9] = ruch[2];
                    miniplansza[3][3] = ruch[2];
                    pole[0] = 3;
                    pole[1] = 3;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '2')
            {
                if (plansza[9][11] == ' ')
                {
                    plansza[9][11] = ruch[2];
                    miniplansza[3][4] = ruch[2];
                    pole[0] = 3;
                    pole[1] = 4;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '3')
            {
                if (plansza[9][13] == ' ')
                {
                    plansza[9][13] = ruch[2];
                    miniplansza[3][5] = ruch[2];
                    pole[0] = 3;
                    pole[1] = 5;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '4')
            {
                if (plansza[11][9] == ' ')
                {
                    plansza[11][9] = ruch[2];
                    miniplansza[4][3] = ruch[2];
                    pole[0] = 4;
                    pole[1] = 3;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '5')
            {
                if (plansza[11][11] == ' ')
                {
                    plansza[11][11] = ruch[2];
                    miniplansza[4][4] = ruch[2];
                    pole[0] = 4;
                    pole[1] = 4;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '6')
            {
                if (plansza[11][13] == ' ')
                {
                    plansza[11][13] = ruch[2];
                    miniplansza[4][5] = ruch[2];
                    pole[0] = 4;
                    pole[1] = 5;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '7')
            {
                if (plansza[13][9] == ' ')
                {
                    plansza[13][9] = ruch[2];
                    miniplansza[5][3] = ruch[2];
                    pole[0] = 5;
                    pole[1] = 3;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '8')
            {
                if (plansza[13][11] == ' ')
                {
                    plansza[13][11] = ruch[2];
                    miniplansza[5][4] = ruch[2];
                    pole[0] = 5;
                    pole[1] = 4;
                    poprawny_ruch = 1;
                }
                else;
            }
            if (ruch[1] == '9')
            {
                if (plansza[13][13] == ' ')
                {
                    plansza[13][13] = ruch[2];
                    miniplansza[5][5] = ruch[2];
                    pole[0] = 5;
                    pole[1] = 5;
                    poprawny_ruch = 1;
                }
                else;
            }
        }
        if (poprawny_ruch == 0)
        {
            cout << "Wybrany ruch jest niewykonalny, sprobuj ponownie: ";
            cin >> ruch[0] >> ruch[1];
            cout << endl;
        }
    }
}

int warunek(int wygrana, char miniplansza[6][6], int pole[2])
{
    wygrana = pion(miniplansza, wygrana, pole);
    if (wygrana != 0) return wygrana;
    wygrana = poziom(miniplansza, wygrana, pole);
    if (wygrana != 0) return wygrana;
    wygrana = diagonal(miniplansza, wygrana, pole);
    if (wygrana != 0) return wygrana;
    return wygrana;
}

int pion(char miniplansza[6][6], int wygrana, int pole[2])
{
    int licznik = 1, prze = pole[0], suw = pole[0];
    if (miniplansza[pole[0]][pole[1]] == 'x')
    {
        for (int k = 0; k < 5; k++)
        {
            if (pole[0] != 0)
            {
                if (miniplansza[pole[0] - 1][pole[1]] == 'x') licznik++;
                else if (miniplansza[pole[0] - 1][pole[1]] != 'x') break;
                pole[0]--;
            }
            else if (pole[0] == 0)
            {
                if (miniplansza[prze + 1][pole[1]] == 'x') licznik++;
                else if (miniplansza[prze + 1][pole[1]] != 'x') break;
                prze++;

            }
            if (licznik == 5)
            {
                wygrana = 1;
                return wygrana;
            }
        }
        pole[0] = suw;
        for (int k = 0; k < 5; k++)
        {
            if (pole[0] == 6) break;
            else if (pole[0] != 0)
            {
                if (miniplansza[pole[0] + 1][pole[1]] == 'x') licznik++;
                else if (miniplansza[pole[0] + 1][pole[1]] != 'x') break;
                pole[0]++;
            }
            if (licznik == 5)
            {
                wygrana = 1;
                return wygrana;
            }
        }
    }
    else if (miniplansza[pole[0]][pole[1]] == 'o')
    {
        for (int k = 0; k < 5; k++)
        {
            if (pole[0] != 0)
            {
                if (miniplansza[pole[0] - 1][pole[1]] == 'o') licznik++;
                else if (miniplansza[pole[0] - 1][pole[1]] != 'o') break;
                pole[0]--;
            }
            else if (pole[0] == 0)
            {
                if (miniplansza[prze + 1][pole[1]] == 'o') licznik++;
                else if (miniplansza[prze + 1][pole[1]] != 'o') break;
                prze++;

            }
            if (licznik == 5)
            {
                wygrana = 2;
                return wygrana;
            }
        }
        pole[0] = suw;
        for (int k = 0; k < 5; k++)
        {
            if (pole[0] == 6) break;
            else if (pole[0] != 0)
            {
                if (miniplansza[pole[0] + 1][pole[1]] == 'o') licznik++;
                else if (miniplansza[pole[0] + 1][pole[1]] != 'o') break;
                pole[0]++;
            }
            if (licznik == 5)
            {
                wygrana = 2;
                return wygrana;
            }
        }
    }
    return wygrana;
}

int poziom(char miniplansza[6][6], int wygrana, int pole[2])
{
    int licznik = 1, prze = pole[1], suw = pole[1];
    if (miniplansza[pole[0]][pole[1]] == 'x')
    {
        for (int k = 0; k < 5; k++)
        {
            if (pole[1] != 0)
            {
                if (miniplansza[pole[0]][pole[1] - 1] == 'x') licznik++;
                else if (miniplansza[pole[0]][pole[1] - 1] != 'x') break;
                pole[1]--;
            }
            else if (pole[1] == 0)
            {
                if (miniplansza[pole[0]][prze + 1] == 'x') licznik++;
                else if (miniplansza[pole[0]][prze + 1] != 'x') break;
                prze++;

            }
            if (licznik == 5)
            {
                wygrana = 1;
                return wygrana;
            }
        }
        pole[1] = suw;
        for (int k = 0; k < 5; k++)
        {
            if (pole[1] == 6) break;
            else if (pole[1] != 0)
            {
                if (miniplansza[pole[0]][pole[1] + 1] == 'x') licznik++;
                else if (miniplansza[pole[0]][pole[1] + 1] != 'x') break;
                pole[1]++;
            }
            if (licznik == 5)
            {
                wygrana = 1;
                return wygrana;
            }
        }
    }
    else if (miniplansza[pole[0]][pole[1]] == 'o')
    {
        for (int k = 0; k < 5; k++)
        {
            if (pole[1] != 0)
            {
                if (miniplansza[pole[0]][pole[1] - 1] == 'o') licznik++;
                else if (miniplansza[pole[0]][pole[1] - 1] != 'o') break;
                pole[1]--;
            }
            else if (pole[1] == 0)
            {
                if (miniplansza[pole[0]][prze + 1] == 'o') licznik++;
                else if (miniplansza[pole[0]][prze + 1] != 'o') break;
                prze++;

            }
            if (licznik == 5)
            {
                wygrana = 2;
                return wygrana;
            }
        }
        pole[1] = suw;
        for (int k = 0; k < 5; k++)
        {
            if (pole[1] == 6) break;
            else if (pole[1] != 0)
            {
                if (miniplansza[pole[0]][pole[1] + 1] == 'o') licznik++;
                else if (miniplansza[pole[0]][pole[1] + 1] != 'o') break;
                pole[1]++;
            }
            if (licznik == 5)
            {
                wygrana = 2;
                return wygrana;
            }
        }
    }
    return wygrana;
}

int diagonal(char miniplansza[6][6], int wygrana, int pole[2])
{
    int licznik = 1, przei = pole[0], przej = pole[1], suwi = pole[0], suwj = pole[1];
    if (miniplansza[pole[0]][pole[1]] == 'x')
    {
        for (int k = 0; k < 5; k++)
        {
            if (pole[0] != 0 && pole[1] != 0)
            {
                if (miniplansza[pole[0] - 1][pole[1] - 1] == 'x') licznik++;
                else if (miniplansza[pole[0] - 1][pole[1] - 1] != 'x') break;
                pole[0]--;
                pole[1]--;
            }
            else if (pole[0] == 0 || pole[1] == 0)
            {
                if (miniplansza[przei + 1][przej + 1] == 'x') licznik++;
                else if (miniplansza[przei + 1][przej + 1] != 'x') break;
                przei++;
                przej++;
            }
            if (licznik == 5)
            {
                wygrana = 1;
                return wygrana;
            }
        }
        for (int k = 0; k < 5; k++)
        {
            if (suwi == 6 || suwj == 6) break;
            else if (miniplansza[suwi + 1][suwj + 1] == 'x') licznik++;
            suwi++;
            suwj++;
            if (licznik == 5)
            {
                wygrana = 1;
                return wygrana;
            }
        }
    }
    else if (miniplansza[pole[0]][pole[1]] == 'o')
    {
        for (int k = 0; k < 5; k++)
        {
            if (pole[0] != 0 && pole[1] != 0)
            {
                if (miniplansza[pole[0] - 1][pole[1] - 1] == 'o') licznik++;
                else if (miniplansza[pole[0] - 1][pole[1] - 1] != 'o') break;
                pole[0]--;
                pole[1]--;
            }
            else if (pole[0] == 0 || pole[1] == 0)
            {
                if (miniplansza[przei + 1][przej + 1] == 'o') licznik++;
                else if (miniplansza[przei + 1][przej + 1] != 'o') break;
                przei++;
                przej++;
            }
            if (licznik == 5)
            {
                wygrana = 2;
                return wygrana;
            }
        }
        for (int k = 0; k < 5; k++)
        {
            if (suwi == 6 || suwj == 6) break;
            else if (miniplansza[suwi + 1][suwj + 1] == 'o') licznik++;
            suwi++;
            suwj++;
            if (licznik == 5)
            {
                wygrana = 2;
                return wygrana;
            }
        }
    }
    return wygrana;
}

void definiowana()
{
    string gracz1[2], gracz2[2];
    int tura = 0, wygrana = 0, pole[2];
    char ruch[3]{}, plansza[15][15]{}, miniplansza[6][6]{};
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if ((i == 1 || i == 13) && j == 3) plansza[i][j] = 'x';
            else if (i == 3 && (j == 5 || j == 11)) plansza[i][j] = 'x';
            else if (i == 11 && j == 1) plansza[i][j] = 'x';
            else if ((i == 11 || i == 13) && j == 11) plansza[i][j] = 'x';
            else if (i == 13 && j == 13) plansza[i][j] = 'x';
            else if ((i == 3 || i == 9) && j == 1) plansza[i][j] = 'o';
            else if ((i == 3 || i == 5 || i == 9) && j == 3) plansza[i][j] = 'o';
            else if (i == 11 && j == 5) plansza[i][j] = 'o';
            else if (i == 3 && j == 9) plansza[i][j] = 'o';
            else if (i == 1 && j == 11) plansza[i][j] = 'o';
            else if ((i == 1 || i == 5 || i == 13) && j == 1) plansza[i][j] = ' ';
            else if (i == 11 && j == 3) plansza[i][j] = ' ';
            else if ((i == 1 || i == 5 || i == 9 || i == 13) && j == 5) plansza[i][j] = ' ';
            else if ((i == 1 || i == 5 || i == 9 || i == 11 || i == 13) && j == 9) plansza[i][j] = ' ';
            else if ((i == 5 || i == 9) && j == 11) plansza[i][j] = ' ';
            else if ((i == 1 || i == 3 || i == 5 || i == 9 || i == 11) && j == 13) plansza[i][j] = ' ';
        }
    }
    cout << "Podaj nazwe gracza 1: ";
    cin >> gracz1[0];
    cout << endl;
    cout << "Gracz 1 rozpocznie gre, jego zetony to 'x' " << endl << endl;
    gracz1[1] = "x";
    cout << "Podaj nazwe gracza 2: ";
    cin >> gracz2[0];
    cout << endl;
    cout << "Gracz 2 - jego zetony to 'o' " << endl << endl;
    gracz2[1] = "o";
    cout << "Gra wkrotce sie rozpocznie" << endl;
    chrono::seconds timespan(4);
    this_thread::sleep_for(timespan);
    system("CLS");
    while (wygrana == 0)
    {
        sekcja(plansza, gracz1, gracz2, tura);
        if (tura == 0)
        {
            cin >> ruch[0] >> ruch[1];

            ruch[2] = 'x';
            decode(ruch, plansza, miniplansza, pole);
            tura = 1;
        }
        else if (tura == 1)
        {
            cin >> ruch[0] >> ruch[1];
            ruch[2] = 'o';
            decode(ruch, plansza, miniplansza, pole);
            tura = 0;
        }
        wygrana = warunek(wygrana, miniplansza, pole);
    }
    system("CLS");
    if (wygrana == 1)
    {
        cout << "Gratuluje, gracz " << gracz1[0] << " wygral ta rozgrywe" << endl;
        cout << "Za chwile zostaniesz przeniesiony do menu" << endl;
        chrono::seconds timespan(4);
        this_thread::sleep_for(timespan);
        system("CLS");
        menu();
    }
    else if (wygrana == 2)
    {
        cout << "Gratuluje, gracz " << gracz2[0] << " wygral ta rozgrywe" << endl;
        cout << "Za chwile zostaniesz przeniesiony do menu" << endl;
        chrono::seconds timespan(4);
        this_thread::sleep_for(timespan);
        system("CLS");
        menu();
    }
}