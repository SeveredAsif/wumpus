#include <iostream>

#include <cmath>

#include <sstream>

#include <time.h>

#include<fstream>

using namespace std;

#define GRIDSIZE 4
#define UP 0
#define DOWN 2
#define LEFT 3
#define RIGHT 1
#define MAX_SHOTS 3

string to_stringg(int x) {
  std::string out_string;
  std::stringstream ss;
  ss << x;
  return ss.str();
}

class Position {

  int x, y;

  public:

    Position(int x, int y) {
      this -> x = x;
      this -> y = y;
    }

  Position() {}

  // Modify the following four so that the resulting position does not leave the grid
  void moveRight() {
    if (x <= 2) {
      x++;
    }
  }

  void moveLeft() {
    if (x >= 1) {
      x--;
    }
  }

  void moveUp() {
    if (y <= 2) {
      y++;
    }
  }

  void moveDown() {
    if (y >= 1) {
      y--;
    }
  }

  bool isAdjacent(Position p) {
    if (p.getX() == x) {
      if ((p.getY() - y) == 1 || (p.getY() - y) == -1) {
        return true;
      }
    } else if (p.getY() == y) {
      if ((p.getX() - x) == 1 || (p.getX() - x) == -1) {
        return true;
      }
    } else {
      return false;
    }
  }

  bool isSamePoint(Position p) {
    if (p.getX() == x) {
      if (p.getY() == y) {
        return true;
      }
    } else {
      return false;
    }
  }

  int getX() {
    return x;
  }

  int getY() {
    return y;
  }

};

class Pit {
  Position p;
  public:
    Pit() {
      srand(time(0));
      p = Position(rand() % 4, rand() % 4);
    }
  Pit(int x, int y) {
    p = Position(x, y);
  }
  Position get_position() {
    return p;
  }
};

class Wumpus {

  bool killed;
  Position p;

  public:

    Wumpus(int x, int y) {
      p = Position(x, y);
      killed = false;
    }

  Wumpus() {
    srand(time(0));
    p = Position(rand() % 4, rand() % 4);
    killed = false;
  }

  void kill() {
    killed = true;
  }
  bool isKilled() {
    return killed;
  }

  Position getPosition() {
    return p;
  }

};

class Player {

  int direction;
  int total_shots;
  bool killed;
  Position p;

  public:

    Player() {
      p = Position(0, 0);
      direction = UP;
      killed = false;
      total_shots = 3;
    }

  int get_direction() {
    return direction;
  }
  int get_shots() {
    return total_shots;
  }
  void set_shots(int shots) {
    total_shots = shots;
  }
  void turnLeft() {
    if (direction == UP) {
      direction = LEFT;
    } else if (direction == LEFT) {
      direction = DOWN;
    } else if (direction == DOWN) {
      direction = RIGHT;
    } else if (direction == RIGHT) {
      direction = UP;
    }
  }

  void turnRight() {
    if (direction == UP) {
      direction = RIGHT;
    } else if (direction == LEFT) {
      direction = UP;
    } else if (direction == DOWN) {
      direction = LEFT;
    } else if (direction == RIGHT) {
      direction = DOWN;
    }
  }

  void moveForward() {
    if (direction == RIGHT) {
      p.moveRight();
    }
    if (direction == UP) {
      p.moveUp();
    }
    if (direction == LEFT) {
      p.moveLeft();
    }
    if (direction == DOWN) {
      p.moveDown();
    }
  }

  bool isAdjacent(Position pos) {
    return p.isAdjacent(pos);
  }

  bool isSamePoint(Position pos) {
    return p.isSamePoint(pos);
  }

  void kill() {
    killed = true;
  }
  Position get_position() {
    return p;
  }

  string getPositionInfo() {
    return "Player is now at " + to_string(p.getX()) + ", " + to_string(p.getY());
  }

  string getDirectionInfo() {
    string s;
    if (direction == UP) s = "up";
    if (direction == DOWN) s = "down";
    if (direction == LEFT) s = "left";
    if (direction == RIGHT) s = "right";
    return "Player is moving at direction: " + s;
  }

};

class WumpusWorld {

  private:

    Player player;
  Wumpus wumpus;
  Pit pit;
  Position gold_position;
  bool ended;
  int flag = 0;

  public:

    WumpusWorld() {
      srand(time(0));
      wumpus = Wumpus(rand() % 4, rand() % 4);
      pit = Pit(rand() % 4, rand() % 4);
      Player player();
      int x = rand() % 4;
      int y = rand() % 4;
      while ((pit.get_position().getX() == x && pit.get_position().getY() == y) || (wumpus.getPosition().getX() == x && wumpus.getPosition().getY() == y)) {
        x = rand() % 4;
        y = rand() % 4;
      }
      cout << x << " " << y << endl;
      gold_position = Position(x, y);
      //Position gold_position(x,y);
    }

  WumpusWorld(int wumpus_x, int wumpus_y) {
    srand(time(0));
    wumpus = Wumpus(wumpus_x, wumpus_y);
    pit = Pit(rand() % 4, rand() % 4);
    int x = rand() % 4;
    int y = rand() % 4;
    while ((pit.get_position().getX() == x && pit.get_position().getY() == y) || (wumpus.getPosition().getX() == x && wumpus.getPosition().getY() == y)) {
      x = rand() % 4;
      y = rand() % 4;
    }
    Player player();
    gold_position = Position(x, y);
  }

  WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y) {
    srand(time(0));
    wumpus = Wumpus(wumpus_x, wumpus_y);
    Player player();
    int x = rand() % 4;
    int y = rand() % 4;
    while (pit.get_position().getX() == gold_x && pit.get_position().getY() == gold_y) {
      x = rand() % 4;
      y = rand() % 4;
    }
    pit = Pit(x, y);
    gold_position = Position(gold_x, gold_y);
  }

  WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y) {
    wumpus = Wumpus(wumpus_x, wumpus_y);
    pit = Pit(pit_x, pit_y);
    Player player();
    gold_position = Position(gold_x, gold_y);
  }

  void moveForward() {
    player.moveForward();
    return showGameState();
  }

  void turnLeft() {
    player.turnLeft();
    return showGameState();
  }

  void turnRight() {
    player.turnRight();
    return showGameState();
  }

  void shoot() {
    if (player.get_shots() != 0) {
      int dir = player.get_direction();
      int x = wumpus.getPosition().getX();
      int y = wumpus.getPosition().getY();
      if (dir == RIGHT) {
        if (y == player.get_position().getY()) {
          if (x > player.get_position().getX()) {
            cout << "killed" << endl;
            wumpus.kill();
            int shots = player.get_shots();
            player.set_shots(shots - 1);
          } else {
            cout << "missed" << endl;
            int shots = player.get_shots();
            player.set_shots(shots - 1);
          }
        } else {
          cout << "missed" << endl;
          int shots = player.get_shots();
          player.set_shots(shots - 1);
        }

      } else if (dir == LEFT) {
        if (y == player.get_position().getY()) {
          if (x < player.get_position().getX()) {
            cout << "killed" << endl;
            wumpus.kill();
            int shots = player.get_shots();
            player.set_shots(shots - 1);
          } else {
            cout << "missed" << endl;
            int shots = player.get_shots();
            player.set_shots(shots - 1);
          }
        } else {
          cout << "missed" << endl;
          int shots = player.get_shots();
          player.set_shots(shots - 1);
        }
      } else if (dir == UP) {
        if (x == player.get_position().getX()) {
          if (y > player.get_position().getY()) {
            cout << "killed" << endl;
            wumpus.kill();
            int shots = player.get_shots();
            player.set_shots(shots - 1);
          } else {
            cout << "missed" << endl;
            int shots = player.get_shots();
            player.set_shots(shots - 1);
          }
        } else {
          cout << "missed" << endl;
          int shots = player.get_shots();
          player.set_shots(shots - 1);
        }
      } else if (dir == DOWN) {
        if (x == player.get_position().getX()) {
          if (y < player.get_position().getY()) {
            cout << "killed" << endl;
            wumpus.kill();
            int shots = player.get_shots();
            player.set_shots(shots - 1);
          } else {
            cout << "missed" << endl;
            int shots = player.get_shots();
            player.set_shots(shots - 1);
          }
        } else {
          cout << "missed" << endl;
          int shots = player.get_shots();
          player.set_shots(shots - 1);
        }
      }
    } else {
      cout << "No Shots left!" << endl;
    }
    return showGameState();
  }

  void showGameState() {
    cout << player.getPositionInfo() << endl;
    cout << player.getDirectionInfo() << endl;
    cout << player.get_shots() << " shots left!" << endl;

    if (player.isAdjacent(wumpus.getPosition()) && flag == 0) {
      cout << "stench!" << endl;
    }

    if (player.isSamePoint(wumpus.getPosition()) && flag == 0) {
      cout << "Player is killed!" << endl;
      player.kill();
      cout << "Game over!" << endl;
      ended = true;
    }

    if (player.isSamePoint(gold_position)) {
      cout << "Got the gold!" << endl;
      cout << "Game ended, you won!" << endl;
      ended = true;
    }

    if (player.isAdjacent(pit.get_position())) {
      cout << "breeze!" << endl;
    }
    if (player.isSamePoint(pit.get_position())) {
      cout << "Rot Forever!" << endl;
      cout << "Game over!" << endl;
      ended = true;
    }
    if (wumpus.isKilled() && flag == 0) {
      cout << "Screamingg!" << endl;
      cout << "Wumpus DEAD!" << endl;
      flag = 1;
    }
  }

  bool isOver() {
    return ended;
  }

};

int main() {
  int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;
  // take the six integers input from file
  //cin>>wumpus_x>>wumpus_y>>gold_x>>gold_y>>pit_x>>pit_y;
  //WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);
  ifstream inputFile;
  inputFile.open("filename.txt");

  if (inputFile.is_open()) {
    inputFile >> wumpus_x >> wumpus_y >> gold_x >> gold_y >> pit_x >> pit_y;
    inputFile.close();
  } else {
    cout << "Error opening the file." << endl;
  }
  WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);
  //WumpusWorld w;
  w.showGameState();
  while (!w.isOver()) {
    cout << "1: move forward" << endl;
    cout << "2: Turn left" << endl;
    cout << "3: Turn right" << endl;
    cout << "4: Shoot" << endl;
    cin >> c;
    if (c == 1) {
      w.moveForward();
    } else if (c == 2) {
      w.turnLeft();
    } else if (c == 3) {
      w.turnRight();
    } else if (c == 4) {
      w.shoot();
    }
  }
  return 0;
}
