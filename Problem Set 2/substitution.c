#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // checking the number of arguments passed on the command line
    if (argc == 2)
    {
        // checking if the number of characters passed in the first command line argument is equal to 26
        if (strlen(argv[1]) == 26)
        {
            // checking each letter against all successive letters for double-ups
            for (int i = 0; i < 26; i++)
            {
                for (int j = i + 1; j < 26; j++)
                {
                    if (argv[1][i] == argv[1][j])
                    {
                        printf("Invalid key. Try again with no digits repeating.\n");
                        return 1;                        
                    }
                }
                // checking if each char in arg is a letter
                if (!isalpha(argv[1][i]))
                {
                    printf("Invalid key. Try again.\n");
                    return 1;                         
                }
            }
            // getting user input
            string plaintext = get_string("plaintext: ");
            for (int i = 0, n = strlen(plaintext); i < n; i++)
            {
                // if lowercase, swap out letter for corresponding char in key 
                if (plaintext[i] > 96 && plaintext[i] < 123)
                {
                    plaintext[i] = tolower(argv[1][plaintext[i] - 97]);
                }
                // if lowercase, swap out letter for corresponding char in key 
                else if ((plaintext[i] > 64 && plaintext[i] < 91))
                {
                    plaintext[i] = toupper(argv[1][plaintext[i] - 65]);
                }
            }
            printf("ciphertext: %s\n", plaintext);
            return 0;
        }
        else
        {
            printf("Invalid key. Key must be 26 digits.\n");
            return 1;
        }
    }
    else
    {
        printf("Invalid key. Try again.\n");
        return 1;
    }
}
