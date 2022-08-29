#include <stdio.h>

int main(void)
{
    char buffer[13];

    int i = 50;
    sprintf(buffer, "0%i\n", i);
    printf("%s\n", buffer);

    float f = 50.0;
    sprintf(buffer, "00%.0f\n", f);
    printf("%s\n", buffer);
}