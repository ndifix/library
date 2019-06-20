class bigint{
    private:
  const int mod=10000;
  const int intmax=1e8;
  const int modd=4;//10^4
    public:
  std::vector<int> num;//num[i]= k%_mod^i
  bigint(){num.push_back(0);};
  bigint(int n){num.push_back(n%mod);num.push_back((n/mod)%mod);num.push_back((n/mod/mod)%mod);shrink();}
  bigint(long long n){long long m=n;while(m){num.push_back(m%mod);m/=mod;}modify();}
  bool operator <(int n){if(size()>=2)return false;return num[0]<n;}
  bool operator <(bigint &B){if(size()<B.size())return true;for(int i=size()-1;i>=0;i--)if(num[i]!=B[i])return num[i]<B[i];return false;}
  bool operator >(int n){if(size()>=2)return true;return num[0]>n;}
  bool operator >(bigint &B){if(size()>B.size())return true;for(int i=size()-1;i>=0;i--)if(num[i]!=B[i])return num[i]>B[i];return false;}
  bool operator ==(int n){if(size()>=2)return false;return num[0]==n;}
  bool operator ==(bigint &B){if(size()!=B.size())return false;for(int i=size()-1;i>=0;i--)if(num[i]!=B[i])return false;return true;}
  template<class T> bool operator <=(T n){return (*this)<n||(*this)==n;}
  template<class T> bool operator >=(T n){return (*this)>n||(*this)==n;}
  bigint& operator =(const int n){bigint B(n);this->num=B.num;return *this;}
  bigint& operator =(const bigint &B){this->num=B.num;return *this;}
  bigint operator +(int n){bigint B(n);return B+(*this);}
  void operator +=(int n){bigint B(n);(*this)+=B;}
  bigint operator -(int n){}
  bigint operator *(int n){bigint B(n);return B*(*this);}
  void operator *=(int n){bigint B(n);(*this)=(*this)*B;}
  bigint operator /(int n){}
  int operator %(int n){bigint ret=*this,buf;long long tmp=1,tmp2;while(ret>=n){buf=0;for(int i=0;i<ret.size();i++){tmp2=ret[i]*tmp;tmp2%=n;buf+=tmp2;tmp*=mod;tmp%=n;}ret=buf;}return ret.num[0];}
  void operator %=(int n){bigint ret=*this,buf;long long tmp=1,tmp2;while(ret>=n){buf=0;for(int i=0;i<ret.size();i++){tmp2=ret[i]*tmp;tmp2%=n;buf+=tmp2;tmp*=mod;tmp%=n;}ret=buf;}(*this)=ret;}
  bigint operator +(bigint &B){bigint ret=(*this);if(ret.size()<B.size())ret.resize(B.size()); for(int i=0;i<(ret.size()<B.size()?ret.size():B.size());i++)ret[i]+=B[i];ret.modify();return ret;}
  void  operator +=(bigint &B){if(num.size()<B.size())num.resize(B.size());for(int i=0;i<(this->size()<B.size()?this->size():B.size());i++)num[i]+=B[i];modify();}
  bigint operator -(bigint &B){bigint ret(0);if(*this < B){return ret;}ret=*this;for(int i=0;i<(ret.size()<B.size()?ret.size():B.size());i++)ret[i]-=B[i];ret.modify();return ret;}
  bigint operator *(bigint &B){bigint ret(0);int s=size();bigint buf;buf.resize(s);for(int i=0;i<B.size();i++){buf.resize(0);buf.resize(s);for(int j=0;j<s;j++){buf.num[j]=B[i]*num[j];}buf.modify();buf<<=i;ret+=buf;ret.modify();}return ret;}
  void operator *=(bigint &B){(*this)=(*this)*B;}
  bigint operator /(bigint &B){}
  bigint operator <<(int i){bigint ret=(*this);for(int j=0;j<i;j++)ret.num.insert(num.begin(),0);}
  void operator <<=(int i){for(int j=0;j<i;j++)num.insert(num.begin(),0);}
  int& operator [](int i){return this->num[i];}
  std::string to_str(){std::string ret,buf_s;int buf=num[num.size()-1];ret+=std::to_string(buf);for(int i=num.size()-2;i>=0;i--){buf=num[i];buf_s=std::to_string(buf);while(buf_s.size()!=modd)buf_s.insert(buf_s.begin(),'0');ret+=buf_s;buf_s.clear();}return ret;}
  int size(){return int(num.size());}
  void resize(int size){num.resize(size);}
  void shrink(){while(num.size()>=2&&num.back()==0)num.pop_back();}
  void modify(){shrink();int tmp;for(int i=0;i<num.size()-1;i++){if(num[i]<0){tmp=(-1)*num[i];tmp+=(tmp/mod)+!!(tmp%mod);num[i+1]-=tmp;num[i]+=tmp*mod;}}if(num.back()==0){num.resize(1);num[0]=0;}shrink();num.resize(num.size()+1);for(int i=0;i<num.size()-1;i++){if(num[i]>=mod){num[i+1]+=(num[i]/mod);num[i]=num[i]%mod;}}shrink();}
  
  friend std::ostream& operator<<(std::ostream& os,bigint& B);
  
};//end of bigint