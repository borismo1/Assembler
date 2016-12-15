//BORIS MOROZOV



//firstPass.c Contains all the functions associated with the the first pass of our algorithm
//on the supplied input.


//All the required standard libraries ,external variables,function prototypes and
//data-structures are defined in this header file.
#include "main.h"




//read the input line by line and invokes the relevant algorithm step.
void firstPass(char* filename){
	strip(filename);
	char buff[80];
		FILE *inputfile;
		inputfile = fopen(filename,"r");
		if(inputfile == NULL){
			perror("Error opening file");
			exit(0);
		}
		while(fgets(buff,sizeof(buff),inputfile)){
			if(isEmptyLine(buff) == 1){
			}
			else if(isComment(buff) == 1){
			}
			else if(isGuidence(buff) == 1){
				dataLineStep(buff);
			}
			else if(isGuidence(buff) == 2){
				stringLineStep(buff);
			}
			else if(isGuidence(buff) == 4){
				externLineStep(buff);
			}
			else if(isInstruction(buff) !=-1 ){
				switch(detectGroupNumber(buff)){
				case 1:
					instructionOfGroupOneStep(buff);
					break;
				case 2:
					instructionOfGroupTwoStep(buff);
					break;
				case 3:
					instructionOfGroupThreeStep(buff);
					break;
				default:
					printf("unknown group");
				}
			}
		}
	instructionTableSize = IC -100;
	dataTableSize = DC;
	updateDataItemAdress();
	mergeDataAndInstructions();
	IC = 100;
	DC = 0;
	fclose(inputfile);
}


//copy data table to the instruction table
void mergeDataAndInstructions(){
	for(int i =0;i< dataTableSize;i++){
		insertInstructionFromArray(dataTable[i]);
	}
}


//this function is responsible for updating the addresses in the symbolTable
void updateDataItemAdress(){
	for(int i=0;i <SP;i++){
		if(symbolTable[i].isExternal !=1 && symbolTable[i].lineType == 1){
			symbolTable[i].address = symbolTable[i].address + 100 + instructionTableSize;
		}
	}
}


//this step is invoked when our algorithm encounters data guidance line.
void dataLineStep(char* line){
	char* lineDuplicate = my_strdup(line);
	static char* token;
	if(isLabeled(line) == 1){
		insertSymbol(extractLable(line),DC,0,1);
		token = strtok(lineDuplicate," ");
		token = strtok(NULL," ");
		token = strtok(NULL," ");
	}
	else{
		token = strtok(lineDuplicate," ");
		token = strtok(NULL," ");
	}
	token  = strtok(token,",");
	if(strstr(token,"-")!= NULL){
		insertDataItem(negateBinary(toArray(decimalToBinary(-1*atoi(token)))));
	}
	else{
		insertDataItem(toArray(decimalToBinary(atoi(token))));
	}
	while((token = strtok(NULL,",")) != NULL){
		if(strstr(token,"-")!= NULL){
			insertDataItem(negateBinary(toArray(decimalToBinary(-1*atoi(token)))));
		}
		else{
			insertDataItem(toArray(decimalToBinary(atoi(token))));
		}
	}
}


//this step is invoked when our algorithm encounters external guidance line.
void externLineStep(char* line){
	char* lineDuplicate = my_strdup(line);
	insertSymbol(getOnlyOperand(lineDuplicate),0,1,3);
}



//this step is invoked when our algorithm encounters group one instruction type line.
void instructionOfGroupOneStep(char* line){
	if(isLabeled(line) == 1){
		insertSymbol(extractLable(line),IC,0,2);
	}
	int sourceOperandAddressingType = addressingTypeDetection(getSourceOperand(line));
	int destanationOperandAddressingType = addressingTypeDetection(getDestanationOperand(line));
	if(sourceOperandAddressingType == 3 && destanationOperandAddressingType == 3){
		IC= IC+2;
	}
	else{
		IC = IC+3;
	}

}

//this step is invoked when our algorithm encounters group two instruction type line.
void instructionOfGroupTwoStep(char* line){
	if(isLabeled(line) == 1){
		insertSymbol(extractLable(line),IC,0,2);
	}
	IC = IC + 2;
}

//this step is invoked when our algorithm encounters group three instruction type line.
void instructionOfGroupThreeStep(char* line){
	if(isLabeled(line) == 1){
		insertSymbol(extractLable(line),IC,0,2);
	}
	++IC;
}


//return a binary representation of the supplied integer (its still a decimal int)
//for 5 it will return 101 = "one hundred and one" .
long decimalToBinary(long n) {
    int remainder;
    long binary = 0, i = 1;

    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}


//will return a pointer to array containing one digit of the supplied integer in every index of the array
int * toArray(int number){
    int n = log10(number) + 1;
    int i;
    int *numberArray = calloc(15, sizeof(int));
    for ( i = 0; i < n; ++i, number /= 10 )
    {
        numberArray[i] = number % 10;
    }
    return numberArray;
}


//will return a binary representation on the supplied char (in 15 bit format)
int* charToBinary(char input){
	int *numberArray = calloc(15, sizeof(int));
	int temp = decimalToBinary(input);
	int *aux = toArray(temp);
	for(int i=0;i<15;i++){
		if(i < sizeof(aux)){
			numberArray[i] = aux[i];
		}
		else{
			numberArray[i] = 0;
		}
	}
	return numberArray;
}

//this step is invoked when we encounter .string guidance line.
void stringLineStep(char* input){
	int i=0;
	char* temp = getString(input);
	if(isLabeled(input) == 1){
		insertSymbol(extractLable(input),DC,0,1);
	}
	while(temp[i] != '\0'){
		insertDataItem(charToBinary(temp[i]));
		++i;
	}
	insertDataItem(zeroLine);
}

//return the negation of a number using two's compliment representation
int* negateBinary(int input[15]){
	static int output[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	for(int i =0;i<15;i++){
		if(input[i] == 1){
			output[i] =0;
		}
		else if(input[i] == 0){
			output[i] =1;
		}
		else{
			printf("SOMETHING WENT TERRABLY WRONG NOT 1 OR 0!");
			exit(0);
		}
	}
	for(int j =0;j<15;j++){
		if(output[j] == 1){
			output[j] = 0;
		}
		else if(output[j] == 0){
			output[j] = 1;
			return output;
		}
	}
	return output;
}
