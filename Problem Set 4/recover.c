#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        char* get_file = argv[1];
        FILE *file = fopen(get_file, "r");
      
        char filename[8];
        int i = 0;
        bool search = true;
        
        unsigned char buffer[512] = {0};

        while (search)
        {
            int byte_num = fread(buffer, sizeof(BYTE), 512, file);
            
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                if (i == 0)
                {
                    sprintf(filename, "%03i.jpg", i);
                    FILE *img = fopen(filename, "w");
                    fwrite(buffer, sizeof(BYTE), 512, img);
                    fclose(img);
                    i++;
                }
                else
                {
                    
                    sprintf(filename, "%03i.jpg", i);
                    FILE *img = fopen(filename, "w");
                    fwrite(buffer, sizeof(BYTE), 512, img);
                    fclose(img);
                    i++;
                }
            }
            else if (byte_num != 512)
            {
                FILE *img = fopen(filename, "a");
                fwrite(buffer, sizeof(BYTE), byte_num, img);
                fclose(img);
                search = false;
            }
            else if (i != 0)
            {
                FILE *img = fopen(filename, "a");
                fwrite(buffer, sizeof(BYTE), 512, img);
                fclose(img);
            }
        }
    }
    
    else
    {
        return 1;
    }
    return 0;
}
