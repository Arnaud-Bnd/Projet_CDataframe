//
// Created by Arnaud Bernard on 20/04/2024.
//

#ifndef PROJET_CDATAFRAME_CDATAFRAME_H
#define PROJET_CDATAFRAME_CDATAFRAME_H


#include "column.h"


typedef struct {
    char *title;
    int num_columns;
    COLUMN **column;
} CDATAFRAME;


/* Create a CDataframe
 * @param1 : CDataframe title
 * @return : Pointer to created column
 */
CDATAFRAME *create_cdataframe(char* title);


/* Insert user input in a CDataframe
 * @param1 : Pointer to a CDataframe
 */
void user_input(CDATAFRAME* cdt);


/* Hard filling of CDataframe */
CDATAFRAME *hard_filling();


/* Print a CDataframe content
 * @param1 : Pointer to a CDataframe
 */
void print_cdt(CDATAFRAME* cdt);


/* Print lines of the CDataframe
 * @param1 : Pointer to a CDataframe
 * @param2 : Starting line number
 * @param3 : End line number
 */
void print_lines(CDATAFRAME* cdt, int x, int y);


/* Print columns of the CDataframe
 * @param1 : Pointer to a CDataframe
 * @param2 : Starting column number
 * @param3 : End column number
 */
void print_col_of_cdt(CDATAFRAME* cdt, int x, int y);


/* Insert line in the CDataframe
 * @param1 : Pointer to a CDataframe
 */
void insert_line(CDATAFRAME* cdt);


/* Delete line in the CDataframe
 * @param1 : Pointer to a CDataframe
 * @param2 : Number of the line to be deleted
 * @return : 1 if the line is deleted 0 otherwise
 */
int delete_line(CDATAFRAME* cdt, int index);


/* Add a new column to a CDataframe
 * @param1 : Pointer to a CDataframe
 * @param2 : Pointer to a column to be added
 * @return : 1 if the column is added 0 otherwise
 */
int insert_column(CDATAFRAME* cdt, COLUMN* column);


/* Delete column in the CDataframe
 * @param1 : Pointer to a CDataframe
 * @param2 : Number of the column to be deleted
 * @return : 1 if the column is deleted 0 otherwise
 */
int delete_col(CDATAFRAME* cdt, int index);


/* Rename a CDataframe column title
 * @param1 : Pointer to a CDataframe
 * @param2 : Number of the column to be change
 * @return : 1 if the column is renamed 0 otherwise
 */
int rename_col(CDATAFRAME *cdt, int index, char *new_name);


/* Search value in the CDataframe
 * @param1 : Pointer to a CDataframe
 * @param2 : Value we search
 * @return : Number of times the value appears
 */
int search_value(CDATAFRAME* cdt, int value);


/* Select a cell
 * @param1 : Pointer to a CDataframe
 * @param2 : Index of the line
 * @param3 : Index of the column
 * @return : Value in the cell
 */
int select_cell(CDATAFRAME* cdt, int index_l, int index_c);


/* Replace a cell
 * @param1 : Pointer to a CDataframe
 * @param2 : Index of the line
 * @param3 : Index of the column
 * @param4 : The value we want
 * @return : 1 replacement successful otherwise 0
 */
int replace_cell(CDATAFRAME* cdt, int index_l, int index_c, int value);


/* Print names of columns
 * @param1 : Pointer to a CDataframe
 */
void print_name_col(CDATAFRAME* cdt);


/* Number of lines
 * @param1 : Pointer to a CDataframe
 * @return : Number of lines in the CDataframe
 */
int number_of_lines(CDATAFRAME* cdt);


/* Number of columns
 * @param1 : Pointer to a CDataframe
 * @return : Number of columns in the CDataframe
 */
int number_of_cols(CDATAFRAME* cdt);


/* Number of cells equal to x
 * @param1 : Pointer to a CDataframe
 * @param2 : X
 * @return : Number of cells equal to x
 */
int cell_equal_to(CDATAFRAME* cdt, int x);

/* Number of cells greater than x
 * @param1 : Pointer to a CDataframe
 * @param2 : X
 * @return : Number of cells greater than x
 */
int cell_greater_than(CDATAFRAME* cdt, int x);


/* Number of cells less than x
 * @param1 : Pointer to a CDataframe
 * @param2 : X
 * @return : Number of cells less than x
 */
int cell_less_than(CDATAFRAME* cdt, int x);


#endif //PROJET_CDATAFRAME_CDATAFRAME_H
