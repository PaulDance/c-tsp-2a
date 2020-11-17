#include "pokemon.h"


struct pokemon_type {
    char type[MAXLEN];
    int n;
    struct pokemon_type* next;
};

/**
 * Frees the given pokemon type recursively.
 * 
 * @param pt The pokemon type to free. 
 */
void pt_free(struct pokemon_type* pt) {
    if (pt != NULL) {
        pt_free(pt->next);
        free(pt);
    }
}


static struct pokemon_type* pokemon_types = NULL;

/**
 * Finds the node with the given type in the pokemon_types.
 * 
 * @param type The type to find.
 * @returns The node having the given type if it exists, NULL otherwise.
 */
struct pokemon_type* find(const char* type) {
    struct pokemon_type* pt = pokemon_types;

    while (pt != NULL && strncmp(pt->type, type, MAXLEN) != 0) {
        pt = pt->next;
    }

    return pt;
}

void add(const char* type, int n) {
    size_t len = strnlen(type, MAXLEN);

    if (len != 0) {
        struct pokemon_type* old_pt = find(type);

        if (old_pt != NULL) {           // If the type already exists in the list,
            old_pt->n += n;             // increment its count;
        } else {                        // otherwise add it as the head.
            struct pokemon_type* new_pt = malloc(sizeof(struct pokemon_type));
            strncpy(new_pt->type, type, len);
            new_pt->n = n;
            new_pt->next = pokemon_types;
            pokemon_types = new_pt;
        }
    }
}

void print(FILE* f) {
    for (struct pokemon_type* pt = pokemon_types;
         pt != NULL; pt = pt->next) {
        fprintf(f, "%s %i\n", pt->type, pt->n);
    }
}

void cleanup(void) {
    pt_free(pokemon_types);
    pokemon_types = NULL;
}


int main() {
    add("Terre", 1);
    add("Feu", 3);
    add("Féérique", 4);
    add("Eau", 5);
    add("Féérique", 3);

    print(stdout);
    cleanup();

    return 0;
}
