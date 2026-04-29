/*

 Use native text to speech on windows and espeak api on Linux. Yay!

*/

#ifdef __unix__

// UNIX say w/ espeak (ng)

#include <espeak-ng/speak_lib.h>

 espeak_AUDIO_OUTPUT output = AUDIO_OUTPUT_SYNCH_PLAYBACK;
 char *path = NULL;
 void* user_data;
 unsigned int *identifier;

extern "C"
void say(char* text)
{
   char voicename[] = {"English"}; // Set voice by its name
   int buflength = 500, options = 0;
   unsigned int position = 0, position_type = 0, end_position = 0, flags = espeakCHARS_AUTO;
   espeak_Initialize(output, buflength, path, options);
   espeak_SetVoiceByName(voicename);
   espeak_Synth(text, buflength, position, (espeak_POSITION_TYPE)position_type, end_position, flags, identifier, user_data);
}

#elif defined(_WIN32) || defined(WIN32)

// windows say

#include <sapi.h>

ISpVoice* pVoice;

extern "C"
void say(char* text)
{
 CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
 CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
 size_t wtextlen = (strlen(text)+2)*sizeof(wchar_t);
 wchar_t* wtext = (wchar_t*)malloc(wtextlen);
 mbstowcs(wtext, text, wtextlen);
 pVoice->Speak(wtext, 0, NULL);
 free(wtext);
 pVoice->Release();
 pVoice = NULL;
 CoUninitialize();
}

#endif
