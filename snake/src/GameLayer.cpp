#include <SDL2/SDL_render.h>
#include "./GameLayer.hpp"
#include "./config.hpp"

GameLayer::GameLayer(SDL_Renderer *renderer) : renderer(renderer) {}

void Video::draw(Game *game) {
  drawBackground();

  // drawGrid();

  drawFood(game->getFoodPosition());

  auto pieces = game->getSnakePieces();
  drawSnake(&pieces);
};

void Video::drawSnake(const std::vector<Position> *pieces) {
  SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0xCC, 0xFF);
  for (const auto &piece: *pieces) {
    pieceSquare.x = piece.x * CELL_WIDTH + PADDING_X;
    pieceSquare.y = piece.y * CELL_HEIGHT + PADDING_Y;
    SDL_RenderFillRect(renderer, &pieceSquare);
  }
}

void Video::drawFood(Position p) {
  pieceSquare.x = p.x * CELL_WIDTH + PADDING_X;
  pieceSquare.y = p.y * CELL_HEIGHT + PADDING_Y;
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x33, 0x33, 0xFF);
  SDL_RenderFillRect(renderer, &pieceSquare);
}

void Video::drawGrid() {
  SDL_SetRenderDrawColor(renderer, 0x20, 0x20, 0x20, 0x00);
  for (int i = 1; i < GRID_Y; i++) {
    SDL_RenderDrawLine(renderer, 0, CELL_HEIGHT * i, GRID_X * CELL_WIDTH,
                       CELL_HEIGHT * i);
  }
  for (int i = 1; i < GRID_X; i++) {
    SDL_RenderDrawLine(renderer, CELL_WIDTH * i, 0, CELL_WIDTH * i,
                       GRID_Y * CELL_HEIGHT);
  }
}

void Video::drawBackground() {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer);
}
