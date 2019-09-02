#pragma once

// Copyright (C) summer 2019 Jiaheng Wang
// License(BSD)
// Author: Jiaheng Wang
// This is a 2D matrix.
//

#ifndef DJA_GRID_H_
#define DJA_GRID_H_

namespace dja {
	template <typename T>
	class Grid {
	public:
		/// \brief The constructor.
		///
		/// \warning The creation of new data array requires the type-T class to have a default constructor.
		Grid(int rows = 0, int cols = 0) 
			:
			data_(nullptr),
			rows_(rows),
			cols_(cols) {
			resize(rows, cols);
		}

		/// \brief The copy constructor.
		Grid(const Grid& src) {
			deepCopy(src);
		}

		/// \brief The destructor.
		~Grid() {
			if (data_) {
				delete[] data_;
				data_ = nullptr;
			}
		}

		Grid& operator=(const Grid& src) {
			if (this != &src) {
				deepCopy(src);
			}
			return *this;
		}

		bool operator==(const Grid& src) {
			return equal(src);
		}

		bool operator!=(const Grid& src) {
			return !equal(src);
		}

		/// \brief Get element at the specific location.
		///
		/// \warning Please ensure they are not out of range.
		const T& operator()(int row, int col) const {
			return data_[row * cols_ + col];
		}

		T& operator()(int row, int col) {
			return data_[row * cols_ + col];
		}

		int height() const {
			return rows_;
		}

		int width() const {
			return cols_;
		}

		int size() const {
			return rows_ * cols_;
		}

		bool equal(const Grid& src) {
			if (this == &src) {
				return true;
			}
			else {
				// comparing with the object itself.
				if (rows_ != src.rows_ || cols_ != src.cols_) {
					return false;
				}
				else {
					for (int i = 0; i < rows_; i++) {
						for (int j = 0; j < cols_; j++) {
							if (operator()(i, j) != src.operator()(i, j)) {
								return false;
							}
						}
					}
					return true;
				}
			}
		}

		/// \brief Resize the grid.
		///
		/// Users can choose whether retain existing data or not.
		bool resize(int rows, int cols, bool retain = false) {
			if (rows_ == rows && cols_ == cols && retain) {
				// not necessary for resize if we are already that size
				return false;
			}
			// save backup of the previous info
			int old_rows, old_cols;
			{
				old_rows = rows_;
				old_cols = cols_;
			}
			T* old_data = data_;
			// resize with the new info
			{
				rows_ = rows;
				cols_ = cols;
			}
			// will call the type-T default constructor
			data_ = new T[rows * cols];
			if (retain) {
				std::cout << "flag" << "\n";
				// retain old elements
				int min_rows, min_cols;
				{
					min_rows = old_rows < rows ? old_rows : rows;
					min_cols = old_cols < cols ? old_cols : cols;
				}
				for (int i = 0; i < min_rows; i++) {
					for (int j = 0; j < min_cols; j++) {
						// it requires type-T class to have operator=
						data_[(i * cols) + j] = old_data[(i * old_cols) + j];
					}
				}
			}
			// release previous memory
			if (old_data) {
				delete[] old_data;
				old_data = nullptr;
			}
		}

		template <typename F>
		void mapAll(F& fn) const {
			for (int i = 0; i < rows_; i++) {
				for (int j = 0; j < cols_; j++) {
					fn(operator()(i, j));
				}
			}
		}

	private:
		/// \brief .
		///
		/// \warning The creation of new data array requires the type-T class to have a default constructor.
		void deepCopy(const Grid& src) {
			int total = src.rows_ * src.cols_;
			// release existing data
			if (data_) {
				delete[] data_;
				data_ = nullptr;
			}
			data_ = new T[total];
			for (int i = 0; i < total; ++i) {
				// it requires type-T class to have operator=
				data_[i] = src.data_[i];
			}
			rows_ = src.rows_;
			cols_ = src.cols_;
		}

		///< \brief the address of the data array
		T* data_;
		int rows_, cols_;
	};
}

#endif	// DJA_GRID_H_