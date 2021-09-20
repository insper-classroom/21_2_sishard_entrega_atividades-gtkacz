// Dump of assembler code for function ex1:
//    0x0000000000000000 <+0>:     lea    (%rdi,%rsi,1),%rax
//    0x0000000000000004 <+4>:     lea    (%rax,%rdx,4),%rcx
//    0x0000000000000008 <+8>:     imul   %rdi,%rdi
//    0x000000000000000c <+12>:    lea    (%rdi,%rsi,2),%rax
//    0x0000000000000010 <+16>:    add    %rax,%rdx
//    0x0000000000000013 <+19>:    cmp    %rdx,%rcx
//    0x0000000000000016 <+22>:    setge  %al
//    0x0000000000000019 <+25>:    movzbl %al,%eax
//    0x000000000000001c <+28>:    retq
// End of assembler dump.

//rdi = long a;
//rsi = long b;
//rdx = long c;
//rcx = long d;
//rax = long r;
//eax = int f;

int solucao_ex1(long a, long b, long c){
    long r, d;
    int f;

    r = a + b;
    d = r + c * 4;
    a *= a;
    r = a + b * 2;
    c += r;
    f = d >= c;

    return f;
}