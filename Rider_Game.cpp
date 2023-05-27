#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<time.h>
#include <fstream>
#include <vector>
#include <algorithm>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;


int enemyY[3];
int enemyX[3];
int enemyFlag[3];
int difficulty = 0;
char car[4][4] = { {' ','±','±',' '},
                   {'±','±','±','±'},
                   {' ','±','±',' '},
                   {'±','±','±','±'} };

int carPos = WIN_WIDTH / 2;
int score;


void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < 17; j++) {
            gotoxy(0 + j, i); cout << "8";
            gotoxy(WIN_WIDTH - j, i); cout << "8";
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(SCREEN_WIDTH, i); cout << "8";
    }
}

void genEnemy(int ind) {
    enemyX[ind] = 17 + rand() % 33;
}

void drawEnemy(int ind) {
    if (enemyFlag[ind] == true) {
        gotoxy(enemyX[ind], enemyY[ind]);     cout << " ** ";
        gotoxy(enemyX[ind], enemyY[ind] + 1); cout << "****";
        gotoxy(enemyX[ind], enemyY[ind] + 2); cout << " ** ";
        gotoxy(enemyX[ind], enemyY[ind] + 3); cout << "****";
    }
}

void eraseEnemy(int ind) {
    if (enemyFlag[ind] == true) {
        gotoxy(enemyX[ind], enemyY[ind]);     cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 1); cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 2); cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 3); cout << "    ";
    }
}

void resetEnemy(int ind) {
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + 22); cout << car[i][j];
        }
    }
}

void eraseCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + 22); cout << " ";
        }
    }
}

int collision() {
    if (enemyY[0] + 4 >= 23) {
        if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9) {
            return 1;
        }
    }
    return 0;
}

void saveScore() {
    
    if (difficulty == 1) {
        ifstream file("results1.txt");
        vector<int> results;
        int value;
        while (file >> value) {
            results.push_back(value);
        }
        file.close();

        // добавить новый результат
        results.push_back(score);

        // отсортировать результаты по убыванию
        sort(results.begin(), results.end(), greater<int>());

        // записать результаты в файл
        ofstream outfile("results1.txt");
        for (int i = 0; i < results.size(); i++) {
            outfile << results[i] << "\n";
        }
        outfile.close();
    }
    else if (difficulty == 3) {
        ifstream file("results3.txt");
        vector<int> results;
        int value;
        while (file >> value) {
            results.push_back(value);
        }
        file.close();

        // добавить новый результат
        results.push_back(score);

        // отсортировать результаты по убыванию
        sort(results.begin(), results.end(), greater<int>());

        // записать результаты в файл
        ofstream outfile("results3.txt");
        for (int i = 0; i < results.size(); i++) {
            outfile << results[i] << "\n";
        }
        outfile.close();
    }
    else {
        ifstream file("results2.txt");
        vector<int> results;
        int value;
        while (file >> value) {
            results.push_back(value);
        }
        file.close();

        // добавить новый результат
        results.push_back(score);

        // отсортировать результаты по убыванию
        sort(results.begin(), results.end(), greater<int>());

        // записать результаты в файл
        ofstream outfile("results2.txt");
        for (int i = 0; i < results.size(); i++) {
            outfile << results[i] << "\n";
        }
        outfile.close();
    }

}

void gameover() {
    system("cls");
    cout << endl;
    gotoxy(10, 11); cout << "--------------------------";
    gotoxy(10, 12); cout << "-------- Game Over -------";
    gotoxy(10, 13); cout << "--------------------------";
    gotoxy(10, 14); cout << "Press any key to go back to the menu";
    _getch();

}

void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5); cout << "Score: " << score << endl;
}

void instructions() {
    system("cls");
    gotoxy(10, 9); cout << "Instructions";
    gotoxy(10, 10); cout << "----------------";
    gotoxy(10, 11); cout << "Avoid Cars by moving left or right. ";
    gotoxy(10, 12); cout << "Press 'a' to move left";
    gotoxy(10, 13); cout << "Press 'd' to move right";
    gotoxy(10, 14); cout << "Press any key to go back to the menu";
    _getch();
}

void selectDifficulty() {
    system("cls");
    gotoxy(10, 9); cout << "Select Difficulty:" << endl;
    gotoxy(10, 10); cout << "1. Student" << endl;
    gotoxy(10, 11); cout << "2. Taxi driver" << endl;
    gotoxy(10, 12); cout << "3. Kazakh" << endl;
    gotoxy(10, 13); cout << "Enter the difficulty level: ";
    cin >> difficulty;
    
}

void Leader() {
    int dif;
    system("cls");
    gotoxy(10, 5); cout << " -------------------------- ";
    gotoxy(10, 6); cout << " |      LEADER BOARD      | ";
    gotoxy(10, 7); cout << " --------------------------";

    gotoxy(10, 9); cout << "Select Difficulty:" << endl;
    gotoxy(10, 10); cout << "1. Student" << endl;
    gotoxy(10, 11); cout << "2. Taxi driver" << endl;
    gotoxy(10, 12); cout << "3. Kazakh" << endl;
    gotoxy(10, 13); cout << "Enter the difficulty level: ";
    cin >> dif;

    if (dif == 1) {
        system("cls");
        gotoxy(10, 5); cout << " -------------------------- ";
        gotoxy(10, 6); cout << " |      LEADER BOARD      | ";
        gotoxy(10, 7); cout << " --------------------------";
        ifstream file;
        file.open("results1.txt");

        int i = 0;
        int scores[10] = { 0 };

        while (!file.eof() && i < 10) {
            file >> scores[i];
            gotoxy(20, 9 + i); cout << i + 1 << ". " << scores[i];
            i++;
        }

        file.close();

        gotoxy(10, 18); cout << "Press any key to go back to the menu";
        _getch();
    }
    else if (dif == 2) {
        system("cls");
        gotoxy(10, 5); cout << " -------------------------- ";
        gotoxy(10, 6); cout << " |      LEADER BOARD      | ";
        gotoxy(10, 7); cout << " --------------------------";
        ifstream file;
        file.open("results2.txt");

        int i = 0;
        int scores[10] = { 0 };

        while (!file.eof() && i < 10) {
            file >> scores[i];
            gotoxy(20, 9 + i); cout << i + 1 << ". " << scores[i];
            i++;
        }

        file.close();

        gotoxy(10, 18); cout << "Press any key to go back to the menu";
        _getch();
    }
    else if (dif == 3) {
        system("cls");
        gotoxy(10, 5); cout << " -------------------------- ";
        gotoxy(10, 6); cout << " |      LEADER BOARD      | ";
        gotoxy(10, 7); cout << " --------------------------";
        ifstream file;
        file.open("results3.txt");

        int i = 0;
        int scores[10] = { 0 };

        while (!file.eof() && i < 10) {
            file >> scores[i];
            gotoxy(20, 9 + i); cout << i + 1 << ". " << scores[i];
            i++;
        }

        file.close();

        gotoxy(10, 18); cout << "Press any key to go back to the menu";
        _getch();
    }

   
}


void play() {

    carPos = -1 + WIN_WIDTH / 2;
    
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH + 7, 2); cout << "CHECKERS";
    gotoxy(WIN_WIDTH + 6, 4); cout << "----------";
    gotoxy(WIN_WIDTH + 6, 6); cout << "----------";
    gotoxy(WIN_WIDTH + 7, 12); cout << "Control ";
    gotoxy(WIN_WIDTH + 7, 13); cout << "-------- ";
    gotoxy(WIN_WIDTH + 2, 14); cout << " A Key - Left";
    gotoxy(WIN_WIDTH + 2, 15); cout << " D Key - Right";

    gotoxy(18, 5); cout << "Press any key to start";
    _getch();
    gotoxy(18, 5); cout << "                      ";

   
    while (1) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'a' || ch == 'A') {
                if (carPos > 18)
                    carPos -= 4;
            }
            if (ch == 'd' || ch == 'D') {
                if (carPos < 50)
                    carPos += 4;
            }
            if (ch == 27) {
                break;
            }
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);
        if (collision() == 1 ) {
            saveScore();
            gameover();
            return;
        }


        switch (difficulty) {
        case 1: // Student
            Sleep(100);
            break;
        case 2: // Taxi driver
            Sleep(50);
            break;
        case 3: // Kazakh
            Sleep(35);
            break;
        default:
            Sleep(50);
            break;
        }
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10)
            if (enemyFlag[1] == 0)
                enemyFlag[1] = 1;

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;

        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 4) {
            resetEnemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4) {
            resetEnemy(1);
            score++;
            updateScore();
        }
        
    }
    
}

int main() {

    
    setcursor(0, 0);
    srand((unsigned)time(NULL));

    do {
        system("cls");
        gotoxy(10, 5); cout << " -------------------------- ";
        gotoxy(10, 6); cout << " |        CHECKERS        | ";
        gotoxy(10, 7); cout << " --------------------------";

        gotoxy(10, 9); cout << "1. Start Game";
        gotoxy(10, 10); cout << "2. Instructions";
        gotoxy(10, 11); cout << "3. Select Difficulty";
        gotoxy(10, 12); cout << "4. Leader Board:";
        gotoxy(10, 13); cout << "5. Quit";
        gotoxy(10, 15); cout << "Select option: ";
        char op = _getche();

        if (op == '1') {
            score = 0;
            play();
        }
        else if (op == '2')
            instructions();
        else if (op == '3')
            selectDifficulty();
        else if (op == '4')
            Leader();
        else if (op == '5')
            exit(0);


    } while (1);

    return 0;
}
