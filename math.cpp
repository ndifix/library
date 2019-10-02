#include <algorithm>
#include <vector>
#include <string>
#include <map>

long long pow(int base,int exp){
    long long ret=1;
    std::vector<long long> buf(32);buf[0]=base;
    for(int i=1;i<32;i++)buf[i]=buf[i-1]*buf[i-1];
    for(int i=0;(1<<i)<=exp;i++)if(exp & (1<<i))ret*=buf[i];
    return ret;
}//高速二乗和
std::vector<std::pair<int,int>> Factorization_v(int n){
    std::vector<std::pair<int,int>> ret;
    int base, exp=0;
    while(n%2==0){n/=2;exp++;}
    if(exp>0)ret.push_back(std::make_pair(2,exp));

    base=3;
    while(n!=1){
        exp=0;
        while(n%base==0){n/=base;exp++;}
        if(exp>0)ret.push_back(std::make_pair(base,exp));
        base+=2;
    }
    return ret;
}//素因数分解
std::map<int,int> Factorization_m(int n){
    std::map<int,int> ret;
    int base;
    while(n%2==0){n/=2;ret[2]++;}

    base=3;
    while(n!=1){
        while(n%base==0){n/=base;ret[base]++;}
        base+=2;
    }
    return ret;
}//素因数分解
std::map<int,int> expLCM(std::map<int,int> A,std::map<int,int> B){
    std::map<int,int> ret;
    for(auto itr=A.begin();itr!=A.end();itr++)
        ret[(*itr).first]+=(*itr).second;
    for(auto itr=B.begin();itr!=B.end();itr++)
        ret[(*itr).first]+=(*itr).second;
    return ret;
}
std::map<int,int> expGCD(std::map<int,int> A,std::map<int,int> B){
    std::map<int,int> ret;
    for(auto itr=A.begin();itr!=A.end();itr++){
        ret[(*itr).first]=std::min(A[(*itr).first],B[(*itr).first]);
    }
    for(auto itr=ret.begin();itr!=ret.end();){
        if((*itr).second==0){ret.erase(itr);itr=ret.begin();}
        else itr++;
    }
    return ret;
}
long long exp_toint(std::map<int,int> e){
    long long ret=1;
    for(auto itr=e.begin();itr!=e.end();itr++)
        ret*=pow((*itr).first,(*itr).second);
    return ret;
}
std::vector<std::vector<long long>> combination_memo;
long long combination(int n, int r){
  if(r==1)return n;
  if(r==0)return 1;
  if(combination_memo.size()<n)combination_memo.resize(n+1);
  if(combination_memo[n].size()<r)combination_memo[n].resize(r+1);
  if(r > n-r)return combination_memo[n][r]=combination(n,n-r);
  if(combination_memo[n][r])return combination_memo[n][r];
  combination_memo[n][r]=combination(n-1,r)+combination(n-1,r-1);
  return combination_memo[n][r];
}//combination_memo is needed

class Quoziente{
        private:
    long long numer, denom;
        public:
    Quoziente(int n, int d){numer=n; denom=d;}
    Quoziente(long long n, long long d){numer=n; denom=d;}
    Quoziente(){numer=denom=1;}
    int gcd(int a,int b){if(a<b)return gcd(b,a);if(a%b==0)return b;return gcd(b, a%b);}
    void nomalize(){int div=gcd(numer,denom);numer/=div;denom/=div;}

    void operator+=(int n){}
    void operator-=(int n){}
    void operator*=(int n){}
    void operator/=(int n){}
    Quoziente operator+(int n){}
    Quoziente operator-(int n){}
    Quoziente operator*(int n){}
    Quoziente operator/(int n){}
    void operator+=(Quoziente n){}
    void operator-=(Quoziente n){}
    void operator*=(Quoziente n){}
    void operator/=(Quoziente n){}
    Quoziente operator+(Quoziente n){}
    Quoziente operator-(Quoziente n){}
    Quoziente operator*(Quoziente n){}
    Quoziente operator/(Quoziente n){}
};

class Matrix{
		public:
	int row, collumn;
	std::vector<std::vector<int>> data;
		
	Matrix(){row=collumn=1;data.resize(1);data[0].push_back(0);}
	Matrix(int r,int c){row=std::min(1,r);collumn=std::min(1,c);data.resize(row);for(int i=0;i<row;i++)data[i].resize(collumn);}
	Matrix(std::vector<std::vector<int>> &v){if(v.size()==0){Matrix();return;}if(v[0].size()==0){Matrix();return;}data=v;row=data.size();collumn=data[0].size();}

	void push_row(std::vector<int> v){if(v.size()==collumn)data.push_back(v);}
	void push_collumn(std::vector<int> v){if(v.size()==row){for(int i=0;i<row;i++)data[i].push_back(v[i]);}}

	void operator+=(Matrix m){if(row!=m.row || collumn!=m.collumn)return;for(int i=0;i<row;i++)for(int j=0;j<collumn;j++){data[i][j]+=m.data[i][j];}}
	void operator-=(Matrix m){if(row!=m.row || collumn!=m.collumn)return;for(int i=0;i<row;i++)for(int j=0;j<collumn;j++){data[i][j]-=m.data[i][j];}}
	Matrix operator+(Matrix m){if(row!=m.row || collumn!=m.collumn)return *this;Matrix ret=(*this);for(int i=0;i<row;i++)for(int j=0;j<collumn;j++){ret.data[i][j]+=m.data[i][j];}return ret;}
	Matrix operator-(Matrix m){if(row!=m.row || collumn!=m.collumn)return *this;Matrix ret=(*this);for(int i=0;i<row;i++)for(int j=0;j<collumn;j++){ret.data[i][j]-=m.data[i][j];}return ret;}
	void operator*=(Matrix m){if(collumn!=m.row)return;Matrix ret(row,m.collumn);for(int i=0;i<row;i++)for(int j=0;j<m.collumn;j++)for(int k=0;k<collumn;k++){ret.data[i][j]+=data[i][k]*m.data[k][j];}data=ret.data;row=ret.row;collumn=ret.collumn;}
	Matrix operator*(Matrix m){if(collumn!=m.row)return *this;Matrix ret(row,m.collumn);for(int i=0;i<row;i++)for(int j=0;j<m.collumn;j++)for(int k=0;k<collumn;k++){ret.data[i][j]+=data[i][k]*m.data[k][j];}return ret;}
};