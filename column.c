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

void delete_column(COLUMN *col) {
    /* Libère la mémoire allouée au tableau de donnée */
    col->T_Physique = 0;
    col->T_Logique = 0;
    col->data = NULL;
    free(col->data);

    /* Libère la mémoire allouée au titre de la colonne */
    col->title = NULL;
    free(col->title);

    /* Libère la mémoire allouée à la colonne */
    col = NULL;
    free(col);
}

void print_col(COLUMN* col) {
    /* Afficher le titre de la colonne */
    printf("\n%s \n", col->title);

    /* Afficher les données de la colonne */
    for (int i = 0 ; i < col->T_Logique ; i++) {
        printf("[%d]\t %d \n", i, col->data[i]);
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
