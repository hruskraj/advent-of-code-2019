#include <cstdio>

using namespace std;

const int MEM_SIZE = 1000;
int input[MEM_SIZE], mem[MEM_SIZE];

void resetMemory(){
    for(int i = 0; i < MEM_SIZE; ++i)
        mem[i] = input[i];
}

int program(int noun, int verb){
    int pc = 0;
    resetMemory();
    mem[1] = noun;
    mem[2] = verb;
    while(mem[pc] != 99){
        if(mem[pc] == 1)
            mem[mem[pc + 3]] = mem[mem[pc + 1]] + mem[mem[pc + 2]];
        else
            mem[mem[pc + 3]] = mem[mem[pc + 1]] * mem[mem[pc + 2]];
        pc += 4;
    }
    return mem[0];
}

int findParameters(int res){
    for(int i = 0; i < 100; ++i){
        for(int j = 0; j < 100; ++j){
            if(program(i, j) == res)
                return 100 * i + j;
        }
    }
    return -1;
}

int main(){
    int a, prSize = 0;
    while(scanf("%d,", &a) == 1)
        input[prSize++] = a;
    printf("%d\n", program(12, 2));
    printf("%d\n", findParameters(19690720));
    return 0;
}
