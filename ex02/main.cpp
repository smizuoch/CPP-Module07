#include "Array.hpp"
#include <iostream>
#include <string>

/* デバッグ表示用 */
template <typename Arr> void dumpArray(const Arr &a, const std::string &tag)
{
	std::cout << tag << " (size=" << a.size() << "): ";
	for (unsigned int i = 0; i < a.size(); ++i)
		std::cout << a[i] << " ";
	std::cout << std::endl;
}

int main()
{
	try
	{
		/* ---------- 1. デフォルトコンストラクタ ---------- */
		Array<int> empty;
		std::cout << "Empty array size = " << empty.size() << "\n\n";

		/* ---------- 2. サイズ指定コンストラクタ ---------- */
		Array<int> ai(5); // int は 0 初期化される
		for (unsigned int i = 0; i < ai.size(); ++i)
			ai[i] = i * 10; // 値を書き込む
		dumpArray(ai, "ai");

		/* ---------- 3. コピーコンストラクタ ---------- */
		Array<int> bi(ai);                       // 深いコピー
		bi[1] = 777;                             // bi のみ変更
		dumpArray(ai, "ai (after bi modified)"); // ai は影響受けない
		dumpArray(bi, "bi");

		/* ---------- 4. 代入演算子 ---------- */
		Array<std::string> as1(3);
		as1[0] = "foo";
		as1[1] = "bar";
		as1[2] = "baz";

		Array<std::string> as2;
		as2 = as1; // copy & swap
		as2[2] = "qux";
		dumpArray(as1, "as1");
		dumpArray(as2, "as2 (modified)");

		/* ---------- 5. 例外発生テスト ---------- */
		std::cout << "\nAttempting out-of-bounds access...\n";
		std::cout << ai[999] << std::endl; // ここで例外
	}
	catch (std::exception &e)
	{
		std::cerr << "Catch: " << e.what() << std::endl;
	}

	return 0;
}
