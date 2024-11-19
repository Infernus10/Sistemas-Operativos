#include <stdio.h>

int dresta(int a, int b);
int psuma(int base, int pot);
int multiplicacion(int a, int b);



int main(){
    int op;
    printf("Que programa quieres usar 1(Dresta) o 2 (Psuma): ");
    scanf("%d", &op);

    if(op == 1) {  
        int a, b;
        printf("Ingresa el dividendo: ");
        scanf("%d", &a);
        printf("Ingresa el divisor: ");
        scanf("%d", &b);

        int resultado_division = dresta(a, b);
        printf("El resultado de la division es: %d\n", resultado_division);
    } else if(op == 2) {
        int base, pot;
        printf("Ingresa la base: ");
        scanf("%d", &base);
        printf("Ingresa la potencia: ");
        scanf("%d", &pot);

        int resultado_potencia = psuma(base, pot);
        printf("El resultado es: %d\n", resultado_potencia);
    } else {
        printf("no se puede");
    }

    return 0;
}

int dresta(int a, int b) {
    if (b == 0) { 
        printf("Error");
        return 1; 
    }

    if (a < b) {
        return 0;  
    } else {
        return 1 + dresta(a - b, b);  
    }
}


int psuma(int base, int pot) {
    if (pot == 0) {
        return 1; 
    } else {
        return multiplicacion(base, psuma(base, pot - 1));
    }
}


int multiplicacion(int a, int b) {
    if (b == 0) {
        return 0;  
    } else {
        return a + multiplicacion(a, b - 1); 
    }
}

