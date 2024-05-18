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
    column->index = NULL;
    column->valid_index = 0;
    column->sort_dir = 0;
    return column;
}


int insert_value(COLUMN* col, int value) {
    /* Vérification du pointeur colonne */
    if (col == NULL) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

    /* Si la colonne n'a pas encore été utilisé, faire une allocation */
    if (col->data == NULL) {
        col->T_Physique += REALLOC_SIZE * sizeof (int);
        col->data = (int*) malloc(col->T_Physique);

        /* Vérification de la bonne allocation */
        if (col->data == NULL) {
            printf("Échec de la réallocation de la mémoire.\n");
            return 0;
        }
    }

    /* S'il n'y a plus de place, faire une réallocation */
    else if (col->T_Physique == col->T_Logique) {
        col->T_Physique += REALLOC_SIZE * sizeof (int);
        col->data = realloc(col->data, col->T_Physique);

        /* Vérification de la bonne réallocation */
        if (col->T_Physique == col->T_Logique) {
            printf("Échec de la réallocation de la mémoire.\n");
            return 0;
        }
    }

    /* S'il y a assez de place, insérer la valeur */
    col->data[(col->T_Logique)++] = value;
    return 1;
}


void delete_column(COLUMN *col) {
    /* Vérification du pointeur colonne */
    if (col == NULL) {
        printf("Le pointeur colonne est déjà NULL.\n");
        return;
    }

    /* Libère la mémoire allouée au tableau de donnée */
    col->T_Physique = 0;
    col->T_Logique = 0;
    free(col->data);
    col->data = NULL;

    /* Libère la mémoire allouée au titre de la colonne */
    free(col->title);
    col->title = NULL;

    /* Libère la mémoire allouée à la colonne */
    //free(col);
    //col = NULL;
}


void print_col(COLUMN* col) {
    /* Vérification du pointeur colonne */
    if (col == NULL) {
        printf("Le pointeur colonne est NULL.\n");
        return;
    }

    if (col->valid_index != 1)

    /* Afficher le titre de la colonne */
    printf("\n%s \n", col->title);

    /* Afficher les données de la colonne */
    for (int i = 0 ; i < col->T_Logique ; i++) {
        printf("[%d]\t %d \n", i, col->data[i]);
    }
    printf("\n");
}


int number_occ(COLUMN* col, int value) {
    /* Vérification du pointeur colonne */
    if (col == NULL) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

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
    /* Vérification du pointeur colonne */
    if (col == NULL) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

    /* Vérifie que la position fait partie du tableau */
    if (pos <= col->T_Logique)
        return col->data[pos];

    /* Sinon retourner 0 */
    return 0;
}


int greater_than(COLUMN* col, int x) {
    /* Vérification du pointeur colonne */
    if (col == NULL) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

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
    /* Vérification du pointeur colonne */
    if (col == NULL) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

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
    /* Vérification du pointeur colonne */
    if (col == NULL) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

    /* Initialisation du compteur */
    int cpt = 0;

    /* Parcours de toutes les données */
    for (int i = 0 ; i < col->T_Logique ; i++) {
        if (col->data[i] == x)
            cpt++;
    }

    return  cpt;
}
