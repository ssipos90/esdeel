#include "./VideoLayer.hpp"
#include "./types.hpp"

VideoLayer::VideoLayer(const App& app): app(app) {}

bool VideoLayer::isOpaque() {
  return true;
};

bool VideoLayer::closeRequested() {
  return close;
};