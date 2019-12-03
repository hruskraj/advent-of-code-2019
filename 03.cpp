#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <climits>

using namespace std;

vector<string> split(const string & s, char delim = ','){
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while(getline(tokenStream, token, delim))
        tokens.push_back(token);
    return tokens;
}

void getVector(const string & s, int & deltaX, int & deltaY){
    stringstream ss(s);
    char c;
    int a;
    ss >> c >> a;
    if(c == 'U' || c == 'D'){
        deltaX = 0;
        deltaY = a * ((c == 'U') ? 1 : -1);
    }
    else{
        deltaY = 0;
        deltaX = a * ((c == 'R') ? 1 : -1);
    }
}

int manhattanDistance(int ax, int ay, int bx = 0, int by = 0){
    return abs(ax - bx) + abs(ay - by);
}

bool isBetween(int x, int a, int b){
    if(b < a)
        swap(a, b);
    return (x >= a) && (x <= b);
}

bool intersects(int ax, int ay, int bx, int by,
                int cx, int cy, int dx, int dy,
                int & px, int & py){
    if(isBetween(cx, ax, bx) && isBetween(dx, ax, bx) && isBetween(ay, cy, dy) && isBetween(by, cy, dy)){
        px = cx;
        py = ay;
        return true;
    }
    if(isBetween(ax, cx, dx) && isBetween(bx, cx, dx) && isBetween(cy, ay, by) && isBetween(dy, ay, by)){
        px = ax;
        py = cy;
        return true;
    }
    return false;
}

int closestFunc(int p_x, int p_y, int i_steps, int j_steps, int i_x, int i_y, int j_x, int j_y){
    return manhattanDistance(p_x, p_y);
}

int lowestNumOfStepsFunc(int p_x, int p_y, int i_steps, int j_steps, int i_x, int i_y, int j_x, int j_y){
    return i_steps + j_steps + manhattanDistance(p_x, p_y, i_x, i_y) + manhattanDistance(p_x, p_y, j_x, j_y);
}

int findOpt(const string & w1, const string & w2, int(*func)(int, int, int, int, int, int, int, int)){
    vector<string> paths1 = split(w1);
    vector<string> paths2 = split(w2);
    int opt = INT_MAX;
    int p_x, p_y;

    int i_x = 0, i_y = 0;
    int i_steps = 0;
    for(string & i : paths1){
        int deltaX, deltaY;
        getVector(i, deltaX, deltaY);
        int j_x = 0, j_y = 0;
        int j_steps = 0;
        for(string & j : paths2){
            int d_x, d_y;
            getVector(j, d_x, d_y);
            if(intersects(i_x, i_y, i_x + deltaX, i_y + deltaY, j_x, j_y, j_x + d_x, j_y + d_y, p_x, p_y) && (p_x != 0 || p_y != 0))
                opt = min(func(p_x, p_y, i_steps, j_steps, i_x, i_y, j_x, j_y), opt);
            j_x += d_x; j_y += d_y;
            j_steps += abs(d_x + d_y);
        }
        i_x += deltaX; i_y += deltaY;
        i_steps += abs(deltaX + deltaY);
    }
    return opt;
}

int main(){
    string w1, w2;
    getline(cin, w1);
    getline(cin, w2);
    printf("%d\n", findOpt(w1, w2, closestFunc));
    printf("%d\n", findOpt(w1, w2, lowestNumOfStepsFunc));
    return 0;
}
