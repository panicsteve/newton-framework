/*	File:		GaugeView.h	Contains:	CGaugeView declarations.	Written by:	Newton Research Group.*/#if !defined(__GAUGEVIEW_H)#define __GAUGEVIEW_H 1#include "RootView.h"/*------------------------------------------------------------------------------	C G a u g e V i e w------------------------------------------------------------------------------*/class CGaugeView : public CView{public:	VIEW_HEADER_MACRO	virtual  void			init(RefArg inContext, CView * inView);	virtual  bool			realDoCommand(RefArg inCmd);	virtual	void			realDraw(Rect * inBounds);	virtual	void			setSlot(RefArg inTag, RefArg inValue);	bool						trackSetValue(CUnit * inUnit);private:	int		fMaxValue;	// +30	int		fMinValue;	// +34};#endif	/* __GAUGEVIEW_H */