int ex4_solucao(int edi, int esi){
    long rdx, rsi;
    int ebx, eax, edx;

    ebx = edi;
    eax = 0;
    scanf("%d %d", &rsi, &rdx);
    edx = rdx;
    eax = rsi;
    eax += (rdx*2);
    eax += ebx;

    return eax;
}