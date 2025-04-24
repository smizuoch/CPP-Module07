#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <algorithm> // std::swap (C++98 OK)
#include <cstddef>   // size_t
#include <stdexcept> // std::out_of_range

/**
 * @brief 可変長テンプレート配列クラス（簡易版 STL::vector のイメージ）
 *
 * - 動的領域は new[] / delete[] で管理
 * - 正統カノニカル形（デフォルト ctor, コピー ctor, 代入演算子, dtor）
 * - operator[] で範囲外なら例外を送出
 */
template <typename T> class Array
{
  public:
	/* ------------------------- コンストラクタ群 -------------------------- */

	// (1) デフォルト : サイズ 0 の空配列
	Array() : _data(NULL), _size(0)
	{
	}

	// (2) サイズ指定コンストラクタ
	explicit Array(unsigned int n) : _data(NULL), _size(n)
	{
		if (n == 0)
			return;         // 空配列なら確保しない
		_data = new T[n](); // () で “デフォルト値” 初期化
	}

	// (3) コピーコンストラクタ（深いコピー）
	Array(const Array &other) : _data(NULL), _size(other._size)
	{
		if (_size)
		{
			_data = new T[_size];
			for (unsigned int i = 0; i < _size; ++i)
				_data[i] = other._data[i]; // 要素ごとコピー
		}
	}

	/* --------------------------- デストラクタ ---------------------------- */
	~Array()
	{
		delete[] _data; // NULL でも delete[] は安全
	}

	/* ------------------------ 代入演算子 (copy&swap) --------------------- */
	Array &operator=(Array rhs) // 値渡しでコピーが作られる
	{
		// copy & swap ─ rhs はローカルなのでここでリソースを交換し
		// 関数終了時に古いリソースが破棄される → 例外安全 & リークなし
		swap(rhs);
		return *this;
	}

	/* ---------------------------- 要素アクセス --------------------------- */
	// 書き換え可
	T &operator[](unsigned int idx)
	{
		rangeCheck(idx);
		return _data[idx];
	}

	// 読み取り専用
	const T &operator[](unsigned int idx) const
	{
		rangeCheck(idx);
		return _data[idx];
	}

	/* ---------------------------- 要素数取得 ----------------------------- */
	unsigned int size() const
	{
		return _size;
	}

  private:
	T *_data;           // 動的に確保した配列
	unsigned int _size; // 要素数

	/* ---- ヘルパ: index が範囲外なら例外を投げる ----------------------- */
	void rangeCheck(unsigned int idx) const
	{
		if (idx >= _size)
			throw std::out_of_range("Array: index out of bounds");
	}

	/* ---- copy & swap 用のスワップ関数 (private) ---------------------- */
	void swap(Array &other)
	{
		std::swap(_data, other._data);
		std::swap(_size, other._size);
	}
};

#endif /* ARRAY_HPP */
