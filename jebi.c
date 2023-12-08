#include "jjuggumi.h"
#include "canvas.h"
#include "keyin.h"
#include <stdio.h>
#include <Windows.h>
#include <string.h>

void player_move(key_t key);
void draw();
void jebi();
void jedi_setting();
void choice(int, int);
void restart(int);
void winner();
void turn();

char Mark[PLAYER_MAX];  // 각 플레이어 위치, 이동 주기
int player_num;
int c;
int g, b;
int l;
int round;
int position[PLAYER_MAX] = { 0 };
int player;

void draw(void) {
	gotoxy(2, 2);
	for (int i = 0; i < n_alive; i++) {
		printf("%c", Mark[i]);
	}
}

void jebi_setting() {
	Mark[1] = '@';
	for (int i = 1; i < n_alive; i++) {
		Mark[i] = '?';
	}
	int s = randint(0, n_alive - 1);
	map_init(10, n_alive * 2 + 3);
	system("cls");
	printf("round %d", round);
	display();
}

void player_move(key_t key, int j) {
	int dir;
	switch (key) {
	case K_LEFT: dir = -1; break;
	case K_RIGHT: dir = -1; break;
	case k_SPACE: dir = 0; break;
	default: return;

		if (dir == 0) {
			choose(g, b);
			return;
		}
		else if (l + dir < 0 || l + dir > n_alive - 1) {
			return;
		}
		if (Mark[l + dir] == ' ') {
			while (1) {
				if (dir > 0) {
					for (int i = l; i < n_player; i++) {
						if (Mark[i] == '?') {
							Mark[i] = '@';
							Mark[l] = '?';
							draw_jebi();
							l = i;
							return;
						}
					}
					c += 1;
				}
				else if (dir < 0) {
					for (int i = l; i >= 0; i--) {
						if (Mark[i] == '?') {
							Mark[i] = '@';
							Mark[l] = '?';
							draw_jebi();
							l = i;
							return;
						}
					}
					c += 1;
				}
				if (c == 2) {
					c = 0;
					return;
				}
			}
		}
		Mark[l + dir] = '@';
		Mark[l] = '?';
		l += dir;
		if (Mark[l - dir] == ' ') {
			draw_jebi();
			return;
		}
		draw_jebi();
	}
}

void choice(int w, int p) {
	char str[50];
	player_num += 1;
	if (position == 1) {
		player[p].is_alive = false;
		n_alive -= 1;
	}

}

void turn() {
	gotory(10, 8);
	printf(", turn : player %d", player_num);
}

void restart(int np) {

}

void winner() {
	if (n_alive == 1) {
		for (int i = 0; i < n_player; i++) {
			if (player[i].is_alive == true) {
				win[i] = true;
				break;
			}
		}
		return 1;
	}
	return 0;
}

void jebi() {
	set_jebi();
	while (1) {
		int nt = n_alive;
		if (player[0].is_alive == true && player_num == 0) {
			print_turn(player_num);
			key_t key = get_key();
			if (key == K_QUIT) {
				break;
			}
			else if (key != K_UNDEFINED && player[0].is_alive == true && win[0] == false) {
				player_pick(key, 0);
			}
		}
		else {
			for (int i = 1; i < n_player; i++) {
				print_turn(player_num);
				if (player[i].is_alive == true) {
					while (1) {
						int com_pick = randint(1, 3);
						switch (com_pick) {
						case 1: Sleep(1000); player_pick(K_LEFT, i);  break;
						case 2: Sleep(1000); player_pick(K_RIGHT, i); break;
						case 3: Sleep(1000); player_pick(K_SPACE, i); break;
						default: break;
						}
						Sleep(1000);
						if (com_pick == 3) {
							break;
						}
					}
					if (player[i].is_alive != true) {
						break;
					}
				}
			}
		}
		int w = winneris();
		if (w == 1) {
			break;
		}
		startNewJebi(nt);
	}
}