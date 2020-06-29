#include "conway.hpp"

Conway::Conway(int _cols, int _rows)
    : m_cols(_cols)
    , m_rows(_rows)
    , world()
{ 
    for (int y = 0; y < m_rows; ++y) {
        std::vector<std::shared_ptr<Cell>> cell_row;
        for (int x = 0; x < m_cols; ++x) {
            cell_row.push_back(std::make_shared<Cell>(x, y));
        }
        world.push_back(cell_row);
    }
}

void Conway::reset() {
    for (auto cell_row : world) {
        for (auto cell : cell_row) {
            cell->setAlive(false);
            cell->setPrevAlive(false);
        }
    }
}

void Conway::run_rules() {

    for (auto cell_row : world) {
        for (auto cell : cell_row) {
            cell->setPrevAlive(cell->isAlive());
        }
    }

    for (auto cell_row : world) {
        for (auto cell : cell_row) {
            int neighbors = countNeighbors(cell);

            // 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
            if (neighbors < 2) { 
                cell->setAlive(false);
            }
            // 2. Any live cell with two or three live neighbours lives on to the next generation.
            if (neighbors == 2) {
                cell->setAlive(cell->isPrevAlive());
            }
            // 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
            if (neighbors > 3) {
                cell->setAlive(false);
            }
            // 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
            if (neighbors == 3) {
                cell->setAlive(true);
            }
        }
    }
}

int Conway::countNeighbors(std::shared_ptr<Cell> cell) {
    int count = 0;

    // Check top
    if (cell->y() > 0) {
        count += world[cell->y() - 1][cell->x()]->isPrevAlive() ? 1 : 0;
    }

    // Check bottom
    if (cell->y() < world.size() - 1) {
        count += world[cell->y() + 1][cell->x()]->isPrevAlive() ? 1 : 0;
    }

    // Check left
    if (cell->x() > 0) {
        count += world[cell->y()][cell->x() - 1]->isPrevAlive() ? 1 : 0;
        // Check top left corner
        if (cell->y() > 0) {
            count += world[cell->y() - 1][cell->x() - 1]->isPrevAlive() ? 1 : 0;
        }
        // Check bottom left corner
        if (cell->y() < world.size() - 1) {
            count += world[cell->y() + 1][cell->x() - 1]->isPrevAlive() ? 1 : 0;
        }
    }

    // Check right
    if (cell->x() < world[cell->y()].size() - 1) {
        count += world[cell->y()][cell->x() + 1]->isPrevAlive() ? 1 : 0;
        // Check top right corner
        if (cell->y() > 0) {
            count += world[cell->y() - 1][cell->x() + 1]->isPrevAlive() ? 1 : 0;
        }
        // Check bottom right corner
        if (cell->y() < world.size() - 1) {
            count += world[cell->y() + 1][cell->x() + 1]->isPrevAlive() ? 1 : 0;
        }
    }

    return count;
}

