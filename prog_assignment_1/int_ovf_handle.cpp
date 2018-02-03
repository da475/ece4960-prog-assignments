#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>

using namespace std;

#define MAX_INT 0x7FFFFFFF

// 2147483647

class excep {

    public:
        int in1;
        int in2;
        int int_mul();
        int factorial(int);
        int check_int_limit(long);

};

int excep::int_mul() {
    long mul = (long)in1 * (long)in2;
    //cout << "mul in func is " << mul << endl;
    return check_int_limit(mul);
}

int excep::factorial (int n)
{
    if (n == 1 || n ==0)
        return 1;

    return n * factorial(n-1);
}

int excep::check_int_limit (long n)
{
    if(n > 2147483647) {
        cout << "Found overflow" << endl;
        return MAX_INT;
    }
    else {
        return (int)n;
    }
}


int main()
{

    excep obj1;

    string input1 = "12";
    string input2 = "34";

    cout << "Enter the 1st number" << endl;
    cin >> input1;

    cout << "Enter the 2nd number" << endl;
    cin >> input2;

    cout << "Entered numbers are " << input1 << " and " << input2 <<  endl;

    if (input1.size() > 10 || input2.size() > 10) {
        cout << "Number more than integer limit, returning!" << endl;
        return 0;
    }

    long long_in1 = stol(input1);
    long long_in2 = stol(input2);

    obj1.in1 = obj1.check_int_limit(long_in1);
    obj1.in2 = obj1.check_int_limit(long_in2);

    int mul = obj1.int_mul();
    cout << "mul is " << mul << endl;

//    cout << "test " << obj1.check_int_limit(3000000000);

    return 0;

}

