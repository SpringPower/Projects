#include "tileset.hpp"

Tileset::Tileset(
    ALLEGRO_FILE *ptFile,
    const TilesetConfig &rtConfig):
    m_tConfig(rtConfig)
{
    m_ptBitmap = al_load_bitmap_f(ptFile, ".png");
    EXPECT_NOT_NULL(m_ptBitmap);
}

Tileset::~Tileset()
{
    al_destroy_bitmap(m_ptBitmap);
}

ALLEGRO_BITMAP *Tileset::GetTile(size_t ulIdentifer)
{
    const Square &tSquare = m_tConfig.at(ulIdentifer);

    ALLEGRO_BITMAP *ptSubBitmap = al_create_sub_bitmap(m_ptBitmap,
                                                       std::get<0>(tSquare),
                                                       std::get<1>(tSquare),
                                                       std::get<2>(tSquare),
                                                       std::get<3>(tSquare));
    EXPECT_NOT_NULL(ptSubBitmap);

    return ptSubBitmap;
}
