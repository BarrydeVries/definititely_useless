/*******************************************************************************
 * crack.c
 *
 * CS50
 * Barry de Vries
 *
 * A basic implementation of a function to crack hashed passwords of lenghts up
 * to 4 characters. When wrong input is given the function returns a 1, if the
 * algorithm is unalbe to find the origional password, 2 will be returned.
 ******************************************************************************/
#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

long long power(int k, int n);
int kraken(string hashedww);

// Defines the max lenght of the password to crack
int maxlengteww = 4;

int main(int argc, string argv[])
/* Check the input, then start craking.*/
{
    
    if (argc != 2)
    {
        // return error for wrong input
        printf("Wrong input.\n");
        return 1;
    }

    else
    {
        return kraken(argv[1]);
    }
}

/**
 * Determine the salt value, then try passwords of all possible sizes.
 * Note that we use integers to represent our passwords.
*/
int kraken(string hashedww)
{
    char saltwaarde[2];
    saltwaarde[0] = hashedww[0];
    saltwaarde[1] = hashedww[1];

    // Try different lengths.
    for (int lengteww = 1; lengteww <= maxlengteww; lengteww++)
    {
        // create an array for the password, keep the \0 in mind!
        char wwpoging[lengteww + 1];
        wwpoging[lengteww] = '\0';

        // Loop over all possible passwords
        for (long long wwgenerator = 0; wwgenerator < power(52, lengteww);
             wwgenerator++)
        {
            long long k = wwgenerator;

            // By taking the modulo of powers of 52 of the wwgenerator, passwords are created.
            for (int wwkarakter = 0; wwkarakter < lengteww; wwkarakter++)
            {
                if ((k % 52) < 26)
                {
                    // genereer een hoofdletter
                    wwpoging[wwkarakter] = (k % 26) + 'A';
                }
                else
                {
                    // genereer een kleine letter
                    wwpoging[wwkarakter] = (k % 26) + 'a';;
                }
                k = k / 52;
            }

            // Check for correctness.
            if (!strcmp(crypt(wwpoging, saltwaarde), hashedww))
            {
                printf("%s\n", wwpoging);
                return 0;
            }
        }
    }
    // Return a failure error.
    printf("Het wachtwoord kon niet gekraakt worden.\n");
    return 2;
}

/**
 * A power function for with long long output.
*/
long long power(int k, int n)
{
    long long p = 1;
    for (int i = 0; i < n; i++)
    {
        p = p * k;
    }
    return p;
}
