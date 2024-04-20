#include <stdio.h>
#include "column.h"

int main() {
    COLUMN *mycol = create_column("My column");
    printf("%s\n", mycol->title);
    int val = 5;
    if (insert_value(mycol, val))
        printf("Value added successfully to my column\n");
    else
        printf("Error adding value to my column\n");

    //for (int i = 0; i)
    return 0;
}

