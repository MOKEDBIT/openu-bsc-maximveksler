/*
 * File:   CodeSegmentMgr.c
 * Author: hq4ever
 *
 * Created on February 27, 2010, 10:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "errorHandler.h"

static unsigned DC = 0;
static unsigned short dataSegment[SEGMENT_MAXIMUM_SIZE];

void initDataSegmentMgr() {
    unsigned int i;
    for(i = 0; i < SEGMENT_MAXIMUM_SIZE; i++) {
        dataSegment[i] = (unsigned int) NULL;
    }

    DC = 0;
}

void forwardDC(){
    DC++;
}

void resetDC(){
    DC = 0;
}
unsigned int getDC() {
    return DC;
}

void storeData(unsigned short data) {
        if (DC < SEGMENT_MAXIMUM_SIZE ){
        dataSegment[DC] = data;
        DC += 1;
    } else {
        handleError(DATA_SEGMENT_OUT_OF_BOUND,NULL);
    }
}

unsigned getData(unsigned index) {
    return dataSegment[index];
}