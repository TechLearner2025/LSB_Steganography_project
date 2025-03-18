# LMS Steganography Project

A simple C program to hide and retrieve messages in BMP images using the Least Significant Bit (LSB) technique.

##  Description 
This program allows users to **encode and decode secret messages** within BMP image files. The message is embedded by modifying the least significant bit of each byte in the image's pixel data.

##  Files 
- `lsb_steganography.c`: The main C source code file.
- `README.md`: This file.

##  Compilation 
To compile the program, use the following command:
```bash
gcc -o lsb_steganography lsb_steganography.c
```

## Usage
### Encoding (Hiding a Message)
```bash
./lsb_steganography encode <input_image> <output_image>
```
The program will prompt you to enter the secret message to encode.

### Decoding (Retrieving a Message)
```bash
./lsb_steganography decode <input_image>
```
The program will print the decoded message if it exists.

## Example
1. **Encode a message:**
```bash
./lsb_steganography encode input.bmp output.bmp
```
Enter your secret message when prompted.

2. **Decode the message:**
```bash
./lsb_steganography decode output.bmp
```
The hidden message will be displayed on the console.

## Limitations
- The program supports messages of up to 1000 characters.
- Only works with uncompressed BMP files.

## Future Improvements
- Add password protection for enhanced security.
- Improve encoding efficiency for larger messages.
- Add support for other image formats.

## License
This project is open-source and available.
