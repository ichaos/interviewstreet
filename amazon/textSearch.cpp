/*
 Given a paragraph of text, write a program to find the first shortest sub-segment that contains each of the given k words at least once. A segment is said to be shorter than other if it contains less number of words.

Ignore characters other than [a-z][A-Z] in the text. Comparison between the strings should be case-insensitive. 

If no sub-segment is found then the program should output “NO SUBSEGMENT FOUND”.

 
Input format :
 
First line of the input contains the text.
Next line contains k , the number of  words given to be searched.
Each of the next k lines contains a word.
 
 
Output format :
 
Print first shortest sub-segment that contains given k words , ignore special characters, numbers.If no sub-segment is found it should return “NO SUBSEGMENT FOUND”
 
Sample Input :
 
This is a test. This is a programming test. This is a programming test in any language.
4
this
a
test
programming
 
Sample Output :
 
a programming test This
 
Explanation :
In this test case segment "a programming test. This" contains given four words. You have to print without special characters, numbers so output is "a programming test This".  Another segment "This is a programming test." also contains given  four words but have more number of words. 
 
Constraint :

Total number of character in a paragraph will not be more than 200,000.
0 < k <= no. of words in paragraph.
0 < Each word length < 15
 */

/* Enter your code here. Read input from STDIN. Print output to STDOUT */

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <climits>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

void formatString(string &s) {
    //transform( s.begin(), s.end(), s.begin(), ::tolower );
    for (int i = 0; i < s.size(); i++) {
        if ((s[i] <= 'z' && s[i] >= 'a') || (s[i] <= 'Z' && s[i] >= 'A')) {
            ;
        } else {
            s.erase(i, 1);
            i--;
        }
    }
}

int main() {
    vector<string> paragraph;
    vector<string> original;
    string firstLine;
    string s;
    getline(cin, firstLine);
    stringstream ss(firstLine);
    while (ss >> s) {
        //remove '.'
        formatString(s);
        if (find(s.begin(), s.end(), '.') != s.end())
            s.erase(find(s.begin(), s.end(), '.'));
        original.push_back(s);
        transform( s.begin(), s.end(), s.begin(), ::tolower );
        //cout << s << "-";
        paragraph.push_back(s);
    }    
    //cout << endl;
    
    int k = 0;
    cin >> k;
    set<string> target;
    map<string, int> current;
    for (int i = 0; i < k; i++) {
        cin >> s;
        transform( s.begin(), s.end(), s.begin(), ::tolower );
        target.insert(s);
    }
    cout << endl;
    
    int count = 0;
    int start = 0;
    int length = INT_MAX;
    int mi = 0;
    for (int i = 0; i < paragraph.size(); i++) {
        if (target.find(paragraph[i]) == target.end()) continue;
        else {
            current[paragraph[i]]++;
            if (current[paragraph[i]] == 1) {
                count++;
                if (count == 1) {
                    start = i;
                }
                if (count == k) { //find one
                    if (i - start + 1 < length) {                        
                        length = i - start + 1;
                        mi = start;
                    }
                        
                    //move the window for next
                    //start = i + 1;
                    for (int j = start; j <= i; j++) {
                        if (target.find(paragraph[j]) != target.end()) {                            
                            if (current[paragraph[j]] == 1) {
                                if (count == k - 1) {
                                    start = j;
                                    break;
                                }                                 
                                count--;
                            }
                            current[paragraph[j]]--;                            
                        }
                    }
                }
            }
        }
    }
    if (length == INT_MAX) { //can't find
        cout << "NO SUBSEGMENT FOUND" << endl;
    } else {
        for (int i = mi; i < mi + length; i++) {
            cout << original[i];
            if (i < mi + length - 1)
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}