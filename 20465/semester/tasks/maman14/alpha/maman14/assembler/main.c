/* 
 * File:   main.c
 * Author: hq4ever
 *
 * Created on February 25, 2010, 9:36 PM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "errorHandler.h"

#include "asmInstruction.h"
#include "asmCommands.h"

    int maxTest = 1;
    int doronTest = 2;

int main(int argc, char** argv) {
    int thisTest = maxTest;

    if(thisTest == maxTest)
        doMaxTest();
    else
        doDoronTest();

    /* FILE *fp; */
    /* printf("%s", FAILURE_TO_OPEN_FILE); */

    return (EXIT_SUCCESS);
}

doMaxTest() {
    AsmInstruction inst = malloc(sizeof(struct AsmInstruction));
    inst->instructionType = INST;

    inst->instruction = malloc(sizeof(union InstructionUnion));
    inst->instruction->INST.command = "mov";
    inst->instruction->INST.srcOP = "LENGTH";
    inst->instruction->INST.srcOPType = DIRECT;
    inst->instruction->INST.dstOP = "r1";
    inst->instruction->INST.dstOPType = REGISTER;

    inst->_log_unparsedAssemblyLine = "MAIN: mov LENGTH, r1";
    inst->lineNumber = 1;

    process(inst);
}

doDoronTest() {
    
}