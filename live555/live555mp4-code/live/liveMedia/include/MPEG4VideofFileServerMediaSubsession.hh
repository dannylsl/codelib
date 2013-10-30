/* 
 * File:   MPEG4VideofFileServerMediaSubsession.hh
 * Author: aravindv
 *
 * Created on 13 March, 2010, 1:30 AM
 */

#ifndef _MPEG4VIDEOFFILESERVERMEDIASUBSESSION_HH
#define	_MPEG4VIDEOFFILESERVERMEDIASUBSESSION_HH

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
// C++ header


#ifndef _FILE_SERVER_MEDIA_SUBSESSION_HH
#include "FileServerMediaSubsession.hh"
#endif

class MPEG4VideofFileServerMediaSubsession: public FileServerMediaSubsession{
public:
  static MPEG4VideofFileServerMediaSubsession*
  createNew(UsageEnvironment& env, char const* fileName, Boolean reuseFirstSource);

  // Used to implement "getAuxSDPLine()":
  void checkForAuxSDPLine1();
  void afterPlayingDummy1();

private:
  MPEG4VideofFileServerMediaSubsession(UsageEnvironment& env,
				      char const* fileName, Boolean reuseFirstSource);
      // called only by createNew();
  virtual ~MPEG4VideofFileServerMediaSubsession();

  void setDoneFlag() { fDoneFlag = ~0; }

private: // redefined virtual functions
  virtual char const* getAuxSDPLine(RTPSink* rtpSink,
				    FramedSource* inputSource);
  virtual FramedSource* createNewStreamSource(unsigned clientSessionId,
					      unsigned& estBitrate);
  virtual RTPSink* createNewRTPSink(Groupsock* rtpGroupsock,
                                    unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource);

private:
  char fDoneFlag; // used when setting up "fSDPLines"
  RTPSink* fDummyRTPSink; // ditto
};






#endif	/* _MPEG4VIDEOFFILESERVERMEDIASUBSESSION_HH */

