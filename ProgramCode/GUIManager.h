#pragma once
#include<SFML/Graphics.hpp>
namespace Game{

    enum class PlayeerItemType{
        //TODO: 物品类型
    };
    enum class WeaponCard {
        Pawn = 1,
        PawnSelected,
        Knight ,
        KnightSelected,
        Bishop ,
        BishopSelected,
        Rook ,
        RookSelected ,
    };

    class GameObject;

class GUIManager
{
    private:
    /* data */
        GameObject* player;
    //文本属性
        sf::Font font;
        sf::Text textBuffer;

        sf::Text healthText;
        sf::Text moveNumText;
        sf::Text attackNumText;


    //额 GUI精灵
        std::vector<sf::Sprite> GUISprites;
        std::vector<sf::Texture> GUITextures;

    //一些位置信息
        static int textX, textY;
        static int textWidth, textHeight;
        static int healthX, healthY;
        static int moveNumX, moveNumY;
        static int attackNumX, attackNumY;
        static int PawnPicX, PawnPicY;
        static int KnightPicX, KnightPicY;
        static int BishopPicX, BishopPicY;
        static int RookPicX, RookPicY;

        GUIManager() = default;

        void setStatsText();
    public:
        void update();
        void draw();
        void init(GameObject* player);
        void writeText(const sf::Text& inputText);
        void clearTextBuffer();
        static GUIManager *getInstance();

        ~GUIManager();
    };
}

