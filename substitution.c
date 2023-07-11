#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// function calling
int validate(string argument[]);
void encipher(string ptext, string KEY);

// main code
int main(int argc, string argv[])
{
    if (argc == 2) // user did enter only 1 key ie argv has only 2 inputs, 1 file name & 1 input.
    {
        // get and validate key & print and return error for invalid key
        int ec = validate(argv); // ec = error code
        if (ec == 1)
        {
            return 1;
        }
        else
        {
            // Ask user for plaintext
            string org = get_string("plaintext :");

            // encipher plaintext and print cyphertext
            string key = argv[1];
            encipher(org, key);
        }
    }
    else if (argc == 1) // user did not enter anything
    {
        printf("./substitution KEY\n");
        return 1;
    }
    else
    {
        printf("Enter only 1 line of KEY w/o spaces!\n");
        return 1;
    }
}

// function 1

int validate(string argument[])
{
    string key = argument[1];
    int len = strlen(key);
    if (len == 26)
    {
        for (int i = 0; i < len; i++) // itterate through the KEY
        {
            if (isalpha(key[i])) // check for if character is alphabetic
            {
                for (int j = 0; j < len; j++) // check for duplicate character
                {
                    if (i == j) // pointer is on the same position
                    {
                        continue;
                    }
                    else
                    {
                        if (key[i] == key[j])  // pointer of both loop different still character same ie duplicate.
                        {
                            printf("Key must not contain repeated characters.\n");
                            return 1;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
            else
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
        }
        return 0; // if everything goes correct.
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
}

// function 2

void encipher(string ptext, string KEY)
{
    int len = strlen(ptext);
    char cipher[len + 1];   // declaring a array of character ie string
    cipher[len] = '\0';    // putting string terminator so  c can process it as string.

    for (int i = 0; i < len; i++)
    {
        if (islower(ptext[i]))
        {
            int asc = ptext[i];  // takes out ascii value of character.
            asc = asc - 97;      // 97 is ascii no of small a.
            cipher[i] = tolower(KEY[asc]);
        }
        else if (isupper(ptext[i]))
        {
            int asc = ptext[i];
            asc = asc - 65 ;    // 65 is ascii no of capital A
            cipher[i] = toupper(KEY[asc]);
        }
        else
        {
            cipher[i] = ptext[i];
        }
    }
    printf("ciphertext: %s\n", cipher); //Printing cyphertext
}
