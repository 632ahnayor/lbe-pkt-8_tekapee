#include <iostream>
#include <vector>
using namespace std;

int main() {
    //NWC

    vector<vector<int>> grid = {{3, 1, 7, 4}, {3, 7, 6, 10}, {8, 3, 3, 2}}; // table
    vector<int> supply = {300, 400, 500}; // supply
    vector<int> demand = {250, 350, 400, 200}; // demand

    int startR = 0; // start row
    int startC = 0; // start col
    int ans = 0;
    // loop runs until it reaches the bottom right corner
    while (startR != grid.size() && startC != grid[0].size()) {
        // if demand is greater than supply
        if (supply[startR] <= demand[startC]) {
            ans += supply[startR] * grid[startR][startC];
            // subtract the value of supply from the demand
            demand[startC] -= supply[startR];
            startR += 1;
        }
        // if supply is greater than demand
        else {
            ans += demand[startC] * grid[startR][startC];
            // subtract the value of demand from the supply
            supply[startR] -= demand[startC];
            startC += 1;
        }
    }

    cout << "The initial feasible basic solution is " << ans << endl;

    return 0;
}
