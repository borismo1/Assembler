//BORIS MOROZOV
//I.D. 314396177



//dataAndPointers.c contains all the external variables and all the functions required
//for maintaining the data structures and counters used in this project.

//All the required standard libraries ,external variables,function prototypes and
//data-structures are defined in this header file.
#include "main.h"

//names saved for registers , pointers and counters.
char registerNames[11][3] = {"r0","r1","r2","r3","r4","r5","r6","r7","IC","DP","SP"};

//pointers
int IC =100;
int DC =0;
int SP =0;


//this variables will be initialized after the first pass of the our algorithm on the input.
int instructionTableSize = 0;
int dataTableSize = 0;

//instructionTable will hold all the instructions lines after the second pass of the algorithm.
struct Instruction instructionTable[1000];

//dataTable will hold all the data items after first pass of the algorithm.
int dataTable[1000][15];

//symbolTable will holds all the symbols we encounter on the first pass .
struct symbol symbolTable[1000];

//this line is inserted into the data segment after the last char of the string.
int zeroLine[15]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


//insert a symbol into the symbolTable and maintain relevant counters.
void insertSymbol(char* name,int address,int isext,int lineType){
	strip(name);
	struct symbol newitem = {name,address,isext,lineType};
	symbolTable[SP] = newitem;
	++SP;
}


//returns 1 if the supplied symbol is a member of the symbolTable and 0 otherwise
int isKnownSymbol(char* sym){
	strip(sym);
	for(int i=0;i<SP;i++){
		if(strcmp(symbolTable[i].lable,sym) == 0 ){
			return 1;
		}
	}
	return 0;
}

//since string concatenation is not part of ANSI I define one by hand .
char* concat(char *s1, char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

//inserts an Instruction struct into the InstructionTable and maintain relevant counters.
void insertInstruction(struct Instruction input){
	instructionTable[IC] = input;
	IC++;
}

void insertInstructionFromArray(int* input){
	struct Instruction newitem;
	for(int i =0;i<15;i++){
		newitem.bits[i] = input[i];
	}
	instructionTable[IC] = newitem;
	IC++;
}

//insert data to dataTable and maintain relevant counters.
void insertDataItem(int input[15]){
	for(int i=0;i<15;i++){
		dataTable[DC][14 -i] = input[i];
	}
	DC++;
}


//returns 1 if the supplied string is a register name.
//ignores new line char at the end. for input = "r4\n" will return 1
int isRegister(char* name){
	for(int i =0; i<11;i++){
		if(  strcmp(name,registerNames[i]) == 0 || strcmp( name , concat(registerNames[i],"\n")) ==0){
			return 1;
		}
	}
	return 0;
}


//print the contents of the dataTable for testing purposes
void printDataTable(){
	for(int i = 0;i< DC;i++){
		printf("item number %d in Data table is\t",i);
		for(int j =0;j<15;j++){
			printf("%d",dataTable[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}


//print the contents of the instructionTable for testing purposes
void printInstructionTable(){
	for(int i=100;i< instructionTableSize +100 +dataTableSize;i++){
		printf("item number %d in Instruction table is\t",i);
		for(int j=0;j<15;j++){
			printf("%d",instructionTable[i].bits[j]);
		}
		printf("\n");
	}
	printf("\n");
}


//print the contents of the symbolTable for testing purposes
void printSymbolTable(){
	for(int i =0;i<SP;i++){
		printf("item number %d in Symbol table is\t",i);
		printf("%s   %d   %d   %d\n",symbolTable[i].lable,symbolTable[i].address,symbolTable[i].isExternal,
				symbolTable[i].lineType);
	}
	printf("\n");
}


//remove '\n' and '\t' at the end of the string
void strip(char *s) {
	int i=0;
    while(s[i] != '\0') {
    	if(s[i] == '\n'){
    		s[i] = '\0';
    		return;
    	}
    	i++;
    }
}


//returns 1 if variable is external
int isExternal(char* name){
	strip(name);
	for(int i=0;i < SP;i++){
		if(strcmp(name,symbolTable[i].lable) == 0){
			if(symbolTable[i].isExternal ==1){
				return 1;
			}
		}
	}
	return 0;
}


//reverse instruction bit array
struct Instruction reverseInstruction(struct Instruction input){
	struct Instruction output;
	for(int i = 0; i< 15;i++){
		output.bits[14-i] = input.bits[i];
	}
	return output;
}
