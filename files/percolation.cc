#include <iostream>
#include <vector>
#include <random>
#include <ctime>
//percolation code in C++, translated from Java
class Percolation {

private:
  class Cell {
  public:
    //creating a nested class Cell
    Cell(int _row, int _col, int _dim, Percolation *encl)
    : row{_row}, col{_col}, dim{_dim}, isOpen{false}, outer{encl} { //outer is a reference to the enclosing percolation object
      if (row == 0) {
        isFull = true;
      } else {
        isFull = false;
      }
    }

    void fillNeighbours() { //fill the open neighbours of the cell
      fillNeighbours(row, col);
    }
    void fillNeighbours(int row, int col) {
      if (row == dim - 1) {
        outer->doesPercolate = true;
      }
      if (outer->grid[row][col].isOpen && outer->grid[row][col].isFull) {
        if (outer->grid[row][col].left != nullptr && outer->grid[row][col].left->isOpen && !outer->grid[row][col].left->isFull) {

          outer->grid[row][col].left->isFull = true;
          fillNeighbours(row, col - 1);
        }

        if (outer->grid[row][col].right != nullptr && outer->grid[row][col].right->isOpen && !outer->grid[row][col].right->isFull) {

					outer->grid[row][col].right->isFull = true;
        	fillNeighbours(row, col + 1);
				}

        if (outer->grid[row][col].above != nullptr && outer->grid[row][col].above->isOpen && !outer->grid[row][col].above->isFull) {

	        outer->grid[row][col].above->isFull = true;
					fillNeighbours(row - 1, col);
				}

        if (outer->grid[row][col].below != nullptr && outer->grid[row][col].below->isOpen && !outer->grid[row][col].below->isFull) {

	        outer->grid[row][col].below->isFull = true;
	        fillNeighbours(row + 1, col);
				}
      }
    }

    Cell *left, *right, *above, *below; //the four adjacent cells
    int row, col, dim; //the coordinates of the cell
    bool isFull, isOpen;
    Percolation *outer; //nested class cannot refer to enclosing class' variables, so a reference to the enclosing class has to be given
  };

  std::vector<std::vector< Cell >> grid; //just use push_back() to fill the grid.
  bool doesPercolate;
  int size;
  int numOpenSites;

public:
  Percolation(int n): size{n}{
    doesPercolate = false;
    numOpenSites = 0;
    grid.resize(n);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        grid[i].push_back(Cell(i, j, n, this));
      }
    }
    //making connections to neighbouring cells
    for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((i > 0 && i < n - 1) && (j > 0 && j < n - 1)) {
                    grid[i][j].left = &grid[i][j - 1];
                    grid[i][j].right = &grid[i][j + 1];
                    grid[i][j].above = &grid[i - 1][j];
                    grid[i][j].below = &grid[i + 1][j];
                }
                else if (i == 0 || i == n - 1) {
                    if (j > 0 && j < n -1) {
                        grid[i][j].left = &grid[i][j - 1];
                        grid[i][j].right = &grid[i][j + 1];
                        if (i == 0) {
                            grid[i][j].above = nullptr;
                            grid[i][j].below = &grid[i + 1][j];
                        }
                        else if (i == n - 1) {
                            grid[i][j].above = &grid[i - 1][j];
                            grid[i][j].below = nullptr;
                        }
                    }
                }
                else if (j == 0 || j == n - 1) {
                    if (i > 0 && i < n - 1) {
                        grid[i][j].above = &grid[i - 1][j];
                        grid[i][j].below = &grid[i + 1][j];

                        if (j == 0) {
                            grid[i][j].left = nullptr;
                            grid[i][j].right = &grid[i][j + 1];
                        }
                        else if ( j == n - 1) {
                            grid[i][j].left = &grid[i][j - 1];
                            grid[i][j].right = nullptr;
                        }
                    }
                }
            }
        }
        grid[0][0].left = nullptr;
        grid[0][0].right = &grid[0][1];
        grid[0][0].above = nullptr;
        grid[0][0].below = &grid[1][0];

        grid[0][n - 1].left = &grid[0][n - 2];
        grid[0][n - 1].right = nullptr;
        grid[0][n - 1].above = nullptr;
        grid[0][n - 1].below = &grid[1][n - 1];

        grid[n - 1][0].left = nullptr;
        grid[n - 1][0].right = &grid[n - 1][1];
        grid[n - 1][0].above = &grid[n - 2][0];
        grid[n - 1][0].below = nullptr;

        grid[n - 1][n - 1].left = &grid[n - 1][n - 2];
        grid[n - 1][n - 1].right = nullptr;
        grid[n - 1][n - 1].above = &grid[n - 2][n - 1];
        grid[n - 1][n - 1].below = nullptr;
  }

  void open(int i, int j) {
    int iActual = i - 1;
    int jActual = j - 1;

        /*if (iActual < 0 || iActual >= size) throw new IndexOutOfBoundsException("row index i out of Bounds\n");
        if (jActual < 0 || jActual >= size) throw new IndexOutOfBoundsException("column index j out of Bounds\n");*/

        if (!grid[iActual][jActual].isOpen) {
            grid[iActual][jActual].isOpen = true;
			      numOpenSites += 1;


            Cell *left, *right, *above , *below;

            left = grid[iActual][jActual].left;
            right = grid[iActual][jActual].right;
            above = grid[iActual][jActual].above;
            below = grid[iActual][jActual].below;

            if (left != nullptr && left->isOpen && left->isFull) {
                grid[iActual][jActual].isFull = true;
                grid[iActual][jActual].fillNeighbours();
            }
            if (right != nullptr && right->isOpen && right->isFull) {
				if (!grid[iActual][jActual].isFull) {
	                grid[iActual][jActual].isFull = true;
	                grid[iActual][jActual].fillNeighbours();
				}
            }
            if (above != nullptr && above->isOpen && above->isFull) {
				if (!grid[iActual][jActual].isFull) {
	                grid[iActual][jActual].isFull = true;
	                grid[iActual][jActual].fillNeighbours();
				}
            }

      if (below != nullptr &&  below->isOpen && below->isFull) {
				if (!grid[iActual][jActual].isFull) {
	                grid[iActual][jActual].isFull = true;
	                grid[iActual][jActual].fillNeighbours();
				}
      }

      }
  }

  bool isOpen(int i, int j) {
    return grid[i - 1][j - 1].isOpen;
  }

  bool isFull (int i, int j) {
    return grid[i - 1][j - 1].isFull;
  }

  bool percolates() {
    return doesPercolate;
  }

  int numberOfOpenSites() {
    return this->numOpenSites;
  }
};

int main(int argc, char const *argv[]) {
  //Percolation percObj(20);
  std::mt19937 engine(time(NULL));
  std::cout << "Enter the grid dimension" << '\n';
  int n;
  std::cin >> n;
  std::uniform_int_distribution<> dist(1, n);
  int i, j, sum;
  sum = 0;
  double p_threshold;
  int test;
  for (test = 0; test < 100; test++) {
    Percolation percObj(n);

    while (!percObj.percolates()) {
      i = dist(engine);
      j = dist(engine);

      if (!percObj.isOpen(i, j)) {
        percObj.open(i, j);
        sum++;
      }
    }
  }

  p_threshold = (1.0 * sum) / (test * n * n);
  std::cout << "*p = " << p_threshold << '\n';
  return 0;
}
