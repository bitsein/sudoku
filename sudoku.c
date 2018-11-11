#include<stdio.h>
#include<stdlib.h>
#define SUCCESS 1    /* 成功 */
#define FAILURE 0    /* 失敗 */
typedef int** sudoku;
short int list[81]; //空白の番地リスト、行×９＋列
short int blank_num; //最初の空白の数
short int num;

sudoku sudoku_new(){ //sudokuのメモリ確保
    sudoku s; int i, j;
    s = malloc(9 * sizeof(int*));
    for(i=0; i<9; i++) s[i] = malloc(9 * sizeof(int));
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            s[i][j] = 0;
        }
    }
    return s;
}

void free_sudoku(sudoku s){ //sudokuのメモリ開放
    int i;
    for(i=0; i<9; i++) free(s[i]);
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

int rule_check(sudoku s, int i, int j, int k){
    int l, m, a, b;
    for(l=0; l<9; l++){
        if(k == s[i][l]) return FAILURE;
    }
    for(l=0; l<9; l++){
        if(k == s[l][j]) return FAILURE;
    }
    a = i/3; b = j/3;
    for(l=3*a; l<3*a+3; l++){
        for(m=3*b; m<3*b+3; m++){
            if(k == s[l][m]) return FAILURE;
        }
    }
    return SUCCESS;
}

int sudoku_append(sudoku s, int i, int j, int k){ //sudokuの(i, j)にkを埋める
    if(rule_check(s, i, j, k) == FAILURE) return FAILURE;    
    s[i][j] = k;
    num++;
    if(num == blank_num){
        print_sudoku(s);
        free_sudoku(s); exit(0);
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

void check_input(sudoku s, int i, int j, int k){
    switch(k){
        case 0:
            s[i][j] = k;
            list[blank_num] = i * 9 + j;
            blank_num++;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            if(rule_check(s, i, j, k) == FAILURE){
                printf("RULE_VIOLATION\n");
                free_sudoku(s); exit(1);
            }
            s[i][j] = k;
            break;
        default:
            printf("INPUT_0_to_9\n");
            free_sudoku(s); exit(1);
    }
}

int main(){
    sudoku s;
    s = sudoku_new();
    int i, j, k;
    blank_num = 0; num = 0;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            scanf("%d", &k);
            check_input(s, i, j, k);
        }
    }
    if(blank_num == 0){
        printf("ALREADY_CLEAR");
        free_sudoku(s); exit(1);
    }
    solver(s);
    printf("CANNOT_SOLVE\n");
    free_sudoku(s);
    return 0;
}
