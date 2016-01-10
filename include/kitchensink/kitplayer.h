#ifndef KITPLAYER_H
#define KITPLAYER_H

#include "kitchensink/kitsource.h"
#include "kitchensink/kitconfig.h"
#include <stdbool.h>

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_thread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KIT_CODECMAX 16
#define KIT_CODECNAMEMAX 128
#define KIT_VBUFFERSIZE 3
#define KIT_ABUFFERSIZE 65536

typedef enum Kit_PlayerState {
    KIT_STOPPED = 0,
    KIT_PLAYING,
    KIT_PAUSED,
    KIT_CLOSED
} Kit_PlayerState;

typedef struct Kit_AudioFormat {
    int bytes;
    bool is_signed;
    int samplerate;
    int channels;
} Kit_AudioFormat;

typedef struct Kit_VideoFormat {
    unsigned int format;
    int width;
    int height;
} Kit_VideoFormat;

typedef struct Kit_Player {
    Kit_PlayerState state;
    Kit_VideoFormat vformat;
    Kit_AudioFormat aformat;
    SDL_Thread *dec_thread;
    SDL_mutex *vmutex;
    SDL_mutex *amutex;
    void *abuffer;
    void *vbuffer;
    void *vcodec_ctx;
    void *acodec_ctx;
    void *tmp_vframe;
    void *tmp_aframe;
    void *swr;
    void *sws;
    const Kit_Source *src;
} Kit_Player;

typedef struct Kit_PlayerInfo {
    char acodec[KIT_CODECMAX];
    char acodec_name[KIT_CODECNAMEMAX];
    char vcodec[KIT_CODECMAX];
    char vcodec_name[KIT_CODECNAMEMAX];
    Kit_VideoFormat video;
    Kit_AudioFormat audio;
} Kit_PlayerInfo;

KIT_API Kit_Player* Kit_CreatePlayer(const Kit_Source *src);
KIT_API void Kit_ClosePlayer(Kit_Player *player);

KIT_API int Kit_UpdatePlayer(Kit_Player *player);
KIT_API int Kit_RefreshTexture(Kit_Player *player, SDL_Texture *texture);
KIT_API int Kit_GetAudioData(Kit_Player *player, unsigned char *buffer, size_t length);
KIT_API void Kit_GetPlayerInfo(const Kit_Player *player, Kit_PlayerInfo *info);

KIT_API Kit_PlayerState Kit_GetPlayerState(const Kit_Player *player);
KIT_API void Kit_PlayerPlay(Kit_Player *player);
KIT_API void Kit_PlayerStop(Kit_Player *player);
KIT_API void Kit_PlayerPause(Kit_Player *player);

#ifdef __cplusplus
}
#endif

#endif // KITPLAYER_H
