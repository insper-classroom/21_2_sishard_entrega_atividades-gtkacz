// TODO implemente uma funcao chamada solucao aqui

// Dump of assembler code for function exercicio:
//    0x000000000000000a <+0>:     endbr64
//    0x000000000000000e <+4>:     add    %edi,%edi
//    0x0000000000000010 <+6>:     lea    (%rsi,%rsi,2),%eax
//    0x0000000000000013 <+9>:     add    %edi,%eax
//    0x0000000000000015 <+11>:    mov    %eax,(%rdx)
//    0x0000000000000017 <+13>:    lea    (%rsi,%rsi,4),%eax
//    0x000000000000001a <+16>:    add    %edi,%eax
//    0x000000000000001c <+18>:    retq
// End of assembler dump.

//edi = int a;
//rsi = long b;
//rdx = long *c;
//eax = int resposta;

int solucao(int a, long b, long *c){
    int r;

    a += a;
    r = b + 2*b;
    r += a;
    *c = r;
    r = b + 4*b;
    r += a;

    return r;
}
