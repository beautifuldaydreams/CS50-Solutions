#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");          
                return 1;
            }
        printf("Success\n");
        string key = argv[1];
        
        printf("%i\n", atoi(key)%26);
        
        string plaintext = get_string("plaintext: ");
        
        for (int x = 0, n = strlen(plaintext); x < n; x++)
            if (plaintext[x] > 96 && plaintext[x] < 123)
            {
                if (plaintext[x] + (atoi(key)%26) > 122)
                {
                    plaintext[x] = plaintext[x] - 26 + (atoi(key)%26);
                }
                else
                {
                    plaintext[x] = plaintext[x] + (atoi(key)%26);
                }
            }
            else if ((plaintext[x] > 64 && plaintext[x] < 91))
            {
                if (plaintext[x] + (atoi(key)%26) > 90)
                {
                    plaintext[x] = plaintext[x] - 26 + (atoi(key)%26);
                }
                else
                {
                    plaintext[x] = plaintext[x] + (atoi(key)%26);
                }
            }
            else
            {
                plaintext[x] = plaintext[x];
            }
        
        printf("ciphertext: ");
        for (int x = 0, n = strlen(plaintext); x < n; x++)
        {
            printf("%c", plaintext[x]);
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        exit(1);
        return 1;
    }
    printf("\n");
}
