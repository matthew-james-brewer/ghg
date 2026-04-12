/*

 It turns out that volume change / getting the volume is non portable. Fixed it!

*/

#ifdef __unix__

// UNIX vol

#include <alsa/asoundlib.h>

extern "C"
void* vol(long volume)
{
    long min, max;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;
    const char *card = "default";
    const char *selem_name = "Master";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    long* ret = NULL;

    if(volume >= 0) {
        snd_mixer_selem_set_playback_volume_all(elem, volume * max / 100);
    } else {
        ret = (long*)malloc(sizeof(long));
        snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_MONO, ret);
    }

    snd_mixer_close(handle);

    return (void*)ret;
}

#elif defined(_WIN32) || defined(WIN32)

// windows vol

#include <windows.h>
#include <commctrl.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <stdio.h>
#include <math.h>

#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

extern "C"
void* vol(long volume) {
    IAudioEndpointVolume *g_pEndptVol = NULL;
    IMMDeviceEnumerator *pEnumerator = NULL;
    IMMDevice *pDevice = NULL;

    CoInitialize(NULL);
    CoCreateInstance(__uuidof(MMDeviceEnumerator),
			NULL, CLSCTX_INPROC_SERVER,
			__uuidof(IMMDeviceEnumerator),
			(void**)&pEnumerator);
    pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    pDevice->Activate(__uuidof(IAudioEndpointVolume),
				CLSCTX_ALL, NULL, (void**)&g_pEndptVol);
    long* ret = NULL;

    if(volume >= 0) {
        float got = (float)volume / 100.0;
        g_pEndptVol->SetMasterVolumeLevelScalar(got, NULL);
    } else {
        float currentVal;
        g_pEndptVol->GetMasterVolumeLevelScalar(&currentVal);
        ret = (long*)malloc(sizeof(long));
        *ret = (long)(currentVal * 100);
    }

    SAFE_RELEASE(pEnumerator)
		SAFE_RELEASE(pDevice)
		SAFE_RELEASE(g_pEndptVol)
		CoUninitialize();

    return (void*)ret;
}
#endif
