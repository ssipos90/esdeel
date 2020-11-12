#include <SDL2/SDL_render.h>
#include "./Video.hpp"
#include "./Game.hpp"
#include "./config.hpp"

Video::Video(SDL_Renderer *renderer) : renderer(renderer) {}

void Video::draw(Game *game) {
  SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
  SDL_RenderClear(renderer);

  // drawGrid();

  // TODO have a class that renders the game state
  Position p = game->getFoodPosition();
  pieceSquare.x = p.x * CELL_WIDTH + PADDING_X;
  pieceSquare.y = p.y * CELL_HEIGHT + PADDING_Y;
  SDL_SetRenderDrawColor(renderer, 0xFF, 0x33, 0x33, 0xFF);
  SDL_RenderFillRect(renderer, &pieceSquare);

  SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0xCC, 0xFF);
  auto pieces = game->getSnakePieces();
  for (const auto &piece : pieces) {
    pieceSquare.x = piece.x * CELL_WIDTH + PADDING_X;
    pieceSquare.y = piece.y * CELL_HEIGHT + PADDING_Y;
    SDL_RenderFillRect(renderer, &pieceSquare);
  }
};

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
