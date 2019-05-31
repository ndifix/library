#include <vector>
#include <string>
#include <map>

int StringToInt(std::string s){
	int ret=0;	if(s.size()>9||s.size()==0) return 0;
	for(int i=0; i<s.size(); i++)
		if(s[i]<'0' && s[i]>'9') return 0;
	ret=s[0]-'0';
	for(int i=1; i<s.size(); i++){	ret*=10;	ret+=s[i]-'0';	}
	return ret;
} //string型をint型に変換
std::string ExtractString(std::string s, int begin, int end){
	std::string t;
	for(int i=begin; i<end; i++) t+=s[i];
	return t;
}// [beg, end)を抽出
int L1_distance(int x1,int y1,int x2,int y2){
	return (x1<x2?x2-x1:x1-x2)+(y1<y2?y2-y1:y1-y2);
}//マンハッタン距離
double L2_distance(int x1,int y1,int x2,int y2){
	double ret=(x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}
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