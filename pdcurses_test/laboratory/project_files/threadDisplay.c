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
static void* thread_display(void* threadid);
static pthread_t thread2;
static pthread_mutex_t mutex_print = PTHREAD_MUTEX_INITIALIZER;

void print(int row, int col, char* str) {

    pthread_mutex_lock(&mutex_print);
    mvprintw(row, col, str);  // this resource is protected by a mutex
    pthread_mutex_unlock(&mutex_print);

}

void create_thread_display(void) {
    pthread_create(&thread2, NULL, thread_display, NULL);
}

void pthread_join_display(void) {
    pthread_join(thread2, NULL);
}