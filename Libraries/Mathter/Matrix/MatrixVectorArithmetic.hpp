#pragma once

#include "MatrixImpl.hpp"

namespace mathter {


//------------------------------------------------------------------------------
// Matrix-vector arithmetic
//------------------------------------------------------------------------------

// v*M
template <class Vt, class Mt, int Vd, int Mcol, eMatrixOrder Morder, bool Packed>
auto operator*(const Vector<Vt, Vd, Packed>& vec, const Matrix<Mt, Vd, Mcol, Morder, eMatrixLayout::ROW_MAJOR, Packed>& mat) {
	using Rt = traits::MatMulElemT<Vt, Mt>;
	Vector<Rt, Mcol, Packed> result;

	result = vec(0) * mat.stripes[0];
	for (int i = 1; i < Vd; ++i) {
		result += vec(i) * mat.stripes[i];
	}
	return result;
}

template <class Vt, class Mt, int Vd, int Mcol, eMatrixOrder Morder, bool Packed>
auto operator*(const Vector<Vt, Vd, Packed>& vec, const Matrix<Mt, Vd, Mcol, Morder, eMatrixLayout::COLUMN_MAJOR, Packed>& mat) {
	using Rt = traits::MatMulElemT<Vt, Mt>;
	Vector<Rt, Mcol, Packed> result;

	for (int i = 0; i < Mcol; ++i) {
		result(i) = Dot(vec, mat.stripes[i]);
	}
	return result;
}

// (v|1)*M
template <class Vt, class Mt, int Vd, eMatrixLayout Mlayout, eMatrixOrder Morder, bool Packed>
auto operator*(const Vector<Vt, Vd, Packed>& vec, const Matrix<Mt, Vd + 1, Vd, Morder, Mlayout, Packed>& mat) {
	return (vec | Vt(1)) * mat;
}

template <class Vt, class Mt, int Vd, eMatrixLayout Mlayout, eMatrixOrder Morder, bool Packed>
auto operator*(const Vector<Vt, Vd, Packed>& vec, const Matrix<Mt, Vd + 1, Vd + 1, Morder, Mlayout, Packed>& mat) {
	using Rt = traits::MatMulElemT<Vt, Mt>;
	auto res = (vec | Vt(1)) * mat;
	res /= res(res.Dimension() - 1);
	return Vector<Rt, Vd, Packed>(res);
}

// M*v
template <class Vt, class Mt, int Vd, int Mrow, eMatrixOrder Morder, bool Packed>
auto operator*(const Matrix<Mt, Mrow, Vd, Morder, eMatrixLayout::ROW_MAJOR, Packed>& mat, const Vector<Vt, Vd, Packed>& vec) {
	using Rt = traits::MatMulElemT<Vt, Mt>;
	Vector<Rt, Mrow, Packed> result;

	for (int i = 0; i < Mrow; ++i) {
		result(i) = Dot(vec, mat.stripes[i]);
	}
	return result;
}

template <class Vt, class Mt, int Vd, int Mrow, eMatrixOrder Morder, bool Packed>
auto operator*(const Matrix<Mt, Mrow, Vd, Morder, eMatrixLayout::COLUMN_MAJOR, Packed>& mat, const Vector<Vt, Vd, Packed>& vec) {
	using Rt = traits::MatMulElemT<Vt, Mt>;
	Vector<Rt, Mrow, Packed> result;

	result = vec(0) * mat.stripes[0];
	for (int i = 1; i < Vd; ++i) {
		result += vec(i) * mat.stripes[i];
	}
	return result;
}


// M*(v|1)
template <class Vt, class Mt, int Vd, eMatrixLayout Mlayout, eMatrixOrder Morder, bool Packed>
auto operator*(const Matrix<Mt, Vd, Vd + 1, Morder, Mlayout, Packed>& mat, const Vector<Vt, Vd, Packed>& vec) {
	return mat * (vec | Vt(1));
}

template <class Vt, class Mt, int Vd, eMatrixLayout Mlayout, eMatrixOrder Morder, bool Packed>
auto operator*(const Matrix<Mt, Vd + 1, Vd + 1, Morder, Mlayout, Packed>& mat, const Vector<Vt, Vd, Packed>& vec) {
	using Rt = traits::MatMulElemT<Vt, Mt>;
	auto res = mat * (vec | Vt(1));
	res /= res(res.Dimension() - 1);
	return (Vector<Rt, Vd, Packed>)res;
}

// v*=M
template <class Vt, class Mt, int Vd, eMatrixOrder Morder, eMatrixLayout Layout, bool Packed>
Vector<Vt, Vd, Packed>& operator*=(Vector<Vt, Vd, Packed>& vec, const Matrix<Mt, Vd, Vd, Morder, Layout, Packed>& mat) {
	vec = vec * mat;
	return vec;
}

template <class Vt, class Mt, int Vd, eMatrixOrder Morder, eMatrixLayout Layout, bool Packed>
Vector<Vt, Vd, Packed>& operator*=(Vector<Vt, Vd, Packed>& vec, const Matrix<Mt, Vd + 1, Vd, Morder, Layout, Packed>& mat) {
	vec = vec * mat;
	return vec;
}

template <class Vt, class Mt, int Vd, eMatrixOrder Morder, eMatrixLayout Layout, bool Packed>
Vector<Vt, Vd, Packed>& operator*=(Vector<Vt, Vd, Packed>& vec, const Matrix<Mt, Vd + 1, Vd + 1, Morder, Layout, Packed>& mat) {
	vec = vec * mat;
	return vec;
}


} // namespace mathter