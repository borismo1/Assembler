//BORIS MOROZOV


#include "main.h"



void secondPass(char* filename){
	char buff[80];
	char* dup = my_strdup(filename);
	FILE *inputfile;
	FILE *entry;
	FILE *exter;
	char* file = strtok(dup,".");
	exter = fopen(concat(file,".ext"),"w");
	entry = fopen(concat(file,".ent"),"w");
	inputfile = fopen(filename,"r");
	if(inputfile == NULL){
		perror("Error opening file");
			exit(0);
		}
		while(fgets(buff,sizeof(buff),inputfile)){
			strip(buff);
			if(isGuidence(buff) == 3){
				fprintf(entry,"%s %s\n",getOnlyOperand(buff),decimalToSuperOctal(getDataAddress(getOnlyOperand(buff))));
			}
			else if(isInstruction(buff) !=-1 ){
				switch(isInstruction(buff)){
					case 0:
						insertInstruction(movCommandToStruct(buff));
						break;
					case 1:
						insertInstruction(cmpCommandToStruct(buff));
						break;
					case 2:
						insertInstruction(addCommandToStruct(buff));
						break;
					case 3:
						insertInstruction(subCommandToStruct(buff));
						break;
					case 4:
						insertInstruction(notCommandToStruct(buff));
						break;
					case 5:
						insertInstruction(clrCommandToStruct(buff));
						break;
					case 6:
						insertInstruction(leaCommandToStruct(buff));
						break;
					case 7:
						insertInstruction(incCommandToStruct(buff));
						break;
					case 8:
						insertInstruction(decCommandToStruct(buff));
						break;
					case 9:
						insertInstruction(jmpCommandToStruct(buff));
						break;
					case 10:
						insertInstruction(bneCommandToStruct(buff));
						break;
					case 11:
						insertInstruction(redCommandToStruct(buff));
						break;
					case 12:
						insertInstruction(prnCommandToStruct(buff));
						break;
					case 13:
						insertInstruction(jsrCommandToStruct(buff));
						break;
					case 14:
						insertInstruction(rtsCommandToStruct(buff));
						break;
					case 15:
						insertInstruction(stopCommandToStruct(buff));
						break;
				}
				switch(detectGroupNumber(buff)){
					case 1:
						switch(addressingTypeDetection(getSourceOperand(buff))){
							case 0:
								insertInstruction(instantAddressing(getSourceOperand(buff)));
								break;
							case 1:
								if(isExternal(getSourceOperand(buff)) == 1){
									fprintf(exter," %s %s\n",getSourceOperand(buff),decimalToSuperOctal(IC));
								}
								insertInstruction(directAddressing((getSourceOperand(buff))));
								break;
							case 2:
								insertInstruction(dynamicAddressing(getSourceOperand(buff)));
								break;
							case 3:
								if(addressingTypeDetection(getDestanationOperand(buff)) == 3){
									insertInstruction(doubleRegisterAddressing(getSourceOperand(buff),getDestanationOperand(buff)));
								}
								else{
									insertInstruction(sourceRegisterAdressing(getSourceOperand(buff)));
								}
						}
						switch (addressingTypeDetection(getDestanationOperand(buff))) {
							case 0:
								insertInstruction(instantAddressing(getDestanationOperand(buff)));
								break;
							case 1:
								if(isExternal(getDestanationOperand(buff)) == 1){
									fprintf(exter," %s %s\n",getDestanationOperand(buff),decimalToSuperOctal(IC));
								}
								insertInstruction(directAddressing(getDestanationOperand(buff)));
								break;
							case 2:
								insertInstruction(dynamicAddressing(getDestanationOperand(buff)));
								break;
							case 3:
								if(addressingTypeDetection(getSourceOperand(buff)) == 3){
								}
								else{
									insertInstruction(destanationRegisterAdressing(getDestanationOperand(buff)));
								}

						}
						break;
					case 2:
						switch(addressingTypeDetection(getOnlyOperand(buff))){
							case 0:
								insertInstruction(instantAddressing(getOnlyOperand(buff)));
								break;
							case 1:
								if(isExternal(getSourceOperand(buff)) == 1){
									fprintf(exter," %s %s\n",getSourceOperand(buff),decimalToSuperOctal(IC));
								}
								insertInstruction(directAddressing(getOnlyOperand(buff)));
								break;
							case 2:
								insertInstruction(dynamicAddressing(getOnlyOperand(buff)));
								break;
							case 3:
								insertInstruction(destanationRegisterAdressing(getOnlyOperand(buff)));
								break;
						}
				}
			}
		}
	fclose(exter);
	fclose(entry);
	fclose(inputfile);
}



//the next family of functions is responsible for generating extra words that follow instructions.

struct Instruction instantAddressing(char* line){
	char* duplicate = my_strdup(line);
	int input = atoi(strtok(duplicate,"#"));
	static int output[15];
	if(input <0 ){
		int temp = decimalToBinary(input*(-1));
		for(int i =0;i<13;i++){
			output[12 -i]= negateBinary(toArray(temp))[i];
		}
	}
	else{
		int temp = decimalToBinary(input);
		for(int i =0;i<13;i++){
			output[i]= toArray(temp)[i];
		}
	}
	output[14] =0;
	output[13] =0;
	struct Instruction out ;
	for(int i =0;i<15;i++){
		out.bits[i] = output[i];
	}
	return out;
}


struct Instruction directAddressing(char* input){
	int address = getDataAddress(input);
	static int output[15];
	for(int i =0;i < 13;i++){
		output[12 -i] = toArray(decimalToBinary(address))[i];
	}
	if(isExternal(input) == 0){
		output[14]=0;
		output[13] =1;
	}
	else{
		output[14]=1;
		output[13] =0;
	}
	struct Instruction out;
	for(int i =0;i<15;i++){
		out.bits[i] = output[i];
	}
	return out;
}

struct Instruction dynamicAddressing(char* input){
	char* duplicate = my_strdup(input);
	char* name = strtok(duplicate,"[");
	int start = atoi(strtok(NULL,"-")) ;
	int end = atoi(strtok(NULL,"]")) ;
	struct Instruction output;
	for(int i=0; i<13;i++){
		if(i <= end - start){
			output.bits[i] = instructionTable[getDataAddress(name)].bits[14 -start -i ];
		}
		else if(output.bits[end -start] == 1){
			output.bits[i] =1;
		}
		else if(output.bits[end -start] == 0){
			output.bits[i] =0;
		}
	}
	struct Instruction output1;
	for(int i=0;i<13;i++){
		output1.bits[12-i] = output.bits[i];
	}
	output1.bits[13] =0;
	output1.bits[14] =0;
	return output1;
}


struct Instruction sourceRegisterAdressing(char* line){
	int binary = decimalToBinary(atoi(&line[1]));
	static int output[15];
	for(int i=1;i <7;i++){
		output[7 -i] = toArray(binary)[i-1];
	}
	struct Instruction out ;
	for(int i =0;i<15;i++){
		out.bits[i] = output[i];
	}
	return out;
}

struct Instruction destanationRegisterAdressing(char* line){
	int binary = decimalToBinary(atoi(&line[1]));
	static int output[15];
	for(int i=7;i <13;i++){
		output[19 -i] = toArray(binary)[i-7];
	}
	struct Instruction out ;
	for(int i =0;i<15;i++){
		out.bits[i] = output[i];
	}
	return out;
}

struct Instruction doubleRegisterAddressing(char* arg1,char* arg2){
	static int output[15];
	int binary1 = decimalToBinary(atoi(&arg1[1]));
	int binary2 = decimalToBinary(atoi(&arg2[1]));
	for(int i=1 ; i <13 ;i++){
		if(i < 7){
			output[7 -i] = toArray(binary1)[i-1];
		}
		else{
			output[19 -i] = toArray(binary2)[i-7];
		}
	}
	struct Instruction out;
	for(int i =0;i<15;i++){
		out.bits[i] = output[i];
	};
	return out;
}



//returns the line of the requested data item. returns -1 if irs not found
int getDataAddress(char* input){
	strip(input);
	for(int i=0;i < SP;i++){
		if(strcmp(symbolTable[i].lable,input) == 0){
			return symbolTable[i].address;
		}
	}
	return -1;
}


//prints the bit array of the supplied struct
void printMachineWord(struct Instruction input){
	for(int i =0;i<15;i++){
		printf("%d",input.bits[i]);
	}
	printf("\n");
}




