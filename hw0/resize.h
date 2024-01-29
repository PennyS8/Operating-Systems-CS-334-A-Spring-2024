#ifndef RESIZE_H
#define RESIZE_H

#include <stdlib.h>

typedef struct point{
	int x_cor;
	int y_cor;
	int color;
}point;

void resize(point*** polyline, int* size){
    // Check if arguments are valid
    if(*polyline == NULL || size == NULL || *size <= 0){
        // Handle invalid arguments
        return;
    }

    // Allocate memory for the new array (twice the original size)
    int newSize = *size * 2;
    point** newPolyline = (point**)malloc(newSize * sizeof(point*));

    // check if memory allocation was successful
    if(newPolyline == NULL){
        // handle memory allocation failure
        return;
    }

    // copy and rotate values from the originla array to the new array
    for(int i = 0; i < *size; i++){
        newPolyline[i * 2 + 1] = (point*)malloc(sizeof(point));
        newPolyline[i * 2 + 1]->x_cor = (*polyline)[i]->x_cor;
        newPolyline[i * 2 + 1]->y_cor = (*polyline)[i]->y_cor;
        newPolyline[i * 2 + 1]->color = (i + 1) % 2; // alternating color i and 0
    }

    // doallocate memory of the original array and update pointers
    for(int i = 0; i < *size; i++){
        free((*polyline)[i]);
    }
    free(*polyline);

    *polyline = newPolyline;
    *size = newSize;

}

#endif