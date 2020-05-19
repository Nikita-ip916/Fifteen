void moveF(int dir, int** gameBoard, const int n, int* emptyElem)
{
    if (dir == 1 && emptyElem[1] < 4 && emptyElem[1] > 0) {
        gameBoard[emptyElem[0]][emptyElem[1]]
                = gameBoard[emptyElem[0]][emptyElem[1] + 1];
        gameBoard[emptyElem[0]][emptyElem[1] + 1] = 0;
    } else if (dir == 2 && emptyElem[1] > 1 && emptyElem[1] < 5) {
        gameBoard[emptyElem[0]][emptyElem[1]]
                = gameBoard[emptyElem[0]][emptyElem[1] - 1];
        gameBoard[emptyElem[0]][emptyElem[1] - 1] = 0;
    } else if (dir == 3 && emptyElem[0] < 4 && emptyElem[0] > 0) {
        gameBoard[emptyElem[0]][emptyElem[1]]
                = gameBoard[emptyElem[0] + 1][emptyElem[1]];
        gameBoard[emptyElem[0] + 1][emptyElem[1]] = 0;
    } else if (dir == 4 && emptyElem[0] > 1 && emptyElem[0] < 5) {
        gameBoard[emptyElem[0]][emptyElem[1]]
                = gameBoard[emptyElem[0] - 1][emptyElem[1]];
        gameBoard[emptyElem[0] - 1][emptyElem[1]] = 0;
    }
}
