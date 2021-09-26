// Dump of assembler code for function ex5:
//    0x0000000000000000 <+0>:     push   %rbx
//    0x0000000000000001 <+1>:     sub    $0x10,%rsp
//    0x0000000000000005 <+5>:     movl   $0x1,0xc(%rsp)
//    0x000000000000000d <+13>:    mov    $0x0,%ebx
//    0x0000000000000012 <+18>:    cmpl   $0x0,0xc(%rsp)
//    0x0000000000000017 <+23>:    jle    0x3b <ex5+59>
//    0x0000000000000019 <+25>:    lea    0xc(%rsp),%rsi
//    0x000000000000001e <+30>:    lea    0x0(%rip),%rdi        # 0x25 <ex5+37>
//    0x0000000000000025 <+37>:    mov    $0x0,%eax
//    0x000000000000002a <+42>:    callq  0x2f <ex5+47>
//    0x000000000000002f <+47>:    mov    0xc(%rsp),%eax
//    0x0000000000000033 <+51>:    test   %eax,%eax
//    0x0000000000000035 <+53>:    jle    0x12 <ex5+18>
//    0x0000000000000037 <+55>:    add    %eax,%ebx
//    0x0000000000000039 <+57>:    jmp    0x12 <ex5+18>
//    0x000000000000003b <+59>:    mov    %ebx,%eax
//    0x000000000000003d <+61>:    add    $0x10,%rsp
//    0x0000000000000041 <+65>:    pop    %rbx
//    0x0000000000000042 <+66>:    retq
// End of assembler dump.

int ex5_solucao(){
    int eax, rsi, ebx;

    eax = 0;
    rsi = 1;
    ebx = 0;

    while(!(rsi <= 0)){
        scanf("%d", &rsi);
        eax = rsi;

        if((!eax <= 0)){
            ebx += eax;
        }
    }
    eax = ebx;

    return eax;
}