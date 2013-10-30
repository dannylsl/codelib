/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// "liveMedia"
// Copyright (c) 1996-2010 Live Networks, Inc.  All rights reserved.
// A 'ServerMediaSubsession' object that creates new, unicast, "RTPSink"s
// on demand, from a MPEG-4 video file.
// Implementation

#include "MPEG4VideofFileServerMediaSubsession.hh"
//#include "MPEG4FrameSource.hh"
#include "MPEG4ESVideoRTPSink.hh"
#include "ByteStreamFileSource.hh"
#include "MPEG4VideoStreamDiscreteFramerffmpeg.hh"
#include "MPEG1or2VideoStreamDiscreteFramer.hh"

MPEG4VideofFileServerMediaSubsession*
MPEG4VideofFileServerMediaSubsession::createNew(UsageEnvironment& env,
					       char const* fileName,
					       Boolean reuseFirstSource) {
  return new MPEG4VideofFileServerMediaSubsession(env, fileName, reuseFirstSource);
}

MPEG4VideofFileServerMediaSubsession
::MPEG4VideofFileServerMediaSubsession(UsageEnvironment& env,
                                      char const* fileName, Boolean reuseFirstSource)
  : FileServerMediaSubsession(env, fileName, reuseFirstSource),
    fDoneFlag(0) {
}

MPEG4VideofFileServerMediaSubsession
::~MPEG4VideofFileServerMediaSubsession() {
}
//this is a change

static void afterPlayingDummy(void* clientData) {
  MPEG4VideofFileServerMediaSubsession* subsess
    = (MPEG4VideofFileServerMediaSubsession*)clientData;
  subsess->afterPlayingDummy1();
}

void MPEG4VideofFileServerMediaSubsession::afterPlayingDummy1() {
  // Unschedule any pending 'checking' task:
  envir().taskScheduler().unscheduleDelayedTask(nextTask());
  // Signal the event loop that we're done:
  setDoneFlag();
}

static void checkForAuxSDPLine(void* clientData) {
  MPEG4VideofFileServerMediaSubsession* subsess
    = (MPEG4VideofFileServerMediaSubsession*)clientData;
  subsess->checkForAuxSDPLine1();
}

void MPEG4VideofFileServerMediaSubsession::checkForAuxSDPLine1() {
  if (fDummyRTPSink->auxSDPLine() != NULL) {
    // Signal the event loop that we're done:
    setDoneFlag();
  } else {
    // try again after a brief delay:
    int uSecsToDelay = 100000; // 100 ms
    nextTask() = envir().taskScheduler().scheduleDelayedTask(uSecsToDelay,
			      (TaskFunc*)checkForAuxSDPLine, this);
  }
}

char const* MPEG4VideofFileServerMediaSubsession
::getAuxSDPLine(RTPSink* rtpSink, FramedSource* inputSource) {
  // Note: For MPEG-4 video files, the 'config' information isn't known
  // until we start reading the file.  This means that "rtpSink"s
  // "auxSDPLine()" will be NULL initially, and we need to start reading
  // data from our file until this changes.
  fDummyRTPSink = rtpSink;

  // Start reading the file:
  fDummyRTPSink->startPlaying(*inputSource, afterPlayingDummy, this);

  // Check whether the sink's 'auxSDPLine()' is ready:
  checkForAuxSDPLine(this);

  envir().taskScheduler().doEventLoop(&fDoneFlag);

  char const* auxSDPLine = fDummyRTPSink->auxSDPLine();
  return auxSDPLine;
}
/*************Wind Changed here*******************************/
MPEG4FrameSource* MPEG4VideofFileServerMediaSubsession
::createNewStreamSource(unsigned /*clientSessionId*/, unsigned& estBitrate) {
	estBitrate = 500;


/**************************************************************/
//FramedSource* MPEG4VideofFileServerMediaSubsession
//::createNewStreamSource(unsigned /*clientSessionId*/, unsigned& estBitrate) {
//  estBitrate = 500; // kbps, estimate
/*
 * as we will be using the ffmpeg parser
 * we do not need bytestream , instead a plain file name suffices.
 * hence changing the signature of
 * MPEG4VideoStreamDiscreteFramerffmpeg to include file name
 * */
  // Create the video source:
  /*********Commented  5 Lines **************************/
//  ByteStreamFileSource* fileSource
//    = ByteStreamFileSource::createNew(envir(), fFileName);
//  if (fileSource == NULL) return NULL;
//  fFileSize = fileSource->fileSize();

  // Create a framer for the Video Elementary Stream:
  MPEG4VideoStreamDiscreteFramerffmpeg::createNew(envir(),fFileName);
  return MPEG4VideoStreamDiscreteFramerffmpeg::createNew(envir(), fFileName);
}

RTPSink* MPEG4VideofFileServerMediaSubsession
::createNewRTPSink(Groupsock* rtpGroupsock,
		   unsigned char rtpPayloadTypeIfDynamic,
		   FramedSource* /*inputSource*/) {
  return MPEG4ESVideoRTPSink::createNew(envir(), rtpGroupsock,
					rtpPayloadTypeIfDynamic);
}