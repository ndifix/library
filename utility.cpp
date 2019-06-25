#include <iostream>
#include <vector>
#include <string>
#include <map>

std::ostream& operator<<(std::ostream& os,std::map<int,int>& obj){
    for(auto itr=obj.begin();itr!=obj.end();itr++){
        os<<itr->first<<"^"<<itr->second<<" ";
    }
    return os;
}
std::ostream& operator<<(std::ostream& os,std::vector<int>& obj){
    for(auto itr=obj.begin();itr!=obj.end();itr++){
        os<<*itr<<" ";
    }
    return os;
}
std::ostream& operator<<(std::ostream& os,std::vector<std::map<int,int>>& obj){
    for(auto itr=obj.begin();itr!=obj.end();itr++){
        os<<*itr<<std::endl;
    }
    return os;
}
std::map<int,int> mapMerge(std::map<int,int> A, std::map<int,int> B){
    std::map<int,int> ret=A;
    for(std::map<int,int>::iterator itr=B.begin();itr!=B.end();itr++){ret[itr->first]+=itr->second;}
    return ret;
}
template<class T>void sort(T &v){std::sort(v.begin(),v.end());}
template<class T>int lower_bound(std::vector<T> &a, T key){
	int s=0,e=a.size();
	int mid;
	while(e-s>2){
		mid=(e+s)/2;
		if(a[mid] < key)s=mid;
		else if(a[mid] > key)e=mid;
		else if(a[mid]==key)e=mid+1;
	}
	if(a[s]>=key)return s;if(a[s+1]>=key)return s+1;return s+2;
}
template<class T>int upper_bound(std::vector<T> &a, T key){
	int s=0,e=a.size();
	int mid;
	while(e-s>2){
		mid=(e+s)/2;
		if(a[mid]<=key)s=mid;
		else if(a[mid]>key && a[mid+1]>key)e=mid+1;
	}
	if(a[s]>key)return s;if(a[s+1]>key)return s+1;return s+2;
}