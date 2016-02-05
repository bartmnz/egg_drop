
#include "egg.h"
#include <stdio.h>
/*TODO
 *
 */
void run(int floors, int eggs){
    if ( floors < 0 || eggs < 0){
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