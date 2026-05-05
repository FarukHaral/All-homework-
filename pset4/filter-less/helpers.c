#include "helpers.h"
#include <math.h>

void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = avg;
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r = image[i][j].rgbtRed, g = image[i][j].rgbtGreen, b = image[i][j].rgbtBlue;
            int sepiaR = round(.393 * r + .769 * g + .189 * b);
            int sepiaG = round(.349 * r + .686 * g + .168 * b);
            int sepiaB = round(.272 * r + .534 * g + .131 * b);
            image[i][j].rgbtRed = (sepiaR > 255) ? 255 : sepiaR;
            image[i][j].rgbtGreen = (sepiaG > 255) ? 255 : sepiaG;
            image[i][j].rgbtBlue = (sepiaB > 255) ? 255 : sepiaB;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / 2; j++) {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) copy[i][j] = image[i][j];
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float r = 0, g = 0, b = 0, count = 0;
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (i+di>=0 && i+di<height && j+dj>=0 && j+dj<width) {
                        r += copy[i+di][j+dj].rgbtRed;
                        g += copy[i+di][j+dj].rgbtGreen;
                        b += copy[i+di][j+dj].rgbtBlue;
                        count++;
                    }
                }
            }
            image[i][j].rgbtRed = round(r/count);
            image[i][j].rgbtGreen = round(g/count);
            image[i][j].rgbtBlue = round(b/count);
        }
    }
}
