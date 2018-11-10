#include<stdio.h>
#include<stdlib.h>
#define SUCCESS 1    /* 成功 */
#define FAILURE 0    /* 失敗 */
typedef int** sudoku;
short int fill_list[81];
short int list[81];
short int num;
short int filled_num;

sudoku sudoku_new(){
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

void free_sudoku(sudoku s){
    int i;
    for(i=0; i<9; i++){
        free(s[i]);
    }
    free(s);
}

void print_sudoku(sudoku s){
    int i, j;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            printf("%d ",s[i][j]);
        }
        printf("\n");
    }
}

int row_check(sudoku s, int i, int j, int k){
    int l;
    for(l=0; l<9; l++){
        if(l != j && k == s[i][l]) return FAILURE;
    }
    return SUCCESS;
}

int column_check(sudoku s, int i, int j, int k){
    int l;
    for(l=0; l<9; l++){
        if(l != i && k == s[l][j]) return FAILURE;
    }
    return SUCCESS;
}

int block_check(sudoku s, int i, int j, int k){
    int a, b, m, n;
    a = i/3; b = j/3;
    for(m=3*a; m<3*a+3; m++){
        for(n=3*b; n<3*b+3; n++){
            if(i != m && j != n && k == s[m][n]) return FAILURE;
        }
    }
    return SUCCESS;
}

int sudoku_append(sudoku s, int i, int j, int k){
    if(row_check(s, i, j, k) == FAILURE) return FAILURE;
    if(column_check(s, i, j, k) == FAILURE) return FAILURE;
    if(block_check(s, i, j, k) == FAILURE) return FAILURE;
    
    fill_list[filled_num] = i * 9 + j;
    s[i][j] = k;
    filled_num++;
    if(filled_num == 81){
        print_sudoku(s);
        free_sudoku(s);
        exit(0);
    }
    return SUCCESS;
}

void sudoku_remove(sudoku s){
    filled_num--; num--;
    int row, column;
    row = fill_list[filled_num] / 9;
    column = fill_list[filled_num] % 9;
    s[row][column] = 0;
}

void solver(sudoku s){
    int i, j, k;
    i = list[num] / 9;
    j = list[num] % 9;
    for(k=1; k<=9; k++){
        if(sudoku_append(s, i, j, k) == SUCCESS){
            num++;
            solver(s);
            sudoku_remove(s);
        }
    }
}

int main(){
    sudoku s;
    s = sudoku_new();
    int i, j, k;
    filled_num = 0; num = 0; k = 0;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            scanf("%d", &s[i][j]);
            if(s[i][j] != 0) filled_num++;
            else{
                list[k] = i * 9 + j; k++;
            }
        }
    }
    solver(s);
    printf("CANNOT_SOLVE");
}
