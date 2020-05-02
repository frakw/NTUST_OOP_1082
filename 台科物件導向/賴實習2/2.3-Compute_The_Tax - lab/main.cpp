#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    double income;
    while (cin >> income) {
        double tax;
        if (income < 750) {
            tax = income * 0.01;
        }
        else if (income < 2250) {
            tax = (income - 750) * 0.02 + 7.50;
        }
        else if (income < 3750) {
            tax = (income - 2250) * 0.03 + 37.50;
        }
        else if (income < 5250) {
            tax = (income - 3750) * 0.04 + 82.50;
        }
        else if (income < 7000) {
            tax = (income - 5250) * 0.05 + 142.50;
        }
        else {
            tax = (income - 7000) * 0.06 + 230.00;
        }
        printf("%.2f\n", tax);
    }
    return 0;
}

/*  Not over $750   l% of income

  $750¡X$2,250    $7.50 plus 2% of amount over $750

  $2,250¡X$3,750  $37.50 plus 3% of amount over $2,250

  $3,750-$5,250   $82.50 plus 4% of amount over $3,750

  $5,250¡X$7,000  $142.50 plus 5% of amount over $5,250

  Over $7,000     $230.00 plus 6% of amount over $7,000
*/