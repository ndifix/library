class Quoziente{
        private:
    long long numer, denom;
        public:
    Quoziente(int n, int d){numer=n; denom=d;}
    Quoziente(long long n, long long d){numer=n; denom=d;}
    Quoziente(){numer=denom=1;}
    int gcd(int a,int b){if(a<b)return gcd(b,a);if(a%b==0)return b;return gcd(b, a%b);}
    void nomalize(){int div=gcd(numer,denom);numer/=div;denom/=div;}

    void operator+=(int n);
    void operator-=(int n);
    void operator*=(int n);
    void operator/=(int n);
    Quoziente operator+(int n);
    Quoziente operator-(int n);
    Quoziente operator*(int n);
    Quoziente operator/(int n);
    void operator+=(Quoziente n);
    void operator-=(Quoziente n);
    void operator*=(Quoziente n);
    void operator/=(Quoziente n);
    Quoziente operator+(Quoziente n);
    Quoziente operator-(Quoziente n);
    Quoziente operator*(Quoziente n);
    Quoziente operator/(Quoziente n);
};