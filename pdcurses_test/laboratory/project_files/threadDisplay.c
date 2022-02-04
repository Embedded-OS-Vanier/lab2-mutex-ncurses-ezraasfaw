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
    attron(BLUE_WHITE);
    mvprintw(0, 0,"////////////////////////////////////////////////////////////////////////////" );
    mvprintw(1, 0,"//                               Controls                                 //");
    mvprintw(1, 0,"//                             Forward(W)                                 //");
    mvprintw(2, 0,"//            Left(L)          Backward(B)         Right()                //");
    mvprintw(3, 0,"//                               Exit(X)                                  //");
    
   
    while(1){ 
        mvprintw(4, 0,"//                          Count: %d                                 //", timer);
        mvprintw(5, 0,"////////////////////////////////////////////////////////////////////////////");

        
        if (get_x() < 6){
            print(6, get_y(), "O");
            //Sleep(10000);
        }
        else if(get_y() <= 0) {
            print(get_x(), 0, "O");
        }
       /* else if (get_y() >= 20) {
            print(get_x(), 20, "O");
        }
        else if (get_x() >= 20) {
            print(20, get_y(), "O");
        }*/
        else {
            print(get_x(), get_y(), "O");
            //Sleep(1000);
            
        }
        /*timer++;
        Sleep(100);
        refresh;*/
       
    }
    
    return NULL;
}

void create_thread_display(void) {
    pthread_create(&thread2, NULL, thread_display, NULL);
}

void pthread_join_display(void) {
    pthread_join(thread2, NULL);
}