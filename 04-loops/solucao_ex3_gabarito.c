/* Implemente aqui sua versão em C da função ex3
 * presente no arquivo ex3.o
 * 
 * Chame sua função de ex3_solucao */

long ex3_solucao(long n, long dig) {
    long soma = 0;
    for (long i = 0; i < n; i++) {
        if (i % dig == 0) {
         soma += i;
        }   
    }
    return soma;
}