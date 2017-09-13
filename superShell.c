#include <stdio.h>


char* read(void){
	int bufsize = 16;
	char *buffer = malloc(sizeof(char) * bufsize);
	int pos = 0;

	// Exemplifies the problem
	char *lesson_buffer = malloc(sizeof(char) * 1);
	lesson_buffer[0] = '5';
	// I don't assign this variable anywhere else

	while(1){
		char c = getchar();
		if(c !='\n'){
      //handle situation where the length is over the limit
			if(pos >= bufsize){
				bufsize = bufsize*2;
				buffer = realloc(buffer, bufsize);
			}
			buffer[pos++] = c;
		}
		else {
			buffer[pos] = '\0'; // null byte

			// Confirm that these two things are both correct
			printf("buffer: %s\n", buffer);
			printf("lesson: %s\n", lesson_buffer);
			free(lesson_buffer);

			// Return the collected string
			return buffer;
		}
	}
}

//A function to split the command and return a char* array
char** splitStr(char command[]){
	int count = 0;
	char* temp;
	char* lastSplit;


	//get the number of space the new char* array needed
	for(temp = command; *temp;temp++){

		if(strncmp(temp, " ", 1)==0){
			count += 1;
			lastSplit = temp;	//remember the last split location
		}

		printf("Iterating %c : %d\n",*temp,count);

	}
  	if(lastSplit != "\0"){
    	count += 1;
  	}
	count += 1; //a trailing for null

	printf("%d\n", count);


	//generate the result array
	char** result = malloc(sizeof(char*) * count);
	char* token = strtok(command, " ");


	size_t index = 0;
	while(token){
		printf(token);
		printf("\n");
		result[index] = token;
		*(result + index++) = token;
		token = strtok(NULL, " ");
	}
	*(result + index++) = "\0";


	return result;


}




//main function of the shell, implement the interface
int main(void){

  while(1){
    printf("Type in something: $");
  	char *cmd = read();
  	printf("You typed: %s\n", cmd);
	char** splitedCommand = splitStr(cmd);
	if(strncmp(splitedCommand[0], "exit") ==0){
		system("exit()");
	}

    printf("Here comes the test part: ");
    int status = system("gcc -o test read_command_naive.c");

    return 0;
  }


}
