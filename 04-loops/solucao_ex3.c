// Dump of assembler code for function ex3:
//    0x0000000000000000 <+0>:     mov    $0x0,%ecx
//    0x0000000000000005 <+5>:     mov    $0x0,%r8d
//    0x000000000000000b <+11>:    jmp    0x11 <ex3+17>
//    0x000000000000000d <+13>:    add    $0x1,%rcx
//    0x0000000000000011 <+17>:    cmp    %rdi,%rcx
//    0x0000000000000014 <+20>:    jge    0x28 <ex3+40>
//    0x0000000000000016 <+22>:    mov    %rcx,%rax
//    0x0000000000000019 <+25>:    cqto
//    0x000000000000001b <+27>:    idiv   %rsi
//    0x000000000000001e <+30>:    test   %rdx,%rdx
//    0x0000000000000021 <+33>:    jne    0xd <ex3+13>
//    0x0000000000000023 <+35>:    add    %rcx,%r8
//    0x0000000000000026 <+38>:    jmp    0xd <ex3+13>
//    0x0000000000000028 <+40>:    mov    %r8,%rax
//    0x000000000000002b <+43>:    retq
// End of assembler dump.

long ex3_solucao(long a, long b){
    long r;
    int c = 0;
    int d = 0;
    long df = (long) d;

    while(!(df >= a)){
        r = df % b;
        if (!(r != 0)){
            c += df;
        }
    df++;
    }
    r = c;

    return r;
}