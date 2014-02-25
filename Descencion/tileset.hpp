#ifndef TILESET_HPP
#define TILESET_HPP

#include <vector>
#include <tuple>
#include <allegro5/allegro5.h>
#include "memory.hpp"

typedef std::vector<Square> TilesetConfig;

class Tileset: public ObjBase
{
public:
    Tileset(
        ALLEGRO_BITMAP *ptBitmap,
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

typedef enum TILESET_WEAPON: size_t
{
    TILESET_WEAPON_NONE = 0,
    TILESET_WEAPON_SHORTSWORD,
    TILESET_WEAPON_FALCHION,
    TILESET_WEAPON_LONGSWORD,
    TILESET_WEAPON_BASTARD_SWORD,
    TILESET_WEAPON_ZWEIHANDER,
    TILESET_WEAPON_KNIFE,
    TILESET_WEAPON_DIRK,
    TILESET_WEAPON_DAGGER,
    TILESET_WEAPON_SHORTBOW,
    TILESET_WEAPON_LONGBOW,
    TILESET_WEAPON_RECURVE_BOW,
    TILESET_WEAPON_SPEAR,
    TILESET_WEAPON_JAVELIN,
    TILESET_WEAPON_TRIDENT,
    TILESET_WEAPON_HANDAXE,
    TILESET_WEAPON_WARAXE,
    TILESET_WEAPON_POLEAXE,
    TILESET_WEAPON_KATANA,
    TILESET_WEAPON_NUNCHUCK,
    TILESET_WEAPON_DOUBLE_BLADED,
    TILESET_WEAPON_MACE,
    TILESET_WEAPON_CUDGEL,
    TILESET_WEAPON_CLUB,
    TILESET_WEAPON_STAFF,
    TILESET_WEAPON_FLAIL,
    TILESET_WEAPON_BUCKLER,
    TILESET_WEAPON_KITE_SHIELD,
    TILESET_WEAPON_TOWER_SHIELD,
    // must be last
    TILESET_WEAPON_NUM
} TILESET_WEAPON;

typedef enum TILESET_ARCH: size_t
{
    TILESET_ARCH_WALL_N = 0,
    TILESET_ARCH_WALL_E,
    TILESET_ARCH_WALL_S,
    TILESET_ARCH_WALL_W,
    TILESET_ARCH_WALL_SE,
    TILESET_ARCH_WALL_SW,
    TILESET_ARCH_WALL_NW,
    TILESET_ARCH_WALL_NE,
    TILESET_ARCH_WALL_SEW,
    TILESET_ARCH_WALL_NSW,
    TILESET_ARCH_WALL_NEW,
    TILESET_ARCH_WALL_NSE,
    TILESET_ARCH_WALL_EW,
    TILESET_ARCH_WALL_NS,
    TILESET_ARCH_WALL_NSEW,
    TILESET_ARCH_WALL_NONE,
    // must be last
    TILESET_ARCH_WALL_NUM
} TILESET_ARCH;


#endif // TILESET_HPP
