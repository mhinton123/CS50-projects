#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

//create byte datatype
typedef uint8_t BYTE;

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    //make sure the user only inputs 1 arg "the forensic file"
    if (argc != 2)
    {
        printf("Incorrect use: recover <filename.raw>\n");
        return 1;
    }
    if (strstr(argv[1], ".raw") == NULL)
    {
        printf("Incorrect use: recover <filename.raw>\n");
        return 1;
    }

    //create buffer to store current block in
    BYTE buffer[BLOCK_SIZE];

    //open the forensic file for reading and check for NULL
    FILE *rawFile = fopen(argv[1], "r");
    if (rawFile == NULL)
    {
        printf("Failed to open .RAW file");
        return 1;
    }

    int e = 0;
    char jpgName[8] = "000.jpg";
    int jpgNum = 0;
    fpos_t position;

    //loop through every block in the .raw file until EOF
    while (fread(buffer, 1, BLOCK_SIZE, rawFile) == BLOCK_SIZE)
    {
        //if first 4 bytes == JPEG sig, then open a new file and start writing blocks to it
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            //check 4th byte contains '0xe#'
            e = 14;
            if (buffer[3] >> 4 == e)
            {
                //format ###.jpgname, add a different number of 0's depending on number
                if (jpgNum < 10)
                {
                    sprintf(jpgName, "00%d.jpg", jpgNum);
                }
                else if (jpgNum >= 10 && jpgNum < 100)
                {
                    sprintf(jpgName, "0%d.jpg", jpgNum);
                }
                else
                {
                    sprintf(jpgName, "%d.jpg", jpgNum);
                }
                printf("%s\n", jpgName);
                jpgNum++;

                //open a new ###.jpg for writing & check for NULL
                FILE *jpg = fopen(jpgName, "w");
                if (jpg == NULL)
                {
                    printf("1.cant open file\n");
                }

                //write sig into new file and check for error
                if (fwrite(buffer, 1, BLOCK_SIZE, jpg) != BLOCK_SIZE)
                {
                    printf("2.cant write buff to new file\n");
                }

                //keep copying blocks to the jpg file until a new sig is found
                while (1)
                {
                    //Get postion before reading the next block
                    fgetpos(rawFile, &position);

                    //Read next block into buff
                    if (fread(buffer, 1, BLOCK_SIZE, rawFile) != BLOCK_SIZE)
                    {
                        //printf("3.cant read next block into buff\n");
                        fclose(jpg);
                        break;
                    }

                    //Check, if buff contains sig
                    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
                    {
                        //check 4th byte contains '0xe#'
                        e = 14;
                        if (buffer[3] >> 4 == e)
                        {
                            //revert back to previous block positon, so we dont skip the sig for next itteration
                            fsetpos(rawFile, &position);
                            //close file
                            fclose(jpg);
                            break;
                        }
                    }

                    //if buff isn't a sig, Write buff into new file
                    if (fwrite(buffer, 1, BLOCK_SIZE, jpg) != BLOCK_SIZE)
                    {
                        printf("4.cant write buff to new file\n");
                    }
                }
            }
        }
    }
    fclose(rawFile);        //close raw file for reading
}