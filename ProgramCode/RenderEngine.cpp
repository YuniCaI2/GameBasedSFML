//
// Created by cai on 25-4-7.
//

#include "RenderEngine.h"

Game::RenderEngine*  Game::RenderEngine::getInstance() {
    static auto* instance = new RenderEngine();
    return instance;
}
