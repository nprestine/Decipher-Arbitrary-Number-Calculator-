#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main() {
    //Add your own code
    //You may comment out the example code snippets below
  
    //First example
    /*BigInt mytest("DADCAFE", 16);
    cout<<mytest.to_string()<<endl;//should print DADCAFE
    BigInt mytest2("1010",2);
    cout<<mytest2.to_string()<<endl;//should print 1010
    BigInt mytest3("1010",2);
    cout<<mytest3.to_int()<<endl;//should print 10
    */
    //Second example
    /*BigInt first("DADCAFE", 16);
    BigInt second("BEEF", 16);
    BigInt sum = first + second;
    first += second;
    cout<<boolalpha<<(first >= second)<<endl;//should print true
    cout<<sum.to_string()<<endl;//should print DAE89ED
    cout<<first.to_string()<<endl;//should print DAE89ED
    */
    //Third example
    BigInt var1(1,10);
    BigInt var2(0,10);
    int compare =0;
    compare =var1.compare(var2);
    cout << compare;
    /*cout<<var4.to_int()<<endl;//should print 72
    cout<<(char)var4.to_int()<<endl;//should print "H"
    */
    
	return 0;
}
