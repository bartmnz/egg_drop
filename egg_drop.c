
#include "egg.h"
#include <stdio.h>

typedef struct{
    int drops;
    size_t floor_max;
    size_t floor_min;
    egg* egg;
}egg_holder;


/* Function searches for the point an egg breaks using binary search
 * @Param -- egg holder containing the egg to be dropped
 * @Return -- void
 */
void binary_search (egg_holder* my_egg ){
    if ( ! my_egg ){
        return;
    } 
    size_t drop_from = (my_egg->floor_min + (my_egg->floor_max - my_egg->floor_min)) / 2;
    egg_drop_from_floor(my_egg->egg, drop_from);
    my_egg->drops++;
    
    if (! egg_is_broken(my_egg->egg)){
        my_egg->floor_min = drop_from + 1;
        binary_search(my_egg);
    }
    my_egg->floor_max = drop_from;
}

/* Function searches for the point an egg breaks by traversing the range one step at a time
 * @Param -- egg holder containing the egg to be dropped
 * @Return -- void
 */
void single_search (egg_holder* my_egg ){
    if ( ! my_egg ){
        return;
    }
    
    egg_drop_from_floor(my_egg->egg, my_egg->floor_min);
    my_egg->drops++;
    if (! egg_is_broken(my_egg->egg)){
        my_egg->floor_min++;
        single_search(my_egg);
    }
    my_egg->floor_max = my_egg->floor_min;
}

/*TODO
 *
 */
void run(int floors, int eggs){
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
    run(floors, eggs);
    
}