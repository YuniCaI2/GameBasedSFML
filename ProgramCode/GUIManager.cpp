#include "GUIManager.h"

#include "GameObject.h"
#include "pbh.h"
#include "Window.h"
#include "Component/PlayerStatsComponent.h"
#include "Component/WeaponComponent.h"

namespace Game{
    int GUIManager::textHeight = 365;
    int GUIManager::textWidth = 140;
    int GUIManager::textX = 630;
    int GUIManager::textY = 130;
    int GUIManager::healthX = 75;
    int GUIManager::healthY = 135;
    int GUIManager::moveNumX = 55;
    int GUIManager::moveNumY = 185;
    int GUIManager::attackNumX = 55;
    int GUIManager::attackNumY = 225;
    int GUIManager::PawnPicX = 15;
    int GUIManager::PawnPicY = 280;
    int GUIManager::KnightPicX = 15 + 90;
    int GUIManager::KnightPicY = 280;
    int GUIManager::BishopPicX = 15;
    int GUIManager::BishopPicY = 280 + 135;
    int GUIManager::RookPicX = 15 + 90;
    int GUIManager::RookPicY = 280 + 135;


    void GUIManager::setStatsText() {//获取属性组件显示血量
        auto playerStats = player->getComponent<Game::PlayerStatsComponent>();
        auto health = playerStats->getCurrentHealth();


        healthText.setFont(font);
        healthText.setString(std::to_string(health) + "/" + std::to_string(playerStats->getMaxHealth()) + " HP");

        //显示血量
        healthText.setPosition(healthX, healthY);
        healthText.setCharacterSize(30);

        //移动信息
        moveNumText.setFont(font);
        std::wstring moveInfo = L"移动次数:";
        moveNumText.setString(moveInfo + std::to_wstring(playerStats->getMoveNum()));
        moveNumText.setPosition(moveNumX, moveNumY);
        moveNumText.setCharacterSize(16);

        //攻击次数信息
        std::wstring attackInfo = L"攻击次数:";
        attackNumText.setFont(font);
        attackNumText.setString(attackInfo + std::to_wstring(playerStats->getAttackNum()));
        attackNumText.setPosition(attackNumX, attackNumY);
        attackNumText.setCharacterSize(16);

    }

    void GUIManager::update()
    {
        setStatsText();

        //更新的是GUI中的贴图状态比如说选中的武器类型是什么
        //---------------------------------------------
        auto weapon = player->getComponent<WeaponComponent>();
        auto selectedWeapon = weapon->getSelectedWeapon();
        if (selectedWeapon == pbh::WeaponType::Pawn) {
            GUISprites[1].setTexture(GUITextures[static_cast<int>(WeaponCard::PawnSelected)]);
            GUISprites[2].setTexture(GUITextures[static_cast<int>(WeaponCard::Knight)]);
            GUISprites[3].setTexture(GUITextures[static_cast<int>(WeaponCard::Bishop)]);
            GUISprites[4].setTexture(GUITextures[static_cast<int>(WeaponCard::Rook)]);
        }
        if (selectedWeapon == pbh::WeaponType::Knight) {
            GUISprites[1].setTexture(GUITextures[static_cast<int>(WeaponCard::Pawn)]);
            GUISprites[2].setTexture(GUITextures[static_cast<int>(WeaponCard::KnightSelected)]);
            GUISprites[3].setTexture(GUITextures[static_cast<int>(WeaponCard::Bishop)]);
            GUISprites[4].setTexture(GUITextures[static_cast<int>(WeaponCard::Rook)]);
        }

        if (selectedWeapon == pbh::WeaponType::Bishop) {
            GUISprites[1].setTexture(GUITextures[static_cast<int>(WeaponCard::Pawn)]);
            GUISprites[2].setTexture(GUITextures[static_cast<int>(WeaponCard::Knight)]);
            GUISprites[3].setTexture(GUITextures[static_cast<int>(WeaponCard::BishopSelected)]);
            GUISprites[4].setTexture(GUITextures[static_cast<int>(WeaponCard::Rook)]);
        }

        if (selectedWeapon == pbh::WeaponType::Rook) {
            GUISprites[1].setTexture(GUITextures[static_cast<int>(WeaponCard::Pawn)]);
            GUISprites[2].setTexture(GUITextures[static_cast<int>(WeaponCard::Knight)]);
            GUISprites[3].setTexture(GUITextures[static_cast<int>(WeaponCard::Bishop)]);
            GUISprites[4].setTexture(GUITextures[static_cast<int>(WeaponCard::RookSelected)]);
        }

        //---------------------------------------------


    }
    
    void GUIManager::draw(){
        for(auto& sprite : GUISprites){
            Window::getWindow().draw(sprite);

        }
        //绘制GUI中的元素

        //绘制字
        Window::getWindow().draw(textBuffer);
        Window::getWindow().draw(healthText);
        Window::getWindow().draw(moveNumText);
        Window::getWindow().draw(attackNumText);
    }
    

    void GUIManager::init(GameObject* player) {
        GUITextures.reserve(100);
        GUISprites.reserve(100);


        // 载入玩家的信息
        this->player = player;

        //硬编码GUI纹理内容
//----------------------------------------------------------------------
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("../resource/bg.png"))
            std::cerr << "Failed to load background texture" << std::endl;
        // 初始化background - 先添加纹理再设置精灵
        GUITextures.push_back(backgroundTexture);
        sf::Sprite backgroundSprite(GUITextures.back());
        backgroundSprite.setPosition(0, 0);
        GUISprites.push_back(backgroundSprite);

        sf::Texture pawnTexture;
        sf::Texture pawnSelectedTexture;
        sf::Texture knightTexture;
        sf::Texture knightSelectedTexture;
        sf::Texture bishopTexture;
        sf::Texture bishopSelectedTexture;
        sf::Texture rookTexture;
        sf::Texture rookSelectedTexture;
        if (! pawnTexture.loadFromFile("../resource/GUIWeaponCard/black_soldier_0.png")) {
            std::cerr << "pawn texture loaded" << std::endl;
        }
        if (! pawnSelectedTexture.loadFromFile("../resource/GUIWeaponCard/black_soldier_1.png")) {
            std::cerr << "pawn selected texture loaded" << std::endl;
        }
        if (! knightTexture.loadFromFile("../resource/GUIWeaponCard/black_horse_0.png")) {
            std::cerr << "knight texture loaded" << std::endl;
        }
        if (! knightSelectedTexture.loadFromFile("../resource/GUIWeaponCard/black_horse_1.png")) {
            std::cerr << "knight selected texture loaded" << std::endl;
        }
        if (! bishopTexture.loadFromFile("../resource/GUIWeaponCard/black_elephant_0.png")) {
            std::cerr << "bishop texture loaded" << std::endl;
        }
        if (! bishopSelectedTexture.loadFromFile("../resource/GUIWeaponCard/black_elephant_1.png")) {
            std::cerr << "bishop selected texture loaded" << std::endl;
        }
        if (! rookTexture.loadFromFile("../resource/GUIWeaponCard/black_car_0.png")) {
            std::cerr << "rook texture loaded" << std::endl;
        }
        if (! rookSelectedTexture.loadFromFile("../resource/GUIWeaponCard/black_car_1.png")) {
            std::cerr << "rook selected texture loaded" << std::endl;
        }

        GUITextures.push_back(pawnTexture);
        sf::Sprite pawnSprite(GUITextures.back());
        pawnSprite.setPosition(PawnPicX, PawnPicY);
        GUISprites.push_back(pawnSprite);
        GUITextures.push_back(pawnSelectedTexture);

        GUITextures.push_back(knightTexture);
        sf::Sprite knightSprite(GUITextures.back());
        knightSprite.setPosition(KnightPicX, KnightPicY);
        GUISprites.push_back(knightSprite);
        GUITextures.push_back(knightSelectedTexture);

        GUITextures.push_back(bishopTexture);
        sf::Sprite bishopSprite(GUITextures.back());
        bishopSprite.setPosition(BishopPicX, BishopPicY);
        GUISprites.push_back(bishopSprite);
        GUITextures.push_back(bishopSelectedTexture);

        GUITextures.push_back(rookTexture);
        sf::Sprite rookSprite(GUITextures.back());
        rookSprite.setPosition(RookPicX, RookPicY);
        GUISprites.push_back(rookSprite);
        GUITextures.push_back(rookSelectedTexture);

//----------------------------------------------------------------------
        // 初始文字
        if (!font.loadFromFile("../resource/font/SIMHEI.TTF"))
            std::cerr << "Failed to load font file" << std::endl;

        textBuffer.setFont(font);
        std::wstring str = L"开始游戏吧！";
        textBuffer.setString(str);
        textBuffer.setCharacterSize(16);
        textBuffer.setPosition(textX, textY);

        //初始化状态显示
        setStatsText();
    }



    void GUIManager::writeText(const std::wstring& inputText)
    {
        textBuffer.setFont(font);
        textBuffer.setString(inputText);
        textBuffer.setPosition(textX, textY);
        textBuffer.setCharacterSize(16);
    }
    
    void GUIManager::clearTextBuffer()
    {
        textBuffer.setString("");
    }

    GUIManager* GUIManager::getInstance()
    {
        static auto* instance = new GUIManager();
        return instance;
    }

    GUIManager::~GUIManager() {
        //没东西的
    }
}
