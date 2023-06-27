// read description

#include <cs50.h>
#include <stdio.h>
#include <math.h>

// calling functions
long get_credit(void);
char checksum(long cred);
int checklen(long cred);
int checkdig(long cred, int len);

int main(void)
{
    // promt for input
    long credit = get_credit();

    // calculate checksum
    char chksum = checksum(credit);

    // check for card length and starting digits
    int len = checklen(credit);
    int dig = checkdig(credit, len);

    // Print AMEX - 15 digits & start w 34/37
    // Print MASTER - 16 digits & start w 51-55
    // Print Visa - 13/16 digits & start w 4
    // Print INVALID if satisfy none.

    if (chksum == true)
    {
        if (len == 13)
        {
            if (dig >= 40 && dig <= 49)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (len == 15)
        {
            if (dig == 34 || dig == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (len == 16)
        {
            if (dig >= 51 && dig <= 55)
            {
                printf("MASTERCARD\n");
            }
            else if (dig >= 40 && dig <= 49)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

// use long since int can only do operations till 32bits. long uses 64bits.
long get_credit(void)
{
    long cred = get_long("Enter your credit card number : ");
    return cred;
}

char checksum(long cred)
{
    long num = cred;
    int i;
    int check1 = 0; // adding all products of every other digits by 2 starting with second to last digit
    int check2 = 0; // adding other digits up
    do
    {
        i = num % 10;
        check2 += i;

        i = num % 100;
        i /= 10;
        i *= 2;

        int j;
        if (i > 9) // when getting a 2 digit number like 6*2=12 , we split both digit and add them up
        {
            j = i % 10; // 2nd digit
            check1 += j;
            j = i / 10; // 1st digit
            check1 += j;
        }
        else
        {
            check1 += i;
        }
        num = num / 100;
    }
    while (num != 0);
    int check = check1 + check2; // finally adding both sum together

    if (check % 10 == 0) // checking last digit of optained number 0 or not
    {
        return true;
    }
    else
    {
        return false;
    }
}

int checklen(long cred) // counting number of digit in the number
{
    int count = 0;
    do
    {
        cred /= 10; // removes last digit
        count += 1;
    }
    while (cred != 0); 
    return count;

}

int checkdig(long cred, int len)
{
    cred = cred / pow(10, len - 2); // to take out first 2 digit of a number, we diving the number by 10^(total no of digit - 2)
    return cred;
}
