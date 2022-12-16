#include <iostream>
#include "game.h"

using namespace std;

int main(int argc, char *argv[]) {
    AdventureGame ag;
    cout << "Welcome to Adventure Game" << endl;
    return ag.start();
}
