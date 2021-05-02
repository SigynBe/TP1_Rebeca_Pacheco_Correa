//
//  main.c
//  TP1_Rebeca_Pacheco_Correa
//
//  Created by Rebeca Pacheco on 27/04/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//MATRIZ

//imprimir matriz
void imprime_mat(int n, char M[][n]){
    
    for(int line = 0; line < n; line++){
        printf("%d | ", line+1);
        
        
        for (int column = 0; column < n; column++) {
            printf("%c ", M[line][column]);
        }
        
        printf("\n");
    }
    
    printf("   ");
    
    for(int line = 0; line < n; line++){
        printf("--");
    }
    
    printf("\n");
    printf("    ");
    
    
    for (int clear = 0; clear < n; clear++) {
        printf("%d ", 1+clear);
    }
    
    printf("\n");
}

//conteudo da matriz
void array_content(int order, char matrix[][order], char character){
    for (int line = 0; line < order; line++){
        for (int column = 0; column < order; column++) {
            matrix[line][column] = character;
        }
    }
}

void fillRandom(int n, char matrix[][n]){
    int line = rand()%n;
    int column = rand()%n;
    
    if(matrix[line][column] == '*'){
        fillRandom( n, matrix);
    }else{
        matrix[line][column] = '*';
    }
    
}

void generateBombs(int n, char matrix[][n]){
    int bombs = 0.2f * (n * n);
    for (int i = 0; i < bombs; i++){
        fillRandom(n, matrix);
    }
}

//coordenadas correspondentes à linha e coluna e retornar o número de bombas presentes nas coordenadas vizinhas

int n_bombas(int n, int l, int c, char M[][n]){
    
    int count = 0;
    
    if(M[l][c] != '*'){
        if(c-1 >= 0 && M[l][c-1] == '*'){
            count++;
        }
        if(c+1 < n && M[l][c+1] == '*'){
            count++;
        }
        if(l+1 < n && c-1 >= 0 && M[l+1][c-1] == '*'){
            count++;
        }
        if(l+1 < n && c+1 < n && M[l+1][c+1] == '*'){
            count++;
        }
        if(l-1 >= 0 && c-1 >= 0 && M[l-1][c-1] == '*'){
            count++;
        }
        
        if(c+1 <  n && l-1 >= 0 && M[l-1][c+1] == '*'){
            count++;
        }
        if(l+1 < n && M[l+1][c] == '*'){
            count++;
        }
        if(l-1 >= 0 && M[l-1][c] == '*'){
            count++;
        }
        if(count != 0){
            M[l][c] = count;
        }
        
    }
    
    return count;
    
}

void toPlay(int n, char matrixInterface[][n], char matrixAnswer[][n], int line, int column){
    
    int store;
    int count = 0;
    int compare = 0.2 * (n*n);
    
    char storeBombs;
    
    if (line > n || column > n || line < 0 || column < 0){
        
        printf("Entrada inválida");
        printf("\n");
        
        imprime_mat(n, matrixInterface);
        printf("Digite a linha e coluna desejada:");
        printf("\n");
        scanf("%d %d", &line, &column);
        
        toPlay(n, matrixInterface, matrixAnswer, line, column);
    }else{
        
        if(matrixAnswer[line-1][column-1] == '*'){
            printf("VOCE PERDEU! FIM DO JOGO.");
            printf("\n");
            
            for (int lineBombs = 0; lineBombs < n; lineBombs++){
                for (int columnBombs = 0; columnBombs < n; columnBombs++) {
                    if(matrixAnswer[lineBombs][columnBombs] == '*'){
                        matrixInterface[lineBombs][columnBombs] = matrixAnswer[lineBombs][columnBombs];
                    }
                }
            }
            imprime_mat(n, matrixInterface);
            printf("\n");
        }else{
            for (int lineWinner = 0; lineWinner < n; lineWinner++){
                for (int columnWinner = 0; columnWinner < n; columnWinner++) {
                    if(matrixInterface[lineWinner][columnWinner] == '?'){
                        count++;
                    }
                }
            }
            if (count == compare) {
                printf("PARABENS! VOCE VENCEU!");
                imprime_mat(n, matrixAnswer);
            }else{
                store = n_bombas(n, line-1, column-1, matrixAnswer);
                storeBombs = (char)store + '0';
                matrixAnswer[line-1][column-1] = storeBombs;
                matrixInterface[line-1][column-1] = matrixAnswer[line-1][column-1];
                
                imprime_mat(n, matrixInterface);
                printf("\n");
                
                printf("Digite a linha e coluna desejada:");
                scanf("%d %d", &line, &column);
                
                toPlay(n, matrixInterface, matrixAnswer, line, column);
                printf("\n");
            }
        }
    }
}

int main(){
    
    int order, line, column;
    srand(time(NULL));
    
    printf("Digite o tamanho da matriz desejada:");
    scanf("%d", &order);
    
    if (order >= 3 && order <= 9) {
        
        char matrixInterface[order][order];
        char matrixAnswer[order][order];
        
        array_content(order, matrixInterface, '?');
        array_content(order, matrixAnswer, '0');
        generateBombs(order, matrixAnswer);
        imprime_mat(order, matrixInterface);
        
        printf("Digite a linha e coluna desejada:");
        scanf("%d %d", &line, &column);
        
        toPlay(order, matrixInterface, matrixAnswer, line, column);
        
    }
    
}
