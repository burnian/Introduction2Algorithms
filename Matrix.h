/*********************************************************
*@Author: Burnian Zhou
*@Create Time: 10/16/2019, 20:38
*@Last Modify: 11/12/2019, 20:57
*@Desc: æÿ’Û∂‘œÛ
*********************************************************/
#pragma once


namespace Bur {
	template<typename T>
	class Matrix
	{
	public:
		Matrix(const size_t row, size_t col, T* arr):m(row), n(col) {
			
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					_data[i][j] = arr[i*m + j];
				}
			}
		};
		~Matrix() {};

		T operator[][](int i, int j){
			return _data[i][j];
		};
	private:
		size_t m; // m row
		size_t n; // n column
		T _data[100][100];
	};
}
