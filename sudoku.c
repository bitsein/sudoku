#include<stdio.h>
#include<stdlib.h>
#define SUCCESS 1    /* 成功 */
#define FAILURE 0    /* 失敗 */
typedef int** sudoku;
short int list[81]; //空白の番地リスト、十の位に行、一の位に列
short int blank_num; //最初の空白の数
short int num;

sudoku sudoku_new(){ //sudokuのメモリ確保
    sudoku s; int i, j;
    s = malloc(9 * sizeof(int*));
    for(i=0; i<9; i++){
        s[i] = malloc(9 * sizeof(int));
    }
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            s[i][j] = 0;
        }
    }
    return s;
}

void free_sudoku(sudoku s){ //sudokuのメモリ開放
    int i;
    for(i=0; i<9; i++){
        free(s[i]);
    }
    free(s);
}

void print_sudoku(sudoku s){ //sudokuを標準出力に表示
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            printf("%d ",s[i][j]);
        }
        printf("\n");
    }
}

int row_check(sudoku s, int i, int j, int k){ //行方向のチェック
    int l;
    for(l=0; l<9; l++){
        if(l != j && k == s[i][l]) return FAILURE;
    }
    return SUCCESS;
}

int column_check(sudoku s, int i, int j, int k){ //列方向のチェック
    int l;
    for(l=0; l<9; l++){
        if(l != i && k == s[l][j]) return FAILURE;
    }
    return SUCCESS;
}

int block_check(sudoku s, int i, int j, int k){ //3*3ブロックのチェック
    int a, b, m, n;
    a = i/3; b = j/3;
    for(m=3*a; m<3*a+3; m++){
        for(n=3*b; n<3*b+3; n++){
            if(i != m && j != n && k == s[m][n]) return FAILURE;
        }
    }
    return SUCCESS;
}

int sudoku_append(sudoku s, int i, int j, int k){ //sudokuの(i, j)にkを埋める
    if(row_check(s, i, j, k) == FAILURE) return FAILURE;
    if(column_check(s, i, j, k) == FAILURE) return FAILURE;
    if(block_check(s, i, j, k) == FAILURE) return FAILURE;
    
    s[i][j] = k;
    num++;
    if(num == blank_num){
        print_sudoku(s);
        free_sudoku(s);
        exit(0);
    }
    return SUCCESS;
}

void sudoku_remove(sudoku s){ //最近埋めたマスを消す
    num--;
    int row, column;
    row = list[num] / 9;
    column = list[num] % 9;
    s[row][column] = 0;
}

void solver(sudoku s){ //再帰的に使う
    int i, j, k;
    i = list[num] / 9;
    j = list[num] % 9;
    for(k=1; k<=9; k++){
        if(sudoku_append(s, i, j, k) == SUCCESS){
            solver(s);
            sudoku_remove(s);
        }
    }
}

int main(){
    sudoku s;
    s = sudoku_new();
    int i, j;
    blank_num = 0; num = 0;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            scanf("%d", &s[i][j]);
            if(s[i][j] == 0) {
                list[blank_num] = i * 9 + j;
                blank_num++;
            }
        }
    }
    solver(s);
    printf("CANNOT_SOLVE");
}
