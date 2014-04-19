#include <string>
#include "config.hpp"

static const char *GRAPHICS_SECTION_NAME =   "Graphics";
static const char *GRAPHICS_WIDTH_NAME =     "Width";
static const char *GRAPHICS_HEIGHT_NAME =    "Height";
static const char *GRAPHICS_MAX_FPS_NAME =   "MaxFps";
static const char *GRAPHICS_MIN_FPS_NAME =   "MinFps";
static const char *GRAPHICS_WINDOWED_NAME =  "Mode";
static const char *GRAPHICS_DISPLAY_NAME =   "Display";
static const char *GRAPHICS_VSYNC_NAME =     "Vsync";

static
ulong
GetUlongConfig(
    ALLEGRO_CONFIG  *ptConfig,
    const char      *pszSection,
    const char      *pszKey)
{
    ASSERT(NULL != ptConfig);
    ASSERT(NULL != pszSection);
    ASSERT(NULL != pszKey);

    const char *pszValue = al_get_config_value(ptConfig, pszSection, pszKey);

    return std::stoul(pszValue);
}

static
void
SetUlongConfig(
    ALLEGRO_CONFIG  *ptConfig,
    const char      *pszSection,
    const char      *pszKey,
    ulong ulValue)
{
    ASSERT(NULL != ptConfig);
    ASSERT(NULL != pszSection);
    ASSERT(NULL != pszKey);

    std::ostringstream tTempBuf;

    tTempBuf << ulValue;

    al_set_config_value(ptConfig, pszSection, pszKey, tTempBuf.str().c_str());
}

static
void
SanitizeConfig(
    CONFIG  &rtConfig)
{
    if ((0 != rtConfig.ulCreationDisplay) && ((ulong)al_get_num_video_adapters() <= rtConfig.ulCreationDisplay))
    {
        LOG("Display creation index invalid, resetting to 0");
        rtConfig.ulCreationDisplay = 0;
    }

    if (0 != (rtConfig.ulWindowed & (~(ALLEGRO_WINDOWED | ALLEGRO_FULLSCREEN | ALLEGRO_FULLSCREEN_WINDOW))))
    {
        LOG("Window mode contains invalid modes, removing");
        rtConfig.ulWindowed &= (ALLEGRO_WINDOWED | ALLEGRO_FULLSCREEN | ALLEGRO_FULLSCREEN_WINDOW);
    }

    if (    (rtConfig.ulWindowed != ALLEGRO_WINDOWED) &&
            (rtConfig.ulWindowed != ALLEGRO_FULLSCREEN) &&
            (rtConfig.ulWindowed != ALLEGRO_FULLSCREEN_WINDOW))
    {
        LOG("Window mode invalid, reverting to windowed");
        rtConfig.ulWindowed = ALLEGRO_WINDOWED;
    }
}

void
LoadConfig(
    ALLEGRO_FILE    *ptGameConfigFile,
    CONFIG          &rtConfig)
{
    ASSERT(ptGameConfigFile);

    ALLEGRO_CONFIG *ptConfiguration = al_load_config_file_f(ptGameConfigFile);
    ASSERT(NULL != ptConfiguration);

    rtConfig.ulWidth = GetUlongConfig(ptConfiguration, GRAPHICS_SECTION_NAME, GRAPHICS_WIDTH_NAME);
    rtConfig.ulHeight = GetUlongConfig(ptConfiguration, GRAPHICS_SECTION_NAME, GRAPHICS_HEIGHT_NAME);
    rtConfig.ulMinFps = GetUlongConfig(ptConfiguration, GRAPHICS_SECTION_NAME, GRAPHICS_MIN_FPS_NAME);
    rtConfig.ulMaxFps = GetUlongConfig(ptConfiguration, GRAPHICS_SECTION_NAME, GRAPHICS_MAX_FPS_NAME);
    rtConfig.ulWindowed = GetUlongConfig(ptConfiguration, GRAPHICS_SECTION_NAME, GRAPHICS_WINDOWED_NAME);
    rtConfig.ulCreationDisplay = GetUlongConfig(ptConfiguration, GRAPHICS_SECTION_NAME, GRAPHICS_DISPLAY_NAME);
    rtConfig.ulVsync = GetUlongConfig(ptConfiguration, GRAPHICS_SECTION_NAME, GRAPHICS_VSYNC_NAME);

    SanitizeConfig(rtConfig);
}

void
DumpConfig(
    ALLEGRO_FILE    *ptTargetConfigFile,
    const CONFIG    &crtConfig)
{
    ASSERT(ptTargetConfigFile);

    ALLEGRO_CONFIG *ptConfig = al_create_config();

    SetUlongConfig(ptConfig, GRAPHICS_SECTION_NAME, GRAPHICS_WIDTH_NAME, crtConfig.ulWidth);
    SetUlongConfig(ptConfig, GRAPHICS_SECTION_NAME, GRAPHICS_HEIGHT_NAME, crtConfig.ulHeight);
    SetUlongConfig(ptConfig, GRAPHICS_SECTION_NAME, GRAPHICS_MIN_FPS_NAME, crtConfig.ulMinFps);
    SetUlongConfig(ptConfig, GRAPHICS_SECTION_NAME, GRAPHICS_MAX_FPS_NAME, crtConfig.ulMaxFps);
    SetUlongConfig(ptConfig, GRAPHICS_SECTION_NAME, GRAPHICS_WINDOWED_NAME, crtConfig.ulWindowed);
    SetUlongConfig(ptConfig, GRAPHICS_SECTION_NAME, GRAPHICS_DISPLAY_NAME, crtConfig.ulCreationDisplay);
    SetUlongConfig(ptConfig, GRAPHICS_SECTION_NAME, GRAPHICS_VSYNC_NAME, crtConfig.ulVsync);

    EXPECT_TRUE(al_save_config_file_f(ptTargetConfigFile, ptConfig));
}
