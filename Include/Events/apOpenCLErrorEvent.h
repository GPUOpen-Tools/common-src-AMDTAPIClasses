//==================================================================================
// Copyright (c) 2016 , Advanced Micro Devices, Inc.  All rights reserved.
//
/// \author AMD Developer Tools Team
/// \file apOpenCLErrorEvent.h
///
//==================================================================================

//------------------------------ apOpenCLErrorEvent.h ------------------------------

#ifndef __APOPENCLERROREVENT_H
#define __APOPENCLERROREVENT_H

// Forward declarations:
template <class TransferableObjectType> class osTransferableObjectCreator;
class apFunctionCall;
// Infra:
#include <AMDTBaseTools/Include/gtString.h>
#include <AMDTAPIClasses/Include/apOpenCLErrorParameters.h>
// Local:
#include <AMDTAPIClasses/Include/Events/apEvent.h>


// ----------------------------------------------------------------------------------
// Class Name:           AP_API apOpenCLErrorEvent
// General Description:
//   Is thrown when an OpenCL error has occurred
// Author:  AMD Developer Tools Team
// Creation Date:        21/2/2010
// ----------------------------------------------------------------------------------
class AP_API apOpenCLErrorEvent : public apEvent
{
public:
    apOpenCLErrorEvent(osThreadId triggeringThreadId, const apOpenCLErrorParameters& openCLErrorsParameter, bool wasGeneratedByBreak);
    virtual ~apOpenCLErrorEvent();
    \
    // Overrides osTransferableObject:
    virtual osTransferableObjectType type() const;
    virtual bool writeSelfIntoChannel(osChannel& ipcChannel) const;
    virtual bool readSelfFromChannel(osChannel& ipcChannel);

    const apOpenCLErrorParameters& openCLErrorParameters() const {return _openCLErrorParameters;}
    const apFunctionCall* breakedOnFunctionCall() const { return _openCLErrorParameters._aptrBreakedOnFunctionCall.pointedObject(); };
    // Overrides apEvent:
    virtual EventType eventType() const;
    virtual apEvent* clone() const;

    // Was the event generated by break?
    bool wasGeneratedByBreak() const {return _wasGeneratedByBreak;};

private:
    // Only the transferable object creator should be able to call my default constructor:
    friend class osTransferableObjectCreator<apOpenCLErrorEvent>;
    apOpenCLErrorEvent();

private:

    // Contains the OpenCL error parameters:
    apOpenCLErrorParameters _openCLErrorParameters;


    // Contain true iff the event was generated by a breakpoint:
    bool _wasGeneratedByBreak;
};

#endif //__APOPENCLERROREVENT_H

