#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue_copy = image[i][j].rgbtBlue;
            float green_copy = image[i][j].rgbtGreen;
            float red_copy = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = round((blue_copy + green_copy + red_copy)/((float)3));
            image[i][j].rgbtGreen = round((blue_copy + green_copy + red_copy)/((float)3));
            image[i][j].rgbtRed = round((blue_copy + green_copy + red_copy)/((float)3));
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue_copy = (float)image[i][j].rgbtBlue;
            float green_copy = (float)image[i][j].rgbtGreen;
            float red_copy = (float)image[i][j].rgbtRed;

            int red, green, blue;

            blue = round(.272 * red_copy + .534 * green_copy + .131 * blue_copy);
            green = round(.349 * red_copy + .686 * green_copy + .168 * blue_copy);
            red = round(.393 * red_copy + .769 * green_copy + .189 * blue_copy);

            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (red > 255)
            {
                red = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int ori_blue[width];
        int ori_green[width];
        int ori_red[width];
        for (int j = 0; j < width; j ++)
        {
            ori_blue[j] = image[i][j].rgbtBlue;
            ori_green[j] = image[i][j].rgbtGreen;
            ori_red[j] = image[i][j].rgbtRed;
        }
        for (int j = 0; j < width; j ++)
        {
            image[i][j].rgbtBlue = ori_blue[width - 1 - j];
            image[i][j].rgbtGreen =  ori_green[width - 1 - j];
            image[i][j].rgbtRed =  ori_red[width - 1 - j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float ori_blue[height][width];
    float ori_green[height][width];
    float ori_red[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            ori_blue[i][j] = (float)image[i][j].rgbtBlue;
            ori_green[i][j] = (float)image[i][j].rgbtGreen;
            ori_red[i][j] = (float)image[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            float red = 0;
            float green = 0;
            float blue = 0;
            float counter = 0;
            
            blue += ori_blue[i][j];
            green += ori_green[i][j];
            red += ori_red[i][j]; 
            counter++;
            
            
            if (j < width - 1)
            {
                blue += ori_blue[i][j + 1];
                green += ori_green[i][j + 1];
                red += ori_red[i][j + 1]; 
                counter++;
            }
            
            if (i < height - 1)
            {
                blue += ori_blue[i + 1][j];
                green += ori_green[i + 1][j];
                red += ori_red[i + 1][j]; 
                counter++;
            }
            
            if (i > 0)
            {
                blue += ori_blue[i - 1][j];
                green += ori_green[i - 1][j];
                red += ori_red[i - 1][j]; 
                counter++;
            }
            
            if (j > 0)
            {
                blue += ori_blue[i][j - 1];
                green += ori_green[i][j - 1];
                red += ori_red[i][j - 1]; 
                counter++;
            }
            
            if (i < height - 1 && j < width - 1)
            {
                blue += ori_blue[i + 1][j + 1];
                green += ori_green[i + 1][j + 1];
                red += ori_red[i + 1][j + 1]; 
                counter++;
            }
            
            if (i < height - 1 && j > 0)
            {
                blue += ori_blue[i + 1][j - 1];
                green += ori_green[i + 1][j - 1];
                red += ori_red[i + 1][j - 1]; 
                counter++;                 
            }
            
            if (i > 0 && j > 0)
            {
                blue += ori_blue[i - 1][j - 1];
                green += ori_green[i - 1][j - 1];
                red += ori_red[i - 1][j - 1]; 
                counter++;                 
            }
            
            if (i > 0 && j < width - 1)
            {
                blue += ori_blue[i - 1][j + 1];
                green += ori_green[i - 1][j + 1];
                red += ori_red[i - 1][j + 1]; 
                counter++;                 
            }
            
            image[i][j].rgbtRed = round(red/counter);
            image[i][j].rgbtGreen = round(green/counter);
            image[i][j].rgbtBlue = round(blue/counter);
        }
    }
    return;
}
