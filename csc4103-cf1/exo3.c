#include <zconf.h>
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


/**
 * @returns The length of the pokedex in pokemons. 
 */
size_t pokedex_len(void) {
    FILE* pd_file = fopen(POKEDEX, "r");
    fseek(pd_file, 0, SEEK_END);
    size_t length = ftell(pd_file) / sizeof(struct pokemon);

    fclose(pd_file);
    return length;
}

void process(size_t first, size_t n) {
    FILE* pd_file = fopen(POKEDEX, "r");
    struct pokemon* pm = malloc(sizeof(struct pokemon));
    fseek(pd_file, first * sizeof(struct pokemon), SEEK_SET);                   // Start at first.
    size_t i = first;

    while (i < first + n && fread(pm, sizeof(struct pokemon), 1, pd_file)) {    // For every pokemon,
        for (size_t j = 0; j < sizeof(pm->type) / MAXLEN; j++) {                // for every of its types,
            if (pm->type[j][0]) {                                               // if it is not empty,
                add(pm->type[j], 1);                                            // add it.
            }
        }

        i++;
    }

    fclose(pd_file);
}


int main(int argc, char** argv) {
    unlink("result");
    size_t nb_children;
    char* err_ptr = NULL;

    if (argc != 2 || (nb_children = strtoul(argv[1], &err_ptr, 0)) == ULONG_MAX
            || err_ptr != argv[1] + strlen(argv[1])) {
        fprintf(stderr, "Usage: %s: <nb_children: integer>\n", argv[0]);
        return 1;
    }

    size_t total = pokedex_len();
    printf("Total: %lu\n", total);
    size_t first = 0, n = total / nb_children;

    for (size_t i = 0; i < nb_children; i++) {
        if (i == nb_children - 1) {
            n += total - n * nb_children;
        }

        const pid_t child_pid = fork();

        if (child_pid == 0) {
            printf("[%i] processing %lu entries from %lu...\n", getpid(), n, first);
            sleep(1);

            cleanup();
            printf("[%i] child quitting.\n", getpid());
            return 0;
        } else {
            first += n;
        }
    }

    wait(NULL);
    print(stdout);
    cleanup();

    printf("[%i] quitting.\n", getpid());
    return 0;
}
