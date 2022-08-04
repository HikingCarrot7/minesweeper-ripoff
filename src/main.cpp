#include "game/minesweeper.hpp"
#include "view/ms_view.hpp"

int main(void) {
  Minesweeper ms;
  MsView view = MsView(ms);
  view.renderGame();

#if 0
    std::vector<int> items(5);

    for (size_t i = 0; i < items.size(); i++) {
        items[i] = 50;
    }

    size_t highlight = 0;

    initscr();
    noecho();
    cbreak();

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);
    WINDOW* window = newwin(maxY, maxX, 0, 0);
    box(window, 0, 0);

    while (1) {
        for (size_t i = 0; i < items.size(); i++) {
            if (i == highlight) {
                wattron(window, A_REVERSE);
            }

            std::string str = std::to_string(items[i]);
            mvwprintw(window, 1, 1 + str.length() * i, str.c_str());
            wattroff(window, A_REVERSE);
        }

        wgetch(window);
    }

    endwin();

    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);

    WINDOW* win = newwin(maxY, maxX, 0, 0);
    box(win, 0, 0);
    wrefresh(win);
    keypad(win, true);

    std::string choices[3] = {"Walk", "Jog", "Run"};

    int choice;
    int highlight = 0;

    while (1) {
        for (int i = 0; i < 3; i++) {
            if (i == highlight) {
                wattron(win, A_REVERSE);
            }

            mvwprintw(win, i + 1, 1, choices[i].c_str());
            wattroff(win, A_REVERSE);
        }

        choice = wgetch(win);

        switch (choice) {
            case KEY_UP:
                highlight = std::max(highlight - 1, 0);
                break;
            case KEY_DOWN:
                highlight = std::min(highlight + 1, 2);
                break;
            default:
                break;
        }

        if (choice == 10) break;
    }

    getch();
    endwin();
#endif
#if 0
    initscr();
    cbreak();
    noecho();

    WINDOW* win = newwin(10, 20, 1, 1);
    refresh();

    start_color();
    init_pair(1, COLOR_CYAN, COLOR_WHITE);

    mvwprintw(win, 1, 1, "Some string...");
    wrefresh(win);

    int left, right, top, bottom, tlc, trc, blc, brc;

    left = right = (int)'$';
    top = bottom = (int)'@';
    tlc = trc = (int)'T';
    blc = brc = (int)'B';

    wborder(win, left, right, top, bottom, tlc, trc, blc, brc);
    wrefresh(win);

    wattron(win, COLOR_PAIR(1));
    wprintw(win, "This is some text");
    wattroff(win, COLOR_PAIR(1));

#if 0
    if (has_colors()) {
        wprintw(win, "Has colors...");
    }

    if (can_change_color()) {
        wprintw(win, "Can change colors");
    }
#endif

    int y, x, maxY, maxX;

    getyx(win, y, x);
    getmaxyx(win, maxY, maxX);

    wprintw(win, "%d %d ", y, x);
    wprintw(win, "%d %d ", maxY, maxX);
    wrefresh(win);

    getch();
    getch();

    endwin();

#endif
}
