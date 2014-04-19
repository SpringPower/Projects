#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <allegro5/allegro.h>
#include "common.hpp"

typedef struct _CONFIG{
    ulong ulWidth;
    ulong ulHeight;
    ulong ulMinFps;
    ulong ulMaxFps;
    ulong ulWindowed;
    ulong ulCreationDisplay;
    ulong ulVsync;
} CONFIG, *PCONFIG;

void
LoadConfig(
    ALLEGRO_FILE    *ptGameConfigFile,
    CONFIG          &rtConfig);

void
DumpConfig(
    ALLEGRO_FILE    *ptTargetConfigFile,
    const CONFIG    &crtConfig);

#endif // CONFIG_HPP
