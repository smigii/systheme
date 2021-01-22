//
// Created by smigii on 2021-01-21.
//

#ifndef SYSTHEME_UI_H
#define SYSTHEME_UI_H

#include <curses.h>
#include <menu.h>
#include <panel.h>

// Main driver for the ncurses ui.
void ui(){
	// Curses init
	initscr();
	curs_set(0);
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_RED);

	int XMAX, YMAX;
	getmaxyx(stdscr, YMAX, XMAX);

	// =============================== //

	getch();

	// Finito
	endwin();
}

#endif //SYSTHEME_UI_H
