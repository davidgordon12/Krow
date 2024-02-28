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
            fprintf(stdout, "Invalid file path\n");
            return 1;
        }

        // Get the size of the file
        fseek(file, 0, SEEK_END);
        int fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        if(fileSize > FILE_MAX) {
            fprintf(stdout, "File too large. Must be less than 1024000 bytes\n");
            return 1;
        }

        char* fileBuffer = (char*)malloc(fileSize * sizeof(char));
        if(fileBuffer == NULL) {
            fprintf(stdout, "Not enough memory to open file\n");
            return 1;
        }

        fread(fileBuffer, sizeof(char), fileSize, file);

        OpenFile(filePath, fileBuffer);
    } else {
        fprintf(stdout, "Please provide a file path\n");
        return 1;
    }

    const char* filePath = argv[1];

    return 0;
}
