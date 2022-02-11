/****************************************************************************
*
*
*	Author				Date			Version
*   Ezra-Fikru Asfaw    1/28/2022        1.0      Worked and completed the menu
* 
*	Ezra-Fikru Asfaw    2/04/2022        2.0      Worked and completed snake 
*                                                 mouvement
*                                                  
*	Ezra-Fikru Asfaw    2/11/2022        3.0      Completed threadDisplay.c
*                                                 Worked on the counter, and
*                                                 blinking the title of the game.
*****************************************************************************/


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <ncurses.h>
#include <sys/ioctl.h>
//#include <sys/time.h>
//#include <libgen.h>
#endif

#include "../laboratory/header/public.h"
#include "../laboratory/header/ncurses_init.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <stdint.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>

#ifdef _WIN32
#define HAVE_STRUCT_TIMESPEC  // for win32 only. Because TIMESPEC is re-defined inside pthread.h
#endif
#include <pthread.h>

/*Globals*/
int cnt;
static void* thread_display(void* threadid);
static pthread_t thread2;
static pthread_mutex_t mutex_print = PTHREAD_MUTEX_INITIALIZER;

void print(int row, int col, char* str) {

    pthread_mutex_lock(&mutex_print);
    mvprintw(row, col, str);  // this resource is protected by a mutex
    pthread_mutex_unlock(&mutex_print);

}

void* thread_display(void* threadid) {
    int timer = 0;
    int cnt = 0;
    int cnt2 = 0;

    //static menu section
    attron(BLUE_WHITE);
    mvprintw(0, 0,"////////////////////////////////////////////////////////////////////////////" );
    mvprintw(1, 0,"                                 Controls                                   ");
    mvprintw(1, 0,"                               Forward(W)                                   ");
    mvprintw(2, 0,"              Left(L)          Backward(B)         Right(R)                 ");
    mvprintw(3, 0,"                                 Exit(X)                                    ");
    mvprintw(6, 0, "////////////////////////////////////////////////////////////////////////////");
    attroff(BLUE_WHITE);

    while (1) {
        //non static menu section
        attron(BLUE_WHITE);
        mvprintw(5, 0, "                                                       Count: %d             ", timer);
        attroff(BLUE_WHITE);

        //displaying snake
        attron(GREEN_WHITE);
        print(get_x(), get_y(), "O");
        attroff(GREEN_WHITE);

        //counter 
        Sleep(10);
        if (cnt++ == 100) {
            timer++;
            cnt = 0;

        }
        //title of the game blink
        if (cnt2++ == 20) {                                                                                     
            attron(RED_WHITE);
            mvprintw(4, 0, "                               Snake Game                                   ");
            attroff(RED_WHITE);
        }
        if (cnt2 == 40) {
            attron(RED_WHITE);
            mvprintw(4, 0, "                                                                            ");
            attroff(RED_WHITE);
            cnt2 = 0;
        }

        refresh();

    }
    return NULL;
}

void create_thread_display(void) {
    pthread_create(&thread2, NULL, thread_display, NULL);
}

void pthread_join_display(void) {
    pthread_join(thread2, NULL);
}