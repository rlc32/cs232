Rlc32
mystery lab

Tool used: Running the program. 
	What I learned : That when just running the program it deletes itself. 
Tool used: Strings. 
	What the tool does: It finds and prints the text strings embedded in binary files such as executables. 
	What I learned: There are several command line options. 
	First there is the command line option -h. -h displays helpful information about the other command line options. 
	The command line option -n <i> allocates <i> items.
		when mystery -n 10 is called only 10 random numbers are created. 
	The command line -p <port> changes the part that is used to send data out using TCP, by defualt the port is 10234. 
	The command line -s sorts.
	The command line -e <seed> uses <seed> to seed the random number generater. 
	Also strings provides a note to use nm on the file.
Tool used: File properties. 
	What the tool does: displays assorted information about the file. 
	What I learned: The file is 14.0 kB in size.
Tool used: running mystery -s. 
	What it does: It prints out 100 numbers sorted from smallest to largest. 
	What I learned: That mystery prints out 100 numbers. When run multiple times the numbers stay the same. The numbers are sorted smallest to largest.
Tool used:running mystery -e helloworld -s. 
	What it did: printed out 100 numbers sorted from smallest to largest. 
	What I learned: That using -e hello and -e helloworld produced the same 100 numbers when compared to each other and when compared to the original numbers provided by just running mystery -s. 
	When using -e 10 I got different random numbers. This leads me to believe -e requires an int or other numeric input.
Tool used nm. 
	What the tool does: nm is used to examine binary files. It displays the contents of those files, or the meta information, specifically the symbol table.  
	What I learned: NM allowed me to see what function calls are being made. List of function calls being made
	accept
	bind
	bzero
	close
	exit
	fflush
	fwrite
	listen
	malloc
	perror
	printf
	puts
	qsort
	random
	sleep
	socket
	sprintf
	srandom
	strcmp
	strlen
	unlink
	write
tool used: mystery -p 
	What it does: allows user to change the port used. 
	What i learned: it is bugged and doesnt allow the user to complete the command. you can continuisly enter text into the terminal and nothing happens.
tool used: Wireshark.
	what it does: packet capture.
	What i learned: Nothing is sent or recieved on port 10234 when running the executible with defualt ports. Wireshark did not capture anything on port 10234.



I think that the program mystery is a random number generater. By default it will delete itself but provide it with cmd line arguments and
the generator will work. The -n cmd argument will allow the user to specify how many random numbers to create. The -e cmd argument allows
the user to enter in a seed. The seed has to be numeric. The -h cmd argument displays the help menu. When looking at the symbol table
provided by NM it has a large amount of calls to set up and listen on sockets. However when ever the program runs it does not send or
receive any packets on the defualt port. Also the -p command is bugged and will not work when called. Thus i beleive that the networking
part of this program is not functioning. 
