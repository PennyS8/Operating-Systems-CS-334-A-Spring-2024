#include <stdio.h>
#include <stdlib.h>
#include "resize.h"

void printPoints(struct point** polyLine, int size){
    for(int i = 0; i < size; i++){
        printf("Orig Pts: x:%d, y:%d, c:%d\n",
                polyLine[i]->x_cor, polyLine[i]->y_cor, polyLine[i]->color);
    }
}

void deallocPolyline(struct point** polyLine, int size) {
    printf("size: %d\n", size);
    for(int i = 0; i < size; i++) {
        free(polyLine[i]);
    }
    free(polyLine);
}

int main(int argc, char* argv[]){
    // check command-line args for proper intput
    if (argc != 2){
        fprintf(stderr, "Usage: %s <input size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int size = atoi(argv[1]);
    if(size <= 0){
        fprintf(stderr, "Input size must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    // Dynamically allocate array of point struct pointers
    struct point** polyLine = (struct point**)malloc(size * sizeof(struct point*));

    printf("%d\n", size);
    // Initialize each array slot with a new instance of a dynamically allocated point struct
    for(int i = 0; i < size; i++){
        polyLine[i] = (struct point*)malloc(sizeof(struct point));
        polyLine[i]->x_cor = size - (size-i);
        polyLine[i]->y_cor = size-i;
        polyLine[i]->color = 0;
    }
    printf("done with allocaitons\n");
    // Print original points
    printPoints(polyLine, size);

    // Call resize with the poly-line and the size
    resize(&polyLine, &size);

    // Print the new (automatically resized) array returned from the resize function
    printPoints(polyLine, size);

    // Deallocate the array
    deallocPolyline(polyLine, size);

    return EXIT_SUCCESS;    
}