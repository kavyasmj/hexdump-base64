#README#
Documentation for USC CSCI 531 Cyptography Assignment 1

GENERAL
Hexdump program: Process input from stdin or file, read one byte at a time
get its hex value. Output data 16 bytes per line. Format the output with spaces, showing number of bytes processed, hex values, and input characters.

BASE64 Encode program: Process input from stdin or file, read 3 bytes, convert to 4 bytes after encoding. Encode every byte(8 bits) to universal ASCII characters(6 bits).
Output the encoded characters, 64 per line. If all 3 bytes are not available then pad with 0's.

BASE64 Decode program: Decode encoded characters, take each character and find the position offset with respect to ASCII character set. Obtain the decimal value, convert to binary. Perform bitwise operations and convert 4 bytes of data read to 3 bytes. Stop when '=' is encountered. Show errors incase of invalid input.


BUILD
Comments:
"make" - to compile
"make clean" - to clear executable files

TESTING:
Test files:
usctommy.gif
yeseterday.txt
