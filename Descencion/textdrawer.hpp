#ifndef TEXTDRAWER_HPP
#define TEXTDRAWER_HPP

#include <string>
#include "memory.hpp"
#include "tileset.hpp"

class TextDrawer : public ObjBase
{
public:
    TextDrawer(PTilesetFactory ptTilesetFactory);

    // Write a string to a certain area denoted by tiles
    // (x of starting tile, y of starting tile, width, height)
    void WriteTile(const std::string &crStr, const Square &tArea);
    // Write a string to a certain area denoted by pixels
    // (x of starting tile, y of starting tile, width, height)
    void WritePixel(const std::string &crStr, const Square &tArea);

private:
    void _WriteChar(char c, ulong x, ulong y);

private:
    PTileset m_ptFont;
};
typedef ObjPointer<TextDrawer> PTextDrawer;

#endif // TEXTDRAWER_HPP
