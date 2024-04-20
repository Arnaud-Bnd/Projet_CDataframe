//
// Created by Arnaud Bernard on 28/03/2024.
//
#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

COLUMN *create_column(char* title) {
    COLUMN* column = (COLUMN*) malloc(sizeof * column);
    column->title = title;
    column->T_Logique = 0;
    column->T_Physique = 0;
    column->data = NULL;
    return column;
}

int insert_value(COLUMN* col, int value) {

    /* Si la colonne n'a pas encore été utilisé, faire une allocation */
    if (col->data == NULL) {
        /* Allocation */
        col->data = (COLUMN*) malloc(REALLOC_SIZE);
        col->T_Physique += REALLOC_SIZE;
        /* Insertion de la valeur */
        col->data[(col->T_Logique)++] = value;
        return 1;
    }

    /* S'il n'y a plus de place, faire une réallocation */
    else if (col->T_Physique == col->T_Logique) {
        /* Réallocation */
        col->T_Physique += REALLOC_SIZE;
        realloc(col->data, col->T_Physique);
        /* Insertion de la valeur */
        col->data[(col->T_Logique)++] = value;
        return 1;
    }

    /* Insertion de la valeur */
    else if (col->T_Physique != col->T_Logique) {
        col->data[(col->T_Logique)++] = value;
        return 1;
    }

    /* Retourner 0 si l'insertion n'a pas été faite */
    else {
        return 0;
    }
}