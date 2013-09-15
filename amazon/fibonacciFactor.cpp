/*
    Given a number K, find the smallest Fibonacci number that shares a common factor( other than 1 ) with it. A number is said to be a common factor of two numbers if it exactly divides both of them. 
 
Output two separate numbers, F and D, where F is the smallest fibonacci number and D is the smallest number other than 1 which divides K and F.
 
Input Format 
 
First line of the input contains an integer T, the number of testcases.
Then follows T lines, each containing an integer K.
 
Output Format
 
Output T lines, each containing the required answer for each corresponding testcase.
 
 

 

Sample Input 
 
3
3
5
161
 
Sample Output
 
3 3
5 5
21 7
 
Explanation
 
There are three testcases. The first test case is 3, the smallest required fibonacci number  3. The second testcase is 5 and the third is 161. For 161 the smallest fibonacci numer sharing a common divisor with it is 21 and the smallest number other than 1 dividing 161 and 7 is 7.
 
Constraints :
 
1 <= T <= 5
2 <= K <= 1000,000
The required fibonacci number is guranteed to be less than 10^18.
 */

/* Enter your code here. Read input from STDIN. Print output to STDOUT */

//there're less 100 fibonacci numbers less than 10^18
#include <iostream>
#include <vector>

using namespace std;

void findFibonaccis(vector<long long> &fibonacci, long long bound) {
    long long a = 2;
    long long b = 3;
    fibonacci.push_back(2);
    //fibonacci.push_back(3);
    long long tmp = 0;
    while (b < bound) {
        fibonacci.push_back(b);
        tmp = b;
        b = a + b;
        a = tmp;
    }

    //cout << "fibonacci.size() = " << fibonacci.size() << endl;
}

void findPrimes(vector<int> &primes, int limits) {
    primes.push_back(2);
    int p = 3;
    bool found = true;
    while (p < limits) {
        found = true;
        for (int i = 0; i < primes.size(); i++) {
            if ((p % primes[i]) == 0) {
                found = false;
                break;
            }
        }
        if (found) {
            primes.push_back(p);
        }
        p += 2;
    }
    //cout << "Primes.size() = " << primes.size() << endl;
}

void parseFactors(vector<int> &primes, int k, vector<int> &factor) {
    int j = 0;
    while (k > 1 && k >= primes[j]) {
        if (k % primes[j]) {
            j++;
        } else {
            k = k / primes[j];
            if (factor.size() == 0 || factor[factor.size() - 1] != primes[j])
                factor.push_back(primes[j]);
        }
    }
}

void parseFactorsII(int k, vector<int> &factor) {
    bool even = false;
    while (k % 2 == 0) {
        k /= 2;
        even = true;
    }
    if (even) {
        factor.push_back(2);
    }
    int p = 3;
    while (k > 1) {
        if (k % p == 0) {
            k /= p;
            if (factor.size() == 0 || factor[factor.size() - 1] != p)
                factor.push_back(p);
        } else {
            p += 2;
        }
    }
}
    
int main() {
    vector<long long> fibonacci;
    long long upBound = 1000000000000000000L;
    findFibonaccis(fibonacci, upBound);
    int limits = 1000000;
    vector<int> primes;
    //findPrimes(primes, limits);
    int t = 0;
    cin >> t;
    int k = 0;
    vector<int> factor;
    for (int i = 0; i < t; i++) {
        cin >> k;
        
        factor.clear();
        //parseFactors(primes, k, factor);
        parseFactorsII(k, factor);
        //find smallest fibonacci number
        for (int i = 0; i < fibonacci.size(); i++) {
            for (int j = 0; j < factor.size(); j++) {
                if ((fibonacci[i] % factor[j]) == 0) { //find F and D
                    cout << fibonacci[i] << " " << factor[j] << endl;
                    i = fibonacci.size();
                    j = factor.size();
                }
            }
        }
    }
}