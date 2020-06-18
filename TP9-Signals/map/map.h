#ifndef MAP_H
#define MAP_H

/* a hashmap.
 * the exact content of the structure may depend on the implementation
 */
struct map;

/* initialize a hashmap */
struct map* map_init();

/* insert the couple (key, value) */
void map_put(struct map* map, int key, void* val);

/* return the value associated with key */
void* map_get(struct map* map, int key);

/* free a map and all the stored values */
void map_free(struct map* map);

#endif /* MAP_H */
