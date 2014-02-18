#ifndef TILESET_HPP
#define TILESET_HPP

#include <vector>
#include <tuple>
#include <allegro5/allegro5.h>
#include "memory.hpp"

typedef std::tuple<int, int, int, int> Square;
typedef std::vector<Square> TilesetConfig;

class Tileset: public ObjBase
{
public:
    Tileset(
        ALLEGRO_FILE *ptFile,
        const TilesetConfig &rtConfig);

    ~Tileset();

    // Returns a pointer to a subbitmap for a specific tile
    // This subbitmap should not be released and should stop being used once the tileset is
    // destroyed (this is okay since tilesets should be created before the game is run and
    // be destroyed only once it is done running
    ALLEGRO_BITMAP *GetTile(
        size_t ulIdentifer);

private:
    ALLEGRO_BITMAP *m_ptBitmap;
    ALLEGRO_BITMAP **m_pptSubBitmaps;
    ulong m_nSubBitmaps;
};
typedef ObjPointer<Tileset> PTileset;

typedef enum TILESET
{
    TILESET_WEAPONS = 0,
    TILESET_ARCH_DUNGEON,
    TILESET_FONT,
    // Must be last:
    TILESET_NUM
} TILESET;

class TilesetFactory: public ObjBase
{
public:
    TilesetFactory();
    PTileset GetTileset(TILESET eTileset);

private:
    PTileset _GetTileset(TILESET eTileset);

private:
    std::vector<PTileset> m_apTilesets;
};
typedef ObjPointer<TilesetFactory> PTilesetFactory;

typedef enum TILESET_CONFIG
{
    TILESET_CONFIG_WEAPONS = 0,
    TILESET_CONFIG_ARCH,
    TILESET_CONFIG_FONT
} TILESET_CONFIG;

typedef enum WEAPON: size_t
{
    WEAPON_NONE = 0,
    WEAPON_SHORTSWORD,
    WEAPON_FALCHION,
    WEAPON_LONGSWORD,
    WEAPON_BASTARD_SWORD,
    WEAPON_ZWEIHANDER,
    WEAPON_KNIFE,
    WEAPON_DIRK,
    WEAPON_DAGGER,
    WEAPON_SHORTBOW,
    WEAPON_LONGBOW,
    WEAPON_RECURVE_BOW,
    WEAPON_SPEAR,
    WEAPON_JAVELIN,
    WEAPON_TRIDENT,
    WEAPON_HANDAXE,
    WEAPON_WARAXE,
    WEAPON_POLEAXE,
    WEAPON_KATANA,
    WEAPON_NUNCHUCK,
    WEAPON_DOUBLE_BLADED,
    WEAPON_MACE,
    WEAPON_CUDGEL,
    WEAPON_CLUB,
    WEAPON_STAFF,
    WEAPON_FLAIL,
    WEAPON_BUCKLER,
    WEAPON_KITE_SHIELD,
    WEAPON_TOWER_SHIELD,
    // must be last
    WEAPON_NUM
} WEAPON;

typedef enum ARCH: size_t
{
    ARCH_WALL_N = 0,
    ARCH_WALL_E,
    ARCH_WALL_S,
    ARCH_WALL_W,
    ARCH_WALL_SE,
    ARCH_WALL_SW,
    ARCH_WALL_NW,
    ARCH_WALL_NE,
    ARCH_WALL_SEW,
    ARCH_WALL_NSW,
    ARCH_WALL_NEW,
    ARCH_WALL_NSE,
    ARCH_WALL_EW,
    ARCH_WALL_NS,
    ARCH_WALL_NSEW,
    ARCH_WALL_NONE,
    // must be last
    ARCH_WALL_NUM
} ARCH;


#endif // TILESET_HPP
