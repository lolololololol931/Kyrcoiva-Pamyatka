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
void saveStats(double timePlayer, int attempts, int everyattempt, int scam) {
    ofstream file("stats.txt");
    if (file.is_open()) {
        file << "��� ���: " << timePlayer << " ������\n";
        file << "ʳ������ �������: " << attempts << "\n";
        file << "ʳ������ ����������: " << everyattempt << "\n";
        file << "ʳ������ ���������: " << scam << "\n";
        file << "------------------------\n";
        file.close();
    }
    else {
        cout << r << "������� ������ ����������!" << o << endl;
    }
}
int Gamefxf()
{
	srand(time(NULL));
	system("chcp 1251>null");
	cout << "\033[2J\033[1;1H"; //�������� ������
    cout << r << "��� ���'��� 4x4\n" << o;
    cout << "������� 1 - �����, 2 - ���:\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        main(); 
    }
    else {
        cout << "\033[2J\033[1;1H";
        cout << y<<"��� ����������, �������� ����-��� ������ ��� ������:\n";
        cin.ignore();
        cin.get();
        cout << "�����'������ ����"<<o;
        for (int i = 1; i < 3; i++) {
            cout <<y<< '.';
            cout << '.'<<o;
            Sleep(500);
        }
        cout << mg" ���������!\n"<<o;
        Sleep(1000);
        cout <<g "������!\n"<<o;
        srand(time(0));

        char cards[4][4];
        char sim[] = "++^^&&99==--##%%";

        random_shuffle(sim, sim + sizeof(sim) - 1);
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cards[i][j] = sim[i * 4 + j];
            }
        }
        cout << m<<c<<"  1 2 3 4"<<o<<mn << endl;
        for (int i = 0; i < 4; i++) {
            cout << m << c << char('A'+ i) << o << mn << " ";
            for (int j = 0; j < 4; j++) {
                cout <<g<< cards[i][j]<<o << " ";
            }
            cout << endl;
        }

        Sleep(5000);

        cout << "\033[2J\033[1;1H";
        cout << "���������� ����!\n";

        cout <<m<<c "  1 2 3 4"<<o<<mn << endl;
        for (int i = 0; i < 4; i++) {
            cout <<m<<c<< char('A' + i)<<o<<mn << " ";
            for (int j = 0; j < 4; j++) {
                cout << r << "X " << o;
            }
            cout << endl;
        }
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
        string pos1, pos2;
        vector<string> answers;
        while (true) {
            cout << "������ �� ������� ��� �������� (���������: A1 B2): ";
            cin >> pos1 >> pos2;

            if (pos1.size() == 2 && pos2.size() == 2) {
                row1 = toupper(pos1[0]) - 'A';
                col1 = pos1[1] - '1';
                row2 = toupper(pos2[0]) - 'A';
                col2 = pos2[1] - '1';

                if (row1 < 0 || row1 >= 4 || col1 < 0 || col1 >= 4 ||
                    row2 < 0 || row2 >= 4 || col2 < 0 || col2 >= 4 ||
                    (row1 == row2 && col1 == col2)) {
                    cout << r << "����������� ����! ��������� �� ���." << o << endl;
                    continue;
                }
                everyattempt++;
                rightattempt = everyattempt - attempts;
            }
            else {
                cout << r << "����������� ������! ������ ���������� ��������� (���������: A1 B2)." << o << endl;
                continue;
            }
            cout << m << c "  1 2 3 4" << o << mn << endl;
            for (int i = 0; i < 4; i++) {
                cout << m << c << char('A' + i) << o << mn << " ";
                for (int j = 0; j < 4; j++) {
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
                    cout << r << "�� ��������! ��������� ��� � ��������.\n" << o;
                    cout << y << "� ��� ��: " << 5 - attempts - 1 << " ������" << o << endl;
                    attempts++;
                    scamattempt++;
                    Sleep(2000);
                    cout << "\033[2J\033[1;1H"; //�������� ������
                }
                else {
                    answers.push_back(pair1);
                    answers.push_back(pair2);
                    cout << g << "���� �������!" << o << endl;
                }
            }
            else {
                cout << y << "���� �� �������. � ��� ��: " << 5 - attempts - 1 << " ������" << o << endl;
                attempts++;
                Sleep(2000);
                cout << "\033[2J\033[1;1H"; //�������� ������
            }
            if (rightattempt == 8) {
                auto endPlayer = chrono::steady_clock::now();
                chrono::duration<double> elapsedPlayer = endPlayer - startPlayer;
                double timePlayer = elapsedPlayer.count();
                saveStats(timePlayer, attempts, everyattempt, scamattempt);
                cout <<g<<"�� ���������! ³�����!"<<o;
                Sleep(1000);
                break;                
            }
            if (attempts == 5) {
                auto endPlayer = chrono::steady_clock::now();
                chrono::duration<double> elapsedPlayer = endPlayer - startPlayer;
                double timePlayer = elapsedPlayer.count();
                saveStats(timePlayer, attempts, everyattempt, scamattempt);
                cout <<r<< "�� ����������� �� 5 ����� ��"<<m<< " ��������" << mn << o;
                Sleep(1000);
                break;
            }
            auto endPlayer = chrono::steady_clock::now();
            chrono::duration<double> elapsedPlayer = endPlayer - startPlayer;
            double timePlayer = elapsedPlayer.count();
            saveStats(timePlayer, attempts, everyattempt, scamattempt);
        }
    }

	return 0;
}