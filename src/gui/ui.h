//
// Created by smigii on 2021-01-21.
//

#ifndef SYSTHEME_UI_H
#define SYSTHEME_UI_H

#include <string>

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
	keypad(stdscr, TRUE);

	int XMAX, YMAX;
	getmaxyx(stdscr, YMAX, XMAX);

	// =============================== //

	std::vector<std::string> choices {"Create", "Edit", "Apply", "Delete"};

	ITEM** my_items = (ITEM **)calloc(choices.size() + 1, sizeof(ITEM *));
	for(int i = 0; i < choices.size(); ++i)
		my_items[i] = new_item(choices.at(i).c_str(), "");
	my_items[choices.size()] = (ITEM *)NULL;

	MENU* menu_home = new_menu((ITEM **)my_items);
	mvprintw(LINES - 2, 0, "F1 to Exit");
	post_menu(menu_home);
	refresh();

	int c;
	int x;
	while((c = getch()) != KEY_F(1)){
		switch(c){
			case KEY_DOWN:
				menu_driver(menu_home, REQ_DOWN_ITEM);
				x = item_index(current_item(menu_home));
				mvprintw(10, 10, "%d", x);
				break;
			case KEY_UP:
				menu_driver(menu_home, REQ_UP_ITEM);
				x = item_index(current_item(menu_home));
				mvprintw(10, 10, "%d", x);
				break;
		}
	}

	free_item(my_items[0]);
	free_item(my_items[1]);
	free_menu(menu_home);

//	getch();

	// Finito
	endwin();
}

#endif //SYSTHEME_UI_H
