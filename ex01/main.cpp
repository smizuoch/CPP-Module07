#include "iter.hpp"
#include <cctype>  // toupper
#include <cstddef> // size_t, NULL
#include <iostream>
#include <string>

/* 汎用プリンタ */
template <typename T> void printElem(const T &x)
{
	std::cout << x << " ";
}

/* int を +1 する関数 */
void addOne(int &x)
{
	++x;
}

/* std::string を大文字化（C++98 互換版） */
void toUpper(std::string &s)
{
	for (std::size_t i = 0; i < s.size(); ++i)
	{
		// unsigned char にキャストしてから toupper すると安全
		s[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(s[i])));
	}
}

int main()
{
	// -------- [1] 基本テスト（int 配列） --------
	int intArr[5] = {0, 1, 2, 3, 4};
	std::cout << "[int] before addOne : ";
	iter(intArr, 5, printElem<int>);
	std::cout << "\n";
	iter(intArr, 5, addOne);
	std::cout << "[int] after  addOne : ";
	iter(intArr, 5, printElem<int>);
	std::cout << "\n\n";

	// -------- [2] 基本テスト（std::string 配列） --------
	std::string strArr[3] = {"apple", "banana", "Cocoa"};
	std::cout << "[string] before toUpper : ";
	iter(strArr, 3, printElem<std::string>);
	std::cout << "\n";
	iter(strArr, 3, toUpper);
	std::cout << "[string] after  toUpper : ";
	iter(strArr, 3, printElem<std::string>);
	std::cout << "\n\n";

	// -------- [3] 空文字列を含むテスト --------
	std::string strArrEmpty[4] = {"", "MixEd", "", "case"};
	std::cout << "[string] before toUpper (empty elems) : ";
	iter(strArrEmpty, 4, printElem<std::string>);
	std::cout << "\n";
	iter(strArrEmpty, 4, toUpper);
	std::cout << "[string] after  toUpper (empty elems) : ";
	iter(strArrEmpty, 4, printElem<std::string>);
	std::cout << "\n\n";

	// -------- [4] 長さゼロテスト --------
	std::cout << "[int] zero-length test: ";
	iter(intArr, 0, printElem<int>); // 警告のみ
	std::cout << "(done)\n\n";

	// -------- [5] ヌルポインタテスト --------
	int *nullInt = NULL; // C++98 では NULL を使う
	std::cout << "[int] null-pointer test: ";
	iter(nullInt, 5, printElem<int>); // 警告のみ
	std::cout << "(done)\n\n";

	// -------- [6] コンパイルエラー検証 --------
	// 以下はコメントアウトしておき、誤適用でコンパイルエラーになることを確認
	// iter(intArr, 5, toUpper);    // ❌ int 配列に toUpper は適用不可
	// iter(strArr, 3, addOne);     // ❌ std::string 配列に addOne は適用不可

	return 0;
}
