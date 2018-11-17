#pragma once
// a matrix based on std::vector.
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include <cassert>
#include <iostream>

namespace djalib
{
	template<typename T = double>
	class Matrix
	{
		typedef T data_type;
		// matrix storage.
		std::vector<std::vector<data_type>> matrix;

		// allocate / deallocate:
		void allocate(
			size_t rows,
			size_t cols) {
			// set up matrix sizes.
			matrix.resize(rows);
			for (size_t idx = 0; idx < rows; ++idx)
				matrix[idx].resize(cols);
		}

	public:
		// get row and col number
		const size_t rows() const {
			return
				matrix.size();
		}
		const size_t cols() const {
			return
				matrix[0].size();
		}

		//------------------------------
		//------------------------------
	public:
		// constructors / destructor:
		Matrix() {
			// allocate memory for new matrix.
			allocate(1, 1);
		}
		Matrix(size_t rank) {
			assert(rank);
			// allocate memory for new matrix.
			allocate(rank, rank);
		}
		Matrix(size_t rows, size_t cols) {
			assert(rows && cols);
			// allocate memory for new matrix.
			allocate(rows, cols);
		}

		// copy constructor:
		Matrix(const Matrix& ref) {
			std::cout << "copy constructor." << "\n";
			matrix.assign(ref.matrix.cbegin(), ref.matrix.cend());
		}
		// move constructor:
		Matrix(Matrix&& gift) {
			std::cout << "move constructor." << "\n";
			matrix = std::move(gift.matrix);
		}

		//------------------------------
		//------------------------------
	public:
		Matrix& operator =(const Matrix& ref) {
			if (this != &ref) {
				std::cout << "copy assign." << "\n";
				matrix.assign(ref.matrix.cbegin(), ref.matrix.cend());
			}
			return *this;
		}
		Matrix& operator =(Matrix&& gift) {
			if (this != &gift) {
				std::cout << "move assign." << "\n";
				matrix = std::move(gift.matrix);
			}
			return *this;
		}

		data_type& operator ()(size_t row, size_t col) {
			assert(!matrix.empty());
			assert(
				row < matrix.size() &&
				col < matrix[0].size() &&
				row >= 0 &&
				col >= 0);
			return
				matrix[row][col];
		}
		const data_type& operator ()(size_t row, size_t col) const {
			assert(!matrix.empty());
			assert(
				row < matrix.size() &&
				col < matrix[0].size() &&
				row >= 0 &&
				col >= 0);
			return
				matrix[row][col];
		}

		//------------------------------
		//------------------------------
	public:
		void resize(
			size_t nrows,
			size_t ncols) {
			assert(nrows && ncols);
			matrix.resize(nrows);
			for (size_t idx = 0; idx < nrows; ++idx)
				matrix[idx].resize(ncols);
		}

		//------------------------------
		//------------------------------
	public:
		template <typename T> 
		friend std::ostream& operator <<(std::ostream& os, const Matrix<T>& mat);

	protected:
		void display(std::ostream& os) const {
			// show the whole matrix.
			if (matrix.empty()) return;
			size_t total_rows = this->rows();
			size_t total_cols = this->cols();
			for (size_t ridx = 0; ridx < total_rows; ridx++) {
				for (size_t cidx = 0; cidx < total_cols; cidx++) {
					os << this->operator()(ridx, cidx) << " ";
				} os << "\n";
			} os << "\n";
		}
	};

	template <typename T>
	std::ostream& operator <<(std::ostream& os, const Matrix<T>& mat) {
		mat.display(os);
		return os;
	}

	// create something:
	Matrix<double> getIdentityMatrix(size_t rank) {
		assert(rank > 0);
		Matrix<double> temp(rank);
		return temp;
	}

}

#endif
