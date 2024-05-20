#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "column.h"
#include "cdataframe.h"
#include "features.h"

int main() {
    CDATAFRAME *cdt = load_from_csv("/Users/arnaudbernard/Documents/01 - Efrei/Année 1/S2/Algorithmique et structure de données/Projet-CDataframe/data.csv", 20);
    //printf("%s\n", cdt->column[0]->title);
    print_cdt(cdt);

    CDATAFRAME *mycdt = hard_filling();
    print_cdt(mycdt);

    save_into_csv(mycdt, "/Users/arnaudbernard/Documents/01 - Efrei/Année 1/S2/Algorithmique et structure de données/Projet-CDataframe/data2.csv");
    return 0;
}


int main1() {
    /* Création d'un CDataFrame */
    // CDATAFRAME *cdt = create_cdataframe("CDataFrame");
    CDATAFRAME *cdt = hard_filling();

    /* Création du pointeur colonne */
    COLUMN *col = NULL;

    int existence_col = 0;

    /* Initialisation variable de l'action de l'utilisateur */
    int action;

    do {
        /* Si aucune colonne existe */
        if (existence_col == 0) {
            /* Afficher le menu et demander l'action */
            action = display_menu_1();

            /* Effectuer l'action */
            switch (action) {
                case 1 : { /* Créer une colonne d'entiers */
                    char nom[20];
                    printf("Choisissez un nom pour la colonne : ");
                    scanf("%s", nom);
                    printf("\n");

                    col = create_column(nom);
                    existence_col = 1;
                    break;
                }

                case 2 : { /* Remplir un CDataframe avec une saisie */
                    user_input(cdt);
                    break;
                }

                case 3 : { /* Afficher le CDataframe */
                    print_cdt(cdt);
                    break;
                }

                case 4 : { /* Afficher une colonne du CDataframe */
                    char name[20];
                    printf("Donnez le nom de la colonne que vous souhaitez afficher : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    print_col(cdt->column[index]);
                    break;
                }

                case 5 : { /* Afficher une partie des lignes du CDataFrame */
                    int x, y;

                    do {
                        printf("Donnez le numéro de la ligne de départ (de 1 à %d) : ", number_of_lines(cdt));
                        scanf("%d", &x);
                    } while (x < 1 || x > number_of_lines(cdt));
                    printf("\n");

                    do {
                        printf("Donnez le numéro de la ligne de fin (de %d à %d) : ", x, number_of_lines(cdt));
                        scanf("%d", &y);
                    } while (y < x || y > number_of_lines(cdt));
                    printf("\n");

                    print_lines(cdt, x, y);
                    break;
                }

                case 6 : { /* Afficher une partie des colonnes du CDataframe */
                    int x = -1, y = -1;

                    char name_x[20];
                    printf("Donnez le nom de la colonne de départ : ");
                    scanf("%s", name_x);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    for (int i = 0; i < cdt->num_columns ; i++) {
                        if (strcmp(cdt->column[i]->title, name_x) == 0) {
                            x = i;
                            break;
                        }
                    }
                    if (x == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    char name_y[20];
                    printf("Donnez le nom de la colonne de fin : ");
                    scanf("%s", name_y);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    for (int i = x ; i < cdt->num_columns ; i++) {
                        if (strcmp(cdt->column[i]->title, name_y) == 0) {
                            y = i;
                            break;
                        }
                    }
                    if (y == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    print_col_of_cdt(cdt, x, y);
                    break;
                }

                case 7 : { /* Ajouter une ligne de valeurs au CDataFrame */
                    insert_line(cdt);
                    break;
                }

                case 8 : { /* Supprimer une ligne de valeurs du CDataFrame */
                    int index;

                    printf("Quelle ligne souhaitez-vous supprimer (1 à %d) ? ", number_of_lines(cdt));
                    do {
                        scanf("%d", &index);
                    } while (index < 1 || index > number_of_lines(cdt));

                    delete_line(cdt, index - 1);
                    break;
                }

                case 9 : { /* Supprimer une colonne du CDataFrame */
                    char name[20];
                    printf("Donnez le nom de la colonne que vous souhaitez supprimer : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    delete_col(cdt, index);
                    break;
                }

                case 10 : { /* Renommer le titre d'une colonne du CDataFrame */
                    char name[20];
                    printf("Donnez le nom de la colonne dont vous souhaitez modifier le nom : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    char new_name[20];
                    printf("Quelle nom voulez-vous donner à la colonne ? ");
                    scanf("%s", new_name);
                    printf("\n");

                    printf("\t%d\n", rename_col(cdt, index, new_name));
                    break;
                }

                case 11 : { /* Chercher une valeur dans le CDataFrame */
                    int val;

                    printf("Quelle valeurs cherchez-vous dans le CDataframe ? ");
                    scanf("%d", &val);

                    printf("La valeur apparait %d fois dans le CDataframe.\n", search_value(cdt, val));
                    break;
                }

                case 12 : { /* Remplacer une cellule du CDataFrame */
                    int x;
                    printf("Donnez le numéro de la ligne de la cellule que vous souhaitez modifier (de 1 à %d) : ",
                           number_of_lines(cdt));
                    do {
                        scanf("%d", &x);
                    } while (x < 1 || x > number_of_lines(cdt));
                    printf("\n");


                    char name[20];
                    printf("Donnez le nom de la colonne de la cellule que vous souhaitez modifier : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int y = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            y = i;
                            break;
                        }
                    }
                    if (y == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int val;
                    printf("Quelle valeur souhaitez-vous ? ");
                    scanf("%d", &val);
                    printf("\n");


                    replace_cell(cdt, x - 1, y, val);
                    printf("\n");
                    break;
                }

                case 13 : { /* Accéder à la valeur d'une cellule du CDataFrame */
                    int x;
                    printf("Donnez le numéro de la ligne de la cellule que vous souhaitez accéder (de 1 à %d) : ",
                           number_of_lines(cdt));
                    do {
                        scanf("%d", &x);
                    } while (x < 1 || x > number_of_lines(cdt));
                    printf("\n");


                    char name[20];
                    printf("Donnez le nom de la colonne de la cellule que vous souhaitez accéder : ");
                    scanf("%s", name);
                    printf("\n");


                    int y = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            y = i;
                            break;
                        }
                    }
                    if (y == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    printf("La valeur à la colonne '%s' et à la ligne %d est : %d.\n", cdt->column[y]->title, x,
                           select_cell(cdt, x - 1, y));
                    break;
                }

                case 14 : { /* Afficher le nom des colonnes du CDataFrame */
                    printf("\n");
                    print_name_col(cdt);
                    break;
                }

                case 15 : { /* Afficher le nombre de lignes du CDataFrame */
                    printf("\nLe CDataframe contient %d lignes.\n\n", number_of_lines(cdt));
                    break;
                }

                case 16 : { /* Afficher le nombre de colonnes du CDataFrame */
                    printf("\nLe CDataFrame contient %d colonnes.\n\n", number_of_cols(cdt));
                    break;
                }

                case 17 : { /* Nombre de cellules égale à une valeur x dans une colonne */
                    char name[20];
                    printf("Donnez le nom de la colonne qui vous intéresse : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules égale à %d dans '%s' est : %d\n\n", x, cdt->column[index]->title, equal_to(cdt->column[index], x));
                    break;
                }

                case 18 : { /* Nombre de cellules plus grandes qu'une valeur x dans une colonne */
                    char name[20];
                    printf("Donnez le nom de la colonne qui vous intéresse : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules plus grandes que %d dans '%s' est : %d\n\n", x, cdt->column[index]->title, greater_than(cdt->column[index], x));
                    break;
                }

                case 19 : { /* Nombre de cellules plus petites qu'une valeur x dans une colonne */
                    char name[20];
                    printf("Donnez le nom de la colonne qui vous intéresse : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules plus petite que %d dans '%s' est : %d\n\n", x, cdt->column[index]->title, less_than(cdt->column[index], x));
                    break;
                }

                case 20 : { /* Nombre de cellules égale à une valeur x */
                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules égale à %d est : %d\n\n", x, cell_equal_to(cdt, x));
                    break;
                }

                case 21 : { /* Nombre de cellules plus grandes qu'une valeur x */
                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules supérieures à %d est : %d\n", x, cell_greater_than(cdt, x));
                    break;
                }

                case 22 : { /* Nombre de cellules plus petites qu'une valeur x */
                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules inférieures à %d est : %d\n\n", x, cell_less_than(cdt, x));
                    break;
                }

                case 23 : { /* Trier une colonne */
                    char name[20];
                    printf("Donnez le nom de la colonne que vous souhaitez trier : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }

                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int sort_order;
                    printf("Vous souhaitez trier la colonne dans l'ordre croissant (0) ou décroissant (1) : ");
                    scanf("%d", &sort_order);

                    cdt->column[index]->valid_index = -1; /////////////////////////////////////////////////////////////////////////////////
                    if (sort_order == ASC)
                        sort(cdt->column[index], ASC);
                    else if (sort_order == DESC)
                        sort(cdt->column[index], DESC);
                    else
                        printf("Cet ordre n'existe pas\n");

                    break;
                }

                case 24 : { /* Afficher le contenu d'une colonne triée */
                    char name[20];
                    printf("Quelle colonne triée souhaitez-vous afficher ? ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    print_col_by_index(cdt->column[index]);
                    break;
                }

                case 25 : { /* Afficher le CDataframe en fonction d'une colonne triée */
                    char name[20];
                    printf("En fonction de quelle colonne voulez-vous trier le CDataframe ? ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    print_sort_cdt(cdt, index);
                    break;
                }

                case 26 : { /* Effacer l'index d'une colonne */
                    char name[20];
                    printf("De quelle colonne triée souhaitez-vous supprimer l'index ? ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    erase_index(cdt->column[index]);
                    break;
                }

                case 27 : { /* Vérifier si une colonne possède un index */
                    char name[20];
                    printf("De quelle colonne souhaitez-vous vérifier l'existence d'un index ? ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    if (check_index(cdt->column[index]) == 0)
                        printf("La colonne n'a pas d'index.\n");
                    else if (check_index(cdt->column[index]) == -1)
                        printf("La colonne possède un index mais celui-ci n'est pas valide.\n");
                    else
                        printf("La colonne a un index valide.\n");

                    break;
                }

                case 28 : { /* Mettre à jour un index */
                    char name[20];
                    printf("De quelle colonne souhaitez-vous mettre à jour l'index ? ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    cdt->column[index]->valid_index = -1; //////////////////////////////////////////////////////////////////////////
                    update_index(cdt->column[index]);
                    break;
                }

                case 29 : { /* Faire une recherche dichotomique */
                    char name[20];
                    printf("Dans quelle colonne triée cherchez-vous la valeur ? ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int val;
                    printf("Quelle valeur cherchez vous ? ");
                    scanf("%d", &val);
                    printf("\n");

                    if (search_value_in_column(cdt->column[index], val) == -2)
                        break;
                    else if (search_value_in_column(cdt->column[index], val) == -1)
                        printf("La valeur ne se trouve pas dans la colonne.\n");
                    else
                        printf("La valeur se trouve à la ligne %d.\n", search_value_in_column(cdt->column[index], val) + 1);
                    break;
                }

                case 30 : { /* Ne rien faire */
                    /* Arrêter le programme */
                    return 1;
                }
            }
        }





        /* Si une colonne existe */
        if (existence_col == 1) {
            /* Afficher le menu et demander l'action */
            action = display_menu_2();

            /* Effectuer l'action */
            switch (action) {
                case 1 : { /* Insérer une valeur dans la colonne préalablement créée */
                    int val;
                    printf("Quelle valeur souhaitez-vous insérer dans la colonne ? ");
                    scanf("%d", &val);
                    printf("\n");

                    insert_value(col, val);
                    break;
                }

                case 2 : { /* Supprimer la colonne préalablement créée */
                    delete_column(col);
                    existence_col = 0;
                    break;
                }

                case 3 : { /* Afficher la colonne préalablement créée */
                    print_col(col);
                    break;
                }

                case 4 : { /* Remplir un CDataframe avec une saisie */
                    user_input(cdt);
                    break;
                }

                case 5 : { /* Afficher le CDataframe */
                    print_cdt(cdt);
                    break;
                }

                case 6 : { /* Afficher une colonne du CDataframe */
                    char name[20];
                    printf("Donnez le nom de la colonne que vous souhaitez afficher : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    print_col(cdt->column[index]);
                    break;
                }

                case 7 : { /* Afficher une partie des lignes du CDataFrame */
                    int x, y;

                    do {
                        printf("Donnez le numéro de la ligne de départ (de 1 à %d) : ", number_of_lines(cdt));
                        scanf("%d", &x);
                    } while (x < 1 || x > number_of_lines(cdt));
                    printf("\n");

                    do {
                        printf("Donnez le numéro de la ligne de fin (de %d à %d) : ", x, number_of_lines(cdt));
                        scanf("%d", &y);
                    } while (y < x || y > number_of_lines(cdt));
                    printf("\n");

                    print_lines(cdt, x, y);
                    break;
                }

                case 8 : { /* Afficher une partie des colonnes du CDataframe */
                    int x = -1, y = -1;

                    char name_x[20];
                    printf("Donnez le nom de la colonne de départ : ");
                    scanf("%s", name_x);
                    printf("\n");

                    for (int i = 0; i < cdt->num_columns ; i++) {
                        if (strcmp(cdt->column[i]->title, name_x) == 0) {
                            x = i;
                            break;
                        }
                    }
                    if (x == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    char name_y[20];
                    printf("Donnez le nom de la colonne de fin : ");
                    scanf("%s", name_y);
                    printf("\n");

                    for (int i = x ; i < cdt->num_columns ; i++) {
                        if (strcmp(cdt->column[i]->title, name_y) == 0) {
                            y = i;
                            break;
                        }
                    }
                    if (y == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    print_col_of_cdt(cdt, x, y);
                    break;
                }

                case 9 : { /* Ajouter une ligne de valeurs au CDataFrame */
                    insert_line(cdt);
                    break;
                }

                case 10 : { /* Supprimer une ligne de valeurs du CDataFrame */
                    int index;

                    printf("Quelle ligne souhaitez-vous supprimer (1 à %d) ? ", number_of_lines(cdt));
                    do {
                        scanf("%d", &index);
                    } while (index < 1 || index > number_of_lines(cdt));

                    delete_line(cdt, index - 1);
                    break;
                }

                case 11 : { /* Ajouter une colonne au CDataFrame */
                    insert_column(cdt, col);
                    break;
                }

                case 12 : { /* Supprimer une colonne du CDataFrame */
                    char name[20];
                    printf("Donnez le nom de la colonne que vous souhaitez supprimer : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    delete_col(cdt, index);
                    break;
                }

                case 13 : { /* Renommer le titre d'une colonne du CDataFrame */
                    char name[20];
                    printf("Donnez le nom de la colonne dont vous souhaitez modifier le nom : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    char new_name[20];
                    printf("Quelle nom voulez-vous donner à la colonne ? ");
                    scanf("%s", new_name);
                    printf("\n");

                    printf("\t%d\n", rename_col(cdt, index, new_name));
                    break;
                }

                case 14 : { /* Chercher une valeur dans le CDataFrame */
                    int val;

                    printf("Quelle valeurs cherchez-vous dans le CDataframe ? ");
                    scanf("%d", &val);

                    printf("La valeur apparait %d fois dans le CDataframe.\n", search_value(cdt, val));
                    break;
                }

                case 15 : { /* Remplacer une cellule du CDataFrame */
                    int x;
                    printf("Donnez le numéro de la ligne de la cellule que vous souhaitez modifier (de 1 à %d) : ",
                           number_of_lines(cdt));
                    do {
                        scanf("%d", &x);
                    } while (x < 1 || x > number_of_lines(cdt));
                    printf("\n");


                    char name[20];
                    printf("Donnez le nom de la colonne de la cellule que vous souhaitez modifier : ");
                    scanf("%s", name);
                    printf("\n");


                    int y = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            y = i;
                            break;
                        }
                    }
                    if (y == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int val;
                    printf("Quelle valeur souhaitez-vous ? ");
                    scanf("%d", &val);
                    printf("\n");


                    replace_cell(cdt, x - 1, y, val);
                    printf("\n");
                    break;
                }

                case 16 : { /* Accéder à la valeur d'une cellule du CDataFrame */
                    int x;
                    printf("Donnez le numéro de la ligne de la cellule que vous souhaitez accéder (de 1 à %d) : ",
                           number_of_lines(cdt));
                    do {
                        scanf("%d", &x);
                    } while (x < 1 || x > number_of_lines(cdt));
                    printf("\n");


                    char name[20];
                    printf("Donnez le nom de la colonne de la cellule que vous souhaitez accéder : ");
                    scanf("%s", name);
                    printf("\n");


                    int y = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            y = i;
                            break;
                        }
                    }
                    if (y == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    printf("La valeur à la colonne '%s' et à la ligne %d est : %d.\n", cdt->column[y]->title, x,
                           select_cell(cdt, x - 1, y));
                    break;
                }

                case 17 : { /* Afficher le nom des colonnes du CDataFrame */
                    printf("\n");
                    print_name_col(cdt);
                    break;
                }

                case 18 : { /* Afficher le nombre de lignes du CDataFrame */
                    printf("\nLe CDataframe contient %d lignes.\n\n", number_of_lines(cdt));
                    break;
                }

                case 19 : { /* Afficher le nombre de colonnes du CDataFrame */
                    printf("\nLe CDataFrame contient %d colonnes.\n\n", number_of_cols(cdt));
                    break;
                }

                case 20 : { /* Nombre de cellules égale à une valeur x dans une colonne */
                    char name[20];
                    printf("Donnez le nom de la colonne qui vous intéresse : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules égale à %d est : %d\n\n", x, equal_to(cdt->column[index], x));
                    break;
                }

                case 21 : { /* Nombre de cellules plus grandes qu'une valeur x dans une colonne */
                    char name[20];
                    printf("Donnez le nom de la colonne qui vous intéresse : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules égale à %d est : %d\n\n", x, greater_than(cdt->column[index], x));
                    break;
                }

                case 22 : { /* Nombre de cellules plus petites qu'une valeur x dans une colonne */
                    char name[20];
                    printf("Donnez le nom de la colonne qui vous intéresse : ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules égale à %d est : %d\n\n", x, less_than(cdt->column[index], x));
                    break;
                }

                case 23 : { /* Nombre de cellules égale à une valeur x */
                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules égale à %d est : %d\n\n", x, cell_equal_to(cdt, x));
                    break;
                }

                case 24 : { /* Nombre de cellules plus grandes qu'une valeur x */
                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules supérieures à %d est : %d\n", x, cell_greater_than(cdt, x));
                    break;
                }

                case 25 : { /* Nombre de cellules plus petites qu'une valeur x */
                    int x;
                    printf("Saisir la valeur x : ");
                    scanf("%d", &x);
                    printf("\n");

                    printf("Le nombre de cellules inférieures à %d est : %d\n\n", x, cell_less_than(cdt, x));
                    break;
                }

                case 26 : { /* Trier une colonne */
                    char name[20];
                    printf("Donnez le nom de la colonne de la cellule que vous souhaitez trier : ");
                    scanf("%s", name);
                    printf("\n");

                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }

                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int sort_order;
                    printf("Vous souhaitez trier la colonne dans l'ordre croissant (0) ou décroissant (1) : ");
                    scanf("%d", &sort_order);

                    cdt->column[index]->valid_index = -1; ////////////////////////////////////////////////////////////////////////////////////
                    if (sort_order == ASC)
                        sort(cdt->column[index], ASC);
                    else if (sort_order == DESC)
                        sort(cdt->column[index], DESC);
                    else
                        printf("Cet ordre n'existe pas\n");

                    break;
                }

                case 27 : { /* Afficher le contenu d'une colonne triée */
                    char name[20];
                    printf("Quelle colonne triée souhaitez-vous afficher ? ");
                    scanf("%s", name);
                    printf("\n");

                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    print_col_by_index(cdt->column[index]);
                    break;
                }

                case 28 : { /* Afficher le CDataframe en fonction d'une colonne triée */
                    char name[20];
                    printf("En fonction de quelle colonne voulez-vous trier le CDataframe ? ");
                    scanf("%s", name);
                    printf("\n");

                    /* Déterminer l'index de la colonne */
                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    print_sort_cdt(cdt, index);
                    break;
                }

                case 29 : { /* Effacer l'index d'une colonne */
                    char name[20];
                    printf("De quelle colonne triée souhaitez-vous supprimer l'index ? ");
                    scanf("%s", name);
                    printf("\n");

                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    erase_index(cdt->column[index]);
                    break;
                }

                case 30 : { /* Vérifier si une colonne possède un index */
                    char name[20];
                    printf("De quelle colonne souhaitez-vous vérifier l'existence d'un index ? ");
                    scanf("%s", name);
                    printf("\n");

                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    if (check_index(cdt->column[index]) == 0)
                        printf("La colonne n'a pas d'index.\n");
                    else if (check_index(cdt->column[index]) == -1)
                        printf("La colonne possède un index mais celui-ci n'est pas valide.\n");
                    else
                        printf("La colonne a un index valide.\n");

                    break;
                }

                case 31 : { /* Mettre à jour un index */
                    char name[20];
                    printf("De quelle colonne souhaitez-vous mettre à jour l'index ? ");
                    scanf("%s", name);
                    printf("\n");

                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    cdt->column[index]->valid_index = -1; ///////////////////////////////////////////////////////////////////////////////////////////
                    update_index(cdt->column[index]);
                    break;
                }

                case 32 : { /* Faire une recherche dichotomique */
                    char name[20];
                    printf("Dans quelle colonne triée cherchez-vous la valeur ? ");
                    scanf("%s", name);
                    printf("\n");

                    int index = -1;
                    for (int i = 0; i < cdt->num_columns; i++) {
                        if (strcmp(cdt->column[i]->title, name) == 0) {
                            index = i;
                            break;
                        }
                    }
                    if (index == -1) {
                        printf("Cette colonne n'existe pas !\n");
                        break;
                    }

                    int val;
                    printf("Quelle valeur cherchez vous ? ");
                    scanf("%d", &val);
                    printf("\n");

                    search_value_in_column(cdt->column[index], val);
                    break;
                }

                case 33 : { /* Ne rien faire */
                    /* Arrêter le programme */
                    return 0;
                }
            }
        }

    } while (1);
}

 