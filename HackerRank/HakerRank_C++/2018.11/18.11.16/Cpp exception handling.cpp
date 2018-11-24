#include <iostream>
#include <stdexcept>

using namespace std;

int largest_proper_divisor(int n) {
    if (n == 0) {
        throw invalid_argument("largest proper divisor is not defined for n=0");
    }
    if (n == 1) {
        throw invalid_argument("largest proper divisor is not defined for n=1");
    }
    for (int i = n/2; i >= 1; --i) {
        if (n % i == 0) {
            return i;
        }
    }
    return -1; // will never happen
}

void process_input(int n) {
    bool check=true;
    try
    {
        int d = largest_proper_divisor(n);
    }
    catch (const std::exception& error)
    {
        cout<<error.what()<<endl;
        check=false;
    }
    if(check)cout << "result=" << largest_proper_divisor(n) << endl;
    cout<<"returning control flow to caller"<<endl;
}

int main() {
    int n;
    cout<<"Num";
    cin >> n;
    process_input(n);
    return 0;
}
