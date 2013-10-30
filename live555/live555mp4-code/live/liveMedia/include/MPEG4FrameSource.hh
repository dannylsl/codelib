/* 
 * File:   MPEG4FrameSource.hh
 * Author: archan
 *
 * Created on 17 March, 2010, 7:18 PM
 */

#ifndef _MPEG4FRAMESOURCE_HH
#define	_MPEG4FRAMESOURCE_HH

#include "MPEG4FrameParserffmpeg.h"
#include "FramedSource.hh"

class MPEG4FrameSource : public FramedSource {
public:
    static MPEG4FrameSource * createNew(UsageEnvironment& env, const char* inputfile);
    MPEG4FrameSource(UsageEnvironment& env, const char * inputfile);
    void getNextFrame(unsigned char* to, unsigned maxSize,
            afterGettingFunc* afterGettingFunc,
            void* afterGettingClientData,
            onCloseFunc* onCloseFunc,
            void* onCloseClientData);

    u_int8_t profile_and_level_indication() const {
        return fProfileAndLevelIndication;
    }
    unsigned char* getConfigBytes(unsigned& numBytes) const;
protected:
    u_int8_t fProfileAndLevelIndication;
    unsigned char* fConfigBytes;
    unsigned fNumConfigBytes;

private:
    unsigned char* fNewConfigBytes;
    unsigned fNumNewConfigBytes;
    afterGettingFunc* fAfterGettingFunc;
    void* fAfterGettingClientData;
    onCloseFunc* fOnCloseFunc;
    void* fOnCloseClientData;
};


#endif	/* _MPEG4FRAMESOURCE_HH */

