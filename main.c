//BORIS MOROZOV



#include "main.h"

//puts everything together
int main(int argc, char **argv) {
		char* buff = argv[1];
		fgets(buff,30,stdin);
		strip(buff);
		firstPass(buff);
		secondPass(buff);
		char* filename = strtok(buff,".");
		FILE* output;
		output = fopen(concat(filename,".ob"),"w");
		fprintf(output, "%s\t%s \n\n",decimalToSuperOctal(instructionTableSize),decimalToSuperOctal(dataTableSize));
		for(int i =100;i< 100 + instructionTableSize + dataTableSize ;i++){
			fprintf(output, "%s\t%s\n",decimalToSuperOctal(i),binaryToSuperOctal(instructionTable[i]));
		}
		fclose(output);
}



