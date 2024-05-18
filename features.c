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

    if (col->valid_index != 1) {
        printf("La colonne n'est pas triée.\n");
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
    sort(col, DESC);
}


int search_value_in_column(COLUMN *col, int val) {
    /* Vérification du tri de la colonne */
    if (col->valid_index == -1 || col->valid_index == 0){
        printf("La colonne n'est pas triée.\n");
        return -2;
    }

    /* Initialisation des variables */
    int m, g = 0, d = col->T_Logique - 1;

    /* Recherche dichotomique par ordre croissant*/
    if (col->sort_dir == ASC) {
        while (g <= d) {
            m = (g + d) / 2;
            if (val == col->data[m]) {
                return m;
            } else if (val > col->data[m]) {
                g = m + 1;
            } else {
                d = m - 1;
            }
        }
    }
    /* Recherche dichotomique par ordre décroissant*/
    else {
        while (g <= d) {
            m = (g + d) / 2;
            if (val == col->data[m]) {
                return m;
            } else if (val < col->data[m]) {
                g = m + 1;
            } else {
                d = m - 1;
            }
        }
    }
    return -1;
}


int display_menu_1() {
    printf("\n========== Menu ==========\n"
           "Attention !!! :\n"
           "- Toutes les actions sur des colonnes effectuer sur des colonnes intégrées au CDataFrame\n"
           "- Après avoir créé une colonne, il faut l'insérer dans le CDataFrame\n\n"
           "1 - Créer une colonne d'entiers\n"
           "2 - Remplir un CDataframe avec une saisie\n"
           "3 - Afficher le CDataframe\n"
           "4 - Afficher une partie des lignes du CDataFrame\n"
           "5 - Afficher une partie des colonnes du CDataFrame\n"
           "6 - Ajouter une ligne de valeurs au CDataFrame\n"
           "7 - Supprimer une ligne de valeurs du CDataFrame\n"
           "8 - Supprimer une colonne du CDataFrame\n"
           "9 - Renommer le titre d'une colonne du CDataFrame\n"
           "10 - Chercher une valeur dans le CDataFrame\n"
           "11 - Remplacer une cellule du CDataFrame\n"
           "12 - Accéder à la valeur d'une cellule du CDataFrame\n"
           "13 - Afficher le nom des colonnes du CDataFrame\n"
           "14 - Afficher le nombre de lignes du CDataFrame\n"
           "15 - Afficher le nombre de colonnes du CDataFrame\n"
           "16 - Nombre de cellules égale à une valeur x dans une colonne\n"
           "17 - Nombre de cellules plus grandes qu'une valeur x dans une colonne\n"
           "18 - Nombre de cellules plus petites qu'une valeur x dans une colonne\n"
           "19 - Nombre de cellules égale à une valeur x dans le CDataFrame\n"
           "20 - Nombre de cellules plus grandes qu'une valeur x dans le CDataFrame\n"
           "21 - Nombre de cellules plus petites qu'une valeur x dans le CDataFrame\n"
           "22 - Trier une colonne\n"
           "23 - Afficher le contenu d'une colonne triée\n"
           "24 - Effacer l'index d'une colonne\n"
           "25 - Vérifier si une colonne possède un index\n"
           "26 - Mettre à jour un index\n"
           "27 - Faire une recherche dichotomique\n"
           "28 - Ne rien faire\n");
    int action;

    do {
        printf("Que voulez-vous faire ?\n");
        scanf("%d", &action);
    } while (action <= 0 || action >= 30);

    return action;
}


int display_menu_2() {
    printf("\n\n========== Menu ==========\n"
           "Attention !!! :\n"
           "- Si vous souhaitez créer une autre colonne, supprimez la colonne déjà\n"
           "  existante, en pensant à l'insérer préalablement dans le CDataframe si nécessaire\n\n"
           "1 - Insérer une valeur dans la colonne préalablement créée\n"
           "2 - Supprimer la colonne préalablement créée\n"
           "3 - Afficher la colonne préalablement créée\n"
           "4 - Remplir un CDataframe avec une saisie\n"
           "5 - Afficher le CDataframe\n"
           "6 - Afficher une partie des lignes du CDataFrame\n"
           "7 - Afficher une partie des colonnes du CDataFrame\n"
           "8 - Ajouter une ligne de valeurs au CDataFrame\n"
           "9 - Supprimer une ligne de valeurs du CDataFrame\n"
           "10 - Ajouter une colonne au CDataFrame\n"
           "11 - Supprimer une colonne du CDataFrame\n"
           "12 - Renommer le titre d'une colonne du CDataFrame\n"
           "13 - Chercher une valeur dans le CDataFrame\n"
           "14 - Remplacer une cellule du CDataFrame\n"
           "15 - Accéder à la valeur d'une cellule du CDataFrame\n"
           "16 - Afficher le nom des colonnes du CDataFrame\n"
           "17 - Afficher le nombre de lignes du CDataFrame\n"
           "18 - Afficher le nombre de colonnes du CDataFrame\n"
           "19 - Nombre de cellules égale à une valeur x dans une colonne\n"
           "20 - Nombre de cellules plus grandes qu'une valeur x dans une colonne\n"
           "21 - Nombre de cellules plus petites qu'une valeur x dans une colonne\n"
           "22 - Nombre de cellules égale à une valeur x dans le CDataFrame\n"
           "23 - Nombre de cellules plus grandes qu'une valeur x dans le CDataFrame\n"
           "24 - Nombre de cellules plus petites qu'une valeur x dans le CDataFrame\n"
           "25 - Trier une colonne\n"
           "26 - Afficher le contenu d'une colonne triée\n"
           "27 - Effacer l'index d'une colonne\n"
           "28 - Vérifier si une colonne possède un index\n"
           "29 - Mettre à jour un index\n"
           "30 - Faire une recherche dichotomique\n"
           "31 - Ne rien faire\n");
    int action;

    printf("Que voulez-vous faire ?\n");
    do {
        scanf("%d", &action);
    } while (action <= 0 || action >= 30);

    return action;
}