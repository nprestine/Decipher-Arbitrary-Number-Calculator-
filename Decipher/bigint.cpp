#include "bigint.h"
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
using namespace std;

BigInt::BigInt(){ //default constructor 
  base = 10;
  isPositive = true;
}

BigInt::BigInt(int setbase){ //constructor for base
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
}

BigInt::~BigInt(){} //deconstructor

BigInt::BigInt(const string &s, int setbase){ //constructor for string input and base set
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    isPositive =true;
    base = setbase;
    int negative = 0;
    if(s[0] == '-'){
        isPositive=false;
        negative=1;
    } 
    for(int i = (s.length()-1); i>=negative; i--){ //read string and wirte
        if(s[i] >= 65 && s[i] <= 90){
            vec.push_back(s[i] - 55);
        }
        else if (s[i]>= 48 && s[i] <= 57){
            vec.push_back(s[i]-48);
        }
    }
}

BigInt::BigInt(int input,int setbase){ //constructor for input value and intput base
    if(setbase < 2 || setbase > 36){
        throw InvalidBaseException();
    }
    base = setbase;
    isPositive = true;
    if(input < 0){
        isPositive=false;
        input *= -1;
    }
    if(input == 0){
        vec.push_back(0);
    }
    while(input!=0){
        vec.push_back(input%setbase);
        input /= setbase;
    }
}

BigInt::BigInt(const BigInt &b){ //constructor from BigInt input
    base = b.base;
    isPositive=b.isPositive;
    vec=b.vec;
}

BigInt & BigInt::operator = (const BigInt &b){ //operator overload for equals
    base = b.base;
    isPositive= b.isPositive;
    vector<int> temp(b.vec.size());
    vec.clear();  //clear previous values
    while(vec.size()<b.vec.size()){
        vec.push_back(0);
    }
    for (unsigned int i=0; i<b.vec.size(); i++){ //read and create vector for RHS object
        
            vec[i] = b.vec[i];
    } 
    return *this; 

}

string BigInt::to_string(){  //create string from BigInt
    int caseIndicator =0;
    if (vec.size()==false) {
        caseIndicator = 1;
    }
    string characterout = ""; 
    if (isPositive==false) {
        characterout = characterout+ "-"; 
    }       
    for (int i = vec.size() - 1; i >= 0; i--) {
        if (vec[i] <= 9 && vec[i] >= 0) {
            characterout = characterout + char(vec[i] + 48); 
        }   
        else {
            characterout = characterout + char(vec[i] + 55); 
        }
    }
    caseIndicator = 2;
    switch(caseIndicator){ //decide which return to do.
        case 1:{
            return "0";
            break;
        }
        case 2:{
            return characterout; 
            break;
        }
    }
    return characterout;
}

int BigInt::to_int() const{ //convert BigInt to int 

    long long int base10=0;
    int boundry =0;
    for(int i=0; i< (int)vec.size(); i++){
        base10 +=(vec[i]*pow(base,i));
        if(base10 >= 2147483648 && isPositive==false){
            boundry =1;
            break;
        }
        if(base10 >= INT_MAX){
            boundry =2;
            break;
        }
    }
    if(isPositive==false){
        base10 *= -1;
    }
    switch(boundry){ //Switch statement for exucution
        case 1:{
            return INT_MIN;
            break;
        }
        case 2:{
            return INT_MAX;
            break;
        }
    }
  return base10;
}

int BigInt::compare(const BigInt &b) const{ //function for comparing
    if(base != b.base){
        throw DiffBaseException();
    }
    int counter = 0;
    if(b.isPositive && isPositive){  //are they positive
        if(vec.size()>b.vec.size()){ // is a bigger than b
            counter = 1;
            return 1;
        }
        else if(vec.size()<b.vec.size()){ //is b bigger than a
            counter = 2;
            return -1;
        }
        else{
            for(int i = vec.size()-1; i>=0; i--){ //do all data members match
                if(b.vec[i] != vec[i]){ 
                    if(b.vec[i]< vec[i]){ //vec[i] is bigger than b.vec[i]
                        counter = 1;
                        return 1;;
                    }
                    else{   // a.vec[i] is smaller than b.vec[i]
                        counter =2;
                        return -1;
                    }
                }
            }

        }
        counter = 3;
    }
    if( !b.isPositive && !isPositive){
        if(b.vec.size()<vec.size()){ //is a bigger than b
            counter = 2;
            return -1;
        }
        else if(b.vec.size() > vec.size()){ //is b bigger than a
            counter = 1;
            return 1;
        }
        else{
            for(int i = vec.size()-1; i>=0; i--){
                if(b.vec[i] != vec[i]){ 
                    if(b.vec[i]< vec[i]){ //vec[i] is bigger than b.vec[i]
                        counter=1;
                        return -1;
                    }
                    else{   // ec[i] is smaller than b.vec[i]
                        counter =2;
                        return 1;
                    }
                }
            }
            counter = 3;
        }   
    }
    if(isPositive && !b.isPositive){
        counter = 1;
        return 1;
    }
    switch (counter){
        case 1: // a is bigger than b
            return 1;
            break;
        case 2: //b is bigger than a
            return -1;
            break;
        case 3: //they are equal
            return 0;
            break;
    }
    return -1;
}

bool operator == (const BigInt &a, const BigInt &b){
  return !(a.compare(b));
}

bool operator != (const BigInt &a, const BigInt &b){
  return (a.compare(b));
}

bool operator <= (const BigInt &a, const BigInt &b){
  return a.compare(b) == -1 || !a.compare(b);
  }

bool operator >= (const BigInt &a, const BigInt &b){
  return a.compare(b) == 1 || !a.compare(b);
}

bool operator > (const BigInt &a, const BigInt &b){
    return a.compare(b) == 1; 
}

bool operator < (const BigInt &a, const BigInt &b){
 return a.compare(b) == -1; 
}

BigInt operator + (const  BigInt &a, const BigInt & b){ //operator overload for + that calls +=
  BigInt copy = a;
  copy += b;
  return copy;
}

const BigInt & BigInt::operator += (const BigInt &b){  //function for += opperator
    if(base != b.base){
        throw DiffBaseException();
    }
    if (isPositive != b.isPositive){
      int counter;
        if(isPositive){
          counter = 1;
        }
    else{
        counter = 2;
    }
    switch(counter){
      case 1:{
      BigInt copy = b;
      copy.isPositive = true;
      *this -= copy;
      if(vec.size() == 1 && vec[0] == 0){
        isPositive = true;
      }
      break;
      }
      case 2:{
      isPositive = true;
      *this -=b;
      if(vec.size() == 1 && vec[0] == 0){
        isPositive = true;
      }
      else{
        isPositive = !isPositive;
      }
      break;
      }
    }
    return *this;
    }
    else{
        int carryover =0;
        unsigned long int big = max(b.vec.size(), vec.size());
        for(unsigned int z = 0; z<big; z++){
            int numerator = 0;
            int deno = 0;
            if(z<b.vec.size()){
                deno = b.vec[z];
            }
            if(z<vec.size()){
                numerator=vec[z];
            }
            int total = deno + numerator +carryover;
            carryover = total/base;
            if(z < vec.size()){
                vec[z] = total%base;
            }
            else{
                vec.push_back(total%base);
            }
        }
        if(carryover){
            vec.push_back(1);
        }
    }
    if(to_int() == 0){
        isPositive =true;
    }

  return *this;
}

BigInt operator - (const  BigInt &a, const BigInt & b){ //minus operator overload that calls -=
  BigInt copy =a;
  return copy -=b; 
}

const BigInt & BigInt::operator -= (const BigInt &b){ //function for - operator overload
    if(base != b.base){
        throw DiffBaseException();
    }
    if (isPositive != b.isPositive) {
      int switcher;
        if (isPositive) {
          switcher = 1;
        }
        else {
          switcher = 2;
        }
        switch(switcher){
          case 1:{
            BigInt copy = b; 
            copy.isPositive = true; 
            *this += copy; 
            if (vec[0] == 0 && vec.size() == 1) {
                isPositive = true; 
            }
            break;
          }
          case 2:{
            isPositive = true; 
            *this += b; 
            if (vec[0] == 0 && vec.size() == 1) {
                isPositive = true; 
            }
            else {
                isPositive = !isPositive; 
            }
            break;
          }
        }
        return *this;    
    }
    
    else {
        BigInt copy = *this; 
        unsigned int largeInt = max(vec.size(), b.vec.size()); 
        int carryover = 0; 
        for (unsigned int i = 0; i < largeInt; i++) {
            int var1 = 0; 
            int var2 = 0; 

            if ((*this < b && isPositive) || (*this >= b && !isPositive)) {
                if (i < vec.size()) {
                    var2 = vec[i]; 
                }
                if (i < b.vec.size()){
                    var1 = b.vec[i]; 
                }
            }
            else {
                if (i < vec.size()) {
                    var1 = vec[i]; 
                }
                if (i < b.vec.size()) {
                    var2 = b.vec[i]; 
                }
            }
            int sum = var1 - var2 + base + carryover; 
            carryover = sum/base - 1; 
            if (i < vec.size()) {
                vec[i] = sum % base; 
            }
            else {
                vec.push_back(sum % base); 
            }
        }
        if(copy>=b){
            isPositive=true;
        }
        else{
            isPositive=false;
        }
    }
    int i = vec.size() - 1; 
    while (vec[i] == 0 && i > 0) {
        vec.pop_back(); 
        i--; 
    }
    return *this; 
}
BigInt operator * (const  BigInt &a, const BigInt &b){ //multiplacation operator overload that calls *=
    BigInt copy = a; 
    copy *= b; 
    return copy;
}

const BigInt & BigInt::operator *= (const BigInt &b){ //mulitiplication operator overload
    if(base != b.base){
        throw DiffBaseException();
    }
    BigInt zip(0,base);
    bool endSign;
    if(isPositive != b.isPositive){
      endSign = false;
    }
    else{
      endSign = true;
    }
    if(*this == zip ){
     
      return *this;
    } else if(b == zip) {
        vec = b.vec;
        isPositive = true;
        return *this;
    }
    
    int returnValue = 0;
    BigInt yi(1,base);
    BigInt buyi(-1,base);
    BigInt ling(0,base);
    if(b.vec[0]==1 && b.vec.size()==1){
      //*this = *this;
      isPositive=endSign;
      returnValue =1;
    }
    else if(vec[0]==1 && vec.size()==1){
      vec =b.vec;
      isPositive=endSign;
      returnValue = 2;
    }
    switch(returnValue){
        case 1:{
            return *this; 
            break;  
        }
        case 2:{
            return *this;
            break;
        }
    }   
    BigInt partialsum(0,base);
    int carryover = 0;
    int productsum = 0;
    for (unsigned int z = 0; z < b.vec.size(); z++) {
        string buffer(z, '0'); 
        BigInt tmp(buffer, base); 
        for (unsigned int q = 0; q < vec.size(); q++) {
            productsum = (b.vec[z]*vec[q]) + carryover; 
            carryover = productsum / base; 
            tmp.vec.push_back(productsum%base); 
        }
        if (carryover != 0) {
            tmp.vec.push_back(carryover); 
        }
        partialsum += tmp; 
        carryover = 0; 
    }
    *this = partialsum; 
    isPositive = endSign; 
    return *this; 
}

BigInt operator / (const  BigInt &a, const BigInt & b){ //opereator overload for / that calls /=
    BigInt copy =a; 
    copy /= b; 
    return copy; 
}



const BigInt & BigInt::operator /= (const BigInt &b){ //operator ooverload for /= that calls dividemain that gets quotient
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();
    }
    BigInt q(base); 
    BigInt r(base); 
    divisionMain(b, q, r); 
    *this = q; 
    return *this; 
}

BigInt operator % (const  BigInt &a, const BigInt & b){  //% operator overload that calls %=

    /************* You complete *************/
    BigInt temp = a; 
    temp %= b; 
    return temp;
}



const BigInt & BigInt::operator %= (const BigInt &b){ //%= operator overload that calls dividemain
    if(base != b.base){
        throw DiffBaseException();
    }
    if(b.vec.size() == 1 && b.vec[0] == 0){
        throw DivByZeroException();//divide by zero.
    }
    BigInt q(base); 
    BigInt r(base); 
    divisionMain(b, r, q); 
    *this = q; 
    return *this;

}

void BigInt::divisionMain(const BigInt &b, BigInt &quotient, BigInt &remainder){ //Function for dividing 

bool endSign; 
    if (isPositive != b.isPositive) {
        endSign = false; 
    }
    else {
        endSign = true; 
    }
    //need a and b positive
    bool originalsignofA = isPositive; 
    isPositive = true;  
    BigInt Btemp = b; 
    Btemp.isPositive = true; 
    int baseCaseReturns =0;
    BigInt zip(0, base); 
    //BC
    if (vec.size() == 1 && vec[0] == 0) {
        baseCaseReturns =1; 
    }
    else if (b.vec.size() == 1 && b.vec[0] == 1) {
        baseCaseReturns =2;
    }
    else if (*this == b) {
        baseCaseReturns =3; 
    }
    else if (*this < Btemp) {
        baseCaseReturns =4; 
    }
    switch(baseCaseReturns){
        case 1:{
        quotient = zip; 
        quotient.isPositive = true; 
        remainder = zip; 
        remainder.isPositive = true; 
        return;
        break;
        }
        case 2:{
        quotient = *this; 
        quotient.isPositive = endSign; 
        remainder = zip; 
        remainder.isPositive = true; 
        return; 
        break;
        }
        case 3:{
        quotient = BigInt(1, base); 
        quotient.isPositive = endSign; 
        remainder = zip; 
        remainder.isPositive = true; 
        return;
        break;
        }
        case 4:{
        quotient = zip; 
        quotient.isPositive = true; 
        remainder = *this; 
        remainder.isPositive = originalsignofA; 
        return;
        break;
        }
    }
    //long division 
    int index = vec.size() - 1; 
    BigInt pullout(vec[index], base); 
    while (pullout < Btemp) {
        index -= 1; 
        pullout.vec.insert(pullout.vec.begin(), vec[index]); 
    }
    
    while (index >= 0){
        int times = 0; 
        while (pullout >= Btemp) {
            pullout -= Btemp; 
            times += 1; 
        }
    
        quotient.vec.insert(quotient.vec.begin(), times); 
        if (pullout.vec.size()== 1 && pullout.vec[0] == 0) {
            pullout.vec.clear(); 
        }
        if (index - 1 >= 0) {
            pullout.vec.insert(pullout.vec.begin(), vec[index-1]); 
        }
        index -= 1; 
    }
    //check if empty 
    if (pullout.vec.size()== 0) {
        remainder.vec.push_back(0); 
        remainder.isPositive = true; 
    }
    else {
        remainder = pullout; 
        remainder.isPositive = originalsignofA; 
    }
    quotient.isPositive = endSign;                 
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'exponentiation' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt pow(const  BigInt &a, const BigInt & b){

    /************* You complete *************/
    BigInt copy = a; 
    copy.exponentiation(b); 
    return copy; 
}

/*
//==================
// MEMBER function
//==================
//  Exponentiation assignment function.
//     - i.e., a.exponentiation(b);
// Note: 1. implement Exponentiation by Squaring (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
*/
const BigInt & BigInt::exponentiation(const BigInt &b){
    if(base != b.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
    BigInt first(1, base); 
    BigInt second(2, base); 
    BigInt result(*this); 
    BigInt exponent = b;  
    bool even; 
    int possibleretunrs =0;
    if (b.vec.size()== 1 && b.vec[0] == 0) {
        possibleretunrs =1; 
    }
    if (b== first) {
        possibleretunrs =2;
    }
    switch(possibleretunrs){
        case 1:{
        *this = first; 
        return *this;
        break;
        }
        case 2:{
        return *this; 
        break;
        }
    }
    BigInt a = first; 
    while (exponent > first) {
       even = ((exponent % second).to_int() == 0); 
        if (even) {
            result *= result; 
        }
        else {
            a *= result; 
            exponent -= first; 
            result *= result; 
        }
        exponent /= second; 
    }
    result *= a; 
    *this = result; 
    return *this; 
}

/*
//======================
// NON-MEMBER function
//======================
// 1. Create a copy of a
// 2. Call the 'modulusExp' function on the copy and b
// 3. Return the copy
// Note: Should take you exactly 3 lines of code
*/
BigInt modPow(const BigInt &a, const BigInt &b, const BigInt &m){

    BigInt copy = a; 
    copy.modulusExp(b, m); 
    return copy; 
}


/*
//==================
// MEMBER function
//==================
//  Modulus Exponentiation assignment function.
//     - i.e., a.modulusExp(b)
// Note: 1. implement Modulus Exponentiation (see the writeup)
//       2. b should be treated as BigInt, not int or other data type.
// Hint: same implementation as exponentiation, but take modulus 
//          after every call to the *= operator.
*/
const BigInt & BigInt::modulusExp(const BigInt &b, const BigInt &m){
    if(base != b.base || base != m.base){
        throw DiffBaseException();
    }
    if(!b.isPositive){
        throw ExpByNegativeException();
    }
    /************* You complete *************/
BigInt zero(0, base); 
    BigInt first(1, base); 
    BigInt second(2, base); 
    BigInt result(*this); 
    BigInt exponent = b;  
    bool iseven; 
    int possiblereturn =0;
    if (b.vec.size()== 1 && b.vec[0] == 0) {
        possiblereturn =1; 
    }
    if (b== first) {
        possiblereturn =2; 
    }
    switch(possiblereturn){
        case 1:{
            *this = first; 
            return *this;
            break;
        }
        case 2:{
            return *this;
            break;
        }
    }
    BigInt a = first; 
    while (exponent > first) {
        iseven = ((exponent % second).to_int() == 0); 
        if (iseven) {
            result *= result; 
            result %= m; 
        }
        else {
            a *= (result % m); 
            result *= result; 
            result %= m; 
            a %= m; 
            exponent -= first; 
        }
        exponent /= second; 
    }
    result *= a; 
    result %= m; 
    *this = result; 
    return *this; 
}

//******************************************************************
//END OF THE ARITHMETIC OPERATORS SECTION
//******************************************************************

//******************************************************************
//START OF SANITY CHECK FUNCTIONS
//YOU CAN USE THEM, BUT DO NOT CHANGE ANYTHING
//THESE FUNCTIONS ARE COMPLETE.
//******************************************************************
void BigInt::printVecItems(){
  cout<<"[";
  for(size_t i = 0;i<vec.size();i++){
    cout<<vec[i];
    if(i < vec.size()-1){
      cout<<",";
    }
  }
  cout<<"]"<<endl;
}

bool BigInt::getSign(){
	return isPositive;
}

int BigInt::getBase(){
	return base;
}
//******************************************************************
//END OF SANITY CHECKS SECTION
//******************************************************************