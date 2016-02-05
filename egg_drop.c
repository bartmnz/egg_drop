
#include "egg.h"
#include <stdio.h>
typedef struct{
    size_t size;
    egg* eggs[];
} carton;

/* creates a new carton of eggs.
 * @Param num -- number of eggs to be in carton.
 * @Return -- a newly malloc'd carton of eggs (also malloc'd);
 */
carton *make_carton(int num){
    if ( num < 1){
        return NULL;
    }
    carton* my = malloc(num*sizeof(carton*));
    my->size = num;
    while( num > 0){
        my->eggs[num-1] = lay_egg();
        num--;
    }
    return my;
}

/*TODO
 *
 */
void run(int floors, carton* eggs){
    if ( floors < 0 || ! eggs){
        return;
    }
}
 
 
/* Program execution begins here
 *
 */
int main(int argc, char *argv[]){
    if ( argc != 3 ){
        fprintf(stderr, "ERROR: useage is:   egg_drop   NUMBER_OF_FLOORS      NUMBER_OF_EGGS");
        exit(0);
    }
    int floors, eggs;
    if (!(floors = strtol(argv[0], NULL, 10)) || (eggs = strtol(argv[1], NULL, 10)) ){
        fprintf(stderr, "ERROR: number of floors and number of eggs must be an integer greater than zero!");
        exit(0);
    }
    carton* my_eggs = make_carton(eggs);
    run(floors, my_eggs);
    
}