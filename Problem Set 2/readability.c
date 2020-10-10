#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void)
{
    float letters = 0;
    float words = 1;
    float sentences = 0;
    
    string text = get_string("Text: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
        {
            letters += 1;
        }
        if (text[i] == 32)
        {
            words += 1;
        }
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences += 1;
        }
    }
    
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;

    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
    
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}
