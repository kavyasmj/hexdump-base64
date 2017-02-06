/******************************************************************************/
/* Program Name: hw1.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: main program to run homework1
 * COntains logic for command line validation, handlign different inputs
 * and calling hexdump and base64 programs
  */
/******************************************************************************/
// headers
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "hexdump.h"
#include "enc-base64.h"
#include "dec-base64.h"


// constants defn
#define MAXPATHLENGTH 256
#ifdef WIN32
#define DIR_SEP '\\'
#else /* ~WIN32 */
#define DIR_SEP '/'
#endif /* WIN32 */

// global var declaration
static char gszProgName[MAXPATHLENGTH];

// method declarations
// get program name for showing usage informatoion
static
void SetProgramName(char *s)
{
    char *c_ptr=strrchr(s, DIR_SEP);

    if (c_ptr == NULL) {
        strcpy(gszProgName, s);
    } else {
        strcpy(gszProgName, ++c_ptr);
    }
}

//execution starts here
int main(int argc, char* argv[]){

	SetProgramName(*argv);

	//command line validations
	if ( argc < 2 || argc > 3 || ( (strcmp(argv[1], "hexdump") != 0 )
	 && (strcmp(argv[1], "enc-base64") != 0 )
	  && (strcmp(argv[1], "dec-base64") != 0 )))
    {
    	// if invalid command
        fprintf(stderr, "Malformed command\n");
        fprintf(stderr,
            "usage: ./%s %s\n", 
            gszProgName, "hexdump|enc-base64|dec-base64 [file]" );
        exit(1);
    }
    else  //valid command
    {
    	//check input file
    	if(argc == 3){
    		
    		struct stat s;
			if( stat(argv[2],&s) == 0 )
			{
			    if( s.st_mode & S_IFDIR )
			    {
			    	//input file is a directory
			        fprintf(stderr, "input file: %s is a directory\n",argv[2]);
	        	    exit(1);
			    }
			}

			//open input file
	        FILE *file = fopen( argv[2], "rb" );

	        /* fopen on failure */
	        if ( file == NULL )
	        {
	            fprintf(stderr, "input file: %s ",argv[2]);
	            perror("");
        	    exit(1);
	        }
	        else  //success on opening file
	        {

	        	if (strcmp(argv[1], "hexdump") == 0)
	        		hex(file);
	        	else if (strcmp(argv[1], "enc-base64") == 0)
	        		en(file); 	        	
	        	else if (strcmp(argv[1], "dec-base64") == 0)
	        		dec(file); 		        
	        	

	        	//close after processing
           		fclose( file );
	     	}
    	}

    	else{
    		/*code to handle stdin, no file handling logic */

    		if (strcmp(argv[1], "hexdump") == 0)
	        		hex(stdin);  
	        else if (strcmp(argv[1], "enc-base64") == 0)
	        	en(stdin); 	        	
	        else if (strcmp(argv[1], "dec-base64") == 0)
	        	dec(stdin); 		        	
    	}
    }

	return 0; //exit program
}