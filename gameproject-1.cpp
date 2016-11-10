#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<deque>
#include <iostream>

int v = 14;   //player1
int s = 13;   //player2


using namespace std;

class timer {
private:
	unsigned long begTime;
public:
	void start() {
		begTime = clock();
	}

	unsigned long elapsedTime() {
		return ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
	}

	bool isTimeout(unsigned long seconds) {
		return seconds >= elapsedTime();
	}
};

struct Bullet {
	int x, y, d;
};

deque<Bullet> bullets;

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}
void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}


void people(int x, int y) { gotoxy(x, y); setcolor(14, 0); printf(" <X> "); }
void people_1(int x, int y) { gotoxy(x, y); setcolor(15, 0); printf(" <X> "); }
void erase_people(int x, int y) { gotoxy(x, y); printf("     "); }
void erase_bullet(int x, int y) { gotoxy(x, y); printf(" "); }


void bullet(int x, int y) {
	Bullet b;
	b.x = x;
	b.y = y;
	b.d = 1;
	bullets.push_back(b);
}
void bullet1(int x, int y) {
	Bullet b;
	b.x = x;
	b.y = y;
	b.d = -1;
	bullets.push_back(b);
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}


void page_nameplayerVSCOM();
void page_nameplayerVSplayer();
void page_game_playerVSplayer();
void page_game_playerVSCOM();
void page_bar();
void shooting_x();
void K_O();
void display_1();
void display_2();
void display_3();
void player1_win();
void player2_win();
void you_win();
void you_lose();


//////////////////////////////////////////////////////////////////////////////// main of game
int main()
{
loop:	shooting_x();

	char key = '/';
	int i = 0;
	int j = 4;

	do {

		if (_kbhit())
		{
			key = _getch();
			if (key == 's')  i++; Beep(5000, 25);
			if (key == 'w')  i--;

		}

		if (i < 0) i = 0;
		if (i == 0)
		{

			gotoxy(31, 19); setcolor(15, j);  printf("  Player Vs Player  ");
			gotoxy(31, 20); setcolor(15, 0);  printf("  Player Vs COM     ");
			gotoxy(36, 21); setcolor(15, 0);  printf("   EXIT  ");
		//	gotoxy(45, 23); setcolor(15, 0); printf("  Waratep tubboon  ");
		}
		if (i == 1)
		{

			gotoxy(31, 19); setcolor(15, 0);  printf("  Player Vs Player  ");
			gotoxy(31, 20); setcolor(15, j);  printf("  Player Vs COM     ");
			gotoxy(36, 21); setcolor(15, 0);  printf("   EXIT  ");
			
		}
		if (i == 2)
		{

			gotoxy(31, 19); setcolor(15, 0);  printf("  Player Vs Player  ");
			gotoxy(31, 20); setcolor(15, 0);  printf("  Player Vs COM     ");
			gotoxy(36, 21); setcolor(15, j);  printf("   EXIT  ");

		}
		if (i == 3) i = 2;
		if (key == ' ' && i == 0) {
			page_game_playerVSplayer();
			i = 0;
			key = '/';
			shooting_x();

		}
		if (key == ' ' && i == 1) {
			page_game_playerVSCOM();
			i = 0;
			key = '/';
			shooting_x();
		}
		if (key == ' ' && i == 2) { 
			setcolor(0, 0); 
			break;
			return 0; }
		fflush(stdin);
	} while (key != ''); setcolor(0, 0);

	//	goto loop;
}
////////////////////////////////////////////////////////////////////////////////cmain of game


void page_bar()
{

	gotoxy(0, 0); setcolor(8, 0); printf("                                 |           |                                  ");
	//gotoxy(0,1); setcolor(8,0); printf("                                 |           |                                  ");	
	gotoxy(0, 2); setcolor(8, 0); printf("_________________________________|___________|__________________________________");
	gotoxy(0, 23); setcolor(0, 3); printf("                                                                                ");
	gotoxy(0, 24); setcolor(8, 0); printf("                                    HOME : F9     RESTART : F10     EXIT : Esc ");

}

void page_game_playerVSplayer()
{
	system("cls");
	int x = 10, y = 12, x_1 = 65, y_1 = 12, bullet_status_1 = 0, bullet_status_2 = 0, xbullet = 0, ybullet = 0, xbullet2 = 0, ybullet2 = 0;
	int sec = 200;
	char key;
	int hel1 = 0, hel2 = 0;
	char nameP1[20], nameP2[20];

	/////////////////////////////////////////////////////////////////////////////

	setcolor(14, 0); gotoxy(20, 10); printf("Enter Name Player 1 : ");
	scanf("%s", &nameP1);
	setcolor(15, 0); gotoxy(20, 12); printf("Enter Name Player 2 : ");
	scanf("%s", &nameP2);
	system("cls");

	display_3(); Sleep(800); Beep(5000, 25); system("cls"); Sleep(100);
	display_2(); Sleep(800); Beep(5000, 25); system("cls"); Sleep(100);
	display_1(); Sleep(800); Beep(5000, 25); system("cls"); Sleep(100);

	//for(int i = 0 ; i < hel1 ; i++) { setcolor(14,0); gotoxy(i * 5 + 5,1); printf("*"); gotoxy(33,1); printf("|");}
	//for(int j = 0 ; j < hel2 ; j++) { setcolor(15,0); gotoxy(j * 5 + 53,1); printf("*"); gotoxy(45,1); printf("|");}
	setcolor(14, 0); gotoxy(10, 1); printf("%s", nameP1); gotoxy(27, 1); printf("%d", hel1); gotoxy(33, 1); printf("|");
	setcolor(15, 0); gotoxy(63, 1); printf("%s", nameP2); gotoxy(49, 1); printf("%d", hel2); gotoxy(45, 1); printf("|");

	people(x, y);
	people_1(x_1, y_1);
	int itemRandTime = 2000;
	int count_bullet = 0;
	int count_bullet1 = 0;
	int max_bullet = 3;
	int max_bullet1 = 3;
	int itemcd = 0;
	int itemcd1 = 0;
	int tTime = 60;
	timer t;
	unsigned int startTime = clock();
	setcursor(0);
	do {
		unsigned long currentTime = clock();
		
		page_bar();
		int cTime = 60 - int(currentTime - startTime) / 1000;
		if (tTime <= 0) {
			break;
		}
		if (cTime != tTime) {
			setcolor(15, 0); gotoxy(38, 1); printf("  "); printf("%d", tTime);
			tTime = cTime;
		}
		
		if (_kbhit())
		{
			//		
			key = _getch();
			if (key == 'a' && x - 1 >= 0) { people(--x, y); }
			if (key == 'd' && x + 1 <= 15) { people(++x, y); }
			if (key == 'w' && y - 1 >= 3) { erase_people(x, y); people(x, --y); }
			if (key == 's' && y + 1 <= 22) { if (y + 1 <= 23) erase_people(x, y); people(x, ++y); }
			if (key == ' ') {
				if (count_bullet < max_bullet) {
					bullet(xbullet = x + 4, ybullet = y);
					count_bullet++;
				}
			}

			///////////////////////////////////////////// player1
			if (key == 'k'  && x_1 - 1 >= 60) { people_1(--x_1, y_1); }
			if (key == ';'  && x_1 + 1 <= 75) { people_1(++x_1, y_1); }
			if (key == 'o'  && y_1 - 1 >= 3) { erase_people(x_1, y_1); people_1(x_1, --y_1); }
			if (key == 'l'  && y_1 + 1 <= 22) { if (y + 1 <= 23) erase_people(x_1, y_1); people_1(x_1, ++y_1); }
			if (key == 'n') {
				if (count_bullet1 < max_bullet1) {
					bullet1(xbullet2 = x_1 - 4, ybullet2 = y_1);
					count_bullet1++;
				}
			}
			fflush(stdin);
		}
		people(x, y);
		people_1(x_1, y_1);
		/////////////////////////////////////////////////////////////////////////////// RANDOM!!!!!!!
		if (itemRandTime <= 0) {
			int random_item = rand() % 5;
			int random_x = rand() % 9 + 35;
			int random_y = rand() % 20 + 3;
			itemRandTime = 2000;
			gotoxy(random_x, random_y);
			printf("%c", 2);
		}
		else {
			itemRandTime -= 15;
		}
		//////////////////////////////////////////////////////////////////////////////// RANDOM!!!!!!

		if (max_bullet > 3) {
			if (itemcd <= 0) {
				gotoxy(2, 1);
				printf("          ", itemcd / 1000);
				max_bullet--;
				itemcd = 5000;
			}
			else {
				gotoxy(2, 1);
				printf("Item : %d", itemcd / 1000);
				itemcd -= 15;
			}
		}
		if (max_bullet1 > 3) {
			if (itemcd1 <= 0) {
				gotoxy(70, 1);
				printf("          ", itemcd1 / 1000);
				max_bullet1--;
				itemcd1 = 5000;
			}
			else {
				gotoxy(70, 1);
				printf("Item : %d", itemcd1 / 1000);
				itemcd1 -= 15;
			}
		}


		//////////////////////////////// status bullet player1
		for (int i = 0; i < bullets.size(); i++) {
			Bullet *b = &bullets[i];
			if (b->d == 1) {
				if (b->x == 75) {
					erase_bullet(b->x, b->y);
					bullets.erase(bullets.begin() + i);
					count_bullet--;
				}
				else {
					if (cursor(b->x + 1, b->y) == '<')
					{
						hel2++;
						setcolor(14, 0); gotoxy(27, 1); printf("%d", hel2); gotoxy(33, 1); printf("|");
					}
					if (cursor(b->x + 1, b->y) == 2) {
						max_bullet++;
						itemcd = 5000;
					}
					erase_bullet(b->x, b->y);
					b->x++;
					gotoxy(b->x, b->y);
					setcolor(14, 0);
					printf("=");
				}

			}
			else {
				if (b->x == 2) {
					erase_bullet(b->x, b->y);
					bullets.erase(bullets.begin() + i);
					count_bullet1--;
				}
				else {
					if (cursor(b->x - 1, b->y) == '>')
					{
						hel1++;
						setcolor(15, 0); gotoxy(49, 1); printf("%d", hel1); gotoxy(45, 1); printf("|");	
					}
					if (cursor(b->x - 1, b->y) == 2) {
						max_bullet1++;
						itemcd1 = 5000;
					}
					erase_bullet(b->x, b->y);
					b->x--;
					gotoxy(b->x, b->y);
					setcolor(15, 0);
					printf("=");
				}
			}
		}
		Sleep(15);

	} while (key != '' || time == 0); system("cls"); //main();
	if (hel2 > hel1) { 
		system("cls"); player1_win(); Sleep(2000);
	}
	else {
		system("cls"); player2_win();  Sleep(2000); 
	}
}

void page_game_playerVSCOM()
{
	system("cls");
	int x = 10, y = 12, x_1 = 65, y_1 = 12, bullet_status_1 = 0, bullet_status_2 = 0, xbullet = 0, ybullet = 0, xbullet2 = 0, ybullet2 = 0;
	int sec = 2000;
	char key;
	int hel1 = 0, hel2 = 0;
	char nameP1[20];
	char nameP2[] = "COM";
	char randomMove_COM[] = "klon;";
	int move_COM;
	int count_bullet = 0;
	int count_bullet1 = 0;
	int max_bullet = 5;
	int max_bullet1 = 5;
	int move_o = 9, move_l = 20;
	int itemcd = 0;
	int itemcd1 = 0;
	/////////////////////////////////////////////////////////////////////////////

	setcolor(14, 0); gotoxy(20, 10); printf("Enter Name Player 1 : ");
	scanf("%s", &nameP1);
	system("cls");

	display_3(); Sleep(800); Beep(5000, 25); system("cls"); Sleep(100);
	display_2(); Sleep(800); Beep(5000, 25); system("cls"); Sleep(100);
	display_1(); Sleep(800); Beep(5000, 25); system("cls"); Sleep(100);

	//for(int i = 0 ; i < hel1 ; i++) { setcolor(14,0); gotoxy(i * 5 + 5,1); printf("*"); gotoxy(33,1); printf("|");}
	//for(int j = 0 ; j < hel2 ; j++) { setcolor(15,0); gotoxy(j * 5 + 53,1); printf("*"); gotoxy(45,1); printf("|");}
	setcolor(14, 0); gotoxy(10, 1); printf("%s", nameP1); gotoxy(27, 1); printf("%d", hel1); gotoxy(33, 1); printf("|");
	setcolor(15, 0); gotoxy(63, 1); printf("%s", nameP2); gotoxy(49, 1); printf("%d", hel2); gotoxy(45, 1); printf("|");
	

	people(x, y);
	people_1(x_1, y_1);

	int AimoveTime = 100;
	int itemRandTime = 2000;
	setcursor(0);
	unsigned long startTime = clock();
	int tTime = 60;
	do {
		unsigned long currentTime = clock();
		page_bar();
		int cTime = 60 - int(currentTime - startTime) / 1000;
		if (tTime <= 0) {
			break;
		}
		if (cTime != tTime) {
			setcolor(15, 0); gotoxy(38, 1); printf("  "); printf("%d", tTime);
			tTime = cTime;
		}
		if (_kbhit())
		{
			//		
			key = _getch();
			
			//		    clock_t t;
			//    		t = clock();
			//    		int x = 20000-t;

			if (key == 'a' && x - 1 >= 0) { people(--x, y); }
			if (key == 'd' && x + 1 <= 15) { people(++x, y); }
			if (key == 'w' && y - 1 >= 3) { erase_people(x, y); people(x, --y); }
			if (key == 's' && y + 1 <= 22) { if (y + 1 <= 23) erase_people(x, y); people(x, ++y); }
			if (key == ' ') { 
				if (count_bullet < max_bullet) {
					bullet(xbullet = x + 4, ybullet = y);
					gotoxy(0, 15);
					count_bullet++;
				}
			}

			///////////////////////////////////////////// player1
			//           if (randomMove_COM[move_COM] == 'o' and y-1 >= 3 ) {erase_people (x_1,y_1); people_1(x_1,--y_1);}
			//           if (randomMove_COM[move_COM] == 'l' and y+1 <= 22 ) {if(y+1 <= 23 ) erase_people(x_1,y_1); people_1(x_1,++y_1);}
			//           if (randomMove_COM[move_COM] == 'n' ) { bullet1(xbullet2 = x_1-4,ybullet2 = y_1); }

			
			fflush(stdin);
		}
		/////////////////////////////////////////////////////////////////////////////// RANDOM!!!!!!!
		people(x, y);
		people_1(x_1, y_1);


		if (max_bullet > 3) {
			if (itemcd <= 0) {
				gotoxy(2, 1);
				printf("          ", itemcd / 1000);
				max_bullet--;
				itemcd = 5000;
			}
			else {
				gotoxy(2, 1);
				printf("Item : %d", itemcd / 1000);
				itemcd -= 15;
			}
		}
		if (max_bullet1 > 3) {
			if (itemcd1 <= 0) {
				gotoxy(70, 1);
				printf("          ", itemcd1 / 1000);
				max_bullet1--;
				itemcd1 = 5000;
			}
			else {
				gotoxy(70, 1);
				printf("Item : %d", itemcd1 / 1000);
				itemcd1 -= 15;
			}
		}


		if (AimoveTime <= 0) {
			move_COM = rand() % 6;
			if (randomMove_COM[move_COM] == 'k'  && x_1 - 1 >= 60) { people_1(--x_1, y_1); }
			if (randomMove_COM[move_COM] == ';'  && x_1 + 1 <= 75) { people_1(++x_1, y_1); }
			if (randomMove_COM[move_COM] == 'o'  && y_1 - 1 >= 3) { erase_people(x_1, y_1); people_1(x_1, --y_1); }
			if (randomMove_COM[move_COM] == 'l'  && y_1 + 1 <= 22) { if (y + 1 <= 23) erase_people(x_1, y_1); people_1(x_1, ++y_1); }
			if (randomMove_COM[move_COM] == 'n' && count_bullet1 < max_bullet1) { bullet1(xbullet2 = x_1 - 4, ybullet2 = y_1); count_bullet1++; }
			AimoveTime = 100;
		}
		else {
			AimoveTime -= 15;
		}
		
		if (itemRandTime <= 0) {
			int random_item = rand() % 5;
			int random_x = rand() % 9 + 35;
			int random_y = rand() % 20 + 3;
			itemRandTime = 2000;
			gotoxy(random_x, random_y); 
			printf("%c", 2);
		}
		else {
			itemRandTime -= 15;
		}

		

		//////////////////////////////////////////////////////////////////////////////// RANDOM!!!!!!


		//////////////////////////////// status bullet player1
		for (int i = 0; i < bullets.size(); i++) {
			Bullet *b = &bullets[i];
			if (b->d == 1) {
				if (b->x == 75) {
					erase_bullet(b->x, b->y);
					bullets.erase(bullets.begin() + i);
					count_bullet--;
				}
				else {
					if (cursor(b->x + 1, b->y) == '<')
					{
						hel2++;
						setcolor(14, 0); gotoxy(27, 1); printf("%d", hel2); gotoxy(33, 1); printf("|");
					}
					if (cursor(b->x + 1, b->y) == 2) {
						max_bullet++;
						itemcd = 5000;
					}
					erase_bullet(b->x, b->y);
					b->x++;
					gotoxy(b->x, b->y);
					setcolor(14, 0);
					printf("=");
				}
			}
			else {
				if (b->x == 2) {
					erase_bullet(b->x, b->y);
					bullets.erase(bullets.begin() + i);
					
				}
				else {
					if (cursor(b->x - 1, b->y) == '>')
					{
						hel1++;
						setcolor(15, 0); gotoxy(49, 1); printf("%d", hel1); gotoxy(45, 1); printf("|");
					}
					if (cursor(b->x - 1, b->y) == 2) {
						max_bullet1++;
						itemcd1 = 5000;
					}
					erase_bullet(b->x, b->y);
					count_bullet1--;
					b->x--;
					gotoxy(b->x, b->y);
					setcolor(15, 0);
					printf("=");
				}
			}
		}
		Sleep(15);


	} while (key != '' || time == 00000);
	system("cls"); //main();
	if (hel2 > hel1) { system("cls"); you_win(); Sleep(2000); return; }
	else { system("cls"); you_win();  Sleep(2000); return; }




}


void K_O()
{
	setcursor(0);
	int i = 14;
	printf("\n\n\n\n\n\n\n");
	setcolor(0, 0); printf("\t\t\t    "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("   "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("      "); setcolor(i, i); printf("________\n");
	setcolor(0, 0); printf("\t\t\t    "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("  "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("       "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("    "); setcolor(i, i); printf("__\n");
	setcolor(0, 0); printf("\t\t\t    "); setcolor(i, i); printf("__"); setcolor(0, 0); printf(" "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("        "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("    "); setcolor(i, i); printf("__\n");
	setcolor(0, 0); printf("\t\t\t    "); setcolor(i, i); printf("____"); setcolor(0, 0); printf("         "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("    "); setcolor(i, i); printf("__\n");
	setcolor(0, 0); printf("\t\t\t    "); setcolor(i, i); printf("__"); setcolor(0, 0); printf(" "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("        "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("    "); setcolor(i, i); printf("__\n");
	setcolor(0, 0); printf("\t\t\t    "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("  "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("       "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("    "); setcolor(i, i); printf("__\n");
	setcolor(0, 0); printf("\t\t\t    "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("   "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("  "); setcolor(i, i); printf("__"); setcolor(0, 0); printf("  "); setcolor(i, i); printf("________"); setcolor(0, 0); printf("  "); setcolor(i, i); printf("__\n"); setcolor(0, 0);
}


void shooting_x()
{
	setcursor(0);
	int j = 14;
	int color_x = 12;
	//shooting
	system("cls");
	printf("\n\n\n");
	setcolor(0, 0); printf("     ");
	setcolor(j, j); printf("_______"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("   "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("  ");
	setcolor(j, j); printf("_______"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("_______");
	setcolor(0, 0); printf("  "); setcolor(j, j); printf("______"); setcolor(0, 0); printf("  ");
	setcolor(j, j); printf("______"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("    "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("_______\n");

	setcolor(0, 0); printf("     ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("       "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("   "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("  ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("   "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("  "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("   ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("    "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("      "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(j, j); printf("___"); setcolor(0, 0); printf("   "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("  "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("   ");
	setcolor(j, j); printf("__\n");

	setcolor(0, 0); printf("     ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("       "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("   "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("  ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("   "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("  "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("   ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("    "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("      "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(j, j); printf("____"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("  "); setcolor(j, j); printf("__\n");

	setcolor(0, 0); printf("     ");
	setcolor(j, j); printf("_______"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("_______");
	setcolor(0, 0); printf("  "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("   ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("   "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("      "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("    "); setcolor(j, j); printf("__"); setcolor(0, 0); printf(" ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf(" "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("  "); setcolor(j, j); printf("__\n");

	setcolor(0, 0); printf("     ");
	setcolor(0, 0); printf("     "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("  ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("   "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("  "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("   ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("   "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("      "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("    "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("  ");
	setcolor(j, j); printf("____"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("  "); setcolor(j, j); printf("___\n");

	setcolor(0, 0); printf("     ");
	setcolor(0, 0); printf("     "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("  ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("   "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("  "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("   ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("   "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(j, j); printf("__"); setcolor(0, 0); printf("      "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("    "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("   ");
	setcolor(j, j); printf("___"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("   "); setcolor(j, j); printf("__\n");

	setcolor(0, 0); printf("     ");
	setcolor(j, j); printf("_______"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("   "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("  ");
	setcolor(j, j); printf("_______"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("_______");
	setcolor(0, 0); printf("    "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(j, j); printf("______"); setcolor(0, 0); printf("  "); setcolor(j, j); printf("__");
	setcolor(0, 0); printf("    "); setcolor(j, j); printf("__"); setcolor(0, 0); printf("  ");
	setcolor(j, j); printf("_______\n"); setcolor(0, 0);

	//x large
	//
	//setcolor(12,12); printf("__");setcolor(0,0); printf("     ");setcolor(12,12); printf("__\n");
	//setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
	//setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf(" ");setcolor(12,12); printf("__\n");					
	//setcolor(0,0); printf("   ");setcolor(12,12); printf("___\n");
	//setcolor(0,0); printf("  ");setcolor(12,12); printf("__");setcolor(0,0); printf(" ");setcolor(12,12); printf("__\n");
	//setcolor(0,0); printf(" ");setcolor(12,12); printf("__");setcolor(0,0); printf("   ");setcolor(12,12); printf("__\n");
	//setcolor(12,12); printf("__");setcolor(0,0); printf("     ");setcolor(12,12); printf("__\n");setcolor(0,0);
	//

	// x small
	printf("\n\n");
	setcolor(0, 0); printf("\t\t\t\t     "); setcolor(color_x, color_x); printf("__"); setcolor(0, 0); printf("   ");
	setcolor(color_x, color_x); printf("__\n");

	setcolor(0, 0); printf("\t\t\t\t    "); setcolor(0, 0); printf("  "); setcolor(color_x, color_x); printf("__");
	setcolor(0, 0); printf(" "); setcolor(color_x, color_x); printf("__\n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(color_x, color_x); printf("____________"); setcolor(0, 0); printf("   ");
	setcolor(color_x, color_x); printf("___"); setcolor(0, 0); printf("   "); setcolor(color_x, color_x); printf("____________\n");

	setcolor(0, 0); printf("\t\t\t\t    "); setcolor(0, 0); printf("  "); setcolor(color_x, color_x); printf("__");
	setcolor(0, 0); printf(" "); setcolor(color_x, color_x); printf("__\n");

	setcolor(0, 0); printf("\t\t\t\t     "); setcolor(color_x, color_x); printf("__"); setcolor(0, 0); printf("   ");
	setcolor(color_x, color_x); printf("__\n"); setcolor(0, 0);


}
void display_1()
{
	int i = 38, j = 3, k = 3;
	gotoxy(i, 5); setcolor(j, k); printf("   ");
	gotoxy(35, 6); setcolor(j, k); printf("      ");
	gotoxy(35, 7); setcolor(j, k); printf("      ");
	gotoxy(i, 8); setcolor(j, k); printf("   ");
	gotoxy(i, 9); setcolor(j, k); printf("   ");
	gotoxy(i, 10); setcolor(j, k); printf("   ");
	gotoxy(i, 11); setcolor(j, k); printf("   ");
	gotoxy(i, 12); setcolor(j, k); printf("   ");
	gotoxy(i, 13); setcolor(j, k); printf("   ");
	gotoxy(i, 14); setcolor(j, k); printf("   ");
	gotoxy(i, 15); setcolor(j, k); printf("   ");
	gotoxy(i, 16); setcolor(j, k); printf("   ");
	gotoxy(i, 17); setcolor(j, k); printf("   ");
	gotoxy(i, 18); setcolor(j, k); printf("   ");
	setcolor(0, 0);
}
void display_2()
{
	int i = 47, l = 31, j = 3, k = 3;
	gotoxy(l, 5); setcolor(j, k); printf("                   ");
	gotoxy(l, 6); setcolor(j, k); printf("                   ");
	gotoxy(i, 7); setcolor(j, k);  printf("   ");
	gotoxy(i, 8); setcolor(j, k);  printf("   ");
	gotoxy(i, 9); setcolor(j, k);  printf("   ");
	gotoxy(i, 10); setcolor(j, k); printf("   ");
	gotoxy(l, 11); setcolor(j, k); printf("                   ");
	gotoxy(l, 12); setcolor(j, k); printf("                   ");
	gotoxy(l, 13); setcolor(j, k); printf("   ");
	gotoxy(l, 14); setcolor(j, k); printf("   ");
	gotoxy(l, 15); setcolor(j, k); printf("   ");
	gotoxy(l, 16); setcolor(j, k); printf("   ");
	gotoxy(l, 17); setcolor(j, k); printf("                   ");
	gotoxy(l, 18); setcolor(j, k); printf("                   ");
	setcolor(0, 0);
}
void display_3()
{
	int i = 47, l = 31, j = 3, k = 3;
	gotoxy(l, 5); setcolor(j, k); printf("                   ");
	gotoxy(l, 6); setcolor(j, k); printf("                   ");
	gotoxy(i, 7); setcolor(j, k);  printf("   ");
	gotoxy(i, 8); setcolor(j, k);  printf("   ");
	gotoxy(i, 9); setcolor(j, k);  printf("   ");
	gotoxy(i, 10); setcolor(j, k); printf("   ");
	gotoxy(l, 11); setcolor(j, k); printf("                   ");
	gotoxy(l, 12); setcolor(j, k); printf("                   ");
	gotoxy(i, 13); setcolor(j, k); printf("   ");
	gotoxy(i, 14); setcolor(j, k); printf("   ");
	gotoxy(i, 15); setcolor(j, k); printf("   ");
	gotoxy(i, 16); setcolor(j, k); printf("   ");
	gotoxy(l, 17); setcolor(j, k); printf("                   ");
	gotoxy(l, 18); setcolor(j, k); printf("                   ");
	setcolor(0, 0);
}
void player1_win()
{
	//  player
	printf("\n\n\n\n\n");
	setcolor(0, 0); printf("\t     "); setcolor(v, v); printf("_______"); setcolor(0, 0); printf("  "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("    "); setcolor(v, v); printf("_______"); setcolor(0, 0); printf("  "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("    "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("  "); setcolor(v, v); printf("______");
	setcolor(0, 0); printf("  "); setcolor(v, v); printf("_______"); setcolor(0, 0); printf("   "); setcolor(v, v); printf("__\n");

	setcolor(0, 0); printf("\t     "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("   "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("  "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("    "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("   "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("   "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("  "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("   "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("      "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("   "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("   "); setcolor(v, v); printf("__\n");

	setcolor(0, 0); printf("\t     "); setcolor(v, v); printf("_______"); setcolor(0, 0); printf("  "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("    "); setcolor(v, v); printf("_______"); setcolor(0, 0); printf("    "); setcolor(v, v); printf("____");
	setcolor(0, 0); printf("    "); setcolor(v, v); printf("____"); setcolor(0, 0); printf("    "); setcolor(v, v); printf("_______");
	setcolor(0, 0); printf("   "); setcolor(v, v); printf("__\n");

	setcolor(0, 0); printf("\t     "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("       "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("    "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("   "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("     "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("     "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("      "); setcolor(v, v); printf("__"); setcolor(0, 0); printf(" "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("     "); setcolor(v, v); printf("__\n");

	setcolor(0, 0); printf("\t     "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("       "); setcolor(v, v); printf("____");
	setcolor(0, 0); printf("  "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("   "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("     "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("     "); setcolor(v, v); printf("______");
	setcolor(0, 0); printf("  "); setcolor(v, v); printf("__"); setcolor(0, 0); printf("  "); setcolor(v, v); printf("__");
	setcolor(0, 0); printf("    "); setcolor(v, v); printf("__\n\n");


	// win!
	setcolor(0, 0); printf("\t\t\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("______"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("___");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("____");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf(" ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf(" "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf(" "); setcolor(12, 12); printf("____"); setcolor(0, 0); printf(" ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("____"); setcolor(0, 0); printf("     \n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(0, 0); printf(" "); setcolor(12, 12); printf("___"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("___");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("______"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(12, 12); printf("___"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n\n");

	setcolor(15, 0);
}

void player2_win()
{
	// player 2
	printf("\n\n\n\n\n");
	setcolor(0, 0); printf("\t     "); setcolor(s, s); printf("_______"); setcolor(0, 0); printf("  "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("    "); setcolor(s, s); printf("_______"); setcolor(0, 0); printf("  "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("    "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("  "); setcolor(s, s); printf("______");
	setcolor(0, 0); printf("  "); setcolor(s, s); printf("_______"); setcolor(0, 0); printf("   "); setcolor(s, s); printf("______\n");

	setcolor(0, 0); printf("\t     "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("   "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("  "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("    "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("   "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("   "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("  "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("   "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("      "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("   "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("   "); setcolor(0, 0); printf("    "); setcolor(s, s); printf("__\n");

	setcolor(0, 0); printf("\t     "); setcolor(s, s); printf("_______"); setcolor(0, 0); printf("  "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("    "); setcolor(s, s); printf("_______"); setcolor(0, 0); printf("    "); setcolor(s, s); printf("____");
	setcolor(0, 0); printf("    "); setcolor(s, s); printf("____"); setcolor(0, 0); printf("    "); setcolor(s, s); printf("_______");
	setcolor(0, 0); printf("   "); setcolor(s, s); printf("______\n");

	setcolor(0, 0); printf("\t     "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("       "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("    "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("   "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("     "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("     "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("      "); setcolor(s, s); printf("__"); setcolor(0, 0); printf(" "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("     "); setcolor(s, s); printf("__\n");

	setcolor(0, 0); printf("\t     "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("       "); setcolor(s, s); printf("____");
	setcolor(0, 0); printf("  "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("   "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("     "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("     "); setcolor(s, s); printf("______");
	setcolor(0, 0); printf("  "); setcolor(s, s); printf("__"); setcolor(0, 0); printf("  "); setcolor(s, s); printf("__");
	setcolor(0, 0); printf("    "); setcolor(s, s); printf("______\n\n");

	// win!
	setcolor(0, 0); printf("\t\t\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("______"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("___");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("____");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf(" ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf(" "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf(" "); setcolor(12, 12); printf("____"); setcolor(0, 0); printf(" ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("____"); setcolor(0, 0); printf("     \n");

	setcolor(0, 0); printf("\t\t\t"); setcolor(0, 0); printf(" "); setcolor(12, 12); printf("___"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("___");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("______"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(12, 12); printf("___"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n\n");

	setcolor(15, 0);
}

void you_win()
{
	printf("\n\n\n\n\n\n\n\n");
	// you win! 
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("________"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("\t"); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("         "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("______");
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("___"); setcolor(0, 0); printf("     "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("         "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("____");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("\t"); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("         "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf(" "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("     "); setcolor(12, 12); printf("____"); setcolor(0, 0); printf("     "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("\t"); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("         "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("\t"); setcolor(0, 0); printf(" ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("___"); setcolor(0, 0); printf("  ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("     "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf(" ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");

	setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__");
	setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("\t"); setcolor(0, 0); printf("  ");
	setcolor(12, 12); printf("____"); setcolor(0, 0); printf(" "); setcolor(12, 12); printf("____"); setcolor(0, 0); printf("      ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(12, 12); printf("____\n");

	setcolor(0, 0); printf("      "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("      "); setcolor(12, 12); printf("________");
	setcolor(0, 0); printf("  "); setcolor(12, 12); printf("________"); setcolor(0, 0); printf("\t"); setcolor(0, 0); printf("   ");
	setcolor(12, 12); printf("__"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("     ");
	setcolor(12, 12); printf("______"); setcolor(0, 0); printf("  "); setcolor(12, 12); printf("__"); setcolor(0, 0); printf("     ");
	setcolor(12, 12); printf("___"); setcolor(0, 0); printf("   "); setcolor(12, 12); printf("__\n");


	setcolor(15, 0);
}

void you_lose()
{
	printf("\n\n\n\n\n\n\n\n");
	// you lose! 
	setcolor(0, 0); printf(" "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("      "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("  ");
	setcolor(9, 9); printf("________"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("    ");
	setcolor(9, 9); printf("__"); setcolor(0, 0); printf("\t"); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("        ");
	setcolor(9, 9); printf("________"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("________"); setcolor(0, 0); printf("  ");
	setcolor(9, 9); printf("________"); setcolor(0, 0); printf("   "); setcolor(9, 9); printf("__\n");

	setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("   "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("\t"); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("        "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("        "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("         "); setcolor(9, 9); printf("__\n");

	setcolor(0, 0); printf("   "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("\t"); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("        "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("        "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("         "); setcolor(9, 9); printf("__\n");

	setcolor(0, 0); printf("    "); setcolor(9, 9); printf("____"); setcolor(0, 0); printf("     "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("\t"); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("        "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("  "); setcolor(9, 9); printf("________"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("______");
	setcolor(0, 0); printf("     "); setcolor(9, 9); printf("__\n");

	setcolor(0, 0); printf("     "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("      "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("\t"); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("        "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("        "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("         "); setcolor(9, 9); printf("__\n");

	setcolor(0, 0); printf("     "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("      "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("\t"); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("        "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("    "); setcolor(9, 9); printf("__");
	setcolor(0, 0); printf("        "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("__\n");

	setcolor(0, 0); printf("     "); setcolor(9, 9); printf("__"); setcolor(0, 0); printf("      "); setcolor(9, 9); printf("________");
	setcolor(0, 0); printf("  "); setcolor(9, 9); printf("________"); setcolor(0, 0); printf("\t"); setcolor(9, 9); printf("________");
	setcolor(0, 0); printf("  "); setcolor(9, 9); printf("________"); setcolor(0, 0); printf("  "); setcolor(9, 9); printf("________");
	setcolor(0, 0); printf("  "); setcolor(9, 9); printf("________"); setcolor(0, 0); printf("   "); setcolor(9, 9); printf("__\n");
	setcolor(15, 0);
}
