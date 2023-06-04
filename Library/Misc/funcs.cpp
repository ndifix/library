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
double L2_distance(int x1,int y1,int x2,int y2);
