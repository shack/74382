#include <stdio.h>

unsigned ovr(unsigned a, unsigned b, unsigned f, unsigned bit) {
    unsigned aa = (a >> bit) & 1;
    unsigned bb = (b >> bit) & 1;
    unsigned ff = (f >> bit) & 1;

    return (!aa && !bb && ff) | (aa && bb && !ff);
}

unsigned func(unsigned s, unsigned a, unsigned b, unsigned c) {
    s &= 7;
    a &= 15;
    b &= 15;
    c &= 1;

    int f;
    int ov = 0;
    int co = 0;

    switch (s) {
    case 0:
        f = ov = co = 0;
        break;
    case 1:
        f = b + (~a & 15) + c;
        ov = ovr(b, ~a, f, 3);
        break;
    case 2:
        f = a + (~b & 15) + c;
        ov = ovr(a, ~b, f, 3);
        break;
    case 3:
        f = a + b + c;
        ov = ovr(a, b, f, 3);
        break;
    case 4:
        f = a ^ b;
        co = ov = (f == 15 ? c : 0);
        break;
    case 5:
        f = a | b;
        co = ov = (f == 15 ? c : 0);
        break;
    case 6:
        f = a & b;
        co = ov = (f == 15 ? c : 0);
        break;
    case 7:
        f = 15;
        co = ov = c;
        break;
    }

    return f | (co << 4) | (ov << 5);
}

int main(int argc, char** argv) {
    for (int s = 0; s < 8; s++) {
        for (int a = 0; a < 16; a++) {
            for (int b = 0; b < 16; b++) {
                for (int c = 0; c < 2; c++) {
                    int f = func(s, a, b, c);
                    printf("%d %d %d %d %d\n", s, a, b, c, f);
                }
            }
        }
    }

}