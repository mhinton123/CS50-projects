#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop one through row and print hex values to console
    for (int px = 0; px < width; px++)
    {
        for (int row = 0; row < height; row++)
        {
            //printf("r: %x g: %x b: %x\n", image[0][px].rgbtRed, image[0][px].rgbtGreen, image[0][px].rgbtBlue);
            //calculate average of RGB, then set all RGB to avg
            double avgF = ((double)image[row][px].rgbtRed + (double)image[row][px].rgbtGreen + (double)image[row][px].rgbtBlue) / 3;
            avgF = round(avgF); //round to nearest whole number
            image[row][px].rgbtRed = avgF;
            image[row][px].rgbtGreen = avgF;
            image[row][px].rgbtBlue = avgF;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through each row
    for (int row = 0; row < height; row++)
    {
        //loop through row and reverse the row of pixels
        for (int px = 0, opPx = width - 1; px < width / 2; px++)
        {
            RGBTRIPLE temp;
            temp = image[row][px];
            image[row][px] = image[row][opPx];
            image[row][opPx] = temp;
            opPx--;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create copy of image
    RGBTRIPLE temp[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int px = 0; px < width; px++)
        {
            temp[row][px] = image[row][px];
        }
    }

    double sumR = 0;
    double sumG = 0;
    double sumB = 0;
    //loop through all pixels in temp[][]
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int counter = 0;
            sumR = 0;
            sumG = 0;
            sumB = 0;
            //loop through 3x3 surrounding pixels
            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    //get x pos relative to raget pixel
                    int currX = x + i;
                    int currY = y + j;

                    //check if pixel is out of bounds
                    if (currX < 0 || currX > (height - 1) || currY < 0 || currY > (width - 1))
                    {
                        //ignore pixel
                    }
                    else
                    {
                        sumR += temp[currX][currY].rgbtRed;
                        sumG += temp[currX][currY].rgbtGreen;
                        sumB += temp[currX][currY].rgbtBlue;
                        counter++;
                    }
                }
            }
            //copy new RGB values for image[x][y]
            sumR /= counter;
            sumG /= counter;
            sumB /= counter;
            sumR = round(sumR);
            sumG = round(sumG);
            sumB = round(sumB);

            image[x][y].rgbtRed = sumR;
            image[x][y].rgbtGreen = sumG;
            image[x][y].rgbtBlue = sumB;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //this filter uses the Sobel Operator to detect edges within an  image

    //create copy of image
    RGBTRIPLE temp[height][width];
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            temp[x][y] = image[x][y];
        }
    }

    //GX sum for RGB
    double gxRed = 0;
    double gxGreen = 0;
    double gxBlue = 0;

    //GY sum for RGB
    double gyRed = 0;
    double gyGreen = 0;
    double gyBlue = 0;

    //final colour value for RGB
    int gRed = 0;
    int gGreen = 0;
    int gBlue = 0;


    //gx kernal
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    //gy kernal
    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    //loop through all pixels in the image
    for (int row = 0; row < height; row++)
    {
        for (int px = 0; px < width; px++)
        {
            //GX sum for RGB
            gxRed = 0;
            gxGreen = 0;
            gxBlue = 0;

            //GY sum for RGB
            gyRed = 0;
            gyGreen = 0;
            gyBlue = 0;

            //final colour value for RGB
            gRed = 0;
            gGreen = 0;
            gBlue = 0;

            //for each target pixel, loop through the 3x3 block of pixels
            for (int x = -1, kernI = 0; x <= 1; x++)
            {
                for (int y = -1, kernJ = 0; y <= 1; y++)
                {
                    //get x and y positions relative to pixel[row][px]
                    int xPos = row + (x);
                    int yPos = px + (y);

                    //check if pixel[xPos][yPos] is out of bounds
                    if (xPos < 0 || xPos > (height - 1) || yPos < 0 || yPos > (width - 1))
                    {
                        //ignore pixel
                    }
                    else
                    {
                        if (gx[kernI][kernJ] == 0)
                        {
                            //ignore adding pixel value to sum
                        }
                        else
                        {
                            //sum gx values for all colour channels
                            gxRed += (temp[xPos][yPos].rgbtRed * (gx[kernI][kernJ]));
                            gxGreen += (temp[xPos][yPos].rgbtGreen * (gx[kernI][kernJ]));
                            gxBlue += (temp[xPos][yPos].rgbtBlue * (gx[kernI][kernJ]));
                        }

                        if (gy[kernI][kernJ] == 0)
                        {
                            //ignore adding pixel value to sum
                        }
                        else
                        {
                            //sum gy values for all colour channels
                            gyRed += (temp[xPos][yPos].rgbtRed * (gy[kernI][kernJ]));
                            gyGreen += (temp[xPos][yPos].rgbtGreen * (gy[kernI][kernJ]));
                            gyBlue += (temp[xPos][yPos].rgbtBlue * (gy[kernI][kernJ]));
                        }

                    }
                    kernJ++;
                }
                kernI++;
            }
            //Gx^2 + Gy^2 and store as new colour value for target pixel [row][px]

            //RED
            gxRed = gxRed * gxRed;                 //sqr both value
            gyRed = gyRed * gyRed;
            gxRed = sqrt((gxRed) + (gyRed));    //Sqrt: Gx^2 + Gy^2
            gRed = round(gxRed);           //round to nearest int

            if (gRed > 255)
            {
                gRed = 255;
            }
            if (gRed < 0)
            {
                gRed = 0;
            }

            image[row][px].rgbtRed = gRed;

            //GREEN
            gxGreen = gxGreen * gxGreen;                 //sqr both value
            gyGreen = gyGreen * gyGreen;
            gxGreen = sqrt((gxGreen) + (gyGreen));    //Sqrt: Gx^2 + Gy^2
            gGreen = round(gxGreen);           //round to nearest int

            if (gGreen > 255)
            {
                gGreen = 255;
            }
            if (gGreen < 0)
            {
                gGreen = 0;
            }

            image[row][px].rgbtGreen = gGreen;

            //BLUE
            gxBlue = gxBlue * gxBlue;                 //sqr both value
            gyBlue = gyBlue * gyBlue;
            gxBlue = sqrt((gxBlue) + (gyBlue));    //Sqrt: Gx^2 + Gy^2
            gBlue = round(gxBlue);           //round to nearest int

            if (gBlue > 255)
            {
                gBlue = 255;
            }
            if (gBlue < 0)
            {
                gBlue = 0;
            }

            image[row][px].rgbtBlue = gBlue;
        }
    }


    return;
}

