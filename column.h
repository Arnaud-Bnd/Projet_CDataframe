//
// Created by Arnaud Bernard on 28/03/2024.
//

#ifndef PROJET_CDATAFRAME_COLUMN_H
#define PROJET_CDATAFRAME_COLUMN_H


#define REALLOC_SIZE 256


typedef struct {
    char *title;
    int T_Logique;
    int T_Physique;
    int *data;
    unsigned long long *index;
    // Index valid
    // 0 : no index
    // -1 : invalid index
    // 1 : valid index
    int valid_index;
    // direction de tri : Ascendant ou Descendant
    // 0 : ASC
    // 1 : DESC
    int sort_dir;
} COLUMN;


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


/* Value at position x
 * @param1 : Pointer to a column
 * @param2 : Position
 * @return : The value at the position x or 0 if the value doesn't exist
 */
int val_at_pos(COLUMN* col, int pos);


/* Number of value > x
 * @param1 : Pointer to a column
 * @param2 : X
 * @return : Number of value greater than x
 */
int greater_than(COLUMN* col, int x);


/* Number of value < x
 * @param1 : Pointer to a column
 * @param2 : X
 * @return : Number of value less than x
 */
int less_than(COLUMN* col, int x);


/* Number of value = x
 * @param1 : Pointer to a column
 * @param2 : X
 * @return : Number of value equal to x
 */
int equal_to(COLUMN* col, int x);


#endif //PROJET_CDATAFRAME_COLUMN_H
