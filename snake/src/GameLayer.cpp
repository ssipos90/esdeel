#include "./GameLayer.hpp"
#include "./config.hpp"
#include <SDL2/SDL_render.h>

void GameLayer::draw(uint32_t deltatime) {
  (void) deltatime;
  drawBackground();

  // drawGrid();

  drawFood(game.getFoodPosition());

  auto pieces = game.getSnakePieces();
  drawSnake(&pieces);
};

void GameLayer::drawSnake(const std::vector<Position> *pieces) {
  SDL_SetRenderDrawColor(app.renderer, 0x33, 0x33, 0xCC, 0xFF);
  for (const auto &piece : *pieces) {
    pieceSquare.x = piece.x * CELL_WIDTH + PADDING_X;
    pieceSquare.y = piece.y * CELL_HEIGHT + PADDING_Y;
    SDL_RenderFillRect(app.renderer, &pieceSquare);
  }
}

void GameLayer::drawFood(Position p) {
  pieceSquare.x = p.x * CELL_WIDTH + PADDING_X;
  pieceSquare.y = p.y * CELL_HEIGHT + PADDING_Y;
  SDL_SetRenderDrawColor(app.renderer, 0xFF, 0x33, 0x33, 0xFF);
  SDL_RenderFillRect(app.renderer, &pieceSquare);
}

void GameLayer::drawGrid() {
  SDL_SetRenderDrawColor(app.renderer, 0x20, 0x20, 0x20, 0x00);
  for (int i = 1; i < GRID_Y; i++) {
    SDL_RenderDrawLine(app.renderer, 0, CELL_HEIGHT * i, GRID_X * CELL_WIDTH,
                       CELL_HEIGHT * i);
  }
  for (int i = 1; i < GRID_X; i++) {
    SDL_RenderDrawLine(app.renderer, CELL_WIDTH * i, 0, CELL_WIDTH * i,
                       GRID_Y * CELL_HEIGHT);
  }
}

void GameLayer::drawBackground() {
  SDL_SetRenderDrawColor(app.renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(app.renderer);
}
