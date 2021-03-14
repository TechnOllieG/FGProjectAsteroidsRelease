#pragma once
#include "Library.h"
#include <vector>
#include "SDL.h"
#include <iostream>
#include <cctype>

#pragma region Symbols
static bool sym_blank[5][3] =
{
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
};

static bool sym_zero[5][3] =
{
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1}
};

static bool sym_one[5][3] =
{
        {0, 1, 0},
        {1, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
};

static bool sym_two[5][3] =
{
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1}
};

static bool sym_three[5][3] =
{
        {1, 1, 1},
        {0, 0, 1},
        {0, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
};

static bool sym_four[5][3] =
{
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1}
};

static bool sym_five[5][3] =
{
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
};

static bool sym_six[5][3] =
{
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
};

static bool sym_seven[5][3] =
{
        {1, 1, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1}
};

static bool sym_eight[5][3] =
{
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
};

static bool sym_nine[5][3] =
{
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
};



static bool sym_a[5][3] =
{
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1}
};

static bool sym_b[5][3] =
{
        {1, 1, 0},
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
};

static bool sym_c[5][3] =
{
        {1, 1, 1},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 1, 1}
};

static bool sym_d[5][3] =
{
        {1, 1, 0},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 0}
};

static bool sym_e[5][3] =
{
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 0},
        {1, 0, 0},
        {1, 1, 1}
};

static bool sym_f[5][3] =
{
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 0},
        {1, 0, 0},
        {1, 0, 0}
};

static bool sym_g[5][3] =
{
        {1, 1, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1}
};

static bool sym_h[5][3] =
{
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1}
};

static bool sym_i[5][3] =
{
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
};

static bool sym_j[5][3] =
{
        {0, 0, 1},
        {0, 0, 1},
        {0, 0, 1},
        {1, 0, 1},
        {1, 1, 1}
};

static bool sym_k[5][3] =
{
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 0},
        {1, 0, 1},
        {1, 0, 1}
};

static bool sym_l[5][3] =
{
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 0, 0},
        {1, 1, 1}
};

static bool sym_m[5][3] =
{
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1}
};

static bool sym_n[5][3] =
{
        {1, 0, 1},
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1},
        {1, 0, 1}
};

static bool sym_p[5][3] =
{
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1},
        {1, 0, 0},
        {1, 0, 0}
};

static bool sym_q[5][3] =
{
        {1, 1, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {0, 1, 0}
};

static bool sym_r[5][3] =
{
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 0},
        {1, 0, 1},
        {1, 0, 1}
};

static bool sym_s[5][3] =
{
        {1, 1, 1},
        {1, 0, 0},
        {1, 1, 1},
        {0, 0, 1},
        {1, 1, 1}
};

static bool sym_t[5][3] =
{
        {1, 1, 1},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
};

static bool sym_u[5][3] =
{
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1}
};

static bool sym_v[5][3] =
{
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {1, 0, 1},
        {0, 1, 0}
};

static bool sym_w[5][3] =
{
        {1, 0, 1},
        {1, 0, 1},
        {1, 1, 1},
        {1, 1, 1},
        {1, 0, 1}
};

static bool sym_x[5][3] =
{
        {1, 0, 1},
        {1, 0, 1},
        {0, 1, 0},
        {1, 0, 1},
        {1, 0, 1}
};

static bool sym_y[5][3] =
{
        {1, 0, 1},
        {1, 0, 1},
        {0, 1, 0},
        {0, 1, 0},
        {0, 1, 0}
};

static bool sym_z[5][3] =
{
        {1, 1, 1},
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1}
};

static bool sym_colon[5][3] =
{
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0},
        {0, 1, 0},
        {0, 0, 0}
};

static bool sym_exclamation[5][3] =
{
		{0, 1, 0},
		{0, 1, 0},
		{0, 1, 0},
		{0, 0, 0},
		{0, 1, 0}
};
#pragma endregion

/// <summary>
/// SymbolDisplay, provides an easy interface to draw symbols on the screen, entirely based on SDL_Rect, takes a bool array that specify "pixels" that should be filled in to create each symbol
/// </summary>
struct SymbolDisplay
{
private:
    std::vector<SDL_Rect> rects;
    int pixelSize;
public:
	SymbolDisplay(Vector2Int position, int pixelSize, const bool inputData[5][3]);
    SymbolDisplay(Vector2Int position, int pixelSize, int numberToDisplay);
    SymbolDisplay(Vector2Int position, int pixelSize, bool* inputData);
    void Init(Vector2Int position, int pixelSize, bool* inputData);
	void Draw(SDL_Renderer* renderer);

    /// <summary>
    /// Takes input text and returns a vector of SymbolDisplays containing the visual representation of the input text.
    /// </summary>
    /// <param name="text">Input text</param>
    /// <param name="screenResolution">The current screen resolution</param>
    /// <param name="pixelSize">The pixel size of the symbol (one symbol is 3 pixels wide and 5 pixels high, space between letters is 1 pixel wide and a space is 3 pixels wide)</param>
    /// <param name="position">The position of the text (top left corner of the first symbol)</param>
    /// <returns>vector with SymbolDisplays</returns>
    static std::vector<SymbolDisplay> GetSymbols(std::string text, int pixelSize, Vector2Int position)
    {
        auto output = std::vector<SymbolDisplay>();
        int length = text.length();

        float xStepBetween = pixelSize * 3 + pixelSize;
        float space = pixelSize * 3;
        Vector2Int currentPos = position;

        for (int i = 0; i < length; i++)
        {
            char currChar = text[i];
            if (currChar == ' ')
            {
                currentPos.x += pixelSize * 2;
                continue;
            }

            bool* arry = GetArrayFromChar(currChar);
            SymbolDisplay current = SymbolDisplay(currentPos, pixelSize, arry);
            output.push_back(current);

            currentPos.x += pixelSize * 4;
        }
        return output;
    }

    /// <summary>
    /// Takes input text and returns a vector of SymbolDisplays containing the horizontally centered visual representation of the input text.
    /// </summary>
    /// <param name="text">Input text</param>
    /// <param name="screenResolution">The current screen resolution</param>
    /// <param name="pixelSize">The pixel size of the symbol (one symbol is 3 pixels wide and 5 pixels high, space between letters is 1 pixel wide and a space is 3 pixels wide)</param>
    /// <param name="yPosition">The y position of the horizontally centered text (based on the top of the symbol)</param>
    /// <returns>vector with SymbolDisplays</returns>
    static std::vector<SymbolDisplay> GetSymbolsCentered(std::string text, Vector2Int m_screenResolution, int pixelSize, int yPosition)
    {
        auto output = std::vector<SymbolDisplay>();
        int length = text.length();
        int widthInPixels = -1;

        float xStepBetween = pixelSize * 3 + pixelSize;
        float space = pixelSize * 3;
        Vector2Int currentPos = Vector2Int(0, yPosition);

        for (int i = 0; i < length; i++)
        {
            char currChar = text[i];

            if (currChar == ' ')
                widthInPixels += 3;
            else
                widthInPixels += 4;
        }

        currentPos.x = (m_screenResolution.x - widthInPixels * pixelSize) * 0.5f;

        for (int i = 0; i < length; i++)
        {
            char currChar = text[i];
            if (currChar == ' ')
            {
                currentPos.x += pixelSize * 2;
                continue;
            }

            bool* arry = GetArrayFromChar(currChar);
            SymbolDisplay current = SymbolDisplay(currentPos, pixelSize, arry);
            output.push_back(current);

            currentPos.x += pixelSize * 4;
        }
        return output;
    }

#pragma region Switches
    static bool* GetArrayFromInt(int numberToDraw)
    {
        switch (numberToDraw)
        {
            case 0: return *sym_zero;
            case 1: return *sym_one;
            case 2: return *sym_two;
            case 3: return *sym_three;
            case 4: return *sym_four;
            case 5: return *sym_five;
            case 6: return *sym_six;
            case 7: return *sym_seven;
            case 8: return *sym_eight;
            case 9: return *sym_nine;
            default: return *sym_blank;
        }
    }

    static bool* GetArrayFromChar(char characterToDraw)
    {
        characterToDraw = (char) std::tolower(characterToDraw);

        switch (characterToDraw)
        {
            case 'a': return *sym_a;
            case 'b': return *sym_b;
            case 'c': return *sym_c;
            case 'd': return *sym_d;
            case 'e': return *sym_e;
            case 'f': return *sym_f;
            case 'g': return *sym_g;
            case 'h': return *sym_h;
            case 'i': return *sym_i;
            case 'j': return *sym_j;
            case 'k': return *sym_k;
            case 'l': return *sym_l;
            case 'm': return *sym_m;
            case 'n': return *sym_n;
            case 'o': return *sym_zero;
            case 'p': return *sym_p;
            case 'q': return *sym_q;
            case 'r': return *sym_r;
            case 's': return *sym_s;
            case 't': return *sym_t;
            case 'u': return *sym_u;
            case 'v': return *sym_v;
            case 'w': return *sym_w;
            case 'x': return *sym_x;
            case 'y': return *sym_y;
            case 'z': return *sym_z;
            case '0': return *sym_zero;
            case '1': return *sym_one;
            case '2': return *sym_two;
            case '3': return *sym_three;
            case '4': return *sym_four;
            case '5': return *sym_five;
            case '6': return *sym_six;
            case '7': return *sym_seven;
            case '8': return *sym_eight;
            case '9': return *sym_nine;
            case ':': return *sym_colon;
            case '!': return *sym_exclamation;
            default: return *sym_blank;
        }
    }
#pragma endregion
};