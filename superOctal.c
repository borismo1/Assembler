//BORIS MOROZOV

#include "main.h"



// binary to "super" octal

char* binaryToSuperOctal(struct Instruction input){
	struct Instruction revInst = reverseInstruction(input);
	char* output = "";
	char* currchar = "";
	for(int i =0;i<15;i = i+3){
		int temp =0;
		for(int j =0;j<3;j++){
			temp = temp +revInst.bits[i + j] * pow(2,j);
		}
		switch(temp){
		case 0:
			currchar = "!";
			break;
		case 1:
			currchar = "@";
			break;
		case 2:
			currchar = "#";
			break;
		case 3:
			currchar = "$";
			break;
		case 4:
			currchar = "%";
			break;
		case 5:
			currchar = "^";
			break;
		case 6:
			currchar = "&";
			break;
		case 7:
			currchar = "*";
			break;
		}
		output = concat(currchar,output);
	}
	return output;
}

//decimal to "super" octal

char* decimalToSuperOctal(int input){
    int rem, i=1, octal=0;
    while (input!=0)
    {
        rem=input%8;
        input/=8;
        octal+=rem*i;
        i*=10;
    }
    char* output="";
    while(10*octal / 10 !=0){
    	switch(octal % 10){
    	case 0:
    		output = concat("!",output);
    		break;
    	case 1:
    		output = concat("@",output);
    		break;
    	case 2:
    		output = concat("#",output);
    		break;
    	case 3:
    		output = concat("$",output);
    		break;
    	case 4:
    		output = concat("%",output);
    		break;
    	case 5:
    		output = concat("^",output);
    		break;
    	case 6:
    		output = concat("&",output);
    		break;
    	case 7:
    		output = concat("*",output);
    		break;
    	}
    	octal = octal /10;
    }
    return output;

}




