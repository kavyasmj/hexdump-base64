/******************************************************************************/
/* Program Name: enc-base64.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: Contains logic to encode characters(8 bits) 
 * to universal ASCII characters(6 bits)
 */
/******************************************************************************/
// headers
#include "enc-base64.h" 

//method declarations
//method to encode the chracters
void en(FILE* file){

        //ASCII char set
        char charac[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        unsigned char in[3] = {0, };    // to store 3 bytes input
        unsigned char op[4] = {0, };    // to store 4 bytes op

        int no_of_bytes = 0;
        no_of_bytes = fread(in, 1, 3, file ); // read 3 butes at a time from file or stdin
        int i = 0;
        while (no_of_bytes != 0) { //until EOF
                // add newline after every 64 characters
                if (i >= 64)
                {
                        i = 0;
                        printf("\n");
                }

                // get ASCII decimal value of each byte, convert to binary,
                // perform bitwise operations, find the decimal representation 
                // of new 6 bit value and get equivalent ascii code 
                op[0] = charac[in[0] >> 2];
                op[1] = charac[((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4)];
                if (no_of_bytes > 1)
                        op[2] = charac[(in[1] & 0x0f) << 2 | (in[2] & 0xc0) >> 6];
                else//if only 1 byte is given, pad with 0's to get 4 bytes
                        op[2] = '=';
                if (no_of_bytes > 2)
                        op[3] = charac[in[2] & 0x3f];
                else
                        op[3] = '=';


                // print out the encoded characters
                int m = 0;
                for(m=0; m<4; m++){
                   printf("%c", op[m]);
                }
                i += 4;

                //clear and re-initialize the buffers
                memset(in, 0, sizeof (char) * sizeof in);
                memset(op, 0, sizeof (char) * sizeof op);
                no_of_bytes = fread(in, 1, 3, file ); //read next batch of bytes
        }
        printf("%s\n",op);
}
