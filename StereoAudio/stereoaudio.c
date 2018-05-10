/*******************************************************************************************************
*
*  FILE NAME	: stereoaudio.c
*
*  DESCRIPTION  : Contains utility fuctions to Deinterleave stereo audio data into separate channel
*				  & to Interleave two mono channel audio data into stereo audio data .
*
*  DATE	               NAME					 REFERENCE			REASON
*  29-Dec-2015         Shashi Shivaraju      Initial code		Stereo Audio Conversions
*******************************************************************************************************/

/*Header inclusion*/
#include "stereoaudio.h"

/**************************************************************************************************
Name            : Deinterleave_StereoAudio
Description     : Deinterleaves stereo audio data into separate mono channel data.
Parameter       : apStereoAudioBuffer : Pointer to stereo audio data buffer.
				  apTempStereoBuffer  : Pointer to temporary audio data buffer.
				  alength			  : Length of the stereo audio data. 
Return Value    : 0 on SUCCESS or Corresponding Error Code.
***************************************************************************************************/
int Deinterleave_StereoAudio(void *apStereoAudioBuffer,void *apTempStereoBuffer,unsigned int alength)
{
	unsigned char  *lTempBuffer = NULL;
	unsigned int lCount = 0;
	unsigned int lBufPosition = 0;

	CHECK_VOID(apStereoAudioBuffer);
	CHECK_VOID(apTempStereoBuffer);
	CHECK_VOID(alength);
	
	lTempBuffer = (unsigned char  *)apTempStereoBuffer;
	memcpy(lTempBuffer,apStereoAudioBuffer,alength);

	for(lCount = 0;lCount < alength;lCount += 4)
	{
		memcpy(((unsigned char *)apStereoAudioBuffer+lBufPosition),((unsigned char *)lTempBuffer+lCount),2);
		memcpy(((unsigned char *)apStereoAudioBuffer+lBufPosition+alength/2),((unsigned char *)lTempBuffer+lCount+2),2);
		lBufPosition += 2;
	}
	return 0;
}

/***************************************************************************************************
Name            : Interleave_StereoAudio
Description     : Interleave two mono channel audio data into stereo audio data buffer.
Parameter       : apAudioBuffer		  : Pointer to audio data buffer containing mono channel data.
				  apTempAudioBuffer   : Pointer to temporary audio data buffer.
				  alength			  : Total length of two mono channel data. 
Return Value    : 0 on SUCCESS or Corresponding Error Code.
***************************************************************************************************/
int Interleave_StereoAudio(void *apAudioBuffer,void *apTempAudioBuffer,unsigned int alength)
{
	unsigned char  *lTempBuffer = NULL;
	unsigned int lCount = 0;
	unsigned int lBufPosition = 0;
	unsigned int lLength = 0;

	CHECK_VOID(apAudioBuffer);
	CHECK_VOID(apTempAudioBuffer);
	CHECK_VOID(alength);

	lTempBuffer = (unsigned char  *)apTempAudioBuffer;
	memcpy(lTempBuffer,apAudioBuffer,alength);

	lLength = alength/2;

	for(lCount = 0;lCount < lLength;lCount += 2)
	{
		memcpy(((unsigned char *)apAudioBuffer+lBufPosition),((unsigned char *)lTempBuffer+lCount),2);
		memcpy(((unsigned char *)apAudioBuffer+lBufPosition+2),((unsigned char *)lTempBuffer+lCount+lLength),2);
		lBufPosition += 4;
	}
	return 0;
}
