//
// Created by Arnaud Bernard on 28/03/2024.
//
#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COLUMN *create_column(char* title) {
    COLUMN* column = (COLUMN *) malloc(sizeof (COLUMN));
    column->title = title;
    column->T_Logique = 0;
    column->T_Physique = 0;
    column->data = NULL;

    return column;
}

int insert_value(COLUMN* col, int value) {
    /* Si la colonne n'a pas encore été utilisé, faire une allocation */
    if (col->data == NULL) {
        col->T_Physique += REALLOC_SIZE * sizeof (int);
        col->data = (int*) malloc(col->T_Physique);
        return 0;
    }

    /* S'il n'y a plus de place, faire une réallocation */
    else if (col->T_Physique == col->T_Logique) {
        col->T_Physique += REALLOC_SIZE * sizeof (int);
        realloc(col->data, col->T_Physique);
        return 0;
    }

    /* S'il y a assez de place, insérer la valeur */
    col->data[(col->T_Logique)++] = value;
    return 1;
}

void delete_column(COLUMN *col) {
    /* Libère la mémoire allouée au tableau de donnée */
    col->T_Physique = 0;
    col->T_Logique = 0;
    free(col->data);
    col->data = NULL;

    /* Libère la mémoire allouée au titre de la colonne */
    free(col->title);
    col->title = NULL;

    /* Libère la mémoire allouée à la colonne */
    free(col);
    col = NULL;
}

void print_col(COLUMN* col) {
    /* Afficher le titre de la colonne */
    printf("\n%s \n", col->title);

    /* Afficher les données de la colonne */
    for (int i = 0 ; i < col->T_Logique ; i++) {
        printf("[%d]\t %d \n", i + 1, col->data[i]);
    }
    printf("\n");
}

int number_occ(COLUMN* col, int value) {
    /* Initialisation du compteur */
    int cpt = 0;

    /* Parcours de toutes les données */
    for (int i = 0 ; i < col->T_Logique ; i++) {
        if (col->data[i] == value)
            cpt++;
    }

    return  cpt;
}

int val_at_pos(COLUMN* col, int pos) {
    /* Vérifie que la position fait partie du tableau */
    if (pos <= col->T_Logique)
        return col->data[pos];

    /* Sinon retourner NULL (0) */
    return (int) NULL;
}

int greater_than(COLUMN* col, int x) {
    /* Initialisation du compteur */
    int cpt = 0;

    /* Parcours de toutes les données */
    for (int i = 0 ; i < col->T_Logique ; i++) {
        if (col->data[i] > x)
            cpt++;
    }

    return  cpt;
}

int less_than(COLUMN* col, int x) {
    /* Initialisation du compteur */
    int cpt = 0;

    /* Parcours de toutes les données */
    for (int i = 0 ; i < col->T_Logique ; i++) {
        if (col->data[i] < x)
            cpt++;
    }

    return  cpt;
}

int equal_to(COLUMN* col, int x) {
    /* Initialisation du compteur */
    int cpt = 0;

    /* Parcours de toutes les données */
    for (int i = 0 ; i < col->T_Logique ; i++) {
        if (col->data[i] == x)
            cpt++;
    }

    return  cpt;
}
