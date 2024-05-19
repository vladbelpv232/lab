#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include "C:/Users/User/CLionProjects/untitled/libs/date_structures/matrix.h"

typedef struct {
    int row;
    int col;
    int **board;
    int **nextState;
    int boardSize;
    int *boardColSize;
} CellArgs;

int **matrix_task_1;

void *increment_submatrix(void *arg) {
    int *query = (int *)arg;
    int row1 = query[0], col1 = query[1], row2 = query[2], col2 = query[3];

    for (int i = row1; i <= row2; i++) {
        for (int j = col1; j <= col2; j++) {
            matrix_task_1[i][j]++;
        }
    }

    pthread_exit(NULL);
}

void task_1(int n, int num_queries, int **queries) {

    matrix_task_1 = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix_task_1[i] = (int *)calloc(n, sizeof(int));
    }

    pthread_t threads[num_queries];
    for (int i = 0; i < num_queries; i++) {
        pthread_create(&threads[i], NULL, increment_submatrix, (void *)queries[i]);
    }

    for (int i = 0; i < num_queries; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < num_queries; i++) {
        free(queries[i]);
    }
    free(queries);
}

void test_for_task_1() {
    int n = 3;
    int num_queries = 2;
    int **queries;

    queries = (int **)malloc(num_queries * sizeof(int *));
    for (int i = 0; i < num_queries; i++) {
        queries[i] = (int *)malloc(4 * sizeof(int));
    }

    queries[0][0] = 1; queries[0][1] = 1; queries[0][2] = 2; queries[0][3] = 2;
    queries[1][0] = 0; queries[1][1] = 0; queries[1][2] = 1; queries[1][3] = 1;

    task_1(n, num_queries, queries);

    int **matrix_t;

    matrix_t = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix_t[i] = (int *)calloc(n, sizeof(int));
    }
    matrix_t[0][0] = 1; matrix_t[0][1] = 1; matrix_t[0][2] = 0;
    matrix_t[1][0] = 1; matrix_t[1][1] = 2; matrix_t[1][2] = 1;
    matrix_t[2][0] = 0; matrix_t[2][1] = 1; matrix_t[2][2] = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            assert(matrix_task_1[i][j] == matrix_t[i][j]);
        }
    }
}

void *processCell(void *arg) {
    CellArgs *cellArgs = (CellArgs *)arg;
    int row = cellArgs->row;
    int col = cellArgs->col;
    int **board = cellArgs->board;
    int **nextState = cellArgs->nextState;
    int boardSize = cellArgs->boardSize;
    int *boardColSize = cellArgs->boardColSize;

    int liveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int r = row + i, c = col + j;
            if (r >= 0 && r < boardSize && c >= 0 && c < boardColSize[r]) {
                liveNeighbors += board[r][c];
            }
        }
    }

    if (board[row][col] == 1) {
        if (liveNeighbors < 2 || liveNeighbors > 3) {
            nextState[row][col] = 0;
        } else {
            nextState[row][col] = 1;
        }
    } else {
        if (liveNeighbors == 3) {
            nextState[row][col] = 1;
        } else {
            nextState[row][col] = 0;
        }
    }

    free(cellArgs);
    pthread_exit(NULL);
}

void task_2(int **board, int boardSize, int *boardColSize) {
    int **nextState = (int **)malloc(boardSize * sizeof(int *));
    for (int i = 0; i < boardSize; i++) {
        nextState[i] = (int *)calloc(boardColSize[i], sizeof(int));
    }

    pthread_t threads[boardSize * boardColSize[0]];
    int threadIndex = 0;

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            CellArgs *cellArgs = (CellArgs *)malloc(sizeof(CellArgs));
            cellArgs->row = i;
            cellArgs->col = j;
            cellArgs->board = board;
            cellArgs->nextState = nextState;
            cellArgs->boardSize = boardSize;
            cellArgs->boardColSize = boardColSize;

            pthread_create(&threads[threadIndex++], NULL, processCell, (void *)cellArgs);
        }
    }

    for (int i = 0; i < threadIndex; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < boardSize; i++) {
        free(board[i]);
        board[i] = nextState[i];
        nextState[i] = NULL;
    }
    free(nextState);
}

void test_for_task_2() {
    int countCol = 3;
    int boardSize = 4;
    int boardColSize[] = {3, 3, 3, 3};
    int **board = (int **)malloc(boardSize * sizeof(int *));
    for (int i = 0; i < boardSize; i++) {
        board[i] = (int *)malloc(boardColSize[i] * sizeof(int));
    }

    board[0][0] = 0; board[0][1] = 1; board[0][2] = 0;
    board[1][0] = 0; board[1][1] = 0; board[1][2] = 1;
    board[2][0] = 1; board[2][1] = 1; board[2][2] = 1;
    board[3][0] = 0; board[3][1] = 0; board[3][2] = 0;

    task_2(board, boardSize, boardColSize);

    int **board_t = (int **)malloc(boardSize * sizeof(int *));
    for (int i = 0; i < boardSize; i++) {
        board_t[i] = (int *)malloc(boardColSize[i] * sizeof(int));
    }

    board_t[0][0] = 0; board_t[0][1] = 0; board_t[0][2] = 0;
    board_t[1][0] = 1; board_t[1][1] = 0; board_t[1][2] = 1;
    board_t[2][0] = 0; board_t[2][1] = 1; board_t[2][2] = 1;
    board_t[3][0] = 0; board_t[3][1] = 1; board_t[3][2] = 0;

    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < countCol; ++j) {
            assert(board[i][j] == board_t[i][j]);
        }
    }
}

int sortedNumsCompare(const void * first_num, const void * second_num){
    return (*(int*)first_num - *(int*)second_num);
}


void fillingNumFrameSorted(int *array, matrix m, size_t ind_row, size_t ind_col){ size_t
            arrayInd = 0;
    for (size_t mIndRow = ind_row - 1; mIndRow < ind_row + 2; mIndRow++){
        for(size_t mIndCol = ind_col - 1; mIndCol < ind_col + 2; mIndCol++){
            if (mIndRow != ind_row || mIndCol != ind_col){
                array[arrayInd++] = m.values[mIndRow][mIndCol];
            }
        }
    }
    qsort(array, 8, sizeof(int), sortedNumsCompare);
}

void task_3(matrix *m, size_t size){
    int frame[8];
    for (size_t indRow = 1; indRow < size - 1; indRow++){
        for(size_t indCol = 1; indCol < size - 1; indCol++){
            fillingNumFrameSorted(frame, *m, indRow, indCol);
            int median = (frame[3] + frame[4]) / 2;
            m->values[indRow][indCol] = median;
        }
    }
}

void test_for_task_3(){
    size_t size = 3;
    matrix got = createMatrixFromArray((int[]) {
            10, 20, 30,
            25, 35, 45,
            15, 25, 35
    }, 3, 3);
    task_3(&got, size);
    matrix expected = createMatrixFromArray( (int[]) {
            10, 20, 30,
            25, 25, 45,
            15, 25, 35
    }, 3, 3);
    assert(areTwoMatricesEqual(&got, &expected));
}

int mainsss(){
    test_for_task_2();
}