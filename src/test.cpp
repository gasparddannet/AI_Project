#include "Solution.h"
#include <vector>
#include <iostream>
using namespace std;


int main() {
    vector<int> solvec = {4,5,7,4,2,6,4,1} ;
    Solution sol = Solution(solvec);
    sol.blockReverse(2,5) ;
    for (int i=0;i<solvec.size();i++) {
        cout << sol.getSolution()[i] ;
    }
}