# GET_NEXT_LINE
Get_Next_Line is the second project of the 42 Ecole Common Core Course. As a student we are expected to code a program that reads from a file descriptor and returns a line ending with the newline character. Readding terminates when the EOF is detected.
The project has helped us appreciate the convenience of static variables in the C language. Static variables maintain their updated values across multiple program calls. Which is essential when we want to read the next line on the next program call after the most recently read line.     
MANDATORY RULES
Function Name		: get_next_line
Prototype          		: int get_next_line(int fd, char **line);
Submission Files   	: get_next_line.c, get_next_line_utils.c, get_next_line.h
Parameters         	: #1. file descriptor for reading, 
                     		  #2. The value of what has been read
Return Value       	: 1 : A line has been read
                     		  0 : EOF has been reached
                    		 -1 : An error happened 
External Functions 	: read, malloc, free
Notes              	: Global Variables are forbidden. Reading uses the BUFFER_SIZE defined during compilation using the command  gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c.
