#include <iostream>
#include <fstream> // read file
#include <vector>
#include <filesystem> //read directory
using namespace std;

int main() {
    //NWM

    // cek semua file dalam folder "input"
    for(const auto& entry : filesystem::directory_iterator("input")) {
        // pilih file dengan .txt
        if(entry.path().extension()==".txt") {
            // file processing
            ifstream infile(entry.path());
            if(!infile) {
                cerr << "error open file" << endl;
                continue;
            }
            
            int rows, cols;
            infile >> rows >> cols;
            
            vector<vector<int>> grid(rows, vector<int>(cols));
            for(int i=0; i<rows; i++) {
                for(int j=0; j<cols; j++) {
                    infile >> grid[i][j];
                }
            }
            
            vector<int> supply(rows);
            for(int i=0; i<rows; i++) {
                infile >> supply[i];
            }
            
            vector<int> demand(cols);
            for(int j=0; j<cols; j++) {
                infile >> demand[j];
            }
            
            int optimal;
            infile >> optimal;
            
            infile.close(); // close file
            
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
            
            cout << "Optimal solution is " << optimal << endl;
            cout << "The initial feasible basic solution is " << ans << endl;
            cout << "Difference " << ans-optimal << endl;
            cout << "Accuracy " << (double(ans)-double(optimal))/double(optimal) << endl << endl;
            
        }
    }

    return 0;
}
