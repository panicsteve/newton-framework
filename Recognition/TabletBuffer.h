/*
	File:		TabletBuffer.h

	Contains:	Input tablet definitions.

	Written by:	Newton Research Group.
*/

#if !defined(__TABLETBUFFER_H)
#define __TABLETBUFFER_H 1

#include "TabletTypes.h"
#include "NewtonTime.h"

class CUPort;


NewtonErr	TabletBufferInit(CUPort * inPort);
void			FlushTabletBuffer(void);
bool			TabletBufferEmpty(void);

void			SetTabletPolling(bool inPolling);
bool			GetTabletPolling(void);
NewtonErr	PollTablet(float *  outX, float *  outY, ULong *  outZ, bool * outPenUp);

void			WakeUpInkerFromInterrupt(Timeout inDelay);
void			WakeUpInker(Timeout inDelay);
NewtonErr	InsertTabletSample(ULong inSample, ULong inTime);
NewtonErr	InsertAndSendTabletSample(ULong inSample, ULong inTime);

ULong			GetInkerData(void);
ULong			SetInkerData(ULong inData);
ULong			SetInkerData(ULong inData, ULong incr);
void			IncInkerIndex(ULong incr);
bool			InkerBufferEmpty(void);
void			FlushInkerBuffer(void);

ULong			GetStrokerData(void);
ULong			GetStrokerData(ULong incr);
void			IncStrokerIndex(ULong incr);
bool			StrokerBufferEmpty(void);


#endif	/* __TABLETBUFFER_H */
