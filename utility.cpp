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