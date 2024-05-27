#include <iostream>
using namespace std;
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
void printer(char mass[10][10]) {
	cout << "  A B C D E F G H I J" <<endl;
	for (int i = 0;i < 10;i++) {
		cout << i<<' ';
		for (int j = 0;j < 10;j++) {
			cout << mass[i][j]<<' ';
		}
		cout << endl;
	}
}
void shooting(char Coutmass[10][10], char mass[10][10]) {
	int cordA, cordB;
	char b[3];
	cin >> b;
	cordB = int(b[0]) - 65;
	cordA = int(b[1])-48;
	if (mass[cordA][cordB] == '~') {
		Coutmass[cordA][cordB] = '-';
		return;
	}
	if (mass[cordA][cordB] == '#' and ((cordA > 0 and mass[cordA - 1][cordB] == '#') or (cordA < 9 and mass[cordA + 1][cordB] == '#') or (cordB > 0 and mass[cordA][cordB - 1] == '#') or (cordB < 9 and mass[cordA][cordB + 1] == '#') or ((cordA < 9 and cordB>0) and mass[cordA + 1][cordB - 1] == '#') or ((cordA < 9 and cordB < 9) and mass[cordA + 1][cordB + 1] == '#') or ((cordA > 0 and cordB < 9) and mass[cordA - 1][cordB + 1] == '#') or ((cordA > 0 and cordB > 0) and mass[cordA - 1][cordB - 1] == '#'))){
		Coutmass[cordA][cordB] = '+';
		return;
	}
	Coutmass[cordA][cordB] = '*';
}
int main()
{
	srand(time(0));
	char bot[10][10];
	char human[10][10];
	char Coutbot[10][10];
	for (int i = 0;i < 10;i++) {
		for (int j = 0;j < 10;j++) {
			bot[i][j] = '~';
			human[i][j] = '~';
			Coutbot[i][j] = '~';
		}
	}
	zapolnenie(bot);
	/*zapolnenie(human);*/
	printer(bot);
	shooting(Coutbot, bot);
	printer(Coutbot);
}