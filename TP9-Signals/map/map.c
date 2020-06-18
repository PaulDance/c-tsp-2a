#include <malloc.h>
#include "map.h"


struct couple {
    int key;
    void* value;
};

struct map {
    size_t length;
    struct couple* array;
};

struct map* map_init() {
    struct map* map = malloc(sizeof(struct map));
    map->array = NULL;
    map->length = 0;
    return map;
}

void map_put(struct map* map, int key, void* val) {
    for (size_t i = 0; i < map->length; i++) {
        if (map->array[i].key == key) {
            map->array[i].value = val;
            return;
        }
    }
    
    map->array = reallocarray(map->array, map->length + 1, sizeof(struct couple));
    map->array[map->length].key = key;
    map->array[map->length].value = val;
    map->length++;
}

void* map_get(struct map* map, int key) {
    for (size_t i = 0; i < map->length; i++) {
        if (map->array[i].key == key) {
            return map->array[i].value;
        }
    }
    
    return NULL;
}

void map_free(struct map* map) {
    for (size_t i = 0; i < map->length; i++) {
        free(map->array[i].value);
    }
    
    free(map->array);
    free(map);
}
