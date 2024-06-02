#include <iostream>
#include <Windows.h>

using namespace std;
int Myquantity = 20;
int Enemyquantity = 20;
void printer(char mass[10][10], bool show) {
	cout << "  A B C D E F G H I J" << endl;
	for (int i = 0;i < 10;i++) {
		cout << i << ' ';
		for (int j = 0;j < 10;j++) {
			if (mass[i][j] == '#' and !show)
				cout << "~ ";
			else
				cout << mass[i][j] << ' ';
		}
		cout << endl;
	}
}
bool isFit(char mass[10][10], int x1, int y1, int size) {
	size--;
	int x2 =x1, y2 = y1;
	bool h = rand() % 2;
	for (int i = 0; i < 2;i++) {
		switch(h) {
			case true:
				while(size > 0 and y2 < 9 and ((y2 < 8) ? (mass[x2][y2 + 2] != '#' and mass[x2-1][y2+2] != '#' and mass[x2+1][y2+2] != '#') : true)) {
					y2++;
					size--;
				}
				while (size > 0 and y1 > 0 and ((y1 > 1) ? (mass[x1][y1 - 2] != '#' and mass[x1-1][y1 - 2] != '#' and mass[x1+1][y1 - 2] != '#') : true))
				{
					y1--;
					size--;
				}
				if (size == 0) {
					for (;y1 <= y2;y1++) {
						mass[x1][y1] = '#';
					}
					return true;
				}
				h = false;
				break;
			case false:
				while (size > 0 and x2 < 9 and ((x2 < 8) ? (mass[x2 + 2][y2] != '#' and mass[x2 + 2][y2+1] != '#' and mass[x2 + 2][y2-1] != '#') : true)) {
					x2++;
					size--;
				}
				while (size > 0 and x1 > 0 and ((x1 > 1) ? (mass[x1 - 2][y1] != '#' and mass[x1 - 2][y1+1] != '#' and mass[x1 - 2][y1-1] != '#'): true))
				{
					x1--;
					size--;
				}
				if (size == 0) {
					for (;x1 <= x2;x1++) {
						mass[x1][y1] = '#';
					}
					return true;
				}
				h = true;
				break;
		}
	}
	return false;
}
void zapolnenie(char mass[10][10]) {
	for (int size = 4;size > 0;size--) {
		for (int j = 5 - size;j > 0;j--) {
			int x, y;
			do
			{
				x = rand() % 10;
				y = rand() % 10;
			} while (mass[x][y] == '#' or x > 0 and mass[x - 1][y] == '#' or x < 9 and mass[x + 1][y] == '#' or y>0 and mass[x][y - 1] == '#' or y < 9 and mass[x][y + 1] == '#' or (x < 9 and y>0) and mass[x + 1][y - 1] == '#' or (x < 9 and y < 9) and mass[x + 1][y + 1] == '#' or (x > 0 and y < 9) and mass[x - 1][y + 1] == '#' or (x > 0 and y > 0) and mass[x - 1][y - 1] == '#');
			if (size == 1) {
				mass[x][y] = '#';
				continue;
			}
			if (!isFit(mass, x, y, size))
				j++;
		}
	}
}
bool shooting(char mass[10][10], int cordA, int cordB) {
	if (mass[cordA][cordB] == '~') {
		mass[cordA][cordB] = '?';
		return false;
	}
	if (mass[cordA][cordB] == '#' and ((cordA > 0 and mass[cordA - 1][cordB] == '#') or (cordA < 9 and mass[cordA + 1][cordB] == '#') or (cordB > 0 and mass[cordA][cordB - 1] == '#') or (cordB < 9 and mass[cordA][cordB + 1] == '#') or ((cordA < 9 and cordB>0) and mass[cordA + 1][cordB - 1] == '#') or ((cordA < 9 and cordB < 9) and mass[cordA + 1][cordB + 1] == '#') or ((cordA > 0 and cordB < 9) and mass[cordA - 1][cordB + 1] == '#') or ((cordA > 0 and cordB > 0) and mass[cordA - 1][cordB - 1] == '#'))) {
		mass[cordA][cordB] = '+';
		return true;
	}
	if ((cordA == 0 or mass[cordA - 1][cordB] != '+') and (cordA == 9 or mass[cordA + 1][cordB] != '+') and (cordB == 0 or mass[cordA][cordB - 1] != '+') and (cordB == 9 or mass[cordA][cordB + 1] != '+')) {
		for (int i = -1; i < 2; i++) {
			for (int j = -1; j < 2; j++) {
				if (i == 0 and j == 0) {
					continue;
				}
				if (cordA + i >= 0 and cordA + i <= 9 and cordB + j >= 0 and cordB + j <= 9) mass[cordA + i][cordB + j] = '?';
			}
		}
		mass[cordA][cordB] = '*';
		return true;
	}
	mass[cordA][cordB] = '+';
	int cordA2 = cordA;
	int cordB2 = cordB;
	if (mass[cordA + 1][cordB] == '+' or mass[cordA - 1][cordB] == '+') {
		while (cordA2 <= 9 and mass[cordA2][cordB2] == '+') {
			if (cordB2 > 0) {
				mass[cordA2][cordB2 - 1] = '?';
			}
			if (cordB2 < 9) {
				mass[cordA2][cordB2 + 1] = '?';
			}
			mass[cordA2][cordB2] = '*';
			cordA2++;
		}

		if (cordA2 <= 9) {
			mass[cordA2][cordB2] = '?';
			if (cordB2 > 0)
				mass[cordA2][cordB2 - 1] = '?';
			if (cordB2 < 9)
				mass[cordA2][cordB2 + 1] = '?';
		}
		cordA--;
		while (cordA >= 0 and mass[cordA][cordB] == '+') {
			if (cordB > 0) {
				mass[cordA][cordB - 1] = '?';
			}
			if (cordB < 9) {
				mass[cordA][cordB + 1] = '?';
			}
			mass[cordA][cordB] = '*';
			cordA--;
		}
		if (cordA >= 0) {
			mass[cordA][cordB] = '?';
			if (cordB > 0)
				mass[cordA][cordB - 1] = '?';
			if (cordB < 9)
				mass[cordA][cordB + 1] = '?';
		}
	}
	else {
		while (cordB2 <= 9 and mass[cordA2][cordB2] == '+') {
			if (cordA2 > 0) {
				mass[cordA2 - 1][cordB2] = '?';
			}
			if (cordA2 < 9) {
				mass[cordA2 + 1][cordB2] = '?';
			}
			mass[cordA2][cordB2] = '*';
			cordB2++;
		}
		if (cordB2 <= 9) {
			mass[cordA2][cordB2] = '?';
			if (cordA2 > 0)
				mass[cordA2 - 1][cordB2] = '?';
			if (cordA2 < 9)
				mass[cordA2 + 1][cordB2] = '?';
		}
		cordB--;
		while (cordB >= 0 and mass[cordA][cordB] == '+') {
			if (cordA > 0) {
				mass[cordA - 1][cordB] = '?';
			}
			if (cordA < 9) {
				mass[cordA + 1][cordB] = '?';
			}
			mass[cordA][cordB] = '*';
			cordB--;
		}
		if (cordB >= 0) {
			mass[cordA][cordB] = '?';
			if (cordB > 0)
				mass[cordA - 1][cordB] = '?';
			if (cordB < 9)
				mass[cordA + 1][cordB] = '?';
		}
	}
}
void NavigateAI(char mass[10][10]) {
	int x=-1, y=-1;
	for (int i = 0;i < 10;i++) {
		for (int j = 0;j < 10;j++) {
			if (mass[i][j] == '+') {
				x = i;
				y = j;
				break;
			}
		}
	}
	if (x == -1) {
		do {
			x = rand() % 10;
			y = rand() % 10;
		} while (mass[x][y] == '?');
		if (shooting(mass, x, y))
			Myquantity--;
		return;
	}
	if (x < 9 and mass[x + 1][y] == '+') {
		bool high = rand() % 2;
		for (int i = 0;i < 2;i++) {
			switch (high)
			{
			case true:
				if (x > 0 and mass[x - 1][y] != '?') {
					if(shooting(mass, x-1, y))
						Myquantity--;
					return;
				}
				high = false;
				break;
			case false:
				if (x < 9 and mass[x + 1][y] != '?') {
					if (shooting(mass, x+1, y))
						Myquantity--;
					return;
				}
				high = true;
				break;
			}
		}
	}
	else if(y<9 and mass[x][y+1] =='+') {
		bool left = rand() % 2;
		for (int i = 0;i < 2;i++) {
			switch (left)
			{
			case true:
				if (y > 0 and mass[x][y-1] != '?') {
					if (shooting(mass, x, y-1))
						Myquantity--;
					return;
				}
				left = false;
				break;
			case false:
				if (y < 9 and mass[x][y+1] != '?') {
					if (shooting(mass, x, y+1))
						Myquantity--;
					return;
				}
				left = true;
				break;
			}
		}
	}
	else {
		bool h = rand() % 2;
		for (int i = 0;i < 2;i++) {
			if (h) {
				bool left = rand() % 2;
				if (left and y > 0 and mass[x][y - 1] != '?') {
					if (shooting(mass, x, y-1))
						Myquantity--;
					return;
				}
				else if (!left and y < 9 and mass[x][y + 1] != '?') {
					if (shooting(mass, x, y+1))
						Myquantity--;
					return;
				}
			}
			bool high = rand() % 2;
			if (high and x > 0 and mass[x - 1][y] != '?') {
				if (shooting(mass, x-1, y))
					Myquantity--;
				
				return;
			}
			else if (!high and x < 9 and mass[x + 1][y] != '?') {
				if (shooting(mass, x+1, y))
					Myquantity--;
				return;
			}
			h = !h;
		}
	}
}
void NavigateHuman(char mass[10][10]) {
	int cordA, cordB;
	char b[3];
	cin >> b;
	cordB = int(b[0]) - 65;
	cordA = int(b[1]) - 48;
	if (shooting(mass, cordA, cordB))
		Enemyquantity--;
}

int main()
{
	std::system("mode con cols=22 lines=27");
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
	srand(time(0));
	char bot[10][10];
	char human[10][10];
	for (int i = 0;i < 10;i++) {
		for (int j = 0;j < 10;j++) {
			bot[i][j] = '~';
			human[i][j] = '~';
		}
	}
	zapolnenie(bot);
	zapolnenie(human);
	cout << "bot\'s map" << endl;
	printer(bot, false);
	cout << "your map" << endl;
	printer(human, true);
	while(Myquantity != 0 and Enemyquantity!=0) {
		NavigateHuman(bot);
		system("cls");
		NavigateAI(human);
		cout << "bot\'s map" << endl;
		printer(bot, false);
		cout << "your map" << endl;
		printer(human, true);
	}
	if (Myquantity == 0) {
		cout << "Defeat(((";
	}
	else {
		cout << "WIIIN";
	}
}