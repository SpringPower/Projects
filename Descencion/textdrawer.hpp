#ifndef TEXTDRAWER_HPP
#define TEXTDRAWER_HPP

#include <string>
#include "memory.hpp"
#include "tileset.hpp"

class TextDrawer : public ObjBase
{
public:
    TextDrawer(PTilesetFactory ptTilesetFactory);

    void WriteTile(const std::string &crStr, const Square &tArea);
    void WritePixel(const std::string &crStr, const Square &tArea);

private:
    void _WriteChar(char c, ulong x, ulong y);

private:
    PTileset m_ptFont;
};

#endif // TEXTDRAWER_HPP
