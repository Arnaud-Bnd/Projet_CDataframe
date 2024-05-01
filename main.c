#include <stdio.h>
#include <string.h>
#include "column.h"
#include "cdataframe.h"
#include "features.h"

int main() {
    COLUMN *mycol = create_column("sorted column");
    int a = 52;
    int b = 44;
    int c = 15;
    int d = 18;
    insert_value(mycol, a);
    insert_value(mycol, b);
    insert_value(mycol, c);
    insert_value(mycol, d);
    printf("Column content before sorting : \n");
    print_col(mycol);
    mycol->valid_index = -1;
    sort(mycol,ASC);
    printf("Column content after sorting : \n");
    print_col_by_index(mycol);

    printf("\nÉtat de l'index : %d\n", check_index(mycol));

    erase_index(mycol);
    mycol->valid_index = -1;

    printf("\nÉtat de l'index : %d\n", check_index(mycol));

    update_index(mycol);

    printf("\nÉtat de l'index : %d\n", check_index(mycol));

    switch (search_value_in_column(mycol, 19)) {
        case -1 :{
            printf("Column not sorted\n");
            break;
        }
        case 0 :{
            printf("Value not found\n");
            break;
        }
        case 1 :{
            printf("Value found\n");
            break;
        }
    }


    /*
    sort(col, ASC);
    */

    /*
    printf("\n");
    for (int i = 0 ; i < col->T_Logique ; i++)
        printf("[%llu]\t\t%d\n", col->index[i], col->data[i]);
    */

    return 0;
}

 