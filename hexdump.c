/******************************************************************************/
/* Program Name: hexdump.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: Contains logic to take characters from input file, convert the 
 * characters to their hexdecimal representation and print the output
 */
/******************************************************************************/
// headers

#include "hexdump.h"

//global var declaration
unsigned char line[16] = {0, };
int bytes_read = 0;

//method declarations
//method to process the input data
static void convert_func(unsigned char line[],int k){ // takes 16 or less char

	//output number of bytes read so far in hex
	printf("%06x: ", bytes_read);
	bytes_read+=16; // processed 16 bytes
	
	int i,j,curr_char = 0;
	
	// logic for output formatting hex representation
	for (j = 0; j < k; j++)
	{	

		if (j == 8)
			printf(" "); // output format

		curr_char = line[j];
		printf("%02x ", (unsigned char)curr_char); //output character
	}
	while ( j < 16)
	{	
		if (j == 8)
			printf(" ");

		printf("-- "); // output format if space is present after EOF
		j++;
	}

	// Ascii characters
	printf(" ");
	for (i = 0; i < k; i++)
	{	
		curr_char = line[i];

		// If the data byte is >=0x20 and <=0x7e you should use the corresponding ASCII character.
		if (curr_char >= 32 && curr_char <= 126) {
	         printf("%c", curr_char);
	     }
	     //  If the data byte is <=0x1f or equals to 0x7f, you should print a period character.
	     else if (curr_char <=31 || curr_char == 127) {
	         printf(".");
	     }
	             
	     //If the data byte is >=0x80 you should print a ~ character.
	     else if (curr_char >= 128){
	         printf("~");
	     }
	}

	while ( i < 16) // output format - new line
	{	
		printf(" ");
		i++;
	}
	printf("\n");
}


//method to read and process the input
void hex(FILE* file){

	unsigned char buf[1];

	int k = 0;
	//read from input file one byte at a time
	while (fread(buf, 1, 1, file ) != 0) {
		if(k<16)
		{
			line[k++] = buf[0]; //update char array
		}
		else{
			convert_func(line,k); //call function for hex conversion
			memset(line, 0, sizeof (char) * sizeof line); //clear and reinitialize array after every loop pass
			k=0;
			line[k++] = buf[0]; //update char array
		}
		
	}
	convert_func(line,k); // //call function for hex converstion, for processing any remaining input
}




