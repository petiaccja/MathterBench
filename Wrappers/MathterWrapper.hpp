#pragma once

#include "../Libraries/Mathter/Matrix.hpp"
#include "../Libraries/Mathter/Quaternion.hpp"
#include "../Libraries/Mathter/Vector.hpp"

#include <random>

class MathterWrapper {
public:
	//----------------------------------
	// Types
	//----------------------------------
	using Vec2 = mathter::Vector<float, 2>;
	using Vec3 = mathter::Vector<float, 3>;
	using Vec4 = mathter::Vector<float, 4>;

	using Mat22 = mathter::Matrix<float, 2, 2>;
	using Mat33 = mathter::Matrix<float, 3, 3>;
	using Mat44 = mathter::Matrix<float, 4, 4>;

	using Quat = mathter::Quaternion<float>;

	//----------------------------------
	// Vector binary operators
	//----------------------------------
	template <class Vec>
	static Vec MulVV(const Vec& lhs, const Vec& rhs);

	template <class Vec>
	static Vec AddVV(const Vec& lhs, const Vec& rhs);

	template <class Vec>
	static Vec DivVV(const Vec& lhs, const Vec& rhs);

	template <class Vec>
	static float Dot(const Vec& lhs, const Vec& rhs);

	template <class Vec>
	static Vec Cross(const Vec& lhs, const Vec& rhs);

	//----------------------------------
	// Vector unary operators
	//----------------------------------
	template <class Vec>
	static float NormV(const Vec& arg);

	template <class Vec>
	static Vec NormalizeV(const Vec& arg);

	//----------------------------------
	// Matrix binary operators
	//----------------------------------
	template <class MatL, class MatR>
	static auto MulMM(const MatL& lhs, const MatR& rhs);

	template <class Mat>
	static auto AddMM(const Mat& lhs, const Mat& rhs);


	//----------------------------------
	// Matrix unary operators
	//----------------------------------
	template <class Mat>
	static auto Transpose(const Mat& arg);

	template <class Mat>
	static Mat Inverse(const Mat& arg);

	template <class Mat>
	static auto Determinant(const Mat& arg);

	template <class Mat>
	static auto Trace(const Mat& arg);

	template <class Mat>
	static Mat Pow3M(const Mat& arg);

	//----------------------------------
	// Extra
	//----------------------------------
	template <class Mat>
	static auto SingularValueDec(const Mat& arg);

	//----------------------------------
	// Vector-matrix multiplication
	//----------------------------------
	template <class Vec, class Mat>
	static auto MulVM(const Vec& v, const Mat& m);

	//----------------------------------
	// Utility
	//----------------------------------
	template <class Vec>
	static void RandomVec(Vec& vec);

	template <class Mat>
	static void RandomMat(Mat& mat);


	//----------------------------------
	// Members
	//----------------------------------
	static std::mt19937 rne;
	static std::uniform_real_distribution<float> rng;
};


inline std::mt19937 MathterWrapper::rne;
inline std::uniform_real_distribution<float> MathterWrapper::rng(-1, 1);


template <class Vec>
Vec MathterWrapper::MulVV(const Vec& lhs, const Vec& rhs) {
	return lhs * rhs;
}

template <class Vec>
Vec MathterWrapper::AddVV(const Vec& lhs, const Vec& rhs) {
	return lhs + rhs;
}

template <class Vec>
Vec MathterWrapper::DivVV(const Vec& lhs, const Vec& rhs) {
	return lhs / rhs;
}

template <class Vec>
float MathterWrapper::Dot(const Vec& lhs, const Vec& rhs) {
	return mathter::Dot(lhs, rhs);
}

template <class Vec>
Vec MathterWrapper::Cross(const Vec& lhs, const Vec& rhs) {
	return mathter::Cross(lhs, rhs);
}

template <class Vec>
float MathterWrapper::NormV(const Vec& arg) {
	return Length(arg);
}

template <class Vec>
Vec MathterWrapper::NormalizeV(const Vec& arg) {
	return Normalize(arg);
}

template <class MatL, class MatR>
auto MathterWrapper::MulMM(const MatL& lhs, const MatR& rhs) {
	return lhs * rhs;
}

template <class Mat>
auto MathterWrapper::AddMM(const Mat& lhs, const Mat& rhs) {
	return lhs + rhs;
}

template <class Mat>
auto MathterWrapper::Transpose(const Mat& arg) {
	return mathter::Transpose(arg);
}

template <class Mat>
Mat MathterWrapper::Inverse(const Mat& arg) {
	return mathter::Inverse(arg);
}

template <class Mat>
auto MathterWrapper::Determinant(const Mat& arg) {
	return mathter::Determinant(arg);
}

template <class Mat>
auto MathterWrapper::Trace(const Mat& arg) {
	return mathter::Trace(arg);
}

template <class Mat>
Mat MathterWrapper::Pow3M(const Mat& arg) {
	return arg * arg * arg;
}

template <class Mat>
auto MathterWrapper::SingularValueDec(const Mat& arg) {
	return DecomposeSVD(arg);
}

template <class Vec, class Mat>
auto MathterWrapper::MulVM(const Vec& v, const Mat& m) {
	return v * m;
}

template <class Vec>
void MathterWrapper::RandomVec(Vec& vec) {
	for (auto& v : vec) {
		v = rng(rne);
	}
}

template <class Mat>
void MathterWrapper::RandomMat(Mat& mat) {
	for (int j = 0; j < mat.ColumnCount(); ++j) {
		for (int i = 0; i < mat.RowCount(); ++i) {
			mat(i, j) = rng(rne);
		}
	}
}
