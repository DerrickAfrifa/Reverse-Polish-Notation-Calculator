#include <stdio.h>
#include <stdlib.h>


int isOperator(char token, char operators[]){
	//char operators[5] = {'+', '-', '*', '/', '%'};
	for (int i = 0; i < 5; ++i){
		if(token == operators[i]) return 1;
	}
	return -1;
}

int tokenise(char str[], int start, char result[]){
	int i;
	for(i=start; str[i] != '\0'; i++){
		result[i-start]=str[i];
		if(str[i] == ' '){
			result[i-start]='\0';
			return i+1;
		}
	}
	result[i-start]='\0';
	return -1;
}

int tokenise_ops(char str[], int start, char result[],char operators[]){
	int i;

	if( isOperator(str[start], operators) == 1 ){
		result[0] = str[start];
		result[1] = '\0';
		return start+1;
	}

	for(i=start; str[i] != '\0'; i++){
		if(str[i] == ' '){
			result[i-start] = '\0';
			return i+1;
		}else if(isOperator(str[i], operators) == 1 ){
			result[i-start] = '\0';
			return i;
		}else{
			result[i-start] = str[i];
		}
	}
	result[i-start] = '\0';
	return -1;
}

void applyOperation(float num1, float num2, char operator, float * p){
	//printf("stack is at %c\n", stack);
	switch(operator){
		case '+':
			*p = num1 + num2;
			break;
		case '-':
			*p = num2 - num1;
			break;
		case '*':
			*p = num1 * num2;
			break;
		case '/':
			*p = num2 / num1;
			break;
		/*case '%':
			*p = num2 % num1;
			break;*/
	}
}

int main(){
	int start = 0;
	char result[256];
	char operators[5] = "+-*/";
	float stack[sizeof(float)*100];
	float token;
	int stackPointer  = -1; 
	float num1 = 0;
	float num2 = 0;
	const int MAX_STRING = 256;
	char buffer[MAX_STRING];
	printf("> ");
	fgets(buffer, MAX_STRING, stdin);

	while ( start != -1 ) {
	  start = tokenise_ops(buffer, start, result, operators);
	  token = atof(result);
	  //printf("... %f\n",token );
	  //printf("result is %s\n", result);	

		if(token == 0){  
			//printf("token %f was zero\n", token);
			//printf("result is %s\n", result);
		  	if(result[0] == '\0') { 
		  		//printf("evaluated to space.\n" );

		  	}
		  	else { //if it's operator
		  		//printf("top stack is %f\n", stack[stackPointer]);
		  		//printf("2nd last in stack is %f\n", stack[stackPointer-1]);
		  		float * p;
		  		//printf("%c evaluated to an operation.\n", result[0]);
		  		num1 = stack[stackPointer--];
		  		num2 = stack[stackPointer];
		  		//printf("num1: %f, num2: %f\n", num1,num2);
		  		p = &stack[stackPointer];
		 		applyOperation(num1, num2, result[0], p);
		  	}
		}else{ //if it's number
		  	//printf("%d evaluated to a number.\n", token);
			//printf("placing in stack %f\n", token);
		  	stackPointer++;
		  	stack[stackPointer] = token;
		}
	}
	printf("> ans %f\n", stack[0]);
	return 0;
}