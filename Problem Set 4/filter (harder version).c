#include "helpers.h"
#include <math.h>
#include <stdbool.h>

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

// Detect edges

bool is_valid_pixel(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}
    
int cap(float x)
{
    return (x < 255)? (x) : 255;
}
    
RGBTRIPLE calculate_gx_gy(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    float gx_green = 0, gx_blue = 0, gx_red = 0;
    float gy_green = 0, gy_blue = 0, gy_red = 0;
    int sobel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    for (int k = -1; k < 2; k++)
    {
        for (int n = -1; n < 2; n++)
        {
            if (is_valid_pixel(i+k, j+n, height, width))
            {
                int x = sobel[k + 1][n + 1];
                gx_green += x * image[i+k][j+n].rgbtGreen;
                gx_blue += x * image[i+k][j+n].rgbtBlue;
                gx_red += x * image[i+k][j+n].rgbtRed;
                
                int y = sobel[n + 1][k + 1];
                gy_green += y * image[i+k][j+n].rgbtGreen;
                gy_blue += y * image[i+k][j+n].rgbtBlue;
                gy_red += y * image[i+k][j+n].rgbtRed;
            }
        }
    }
    
    RGBTRIPLE pixel;
    pixel.rgbtGreen = cap(round(sqrt(gx_green * gx_green + gy_green * gy_green)));
    pixel.rgbtRed = cap(round(sqrt(gx_red * gx_red + gy_red * gy_red)));
    pixel.rgbtBlue = cap(round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue)));
    return pixel;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE final[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
            final[i][j] = calculate_gx_gy(i, j, height, width, image);
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = final[i][j];
        }
    }
    return;
}
