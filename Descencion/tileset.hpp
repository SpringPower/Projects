#ifndef TILESET_HPP
#define TILESET_HPP

#include <vector>
#include <tuple>
#include <allegro5/allegro5.h>
#include "common.hpp"

typedef std::tuple<int, int, int, int> Square;
typedef std::vector<Square> TilesetConfig;

class Tileset
{
public:
    Tileset(
        ALLEGRO_FILE *ptFile,
        const TilesetConfig &rtConfig);

    ~Tileset();

    ALLEGRO_BITMAP *GetTile(
        size_t ulIdentifer);

private:
    ALLEGRO_BITMAP *m_ptBitmap;
    TilesetConfig m_tConfig;
};

#endif // TILESET_HPP
