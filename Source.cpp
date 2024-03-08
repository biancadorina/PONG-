#include<stdio.h>
#include <Windows.h>
#include <WinBase.h>
#include <conio.h>
#include <time.h>
#include<string.h>

#define CHR_TOP_LEFT 218
#define CHR_DOWN_LEFT 192
#define CHR_TOP_RIGHT 191
#define CHR_DOWN_RIGHT 217
#define CHR_VERTICAL_BORDER 179
#define CHR_HORIZONTAL_BORDER 196
#define CHR_NET_BORDER 220
#define CHR_PADDLE 220
#define CHR_BALL 233

int l = 25;
int L = 2 * l;
int total_width = L * 2;
char p1[4], p2[4];
char v[100][100];
int l_paddle = l / 2;
int p1_x = 0;
int p2_x = 0;
int ball_x;
int ball_y;
int ball_direction_x = 0;
int ball_direction_y = 0;
int player1 = 0;
int player2 = 0;
int speed = 4000;
char play[100][100];
char lvl[100][100];
char pong[] = "  P O N G - G A M E";
char hard[] = { ' ',' ','  ','H','a','r','d',' ','-',' ','p','r','e','s','s',' ','H', NULL };
char easy[] = { ' ',' ','E','a','s','y',' ','-',' ','p','r','e','s','s',' ','E', NULL };
char starts1[] = { 'S','T','A','R','T', NULL };
char start1[] = { 'S','i','n','g','l','e','p','l','a','y','e','r', ' ','-',' ','p','r','e','s','s',' ','1', NULL };
char start2[] = { 'M','u','l','t','i','p','l','a','y','e','r',' ', ' ','-',' ','p','r','e','s','s',' ','2', NULL };
char exitt[] = { 'E','X','I','T','-','p','r','e','s','s',' ','3', NULL };
char w1[] = { 'P','1','-','w','i','n','n','e','r', NULL };
char w2[] = { 'P','2','-','w','i','n','n','e','r', NULL };
bool pause = false;
bool boot = false;
int pos1;
int pos2;
int nr_serves = 0;
void print_board();
void choose2();
void go_to_game();

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
void clean() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

int find_position(int a) {    //returneaza pozitia din mijlocul paletei in functie de miscarea acesteia
	return (a - l_paddle / 2);
}

void hard_function() {				//injumatateste lungimea paletei
	l_paddle = l_paddle / 2;

}

void paddle1()
{
	int middle = L / 2;
	int new_x;
	for (int i = 0; i < l_paddle; i++) {
		new_x = middle - l_paddle / 2 + i + p1_x;  //pozitionarea paletei pe mijloc cu ajutorul "middle" cand incepe jocul
		v[1][new_x] = CHR_PADDLE;
	}
	pos1 = find_position(new_x);
}

void limits_p1_left()
{
	if (L / 2 - l_paddle / 2 + p1_x == 1)   //paleta ramane in chenar,cand ajunge pe pozitia barei aceasta nu mai continua miscarea
	{
		p1_x = p1_x;
	}
	else {
		if (!pause) {
			p1_x -= 1;       //pozitioneaza paleta spre stanga
		}
	}
}

void limits_p1_right()
{
	if (l_paddle < l / 2) {
		if (L / 2 + p1_x + l_paddle / 2 == L - 2)  //paleta ramane in chenar,cand ajunge pe pozitia barei aceasta nu mai continua miscarea
		{
			p1_x = p1_x;
		}
		else {
			if (!pause) {
				p1_x += 1;
			}
		}
	}
	else {
		if (L / 2 + p1_x + l_paddle / 2 == L - 1)  //paleta ramane in chenar,cand ajunge pe pozitia barei aceasta nu mai continua miscarea
		{
			p1_x = p1_x;
		}
		else {
			if (!pause) {
				p1_x += 1;
			}
		}
	}
}

void paddle2()
{
	int middle = L / 2;
	int new_x;
	for (int i = 0; i < l_paddle; i++) {
		new_x = middle - l_paddle / 2 + i + p2_x;
		v[l - 2][new_x] = CHR_PADDLE;
	}
	pos2 = find_position(new_x);
}

void limits_p2_left()
{

	if (L / 2 - l_paddle / 2 + p2_x == 1) {
		p2_x = p2_x;
	}
	else {
		if (!pause) {
			p2_x -= 1;
		}
	}

}

void limits_p2_right()
{
	if (l_paddle < l / 2) {
		if (L / 2 + p2_x + l_paddle / 2 == L - 2) {
			p2_x = p2_x;
		}
		else {
			if (!pause) {
				p2_x += 1;
			}
		}
	}
	else {
		if (L / 2 + p2_x + l_paddle / 2 == L - 1) {
			p2_x = p2_x;
		}
		else {
			if (!pause) {
				p2_x += 1;
			}
		}
	}
}

void auto_paddle()
{

	if (ball_direction_x == -1) {       //miscarea automata a paletei in functie de directia bilei
		limits_p1_left();
	}

	if (ball_direction_x == 1) {
		limits_p1_right();
	}
}



void generate_ball_direction()		//genereaza directia bilei oblica, aleatorie(spre dreapta sau pe stanga)
{
	bool top = rand() % 2;
	bool left = rand() % 2;

	if (top) {
		ball_direction_y = -1;
	}
	else {
		ball_direction_y = 1;
	}

	if (left) {
		ball_direction_x = -1;
	}
	else {
		ball_direction_x = 1;
	}
}

void generate_ball()	//genereaza bila dintr-o pozitie random de pe fileu
{
	srand(time(0));
	ball_x = 2 + rand() % ((L / 2) - 2);
	ball_y = l / 2 - 1;

	v[ball_y][ball_x] = CHR_BALL;

	generate_ball_direction();
}

void set_score()              //afiseaza scorul pentru jucatori in exteriorul chenarului
{
	v[1][L] = ' ';
	v[1][L + 1] = 'p';
	v[1][L + 2] = '1';
	v[l - 2][L] = ' ';
	v[l - 2][L + 1] = 'p';
	v[l - 2][L + 2] = '2';

	v[l / 2 - 1][L] = 'p';
	v[l / 2 - 1][L + 1] = '1';
	v[l / 2 - 1][L + 2] = ' ';
	v[l / 2 - 1][L + 3] = '|';
	v[l / 2 - 1][L + 4] = ' ';
	v[l / 2 - 1][L + 5] = 'p';
	v[l / 2 - 1][L + 6] = '2';

	v[l / 2][L + 1] = ' ';
	v[l / 2][L + 3] = ' ';
	v[l / 2][L + 4] = ' ';
	v[l / 2][L + 5] = ' ';

	v[l / 2][L + 2] = player1;
	v[l / 2][L + 6] = player2;

	v[l / 2][L + 7] = ' ';
	v[l / 2][L + 8] = ' ';
	v[l / 2][L + 9] = ' ';
	v[l / 2][L + 10] = ' ';

}

void serve_p1() {			// mingea este servita din mijlocul paletei
	paddle1();
	ball_y = 3;
	ball_x = pos1;
	v[ball_y][ball_x] = CHR_BALL;

	generate_ball_direction();
}

void serve_p2() {
	paddle2();
	ball_y = l - 3;
	ball_x = pos2;
	v[ball_y][ball_x] = CHR_BALL;

	generate_ball_direction();
}

void player_serve()			//face ca fiecare player sa serveasca de doua ori consecutiv
{
	if (nr_serves % 4 < 2) {
		serve_p1();
	}
	else {
		serve_p2();
	}
	nr_serves++;
}

void clean_menu() {
	int k1 = 0;

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < L; j++) {
			v[i][j] = ' ';
			v[0][j] = v[l - 1][j] = CHR_HORIZONTAL_BORDER;
		}
		v[i][L - 1] = v[i][0] = CHR_VERTICAL_BORDER;
	}
	v[0][0] = CHR_TOP_LEFT;
	v[l - 1][0] = CHR_DOWN_LEFT;
	v[0][L - 1] = CHR_TOP_RIGHT;
	v[l - 1][L - 1] = CHR_DOWN_RIGHT;

	if (player1 == 11) //implementarea mesajului "player1=winner"
	{
		while (k1 < strlen(w1)) {
			v[l / 4][(L / 2) - (strlen(w1) / 2) + k1] = w1[k1];
			k1++;
		}
	}

	int  k2 = 0;
	if (player2 == 11)		//implementare mesajului "player1=winner"
	{
		while (k2 < strlen(w2)) {
			v[l / 4][(L / 2) - (strlen(w2) / 2) + k2] = w2[k2];
			k2++;
		}
	}

	//implementarea meniului final

	int k3 = 0;
	while (k3 < strlen(start1)) {
		v[2 * (l / 4)][(L / 2) - (strlen(start1) / 2) + k3] = start1[k3];
		k3++;
	}

	int k4 = 0;
	while (k4 < strlen(start2)) {
		v[2 * (l / 4) + 2][(L / 2) - (strlen(start2) / 2) + k4] = start2[k4];
		k4++;
	}

	int k5 = 0;
	while (k5 < strlen(exitt)) {
		v[2 * (l / 4) + 4][(L / 2) - (strlen(exitt) / 2) + k5] = exitt[k5];
		k5++;
	}

	print_board();
}

bool game_over() {
	if (player1 == 11 || player2 == 11)    //se verifica daca jocul a fost pierdut 
	{
		clean_menu();
		player1 = player2 = 0;      //face ca scorului sa inceapa de la 0 de fiecare data cand incepe jocul
		return true;
	}
	if (ball_y == 1) {        //tine scorul pentru player2
		player2++;
		player_serve();
	}
	if (ball_y == l - 2) {       //tine scorul pentru player2
		player1++;
		player_serve();
	}

	set_score();

	return false;
}

void bouncing()      //face bila sa ricoseze cand loveste barele verticale si de palete paletele 
{
	if (ball_x == 1) {
		ball_direction_x = 1;
	}

	if (ball_x == L - 2) {
		ball_direction_x = -1;
	}

	for (int i = 0; i < l_paddle + 2; i++) {
		int new_x = L / 2 + i + p1_x - l_paddle / 2 - 1;
		if (ball_x == new_x && ball_y == 2) {
			ball_direction_y = 1;
		}
	}

	for (int i = 0; i < l_paddle + 2; i++) {
		int new_x = L / 2 + i + p2_x - l_paddle / 2 - 1;
		if (ball_x == new_x && ball_y == l - 3) {
			ball_direction_y = -1;
		}
	}
}

void board() {         //matricea pentru chenarul jocului

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < L; j++) {
			v[i][j] = ' ';
		}

		for (int i = 0; i < l; i++) {
			v[i][L - 1] = v[i][0] = CHR_VERTICAL_BORDER;
		}

		for (int j = 0; j < L; j++) {
			v[0][j] = v[l - 1][j] = CHR_HORIZONTAL_BORDER;
			v[(l / 2) - 1][j] = CHR_NET_BORDER;
		}
	}

	v[(l / 2) - 1][0] = CHR_VERTICAL_BORDER;
	v[(l / 2) - 1][L - 1] = CHR_VERTICAL_BORDER;
	v[0][0] = CHR_TOP_LEFT;
	v[l - 1][0] = CHR_DOWN_LEFT;
	v[0][L - 1] = CHR_TOP_RIGHT;
	v[l - 1][L - 1] = CHR_DOWN_RIGHT;

	player_serve();
}

void print_board() {      //afisarea matricei jocului
	clean();
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < total_width; j++) {
			if (i == l / 2 && (j == L + 2 || j == L + 6)) {
				printf("%d", v[i][j]);
			}
			else {
				printf("%c", v[i][j]);
			}
		}
		printf("\n");
	}
}

void moving_ball() {           //miscarea bilei in functie e directie
	ball_x += ball_direction_x;
	ball_y += ball_direction_y;

	v[ball_y][ball_x] = CHR_BALL;

	bouncing();
}

void initalize_game() {
	paddle1();
	paddle2();

	if (!pause) {             //"inghetarea" bilei in cazul pauzei
		moving_ball();
	}
}

void clean_board() {
	if (pause == false) {
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < L; j++) {
				if (i == 0 || j == 0 || i == l - 1 || j == L - 1) {
					v[i][j] = v[i][j];
				}
				else {
					if (i == (l / 2) - 1) {
						v[i][j] = CHR_NET_BORDER;
					}
					else {
						v[i][j] = ' ';
					}
				}
			}
		}
	}

}

void moving_paddle()		//face ca paletele sa se miste prin apasarea 'a' sau 'd' pentru paleta de sus si pe sageti pentru cea de jos
{
	if (boot) {            //daca variabila boot este adevarata, se va juca cu computerul
		auto_paddle();
	}

	char tasta;
	if (_kbhit()) {
		tasta = _getch();
		switch (tasta) {
		case 'a':
			if (!boot) {
				limits_p1_left();
			}
			break;
		case'd':
			if (!boot) {
				limits_p1_right();
			}
			break;
		case 75:
			limits_p2_left();
			break;
		case 77:
			limits_p2_right();
			break;
		case 32:
			if (pause) {              //daca este apasata tasta space se va schimba valoarea variabilei "pause" pentru a pune pauza
				pause = false;
			}
			else {
				pause = true;
			}
			break;
		}
	}
}

void start()			//porneste jocul 
{
	player1 = 0;
	player2 = 0;
	board();
	while (!game_over()) {   //se redeseneaza matricea jocului (fiind dat efectul de miscare) atat timp cat  jocul nu e pierdut 
		clean_board();
		initalize_game();
		for (int i = 0; i < speed; i++)
		{
			moving_paddle();
			Sleep(0.5);
		}
		print_board();
	}
}

void menu() {           //initializarea matricei celui de-al doillea meniu


	for (int i = 0; i < l; i++) {
		for (int j = 0; j < L; j++) {
			play[i][j] = ' ';
			play[0][j] = play[l - 1][j] = CHR_HORIZONTAL_BORDER;
		}
		play[i][L - 1] = play[i][0] = CHR_VERTICAL_BORDER;
	}

	for (int i = l / 5; i < 2 * (l / 5); i++) {
		play[i][(L / 4)] = CHR_VERTICAL_BORDER;
		play[i][(L / 4) + 2 * (L / 4)] = CHR_VERTICAL_BORDER;
	}

	for (int i = 3 * (l / 5); i < 4 * (l / 5); i++) {
		play[i][(L / 4)] = CHR_VERTICAL_BORDER;
		play[i][(L / 4) + 2 * (L / 4)] = CHR_VERTICAL_BORDER;
	}

	int k1 = 0, s1 = 0, s2 = 0;
	for (int j = (L / 4) + 1; j < (L / 4) + 2 * (L / 4); j++) {
		play[l / 5][j] = CHR_HORIZONTAL_BORDER;
		play[2 * (l / 5)][j] = CHR_HORIZONTAL_BORDER;

		if (k1 < strlen(starts1)) {
			play[(l / 5) + 1][j] = starts1[k1];
			k1++;
		}
		if (s1 < strlen(start1)) {
			play[(l / 5) + 2][j] = start1[s1];
			s1++;
		}
		if (s2 < strlen(start2)) {
			play[(l / 5) + 3][j] = start2[s2];
			s2++;
		}
	}

	int k2 = 0;
	for (int j = (L / 4) + 1; j < (L / 4) + 2 * (L / 4); j++) {
		play[3 * (l / 5)][j] = CHR_HORIZONTAL_BORDER;
		play[4 * (l / 5)][j] = CHR_HORIZONTAL_BORDER;

		if (k2 < 12) {
			play[3 * (l / 5) + 2][j] = exitt[k2];
			k2++;
		}
	}
	play[l / 5][L / 4] = CHR_TOP_LEFT;
	play[l / 5][(L / 4) + 2 * (L / 4)] = CHR_TOP_RIGHT;
	play[2 * (l / 5)][L / 4] = CHR_DOWN_LEFT;
	play[2 * (l / 5)][(L / 4) + 2 * (L / 4)] = CHR_DOWN_RIGHT;
	play[3 * (l / 5)][L / 4] = CHR_TOP_LEFT;
	play[3 * (l / 5)][(L / 4) + 2 * (L / 4)] = CHR_TOP_RIGHT;
	play[4 * (l / 5)][L / 4] = CHR_DOWN_LEFT;
	play[4 * (l / 5)][(L / 4) + 2 * (L / 4)] = CHR_DOWN_RIGHT;
	play[(l / 2) - 1][0] = CHR_VERTICAL_BORDER;
	play[(l / 2) - 1][L - 1] = CHR_VERTICAL_BORDER;
	play[0][0] = CHR_TOP_LEFT;
	play[l - 1][0] = CHR_DOWN_LEFT;
	play[0][L - 1] = CHR_TOP_RIGHT;
	play[l - 1][L - 1] = CHR_DOWN_RIGHT;
}



void print_menu() {     //afisarea celui de-al doilea meniu
	clean();
	menu();
	choose2();

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < L; j++) {
			printf("%c", play[i][j]);
		}
		printf("\n");
	}
}

void level() {         //initializeaza matricea primului meniu
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < L; j++) {
			lvl[i][j] = ' ';
			lvl[0][j] = lvl[l - 1][j] = CHR_HORIZONTAL_BORDER;
		}
		lvl[i][L - 1] = lvl[i][0] = CHR_VERTICAL_BORDER;
	}

	for (int i = l / 5; i < 2 * (l / 5); i++) {
		lvl[i][(L / 4)] = CHR_VERTICAL_BORDER;
		lvl[i][(L / 4) + 2 * (L / 4)] = CHR_VERTICAL_BORDER;
	}

	for (int i = 3 * (l / 5); i < 4 * (l / 5); i++) {
		lvl[i][(L / 4)] = CHR_VERTICAL_BORDER;
		lvl[i][(L / 4) + 2 * (L / 4)] = CHR_VERTICAL_BORDER;
	}

	int k1 = 0, s1 = 0;
	for (int j = (L / 4) + 1; j < (L / 4) + 2 * (L / 4); j++) {
		lvl[l / 5][j] = CHR_HORIZONTAL_BORDER;
		lvl[2 * (l / 5)][j] = CHR_HORIZONTAL_BORDER;

		if (k1 < strlen(pong)) {
			lvl[(l / 5) / 2][j] = pong[k1];
			k1++;
		}
		if (s1 < strlen(easy)) {
			lvl[(l / 5) + 2][j] = easy[s1];
			s1++;
		}

	}


	int k2 = 0;
	for (int j = (L / 4) + 1; j < (L / 4) + 2 * (L / 4); j++) {
		lvl[3 * (l / 5)][j] = CHR_HORIZONTAL_BORDER;
		lvl[4 * (l / 5)][j] = CHR_HORIZONTAL_BORDER;

		if (k2 < strlen(hard)) {
			lvl[3 * (l / 5) + 2][j] = hard[k2];
			k2++;
		}
	}



	lvl[l / 5][L / 4] = CHR_TOP_LEFT;
	lvl[l / 5][(L / 4) + 2 * (L / 4)] = CHR_TOP_RIGHT;
	lvl[2 * (l / 5)][L / 4] = CHR_DOWN_LEFT;
	lvl[2 * (l / 5)][(L / 4) + 2 * (L / 4)] = CHR_DOWN_RIGHT;
	lvl[3 * (l / 5)][L / 4] = CHR_TOP_LEFT;
	lvl[3 * (l / 5)][(L / 4) + 2 * (L / 4)] = CHR_TOP_RIGHT;
	lvl[4 * (l / 5)][L / 4] = CHR_DOWN_LEFT;
	lvl[4 * (l / 5)][(L / 4) + 2 * (L / 4)] = CHR_DOWN_RIGHT;
	lvl[(l / 2) - 1][0] = CHR_VERTICAL_BORDER;
	lvl[(l / 2) - 1][L - 1] = CHR_VERTICAL_BORDER;
	lvl[0][0] = CHR_TOP_LEFT;
	lvl[l - 1][0] = CHR_DOWN_LEFT;
	lvl[0][L - 1] = CHR_TOP_RIGHT;
	lvl[l - 1][L - 1] = CHR_DOWN_RIGHT;
}

void print_level()		//afiseaza  matricea cu  primul meniu
{
	level();
	for (int i = 0; i < l; i++) {
		for (int j = 0; j < L; j++) {
			printf("%c", lvl[i][j]);
		}
		printf("\n");
	}
}

void clean_level() {     //pune spatii in maatricea primului meniu
	int k1 = 0;

	for (int i = 0; i < l; i++) {
		for (int j = 0; j < L; j++) {
			play[i][j] = ' ';
			play[0][j] = v[l - 1][j] = CHR_HORIZONTAL_BORDER;
		}
		play[i][L - 1] = play[i][0] = CHR_VERTICAL_BORDER;
	}
	play[0][0] = CHR_TOP_LEFT;
	play[l - 1][0] = CHR_DOWN_LEFT;
	play[0][L - 1] = CHR_TOP_RIGHT;
	play[l - 1][L - 1] = CHR_DOWN_RIGHT;
	print_menu();
}

void choose2() {		//alegerea numarului de jucatori
	menu();
	char press;
	if (_kbhit()) {
		press = _getch();
		switch (press) {
		case '2':
			boot = false;
			start();
			break;
		case '1':
			boot = true;
			start();
			break;
		case'3':
			exit(1);
			break;
		}
	}
}

void choose()     //modalitatea de a alege nivelul de dificultate 
{
	level();
	char press;
	if (_kbhit()) {
		press = _getch();
		switch (press) {
		case 'h':
			hard_function();
			clean_level();
			go_to_game();

			break;
		case'e':
			clean_level();
			go_to_game();
			break;
		}

	}
}

void go_to_game() {      //prin apasarea tastei in functie de alegere conduce la inceperea jocului
	hidecursor();
	print_menu();

	while (true)
	{
		choose2();
	}
}

void main() {             ////prin apasarea tastei in functie de alegere conduce la urmatorul meniu
	hidecursor();
	print_level();

	while (true)
	{
		choose();
	}
}