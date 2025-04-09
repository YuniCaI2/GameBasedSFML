//
// Created by cai on 25-4-3.
//

#include "Player.h"

void Game::Player::setItem(Item *item) {
    items.push_back(item);
}

Game::Player::Player() {
    items.clear();

    chessNum[pbh::Knight] = 0;
    chessNum[pbh::Bishop] = 0;
    chessNum[pbh::Pawn] = 0;
    chessNum[pbh::Rook] = 0;
}

