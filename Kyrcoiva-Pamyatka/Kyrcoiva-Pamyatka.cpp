#include <iostream>
#include <CoreWindow.h>
#include "mainGamefхf.h"
#include "mainGamefvxs.h"
using namespace std;


int main()
{
    system("chcp 1251>null");
    cout << "main\n";
    short choice;
    cin >> choice;
    switch (choice) {
    case 1:
        Gamefxf(); break;
    case 2:
        Gamefvxs(); break;
    }


    return 0;
}
