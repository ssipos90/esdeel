
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include "./VideoLayer.hpp"
#include "./Game.hpp"
#include "./config.hpp"

#define PADDING 0.1
#define PADDING_X (int) (CELL_WIDTH * PADDING)
#define PADDING_Y (int) (CELL_HEIGHT * PADDING)

class GameLayer: public VideoLayer {
public:
  using VideoLayer::VideoLayer;
  void draw(uint32_t deltatime) override;

private:
  Game game;
  SDL_Rect pieceSquare = {0, 0, CELL_WIDTH - PADDING_X * 2 , CELL_HEIGHT - PADDING_Y * 2};

  void drawFood(Position p);
  void drawSnake(const std::vector<Position> *pieces);

  void drawGrid();
  void drawBackground();
};
