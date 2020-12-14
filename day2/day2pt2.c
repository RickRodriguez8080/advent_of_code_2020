#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool check_text_file(FILE *in);
int valid_password_count(FILE *in, char *policy_with_password);
bool password_meets_policy(char *policy_with_password, size_t len);
bool valid_password(char *password, size_t password_length, char letter_to_be_compared, int position1, int position2);

int main(int argc, char** argv) {

    FILE *infile;    
    char current_instruction[40];

    // check for valid input file
    infile = fopen("sample_text", "r");
    bool valid_text_file = check_text_file(infile);

    if (valid_text_file) {
        int total_count = valid_password_count(infile, current_instruction);
        printf("The total number of valid passwords: %d\n", total_count);
    }    

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

// Strips one row consisting of a policy and its password
// Sends the instruction to password_with_policy()
// Increments the counter if the password meets the policy
// Returns the total count of valid passwords
int valid_password_count(FILE *in, char *policy_with_password) {
    
    int count = 0;
    while (fgets(policy_with_password, 40, in) != NULL) {
        
        
        //grab one row of policy/password instructions at a time...
        policy_with_password[strcspn(policy_with_password, "\n")] = '\0';
        size_t len = strlen(policy_with_password);     

        if (password_meets_policy(policy_with_password, len)) {
            count++;
        }
    }    
    return count;
}

//  Strips the policy and password into its constituent parts
//  1. position1 refers to an index - 1 in the array
//  2. position2 refers to an index - 1 in the array
//  3. the letter to be compared and
//  4. the password itself
//  Returns the value of provided to it by valid_password()
bool password_meets_policy(char *policy_with_password, size_t len) {

    // tokenize the policy and password    
    int position1, position2;
    char comparison_letter;
    char *passwordPtr;    
    
    char *tokenPtr;
    tokenPtr = strtok(policy_with_password, " -:");
    position1 = atoi(tokenPtr);
    //printf("%d ", min_value);

    tokenPtr = strtok(NULL, " -:");
    position2 = atoi(tokenPtr);
    //printf("%d ", max_value);

    tokenPtr = strtok(NULL, " -:");
    comparison_letter = *tokenPtr;
    //printf("%c ", comparison_letter);

    tokenPtr = strtok(NULL, " -:");
    passwordPtr = tokenPtr;
    //printf("%s ", passwordPtr);

    size_t password_length = strlen(passwordPtr);
    //printf("%ld ", password_length);

    // check password validity
    if (valid_password(passwordPtr, password_length, comparison_letter, position1, position2)) {
        //printf("Valid\n");
        return true;
    }
    else {
        //printf("Not valid\n");
        return false;
    }
}

// Compares the characters in the password to the letter that needs to be compared.
// If such letter appears at one (and only one) of the indexed position, return true, otherwise false.
bool valid_password(char *password, size_t password_length, char letter_to_be_compared, int position1, int position2) {

    // check that the occurences of the character meets the policy requirement (XOR)
    if (password[position1 - 1] == letter_to_be_compared ^ password[position2 - 1] == letter_to_be_compared) {
        return true;
    } 
    else {
        return false;
    }
}
