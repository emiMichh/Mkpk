#include <stdio.h>
#include <string.h>

#define MAX_LEN 200

// Función para eliminar las implicaciones en una FBF
void eliminarImplicaciones(char *expresion, char *resultado) {
    int len = strlen(expresion);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (expresion[i] == '-') { // Encontramos "-" como implicación
            resultado[j - 1] = '('; // Reemplazamos "A - B" por "(~A + B)"
            resultado[j++] = '~';
            resultado[j++] = expresion[i - 1];
            resultado[j++] = '+';
        } else {
            resultado[j++] = expresion[i];
        }
    }
    resultado[j++] = ')';
    resultado[j] = '\0';
}

int main() {
    char expresion[MAX_LEN] = "(((a+b)*(c-d))+~(x*y))";
    char resultado[MAX_LEN];
    
    eliminarImplicaciones(expresion, resultado);
    
    printf("Original: %s\n", expresion);
    printf("Sin implicaciones: %s\n", resultado);
    
    return 0;
}
