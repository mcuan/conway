#ifndef CONWAY_HPP_
#define CONWAY_HPP_

#include <vector>
#include <memory>

class Cell {
  public:
    Cell(int _x, int _y)
        : m_x(_x)
        , m_y(_y)
        , m_alive(false)
        , m_prevAlive(false)
    { }

    int x() { return m_x; }
    int y() { return m_y; }

    bool isAlive() { return m_alive; }
    void setAlive(bool _alive) { m_alive = _alive; }

    bool isPrevAlive() { return m_prevAlive; }
    void setPrevAlive(bool _prevAlive) { m_prevAlive = _prevAlive; }

    void toggleAlive() { m_alive = !m_alive; m_prevAlive = !m_prevAlive; }

  private:
    int m_x;
    int m_y;

    bool m_alive;
    bool m_prevAlive;
};

class Conway {
  public:
    Conway(int _cols, int _rows);

    void reset();
    void run_rules();
    std::vector<std::vector<std::shared_ptr<Cell>>> world;

  private:
    int countNeighbors(std::shared_ptr<Cell> cell);
    int m_rows, m_cols;
};

#endif /* CONWAY_HPP_ */