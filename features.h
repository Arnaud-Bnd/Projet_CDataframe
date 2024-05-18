//
// Created by Arnaud Bernard on 29/04/2024.
//

#ifndef PROJET_CDATAFRAME_FEATURES_H
#define PROJET_CDATAFRAME_FEATURES_H


#include "cdataframe.h"

#define ASC 0
#define DESC 1

/* Sort a column according to a given order
 * @param1 : Pointer to the column to sort
 * @param2 : Sort type (ASC or DESC)
 */
void sort(COLUMN *col, int sort_dir);


/* Quicksort
 * @param1 : Pointer to the column to sort
 * @param2 : Left terminal
 * @param3 : Right terminal
 */
void quicksort(int *tab, int left, int right);

/* Partition
 * @param1 : Pointer to the column to sort
 * @param2 : Left terminal
 * @param3 : Right terminal
 */
int partition(int *tab, int left, int right);


/* Print a CDataframe content
 * @param1 : Pointer to a CDataframe
 */
void print_sort_cdt(CDATAFRAME *cdt, int index);


/* Display the content of a sorted column
 * @param1 : Pointer to a column
 */
void print_col_by_index(COLUMN *col);


/* Remove the index of a column
 * @param1 : Pointer to a column
 */
void erase_index(COLUMN *col);


/* Check if an index is correct
 * @param1 : Pointer to a column
 * @return :  0 : index not existing,
             -1 : the index exists but invalid,
              1 : the index is correct
 */
int check_index(COLUMN *col);


/* Update the index
 * @param1 : Pointer to a column
 */
void update_index(COLUMN *col);


/* Check if a value exist in a column
 * @param1 : Pointer to a column
 * @param2 : Pointer to the value to search
 * @return : -1 : column not sorted
              0 : value not found
              1 : value found
*/
int search_value_in_column(COLUMN *col, int val);


/* Display menu 1
 * (without column created)
 */
int display_menu_1();


/* Display menu 2
 * (with column created)
 */
int display_menu_2();


#endif //PROJET_CDATAFRAME_FEATURES_H
