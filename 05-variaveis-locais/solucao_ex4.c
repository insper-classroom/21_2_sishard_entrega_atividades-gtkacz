// Dump of assembler code for function ex4:
//    0x0000000000000000 <+0>:     push   %rbx
//    0x0000000000000001 <+1>:     sub    $0x10,%rsp
//    0x0000000000000005 <+5>:     mov    %edi,%ebx
//    0x0000000000000007 <+7>:     lea    0x8(%rsp),%rdx
//    0x000000000000000c <+12>:    lea    0xc(%rsp),%rsi
//    0x0000000000000011 <+17>:    lea    0x0(%rip),%rdi        # 0x18 <ex4+24>
//    0x0000000000000018 <+24>:    mov    $0x0,%eax
//    0x000000000000001d <+29>:    callq  0x22 <ex4+34>
//    0x0000000000000022 <+34>:    mov    0x8(%rsp),%edx
//    0x0000000000000026 <+38>:    mov    0xc(%rsp),%eax
//    0x000000000000002a <+42>:    lea    (%rax,%rdx,2),%eax
//    0x000000000000002d <+45>:    add    %ebx,%eax
//    0x000000000000002f <+47>:    add    $0x10,%rsp
//    0x0000000000000033 <+51>:    pop    %rbx
//    0x0000000000000034 <+52>:    retq
// End of assembler dump.

int ex4_solucao(int a){
    long b, c;
    int d, r, e;

    d = a;
    r = 0;
    scanf("%d %d", &c, &b);
    e = b;
    r = c;
    r += (b*2);
    r += d;

    return r;
}