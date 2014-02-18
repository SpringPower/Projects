#include "tileset.hpp"

Tileset::Tileset::Tileset(
    ALLEGRO_FILE *ptFile,
    const TilesetConfig &rtConfig):
    m_nSubBitmaps(rtConfig.size())
{
    m_ptBitmap = al_load_bitmap_f(ptFile, ".png");
    EXPECT_NOT_NULL(m_ptBitmap);

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

    atConfig.resize(WEAPON_NUM);

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
    const int iWidth = TILE_WIDTH;
    const int iHeight = TILE_HEIGHT;

    atConfig.resize(ARCH_WALL_NUM);

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

ALLEGRO_FILE *
GetTilesetFile(
    TILESET eFile)
{
    EXPECT_TRUE(TILESET_NUM > eFile);

    ALLEGRO_FILE *ptFile = al_fopen(g_apszTilesetFiles[eFile], "r");
    EXPECT_NOT_NULL(ptFile);

    return ptFile;
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

    ALLEGRO_FILE *ptFile = GetTilesetFile(eTileset);
    TilesetConfig tConfig = GetTilesetConfig(g_aeFileToConfig[eTileset]);

    tTileset = new Tileset(ptFile, tConfig);

    al_fclose(ptFile);

    return std::move(tTileset);
}
