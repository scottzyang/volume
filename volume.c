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
        printf("Usage: ./volume input.wav output.wav factor\n");  // verifies that user input is valid
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

    // TODO: Copy header from input file to output file
    uint8_t *header = malloc(sizeof(uint8_t) * HEADER_SIZE); // dynamically allocating memory in the heap

    // reads memory size of 8 bit integer 44 (HEADER_SIZE) times from the input to the header
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output); // writes """ from header to output

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input)) // while it is able to read one sample of 16 bits.
        //It'll keep reading until there is nothing to read then while loop will stop.
        // read from input file and store the memory into the address of buffer
    {
        buffer *= factor; // multiply by factor
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    free(header); // freeing the memory in the heap
    fclose(input);
    fclose(output);
}
