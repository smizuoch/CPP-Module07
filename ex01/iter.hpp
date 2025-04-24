#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>  // size_t, NULL
#include <iostream> // 警告メッセージ用の std::cerr

/* ************************************************************************** */
/*                    非 const 配列用オーバーロード（書き換え可）            */
/* ************************************************************************** */
template <typename T, typename F> void iter(T *array, std::size_t len, F func)
{
	/* --- 防御コード: NULL あるいは長さ 0 は “何もしない” --------------- */
	if (array == NULL)
	{
		std::cerr << "iter(): A NULL pointer was passed — skipping processing." << std::endl;
		return; // これでセグフォを防ぐ
	}
	if (len == 0)
		return;

	/* --- 通常処理: 配列の各要素に func を適用 --------------------------- */
	for (std::size_t i = 0; i < len; ++i)
		func(array[i]); // i 番目の要素を func へ渡す
}

/* ************************************************************************** */
/*                    const 配列用オーバーロード（読み取り専用）             */
/* ************************************************************************** */
template <typename T, typename F> void iter(T const *array, std::size_t len, F func)
{
	/* NULL／長さ 0 ガードは同じロジック */
	if (array == NULL)
	{
		std::cerr << "iter(): A NULL pointer was passed — skipping processing." << std::endl;
		return;
	}
	if (len == 0)
		return;

	for (std::size_t i = 0; i < len; ++i)
		func(array[i]);
}

#endif /* ITER_HPP */
