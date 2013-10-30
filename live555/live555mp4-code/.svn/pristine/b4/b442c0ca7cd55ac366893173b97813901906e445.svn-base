


#include "MPEG4FrameSource.hh"
#include "MPEG4FrameParserffmpeg.h"

#include "FramedSource.hh"

static MPEG4FrameSource * MPEG4FrameSource::createNew(UsageEnvironment& env, const char* inputfile) {
    return new MPEG4FrameSource(env, inputfile);
}

MPEG4FrameSource::MPEG4FrameSource(UsageEnvironment& env, const char* inputfile) : FramedSource(env) {
    fInputSource = this;
    MPEG4FrameParser_init(inputfile);
}

void MPEG4FrameSource::getNextFrame(unsigned char* to,
        unsigned maxSize, afterGettingFunc* afterGettingFunc,
        void* afterGettingClientData, onCloseFunc* onCloseFunc,
        void* onCloseClientData) {

    //  // Make sure we're not already being read:
    //  if (fIsCurrentlyAwaitingData) {
    //    envir() << "FramedSource[" << this << "]::getNextFrame(): attempting to read more than once at the same time!\n";
    //    abort();
    //  }

    fTo = to;
    fMaxSize = maxSize;
    fNumTruncatedBytes = 0; // by default; could be changed by doGetNextFrame()
    fDurationInMicroseconds = 0; // by default; could be changed by doGetNextFrame()
    fAfterGettingFunc = afterGettingFunc;
    fAfterGettingClientData = afterGettingClientData;
    fOnCloseFunc = onCloseFunc;
    fOnCloseClientData = onCloseClientData;
    //fIsCurrentlyAwaitingData = True; // commented as we are not using
    float * duration = malloc(sizeof(float));
    float * pts = malloc(sizeof(float));
    int size ;//= malloc(sizeof(int));
    //uint8_t * buff = malloc(10000);
    getNextMPEG4Frame(&fTo,fMaxSize,fNumTruncatedBytes,&size,pts,duration);

    //doGetNextFrame(); this is replaced by getNext

}