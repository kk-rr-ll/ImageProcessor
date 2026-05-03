#include "text_renderer/text_renderer.h"
#include <algorithm>
#include <cmath>
#include <map>

namespace image_processor {

struct SimpleFont {
    static const int CHAR_WIDTH = 8;
    static const int CHAR_HEIGHT = 8;
    
    static std::map<char, std::vector<std::string>> getFont() {
        static std::map<char, std::vector<std::string>> font;
        
        // thx deepseek
        font['A'] = {
            "  ##  ",
            " #  # ",
            "#    #",
            "#    #",
            "######",
            "#    #",
            "#    #",
            "#    #"
        };
        
        font['B'] = {
            "##### ",
            "#    #",
            "#    #",
            "##### ",
            "#    #",
            "#    #",
            "#    #",
            "##### "
        };
        
        font['C'] = {
            " #### ",
            "#    #",
            "#     ",
            "#     ",
            "#     ",
            "#     ",
            "#    #",
            " #### "
        };
        
        font['D'] = {
            "####  ",
            "#   # ",
            "#    #",
            "#    #",
            "#    #",
            "#    #",
            "#   # ",
            "####  "
        };
        
        font['E'] = {
            "######",
            "#     ",
            "#     ",
            "####  ",
            "#     ",
            "#     ",
            "#     ",
            "######"
        };
        
        font['F'] = {
            "######",
            "#     ",
            "#     ",
            "####  ",
            "#     ",
            "#     ",
            "#     ",
            "#     "
        };
        
        font['G'] = {
            " #### ",
            "#    #",
            "#     ",
            "#  ###",
            "#    #",
            "#    #",
            "#   # ",
            " ###  "
        };
        
        font['H'] = {
            "#    #",
            "#    #",
            "#    #",
            "######",
            "#    #",
            "#    #",
            "#    #",
            "#    #"
        };
        
        font['I'] = {
            "###",
            " # ",
            " # ",
            " # ",
            " # ",
            " # ",
            " # ",
            "###"
        };
        
        font['J'] = {
            "   ###",
            "    # ",
            "    # ",
            "    # ",
            "    # ",
            "#   # ",
            "#   # ",
            " ###  "
        };
        
        font['K'] = {
            "#   #",
            "#  # ",
            "# #  ",
            "##   ",
            "# #  ",
            "#  # ",
            "#   #",
            "#   #"
        };
        
        font['L'] = {
            "#     ",
            "#     ",
            "#     ",
            "#     ",
            "#     ",
            "#     ",
            "#     ",
            "######"
        };
        
        font['M'] = {
            "#     #",
            "##   ##",
            "# # # #",
            "#  #  #",
            "#     #",
            "#     #",
            "#     #",
            "#     #"
        };
        
        font['N'] = {
            "#    #",
            "##   #",
            "# #  #",
            "#  # #",
            "#   ##",
            "#    #",
            "#    #",
            "#    #"
        };
        
        font['O'] = {
            " #### ",
            "#    #",
            "#    #",
            "#    #",
            "#    #",
            "#    #",
            "#    #",
            " #### "
        };
        
        font['P'] = {
            "##### ",
            "#    #",
            "#    #",
            "##### ",
            "#     ",
            "#     ",
            "#     ",
            "#     "
        };
        
        font['Q'] = {
            " #### ",
            "#    #",
            "#    #",
            "#    #",
            "#    #",
            "#  # #",
            "#   # ",
            " ## # "
        };
        
        font['R'] = {
            "##### ",
            "#    #",
            "#    #",
            "##### ",
            "#  #  ",
            "#   # ",
            "#    #",
            "#    #"
        };
        
        font['S'] = {
            " #### ",
            "#    #",
            "#     ",
            "  ##  ",
            "    # ",
            "     #",
            "#    #",
            " #### "
        };
        
        font['T'] = {
            "######",
            "  #   ",
            "  #   ",
            "  #   ",
            "  #   ",
            "  #   ",
            "  #   ",
            "  #   "
        };
        
        font['U'] = {
            "#    #",
            "#    #",
            "#    #",
            "#    #",
            "#    #",
            "#    #",
            "#    #",
            " #### "
        };
        
        font['V'] = {
            "#    #",
            "#    #",
            " #  # ",
            " #  # ",
            "  ##  ",
            "  ##  ",
            "  ##  ",
            "  ##  "
        };
        
        font['W'] = {
            "#     #",
            "#     #",
            "#     #",
            "#  #  #",
            "# # # #",
            "##   ##",
            "#     #",
            "#     #"
        };
        
        font['X'] = {
            "#    #",
            " #  # ",
            "  ##  ",
            "  ##  ",
            "  ##  ",
            " #  # ",
            "#    #",
            "#    #"
        };
        
        font['Y'] = {
            "#    #",
            " #  # ",
            "  ##  ",
            "  ##  ",
            "  #   ",
            "  #   ",
            "  #   ",
            "  #   "
        };
        
        font['Z'] = {
            "######",
            "    # ",
            "   #  ",
            "  #   ",
            " #    ",
            "#     ",
            "#     ",
            "######"
        };
        
        font['0'] = {
            " #### ",
            "#    #",
            "#   ##",
            "#  # #",
            "# #  #",
            "##   #",
            "#    #",
            " #### "
        };
        
        font['1'] = {
            "  #   ",
            " ##   ",
            "# #   ",
            "  #   ",
            "  #   ",
            "  #   ",
            "  #   ",
            "##### "
        };
        
        font['2'] = {
            " #### ",
            "#    #",
            "     #",
            "    # ",
            "   #  ",
            "  #   ",
            " #    ",
            "######"
        };
        
        font['3'] = {
            " #### ",
            "#    #",
            "     #",
            "  ### ",
            "     #",
            "     #",
            "#    #",
            " #### "
        };
        
        font['4'] = {
            "   #  ",
            "  ##  ",
            " # #  ",
            "#  #  ",
            "######",
            "   #  ",
            "   #  ",
            "   #  "
        };
        
        font['5'] = {
            "######",
            "#     ",
            "#     ",
            "####  ",
            "     #",
            "     #",
            "#    #",
            " #### "
        };
        
        font['6'] = {
            " #### ",
            "#    #",
            "#     ",
            "##### ",
            "#    #",
            "#    #",
            "#    #",
            " #### "
        };
        
        font['7'] = {
            "######",
            "     #",
            "    # ",
            "   #  ",
            "  #   ",
            " #    ",
            "#     ",
            "#     "
        };
        
        font['8'] = {
            " #### ",
            "#    #",
            "#    #",
            " #### ",
            "#    #",
            "#    #",
            "#    #",
            " #### "
        };
        
        font['9'] = {
            " #### ",
            "#    #",
            "#    #",
            " #####",
            "     #",
            "     #",
            "#    #",
            " #### "
        };
        
        font['!'] = {
            " # ",
            " # ",
            " # ",
            " # ",
            " # ",
            "   ",
            " # ",
            " # "
        };
        
        font['?'] = {
            " ### ",
            "#   #",
            "    #",
            "   # ",
            "  #  ",
            "  #  ",
            "     ",
            "  #  "
        };
        
        font['.'] = {
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "## ",
            "## "
        };
        
        font[','] = {
            "   ",
            "   ",
            "   ",
            "   ",
            "   ",
            "## ",
            " # ",
            "#  "
        };
        
        font[' '] = {
            "      ",
            "      ",
            "      ",
            "      ",
            "      ",
            "      ",
            "      ",
            "      "
        };
        
        return font;
    }
};

void TextRenderer::drawText(Image& img, 
                           const std::string& text, 
                           int x, int y,
                           const std::vector<uint8_t>& color,
                           int fontSize,
                           const std::string& fontFamily) {
    if (text.empty() || fontSize <= 0) return;
    if (x < 0 || y < 0 || x >= img.getWidth() || y >= img.getHeight()) return;
    
    auto font = SimpleFont::getFont();
    int currentX = x;
    int currentY = y;
    int channels = img.getChannels();
    
    float scaleX = fontSize / 8.0f;
    float scaleY = fontSize / 8.0f;
    
    for (char c : text) {
        if (c == '\n') {
            currentX = x;
            currentY += fontSize * 1.5;
            continue;
        }
        
        char upperC = c;
        if (c >= 'a' && c <= 'z') {
            upperC = c - 32;
        }
        
        if (font.find(upperC) == font.end()) {
            currentX += fontSize * 0.6;
            continue;
        }
        
        const auto& charBitmap = font[upperC];
        
        for (int row = 0; row < SimpleFont::CHAR_HEIGHT; row++) {
            for (int col = 0; col < SimpleFont::CHAR_WIDTH; col++) {
                if (charBitmap[row][col] == '#') {
                    int startX = currentX + col * scaleX;
                    int startY = currentY + row * scaleY;
                    int endX = currentX + (col + 1) * scaleX;
                    int endY = currentY + (row + 1) * scaleY;
                    
                    for (int py = startY; py < endY && py < img.getHeight(); py++) {
                        for (int px = startX; px < endX && px < img.getWidth(); px++) {
                            if (px >= 0 && py >= 0) {
                                int pixelIndex = (py * img.getWidth() + px) * channels;
                                
                                if (channels == 1) {
                                    uint8_t grayValue = 0.299 * color[0] + 0.587 * color[1] + 0.114 * color[2];
                                    img.getData()[pixelIndex] = grayValue;
                                } else {
                                    for (int ch = 0; ch < std::min(channels, 3); ch++) {
                                        img.getData()[pixelIndex + ch] = color[ch];
                                    }
                                    if (channels == 4) {
                                        img.getData()[pixelIndex + 3] = 255;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        
        currentX += fontSize * 0.8; 
    }
}

}