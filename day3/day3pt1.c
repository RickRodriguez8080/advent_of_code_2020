#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ROW 323
#define COL 31

bool check_text_file(FILE *in);
void text_to_multi_d_array(FILE *in, char array[][COL], unsigned length);
int tree_counter(char array[][COL]);
void print_forest(char array[][COL]);

int main(int argc, char **argv) {

    FILE *infile;
    char forest[ROW][COL];
    
    // check for valid input file
    infile = fopen("sampletext", "r");
    bool valid_text_file = check_text_file(infile);

    // get length of one row of forest
    unsigned col_length = COL;
    
    // convert the file to a multi-dimensional array
    text_to_multi_d_array(infile, forest, col_length);
    
    // time to count the trees we hit as we traverse the forest...
    int count = tree_counter(forest);

    // display the forest with hits ('T') and misses ('N') with tree count
    print_forest(forest);
    printf("Tree hit count: %d\n", count);

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


// tree_counter() iterates through a 2D array in a 1 down / 3 right slope
// and counts any '#' as a hit and labels it 'T'.  A miss is labeled 'N'.
int tree_counter(char array[][COL]) {

    // begin determining how many trees you will hit when sledding 1 down/3 right

    unsigned row = 0;
    unsigned col = 0;
    int tree_counter = 0;

    if (array[row][col] == '#') {               // check initial position for a tree
        ++tree_counter;
    }
    
    ++row;                                      // move to the next row
    int right_counter = 0;                      // this counter is for moving to thee right 3 places

    while (row < ROW) {                         // as you are traversing the forest in the downward direction...
        while (right_counter < 3) {             // begin tree checking moving in the rightward direction

            ++col;                              // move one spot to the right of the current row

            if (col == COL) {                   // if you reach the end of the current forest row
                col = 0;                        // start at the beginning of the same row
            }
            ++right_counter;                    // add to the rightward moving counter
        }

        right_counter = 0;                      // once done with moving to the right, make sure to reset the rightward moving counter for the next iteration

        if (array[row][col] == '#') {           // check if there is a tree at the current array position
            array[row][col] = 'T';              // display that a tree was hit at position
            ++tree_counter;
        }
        else {
            array[row][col] = 'N';              // display that there was no tree at position
        }
        
        ++row;                                  // go to the next row
    }

    return tree_counter;
}

// print_forest() displays how the forest was traversed,
// printing any hits ('T') and misses ('N')
void print_forest(char array[][COL]) {

    for(unsigned i = 0; i < ROW - 1; i++) {
        for(unsigned j = 0; j < COL; j++) {
            printf("%c", array[i][j]);
        }
        printf("\n");
    }   
}