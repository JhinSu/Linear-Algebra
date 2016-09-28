A = rdcoord('EC2_A1.txt');
[P, L, U, sign] = splu(A);
b = rdcoordb('EC2_b1.txt');
x = splv(A, b);