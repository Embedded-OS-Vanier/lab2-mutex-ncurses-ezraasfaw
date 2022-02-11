/****************************************************************************
*
*
*	Author				Date			Version
*   Ezra-Fikru Asfaw    1/28/2022        1.0      Worked and completed the ability.
*                                                 to retive the key input to move the 
*                                                 snake.
*
*	Ezra-Fikru Asfaw    2/04/2022        2.0      Worked and completed the ability to send
*                                                 the keyboard input to threadKeybd.c.
*
*	Ezra-Fikru Asfaw    2/11/2022        3.0      Completed threadKeybd.c
*                                                 Worked and completed the borders.
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
static int x = 7;
static int y = 0;
static void* thread_kd(void* threadid);
static pthread_t thread1;
static pthread_mutex_t mutex_xy = PTHREAD_MUTEX_INITIALIZER;





void* thread_kd(void* threadid) {     //retive keyboard input
    int temp_x = 0, temp_y = 0, input;
    while (1) {
        input = getch();  // blocking queue 
        Sleep(20);
        temp_x = get_x();
        temp_y = get_y();
        if (input == 's') set_x(++temp_x); // increments x
        else if (input == 'w') set_x(--temp_x); // decrements x
        else if (input == 'd') set_y(++temp_y); // increments y
        else if (input == 'a') set_y(--temp_y); // decrements y
        else if (input == 'x') exit(1);
    }
    return NULL;

}
void set_x(int _x) { 
    pthread_mutex_lock(&mutex_xy);
    x = _x;// protected global variable
    if (x < 7) {    //x axis starting borders
        x = 7;
    }
    if (x > 29) {
        x = 29;
    }
    pthread_mutex_unlock(&mutex_xy);
}

int get_x(void) {    //x axis ending borders
    int Xtemp;
    pthread_mutex_lock(&mutex_xy);
    Xtemp = x;// protected global variable
    pthread_mutex_unlock(&mutex_xy);
    return Xtemp;
}

void set_y(int _y) {
    pthread_mutex_lock(&mutex_xy);
    y = _y;// protected global variable
    if (y <= 0) {    //y axis starting borders
        y = 0;
    }
    if (y >= 75) {
        y = 75;
    }
    pthread_mutex_unlock(&mutex_xy);
}

int get_y(void) {    //y axis ending borders
    int Ytemp;
    pthread_mutex_lock(&mutex_xy);
    Ytemp = y;// protected global variable
    pthread_mutex_unlock(&mutex_xy);
    return Ytemp;
}


void create_thread_kb(void) {
    pthread_create(&thread1, NULL, thread_kd, NULL);
}

void pthread_join_kb(void) {
    pthread_join(thread1, NULL);
}
