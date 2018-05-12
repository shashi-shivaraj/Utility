/**************************************************************************************
*
*  FILE NAME	: Switch_AudioRoute.c
*
*  DESCRIPTION  : A program to dynamic switch the audio route between inbuilt speakers 
* 				  and connected headphones by using ALSA API's.
*
*  DATE	              NAME	               REFERENCE	        REASON
*  27th-Jun-2015      Shashi Shivaraju     Initial				ALSA Programming
*
****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <alsa/asoundlib.h>

/* Function Prototypes */
static int Configure_Alsa_Switch();
static int alsa_set_mixer_switch(int aval);

int main()
{
	int ret = 0;
	while (ret != -1)
	{
		ret = Configure_Alsa_Switch();
	}
	return 0;
}

static int Configure_Alsa_Switch()
{
	int err = 0;
	char inChar;
	fflush(stdin);				
	printf("\n****************************************");
	printf("\n Set Alsa Switch:");
	printf("\n OFF---------->0");
	printf("\n ON----------->1");
	printf("\n EXIT--------->e");
	printf("\n ");
	printf("\n****************************************");

	
		printf("\n Enter the command :");
		scanf("\n %c",&inChar);

		switch (inChar)
		{
		case '0':
			err = alsa_set_mixer_switch(0);
			if (0 != err)
			printf("Unable to set mixer switch to off\n");
			break;

		case '1':
			err = alsa_set_mixer_switch(1);
			if(0 != err)
			printf("Unable to set mixer switch to on\n");
			break;
			
		case 'e':
			 err = -1;
			 printf("exiting the program\n");
			 break;

		default:
			printf("Set Alsa Switch Not supported for entered value\n");
			break;
		}
	
	return err;
}

static int alsa_set_mixer_switch(int aval)
{
	int lStatus = 0;
	const char *mixer_name = "Switch";
	int err =0;
	const char* card="default";
	static snd_mixer_t *mixer_handle = NULL;
	
	snd_mixer_elem_t *elem;
	snd_mixer_selem_id_t *sid;
	snd_mixer_selem_id_alloca(&sid);
	snd_mixer_selem_id_set_index(sid, 0);
	snd_mixer_selem_id_set_name(sid, mixer_name);
	
	
	if ((err = snd_mixer_open(&mixer_handle, 0)) < 0)
	{
		printf("Mixer %s open error: %s",card , snd_strerror(err));
		return -1 ;
	}
	if ((err = snd_mixer_attach(mixer_handle,card)) < 0) 
	{
		printf("Mixer attach %s error: %s",card, snd_strerror(err));
		snd_mixer_close(mixer_handle);
		mixer_handle = NULL;
		return -1 ;
	}
	if ((err = snd_mixer_selem_register(mixer_handle,  NULL, NULL)) < 0)
	{
		printf("Mixer register error: %s", snd_strerror(err));
		snd_mixer_close(mixer_handle);
		mixer_handle = NULL;
		return -1;
	}
	err = snd_mixer_load(mixer_handle);
	if (err < 0)
 	{
		printf("Mixer %s load error: %s",card, snd_strerror(err));
		snd_mixer_close(mixer_handle);
		mixer_handle = NULL;
		return -1 ;
	}
	
	elem = snd_mixer_find_selem(mixer_handle, sid);
	printf("simple control '%s',%i\n", snd_mixer_selem_id_get_name(sid), snd_mixer_selem_id_get_index(sid));

	if (!elem)
	{
		printf("Unable to find simple control '%s',%i\n", snd_mixer_selem_id_get_name(sid), snd_mixer_selem_id_get_index(sid));
		snd_mixer_close(mixer_handle);
		mixer_handle = NULL;
		return -1;
	}
	
	if (snd_mixer_selem_has_playback_switch	((snd_mixer_elem_t *)mixer_handle))
	{
		err = snd_mixer_selem_set_playback_switch ((snd_mixer_elem_t *)mixer_handle, SND_MIXER_SCHN_MONO,aval);
		if (err < 0)
		{
			printf("Mixer %s error: %s\n",card, snd_strerror(err));
			snd_mixer_close(mixer_handle);
			mixer_handle = NULL;
			return -1 ;
		}
	}

	if(mixer_handle)
	{
		snd_mixer_close(mixer_handle);
	}
	return 0;
}
