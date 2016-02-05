
#include "egg.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

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
    size_t drop_from = (my_egg->floor_min + (my_egg->floor_max - my_egg->floor_min) / 2);
    egg_drop_from_floor(my_egg->egg, drop_from);
    my_egg->drops++;
    printf("drops (%d) min (%zu) max (%zu) drop_from (%zu)\n", my_egg->drops, my_egg->floor_min, my_egg->floor_max, drop_from);
    if (my_egg->drops > 20) exit(0);
    if (! egg_is_broken(my_egg->egg)){
        my_egg->floor_min = drop_from + 1;
        binary_search(my_egg);
    }
    my_egg->floor_max = drop_from +1;
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
    printf("drops (%d) min (%zu) max (%zu) drop_from (%zu)\n", my_egg->drops, my_egg->floor_min, my_egg->floor_max, my_egg->floor_min);
    if (! egg_is_broken(my_egg->egg)){
        my_egg->floor_min++;
        single_search(my_egg);
    }
    my_egg->floor_max = my_egg->floor_min - 1;
}

/* Function searches for the point an egg breaks using the quadratic algorithm
 * @Param -- egg holder containing the egg to be dropped
 * @Return -- void
 */
void search_two (egg_holder* my_egg){
    if( ! my_egg ){
        return;
    }
    
    int floors = my_egg->floor_max - my_egg->floor_min;
    size_t step = (size_t) ((sqrt(1+(8*floors))-1)/2) + 1;
    size_t next_floor = my_egg->floor_min + step;
    printf("number of floors (%d) step (%zu) \n", floors, step);
    //if(step == 0) step = 1;
    while (next_floor <= my_egg->floor_max){
        egg_drop_from_floor(my_egg->egg, next_floor);
        my_egg->drops++;
        printf("drops (%d) min (%zu) max (%zu) drop_from (%zu)\n", my_egg->drops, my_egg->floor_min, my_egg->floor_max, next_floor);
        if (egg_is_broken(my_egg->egg)){
           my_egg->floor_max = next_floor;
           break;
        }
        my_egg->floor_min = next_floor;
        step = step - 1;
        next_floor += step;
    }
    if (! egg_is_broken(my_egg->egg)){
        search_two(my_egg); // run again on the remaining values
    }
}

/* Function solves the "two egg problem" for given number of floors and eggs 
 * using the fewest number of drops possible
 * @Param floors -- number of floors in building must be > 0
 * @Param eggs -- number of eggs to drop must be > 0
 * @Return 1 on success 0 on failure
 */
int run (int floors, int eggs){
    if ( floors < 0 ){
        fprintf(stderr, "ERROR: buildings can't have 0 floors\n");
        return 0;
    }
    egg_holder* my_egg = malloc(sizeof(egg_holder));
    memset(my_egg, 0, sizeof(egg_holder));
    if (! my_egg){
        return 0;
    }
    my_egg->drops = 0;
    my_egg->floor_max = floors;
    my_egg->floor_min = 1;
    while ( my_egg->floor_max > my_egg->floor_min && eggs){
        my_egg->egg = lay_egg();
        if ( ! my_egg->egg ){
            fprintf( stderr, "ERROR: couldn't allocate space!!");
            return 0;
        }
        if ( eggs > 2){
            binary_search( my_egg );
            printf("binary \n");
        } else if ( eggs == 2){
            search_two( my_egg );
            printf("search tow \n");
        } else {
            single_search( my_egg );
            printf("single \n");
        }
        cook_egg(my_egg->egg);
        eggs--;
        if ( my_egg->floor_max == 0 ){ // something bad happened
            return 0;
        }
    }
    fprintf(stdout, "Max safe Floor: %zu \nNumber of Drops: %d \n", 
            my_egg->floor_max, my_egg->drops);
    free(my_egg);
    return 1;
}
 
 
/* Program execution begins here
 *
 */
int main(int argc, char *argv[]){
    if ( argc != 3 ){
        fprintf(stderr, "ERROR: useage is:   egg_drop   NUMBER_OF_FLOORS      NUMBER_OF_EGGS");
        exit(0);
    }
    long floors = strtol(argv[1], NULL, 10);
    long eggs = strtol(argv[2], NULL, 10);
    printf( "%ld, %ld\n", floors, eggs);
    if (!floors  || !eggs ){
        fprintf(stderr, "ERROR: number of floors and number of eggs must be an integer greater than zero!\n");
        exit(0);
    }
    if (! run(floors, eggs)){
        fprintf(stderr, "ERROR: LIAM stop putting in silly things!!\n");
        exit(0);
    };
    
}