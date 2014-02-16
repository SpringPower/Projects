#include "tilesetconfigs.hpp"

static
TilesetConfig
GetWeaponTilesetConfig()
{
    TilesetConfig atConfig;
    const int iWidth = 16;
    const int iHeight = 16;

    atConfig[WEAPON_NONE         ] = Square(  0,   0, iWidth, iHeight);
    atConfig[WEAPON_SHORTSWORD   ] = Square( 16,   0, iWidth, iHeight);
    atConfig[WEAPON_FALCHION     ] = Square( 32,   0, iWidth, iHeight);
    atConfig[WEAPON_LONGSWORD    ] = Square( 48,   0, iWidth, iHeight);
    atConfig[WEAPON_BASTARD_SWORD] = Square( 64,   0, iWidth, iHeight);
    atConfig[WEAPON_ZWEIHANDER   ] = Square( 80,   0, iWidth, iHeight);
    atConfig[WEAPON_KNIFE        ] = Square( 96,   0, iWidth, iHeight);
    atConfig[WEAPON_DIRK         ] = Square(112,   0, iWidth, iHeight);
    atConfig[WEAPON_DAGGER       ] = Square(  0,  16, iWidth, iHeight);
    atConfig[WEAPON_SHORTBOW     ] = Square( 16,  16, iWidth, iHeight);
    atConfig[WEAPON_LONGBOW      ] = Square( 32,  16, iWidth, iHeight);
    atConfig[WEAPON_RECURVE_BOW  ] = Square( 48,  16, iWidth, iHeight);
    atConfig[WEAPON_SPEAR        ] = Square( 64,  16, iWidth, iHeight);
    atConfig[WEAPON_JAVELIN      ] = Square( 80,  16, iWidth, iHeight);
    atConfig[WEAPON_TRIDENT      ] = Square( 96,  16, iWidth, iHeight);
    atConfig[WEAPON_HANDAXE      ] = Square(112,  16, iWidth, iHeight);
    atConfig[WEAPON_WARAXE       ] = Square(  0,  32, iWidth, iHeight);
    atConfig[WEAPON_POLEAXE      ] = Square( 16,  32, iWidth, iHeight);
    atConfig[WEAPON_KATANA       ] = Square( 32,  32, iWidth, iHeight);
    atConfig[WEAPON_NUNCHUCK     ] = Square( 48,  32, iWidth, iHeight);
    atConfig[WEAPON_DOUBLE_BLADED] = Square( 64,  32, iWidth, iHeight);
    atConfig[WEAPON_MACE         ] = Square( 80,  32, iWidth, iHeight);
    atConfig[WEAPON_CUDGEL       ] = Square( 96,  32, iWidth, iHeight);
    atConfig[WEAPON_CLUB         ] = Square(112,  32, iWidth, iHeight);
    atConfig[WEAPON_STAFF        ] = Square(  0,  48, iWidth, iHeight);
    atConfig[WEAPON_FLAIL        ] = Square( 16,  48, iWidth, iHeight);
    atConfig[WEAPON_BUCKLER      ] = Square( 32,  48, iWidth, iHeight);
    atConfig[WEAPON_KITE_SHIELD  ] = Square( 48,  48, iWidth, iHeight);
    atConfig[WEAPON_TOWER_SHIELD ] = Square( 64,  48, iWidth, iHeight);

    return std::move(atConfig);
}

static
TilesetConfig
GetArchitechtureConfig()
{
    TilesetConfig atConfig;
    const int iWidth = 16;
    const int iHeight = 16;

    atConfig[ARCH_WALL_N   ] = Square(  0,   0, iWidth, iHeight);
    atConfig[ARCH_WALL_E   ] = Square( 16,   0, iWidth, iHeight);
    atConfig[ARCH_WALL_S   ] = Square( 16,  16, iWidth, iHeight);
    atConfig[ARCH_WALL_W   ] = Square(  0,  16, iWidth, iHeight);
    atConfig[ARCH_WALL_SE  ] = Square( 32,   0, iWidth, iHeight);
    atConfig[ARCH_WALL_SW  ] = Square( 48,   0, iWidth, iHeight);
    atConfig[ARCH_WALL_NW  ] = Square( 48,  16, iWidth, iHeight);
    atConfig[ARCH_WALL_NE  ] = Square( 32,  16, iWidth, iHeight);
    atConfig[ARCH_WALL_SEW ] = Square(  0,  32, iWidth, iHeight);
    atConfig[ARCH_WALL_NSW ] = Square( 16,  32, iWidth, iHeight);
    atConfig[ARCH_WALL_NEW ] = Square( 16,  48, iWidth, iHeight);
    atConfig[ARCH_WALL_NSE ] = Square(  0,  48, iWidth, iHeight);
    atConfig[ARCH_WALL_EW  ] = Square( 32,  32, iWidth, iHeight);
    atConfig[ARCH_WALL_NS  ] = Square( 48,  32, iWidth, iHeight);
    atConfig[ARCH_WALL_NSEW] = Square( 48,  48, iWidth, iHeight);
    atConfig[ARCH_WALL_NONE] = Square( 32,  48, iWidth, iHeight);

    return std::move(atConfig);
}

TilesetConfig GetTilesetConfig(TILESET_CONFIG eConfig)
{
    TilesetConfig tConfig;
    switch (eConfig) {
    case TILESET_CONFIG_WEAPONS:
        tConfig = GetWeaponTilesetConfig();
        break;
    case TILESET_CONFIG_ARCH:
        tConfig = GetArchitechtureConfig();
        break;
    default:
        EXPECT_NOT(eConfig, eConfig);
        break;
    }

    return std::move(tConfig);
}

const char *g_apszTilesetFiles[] =
{
    "./resources/weapons.png",
    "./resources/dungeonwalls.png"
};

ALLEGRO_FILE *
GetTilesetFile(
    TILESET_FILE eFile)
{
    EXPECT_TRUE(TILESET_FILE_NUM > eFile);

    ALLEGRO_FILE *ptFile = al_fopen(g_apszTilesetFiles[eFile], "r");
    EXPECT_NOT_NULL(ptFile);

    return ptFile;
}
