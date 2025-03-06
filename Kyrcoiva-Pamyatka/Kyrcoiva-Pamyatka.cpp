#include <iostream>
#include <CoreWindow.h>
#include "mainGamefхf.h"
#include "mainGamefvxs.h"
#define r "\033[31m"
#define b "\033[34m"
#define y "\033[33m"
#define o "\033[0m"
#define m "\033[5m"
#define mn "\033[25m"

using namespace std;


int main()
{
    system("chcp 1251>null");
    cout << r << "ГРА ПАМ'ЯТЬ\n"<<o;
    Sleep(1000);
    cout << "Виберіть розмір поля "<<m<<b<< "4x4"<<mn<<o<<" - 1 або "<<m<<y<< "5x6"<<mn<<o<<" - 2:\n";
    short choice;
    cin >> choice;
    while (choice != 1 && choice != 2) {  
        cerr << "Виберіть " << r << "1" << o << " або " << r << "2" << o << " для початку гри!\n";
        cin >> choice;
    }
    switch (choice) {
    case 1:
        Gamefxf(); break;
    case 2:
        Gamefvxs(); break;
    }



    return 0;
}
