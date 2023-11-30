//Programming Porject 2
//Author: Leon Magbanua
#include <stdio.h>
#include <string.h>

#define FILENAME "Programming-Project-3.txt"
#define ARRAY_MAX 20

//Function Declarations
void doMath(FILE* reading, char operation[], int reg[], int flags[]);
void setRegistersAndFlags(int reg[], int flags[]);
void checkFlagsArith(int flags[], char type, int result, int oper1, int oper2);
void checkFlagsLog(int flags[], int result);
void checkFlagsShift(int flags[], int result, int op, char shiftType);

void showRegisters(int reg[]);

//Main
int main(){
    FILE* dataFile;
    int NZCV[4], registers[8];
    char operation[ARRAY_MAX];
    dataFile = fopen(FILENAME, "r");
    setRegistersAndFlags(registers, NZCV);

    //reads from file
    if (dataFile == NULL){
		printf("Issue opening file.\n");
	}else{
        while(fscanf(dataFile, "%s", operation) != EOF){
            doMath(dataFile, operation, registers, NZCV);
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

void doMath(FILE* reading, char operation[], int reg[], int flags[]){
    signed int registerA, registerB, registerC, immediateVal, temp;
    char rval1, rval2, rval3;
    int operationType = 0; // 1 = Arithmetic, 2 = Logical/Move, 3 = Shift/Rotate
    if((strcmp(operation, "mov") == 0)||(strcmp(operation, "MOV") == 0)){
        fscanf(reading, " %c%i, #%X", &rval1, &registerA, &immediateVal);
        reg[registerA] = immediateVal;
        printf("%s %c%i, #0x%08X \n", operation, rval1, registerA, immediateVal);
        operationType = 2;
    }else if((strcmp(operation, "ADDS") == 0)||(strcmp(operation, "adds") == 0)||(strcmp(operation, "ADD") == 0)||(strcmp(operation, "add") == 0)){
        fscanf(reading, " %c%i, %c%i, %c%i", &rval1, &registerA, &rval2, &registerB, &rval3, &registerC);
        reg[registerA] = reg[registerB] + reg[registerC];
        printf("%s %c%i, %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB, rval3, registerC);
        operationType = 1;
    }else if((strcmp(operation, "SUBS") == 0)||(strcmp(operation, "subs") == 0)||(strcmp(operation, "SUB") == 0)||(strcmp(operation, "sub") == 0)){
        fscanf(reading, " %c%i, %c%i, %c%i", &rval1, &registerA, &rval2, &registerB, &rval3, &registerC);
        reg[registerA] = reg[registerB] - reg[registerC];
        printf("%s %c%i, %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB, rval3, registerC);
        operationType = 1;
    }else if((strcmp(operation, "ANDS") == 0)||(strcmp(operation, "ands") == 0)||(strcmp(operation, "AND") == 0)||(strcmp(operation, "and") == 0)){
        fscanf(reading, " %c%i, %c%i, %c%i", &rval1, &registerA, &rval2, &registerB, &rval3, &registerC);
        reg[registerA] = reg[registerB] & reg[registerC];
        printf("%s %c%i, %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB, rval3, registerC);
        operationType = 2;
    }else if((strcmp(operation, "ORRS") == 0)||(strcmp(operation, "orrs") == 0)||(strcmp(operation, "ORR") == 0)||(strcmp(operation, "orr") == 0)){
        fscanf(reading, " %c%i, %c%i, %c%i", &rval1, &registerA, &rval2, &registerB, &rval3, &registerC);
        reg[registerA] = reg[registerB] | reg[registerC];
        printf("%s %c%i, %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB, rval3, registerC);
        operationType = 2;
    }else if((strcmp(operation, "XORS") == 0)||(strcmp(operation, "xors") == 0)||(strcmp(operation, "XOR") == 0)||(strcmp(operation, "xor") == 0)){
        fscanf(reading, " %c%i, %c%i, %c%i", &rval1, &registerA, &rval2, &registerB, &rval3, &registerC);
        reg[registerA] = reg[registerB] ^ reg[registerC];
        printf("%s %c%i, %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB, rval3, registerC);
        operationType = 2;
    }else if((strcmp(operation, "LSRS") == 0)||(strcmp(operation, "lsrs") == 0)||(strcmp(operation, "LSR") == 0)||(strcmp(operation, "lsr") == 0)){
        fscanf(reading, " %c%i, %c%i, #%i", &rval1, &registerA, &rval2, &registerB, &immediateVal);
        reg[registerA] = reg[registerB] >> immediateVal;
        printf("%s %c%i, %c%i, #%i\n", operation, rval1, registerA, rval2, registerB, immediateVal);
        operationType = 3;
    }else if((strcmp(operation, "LSLS") == 0)||(strcmp(operation, "lsls") == 0)||(strcmp(operation, "LSL") == 0)||(strcmp(operation, "lsl") == 0)){
        fscanf(reading, " %c%i, %c%i, #%i", &rval1, &registerA, &rval2, &registerB, &immediateVal);
        reg[registerA] = reg[registerB] << immediateVal;
        printf("%s %c%i, %c%i, #%i\n", operation, rval1, registerA, rval2, registerB, immediateVal);
        operationType = 3;
    }else if((strcmp(operation, "CMP") == 0)||(strcmp(operation, "cmp") == 0)){
        fscanf(reading, " %c%i, %c%i", &rval1, &registerA, &rval2, &registerB);
        temp = reg[registerA] - reg[registerB];
        printf("%s %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB);
        operationType = 1;
    }else if((strcmp(operation, "TST") == 0)||(strcmp(operation, "tst") == 0)){
        fscanf(reading, " %c%i, %c%i", &rval1, &registerA, &rval2, &registerB);
        temp = reg[registerA] & reg[registerB];
        printf("%s %c%i, %c%i\n", operation, rval1, registerA, rval2, registerB);
        operationType = 2;
    }else{
        printf("Error! \n");
    }
    //Check Flags
    if((operation[3] == 'S')||(operation[3] == 's')||(strcmp(operation, "CMP") == 0)||(strcmp(operation, "cmp"))||(strcmp(operation, "TST") == 0)||(strcmp(operation, "tst") == 0)){
        printf("heck\n");
        switch (operationType){
        case 1:
            if((strcmp(operation, "CMP") == 0)||(strcmp(operation, "cmp") == 0)) checkFlagsArith(flags, operation[0], temp, reg[registerB], reg[registerC]);
            else checkFlagsArith(flags, operation[0], reg[registerA], reg[registerB], reg[registerC]);
            break;
        case 2:
            if((strcmp(operation, "TST") == 0)||(strcmp(operation, "tst") == 0)) checkFlagsLog(flags, temp);
            else checkFlagsLog(flags, reg[registerA]);
            break;
        case 3:
            checkFlagsShift(flags, reg[registerA], reg[registerB],operation[2]);
            break;
        default:
            break;
        }
    }
    showRegisters(reg);
    printf("N = %i Z = %i C = %i V = %i \n", flags[0], flags[1], flags[2], flags[3]);
}

void showRegisters(int reg[]){
    for(int i = 0; i < 8; i++){
        printf("R%i: 0x%08X  ", i, reg[i]);
    }
    printf("\n");
}

void checkFlagsArith(int flags[], char type, int result, int oper1, int oper2){
    if(result < 0x0) flags[0] = 1;  //Negative
    else flags[0] = 0;

    if(result == 0x0) flags[1] = 1; //Zero
    else flags[1] = 0;

    if((type == 'A')||(type == 'a')){   //Carry
        if((oper1 < 0x0)&&(oper2 < 0x0)) flags[2] = 1;
        else flags[2] = 0;
    }else{
        if((oper1 < 0x0)&&(oper2 > 0x0)) flags[2] = 1;
        else flags[2] = 0;
    }
    if((type == 'A')||(type == 'a')){     //Overflow
        if((oper1 > 0x0)&&(oper2 > 0x0)&&(result < 0x0)) flags[3] = 1;
        else if((oper1 < 0x0)&&(oper2 < 0x0)&&(result > 0x0)) flags[3] = 1;
        else flags[3] = 0;
    }else{
        if((oper1 > 0x0)&&(oper2 < 0x0)&&(result < 0x0)) flags[3] = 1;
        else if((oper1 < 0x0)&&(oper2 > 0x0)&&(result > 0x0)) flags[3] = 1;
        else flags[3] = 0;
    }
}

void checkFlagsLog(int flags[], int result){
    if(result < 0x0) flags[0] = 1;  //Negative
    else flags[0] = 0;

    if(result == 0x0) flags[1] = 1; //Zero
    else flags[1] = 0;
}

void checkFlagsShift(int flags[], int result, int op, char shiftType){
    if(result < 0x0) flags[0] = 1;  //Negative
    else flags[0] = 0;

    if(result == 0x0) flags[1] = 1; //Zero
    else flags[1] = 0;

    if((shiftType == 'L')||(shiftType == 'l')){
        if(op < 0x0) flags[2] = 1;
        else flags[2] = 0;
    }
    else{
        if((op & 0x00000001) == 0x0) flags[2] = 0;
        else flags[2] = 1;
    }
}