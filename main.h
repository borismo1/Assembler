//BORIS MOROZOV



//The only Header file in this project, its included in all the c source files.
//It contains all the necessary standard libraries includes and all the prototypes for this project.
#ifndef MAIN_H_
#define MAIN_H_


//standard libraries I used for this project.
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

//functions prototypes from: "inputComprehension.c", "dataAndPointers.c", "firstPass.c" and "secondPass.c".

//Prototypes from "inputComprehension.c"
char* my_strdup(const char*);
int lineReader();
int isEmptyLine(char*);
int isComment(char*);
int isGuidence(char*);
int isInstruction(char*);
int isLabeled(char*);
int detectGroupNumber(char*);
int addressingTypeDetection(char*);
char* getDestanationOperand(char*);
char* getSourceOperand(char*);
char* getOnlyOperand(char*);
char* extractLable(char*);
char* getString(char* line);
struct BinaryNumber toBinary(int);
struct Instruction movCommandToStruct(char*);
struct Instruction addCommandToStruct(char* line);
struct Instruction subCommandToStruct(char* line);
struct Instruction cmpCommandToStruct(char* line);
struct Instruction leaCommandToStruct(char* line);
struct Instruction notCommandToStruct(char* line);
struct Instruction clrCommandToStruct(char* line);
struct Instruction incCommandToStruct(char* line);
struct Instruction decCommandToStruct(char* line);
struct Instruction jmpCommandToStruct(char* line);
struct Instruction bneCommandToStruct(char* line);
struct Instruction redCommandToStruct(char* line);
struct Instruction prnCommandToStruct(char* line);
struct Instruction jsrCommandToStruct(char* line);
struct Instruction rtsCommandToStruct(char* line);
struct Instruction stopCommandToStruct(char* line);

//Prototypes from "dataAndPointers.c"
int isRegister(char*);
int isKnownSymbol(char*);
void printDataTable();
void printSymbolTable();
void printInstructionTable();
void insertSymbol(char*,int,int,int);
void insertDataItem(int[15]);
void insertInstruction(struct Instruction);
char* concat(char*, char*);
void insertInstructionFromArray(int*);
void strip(char *);
int isExternal(char*);
struct Instruction reverseInstruction(struct Instruction);

//Prototypes from "firtsPass.c"
long decimalToBinary(long);
void dataLineStep(char*);
int * toArray(int );
int* charToBinary(char);
void stringLineStep(char*);
void externLineStep(char* );
int* negateBinary(int input[15]);
void firstPass(char*);
void instructionOfGroupOneStep(char*);
void instructionOfGroupTwoStep(char*);
void instructionOfGroupThreeStep(char*);
void updateDataItemAdress();
void mergeDataAndInstructions();

//Prototypes from "secondPass.c"

void printMachineWord(struct Instruction);
struct Instruction instantAddressing(char*);
struct Instruction directAddressing(char*);
int getDataAddress(char*);
struct Instruction dynamicAddressing(char*);
struct Instruction sourceRegisterAdressing(char*);
struct Instruction destanationRegisterAdressing(char*);
struct Instruction doubleRegisterAddressing(char*,char*);
void secondPass(char*);

//Prototypes from "octalSpecial.c"
char* binaryToSuperOctal(struct Instruction);
char* decimalToSuperOctal(int);

//A simple struct containing integer array of size 15.
struct Instruction{
	int bits[15];
};

//A simple struct containing 4 fields to describe a symbol.
struct symbol{
	char *lable;
	int address;
	int isExternal; //1 means external 0 means local
	int lineType; //1 for guidance , 2 for instruction and 3 for unknown

};



//will be removed later (hopefully)
struct BinaryNumber{
	int bits[2];
};


//external variables mostly pointer and tables relevant for two pass algorithm.
extern char registerNames[11][3];
extern int IC;
extern int DC;
extern int SP;
extern struct Instruction instructionTable[1000];
extern int dataTable[1000][15];
extern struct symbol symbolTable[1000];
extern int zeroLine[15];
extern int instructionTableSize;
extern int dataTableSize;


#endif /* MAIN_H_ */
