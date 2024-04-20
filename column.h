//
// Created by Arnaud Bernard on 28/03/2024.
//

#ifndef PROJET_CDATAFRAME_COLUMN_H
#define PROJET_CDATAFRAME_COLUMN_H

typedef struct {
    char *title;
    int T_Logique;
    int T_Physique;
    int *data;
} COLUMN;

#define REALLOC_SIZE 256

/* Create a column
 * @param1 : Column title
 * @return : Pointer to created column
 */
COLUMN *create_column(char* title);

/* Add a new value to a column
 * @param1 : Pointer to a column
 * @param2 : The value to be added
 * @return : 1 if the value is added 0 otherwise
 */
int insert_value(COLUMN* col, int value);

/* Free allocated memory
 * @param1 : Pointer to a column
 */
void delete_column(COLUMN *col);

/* Print a column content
 * @param1 : Pointer to a column
 */
void print_col(COLUMN* col);

/* Number of occurrences
 *  @param1 : Pointer to a column
 *  @param2 : Value to count
 *  @return : Number of occurrences of the value
 */
int number_occ(COLUMN* col, int value);

#endif //PROJET_CDATAFRAME_COLUMN_H
