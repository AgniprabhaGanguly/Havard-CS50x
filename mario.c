#include <cs50.h>
#include <stdio.h>

int get_height(void);
void get_piramid(int H);

int main(void)
{
    int n = get_height();

    get_piramid(n);
}

int get_height(void)
{
    int ht;
    do // asking height of piramid
    {
        ht = get_int("Enter height of piramid :");
    }
    while (ht < 1 || ht > 8);
    return ht;
}

void get_piramid(int H)
{
    for (int i = 1; i <= H; i++)
    {
        // space
        for (int j = 0; j < (H - i); j++)
        {
            printf(" ");
        }
        // left piramid
        for (int k = 0; k < i; k++)
        {
            printf("#");
        }
        // 2 space gap
        printf("  ");
        // right piramid
        for (int l = 0; l < i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
