#include "krow.h"
#include <stdio.h>

int main(int argc, char** argv) {
    if(argc < 2) {
        fprintf(stdout, "Please provide a file path\n");
        return 1;
    }

    const char* filePath = argv[1];

    OpenFile(filePath);

    return 0;
}
