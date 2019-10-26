#include <vector>
#include <iostream>
namespace ndifix{

class Matrix{
		public:
	int row, collumn;
	std::vector<std::vector<int>> data;
		
	Matrix(){row=collumn=2;data.resize(row);for(int i=0;i<row;i++)data[i].resize(collumn);}
	Matrix(int r,int c){row=std::max(1,r);collumn=std::max(1,c);data.resize(row);for(int i=0;i<row;i++)data[i].resize(collumn);}
	Matrix(std::vector<std::vector<int>> &v){if(v.size()==0){Matrix();return;}if(v[0].size()==0){Matrix();return;}data=v;row=data.size();collumn=data[0].size();}

	void push_row(std::vector<int> v){if(v.size()==collumn)data.push_back(v);}
	void push_collumn(std::vector<int> v){if(v.size()==row){for(int i=0;i<row;i++)data[i].push_back(v[i]);}}

	void operator+=(Matrix m){if(row!=m.row || collumn!=m.collumn)return;for(int i=0;i<row;i++)for(int j=0;j<collumn;j++){data[i][j]+=m.data[i][j];}}
	void operator-=(Matrix m){if(row!=m.row || collumn!=m.collumn)return;for(int i=0;i<row;i++)for(int j=0;j<collumn;j++){data[i][j]-=m.data[i][j];}}
	Matrix operator+(Matrix m){if(row!=m.row || collumn!=m.collumn)return *this;Matrix ret=(*this);for(int i=0;i<row;i++)for(int j=0;j<collumn;j++){ret.data[i][j]+=m.data[i][j];}return ret;}
	Matrix operator-(Matrix m){if(row!=m.row || collumn!=m.collumn)return *this;Matrix ret=(*this);for(int i=0;i<row;i++)for(int j=0;j<collumn;j++){ret.data[i][j]-=m.data[i][j];}return ret;}
	void operator*=(Matrix m){if(collumn!=m.row)return;Matrix ret(row,m.collumn);for(int i=0;i<row;i++)for(int j=0;j<m.collumn;j++)for(int k=0;k<collumn;k++){ret.data[i][j]+=data[i][k]*m.data[k][j];}data=ret.data;row=ret.row;collumn=ret.collumn;}
	Matrix operator*(Matrix m){
		if(collumn!=m.row)return *this;
		Matrix ret(row,m.collumn);
		for(int i=0;i<row;i++)for(int j=0;j<m.collumn;j++)for(int k=0;k<collumn;k++)ret.data[i][j]+=data[i][k]*m.data[k][j];
		return ret;}
	void operator=(std::vector<std::vector<int>> v){data=v;row=v.size();if(row)collumn=v[0].size();}


	friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

std::ostream& operator<<(std::ostream& os, const Matrix& m){
	for(int i=0;i<m.row;i++){
		for(int j=0;j<m.collumn;j++){
			os<<m.data[i][j];
			if(j!=m.collumn-1)os<<"\t";
			if(i!=m.row-1&&j==m.collumn-1)os<<"\n";
		}
	}
	return os;
}

}