//
//  lab02.c
//  lab02 project for cs232. Copying a file from one location to another.
//
//  Created by Russ Clousing on 2/10/18.
//  Copyright © 2018 Russ Clousing. All rights reserved.
//
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char **argv)
{
	//pointers to the files that need to be copied and created/pasted
    FILE *fpSource, *fpDest;
    //char that is being copied
    char ch;
    //position tracker. It is long because ftell returns a long.
    long pos;
 
    struct stat status;
    int stats;
   
    //check to see if dest file already exists if so prints error and exits
    if (access(argv[2], F_OK) != -1)
    {
    	perror("\nDestination file already exists\n");
    	return(-1);
    }
    
    //check to make sure source file is not a regular file
    stats = stat(argv[1], &status);
    if (S_ISREG(status.st_mode) == 0)
    {
    	perror("Source file is not a regular file");
	return(-1);
    }

    //Actually copying the file
    if ((fpSource = fopen(argv[1],"r")) == NULL)
    {
        perror("\nFile cannot be opened");
        return(-1);
    }
    fpDest = fopen(argv[2], "w");
    fseek(fpSource, 0L, SEEK_END); // file pointer at end of file
    pos = ftell(fpSource);
    fseek(fpSource, 0L, SEEK_SET); // file pointer set at start
    while (pos--)
    {
        ch = fgetc(fpSource);  // copying file character by character
        fputc(ch, fpDest);
    }
    fflush(NULL);	//closes all files that are open.
    return(0);
}
