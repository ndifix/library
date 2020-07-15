#ifndef NDIFIX_SEGMENTTREE
#define NDIFIX_SEGMENTTREE

#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

namespace ndifix {
// 単位元と2項演算 TxT -> T が定義されているものについて定義する。
// 木のサイズは後から変更不可にする。
// i-thを変更することができる
// [s, e)における値、位置を取得できる
template <class T>
class SegmentTree {
  // 最下層は2^rank のサイズを持つようにする。
  // rank は1-indexed
  // i-thデータはnodes[length-1+i]
  // i-th nodeの子は 2i+1, 2i+2。親は (i-1)/2
  // 先頭から詰めてデータを格納。

 private:
  // 有効な配列長です
  int size;

  // 1-indexedの木の深さです
  int rank;

  // 最下層の長さです
  int length;

  std::vector<T> nodes;

  // 単位元
  T id = 0;

  // 構造に入れる演算
  T func(T a, T b) { return std::max(a, b); }

  // 検索に使う比較演算
  bool comp(T a, T b) {
    // aの方を掘り下げる場合 true
    // bの方を掘り下げる場合 false

    return a > b;
  }

  // sizeからrankを初期化します。
  void setRankAndId() {
    if (size < 1)
      throw std::out_of_range("サイズは1以上である必要があります\n");
    rank = std::ceil(std::log2(size)) + 1;
    length = 1 << (rank - 1);
    nodes.resize((1 << rank) - 1);
    for (auto &i : nodes) {
      i = id;
    }
  }

  // 初期データから木を初期化します
  void init() {
    for (int i = length - 2; i >= 0; i--) {
      nodes[i] = func(nodes[2 * i + 1], nodes[2 * i + 2]);
    }
  }

  // nodes[i]が属するrankを返します。
  int Rank(int i) { return (int)floor(log2(i + 1)) + 1; }

  // nodes[i]のrank内での順序を返します
  int Th(int i) { return i + 1 - (1 << (Rank(i) - 1)); }

  // rank, thで指定されたnodeの値を返します。
  T Get(int rk, int th) {
    int i = (1 << (rk - 1)) - 1 + th;
    return nodes[i];
  }

  // nodes[i]が被覆する範囲を返します。
  std::pair<int, int> range(int index) {
    std::pair<int, int> ret(std::make_pair(0, 0));
    int exp = 1 << (rank - Rank(index));
    ret.first = Th(exp - 1 + index * exp);
    ret.second = ret.first + exp;

    return ret;
  }

 public:
#pragma region Constructors

  SegmentTree(T identity, int s) {
    id = identity;
    size = s;
    setRankAndId();
  }

  SegmentTree(T identity, std::vector<T> &data) {
    id = identity;
    size = data.size();
    setRankAndId();
    for (int i = 0; i < size; i++) {
      nodes[length - 1 + i] = data[i];
    }
    init();
  }

#pragma endregion

#pragma region Methods

  // 最下層th 番目のnodeのみが変更されたときに伝播させます。
  void cal(int th) {
    if (th < 0 || th > size)
      throw std::out_of_range("不正な範囲へのアクセス\n");
    int index = length - 1 + th;

    while (index) {
      index % 2 == 0
          ? nodes[(index - 1) / 2] = func(nodes[index - 1], nodes[index])
          : nodes[(index - 1) / 2] = func(nodes[index], nodes[index + 1]);
      index = (index - 1) / 2;
    }
  }

  // 最下層th 番目のnodeをvalに変更します。
  void update(int th, int val) {
    nodes[length - 1 + th] = val;
    cal(th);
  }

  // compで定義されたものの値を返します。
  // [s, e) -> T
  T FindValueByRange(int s, int e) {
    if (s + 1 > e) throw std::out_of_range();
    if (s + 1 == e) return Get(rank, s);
    std::pair<int, int> key(std::make_pair(s, e));
    T ret = id;

    for (int i = 0; i < nodes.size(); i++) {
    }
    return ret;
  }

  // compで定義されたもののindexを返します。
  // [s, e) -> index(T)
  int FindIndexByRange(int s, int e) {}

  // 木全体を出力します。
  void PrintAll() {
    for (int r = 1; r <= rank; r++) {
      for (int th = 0; th < 1 << (r - 1); th++) {
        std::cout << Get(r, th);
        for (int t = 0; t < 1 << (rank - r); t++) std::cout << "\t";
      }
      std::cout << std::endl;
    }
  }

#pragma endregion
};

}  // namespace ndifix

#endif  // !NDIFIX_AEGMENTTREE