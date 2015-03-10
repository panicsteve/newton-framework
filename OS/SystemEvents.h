/*	File:		SystemEvents.h	Contains:	Operating System Event definitions.	Written by:	Newton Research Group.*/#if !defined(__SYSTEMEVENTS_H)#define __SYSTEMEVENTS_H 1#if !defined(__NEWTON_H)#include "Newton.h"#endif#if !defined(__KERNELTYPES_H)#include	"KernelTypes.h"#endif#if !defined(__NAMESERVER_H)#include	"NameServer.h"#endif#if !defined(__USERPORTS_H)#include	"UserPorts.h"#endif// SystemEvents#define kSysEvent_PowerOn					'pwon'#define kSysEvent_PowerOff					'pwof'#define kSysEvent_AppAlive					'aliv'#define kSysEvent_NewICCard				'card'#define kSysEvent_DeviceNotification	'dnot'#define kSysEvent_PowerOffPending		'ppen'/*--------------------------------------------------------------------------------	C O S E v e n t--------------------------------------------------------------------------------*/class COSEvent	// was TSystemEvent NOT TAESystemEvent{public:					COSEvent(SystemEvent inEvent = 0);	void			setEvent(SystemEvent inEvent);	NewtonErr	registerForSystemEvent(ObjectId inPortId, ULong inSendFilter = 0, Timeout inTimeout = kNoTimeout);	NewtonErr	unregisterForSystemEvent(ObjectId inPortId);private:	friend class CSendSystemEvent;	CUPort		fNameServerPort;	SystemEvent	fEvent;};/*--------------------------------------------------------------------------------	C S e n d S y s t e m E v e n t--------------------------------------------------------------------------------*/class CSendSystemEvent : public COSEvent{public:					CSendSystemEvent(SystemEvent event = 0) : COSEvent(event) {};	NewtonErr	init(void);	NewtonErr	sendSystemEvent(void * inMessage, size_t inMessageSize);	NewtonErr	sendSystemEvent(CUAsyncMessage * inAsyncMessage, void * inMessage, size_t inMessageSize, void * outReply, ULong outReplySize);private:	CUSharedMemMsg		fMsgToSend;	CSysEventRequest	fMsgToNameServer;};#endif	/* __SYSTEMEVENTS_H */