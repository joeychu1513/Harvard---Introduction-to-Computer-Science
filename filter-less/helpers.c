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
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int rounded_average = round(average);
            image[i][j].rgbtBlue = rounded_average;
            image[i][j].rgbtGreen = rounded_average;
            image[i][j].rgbtRed = rounded_average;
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
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            int rounded_sepiaRed = round(sepiaRed);
            if (rounded_sepiaRed < 0)
            {
                rounded_sepiaRed = 0;
            }
            else if (rounded_sepiaRed > 255)
            {
                rounded_sepiaRed = 255;
            }
            image[i][j].rgbtRed = rounded_sepiaRed;

            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            int rounded_sepiaGreen = round(sepiaGreen);
            if (rounded_sepiaGreen < 0)
            {
                rounded_sepiaGreen = 0;
            }
            else if (rounded_sepiaGreen > 255)
            {
                rounded_sepiaGreen = 255;
            }
            image[i][j].rgbtGreen = rounded_sepiaGreen;

            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;
            int rounded_sepiaBlue = round(sepiaBlue);
            if (rounded_sepiaBlue < 0)
            {
                rounded_sepiaBlue = 0;
            }
            else if (rounded_sepiaBlue > 255)
            {
                rounded_sepiaBlue = 255;
            }
            image[i][j].rgbtBlue = rounded_sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copied[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copied[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copied[i][width - j - 1];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE copied[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copied[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1)
            {
                float blur_Blue = (copied[i][j].rgbtBlue + copied[i][j - 1].rgbtBlue + copied[i][j + 1].rgbtBlue +
                copied[i - 1][j - 1].rgbtBlue + copied[i - 1][j].rgbtBlue + copied[i - 1][j + 1].rgbtBlue +
                copied[i + 1][j - 1].rgbtBlue + copied[i + 1][j].rgbtBlue + copied[i + 1][j + 1].rgbtBlue) / 9.0;
                int rounded_Blue = round(blur_Blue);
                if (rounded_Blue < 0)
                {
                    rounded_Blue = 0;
                }
                else if (rounded_Blue > 255)
                {
                    rounded_Blue = 255;
                }
                image[i][j].rgbtBlue = rounded_Blue;

                float blur_Green = (copied[i][j].rgbtGreen + copied[i][j - 1].rgbtGreen + copied[i][j + 1].rgbtGreen +
                copied[i - 1][j - 1].rgbtGreen + copied[i - 1][j].rgbtGreen + copied[i - 1][j + 1].rgbtGreen +
                copied[i + 1][j - 1].rgbtGreen + copied[i + 1][j].rgbtGreen + copied[i + 1][j + 1].rgbtGreen) / 9.0;
                int rounded_Green = round(blur_Green);
                if (rounded_Green < 0)
                {
                    rounded_Green = 0;
                }
                else if (rounded_Green > 255)
                {
                    rounded_Green = 255;
                }
                image[i][j].rgbtGreen = rounded_Green;

                float blur_Red = (copied[i][j].rgbtRed + copied[i][j - 1].rgbtRed + copied[i][j + 1].rgbtRed +
                copied[i - 1][j - 1].rgbtRed + copied[i - 1][j].rgbtRed + copied[i - 1][j + 1].rgbtRed +
                copied[i + 1][j - 1].rgbtRed + copied[i + 1][j].rgbtRed + copied[i + 1][j + 1].rgbtRed) / 9.0;
                int rounded_Red = round(blur_Red);
                if (rounded_Red < 0)
                {
                    rounded_Red = 0;
                }
                else if (rounded_Red > 255)
                {
                    rounded_Red = 255;
                }
                image[i][j].rgbtRed = rounded_Red;
            }

            // top left
            else if (i == 0 && j == 0)
            {
                float blur_Blue = (copied[i][j].rgbtBlue + copied[i][j + 1].rgbtBlue + copied[i + 1][j].rgbtBlue +
                copied[i + 1][j + 1].rgbtBlue) / 4.0;
                int rounded_Blue = round(blur_Blue);
                if (rounded_Blue < 0)
                {
                    rounded_Blue = 0;
                }
                else if (rounded_Blue > 255)
                {
                    rounded_Blue = 255;
                }
                image[i][j].rgbtBlue = rounded_Blue;

                float blur_Green = (copied[i][j].rgbtGreen + copied[i][j + 1].rgbtGreen + copied[i + 1][j].rgbtGreen +
                copied[i + 1][j + 1].rgbtGreen) / 4.0;
                int rounded_Green = round(blur_Green);
                if (rounded_Green < 0)
                {
                    rounded_Green = 0;
                }
                else if (rounded_Green > 255)
                {
                    rounded_Green = 255;
                }
                image[i][j].rgbtGreen = rounded_Green;

                float blur_Red = (copied[i][j].rgbtRed + copied[i][j + 1].rgbtRed + copied[i + 1][j].rgbtRed +
                copied[i + 1][j + 1].rgbtRed) / 4.0;
                int rounded_Red = round(blur_Red);
                if (rounded_Red < 0)
                {
                    rounded_Red = 0;
                }
                else if (rounded_Red > 255)
                {
                    rounded_Red = 255;
                }
                image[i][j].rgbtRed = rounded_Red;
            }

            // top right
            else if (i == 0 && j == width - 1)
            {
                float blur_Blue = (copied[i][j].rgbtBlue + copied[i][j - 1].rgbtBlue + copied[i + 1][j].rgbtBlue +
                copied[i + 1][j - 1].rgbtBlue) / 4.0;
                int rounded_Blue = round(blur_Blue);
                if (rounded_Blue < 0)
                {
                    rounded_Blue = 0;
                }
                else if (rounded_Blue > 255)
                {
                    rounded_Blue = 255;
                }
                image[i][j].rgbtBlue = rounded_Blue;

                float blur_Green = (copied[i][j].rgbtGreen + copied[i][j - 1].rgbtGreen + copied[i + 1][j].rgbtGreen +
                copied[i + 1][j - 1].rgbtGreen) / 4.0;
                int rounded_Green = round(blur_Green);
                if (rounded_Green < 0)
                {
                    rounded_Green = 0;
                }
                else if (rounded_Green > 255)
                {
                    rounded_Green = 255;
                }
                image[i][j].rgbtGreen = rounded_Green;

                float blur_Red = (copied[i][j].rgbtRed + copied[i][j - 1].rgbtRed + copied[i + 1][j].rgbtRed +
                copied[i + 1][j - 1].rgbtRed) / 4.0;
                int rounded_Red = round(blur_Red);
                if (rounded_Red < 0)
                {
                    rounded_Red = 0;
                }
                else if (rounded_Red > 255)
                {
                    rounded_Red = 255;
                }
                image[i][j].rgbtRed = rounded_Red;
            }

            // bottom left
            else if (i == height - 1 && j == 0)
            {
                float blur_Blue = (copied[i][j].rgbtBlue + copied[i][j + 1].rgbtBlue + copied[i - 1][j].rgbtBlue +
                copied[i - 1][j + 1].rgbtBlue) / 4.0;
                int rounded_Blue = round(blur_Blue);
                if (rounded_Blue < 0)
                {
                    rounded_Blue = 0;
                }
                else if (rounded_Blue > 255)
                {
                    rounded_Blue = 255;
                }
                image[i][j].rgbtBlue = rounded_Blue;

                float blur_Green = (copied[i][j].rgbtGreen + copied[i][j + 1].rgbtGreen + copied[i - 1][j].rgbtGreen +
                copied[i - 1][j + 1].rgbtGreen) / 4.0;
                int rounded_Green = round(blur_Green);
                if (rounded_Green < 0)
                {
                    rounded_Green = 0;
                }
                else if (rounded_Green > 255)
                {
                    rounded_Green = 255;
                }
                image[i][j].rgbtGreen = rounded_Green;

                float blur_Red = (copied[i][j].rgbtRed + copied[i][j + 1].rgbtRed + copied[i - 1][j].rgbtRed +
                copied[i - 1][j + 1].rgbtRed) / 4.0;
                int rounded_Red = round(blur_Red);
                if (rounded_Red < 0)
                {
                    rounded_Red = 0;
                }
                else if (rounded_Red > 255)
                {
                    rounded_Red = 255;
                }
                image[i][j].rgbtRed = rounded_Red;
            }

            // bottom right
            else if (i == height - 1 && j == width - 1)
            {
                float blur_Blue = (copied[i][j].rgbtBlue + copied[i][j - 1].rgbtBlue + copied[i - 1][j].rgbtBlue +
                copied[i - 1][j - 1].rgbtBlue) / 4.0;
                int rounded_Blue = round(blur_Blue);
                if (rounded_Blue < 0)
                {
                    rounded_Blue = 0;
                }
                else if (rounded_Blue > 255)
                {
                    rounded_Blue = 255;
                }
                image[i][j].rgbtBlue = rounded_Blue;

                float blur_Green = (copied[i][j].rgbtGreen + copied[i][j - 1].rgbtGreen + copied[i - 1][j].rgbtGreen +
                copied[i - 1][j - 1].rgbtGreen) / 4.0;
                int rounded_Green = round(blur_Green);
                if (rounded_Green < 0)
                {
                    rounded_Green = 0;
                }
                else if (rounded_Green > 255)
                {
                    rounded_Green = 255;
                }
                image[i][j].rgbtGreen = rounded_Green;

                float blur_Red = (copied[i][j].rgbtRed + copied[i][j - 1].rgbtRed + copied[i - 1][j].rgbtRed +
                copied[i - 1][j - 1].rgbtRed) / 4.0;
                int rounded_Red = round(blur_Red);
                if (rounded_Red < 0)
                {
                    rounded_Red = 0;
                }
                else if (rounded_Red > 255)
                {
                    rounded_Red = 255;
                }
                image[i][j].rgbtRed = rounded_Red;
            }

            // top edge
            else if (i == 0 && j != width - 1 && j != 0)
            {
                float blur_Blue = (copied[i][j].rgbtBlue + copied[i][j - 1].rgbtBlue + copied[i][j + 1].rgbtBlue +
                copied[i + 1][j - 1].rgbtBlue + copied[i + 1][j].rgbtBlue + copied[i + 1][j + 1].rgbtBlue) / 6.0;
                int rounded_Blue = round(blur_Blue);
                if (rounded_Blue < 0)
                {
                    rounded_Blue = 0;
                }
                else if (rounded_Blue > 255)
                {
                    rounded_Blue = 255;
                }
                image[i][j].rgbtBlue = rounded_Blue;

                float blur_Green = (copied[i][j].rgbtGreen + copied[i][j - 1].rgbtGreen + copied[i][j + 1].rgbtGreen +
                copied[i + 1][j - 1].rgbtGreen + copied[i + 1][j].rgbtGreen + copied[i + 1][j + 1].rgbtGreen) / 6.0;
                int rounded_Green = round(blur_Green);
                if (rounded_Green < 0)
                {
                    rounded_Green = 0;
                }
                else if (rounded_Green > 255)
                {
                    rounded_Green = 255;
                }
                image[i][j].rgbtGreen = rounded_Green;

                float blur_Red = (copied[i][j].rgbtRed + copied[i][j - 1].rgbtRed + copied[i][j + 1].rgbtRed +
                copied[i + 1][j - 1].rgbtRed + copied[i + 1][j].rgbtRed + copied[i + 1][j + 1].rgbtRed) / 6.0;
                int rounded_Red = round(blur_Red);
                if (rounded_Red < 0)
                {
                    rounded_Red = 0;
                }
                else if (rounded_Red > 255)
                {
                    rounded_Red = 255;
                }
                image[i][j].rgbtRed = rounded_Red;

            }

            // bottom edge
            else if (i == height - 1 && j != width - 1 && j != 0)
            {
                float blur_Blue = (copied[i][j].rgbtBlue + copied[i][j - 1].rgbtBlue + copied[i][j + 1].rgbtBlue +
                copied[i - 1][j - 1].rgbtBlue + copied[i - 1][j].rgbtBlue + copied[i - 1][j + 1].rgbtBlue) / 6.0;
                int rounded_Blue = round(blur_Blue);
                if (rounded_Blue < 0)
                {
                    rounded_Blue = 0;
                }
                else if (rounded_Blue > 255)
                {
                    rounded_Blue = 255;
                }
                image[i][j].rgbtBlue = rounded_Blue;

                float blur_Green = (copied[i][j].rgbtGreen + copied[i][j - 1].rgbtGreen + copied[i][j + 1].rgbtGreen +
                copied[i - 1][j - 1].rgbtGreen + copied[i - 1][j].rgbtGreen + copied[i - 1][j + 1].rgbtGreen) / 6.0;
                int rounded_Green = round(blur_Green);
                if (rounded_Green < 0)
                {
                    rounded_Green = 0;
                }
                else if (rounded_Green > 255)
                {
                    rounded_Green = 255;
                }
                image[i][j].rgbtGreen = rounded_Green;

                float blur_Red = (copied[i][j].rgbtRed + copied[i][j - 1].rgbtRed + copied[i][j + 1].rgbtRed +
                copied[i - 1][j - 1].rgbtRed + copied[i - 1][j].rgbtRed + copied[i - 1][j + 1].rgbtRed) / 6.0;
                int rounded_Red = round(blur_Red);
                if (rounded_Red < 0)
                {
                    rounded_Red = 0;
                }
                else if (rounded_Red > 255)
                {
                    rounded_Red = 255;
                }
                image[i][j].rgbtRed = rounded_Red;
            }
            // left edge
            else if (j == 0 && i != height - 1 && i != 0)
            {
                float blur_Blue = (copied[i][j].rgbtBlue + copied[i][j + 1].rgbtBlue + copied[i - 1][j].rgbtBlue +
                copied[i - 1][j + 1].rgbtBlue + copied[i + 1][j].rgbtBlue + copied[i + 1][j + 1].rgbtBlue) / 6.0;
                int rounded_Blue = round(blur_Blue);
                if (rounded_Blue < 0)
                {
                    rounded_Blue = 0;
                }
                else if (rounded_Blue > 255)
                {
                    rounded_Blue = 255;
                }
                image[i][j].rgbtBlue = rounded_Blue;


                float blur_Green = (copied[i][j].rgbtGreen + copied[i][j + 1].rgbtGreen + copied[i - 1][j].rgbtGreen +
                copied[i - 1][j + 1].rgbtGreen + copied[i + 1][j].rgbtGreen + copied[i + 1][j + 1].rgbtGreen) / 6.0;
                int rounded_Green = round(blur_Green);
                if (rounded_Green < 0)
                {
                    rounded_Green = 0;
                }
                else if (rounded_Green > 255)
                {
                    rounded_Green = 255;
                }
                image[i][j].rgbtGreen = rounded_Green;

                float blur_Red = (copied[i][j].rgbtRed + copied[i][j + 1].rgbtRed + copied[i - 1][j].rgbtRed +
                copied[i - 1][j + 1].rgbtRed + copied[i + 1][j].rgbtRed + copied[i + 1][j + 1].rgbtRed) / 6.0;
                int rounded_Red = round(blur_Red);
                if (rounded_Red < 0)
                {
                    rounded_Red = 0;
                }
                else if (rounded_Red > 255)
                {
                    rounded_Red = 255;
                }
                image[i][j].rgbtRed = rounded_Red;
            }

            // right edge
            else if (j == width - 1 && i != height - 1 && i != 0)
            {
                float blur_Blue = (copied[i][j].rgbtBlue + copied[i][j - 1].rgbtBlue + copied[i - 1][j].rgbtBlue +
                copied[i - 1][j - 1].rgbtBlue + copied[i + 1][j].rgbtBlue + copied[i + 1][j - 1].rgbtBlue) / 6.0;
                int rounded_Blue = round(blur_Blue);
                if (rounded_Blue < 0)
                {
                    rounded_Blue = 0;
                }
                else if (rounded_Blue > 255)
                {
                    rounded_Blue = 255;
                }
                image[i][j].rgbtBlue = rounded_Blue;


                float blur_Green = (copied[i][j].rgbtGreen + copied[i][j - 1].rgbtGreen + copied[i - 1][j].rgbtGreen +
                copied[i - 1][j - 1].rgbtGreen + copied[i + 1][j].rgbtGreen + copied[i + 1][j - 1].rgbtGreen) / 6.0;
                int rounded_Green = round(blur_Green);
                if (rounded_Green < 0)
                {
                    rounded_Green = 0;
                }
                else if (rounded_Green > 255)
                {
                    rounded_Green = 255;
                }
                image[i][j].rgbtGreen = rounded_Green;

                float blur_Red = (copied[i][j].rgbtRed + copied[i][j - 1].rgbtRed + copied[i - 1][j].rgbtRed +
                copied[i - 1][j - 1].rgbtRed + copied[i + 1][j].rgbtRed + copied[i + 1][j - 1].rgbtRed) / 6.0;
                int rounded_Red = round(blur_Red);
                if (rounded_Red < 0)
                {
                    rounded_Red = 0;
                }
                else if (rounded_Red > 255)
                {
                    rounded_Red = 255;
                }
                image[i][j].rgbtRed = rounded_Red;
            }




        }
    }
    return;
}
