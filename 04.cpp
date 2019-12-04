#include <cstdio>

using namespace std;

bool hasDouble(int a){
    int lastDigit = a % 10;
    a /= 10;
    while(a != 0){
        if(a % 10 == lastDigit)
            return true;
        lastDigit = a % 10;
        a /= 10;
    }
    return false;
}

bool hasPreciseDouble(int a){
    int lastDigit = a % 10;
    int count = 1;
    a /= 10;
    while(a != 0){
        if(a % 10 == lastDigit)
            ++count;
        else{
            if(count == 2)
                return true;
            count = 1;
        }
        lastDigit = a % 10;
        a /= 10;
    }
    return count == 2;
}

bool isIncreasing(int a){
    int lastDigit = a % 10;
    a /= 10;
    while(a != 0){
        if(a % 10 > lastDigit)
            return false;
        lastDigit = a % 10;
        a /= 10;
    }
    return true;
}

int solve(int from, int to, bool firstPart = true){
    int count = 0;
    for(int i = from; i <= to; ++i){
        if(isIncreasing(i) && (firstPart ? hasDouble(i) : hasPreciseDouble(i)))
            ++count;
    }
    return count;
}

int main(){
    printf("%d\n", solve(197487, 673251));
    printf("%d\n", solve(197487, 673251, false));
    return 0;
}
