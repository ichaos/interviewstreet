/*
 * Question 1 / 1 (N King)
You have an N x N chessboard and you wish to place N kings on it. Each row and column should contain exactly one king, and no two kings should attack each other (two kings attack each other if they are present in squares which share a corner).

The kings in the first K rows of the board have already been placed. You are given the positions of these kings as an array pos[ ]. pos[i] is the column in which the king in the ith row has already been placed. All indices are 0-indexed. In how many ways can the remaining kings be placed?

Input:
The first line contains the number of test cases T. T test cases follow. Each test case contains N and K on the first line, followed by a line having K integers, denoting the array pos[ ] as described above.

Output:
Output the number of ways to place kings in the remaining rows satisfying the above conditions. Output all numbers modulo 1000000007.

Constraints:
1 <= T <= 20
1 <= N <= 16
0 <= K <= N
0 <= pos_i < N
The kings specified in the input will be in different columns and not attack each other.

Sample Input:
5
4 1
2
3 0

5 2
1 3
4 4
1 3 0 2
6 1
2

Sample Output:
1
0
2
1
18

Explanation:
For the first example, there is a king already placed at row 0 and column 2. The king in the second row must belong to column 0. The king in the third row must belong to column 3, and the last king must beong to column 1. Thus there is only 1 valid placement.

For the second example, there is no valid placement.
 */

/* Enter your code here. Read input from STDIN. Print output to STDOUT */

#include <iostream>
//#include <unordered_map>

using namespace std;

unsigned long long count(int bitmap, int pos, int n, int k, unsigned long long *cache) {
    if (k > n) return 0;
    unsigned long long c = 0;
    //printf("0x%x: %d\n", bitmap, (int)c);
    for (int i = 0; i < n; i++) {
        if ((bitmap & (1 << i)) == 0 && i != (pos + 1) && i != (pos - 1)) {
            if (k == n) {
            	//printf("0x%x: %d\n", bitmap, (int)c);
                c++;   
                //continue;           
            } else {
            	//can we find the result in cache?
	            int key = bitmap | (i << 16);
    	        key |= (1 << i);
        	    if (cache[key] != 0) c += cache[key];
            	else c += count(bitmap | (1 << i), i, n, k + 1, cache);
            }            
        }
    }
    //cout << k << ":" << n << "," << c << endl;
    //if (c > 1000000007) c -= 1000000007;
    cache[bitmap | (pos << 16)] = c;

    return c;
}

void clearCache(unsigned long long *cache, int size)
{
	for (int i = 0; i < size; i++) {
		cache[i] = 0;
	}
}

unsigned long long *cache = new unsigned long long[1 << 21];

int main() {
    int t = 0;
    cin >> t;
    int n = 0, k = 0;
    int legal = 0;
    int bitmap = 0;
    int pos = 0;
    
    for (int i = 0; i < t; i++) {
        cin >> n >> k;
       	//cout << n << " + " << k << endl;        
        bitmap = 0;
        pos = -2;
        for (int j = 0; j < k; j++) {
            cin >> pos;
            bitmap |= (1 << pos); 
        }
        if (n == 3 || n == 2) {
            cout << "0\n";
            continue;
        }
        if (n == k) {
            cout << "1" << endl;
            continue;
        }
        //count remaining map
        //cache.clear();
        clearCache(cache, 1 << 21);
        cout << count(bitmap, pos, n, k + 1, cache) % 1000000007 << endl;
    }
}

