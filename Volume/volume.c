// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //create a buffer, fread input into buffer, fwrite into output
    uint8_t buff[HEADER_SIZE];
    if (fread(buff, sizeof(uint8_t), HEADER_SIZE, input) < HEADER_SIZE)
    {
        printf("failed to read header into buff");
    }

    if (fwrite(buff, sizeof(uint8_t), HEADER_SIZE, output) < HEADER_SIZE)
    {
        printf("failed to write to output");
    }

    //read samples until EOF, multiply each sample by factor, then write to output
    int16_t sample[1];
    while (fread(sample, sizeof(int16_t), 1, input) != 0)
    {
        sample[0] *= factor;

        fwrite(sample, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}



