//Programming Porject 2
//Author: Leon Magbanua
#include <stdio.h>
#include <string.h>

#define FILENAME "Programming-Project-3.txt"
#define ARRAY_MAX 20

//Function Declarations
void doMath(FILE* reading, char operation[], int reg[]);
void setRegistersAndFlags(int reg[], int flags[]);
/*displayMovOperands();
displayShiftOperands();
displayNoResultOperands();
displayOtherwise();*/

void showRegisters(int reg[]);

//Main
int main(){
    FILE* dataFile;
    signed int operand1, operand2, operand3;
    int NZCV[4];
    int registers[8];
    char operation[ARRAY_MAX];
    dataFile = fopen(FILENAME, "r");
    setRegistersAndFlags(registers, NZCV);

    //reads from file
    if (dataFile == NULL){
		printf("Issue opening file.\n");
	}else{
        while(fscanf(dataFile, "%s", operation) != EOF){
            doMath(dataFile, operation, registers);
        }   
    }
    fclose(dataFile);

    return 0;
}

//Function Definitions
void setRegistersAndFlags(int reg[], int flags[]){
    for(int i = 0; i < 8; i++){
        reg[i] = 0;
    }
    for(int i = 0; i < 4; i++){
        flags[i] = 0;
    }
}

void doMath(FILE* reading, char operation[], int reg[]){
    signed int registerA, registerB, registerC, immediateVal;
    char rval1, rval2, rval3;
    if((strcmp(operation, "mov") == 0)||(strcmp(operation, "MOV") == 0)){
        fscanf(reading, " %c%i, #%X", &rval1, &registerA, &immediateVal);
        reg[registerA] = immediateVal;
        printf("%s %c%i, #0x%08X \n", operation, rval1, registerA, immediateVal);
    }else if((strcmp(operation, "ADDS") == 0)||(strcmp(operation, "adds") == 0)||(strcmp(operation, "ADD") == 0)||(strcmp(operation, "add") == 0)){
        fscanf(reading, " %c%i, %c%i, %c%i", &rval1, &registerA, &rval2, &registerB, &rval3, &registerC);
        reg[registerA] = reg[registerB] + reg[registerC];
        printf("%s %c%i, %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB, rval3, registerC);
    }else if((strcmp(operation, "SUBS") == 0)||(strcmp(operation, "subs") == 0)||(strcmp(operation, "SUB") == 0)||(strcmp(operation, "sub") == 0)){
        fscanf(reading, " %c%i, %c%i, %c%i", &rval1, &registerA, &rval2, &registerB, &rval3, &registerC);
        reg[registerA] = reg[registerB] - reg[registerC];
        printf("%s %c%i, %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB, rval3, registerC);
    }else if((strcmp(operation, "ANDS") == 0)||(strcmp(operation, "ands") == 0)||(strcmp(operation, "AND") == 0)||(strcmp(operation, "and") == 0)){
        fscanf(reading, " %c%i, %c%i, %c%i", &rval1, &registerA, &rval2, &registerB, &rval3, &registerC);
        reg[registerA] = reg[registerB] & reg[registerC];
        printf("%s %c%i, %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB, rval3, registerC);
    }else if((strcmp(operation, "ORRS") == 0)||(strcmp(operation, "orrs") == 0)||(strcmp(operation, "ORR") == 0)||(strcmp(operation, "orr") == 0)){
        fscanf(reading, " %c%i, %c%i, %c%i", &rval1, &registerA, &rval2, &registerB, &rval3, &registerC);
        reg[registerA] = reg[registerB] | reg[registerC];
        printf("%s %c%i, %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB, rval3, registerC);
    }else if((strcmp(operation, "XORS") == 0)||(strcmp(operation, "xors") == 0)||(strcmp(operation, "XOR") == 0)||(strcmp(operation, "xor") == 0)){
        fscanf(reading, " %c%i, %c%i, %c%i", &rval1, &registerA, &rval2, &registerB, &rval3, &registerC);
        reg[registerA] = reg[registerB] ^ reg[registerC];
        printf("%s %c%i, %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB, rval3, registerC);
    }else if((strcmp(operation, "LSRS") == 0)||(strcmp(operation, "lsrs") == 0)||(strcmp(operation, "LSR") == 0)||(strcmp(operation, "lsr") == 0)){
        
    }else if((strcmp(operation, "LSLS") == 0)||(strcmp(operation, "lsls") == 0)||(strcmp(operation, "LSL") == 0)||(strcmp(operation, "lsl") == 0)){
        
    }else if((strcmp(operation, "CMP") == 0)||(strcmp(operation, "cmp") == 0)){
        
    }else if((strcmp(operation, "TST") == 0)||(strcmp(operation, "tst") == 0)){
        
    }else{
        printf("Error! \n");
    }


}

void showRegisters(int reg[]){
    for(int i = 0; i < 8; i++){
        printf("R%i: 0x%08X  ", i, reg[i]);
    }
    printf("\n");
}

