#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // do while, keep asking till get the right answer

    int h;
    int i;
    int j;

    do
    {
        h = get_int("height? (must be 1 to 8) ");
    }
    while (h < 1 || h > 8);

    // print according to the int
    // print column
    for (i = 1; i < h + 1; i += 1)
    {
        // print row - number of space
        for (j = i; j < h; j += 1)
        {
            printf(" ");
        };

        // print row - number of #
        for (j = h - i; j < h; j += 1)
        {
            printf("#");
        };
        printf("\n");
    };


}