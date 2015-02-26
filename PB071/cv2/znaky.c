#include <stdio.h>

int main() {
    char c = getchar();
    int number;
    unsigned hexNum;

    while( getchar() != '\n' );

    printf( "Znak c: %c\n", c );

    scanf( "%d", &number );
    scanf( "%X", &hexNum );

    printf( "%03i\n", number );
    printf( "0x%X\n", hexNum );

    return 0;
}
