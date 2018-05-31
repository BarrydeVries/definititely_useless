/*******************************************************************************
 * crack.c
 *
 * CS50
 * Barry de Vries
 *
 * De functie vind bij een gehashed wachtwoord het oorspronkelijke wachtwoord,
 * voor wachtwoorden van lengte vier. Bij foute input zal main een 1 als output
 * geven, bij succes een 0 en wanneer het script onsuccesvol is in het kraken
 * van de input, is de output van main een 2.
 ******************************************************************************/
#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

long long power(int k, int n);
int kraken(string hashedww);

// hier wordt de maximale lengte van het te kraken wachtwoord gedefinieerd
int maxlengteww = 4;

int main(int argc, string argv[])
{
    // checken of er precies één hashed wachtwoord wordt meegegeven
    if (argc != 2)
    {
        printf("Uw input heeft het verkeerde formaat.\n");
        return 1;
    }
    // beginnen met het kraken
    else
    {
        return kraken(argv[1]);
    }
}

/**
 * De functie bepaald eerst de salt waarde, waarna voor iedere mogelijke lengte
 * alle mogelijke wachtwoorden wordt gegenereerd en geverifieerd.
*/
int kraken(string hashedww)
{
    char saltwaarde[2];
    saltwaarde[0] = hashedww[0];
    saltwaarde[1] = hashedww[1];

    // loop over de lengte van het wachtwoord
    for (int lengteww = 1; lengteww <= maxlengteww; lengteww++)
    {
        // hierin worden de poging gecreëerd
        char wwpoging[lengteww + 1];
        wwpoging[lengteww] = '\0';

        // deze loop loopt over alle mogelijke wachtwoorden van de geven lengte
        for (long long wwgenerator = 0; wwgenerator < power(52, lengteww);
             wwgenerator++)
        {
            long long k = wwgenerator;

            // we passen de poging array aan voor de volgende poging op basis
            // van de waarde van de wwgenerator modulo machten van 52, het
            // aantal kleine, en hoofdletters
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

            // de check of het wachtwoord correct is
            if (!strcmp(crypt(wwpoging, saltwaarde), hashedww))
            {
                printf("%s\n", wwpoging);
                return 0;
            }
        }
    }
    printf("Het wachtwoord kon niet gekraakt worden.\n");
    return 2;
}

/**
 * Een power functie.
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