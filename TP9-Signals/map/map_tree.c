#include <malloc.h>
#include "map.h"


struct bt {
    int key;
    void* value;
    struct bt* left;
    struct bt* right;
};

struct bt* bt_init() {
    struct bt* bt = malloc(sizeof(struct bt));
    bt->key = 0;
    bt->value = bt->left = bt->right = NULL;
    return bt;
}

struct bt* bt_insert(struct bt* tree, int key, void* value) {
    if (tree == NULL) {
        struct bt* leaf = bt_init();
        leaf->key = key;
        leaf->value = value;
        return leaf;
    } else if (key < tree->key) {
        tree->left = bt_insert(tree->left, key, value);
    } else if (key > tree->key) {
        tree->right = bt_insert(tree->right, key, value);
    } else {
        tree->value = value;
    }
    
    return tree;
}

struct bt* bt_search(struct bt* bt, int key) {
    if (bt == NULL) {
        return NULL;
    } else if (key < bt->key) {
        return bt_search(bt->left, key);
    } else if (key > bt->key) {
        return bt_search(bt->right, key);
    } else {
        return bt;
    }
}

void bt_print(struct bt* bt) {
    if (bt == NULL) {
        printf("LEAF\n");
    } else {
        printf("(%i, %p)\n", bt->key, bt->value);
        printf("l: ");
        bt_print(bt->left);
        printf("r: ");
        bt_print(bt->right);
    }
}

void bt_free(struct bt* bt) {
    if (bt->left != NULL) {
        bt_free(bt->left);
    }

    if (bt->right != NULL) {
        bt_free(bt->right);
    }
    
    free(bt->value);
    free(bt);
}


struct map {
    struct bt* bt;
};

struct map* map_init() {
    struct map* map = malloc(sizeof(struct map));
    map->bt = NULL;
    return map;
}

void map_put(struct map* map, int key, void* val) {
    map->bt = bt_insert(map->bt, key, val);
}

void* map_get(struct map* map, int key) {
    struct bt* bt = bt_search(map->bt, key);
    return bt == NULL ? NULL : bt->value;
}

void map_free(struct map* map) {
    bt_free(map->bt);
    free(map);
}
