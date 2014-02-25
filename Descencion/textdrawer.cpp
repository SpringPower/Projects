#include <vector>
#include "textdrawer.hpp"

TextDrawer::TextDrawer(PTilesetFactory ptTilesetFactory)
{
    m_ptFont = ptTilesetFactory->GetTileset(TILESET_FONT);
}

void TextDrawer::WriteTile(const std::string &crStr, const Square &tArea)
{
    const Square tSquare(
                std::get<0>(tArea)*TILE_WIDTH,
                std::get<1>(tArea)*TILE_HEIGHT,
                std::get<2>(tArea)*TILE_WIDTH,
                std::get<3>(tArea)*TILE_HEIGHT);
    WritePixel(crStr, tSquare);
}

std::vector<std::string> SplitString(const char cSplitChar, const std::string &crStr)
{
    std::vector<std::string> atSplit;
    size_t cbWordStart = 0;
    size_t cbWordEnd = crStr.find_first_of(cSplitChar, cbWordStart);

    while (std::string::npos != cbWordEnd)
    {
        atSplit.push_back(crStr.substr(cbWordStart, cbWordEnd - cbWordStart));
        cbWordStart = cbWordEnd + 1;
        cbWordEnd = crStr.find_first_of(cSplitChar, cbWordStart);
    }
    atSplit.push_back(crStr.substr(cbWordStart, cbWordEnd - cbWordStart));

    return std::move(atSplit);
}

std::vector<std::string> SplitLine(const std::string &crStr, ulong nMaxLen)
{
    std::vector<std::string> atResult;
    std::vector<std::string> atWords = SplitString(' ', crStr);

    EXPECT_TRUE(0 < atWords.size());

    for (ulong i=0; i<atWords.size();)
    {
        if (atWords.at(i).size() > nMaxLen)
        {
            atResult.push_back(atWords[i].substr(0, nMaxLen));
            atWords[i] = atWords[i].substr(nMaxLen);
            continue;
        }

        std::stringstream ssLine;

        ssLine << atWords.at(i);
        ++i;

        if (i >= atWords.size())
        {
            break;
        }

        while ((i < atWords.size()) && (ssLine.str().size() + atWords.at(i).size() + 1 < nMaxLen))
        {
            ssLine << ' ' << atWords.at(i);
            ++i;
        }

        atResult.push_back(ssLine.str());
    }


    return std::move(atResult);
}

std::vector<std::string> SplitToLines(const std::string &crStr, ulong nMaxLen)
{
    std::vector<std::string> atResult;
    std::vector<std::string> atInitialLines = SplitString('\n', crStr);

    for (auto strLine: atInitialLines)
    {
        std::vector<std::string> atLines = SplitLine(strLine, nMaxLen);
        atResult.insert(atResult.end(), atLines.begin(), atLines.end());
    }

    return std::move(atResult);
}

void TextDrawer::_WriteChar(char c, ulong x, ulong y)
{
    ALLEGRO_BITMAP *ptCharImage = m_ptFont->GetTile(c);

    al_draw_bitmap(ptCharImage, x, y, 0);
}

void TextDrawer::WritePixel(const std::string &crStr, const Square &tArea)
{
    EXPECT_TRUE(std::get<2>(tArea) > 0);
    EXPECT_TRUE(std::get<3>(tArea) > 0);

    const ulong ulXStart = std::get<0>(tArea);
    const ulong ulYStart = std::get<1>(tArea);
    const ulong nColumns = std::get<2>(tArea) / FONT_WIDTH;
    const ulong nLines = std::get<3>(tArea) / FONT_HEIGHT;

    std::vector<std::string> atLines = SplitToLines(crStr, nColumns);

    for (ulong i=0; i<std::min((size_t)nLines, atLines.size()); ++i)
    {
        const std::string &crtLine = atLines.at(i);
        for (ulong j=0; j<crtLine.size(); ++j)
        {
            _WriteChar(crtLine.at(j), ulXStart + j*FONT_WIDTH, ulYStart + i*FONT_HEIGHT);
        }
    }
}
