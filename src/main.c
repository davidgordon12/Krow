#include <stdio.h>
#include <stdlib.h>

#include "krow.h"

#define FILE_MAX    1024000

int main(int argc, char** argv) {
    if(argc == 1) {
        OpenFile("", "");
    }
    else if(argc == 2) {
        char buffer[FILE_MAX];
        const char* filePath = argv[1];

        FILE* file = fopen(filePath, "r+");
        if(file == NULL) {
            fprintf(stderr, "Invalid file path");
        }

        // Get the size of the file
        fseek(file, 0, SEEK_END);
        int fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        if(fileSize > FILE_MAX) {
            fprintf(stderr, "File too large. Must be less than 1024000 bytes");
        }

        char* fileBuffer = (char*)malloc(fileSize * sizeof(char));
        if(fileBuffer == NULL) {
            fprintf(stderr, "Not enough memory to open file");
        }

        fread(fileBuffer, sizeof(char), fileSize, file);


        OpenFile(filePath, fileBuffer);
    } else {
        fprintf(stderr, "Please provide a file path");
        return 0;
    }

    const char* filePath = argv[1];
}
