#include <stdio.h>

int main() {
    unsigned int x = 1;              // integer with value 1
    char *c = (char*)&x;             // interpret its address as a char pointer

    if (*c) {
        printf("System is Little Endian\n");
    } else {
        printf("System is Big Endian\n");
    }

    return 0;
}
