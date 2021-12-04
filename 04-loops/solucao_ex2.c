// Dump of assembler code for function soma_n:
//    0x0000000000000000 <+0>:     mov    $0x0,%edx
//    0x0000000000000005 <+5>:     mov    $0x0,%eax
//    0x000000000000000a <+10>:    jmp    0x15 <soma_n+21>
//    0x000000000000000c <+12>:    movslq %edx,%rcx
//    0x000000000000000f <+15>:    add    %rcx,%rax
//    0x0000000000000012 <+18>:    add    $0x1,%edx
//    0x0000000000000015 <+21>:    cmp    %edi,%edx
//    0x0000000000000017 <+23>:    jl     0xc <soma_n+12>
//    0x0000000000000019 <+25>:    repz retq
// End of assembler dump.

//edi = int a;
//edx = int b;
//rcx = long c;
//rax = long r;

int soma_n_solucao(long c, int a){
    long r;
    int b = 0;

    while(b < a){
        c = (long) b;
        r += c;
        b++;
    }

    return r;
}