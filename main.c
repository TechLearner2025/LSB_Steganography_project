#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BMP_HEADER_SIZE 54  // Standard BMP header size
#define MAX_MSG_SIZE 1000    // Max message length to encode

// Function to encode a message into the BMP file
void encode(char *inputImagePath, char *outputImagePath)
{
    FILE *inputImage = fopen(inputImagePath, "rb");
    FILE *outputImage = fopen(outputImagePath, "wb");

    if (!inputImage || !outputImage)
    {
        printf("Error: Could not open files. Make sure the paths are correct.\n");
        return;
    }

    // Copying header as-is from input to output image
    unsigned char header[BMP_HEADER_SIZE];
    fread(header, 1, BMP_HEADER_SIZE, inputImage);
    fwrite(header, 1, BMP_HEADER_SIZE, outputImage);

    char message[MAX_MSG_SIZE];
    printf("Enter message to hide (max %d characters): ", MAX_MSG_SIZE);
    fgets(message, MAX_MSG_SIZE, stdin);

    // Trimming newline character if exists
    size_t len = strlen(message);
    if (message[len - 1] == '\n') message[len - 1] = '\0';

    int c, msgIndex = 0, bitIndex = 0;
    char currentChar = message[msgIndex];

    while ((c = fgetc(inputImage)) != EOF)
    {
        if (currentChar == '\0' && bitIndex == 0)
        {
            fputc(c, outputImage);  // Simply copy remaining data
            continue;
        }

        if (bitIndex < 8)
        {
            // Encoding one bit at a time
            c = (c & 0xFE) | ((currentChar >> bitIndex) & 1);
            bitIndex++;
            if (bitIndex == 8)  // Move to next character
            {
                bitIndex = 0;
                currentChar = message[++msgIndex];
            }
        }
        fputc(c, outputImage);
    }

    fclose(inputImage);
    fclose(outputImage);

    printf("Message successfully encoded into the image.\n");
}

// Function to decode a message from the BMP file
void decode(char *imagePath)
{
    FILE *image = fopen(imagePath, "rb");

    if (!image)
    {
        printf("Error: Could not open image file.\n");
        return;
    }

    fseek(image, BMP_HEADER_SIZE, SEEK_SET);  // Skip BMP header

    int c, bitIndex = 0;
    char currentChar = 0;

    printf("Decoded message: ");

    while ((c = fgetc(image)) != EOF)
    {
        currentChar |= (c & 1) << bitIndex;
        bitIndex++;

        if (bitIndex == 8)
        {
            if (currentChar == '\0')  // Null terminator indicates end of message
            {
                break;
            }
            printf("%c", currentChar);
            bitIndex = 0;
            currentChar = 0;
        }
    }

    fclose(image);
    printf("\nDecoding completed successfully.\n");
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <encode/decode> <input_image> [output_image]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "encode") == 0)
    {
        if (argc != 4)
        {
            printf("Usage: %s encode <input_image> <output_image>\n", argv[0]);
            return 1;
        }
        encode(argv[2], argv[3]);
    }
    else if (strcmp(argv[1], "decode") == 0)
    {
        if (argc != 3)
        {
            printf("Usage: %s decode <input_image>\n", argv[0]);
            return 1;
        }
        decode(argv[2]);
    }
    else
    {
        printf("Invalid operation. Use 'encode' or 'decode'.\n");
        return 1;
    }

    return 0;
}
