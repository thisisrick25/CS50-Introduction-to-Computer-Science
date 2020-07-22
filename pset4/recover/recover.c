#include <stdio.h>
#include <stdlib.h>

size_t SIZE = 512;

int main(int argc, char *argv[])
{
    // Initialize and store file name
    char *image = argv[1];

    //accepts exactly single command line argument
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //open image for reading; return error if unable to access
    FILE *inpic = fopen(image, "r");

    // If image cannot be opened for reading then end
    if (inpic == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", image);
        return 2;
    }

    // Initialize JPG identification search buffer to size of read in chunks
    // Using 'unsigned' for 0 to 255
    unsigned char buffer[SIZE];

    //index for blocks searched in card.raw;
    int openFileTracker = 0;

    //filename buffer
    char filename[8];

    //jpeg's recovered
    short jpegTracker = 0;

    FILE *outpic;

    while (fread(&buffer, SIZE, 1, inpic))
    {
        // Check first 4 bytes of buffered chunk to see if it corrisponds to the start of a JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (openFileTracker)
            {
                // close the previously opened file
                fclose(outpic);

                // set openFileTracker as false
                openFileTracker = 0;

                // create new file name
                sprintf(filename, "%03d.jpg", jpegTracker);

                // apply and open this new file
                outpic = fopen(filename, "a");

                // set openFileTracker to true
                openFileTracker = 1;

                // Increment our file naming tracker
                jpegTracker++;
            }

            // If we do NOT have an open file
            if (!openFileTracker)
            {
                // name a new file and open it
                sprintf(filename, "%03d.jpg", jpegTracker);
                outpic = fopen(filename, "w");

                // We now have an open file.
                openFileTracker = 1;

                jpegTracker++;
            }

            // write the buffer to the file
            fwrite(&buffer, SIZE, 1, outpic);
        }

        //if it is not start of new JPEG
        else
        {
            if (openFileTracker)
            {
                // Write the block to the file
                fwrite(&buffer, SIZE, 1, outpic);
            }

            if (!openFileTracker)
            {
                // This simply does nothing since this block of 512 bytes can be discarded and we move back to top of the while loop.
            }
        }
    }

    // Close the initial image file
    fclose(inpic);

    // close any open jpeg file
    fclose(outpic);

    return 0;
}