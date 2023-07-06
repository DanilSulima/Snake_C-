#include <iostream>
#include <random>
#include<conio.h>
using namespace std;
bool setApple(char **field) {
	//todo
}
struct snakePart {
	int x, y;
	snakePart* next;
	snakePart* prev;
};
void printField(char **field, int fieldWidth, int fieldHeight) {
	for (int i = 0; i < fieldHeight; i++) {
		for (int j = 0; j < fieldWidth; j++) {
			cout << field[i][j];
		}
		cout << "|\n";
	}
	for (int j = 0; j < fieldWidth; j++)
		cout << "_";
};
void clearField(char** field, int fieldWidth, int fieldHeight) {

	for (int i = 0; i < fieldHeight; i++) {
		for (int j = 0; j < fieldWidth; j++) {
			field[i][j] = ' ';
		}
	}
};

int main() {
	setlocale(LC_ALL, "UKR");
	int fieldWidth, fieldHeight;
	do {
		system("cls");
		cout << " Width: ";
		cin >> fieldWidth;
		cout << " Height: ";
		cin >> fieldHeight;
	} while ((fieldWidth <= 2) or (fieldHeight <= 2));
	char** field = new char* [fieldHeight];
	for(int i = 0; i < fieldHeight; i++) {
		field[i] = new char[fieldWidth];
	}
	clearField(field, fieldHeight, fieldWidth);
	system("cls");
	for (int i = 0; i < fieldHeight; i++) {
		for (int j = 0; j < fieldWidth; j++) {
			cout<<field[i][j];
		}
		cout << endl;
	}

	snakePart snake;
	snakePart* snakeHead= &snake;
	snake.x = rand() % fieldWidth;
	snake.y = rand() % fieldHeight;
	snake.next = NULL; 
	snake.prev = NULL;

	bool alive = true;
	char symbol; 
	int currentLegth = 0;
	int appleX, appleY;
	appleX = rand() % fieldWidth;
	appleY = rand() % fieldHeight; 

	snakePart* snakeCurrent = snakeHead;

	int snakeXprev, snakeYprev;

	int lenght = 1;

	while (alive)
	{
		snakeXprev = snake.x;
		snakeYprev = snake.y;
		symbol = _getch();
		if ((symbol == 'w') or symbol == 'W') {
			snake.y -= 1;
			if (snake.y < 0) snake.y = fieldHeight - 1;
		}
		if ((symbol == 's') or symbol == 'S') {
			snake.y = ((snake.y + 1) % fieldHeight);
		}
		if ((symbol == 'a') or symbol == 'A') {
			snake.x -= 1;
			if (snake.x < 0) snake.x = fieldHeight - 1;
		}
		if ((symbol == 'd') or symbol == 'D') {
			snake.x = ((snake.x + 1) % fieldHeight);
		}

		snakeCurrent = snakeHead;
		if (lenght > 1) {
			snakeCurrent = snakeCurrent->next;
			while (snakeCurrent->next != NULL) {
				if (field[snake.y][snake.x] == 'o') {
					alive = false;
					break;
				}
				snakeCurrent = snakeCurrent->next;
			}
		}
		if (!alive) break;

		if ((snake.x == appleX) and (snake.y == appleY)) {

			do {
				appleX = rand() % fieldWidth;
				appleY = rand() % fieldHeight;

			} while ((field[appleY][appleX] != ' '));

			snakeCurrent = snakeHead;
			while (snakeCurrent->next != NULL) snakeCurrent = snakeCurrent->next;
			snakeCurrent->next = new snakePart;
			snakeCurrent->next->x = snakeXprev;
			snakeCurrent->next->y = snakeYprev;
			snakeCurrent->next->prev = snakeCurrent;
			snakeCurrent->next->next = NULL;
			lenght++;
		}

		snakeCurrent = snakeHead;

		if (lenght > 1) {
			while (snakeCurrent->next != NULL) snakeCurrent = snakeCurrent->next;
			while (snakeCurrent != snakeHead->next) {
				snakeCurrent->x = snakeCurrent->prev->x;
				snakeCurrent->y = snakeCurrent->prev->y;
				snakeCurrent = snakeCurrent->prev;
			}
			snakeCurrent->x = snakeXprev;
			snakeCurrent->y = snakeYprev;
		}
		snakeCurrent = snakeHead;
			
		currentLegth = 0;

		clearField(field, fieldHeight, fieldWidth);

		field[appleY][appleX] = '+';

		while (snakeCurrent != NULL) {
			if (currentLegth == 0) field[snakeCurrent->y][snakeCurrent->x] = 'O';
			else field[snakeCurrent->y][snakeCurrent->x] = 'o';
			currentLegth++;
			snakeCurrent = snakeCurrent->next;
		}
		system("cls");
		cout << " Your current score: " << lenght << endl;
		printField(field, fieldHeight, fieldWidth);
	}
	system("cls");
	cout <<"\n    Game over!    ";
	cout << "\n    Your score : " << lenght << endl;
	return 0;
}

