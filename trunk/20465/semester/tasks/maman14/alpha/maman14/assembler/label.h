/* 
 * File:   label.h
 * Author: doron
 *
 * Created on March 2, 2010, 1:32 PM
 */

#ifndef _LABEL_H
#define	_LABEL_H

#include "constants.h"

void initLabelTable(void);
_bool getLabelAddress(char*, unsigned*);
_bool addLabel(char*, unsigned );

#endif	/* _LABEL_H */
