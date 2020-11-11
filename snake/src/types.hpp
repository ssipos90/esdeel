#pragma once

enum ResourceImages {
  IMAGE_DEFAULT,
  IMAGE_UP,
  IMAGE_DOWN,
  IMAGE_LEFT,
  IMAGE_RIGHT,
  IMAGE_TOTAL
};

enum ResourceTextures {
  TEXTURE_UP,
  TEXTURE_DOWN,
  TEXTURE_LEFT,
  TEXTURE_RIGHT,
  TEXTURE_TOTAL
};

enum class Direction { UP, DOWN, LEFT, RIGHT };

typedef struct Position {
  int x;
  int y;
} Position;
