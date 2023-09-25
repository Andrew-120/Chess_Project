#include <iostream>
#include <vector>

class Piece {
private:
    int x;
    int y;

public:
    Piece() : x(0), y(0) {} 

    Piece(int startX, int startY) : x(startX), y(startY) {}

    bool move(int newX, int newY, int choose_piece)
    {
        if (newX < 0 || newX >= 8 || newY < 0 || newY >= 8) {
            return false;
        }

        int deltaX = newX - x;
        int deltaY = newY - y;

        if (deltaX == 0 && deltaY == 1 && choose_piece == 0) {
            x = newX;
            y = newY;
            return true;
        }
        else if (deltaX == 0 && deltaY == -1 && choose_piece == 0) {
            x = newX;
            y = newY;
            return true;
        }
        if (abs(deltaX) == 1 && abs(deltaY) == 1 && abs(deltaX) == abs(deltaY) && choose_piece == 1) {
            x = newX;
            y = newY;
            return true;
        }
        else if (deltaX == 1 && deltaY == 0 && choose_piece == 2) {
            x = newX;
            y = newY;
            return true;
        }
        else if (deltaX == -1 && deltaY == 0 && choose_piece == 2) {
            x = newX;
            y = newY;
            return true;
        }

        return false; 
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int newX) {
        x = newX;
    }

    void setY(int newY) {
        y = newY;
    }
};

enum class Player { PLAYER1, PLAYER2 };

class Board {
private:
    Piece player1Pieces[3];
    Piece player2Pieces[3];
    Player currentPlayer;

public:
    Board() : currentPlayer(Player::PLAYER1) {
        player1Pieces[0] = Piece(1, 0); // Circle
        player1Pieces[1] = Piece(3, 0); // Triangle
        player1Pieces[2] = Piece(5, 0); // Square

        player2Pieces[0] = Piece(5, 7); // Circle
        player2Pieces[1] = Piece(3, 7); // Triangle
        player2Pieces[2] = Piece(1, 7); // Square
    }

    Player playerWithTurn() const {
        return currentPlayer;
    }

    bool requiredMovement(int choose_piece) {
        int pieceIndex, newX, newY;
        std::cout << "Player " << (currentPlayer == Player::PLAYER1 ? "1" : "2") << ", enter piece index, newX, and newY: ";
        std::cin >> pieceIndex >> newX >> newY;
        choose_piece = pieceIndex;
        if (pieceIndex < 0 || pieceIndex >= 3) {
            std::cout << "Invalid piece index. Try again." << std::endl;
            return false; 
        }

        bool validMove = false;
        if (currentPlayer == Player::PLAYER1) {
            validMove = player1Pieces[pieceIndex].move(newX, newY, choose_piece);
        }
        else if (currentPlayer == Player::PLAYER2) {
            validMove = player2Pieces[pieceIndex].move(newX, newY, choose_piece);
        }

        if (!validMove) {
            std::cout << "Invalid move. Try again." << std::endl;
        }

        if (validMove) {
            currentPlayer = (currentPlayer == Player::PLAYER1) ? Player::PLAYER2 : Player::PLAYER1;
        }

        return validMove;
    }

    bool isValidMove(int newX, int newY) const {
        return newX >= 0 && newX < 8 && newY >= 0 && newY < 8;
    }

    bool winningState() const {
        for (int i = 0; i < 3; i++) {
            if (player1Pieces[i].getY() == 7) {
                return true;
            }

            if (player2Pieces[i].getY() == 0) {
                return true;
            }
        }

        return false;
    }

    Player winner() const {
        if (winningState()) {
            return currentPlayer == Player::PLAYER1 ? Player::PLAYER2 : Player::PLAYER1;
        }
        return Player::PLAYER1;
    }
};

int main() {
    int choose_piece = -1;

    Board gameBoard;

    while (!gameBoard.winningState()) {
        std::cout << "Current Player: " << (gameBoard.playerWithTurn() == Player::PLAYER1 ? "Player 1" : "Player 2") << std::endl;

        bool validMove = true;
        while (validMove) {
            validMove = gameBoard.requiredMovement(choose_piece);
            if (!validMove) {
                std::cout << "Invalid move. Try again." << std::endl;
            }
        }
    }

    Player winner = gameBoard.winner();
    std::cout << "Player " << (winner == Player::PLAYER1 ? "1" : "2") << " wins!" << std::endl;

    return 0;
}