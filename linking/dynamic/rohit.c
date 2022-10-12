#include "rohit.h"
/**
 * Compile this is gcc -shared -fPIC -o lib<lib_name>.so rohit.c
 * then update export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH
 * then compile main as gcc main.c -L. -lrohit -o main
 * 
 */

void hello(void){

    printf("Hello rohit\n");
}