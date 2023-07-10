#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int CLIn(string para);

int main(void)
{
    string inp = get_string("Enter a paragraph : ");

    // calculate Coleman Liau Index
    int ind = CLIn(inp);

    // print grades

    // important : instead of using copy paster to print 16 different cases for switch or tediously long if else statement which would be a
    // bad design i instead used the help of newly learned array to tackle this and make the code shorter.

    int grades[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    if (ind <= 0)
    {
        printf("Before Grade 1\n");
    }
    else if (ind > 0 && ind < 17)
    {
        printf("Grade %i\n", grades[ind]);
    }
    else
    {
        printf("Grade 16+\n");
    }
}


int CLIn(string para)
{
    // Calculate no of words, letters and sentences.
    int len =  strlen(para);

    int letters = 0;
    int words = 1;
    int sentcs = 0; // counting no of sentences

    for (int i = 0; i < len; i++) // itterate through the string inputted by user
    {
        char x = para[i];
        if (isalpha(x))
        {
            letters += 1;
        }
        else if (isblank(x))
        {
            words += 1;
        }
        else
        {
            switch (x)
            {
                case '.':
                    sentcs += 1;
                    break;
                case '!':
                    sentcs += 1;
                    break;
                case '?':
                    sentcs += 1;
                    break;
            }
        }
    } // end of for loop

    // INDEX calculation
    int L = (letters * 100) / words; // no of letters per 100 words***
    int S = (sentcs * 100) / words;
    float indexf = (0.0588 * L) - (0.296 * S) - 15.8;
    int index = round(indexf);
    return index;
}
