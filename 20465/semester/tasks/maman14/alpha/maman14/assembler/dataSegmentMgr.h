/* 
 * File:   dataSegmentMgr.h
 * Author: hq4ever
 *
 * Created on March 27, 2010, 12:25 AM
 */

#ifndef _DATASEGMENTMGR_H
#define	_DATASEGMENTMGR_H

void initDataSegmentMgr();
unsigned int getDC();
void storeData(unsigned short data);
unsigned getData(unsigned);
void resetDC();
void forwardDC();

#endif	/* _DATASEGMENTMGR_H */

