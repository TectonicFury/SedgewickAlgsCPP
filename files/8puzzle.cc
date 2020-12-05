#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <queue>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <cstdio>
using std::vector;

namespace AMA {

  class Board {
  public:
    Board(vector<vector<int>>& tiles) {
      _dimension = tiles.size();
      the_board = tiles;
      manhattanDist = -1;
      int flag = 0;
      for(int i = 0; i < _dimension; i++) {
        for(int j = 0; j < _dimension; j++) {
          if(the_board[i][j] == 0) {
            i0 = i;
            j0 = j;
            flag = 1;
            break;
          }
        }
        if (flag == 1) {
          break;
        }
      }
    }

    Board() {
      _dimension = 3;
      the_board.resize(3);
      manhattanDist = -1;
      for (size_t i = 0; i < _dimension; i++) {
        for (size_t j = 0; j < _dimension; j++) {
          the_board[i].push_back(i * _dimension + j);
        }
      }
    }

    Board(const Board& bd) { //copy constructor
      _dimension = bd._dimension;
      the_board = bd.the_board;
      i0 = bd.i0;
      j0 = bd.j0;
      manhattanDist = -1;
    }

    Board& operator=(const Board& bd) {
      _dimension = bd._dimension;
      the_board = bd.the_board;
      i0 = bd.i0;
      j0 = bd.j0;
      manhattanDist = -1;
      return *this;
    }

    Board(Board&& bd) noexcept { //move constructor
      _dimension = bd._dimension;
      i0 = bd.i0;
      j0 = bd.j0;
      manhattanDist = -1;
      the_board = std::move(bd.the_board);
    }

    Board& operator=(Board&& bd) noexcept { //move assignment
      _dimension = bd._dimension;
      i0 = bd.i0;
      j0 = bd.j0;
      manhattanDist = -1;
      the_board = std::move(bd.the_board);
      return *this;
    }

    int dimension() {
      return _dimension;
    }

    int hamming() {
      int hammingDistance = 0;
      for(int i = 0; i < _dimension; i++) {
        for(int j = 0; j < _dimension; j++) {
          if(the_board[i][j] != 0) {
            if(the_board[i][j] != (i * _dimension + j + 1)) hammingDistance++;
          }
        }
      }
      return hammingDistance;
    }

    int manhattan() {
      if(manhattanDist < 0){
			int i1,j1;
			manhattanDist = 0;
			for(int i = 0; i < _dimension; i++) {
				for(int j = 0; j < _dimension; j++) {
					if(the_board[i][j] != 0) {
						if(the_board[i][j] != i * _dimension + j + 1) {
							i1 = (the_board[i][j] - 1)/_dimension;
							j1 = (the_board[i][j] - 1)%_dimension;
							manhattanDist += abs(i1-i) + abs(j1 - j);
						}
					}
				}
			}
		  }
		  return manhattanDist;
    }

    bool isGoal() {
      return hamming() == 0;
    }

    bool equals(Board b) {
      if (_dimension != b._dimension) return false;
      for (int i = 0; i < _dimension; i++) {
        for (int j = 0; j < _dimension; j++) {
          if (the_board[i][j] != b.the_board[i][j]) return false;
        }
      }
      return true;
    }

    vector<Board> neighbours() {
      vector<Board> neighbouringBoards;

      if(j0 > 0) {
			Board leftMove(the_board);
			leftMove.the_board[i0][j0] = the_board[i0][j0 - 1];
			leftMove.the_board[i0][j0 - 1] = 0;
			leftMove.j0 = j0 - 1;
			neighbouringBoards.push_back(leftMove);
		}

		if(j0 < _dimension - 1) {
			Board rightMove(the_board);
			rightMove.the_board[i0][j0] = the_board[i0][j0 + 1];
			rightMove.the_board[i0][j0 + 1] = 0;
			rightMove.j0 = j0 + 1;
			neighbouringBoards.push_back(rightMove);
		}

		if(i0 > 0) {
			Board upMove(the_board);
			upMove.the_board[i0][j0] = the_board[i0 - 1][j0];
			upMove.the_board[i0 - 1][j0] = 0;
			upMove.i0 = i0 - 1;
			neighbouringBoards.push_back(upMove);
		}

		if(i0 < _dimension - 1) {
			Board downMove(the_board);
			downMove.the_board[i0][j0] = the_board[i0 + 1][j0];
			downMove.the_board[i0 + 1][j0] = 0;
			downMove.i0 = i0 + 1;
			neighbouringBoards.push_back(downMove);
		}

      return neighbouringBoards;
    }

    Board twin() {
      Board bTwin(the_board);
      int irow1, irow2, jcol1, jcol2,temp;
      std::minstd_rand engine(time(NULL));
      std::uniform_int_distribution dist(0, _dimension - 1);
      bool done = false;
      while(!done) {
        irow1 = dist(engine);
        jcol1 = dist(engine);

        if(bTwin.the_board[irow1][jcol1] != 0) {

          irow2 = dist(engine);
          jcol2 = dist(engine);

          if((bTwin.the_board[irow2][jcol2] != 0) && (bTwin.the_board[irow2][jcol2] != bTwin.the_board[irow1][jcol1])) {
            temp = bTwin.the_board[irow1][jcol1];
            bTwin.the_board[irow1][jcol1] = bTwin.the_board[irow2][jcol2];
            bTwin.the_board[irow2][jcol2] = temp;
            done = true;
          }
        }
      }
      return bTwin;
    }

    friend std::ostream& operator<<(std::ostream& os, const Board& bd) {
      os << bd._dimension << "\n";
      for (size_t k = 0; k < bd._dimension; k++) {
        for (size_t l = 0; l < bd._dimension; l++) {
          os << bd.the_board[k][l] <<" ";
        }
        os <<"\n";
      }
      return os;
    }

  private:
    int _dimension;
    vector<vector<int>> the_board;
    int i0, j0;
    int manhattanDist;
  };

  class Solver {

  public:

    class Node {

    public:
      Board node_bd;
      int moves;
      Node* previous;

      Node(Board bd, int movs, Node* prev) : node_bd{bd} {
        moves = movs;
        previous = prev;

      }

      Node() : node_bd{Board()} {
        previous = nullptr;
        moves = 0;
      }

      Node(const Node& nd) {
        node_bd = nd.node_bd;
        previous = nd.previous;
        moves = nd.moves;
      }

      Node& operator=(const Node& nd) {
        node_bd = nd.node_bd;
        previous = nd.previous;
        moves = nd.moves;
        //std::cout << "copy operator " << '\n';
        //printf("%p\n", previous);
        return *this;
      }

      bool compare_nodes(Node* a) {
        return !((this->node_bd.manhattan() + this->moves) < (a->node_bd.manhattan() + a->moves));
      }
    };

    class NodeCompare {
    public:
      bool operator() (Node* a, Node* b) {
        return a->compare_nodes(b);
      }
    };

  Solver(Board init_bd) {
    moves_for_init = 0;
    moves_for_twin = 0;
    Node* init_node = new Node(init_bd, 0, nullptr);
    Node* init_node_twin = new Node(init_bd.twin(), 0, nullptr);

    pq.push(init_node);
    pq_twin.push(init_node_twin);

    Node* min_node_pq;
    Node* min_node_pq_twin;
    Node* temp;
    //std::cout << "temp address = " << temp <<'\n';
    min_node_pq = pq.top();
    //std::cout << "min_node_pq address = " << min_node_pq << '\n';
    //solutionVec.push_back(min_node_pq->node_bd);
    min_node_pq_twin = pq_twin.top();
    //std::cout << "min_node_pq_twin address = " << min_node_pq_twin << '\n';
    pq.pop();
    pq_twin.pop();

    while (!(min_node_pq->node_bd.isGoal() || min_node_pq_twin->node_bd.isGoal())) {
      vector<Board> ngbrs = min_node_pq->node_bd.neighbours();
      vector<Board> ngbrs_twin = min_node_pq_twin->node_bd.neighbours();
      //std::cout << "************count********* = " << moves_for_init << '\n';
      for (auto& bd : ngbrs) {
        temp = new Node(bd, min_node_pq->moves + 1, min_node_pq);
        //std::cout << "temp address orig = " << temp <<'\n';
        if (min_node_pq->previous == nullptr) {
          pq.push(temp);
          //delete temp;
        } else{
					if(!temp->node_bd.equals(min_node_pq->previous->node_bd)){
            //std::cout << "orig" << '\n';
						pq.push(temp);
            //delete temp;
					}
				}
      }

      for (auto& bd : ngbrs_twin) {
        temp = new Node(bd, min_node_pq_twin->moves + 1, min_node_pq_twin);
        //std::cout << "temp address twin = " << temp <<'\n';
        if (min_node_pq_twin->previous == nullptr) {
          pq_twin.push(temp);
        } else{
					if(!temp->node_bd.equals(min_node_pq_twin->previous->node_bd)){
            //std::cout << "twin" << '\n';
						pq_twin.push(temp);
					}
				}
      }

      min_node_pq = pq.top();

      pq.pop();
      min_node_pq_twin = pq_twin.top();
      pq_twin.pop();

      ++moves_for_init;
      ++moves_for_twin;
    }
    std::cout << "the total trials = " << moves_for_init << '\n';
    if (min_node_pq->node_bd.isGoal()) {
      //std::cout << "success" << '\n';
      //std::cout << min_node_pq->node_bd << '\n';
      _isSolvable = true;
      moves_for_init = min_node_pq->moves;

      solutionVec.push_back(min_node_pq->node_bd);

      while (min_node_pq->previous != nullptr) {
        min_node_pq = min_node_pq->previous;
        solutionVec.push_back(min_node_pq->node_bd);
        //std::cout << "hi " << solutionVec.size() << '\n';
      }
      std::reverse(solutionVec.begin(), solutionVec.end());

    } else if (min_node_pq_twin->node_bd.isGoal()) {
      _isSolvable = false;
    }
  }

  bool isSolvable() {
    return _isSolvable;
  }

  vector<Board>& solution() {
    return solutionVec;
  }

  int numMoves() {
    return moves_for_init;
  }
private:
  int moves_for_init;
  int moves_for_twin;
  std::priority_queue<Node*, std::vector<Node*>, NodeCompare> pq;
  std::priority_queue<Node*, std::vector<Node*>, NodeCompare> pq_twin;
  bool _isSolvable;
  vector<Board> solutionVec;
  };

}

int main(int argc, char* argv[]) {
  //std::cout << "Allaahu Akbarr!!" << '\n';
  std::ifstream in(argv[1]);
  int n;

  in >> n;
  vector<vector<int>> tile(n);
  int m;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      in >> m;
      tile[i].push_back(m);
    }
  }

  AMA::Board b(tile);
  //std::cout << "original board = " << '\n';
  //std::cout << b << '\n';
  const auto start = std::chrono::steady_clock::now();
  
  AMA::Solver slvr(b);

  const auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Time in seconds: " << elapsed.count() << '\n';

  std::cout << slvr.isSolvable() << '\n';

  if (slvr.isSolvable()) {
    vector<AMA::Board> boards = slvr.solution();
    for (size_t i = 0; i < boards.size(); i++) {
      std::cout << boards[i] << '\n';
    }
    std::cout << boards.size() << '\n';
  }

  std::cout << slvr.numMoves() << '\n';


}
