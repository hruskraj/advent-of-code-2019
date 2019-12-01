#include <cstdio>
#include <algorithm>

using namespace std;

int calculateFuel(int mass){
    return max(mass / 3 - 2, 0);
}

int main(){
    int a, out1 = 0, out2 = 0;
    while(scanf("%d", &a) == 1){
        out1 += calculateFuel(a);
        while((a = calculateFuel(a)) != 0){
            out2 += a;
        }
    }
    printf("%d\n", out1);
    printf("%d\n", out2);
    return 0;
}
