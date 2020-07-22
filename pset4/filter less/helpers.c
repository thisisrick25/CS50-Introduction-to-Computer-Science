#include "helpers.h"
#include "math.h"
#include "stdio.h"
#include "string.h"

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // use sepia algorithim
            float sr = (float) .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sg = (float) .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sb = (float) .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            // round values
            int rsr = round(sr);
            int rsg = round(sg);
            int rsb = round(sb);
            // make sure it doesnt go over 255
            if (rsr > 255)
            {
                rsr = 255;
            }
            if (rsg > 255)
            {
                rsg = 255;
            }
            if (rsb > 255)
            {
                rsb = 255;
            }
            // set values as rgb values
            image[i][j].rgbtRed = rsr;
            image[i][j].rgbtGreen = rsg;
            image[i][j].rgbtBlue = rsb;
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