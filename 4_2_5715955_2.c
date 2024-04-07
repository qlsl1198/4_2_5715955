#include <stdio.h>
#include <stdlib.h> // exit 함수를 사용하기 위해 추가

#define MAX_TERMS 101

struct {
    float coef;
    int expon;
} terms[MAX_TERMS] = { {7.0, 6}, { 5.0, 3 }, {9.0, 2}, {1.0, 0},
                      {5.0, 3}, {2.0, 2}, {1.0, 1}, {10.0,0} };
int avail = 8;

void print_poly(int s, int e);
void poly_multiply(int As, int Ae, int Bs, int Be, int* Csp, int* Cep);

int main() {
    int Cs = 0, Ce = 0; // Cs와 Ce 변수를 초기화
    printf("A = ");
    print_poly(0, 3);
    printf("B = ");
    print_poly(4, 7);

    printf("-----------------------------------------\n"); // 다항식과 결과 값 구분선

    // 다항식의 곱셈 수행
    poly_multiply(0, 3, 4, 7, &Cs, &Ce);
    printf("A * B = ");
    print_poly(Cs, Ce);

    return 0;
}

void attach(float coef, int expon) {
    if (avail >= MAX_TERMS) { // avail이 MAX_TERMS와 같을 경우에도 오류 처리하도록 수정
        fprintf(stderr, "Too long terms");
        exit(1);
    }
    terms[avail].coef = coef;
    terms[avail].expon = expon;
    avail++; // avail 변수를 증가시켜야 다음에 추가될 항의 위치가 올바르게 지정됨
}

void poly_multiply(int As, int Ae, int Bs, int Be, int* Csp, int* Cep) {
    int c_start = avail;
    for (int i = As; i <= Ae; i++) {
        for (int j = Bs; j <= Be; j++) {
            attach(terms[i].coef * terms[j].coef, terms[i].expon + terms[j].expon);
        }
    }
    *Csp = c_start;
    *Cep = avail - 1;
}

void print_poly(int s, int e) {
    int i;
    for (i = s; i < e; i++) {
        printf("%3.1fx^%d + ", terms[i].coef, terms[i].expon);
    }
    printf("%3.1fx^%d\n", terms[i].coef, terms[i].expon);
}
