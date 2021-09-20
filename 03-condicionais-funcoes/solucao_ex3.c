// Dump of assembler code for function ex3:
//    0x0000000000000000 <+0>:     cmp    %rsi,%rdi
//    0x0000000000000003 <+3>:     setl   %al
//    0x0000000000000006 <+6>:     movzbl %al,%eax
//    0x0000000000000009 <+9>:     mov    %eax,(%rdx)
//    0x000000000000000b <+11>:    cmp    %rsi,%rdi
//    0x000000000000000e <+14>:    sete   %al
//    0x0000000000000011 <+17>:    movzbl %al,%eax
//    0x0000000000000014 <+20>:    mov    %eax,(%rcx)
//    0x0000000000000016 <+22>:    cmp    %rsi,%rdi
//    0x0000000000000019 <+25>:    setg   %al
//    0x000000000000001c <+28>:    movzbl %al,%eax
//    0x000000000000001f <+31>:    mov    %eax,(%r8)
//    0x0000000000000022 <+34>:    retq
// End of assembler dump.

//rdi = long a;
//rsi = long b;
//eax = int r;
//rdx = long *c;
//rcx = long *d;
//r8 = long *e;

void solucao_ex3(long a, long b, int *c, int *d, int *e){
    int r;
    //int *c, *d, *e;

    r = (a < b);
    *c = r;

    r = (a == b);
    *d = r;

    r = (a > b);
    *e = r;
}