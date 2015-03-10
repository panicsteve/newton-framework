/*
	File:		DriverCallbacks.h

	Contains:	Callbacks available to all print drivers

	Copyright:	� 1993-1995 by Apple Computer, Inc., all rights reserved.

	Derived from v4 internal.

*/


#ifndef __DRIVERCALLBACKS_H
#define __DRIVERCALLBACKS_H

#ifndef __CONFIGPRINTING_H
#include "ConfigPrinting.h"
#endif

#ifndef __NEWTON_H
#include "Newton.h"
#endif

#ifndef __PRINTTYPES_H
#include "PrintTypes.h"
#endif

#ifndef __PRINTERRORS_H
#include "PrintErrors.h"
#endif

#ifndef __OBJECTS_H
#include "Objects.h"
#endif

#ifndef	__LONGTIME_H
#include "Longtime.h"
#endif



	/*----- Available callbacks -----*/

PrProblemResolution CallHandleProblem(PrintConnect* connect, TPrinter* thePrinter,
							NewtonErr problemCode, Timeout retryTime, Boolean fixedBtn);

void PrReleaseControl(TTimeout howlong, TPrinter* thePrinter);	// let the main task run
void PrRegainControl(TPrinter* thePrinter);						// tell the main task to let go


#endif