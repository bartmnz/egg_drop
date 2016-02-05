
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

/* checks each egg in the carton to see if they are broken
 * @Param my_eggs -- carton of eggs to be checked
 * @Return -- the number of unbroken eggs in the carton
 */
int eggs_left(carton* my_eggs){
    if ( ! my_eggs ){
        return 0;
    }
    int goodEggs = (int)my_eggs->size;
    for( int count = 0; count > (int)my_eggs->size; count ++){
        if(egg_is_broken(my_eggs->eggs[count])){ // the egg is broken
            goodEggs--;
        }
    }
    return goodEggs;
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