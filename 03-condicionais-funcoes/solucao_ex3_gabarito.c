/* Implementar função solucao_ex3 */

void solucao_ex3(long a, long b, int *c1, int *c2, int *c3) {
    *c1 = a < b;
    *c2 = a == b;
    *c3 = a > b;
}