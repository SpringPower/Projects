#include "tileset.hpp"

Tileset::Tileset::Tileset(
    ALLEGRO_BITMAP *ptBitmap,
    const TilesetConfig &rtConfig):
    m_ptBitmap(ptBitmap),
    m_nSubBitmaps(rtConfig.size())
{
    m_pptSubBitmaps = new ALLEGRO_BITMAP*[m_nSubBitmaps];
    EXPECT_NOT_NULL(m_pptSubBitmaps);

    for (ulong i=0; i<m_nSubBitmaps; ++i)
    {
        const Square &crtSquare = rtConfig.at(i);
        m_pptSubBitmaps[i] = al_create_sub_bitmap(m_ptBitmap,
                                                  std::get<0>(crtSquare),
                                                  std::get<1>(crtSquare),
                                                  std::get<2>(crtSquare),
                                                  std::get<3>(crtSquare));
        EXPECT_NOT_NULL(m_pptSubBitmaps[i]);
    }
}

Tileset::Tileset::~Tileset()
{
    al_destroy_bitmap(m_ptBitmap);
}

ALLEGRO_BITMAP *Tileset::Tileset::GetTile(size_t ulIdentifer)
{
    EXPECT_TRUE(m_nSubBitmaps > ulIdentifer);
    ASSERT(NULL != m_pptSubBitmaps[ulIdentifer]);

    return m_pptSubBitmaps[ulIdentifer];
}

static
TilesetConfig
GetWeaponTilesetConfig()
{
    TilesetConfig atConfig;
    const int iWidth = TILE_WIDTH;
    const int iHeight = TILE_HEIGHT;

    atConfig.resize(TILESET_WEAPON_NUM);

    atConfig[TILESET_WEAPON_NONE         ] = Square(  0,   0, iWidth, iHeight);
    atConfig[TILESET_WEAPON_SHORTSWORD   ] = Square( 16,   0, iWidth, iHeight);
    atConfig[TILESET_WEAPON_FALCHION     ] = Square( 32,   0, iWidth, iHeight);
    atConfig[TILESET_WEAPON_LONGSWORD    ] = Square( 48,   0, iWidth, iHeight);
    atConfig[TILESET_WEAPON_BASTARD_SWORD] = Square( 64,   0, iWidth, iHeight);
    atConfig[TILESET_WEAPON_ZWEIHANDER   ] = Square( 80,   0, iWidth, iHeight);
    atConfig[TILESET_WEAPON_KNIFE        ] = Square( 96,   0, iWidth, iHeight);
    atConfig[TILESET_WEAPON_DIRK         ] = Square(112,   0, iWidth, iHeight);
    atConfig[TILESET_WEAPON_DAGGER       ] = Square(  0,  16, iWidth, iHeight);
    atConfig[TILESET_WEAPON_SHORTBOW     ] = Square( 16,  16, iWidth, iHeight);
    atConfig[TILESET_WEAPON_LONGBOW      ] = Square( 32,  16, iWidth, iHeight);
    atConfig[TILESET_WEAPON_RECURVE_BOW  ] = Square( 48,  16, iWidth, iHeight);
    atConfig[TILESET_WEAPON_SPEAR        ] = Square( 64,  16, iWidth, iHeight);
    atConfig[TILESET_WEAPON_JAVELIN      ] = Square( 80,  16, iWidth, iHeight);
    atConfig[TILESET_WEAPON_TRIDENT      ] = Square( 96,  16, iWidth, iHeight);
    atConfig[TILESET_WEAPON_HANDAXE      ] = Square(112,  16, iWidth, iHeight);
    atConfig[TILESET_WEAPON_WARAXE       ] = Square(  0,  32, iWidth, iHeight);
    atConfig[TILESET_WEAPON_POLEAXE      ] = Square( 16,  32, iWidth, iHeight);
    atConfig[TILESET_WEAPON_KATANA       ] = Square( 32,  32, iWidth, iHeight);
    atConfig[TILESET_WEAPON_NUNCHUCK     ] = Square( 48,  32, iWidth, iHeight);
    atConfig[TILESET_WEAPON_DOUBLE_BLADED] = Square( 64,  32, iWidth, iHeight);
    atConfig[TILESET_WEAPON_MACE         ] = Square( 80,  32, iWidth, iHeight);
    atConfig[TILESET_WEAPON_CUDGEL       ] = Square( 96,  32, iWidth, iHeight);
    atConfig[TILESET_WEAPON_CLUB         ] = Square(112,  32, iWidth, iHeight);
    atConfig[TILESET_WEAPON_STAFF        ] = Square(  0,  48, iWidth, iHeight);
    atConfig[TILESET_WEAPON_FLAIL        ] = Square( 16,  48, iWidth, iHeight);
    atConfig[TILESET_WEAPON_BUCKLER      ] = Square( 32,  48, iWidth, iHeight);
    atConfig[TILESET_WEAPON_KITE_SHIELD  ] = Square( 48,  48, iWidth, iHeight);
    atConfig[TILESET_WEAPON_TOWER_SHIELD ] = Square( 64,  48, iWidth, iHeight);

    return std::move(atConfig);
}

static
TilesetConfig
GetArchitechtureConfig()
{
    TilesetConfig atConfig;
    const int iWidth = TILE_WIDTH;
    const int iHeight = TILE_HEIGHT;

    atConfig.resize(TILESET_ARCH_WALL_NUM);

    atConfig[TILESET_ARCH_WALL_N   ] = Square(  0,   0, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_E   ] = Square( 16,   0, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_S   ] = Square( 16,  16, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_W   ] = Square(  0,  16, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_SE  ] = Square( 32,   0, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_SW  ] = Square( 48,   0, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_NW  ] = Square( 48,  16, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_NE  ] = Square( 32,  16, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_SEW ] = Square(  0,  32, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_NSW ] = Square( 16,  32, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_NEW ] = Square( 16,  48, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_NSE ] = Square(  0,  48, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_EW  ] = Square( 32,  32, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_NS  ] = Square( 48,  32, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_NSEW] = Square( 48,  48, iWidth, iHeight);
    atConfig[TILESET_ARCH_WALL_NONE] = Square( 32,  48, iWidth, iHeight);

    return std::move(atConfig);
}

static
TilesetConfig
GetFontConfig()
{
    TilesetConfig atConfig;
    const int iWidth = FONT_WIDTH;
    const int iHeight = FONT_HEIGHT;

    for (int i=0; i<16; ++i)
    {
        for (int j=0;j <16; ++j)
        {
            atConfig.push_back(Square(j*FONT_WIDTH, i*FONT_HEIGHT, iWidth, iHeight));
        }
    }

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
    case TILESET_CONFIG_FONT:
        tConfig = GetFontConfig();
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
    "./resources/dungeonwalls.png",
    "./resources/goodfont.png"
};
static_assert(ARRAY_ENTRIES(g_apszTilesetFiles) == TILESET_NUM, "Number of filenames does not match FILE_NUM");

const TILESET_CONFIG g_aeFileToConfig[] =
{
    TILESET_CONFIG_WEAPONS,
    TILESET_CONFIG_ARCH,
    TILESET_CONFIG_FONT
};
static_assert(ARRAY_ENTRIES(g_aeFileToConfig) == TILESET_NUM, "Number of configs does not match FILE_NUM");

ALLEGRO_BITMAP *
GetTilesetFile(
    TILESET eFile)
{
#ifndef BUILD_WINDOWS // Currently a bug in the build/Allegro prevents al_load_bitmap_f from working right
    EXPECT_TRUE(TILESET_NUM > eFile);

    ALLEGRO_FILE *ptFile = al_fopen(g_apszTilesetFiles[eFile], "r");
    EXPECT_NOT_NULL(ptFile);

    ALLEGRO_BITMAP *ptBitmap = al_load_bitmap_f(ptFile, ".png");
    EXPECT_NOT_NULL(ptBitmap);

    al_fclose(ptFile);
#else
    ALLEGRO_BITMAP *ptBitmap = al_load_bitmap(g_apszTilesetFiles[eFile]);
#endif

    return ptBitmap;
}


TilesetFactory::TilesetFactory()
{
    for (ulong i=0; i<TILESET_NUM; ++i)
    {
        m_apTilesets.push_back(_GetTileset((TILESET)i));
    }
}

PTileset TilesetFactory::GetTileset(TILESET eTileset)
{
    return m_apTilesets.at(eTileset);
}

PTileset TilesetFactory::_GetTileset(TILESET eTileset)
{
    PTileset tTileset;

    EXPECT_TRUE(TILESET_NUM > eTileset);

    ALLEGRO_BITMAP *ptBitmap = GetTilesetFile(eTileset);
    TilesetConfig tConfig = GetTilesetConfig(g_aeFileToConfig[eTileset]);

    tTileset = new Tileset(ptBitmap, tConfig);

    return std::move(tTileset);
}
