//
// Created by Arnaud Bernard on 29/04/2024.
//
#include "features.h"
#include <stdlib.h>
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


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
                for (int i = 0; i < col->T_Logique - 1; i++) {
                    int max_idx = i;
                    for (int j = i + 1; j < col->T_Logique; j++) {
                        if (col->data[col->index[j]] < col->data[col->index[max_idx]]) {
                            max_idx = j;
                        }
                    }
                    if (max_idx != i) {
                        int temp = col->index[i];
                        col->index[i] = col->index[max_idx];
                        col->index[max_idx] = temp;
                    }
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
                for (int i = 0; i < col->T_Logique - 1; i++) {
                    int min_idx = i;
                    for (int j = i + 1; j < col->T_Logique; j++) {
                        if (col->data[col->index[j]] > col->data[col->index[min_idx]]) {
                            min_idx = j;
                        }
                    }
                    if (min_idx != i) {
                        int temp = col->index[i];
                        col->index[i] = col->index[min_idx];
                        col->index[min_idx] = temp;
                    }
                }
            }

            break;
        }
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


void print_sort_cdt(CDATAFRAME *cdt, int index){
    /* Vérification de la taille du CDataframe */
    if (cdt == NULL) {
        printf("Le pointeur CDataframe est NULL.\n");
        return;
    }

    if (cdt->column[index]->valid_index != 1) {
        printf("La colonne n'est pas triée.\n");
        return;
    }

    /* Afficher le titre du CDataframe */
    printf("%s\n", cdt->title);

    /* Vérification du nombre de colonnes */
    if (cdt->num_columns == 0) {
        printf("Le CDataframe n'a pas de colonnes.\n");
        return;
    }

    /* Boucle pour les titres des colonnes */
    printf("\t\t");
    for (int i = 0 ; i < cdt->num_columns ; i++) {
        // Afficher le titre de la colonne
        printf("%s\t\t", (char *) cdt->column[i]->title);
    }
    printf("\n");

    /* Trouver la colonne avec le plus de lignes */
    int max_rows = number_of_lines(cdt);

    /* Boucle pour les valeurs des colonnes */
    for (int j = 0 ; j < max_rows ; j++){   // Variation de la ligne
        /* Afficher le numéro de la ligne */
        printf("[%d]\t\t", j + 1);

        /* Afficher les valeurs */
        for (int i = 0 ; i < cdt->num_columns ; i++) {    // Variation de la colonne
            for (int k = 0 ; i < cdt->num_columns ; k++) {    // Variation de l'index
                if (j == cdt->column[index]->index[k]) {
                    // Afficher la valeur
                    printf("%d\t\t\t\t", cdt->column[i]->data[k]);
                    break;
                }
            }
        }
        printf("\n"); // Passage à la ligne suivante
    }
    printf("\n");
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
        for (int j = 0 ; j < col->T_Logique ; j++) {
            if (i == col->index[j]) {
                printf("[%llu] : %d\n", col->index[j] + 1, col->data[j]);
            }
        }
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
           "4 - Afficher une colonne du CDataframe\n"
           "5 - Afficher une partie des lignes du CDataFrame\n"
           "6 - Afficher une partie des colonnes du CDataFrame\n"
           "7 - Ajouter une ligne de valeurs au CDataFrame\n"
           "8 - Supprimer une ligne de valeurs du CDataFrame\n"
           "9 - Supprimer une colonne du CDataFrame\n"
           "10 - Renommer le titre d'une colonne du CDataFrame\n"
           "11 - Chercher une valeur dans le CDataFrame\n"
           "12 - Remplacer une cellule du CDataFrame\n"
           "13 - Accéder à la valeur d'une cellule du CDataFrame\n"
           "14 - Afficher le nom des colonnes du CDataFrame\n"
           "15 - Afficher le nombre de lignes du CDataFrame\n"
           "16 - Afficher le nombre de colonnes du CDataFrame\n"
           "17 - Nombre de cellules égale à une valeur x dans une colonne\n"
           "18 - Nombre de cellules plus grandes qu'une valeur x dans une colonne\n"
           "19 - Nombre de cellules plus petites qu'une valeur x dans une colonne\n"
           "20 - Nombre de cellules égale à une valeur x dans le CDataFrame\n"
           "21 - Nombre de cellules plus grandes qu'une valeur x dans le CDataFrame\n"
           "22 - Nombre de cellules plus petites qu'une valeur x dans le CDataFrame\n"
           "23 - Trier une colonne\n"
           "24 - Afficher le contenu d'une colonne triée\n"
           "25 - Afficher le CDataframe en fonction d'une colonne triée\n"
           "26 - Effacer l'index d'une colonne\n"
           "27 - Vérifier si une colonne possède un index\n"
           "28 - Mettre à jour un index\n"
           "29 - Faire une recherche dichotomique\n"
           "30 - Ne rien faire\n");
    int action;

    do {
        printf("Que voulez-vous faire ?\n");
        scanf("%d", &action);
    } while (action <= 0 || action > 30);

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
           "6 - Afficher une colonne du CDataframe\n"
           "7 - Afficher une partie des lignes du CDataFrame\n"
           "8 - Afficher une partie des colonnes du CDataFrame\n"
           "9 - Ajouter une ligne de valeurs au CDataFrame\n"
           "10 - Supprimer une ligne de valeurs du CDataFrame\n"
           "11 - Ajouter une colonne au CDataFrame\n"
           "12 - Supprimer une colonne du CDataFrame\n"
           "13 - Renommer le titre d'une colonne du CDataFrame\n"
           "14 - Chercher une valeur dans le CDataFrame\n"
           "15 - Remplacer une cellule du CDataFrame\n"
           "16 - Accéder à la valeur d'une cellule du CDataFrame\n"
           "17 - Afficher le nom des colonnes du CDataFrame\n"
           "18 - Afficher le nombre de lignes du CDataFrame\n"
           "19 - Afficher le nombre de colonnes du CDataFrame\n"
           "20 - Nombre de cellules égale à une valeur x dans une colonne\n"
           "21 - Nombre de cellules plus grandes qu'une valeur x dans une colonne\n"
           "22 - Nombre de cellules plus petites qu'une valeur x dans une colonne\n"
           "23 - Nombre de cellules égale à une valeur x dans le CDataFrame\n"
           "24 - Nombre de cellules plus grandes qu'une valeur x dans le CDataFrame\n"
           "25 - Nombre de cellules plus petites qu'une valeur x dans le CDataFrame\n"
           "26 - Trier une colonne\n"
           "27 - Afficher le contenu d'une colonne triée\n"
           "28 - Afficher le CDataframe en fonction d'une colonne triée\n"
           "29 - Effacer l'index d'une colonne\n"
           "30 - Vérifier si une colonne possède un index\n"
           "31 - Mettre à jour un index\n"
           "32 - Faire une recherche dichotomique\n"
           "33 - Ne rien faire\n");
    int action;

    printf("Que voulez-vous faire ?\n");
    do {
        scanf("%d", &action);
    } while (action <= 0 || action > 33);

    return action;
}