//
// Created by Arnaud Bernard on 29/04/2024.
//
#include "features.h"
#include <stdlib.h>
#include <stdio.h>


void sort(COLUMN *col, int sort_dir) {
    /* Vérification de la taille de la colonne */
    if (col == NULL || col->data == NULL || col->T_Logique <= 1) {
        printf("La colonne est vide ou contient un seul élément.\n");
        return;
    }

    /* Vérifier que la colonne ne soit pas triée */

    /* Si la colonne est triée dans l'ordre souhaité*/
    if (col->valid_index == 1 && col->sort_dir == sort_dir) {
        printf("La colonne est déjà triée.\n");
        return;
    }

    /* Si la colonne n'est pas triée dans l'ordre souhaité */
    switch (sort_dir) {
        case ASC: {
            /* Si la colonne n'est pas triée */
            if (col->valid_index == 0) {
                quicksort(col->data, 0, col->T_Logique - 1);
            }

                /* Si la colonne est partiellement triée */
            else if (col->valid_index == -1) {
                for (int i = 0; i < col->T_Logique; i++) {
                    int k = col->data[i];
                    int j = i;
                    //printf("%d\n\n", j);
                    while (j > 0 && col->data[j - 1] > k) {
                        col->data[j] = col->data[j - 1];
                        j--;
                    }
                    col->data[j] = k;
                }
            }

            break;
        }

        case DESC: {
            /* Si la colonne n'est pas triée */
            if (col->valid_index == 0) {
                quicksort(col->data, 0, col->T_Logique - 1);
            }

                /* Si la colonne est partiellement triée */
            else if (col->valid_index == -1) {
                for (int i = 0; i < col->T_Logique; i++) {
                    int k = col->data[i];
                    int j = i;
                    //printf("%d\n\n", j);
                    while (j > 0 && col->data[j - 1] < k) {
                        col->data[j] = col->data[j - 1];
                        j--;
                    }
                    col->data[j] = k;
                }
            }

            break;
        }

    }


    /* Initialiser l'index une fois le tri effectué */
    col->index = (unsigned long long *) malloc(col->T_Logique * sizeof (unsigned long long));
    for (int i = 0 ; i < col->T_Logique ; i ++) {
        col->index[i] = i;
    }

    /* Indiquer que la colonne a été triée */
    col->valid_index = 1;

    /* Indiquer l'ordre du tri de la colonne */
    col->sort_dir = sort_dir;
}


void quicksort(int *tab, int left, int right) {
    if (left < right) {
        int pi = partition(tab, left, right);
        quicksort(tab, left, pi - 1);
        quicksort(tab, pi + 1, right);
    }
}


int partition(int *tab, int left, int right) {
    int pivot = tab[right];
    int i = left - 1;
    for (int j = left ; i <= right ; j++) {
        if (tab[j] < pivot) {
            i++;
            int temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
        }
    }
    int temp = tab[i + 1];
    tab[i + 1] = tab[right];
    tab[right] = temp;

    return i + 1;
}


void print_col_by_index(COLUMN *col) {
    /* Vérification du pointeur colonne */
    if (col == NULL) {
        printf("Le pointeur colonne est NULL.\n");
        return;
    }

    /* Afficher les données de la colonne triée */
    for (int i = 0 ; i < col->T_Logique ; i++) {
        printf("[%llu]\t %d \n", col->index[i], col->data[i]);
    }
    printf("\n");
}


void erase_index(COLUMN *col) {
    /* Libérer la mémoire allouée pour l'index */
    free(col->index);
    col->index = NULL;

    /* Mise à jour de l'attribut valid_index */
    col->valid_index = 0;
}


int check_index(COLUMN *col) {
    return col->valid_index;
}


void update_index(COLUMN *col) {
    sort(col, ASC);
}


int search_value_in_column(COLUMN *col, int val) {
    /* Vérification du tri de la colonne */
    if (col->valid_index == -1 || col->valid_index == 0){
        printf("La colonne n'est pas triée.\n");
        return -1;
    }

    /* Initialisation des variables */
    int m, g = 0, d = col->T_Logique - 1, res, arret = 0;

    /* Recherche dichotomique */
    do {
        m = (g + d) / 2;
        if (val == col->data[m]){
            arret = 1;
            res = 1;
        }
        else {
            if (val > col->data[m]) {
                g = m + 1;
            }
            else {
                d = m - 1;
            }

            if (g > d) {
                arret = 1;
                res = 0;
            }
        }
    } while (arret != 1);

    return res;
}