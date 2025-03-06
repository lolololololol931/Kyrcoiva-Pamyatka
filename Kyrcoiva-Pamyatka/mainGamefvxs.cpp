#include <iostream>
#include <CoreWindow.h>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include "main.h"
#include <vector>
#define r "\033[31m"
#define b "\033[34m"
#define g "\033[32m"
#define y "\033[33m"
#define o "\033[0m"
#define m "\033[5m"
#define mn "\033[25m"
#define c "\033[36m"
#define mg "\033[35m"
using namespace std;
void saveStats1(double timePlayer, int attempts, int everyattempt, int scam) {
    ofstream file("stats5x6.txt");
    if (file.is_open()) {
        file << "Час гри: " << timePlayer << " секунд\n";
        file << "Кількість помилок: " << attempts << "\n";
        file << "Кількість переворотів: " << everyattempt << "\n";
        file << "Кількість хитрувань: " << scam << "\n";
        file << "------------------------\n";
        file.close();
    }
    else {
        cout << r << "Помилка запису статистики!" << o << endl;
    }
}
int Gamefvxs()
{
    srand(time(NULL));
    system("chcp 1251>null");
    cout << "\033[2J\033[1;1H"; //очищення екрану
    cout << r << "ГРА ПАМ'ЯТЬ 5x6\n" << o;
    cout << "Виберіть 1 - вийти, 2 - гра:\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        main();
    }
    else {
        cout << "\033[2J\033[1;1H";
        cout << y << "Гра починається, натисніть будь-яку клавішу для старту:\n";
        cin.ignore();
        cin.get();
        cout << "Запам'ятайте пари" << o;
        for (int i = 1; i < 3; i++) {
            cout << y << '.';
            cout << '.' << o;
            Sleep(500);
        }
        cout << mg" Готуйтесь!\n" << o;
        Sleep(1000);
        cout << g "ПОЧАЛИ!\n" << o;
        srand(time(0));

        char cards[5][6];
        char sim[] = "AABBCCDDEEFFGGHHIIJJKKLLVVNNZZ";

        random_shuffle(sim, sim + sizeof(sim) - 1);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 6; j++) {
                cards[i][j] = sim[i * 6 + j];
            }
        }
        cout << m << c << "  1 2 3 4 5 6" << o << mn << endl;
        for (int i = 0; i < 5; i++) {
            cout << m << c << char('A' + i) << o << mn << " ";
            for (int j = 0; j < 6; j++) {
                cout << g << cards[i][j] << o << " ";
            }
            cout << endl;
        }

        Sleep(8000);

        cout << "\033[2J\033[1;1H";
        cout << "Розгадайте пари!\n";

        auto startPlayer = chrono::steady_clock::now();
        auto endPlayer = chrono::steady_clock::now();
        chrono::duration<double> elapsedPlayer = endPlayer - startPlayer;
        double timePlayer = elapsedPlayer.count();
        int attempts = 0;
        int everyattempt = 0;
        int rightattempt = 0;
        int scamattempt = 0;
        int scamalert = 0;
        int row1, col1, row2, col2;
        int choice;
        string pos1, pos2;
        vector<string> answers;
        while (true) {
            cout << m << c "  1 2 3 4 5 6" << o << mn << endl;
            for (int i = 0; i < 5; i++) {
                cout << m << c << char('A' + i) << o << mn << " ";
                for (int j = 0; j < 6; j++) {
                    cout << r << "X " << o;
                }
                cout << endl;
            }
            cout << "Введіть дві позиції для відкриття (наприклад: A1 B2): ";
            cin >> pos1 >> pos2;

            if (pos1.size() == 2 && pos2.size() == 2) {
                row1 = toupper(pos1[0]) - 'A';
                col1 = pos1[1] - '1';
                row2 = toupper(pos2[0]) - 'A';
                col2 = pos2[1] - '1';

                if (row1 < 0 || row1 >= 5 || col1 < 0 || col1 >= 6 ||
                    row2 < 0 || row2 >= 5 || col2 < 0 || col2 >= 6 ||
                    (row1 == row2 && col1 == col2)) {
                    cout << r << "Некоректний вибір! Спробуйте ще раз." << o << endl;
                    continue;
                }
                everyattempt++;
                rightattempt = everyattempt - attempts;
            }
            else {
                cout << r << "Некоректний формат! Введіть координати правильно (наприклад: A1 B2)." << o << endl;
                continue;
            }
            cout << m << c "  1 2 3 4 5 6" << o << mn << endl;
            for (int i = 0; i < 5; i++) {
                cout << m << c << char('A' + i) << o << mn << " ";
                for (int j = 0; j < 6; j++) {
                    if ((i == row1 && j == col1) || (i == row2 && j == col2)) {
                        cout << g << cards[i][j] << " " << o;
                    }
                    else {
                        cout << r << "X " << o;
                    }
                }
                cout << endl;
            }
            if (cards[row1][col1] == cards[row2][col2]) {
                string pair1 = string(1, cards[row1][col1]) + to_string(row1) + to_string(col1);
                string pair2 = string(1, cards[row2][col2]) + to_string(row2) + to_string(col2);

                if (find(answers.begin(), answers.end(), pair1) != answers.end() || find(answers.begin(), answers.end(), pair2) != answers.end()) {
                    cout << r << "Не хитруйте! Помилочку вам в копілочку.\n" << o;
                    cout << y << "У вас ще: " << 7 - attempts - 1 << " спроби" << o << endl;
                    attempts++;
                    scamattempt++;
                    Sleep(2000);
                    cout << "\033[2J\033[1;1H"; //очищення екрану
                }
                else {
                    answers.push_back(pair1);
                    answers.push_back(pair2);
                    cout << g << "Пари співпали!" << o << endl;
                }
            }
            else {
                cout << y << "Пари не співпали. У вас ще: " << 7 - attempts - 1 << " спроби" << o << endl;
                attempts++;
                Sleep(2000);
                cout << "\033[2J\033[1;1H"; //очищення екрану
            }
            if (rightattempt == 15) {
                auto endPlayer = chrono::steady_clock::now();
                chrono::duration<double> elapsedPlayer = endPlayer - startPlayer;
                double timePlayer = elapsedPlayer.count();
                saveStats1(timePlayer, attempts, everyattempt, scamattempt);
                cout << "\033[2J\033[1;1H"; //очищення екрану
                cout << g << "Ви перемогли! Вітання!" << o;
                cout << g << "Ваша статистика збережена у файлі. Перегляньте результати та спробуйте ще раз!" << o;
                Sleep(1000);
                int choice;
                cout << g << "\nХочете продовжити гру? 1 - так, 2 - ні:  " << o;
                cin >> choice;
                if (choice == 1) {
                    cout << "\033[2J\033[1;1H"; // очищення екрану
                    Gamefvxs();
                }
                else if (choice == 2) {
                    cout << g "Дякуємо а гру" << o;
                    Sleep(1000);
                    break;
                }
                else {
                    cout << r << "Введіть коректне значення" << o;
                    Sleep(1000);
                    break;
                }
            }
            if (attempts == 7) {
                auto endPlayer = chrono::steady_clock::now();
                chrono::duration<double> elapsedPlayer = endPlayer - startPlayer;
                double timePlayer = elapsedPlayer.count();
                saveStats1(timePlayer, attempts, everyattempt, scamattempt);
                cout << "\033[2J\033[1;1H"; //очищення екрану
                cout << r << "Ви використали всі 7 спроб та" << m << " ПРОГРАЛИ" << mn << o;
                cout << r << "\nВаша статистика збережена у файлі.Перегляньте результати та спробуйте ще раз!" << o;
                Sleep(1000);
                int choice;
                cout << r << "\nХочете продовжити гру? 1 - продовження старої, 2 - нова, 3 - ні:  " << o;
                cin >> choice;
                if (choice == 1) {
                    cout << "\033[2J\033[1;1H"; // очищення екрану
                    attempts = 0;
                    continue;
                }
                else if (choice == 2) {
                    cout << "\033[2J\033[1;1H"; // очищення екрану
                    Gamefvxs();
                }
                else if (choice == 3) {
                    cout << g "Дякуємо а гру" << o;
                    Sleep(1000);
                    break;
                }
                else {
                    cout << r << "Введіть коректне значення" << o;
                    Sleep(1000);
                    break;
                }
            }                
            auto endPlayer = chrono::steady_clock::now();
            chrono::duration<double> elapsedPlayer = endPlayer - startPlayer;
            double timePlayer = elapsedPlayer.count();
            saveStats1(timePlayer, attempts, everyattempt, scamattempt);
            }
            
        }
        return 0;
    }

    


