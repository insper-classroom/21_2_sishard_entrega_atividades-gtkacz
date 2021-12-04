long vezes2(long a);

<<<<<<< HEAD
// Dump of assembler code for function ex2:
//    0x0000000000000005 <+0>:     push   %rbx
//    0x0000000000000006 <+1>:     mov    %rdi,%rbx
//    0x0000000000000009 <+4>:     mov    %rsi,%rdi
//    0x000000000000000c <+7>:     callq  0x <vezes2>
//    0x0000000000000011 <+12>:    cmp    %rbx,%rax
//    0x0000000000000014 <+15>:    jle    0x19 <ex2+20>
//    0x0000000000000016 <+17>:    add    %rbx,%rbx
//    0x0000000000000019 <+20>:    add    %rbx,%rax
//    0x000000000000001c <+23>:    pop    %rbx
//    0x000000000000001d <+24>:    retq
// End of assembler dump.

//rdi = long a;
//rsi = long b;
//rbx = long c;
//rax = long r;

long solucao_ex2(long a, long b){
    long r, c;

    c = a;
    a = b;

    r = vezes2(a);

    if (!(r <= c)){
        c += c;
    }

    r += c;

    return r;
}
=======
/* Implementar função solucao_ex2 */
>>>>>>> template/main
