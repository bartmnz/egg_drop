#include "egg.h"
/*sample code provided as part of assignment used for testing purposes
 *
 */
static const int SECRET_FLOOR_LIMIT = 10;
egg *lay_egg(void){
    egg *e = malloc(sizeof(*e));
    if(e) {
        e->id = SECRET_FLOOR_LIMIT;
    }
    return e;
}

void destroy_egg(egg *e){
    free(e);
}

bool egg_is_broken(egg *e){
    return e->id == 0;
}

void egg_drop_from_floor(egg *e, size_t breakAt){
    if(e &&(size_t)e->id < breakAt) { 
        e->id = 0;
    }
}
