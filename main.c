#include <stdio.h>
#include "data.h"

int main() {
    COLUMN *mycol = create_column("My column");
    printf("%s\n", mycol->title);
    return 0;
}

