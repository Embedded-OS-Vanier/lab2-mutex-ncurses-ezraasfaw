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




static pthread_mutex_t mutex_print = PTHREAD_MUTEX_INITIALIZER;

void print(int row, int col, char* str) {

    pthread_mutex_lock(&mutex_print);
    mvprintw(row,col,str);  // this resource is protected by a mutex
    pthread_mutex_unlock(&mutex_print);

}

void* thread_kd(void* threadid) {

    while (1) {

        attron(BLUE_WHITE);
        //mvprintw(2, 0, "Good morning!\n");
        print(1, 0, "Good morning!\n");
        attroff(BLUE_WHITE);
        refresh();
        Sleep(1);
    }
    //return NULL;
}
void* thread2(void* threadid) {

    while (1) {

        attron(GREEN_WHITE);
        //mvprintw(2, 0, "Hello World!\n");
        print(2, 0, "Hello World!\n");
        attroff(GREEN_WHITE);
        refresh();
        Sleep(1);
    }
    //return NULL;
}


int main(void){
    init_ncurses();
    
        pthread_t thread1id, thread2id;
        //pthread_create(&thread1id, NULL, thread1, NULL);
        //pthread_create(&thread2id, NULL, thread2, NULL);
        //pthread_join(thread1id, NULL);
        //pthread_join(thread2id, NULL);

        create_thread_kb(&thread1id, NULL, thread1, NULL);
        create_thread_display(&thread1id, NULL, thread2, NULL);
        pthread_join_kb(thread1id, NULL);
        pthread_join_display(thread2id, NULL);

        return 1;

}
///*Globals*/
//static int x = 0; 
//static pthread_mutex_t
//mutex_xy = PTHREAD_MUTEX_INITIALIZER; 
//void* thread_routine1(void* threadid) {
//    int temp_x = 0, 
//        input; 
//    while (1) {
//        input = getch();  // blocking queue 
//        temp_x= get_x();
//        if (input == 'u') set_x(++temp_x); // increments x
//        else if(input == 'd') set_x(--temp_x); // decrements x
//        else if(input == 'x') break;
//    }
//    return NULL;
//
//}void set_x(int _x) {
//    pthread_mutex_lock(&mutex_xy);
//    x = _x;// protected global variable
//    pthread_mutex_unlock(&mutex_xy);
//}
//
//int get_x(void) {
//    int temp;
//    pthread_mutex_lock(&mutex_xy);
//    temp = x;// protected global variable
//    pthread_mutex_unlock(&mutex_xy);
//    return temp;
//}