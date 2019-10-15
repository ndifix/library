#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
class SciNum{
    private:
  //仮数、有効桁数、指数部, max digit=7
  int num, digit, exp;
  
  int exp10[10]={
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
  };
  int min(int a, int b){return a<b?a:b;}
  int max(int a, int b){return a>b?a:b;}
  int abs(int n){return n>=0?n:-n;}

    public:
  SciNum(int n=1, int e=0, int d=2){
    num=n;
    digit=max(3,min(d+2,7));
    exp=e;
    modify();
  }
  SciNum(double n){
    digit=6;
    exp=0;
    num=n;
    while(n!=num && n<100000000){
      n*=10; exp--;
      num=n;
    }
    modify();
  }
  void modify(){
    while(abs(num)>=exp10[digit]){
      num/=10;
      exp++;
    }
    while(abs(num)<exp10[digit-1]){
      num*=10;
      exp--;
    }
  }
  void operator=(SciNum snum){
    num=snum.num;
    digit=snum.digit;
    exp=snum.exp;
  }

  std::string toString(){
    int top=num/exp10[digit-1], decimical=num%exp10[digit-1];
    if(decimical%100 >=50)decimical+=100;
    decimical/=100;
    std::stringstream ss;
    ss<<top<<'.';
    ss<<std::setfill('0')<<std::left<<std::setw(digit-3)<<decimical<<'e'<<exp+digit-1;
    return ss.str();
  }
  double toDouble(){
    double ret=num;
    while(exp>0){
      ret*=10.0;exp--;
    }
    while(exp<0){
      ret/=10.0;exp++;
    }
    return ret;
  }
  friend SciNum operator+(SciNum,SciNum);
  friend SciNum operator-(SciNum,SciNum);
  friend SciNum operator*(SciNum,SciNum);
  //friend SciNum operator/(SciNum,SciNum);
  friend double operator/(SciNum,SciNum);
  friend std::ostream& operator<<(std::ostream&, const SciNum&);
};
SciNum operator+(SciNum a, SciNum b){
  //a.digit=a.min(a.digit,b.digit);a.modify();
  //b.digit=b.min(a.digit,b.digit);b.modify();
  
  if(a.exp<b.exp)a.num/=a.exp10[b.exp-a.exp];
  else b.num/=b.exp10[a.exp-b.exp];
  a.num+=b.num;
  a.exp=a.max(a.exp,b.exp);
  a.modify();
  return a;
}
SciNum operator-(SciNum a, SciNum b){
  b.num*=(-1);
  return a+b;
}
SciNum operator*(SciNum a, SciNum b){
  long long anum=a.num,bnum=b.num;
  a.digit=a.min(a.digit,b.digit);
  a.exp+=b.exp;
  anum*=bnum;
  while(anum>=a.exp10[a.digit] || anum<=-a.exp10[a.digit]){
    a.exp++;
    anum/=10;
  }
  a.num=anum;
  a.modify();
  return a;
}
double operator/(SciNum a, SciNum b){
  double ad=a.toDouble();
  double bd=b.toDouble();
  return ad/bd;
}
std::ostream& operator<<(std::ostream& os,SciNum& snum){
  std::string s=snum.toString();
  os<<s;
  return os;
}