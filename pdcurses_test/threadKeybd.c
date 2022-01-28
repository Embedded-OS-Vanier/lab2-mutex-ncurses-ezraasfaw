/****************************************************************************
*
*
*	Author				Date			Version
*	Ezra-Fikru Asfaw
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

#include "../header/public.h"
#include "../header/ncurses_init.h"
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
static int x = 0;
static int y = 0;
static void* thread_kd(void* threadid);
static pthread_t thread1;
static pthread_mutex_t mutex_xy = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex_print = PTHREAD_MUTEX_INITIALIZER;

//void print(int row, int col, char* str) {
//
//    pthread_mutex_lock(&mutex_print);
//    mvprintw(row, col, str);  // this resource is protected by a mutex
//    pthread_mutex_unlock(&mutex_print);
//
//}

void create_thread_kb(void) {
    pthread_create(&thread1, NULL, thread_kd, NULL);
}

void pthread_join_kb(void) {
    pthread_join(thread1, NULL);
}

void* thread_kd(void* threadid) {
    int temp_x = 0,
        input;
    while (1) {
        input = getch();  // blocking queue 
        temp_x = get_x();
        if (input == 'u') set_x(++temp_x); // increments x
        else if (input == 'd') set_x(--temp_x); // decrements x
        else if (input == 'x') break;
    }
    return NULL;

}
void set_x(int _x) {
    pthread_mutex_lock(&mutex_xy);
    x = _x;// protected global variable
    pthread_mutex_unlock(&mutex_xy);
}

int get_x(void) {
    int temp;
    pthread_mutex_lock(&mutex_xy);
    temp = x;// protected global variable
    pthread_mutex_unlock(&mutex_xy);
    return temp;
}

void set_y(int _y) {
    pthread_mutex_lock(&mutex_xy);
    y = _y;// protected global variable
    pthread_mutex_unlock(&mutex_xy);
}

int get_y(void) {
    int temp;
    pthread_mutex_lock(&mutex_xy);
    temp = y;// protected global variable
    pthread_mutex_unlock(&mutex_xy);
    return temp;
}