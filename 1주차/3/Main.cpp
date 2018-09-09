#include <iostream>
#include <string>

using namespace std;

int main() {
	string st, s, b;
    int t, a, temp;
    int bucket[10] = {0,};

    cin >> st;
    t = stoi(st);
    for(int i = 0; i < t; i++){
        cin >> s;
        b = "";
        for(int j = 0; j < s.length(); j++){
            bucket[stoi(s.substr(j,1))]++;
        }
        for(int j = 0; j < 10; j++){
            if (bucket[j]){
                a = j;
                bucket[j]--;
                break;
            }
        }
        for(int j = 9; j >= 0; j--){
            while(bucket[j]){
                b.append(to_string(j));
                bucket[j]--;
            }
        }
        for(int j = b.length() - 1; j >= 0; j--){
            temp = stoi(b.substr(j,1));
            b.replace(j, 1, to_string((temp + a) % 10));
            
            if(j == 0 && temp + a >= 10){
                b.insert(0, "1");
            }

            if (temp + a < 10)
                break;
            
            a = 1;
        }
        cout << b << endl;
    }
}
