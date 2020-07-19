#ifndef CHESS_GAME_ENGINE_HPP_
#define CHESS_GAME_ENGINE_HPP_

#include "olcPixelGameEngine.h"
#include "conway.hpp"

static constexpr int PIXEL_SIZE = 1;
static constexpr int SCALE_FACTOR = 10;

class GameEngine : public olc::PixelGameEngine {
  public:
    GameEngine(int _rows, int _cols);

    int getRows() { return m_rows; }
    int getCols() { return m_cols; }

  private:
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;

    int scaleX(float x_);
    int scaleY(float y_);

    void drawGrid();
    void refreshScene();

    int m_cols;
    int m_rows;

    bool running;
    float time_acc;

    Conway conway;
};

#endif /* CHESS_GAME_ENGINE_HPP_ */