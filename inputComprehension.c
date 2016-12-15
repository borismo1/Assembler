//BORIS MOROZOV
//I.D. 314396177



//inputComprehension.c Contains all the necessary functions for getting unstructured data from a file,
//parsing it and translating it to machine code.

//All the required standard libraries ,external variables,function prototypes and
//data-structures are defined in this header file.
#include "main.h"


//returns 1 for empty line 2 for comment line 3 for guidence line
//and 4 for instruction line, otherwise return -1
int lineType(char* line){
	if(isEmptyLine(line) == 1){
		printf("this line is eampty:%s",line);
		return 1;
	}
	else if(isComment(line) == 1){
		printf("this line is a comment:%s",line);
		return 2;
	}
	else if(isGuidence(line) == 1 && isGuidence(line) == 2 &&
			isGuidence(line) == 3 && isGuidence(line) == 4){
		printf("this line is Guidance-type line:%s",line);
		return 3;
	}
	else if(isInstruction(line) == 1){
		printf("this line is Instraction-type line:%s",line);
		return 4;
	}
	else{
		printf("this line is an abomination:%s",line);
		return -1;
	}
}


//returns 0 if the line is not empty and 1 otherwise.
int isEmptyLine(char *s){
	while(*s != '\0'){
		if(!isspace(*s)){
			return 0;
		}
		s++;
	}
	return 1;
}



//returns 1 if the supplied line is a comment line.
int isComment(char *s){
	if(*s == ';'){
		return 1;
	}
	return 0;
}



//returns 1 if the supplied line is .data line 2 for.string line 3 for entry
//and 4 for .extern . 0 otherwise.
int isGuidence(char* line){
	if(strstr(line,".data") != NULL){
		return 1;
	}
	else if(strstr(line,".string") != NULL){
			return 2;
	}
	else if(strstr(line,".entry") != NULL){
		return 3;
	}
	else if(strstr(line,".extern") != NULL){
		return 4;
	}
	else{
		return 0;
	}
}



//returns 0 to 15 if the supplied line is a recognized command and -1 otherwise.
int isInstruction(char* line){
	if(strstr(line,"mov") != NULL){
		return 0;
	}
	else if(strstr(line,"cmp") != NULL){
		return 1;
	}
	else if(strstr(line,"add") != NULL){
		return 2;
	}
	else if(strstr(line,"sub") != NULL){
		return 3;
	}
	else if(strstr(line,"lea") != NULL){
		return 6;
	}
	else if(strstr(line,"not") != NULL){
		return 4;
	}
	else if(strstr(line,"clr") != NULL){
		return 5;
	}
	else if(strstr(line,"inc") != NULL){
		return 7;
	}
	else if(strstr(line,"dec") != NULL){
		return 8;
	}
	else if(strstr(line,"jmp") != NULL){
		return 9;
	}
	else if(strstr(line,"bne") != NULL){
		return 10;
	}
	else if(strstr(line,"red") != NULL){
		return 11;
	}
	else if(strstr(line,"prn") != NULL){
		return 12;
	}
	else if(strstr(line,"jsr") != NULL){
		return 13;
	}
	else if(strstr(line,"rts") != NULL){
		return 14;
	}
	else if(strstr(line,"stop") != NULL){
		return 15;
	}
	else{
		return -1;
	}
}


//returns 1 if the function detects a Label (assumes correct input) and 0 otherwise.
int isLabeled(char* line){
	char *possibleLable ;
	char *lineDuplicate = my_strdup(line);
	possibleLable = strtok(lineDuplicate,":");
	if(strcmp(line,possibleLable) ==0){
		return 0;
	}
	return 1;
}


//extracts the label from the supplied instruction and returns a pointer to it.
char* extractLable(char* line){
	char *lineDuplicate = my_strdup(line);
	static char* token ;
	token = strtok(lineDuplicate,":");
	return token;
}


//detects the group of the instruction and return an integer representing the group,
int detectGroupNumber(char* line){
	if(strstr(line,"mov") != NULL || strstr(line,"cmp") != NULL || strstr(line,"add") != NULL
			 || strstr(line,"sub") != NULL || strstr(line,"lea") != NULL){
		return 1;
	}
	else if(strstr(line,"not") != NULL || strstr(line,"clr") != NULL || strstr(line,"inc") != NULL ||
			strstr(line,"dec") != NULL || strstr(line,"jmp") != NULL || strstr(line,"bne") != NULL ||
			strstr(line,"red") != NULL || strstr(line,"prn") != NULL || strstr(line,"jsr") != NULL){
		return 2;
	}
	else if(strstr(line,"rts") != NULL || strstr(line,"stop") != NULL){
		return 3;
	}
	else {
		return 0;
	}
}

//returns the pointer to the name of the destination operand
char* getDestanationOperand(char* line){
	char* lineDuplicate = my_strdup(line);
	static char* token;
	if(isLabeled(line) == 1){
		token = strtok(lineDuplicate," ");
		token = strtok(NULL," ");
		token = strtok(NULL,",");
		token = strtok(NULL,",");
		strip(token);
		return token;
	}
	token = strtok(lineDuplicate,",");
	token = strtok(NULL," ");
	return token;
}

//returns the pointer to the name of the source operand
char* getSourceOperand(char* line){
	char* lineDuplicate = my_strdup(line);
	static char* token;
	if(isLabeled(line) == 1){
		token = strtok(lineDuplicate," ");
		token = strtok(NULL," ");
		token = strtok(NULL,",");
		return token;
	}
	token = strtok(lineDuplicate," ");
	token = strtok(NULL,",");
	strtok(token," ");
	return token;
}


//in case of instruction with one operand returns a pointer to the name of the only operand.
char* getOnlyOperand(char* line){
	char* lineDuplicate = my_strdup(line);
	static char* token;
	if(isLabeled(line) == 1){
		token = strtok(lineDuplicate," ");
		token = strtok(NULL," ");
		token = strtok(NULL,"\n");
		return token;
	}
	token = strtok(lineDuplicate," ");
	token = strtok(NULL," ");
	strip(token);
	return token;
}

//returns the pointer to the string value of .string type guidance line
char* getString(char* line){
	char* lineDuplicate = my_strdup(line);
	static char* token;
	token = strtok(lineDuplicate,"\"");
	token = strtok(NULL,"\"");
	return token;
}

//based on the operand type returns the relevant addressing type .
int addressingTypeDetection(char* operand){
	if(strstr(operand,"#") != NULL){
		return 0;
	}
	else if(isKnownSymbol(operand) == 1){
		return 1;
	}
	else if(strstr(operand,"[") != NULL && strstr(operand,"]") != NULL){
		return 2;
	}
	else if(isRegister(operand)==1){
		return 3;
	}
	return -1;
}



//returns an array representing numbers 1-4 in binary. (used auxiliary struct for easer array passing)
struct BinaryNumber toBinary(int decimal){
	struct BinaryNumber output;
	switch(decimal){
	case 0:
		output.bits[0] = 0;
		output.bits[1] = 0;
		break;
	case 1:
		output.bits[0] = 1;
		output.bits[1] = 0;
		break;
	case 2:
		output.bits[0] = 0;
		output.bits[1] = 1;
		break;
	case 3:
		output.bits[0] = 1;
		output.bits[1] = 1;
		break;
	default:
		printf("outofScope\n");
	}
	return output;
}


//turns out "strdup" is not part of ANSI C so I define it by hand to maintain pure ANSI code.
char* my_strdup(const char *input){
	char *output = malloc(strlen(input) + 1);
	if(output){
		strcpy(output,input);
	}
	return output;
}


//all following functions are for initializing of Instruction struct with
//relevant members after parsing instruction-type line from input.
//divided into three groups.

/////////////// group 1 instructions///////////////////////////////////////


struct Instruction movCommandToStruct(char* line){
	int bit1[2],bit2[2] ;
	bit1[0] = toBinary(addressingTypeDetection(getSourceOperand(line))).bits[0];
	bit1[1] = toBinary(addressingTypeDetection(getSourceOperand(line))).bits[1];
	bit2[0] = toBinary(addressingTypeDetection(getDestanationOperand(line))).bits[0];
	bit2[1] = toBinary(addressingTypeDetection(getDestanationOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,1,0,0,0,0,0,bit1[1],bit1[0],bit2[1],bit2[0],0,0}};
	return output;
}

struct Instruction cmpCommandToStruct(char* line){
	int bit1[2],bit2[2] ;
	bit1[0] = toBinary(addressingTypeDetection(getSourceOperand(line))).bits[0];
	bit1[1] = toBinary(addressingTypeDetection(getSourceOperand(line))).bits[1];
	bit2[0] = toBinary(addressingTypeDetection(getDestanationOperand(line))).bits[0];
	bit2[1] = toBinary(addressingTypeDetection(getDestanationOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,1,0,0,0,0,1,bit1[1],bit1[0],bit2[1],bit2[0],0,0}};
	return output;
}

struct Instruction addCommandToStruct(char* line){
	int bit1[2],bit2[2] ;
	bit1[0] = toBinary(addressingTypeDetection(getSourceOperand(line))).bits[0];
	bit1[1] = toBinary(addressingTypeDetection(getSourceOperand(line))).bits[1];
	bit2[0] = toBinary(addressingTypeDetection(getDestanationOperand(line))).bits[0];
	bit2[1] = toBinary(addressingTypeDetection(getDestanationOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,1,0,0,0,1,0,bit1[1],bit1[0],bit2[1],bit2[0],0,0}};
	return 	output;
}


struct Instruction subCommandToStruct(char* line){
	int bit1[2],bit2[2] ;
	bit1[0] = toBinary(addressingTypeDetection(getSourceOperand(line))).bits[0];
	bit1[1] = toBinary(addressingTypeDetection(getSourceOperand(line))).bits[1];
	bit2[0] = toBinary(addressingTypeDetection(getDestanationOperand(line))).bits[0];
	bit2[1] = toBinary(addressingTypeDetection(getDestanationOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,1,0,0,0,1,1,bit1[1],bit1[0],bit2[1],bit2[0],0,0}};
	return output;
}

struct Instruction leaCommandToStruct(char* line){
	int bit1[2],bit2[2] ;
	bit1[0] = toBinary(addressingTypeDetection(getSourceOperand(line))).bits[0];
	bit1[1] = toBinary(addressingTypeDetection(getSourceOperand(line))).bits[1];
	bit2[0] = toBinary(addressingTypeDetection(getDestanationOperand(line))).bits[0];
	bit2[1] = toBinary(addressingTypeDetection(getDestanationOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,1,0,0,1,1,0,bit1[1],bit1[0],bit2[1],bit2[0],0,0}};
	return output;
}

////////////////group 2 instructions///////////////////////////////////////

struct Instruction notCommandToStruct(char* line){
	int bit[2] ;
	bit[0] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[0];
	bit[1] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,0,1,0,1,0,0,0,0,bit[1],bit[0],0,0}};
	return output;
}

struct Instruction clrCommandToStruct(char* line){
	int bit[2] ;
	bit[0] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[0];
	bit[1] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,0,1,0,1,0,1,0,0,bit[1],bit[0],0,0}};
	return output;
}

struct Instruction incCommandToStruct(char* line){
	int bit[2] ;
	bit[0] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[0];
	bit[1] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,0,1,0,1,1,1,0,0,bit[1],bit[0],0,0}};
	return output;
}

struct Instruction decCommandToStruct(char* line){
	int bit[2] ;
	bit[0] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[0];
	bit[1] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,0,1,1,0,0,0,0,0,bit[1],bit[0],0,0}};
	return output;
}


struct Instruction jmpCommandToStruct(char* line){
	int bit[2] ;
	bit[0] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[0];
	bit[1] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,0,1,1,0,0,1,0,0,bit[1],bit[0],0,0}};
	return output;
}


struct Instruction bneCommandToStruct(char* line){
	int bit[2] ;
	bit[0] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[0];
	bit[1] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,0,1,1,0,1,0,0,0,bit[1],bit[0],0,0}};
	return output;
}

struct Instruction redCommandToStruct(char* line){
	int bit[2] ;
	bit[0] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[0];
	bit[1] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,0,1,1,0,1,1,0,0,bit[1],bit[0],0,0}};
	return output;
}


struct Instruction prnCommandToStruct(char* line){
	int bit[2] ;
	bit[0] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[0];
	bit[1] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,0,1,1,1,0,0,0,0,bit[1],bit[0],0,0}};
	return output;
}

struct Instruction jsrCommandToStruct(char* line){
	int bit[2] ;
	bit[0] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[0];
	bit[1] = toBinary(addressingTypeDetection(getOnlyOperand(line))).bits[1];
	struct Instruction output = {{1,0,1,0,1,1,1,0,1,0,0,bit[1],bit[0],0,0}};
	return output;
}

//////////////group 3 instructions//////////////////////////////////////////////////////
struct Instruction rtsCommandToStruct(char* line){
	struct Instruction output = {{1,0,1,0,0,1,1,1,0,0,0,0,0,0,0}};
	return output;
}


struct Instruction stopCommandToStruct(char* line){
	struct Instruction output = {{1,0,1,0,0,1,1,1,1,0,0,0,0,0,0}};
	return output;
}



