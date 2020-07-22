#include "helpers.h"
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // get average of rgb value of each pixel
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;
            float avgr = (float)(r + g + b) / 3;
            int avg = round(avgr);
            // set avg for rgb values
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE ib = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = ib;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary storage
    RGBTRIPLE temp[height][width];

    // Copying the image to keep an unaltered version to loop over
    memcpy(temp, image, sizeof(RGBTRIPLE) * height * width);

    // Iterate over every row of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over every column of the image
        for (int j = 0; j < width; j++)
        {
            // Initiate average counter at 0.0
            // Gotta avoid the truncated integer problem
            float average = 0.0;
            // Initiate RGB values at 0
            int red = 0;
            int green = 0;
            int blue = 0;

            // Iterate over rows around current row
            for (int k = -1; k <= 1; k++)
            {
                // Iterate over columns around current column
                for (int l = -1; l <= 1; l++)
                {
                    // If current row + next row are within bounds
                    // If current column + next column are within bounds
                    if (i + k != height &&
                        i + k != -1 &&
                        j + l != width &&
                        j + l != -1)
                    {
                        // Update RGB values to the sum both pixels' RGB values
                        red += temp[i + k][j + l].rgbtRed;
                        green += temp[i + k][j + l].rgbtGreen;
                        blue += temp[i + k][j + l].rgbtBlue;
                        // Increment average by one for one pixel in the sum
                        average++;
                    }
                }
            }
            // Set each RGB values to their blurred values
            image[i][j].rgbtRed = round(red / average);
            image[i][j].rgbtGreen = round(green / average);
            image[i][j].rgbtBlue = round(blue / average);
        }
    }
    return;
}

// stops max value at 255 preventing overflow
int limit(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //create temporary values to store the calculations
    float sumBlueY;
    float sumGreenY;
    float sumRedY;
    float sumBlueX;
    float sumGreenX;
    float sumRedX;
    float modifierX;
    float modifierY;

    //create a temporary table of colors to not alter the calculations
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //Resets values for every pixel
            sumBlueY = 0.0;
            sumGreenY = 0.0;
            sumRedY = 0.0;
            sumBlueX = 0.0;
            sumGreenX = 0.0;
            sumRedX = 0.0;

            // sums values of the pixel and 8 neighboring ones after applying a modifier, skips iteration if it goes outside the pic
            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }

                    // calculates modifiers for vertical and horizantal borders
                    modifierX = (k + 1 * k - k * abs(h));
                    modifierY = (h + 1 * h - h * abs(k));

                    sumBlueX += image[j + k][i + h].rgbtBlue * modifierX;
                    sumGreenX += image[j + k][i + h].rgbtGreen * modifierX;
                    sumRedX += image[j + k][i + h].rgbtRed * modifierX;

                    sumBlueY += image[j + k][i + h].rgbtBlue * modifierY;
                    sumGreenY += image[j + k][i + h].rgbtGreen * modifierY;
                    sumRedY += image[j + k][i + h].rgbtRed * modifierY;
                }
            }

            // obtains the final values of the pixels combining X and Y calculations
            temp[j][i].rgbtBlue = limit(round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY)));
            temp[j][i].rgbtGreen = limit(round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY)));
            temp[j][i].rgbtRed = limit(round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY)));
        }
    }

    //copies values from temporary table
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
    return;
}
