/* 
 * File:   CodeSegmentMgr.h
 * Author: hq4ever
 *
 * Created on February 27, 2010, 11:03 PM
 */

#ifndef _CODESEGMENTMGR_H
#define	_CODESEGMENTMGR_H

#include "asmInstruction.h"


#ifndef _INSTRUCTIONSTRUCTURE_H
#include "asmInstruction.h"
#endif

void resetCode();
unsigned int getIC();
unsigned short storeCode(unsigned short data);
unsigned short getCode(unsigned short);
LinkerAddress getCodeLinkerType(unsigned short index);
void setCodeLinkerType(LinkerAddress type);
void forward();
void resetIC();

#endif	/* _CODESEGMENTMGR_H */
