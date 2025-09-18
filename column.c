//
// Created by Arnaud Bernard on 28/03/2024.
//
#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////////:
Column *createColumn(char* title) {
    Column* column = (Column *) malloc(sizeof (Column));
    column->title = title;
    column->T_Logique = 0;
    column->T_Physique = 0;
    column->data = NULL;
    column->index = NULL;
    column->mValidIndex = 0;
    column->mSortDir = 0;
    return column;
}

int insertValue(Column* col, int value) {
    /* Vérification du pointeur colonne */
    if (!col) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

    /* Si la colonne n'a pas encore été utilisé, faire une allocation */
    if (!col->data) {
        col->T_Physique += REALLOC_SIZE * sizeof (int);
        col->data = (int*) malloc(col->T_Physique);

        /* Allouer la place nécessaire à l'index */
        col->index = (uint64_t *) malloc(0 * sizeof (uint64_t)); // ??? malloc 0 ???

        /* Vérification de la bonne allocation */
        if (!col->data) {
            printf("Échec de la réallocation de la mémoire.\n");
            return 0;
        }
    }

    /* S'il n'y a plus de place, faire une réallocation */
    else if (col->T_Physique == col->T_Logique) {
        col->T_Physique += REALLOC_SIZE * sizeof (int);
        col->data = realloc(col->data, col->T_Physique); /// ???? pas de contrôle d'erreur d'allocation !!!!

        /* Vérification de la bonne réallocation */
        if (col->T_Physique == col->T_Logique) {
            printf("Échec de la réallocation de la mémoire.\n");
            return 0;
        }
    }

    /* S'il y a assez de place, insérer la valeur */
    col->data[(col->T_Logique)++] = value;

    /* Indiquer que la colonne n'est plus triée */
    col->mValidIndex = -1;

    /* Indiquer l'index associé à la valeur */
    col->index = realloc(col->index, sizeof (unsigned long long) * col->T_Logique);
    col->index[col->T_Logique - 1] = col->T_Logique - 1;

    return 1;
}

void deleteColumn(Column *col) {
    /* Vérification du pointeur colonne */
    if (!col) {
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

void printColumn(Column* col) {
    /* Vérification du pointeur colonne */
    if (!col) {
        printf("Le pointeur colonne est NULL.\n");
        return;
    }

    /* Afficher le titre de la colonne */
    printf("\n%s \n", col->title);

    /* Afficher les données de la colonne */
    for (int i = 0 ; i < col->T_Logique ; i++) {
        printf("[%d]\t %d \n", i + 1, col->data[i]);
    }
    printf("\n");
}

int numberOcc(Column* col, int value) {
    /* Vérification du pointeur colonne */
    if (!col) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

    /* Parcours de toutes les données */
    int cpt = 0;
    for (int i = 0 ; i < col->T_Logique ; i++) {
        if (col->data[i] == value)
            cpt++;
    }

    return  cpt;
}

int valAtPos(Column* col, int pos) {
    if (!col) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

    /* Vérifie que la position fait partie du tableau */
    if (pos <= col->T_Logique) return col->data[pos];

    /* Sinon retourner 0 */
    return 0;
}


int greater_than(Column* col, int x) {
    if (!col) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

    /* Parcours de toutes les données */
    int cpt = 0;
    for (int i = 0 ; i < col->T_Logique ; i++) {
        if (col->data[i] > x)
            cpt++;
    }

    return  cpt;
}

int lessThan(Column* col, int x) {
    if (!col) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

    /* compte les valeurs inferieur à x dans la colonne courante */
    int cpt = 0;
    for (int i = 0 ; i < col->T_Logique ; i++) {
        if (col->data[i] < x)
            cpt++;
    }

    return  cpt;
}

int equalTo(Column* col, int x) {
    if (!col) {
        printf("Le pointeur colonne est NULL.\n");
        return 0;
    }

    /* compte les valeurs égales à x dans la colonne courante */
    int cpt = 0;
    for (int i = 0 ; i < col->T_Logique ; i++) {
        if (col->data[i] == x)
            cpt++;
    }

    return  cpt;
}
