/*
* Author: Penny Silliman
* Date: 2/22/2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 50
#define MAX_LINE_LENGTH 200

int main(const int argc, const char * argv []) {
    // Check if the correct number of arguments is provided
    if(argc != 3){
        printf("Usage: %s <password_file> <hashed_password>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    const char *hashed_password = argv[2];

    // Open the password file for reading
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Error: Unable to open file %s\n", filename);
        return 1;
    }

    char password[MAX_PASSWORD_LENGTH];
    char line[MAX_LINE_LENGTH];
    int found = 0;

    // Read each line from the file
    while(fgets(line, sizeof(line), file) != NULL){
        // Parse the line into username and password
        if(fscanf(line, "%s", password) != 1){
            printf("Error: Malformed line in file\n");
            continue;
        }
        // Compare the hashed password with the one provided
        if (strcmp(password, hashed_password) == 0) {
            printf("Match found for password: %s\n", password);
            found = 1;
            break;
        }
    }
    // Close the file
    fclose(file);

    if(!found){
        printf("No match fonud for the provided hashed password.\n");
    }

    return 0;
}