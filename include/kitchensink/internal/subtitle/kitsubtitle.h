#ifndef KITSUBTITLE_H
#define KITSUBTITLE_H

#include <SDL2/SDL_render.h>

#include "kitchensink/kitconfig.h"
#include "kitchensink/kitformats.h"
#include "kitchensink/kitplayer.h"
#include "kitchensink/internal/kitdecoder.h"

KIT_LOCAL Kit_Decoder* Kit_CreateSubtitleDecoder(const Kit_Source *src, Kit_SubtitleFormat *format, int w, int h);
KIT_LOCAL int Kit_GetSubtitleDecoderDataTexture(Kit_Decoder *dec, SDL_Texture *texture);

#endif // KITSUBTITLE_H
