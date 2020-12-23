#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ROW 323
#define COL 31

bool check_text_file(FILE *in);
void text_to_multi_d_array(FILE *in, char array[][COL], unsigned length);
int tree_product(char array[][COL], int right_direction[], int down_direction[], int right_array_size, int down_array_size);
int tree_counter(char array[][COL], int right_direction, int down_direction);

int main(int argc, char **argv) {

    FILE *infile;
    char forest[ROW][COL];
    int right_traverse[5] = {1, 3, 5, 7, 1};
    int down_traverse[5] = {1, 1, 1, 1, 2};    
    
    // check for valid input file
    infile = fopen("sampletext", "r");
    bool valid_text_file = check_text_file(infile);

    // get lengths of arrays
    unsigned col_length = COL;
    int right_array_size = sizeof right_traverse / sizeof right_traverse[0];
    int down_array_size = sizeof down_traverse / sizeof down_traverse[0];
    
    // convert the file to a multi-dimensional array
    text_to_multi_d_array(infile, forest, col_length);
    
    // get product of all tree hit scenarios...
    int product = tree_product(forest, right_traverse, down_traverse, right_array_size, down_array_size);

    printf("Tree product count: %d\n", product);
    fclose(infile);

    return 0;
}


//  Checks that the file exists and can be opened
bool check_text_file(FILE *in) {    
        
    if (in == NULL) {
        fprintf(stderr, "Error. File name does not exist.");
        return 0;
    }
    return true;
}


// text_to_multi_d_array() copies the contents of a file, character
// by character, to a 2D array.  Each line in the file is copied
// onto a new row in the 2D array
void text_to_multi_d_array(FILE *in, char array[][COL], unsigned length) {

    char line[length];
    unsigned row = 0;    

    while(fgets(line, 40, in) != NULL) {            // while copying another line of characters to the 1D array
    
        line[strcspn(line, "\n")] = '\0';           // strip the newline

        for(unsigned i = 0; i < length; ++i) {      // copy the contents of the 1D array to the current row of the 2D array
            array[row][i] = line[i];
        }
        ++row;                                      // go to the next row of the 2D array
    }
}

// tree_product() collects tree hit counts from a series of given slopes and returns the product
int tree_product(char array[][COL], int right_direction[], int down_direction[], int right_array_size, int down_array_size) {

    int tree_count = 0;
    int product = 0;        

    int i = 0;
    while (i < down_array_size && i < right_array_size) {                           // while there is a valid vertical and horizontal value for a slope...
        
        if (i == 0) {                                                               // if it is the first of the tree counts...
            product = tree_counter(array, right_direction[i], down_direction[i]);   // simply assign it
            //printf("Iteration %d: %d\n", i, product);
            ++i;
        } else {
            tree_count = tree_counter(array, right_direction[i], down_direction[i]);    // multiplying all other tree counts
            //printf("Iteration %d: %d\n", i, tree_count);
            product *= tree_count;
            ++i;
        }
    }

    return product;
}

// tree_counter() iterates through a 2D array in a down / right slope
// and counts any '#' as a hit.
int tree_counter(char array[][COL], int right_direction, int down_direction) {

    // begin determining how many trees you will hit when sledding down/right

    unsigned row = 0;
    unsigned col = 0;
    int tree_counter = 0;

    if (array[row][col] == '#') {               // check initial position for a tree
        ++tree_counter;
    }
    
    row = down_direction;                       // move to the next instructed row
    int right_counter = 0;                      // this counter is for moving to the right the given amount of places

    while (row < ROW) {                         // as you are traversing the forest in the downward direction...
        while (right_counter < right_direction) {   // begin moving in the rightward direction...
            ++col;                              // move one spot to the right of the current row

            if (col == COL) {                   // if you reach the end of the current forest row
                col = 0;                        // start at the beginning of the same row
            }
            ++right_counter;                    // add to the rightward moving counter
        }

        right_counter = 0;                      // once done with moving to the right, make sure to reset the rightward moving counter for the next iteration

        if (array[row][col] == '#') {           // check if there is a tree at the current position
            ++tree_counter;
        }
        
        row += down_direction;                   // go to the next instructed row
    }

    return tree_counter;
}
