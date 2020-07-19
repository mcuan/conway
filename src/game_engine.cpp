#include "game_engine.hpp"

GameEngine::GameEngine(int _cols, int _rows)
    : m_cols(_cols) 
    , m_rows(_rows)
    , conway(_cols, _rows)
    , running(false)
    , time_acc(0.0)
{
    printf("Creating game with %d rows and %d cols\n", m_rows, m_cols);
}

bool GameEngine::OnUserCreate() {
    refreshScene();
    return true;
}

bool GameEngine::OnUserUpdate(float fElapsedTime) {
    int mouse_x = getCols() * GetMouseX() / ScreenWidth();
    int mouse_y = getRows() * GetMouseY() / ScreenHeight();

    if(GetKey(olc::Key::SPACE).bReleased) {
        running = !running;
    }

    if(GetKey(olc::Key::R).bReleased) {
        running = false;
        conway.reset();
        refreshScene();
    }

    if(GetKey(olc::Key::Q).bReleased) {
        return false;
    }

    if (!running) {
        if(GetMouse(0).bReleased) {
            conway.world[mouse_y][mouse_x]->toggleAlive();
            refreshScene();
        }
    } 
    else {
        time_acc += fElapsedTime;
        if (time_acc > 0.1)
        {
            conway.run_rules();
            time_acc = 0.0;
            refreshScene();
        }
    }

    return true;
}

int GameEngine::scaleX(float x_) {
    return static_cast<int>(x_ * ScreenWidth() / m_cols);
}

int GameEngine::scaleY(float y_) {
    return static_cast<int>(y_ * ScreenHeight() / m_rows);
}

void GameEngine::drawGrid() {
    for (int row = 0; row < getRows(); ++row) {
        DrawLine(scaleX(0), scaleY(row), scaleX(getCols()), scaleY(row), olc::DARK_GREEN);
    }

    for (int col = 0; col < getCols(); ++col) {
        DrawLine(scaleX(col), scaleY(0), scaleX(col), scaleY(getRows()), olc::DARK_GREEN);
    }

    for (auto cell_row : conway.world) {
        for (auto cell : cell_row) {
            if (cell->isAlive())
                FillRect(scaleX(cell->x()), scaleY(cell->y()), SCALE_FACTOR, SCALE_FACTOR, olc::GREEN);
        }
    }
}

void GameEngine::refreshScene() {
    // Clear screen. Set bg to black
    Clear(olc::BLACK);
    // Draw grid
    drawGrid();
}