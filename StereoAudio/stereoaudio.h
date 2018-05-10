/**************************************************************************************
*
*  FILE NAME	: stereoaudio.h
*
*  DESCRIPTION  : header file
*
*  DATE	              NAME					 REFERENCE			REASON
*  
*  29-Dec-2015        Shashi Shivaraju       Initial code		Stereo Audio Conversion
*
**************************************************************************************/
/*Header Inclusions*/
#include <stdio.h>
#include <string.h>


/*Macro Definations*/
#define CHECK_VOID(X)	if(!X){ return -1;}


/*Function Prototypes*/
/***************************************************************************************************
Name            : Deinterleave_StereoAudio
Description     : Deinterleaves stereo audio data into separate mono channel data.
Parameter       : apStereoAudioBuffer : stereo audio data buffer.
				  apTempStereoBuffer  : temporary audio data buffer.
				  alength			  : Length of the stereo audio data. 
Return Value    : 0 on SUCCESS or Corresponding Error Code.
***************************************************************************************************/
int Deinterleave_StereoAudio(void *apStereoAudioBuffer,void *apTempStereoBuffer,unsigned int alength);

/**************************************************************************************************
Name            : Interleave_StereoAudio
Description     : Interleave two mono channel audio data into stereo audio data buffer.
Parameter       : apAudioBuffer		  : Pointer to audio data buffer containing mono channel data.
				  apTempAudioBuffer   : Pointer to temporary audio data buffer.
				  alength			  : Total length of two mono channel data. 
Return Value    : 0 on SUCCESS or Corresponding Error Code.
***************************************************************************************************/
int Interleave_StereoAudio(void *apAudioBuffer,void *apTempAudioBuffer,unsigned int alength);
