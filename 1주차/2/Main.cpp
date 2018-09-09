#include <iostream>
#include <string>

using namespace std;

int main() {
	string a, answer;
    size_t month, day;
    cin >> a;
    month = stoi(a.substr(0,2));
    day = stoi(a.substr(3,2));

    switch(month){
        case 8:
            answer = day == 31 ? "YES" : "NO";
            break;
        case 9:
            answer = (day == 7 || day == 14 || day == 28) ? "YES" : "NO";
            break;
        case 10:
            answer = (day == 5 || day == 12 || day == 26) ? "YES" : "NO";
            break;
        case 11:
            answer = (day == 9 || day == 16 || day == 23 || day == 30) ? "YES" : "NO";
            break;
        default:
            answer = "NO";
    }
    cout << answer << endl;
}
