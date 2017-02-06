/******************************************************************************/
/* Program Name: dec-base64.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: Contains logic to decode base64 encoded characters
 */
/******************************************************************************/
// headers
#include "dec-base64.h" 


//global var declaration
//ASCII char set
char charac[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 


//method declarations
// method to print out the decoded characters
static void print_output(unsigned char inp[],int count){

	unsigned int inter[4] = {0, };
    unsigned char op[4] = {0, };
    char*e = 0;
    
    //convert given bytes to decimal value
    int k = 0;
    for (k = 0; k < count; k++)
    {       
    	//get index value of a character in the encoding data
        e = 0;
        e = strchr(charac, inp[k]);
        inter[k] = (int)(e - charac) ;
        //check for invalid character
        if (inter[k] > 63 || inter[k] < 0) //defined ascii range
        {
        	fprintf(stderr, "Error: cannot decode invalid character %c \n", inp[k]);
        	exit(1);
        }
    }

    //if nothing to process except =
    if (count < 0)
    	return; //print nothing

    // logic to convert 4 bytes of data into 3, convert decimal to binary, perform bitwise oeprations
    //check and print only bytes recieved. May not always get 4 bytes of data
    if (count == 1)
    	op[0] = (inter[0] << 2);
    else
    	op[0] = (inter[0] << 2) | ((inter[1] & 0x30) >> 4);

    if (count == 2)
    	op[1] = (inter[1] << 4);
    else
    	op[1] = (inter[1] << 4) | ((inter[2]  & 0x3c) >> 2);

    if (count == 3 )
    	op[2] = ((inter[2] & 0x03)<< 6);
    else
    	op[2] = (((inter[2] & 0x03)<< 6) | (inter[3] & 0x3f));


    //output the resultant decoded characters
    int i = 0;
    for(i=0; i< count-1; i++) {
            printf("%c", op[i]);
    }
}


// method to decode input stream
void dec(FILE* file){
    unsigned char in[1];
    
    int count = 0;
    unsigned char inp[4] = {0, };

    //read input one byte at a time
    while (fread(in, 1, 1, file) > 0){

    	//ignore new line charcters
      	if (in[0] == '\n')
      	      continue;

      	// reached the end of file, stop processing
      	if (in[0] == '='){
      		//convert any remainign characters
      		print_output(inp,count);
      		break;
      	}

      	//update 4 byte with the one read byte 
      	inp[count++] = in[0];
      	if (count < 4) // wait for 4 bytes
      	      continue;
      	else{ // call function to process and decode the 4 bytes
      		print_output(inp,count);
      		count = 0; // rest counter
      	}
    }
}
