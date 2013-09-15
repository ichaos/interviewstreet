/*
	Given a 2–d matrix , which has only 1’s and 0’s in it. Find the total number of connected sets in that matrix.
 
 
Explanation:
Connected set can be defined as group of cell(s) which has 1 mentioned on it and have at least one other cell in that set with which they share the neighbor relationship. A cell with 1 in it and no surrounding neighbor having 1 in it can be considered as a set with one cell in it. Neighbors can be defined as all the cells adjacent to the given cell in 8 possible directions ( i.e N , W , E , S , NE , NW , SE , SW direction ). A cell is not a neighbor of itself.
 
 
Input format :
 
First line of the input contains T , number of test-cases.
Then follow T testcases. Each testcase has given format.
N [ representing the dimension of the matrix N X N ].
Followed by N lines , with N numbers on each line.
 
 
 
Ouput format :
 
For each test case print one line ,  number of connected component it has.
 
Sample Input :
 
4
4
0 0 1 0
1 0 1 0
0 1 0 0
1 1 1 1
4
1 0 0 1
0 0 0 0
0 1 1 0
1 0 0 1
5
1 0 0 1 1
0 0 1 0 0
0 0 0 0 0
1 1 1 1 1
0 0 0 0 0
8
0 0 1 0 0 1 0 0
1 0 0 0 0 0 0 1
0 0 1 0 0 1 0 1
0 1 0 0 0 1 0 0
1 0 0 0 0 0 0 0
0 0 1 1 0 1 1 0
1 0 1 1 0 1 1 0
0 0 0 0 0 0 0 0
 
Sample output :
 
1
3
3
9
 
Constraint :
 
0 < T < 6 
0 < N < 1009 

 */

/* Enter your code here. Read input from STDIN. Print output to STDOUT */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int countConnectedSet(vector<vector<int> > &matrix) {
    int set = 0;
    queue<int> q;
    int n = matrix.size();
    vector<vector<bool> > visited(n, vector<bool>(n, false));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (visited[i][j] || matrix[i][j] == 0) continue;
            set++;
            q.push((i << 16) | j);
            visited[i][j] = true;
            while (!q.empty()) {
                //find all neighbors
                int p = q.front();
                q.pop();
                int x = p >> 16;
                int y = p & 0xffff;
                //left top
                if (x > 0 && y > 0 && matrix[x - 1][y - 1] && !visited[x - 1][y - 1]) {
                    visited[x - 1][y - 1] = true;
                    q.push(((x - 1) << 16) | (y - 1));
                }
                //middle top
                if (x > 0 && matrix[x - 1][y] && !visited[x - 1][y]) {
                    visited[x - 1][y] = true;
                    q.push(((x - 1) << 16) | (y));
                }
                //right top
                if (x < n - 1 && y < n - 1 && matrix[x + 1][y + 1] && !visited[x + 1][y + 1]) {
                    visited[x + 1][y + 1] = true;
                    q.push(((x + 1) << 16) | (y + 1));
                }
                //left
                if (y > 0 && matrix[x][y - 1] && !visited[x][y - 1]) {
                    visited[x][y - 1] = true;
                    q.push((x << 16) | (y - 1));
                }
                //right
                if (y < n - 1 && matrix[x][y + 1] && !visited[x][y + 1]) {
                    visited[x][y + 1] = true;
                    q.push(((x) << 16) | (y + 1));
                }
                //left bottom
                if (x < n - 1 && y > 0 && matrix[x + 1][y - 1] && !visited[x + 1][y - 1]) {
                    visited[x + 1][y - 1] = true;
                    q.push(((x + 1) << 16) | (y - 1));
                }
                
                //middle bottom
                if (x < n - 1 && matrix[x + 1][y] && !visited[x + 1][y]) {
                    visited[x + 1][y] = true;
                    q.push(((x + 1) << 16) | (y));
                }
                
                //right bottom
                if (x < n - 1 && y < n - 1 && matrix[x + 1][y + 1] && !visited[x + 1][y + 1]) {
                    visited[x + 1][y + 1] = true;
                    q.push(((x + 1) << 16) | (y + 1));
                }
            }
        }
    }
    return set;
}

int main() {
    int t = 0;
    cin >> t;
    
    int n = 0;
    int cell = 0;
    for (int i = 0; i < t; i++) {
        cin >> n;
        
        vector<vector<int> > matrix(n);
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                cin >> cell;
                matrix[j].push_back(cell);
            }
        }
        
        //count connected set
        cout << countConnectedSet(matrix) << endl;
    }
}