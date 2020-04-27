void moveF(int dir, int** arr, const int n, int* mas)
{
    if (dir == 1 && mas[1] < 4) {
        arr[mas[0]][mas[1]] = arr[mas[0]][mas[1] + 1];
        arr[mas[0]][mas[1] + 1] = 0;
    } else if (dir == 2 && mas[1] > 1) {
        arr[mas[0]][mas[1]] = arr[mas[0]][mas[1] - 1];
        arr[mas[0]][mas[1] - 1] = 0;
    } else if (dir == 3 && mas[0] < 4) {
        arr[mas[0]][mas[1]] = arr[mas[0] + 1][mas[1]];
        arr[mas[0] + 1][mas[1]] = 0;
    } else if (dir == 4 && mas[0] > 1) {
        arr[mas[0]][mas[1]] = arr[mas[0] - 1][mas[1]];
        arr[mas[0] - 1][mas[1]] = 0;
    }
}
