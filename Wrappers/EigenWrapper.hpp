#pragma once

#include "../Libraries/Eigen/Dense"
#include "../Libraries/Eigen/LU" 

#include <random>

class EigenWrapper {
public:
	//----------------------------------
	// Types
	//----------------------------------
	using Vec2 = Eigen::Vector2f;
	using Vec3 = Eigen::Vector3f;
	using Vec4 = Eigen::Vector4f;

	using Mat22 = Eigen::Matrix<float, 2, 2>;
	using Mat33 = Eigen::Matrix<float, 3, 3>;
	using Mat44 = Eigen::Matrix<float, 4, 4>;

	using Quat = Eigen::Quaternion<float>;

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

	template <class Scalar, int RowsL, int Match, int ColsR, int Options, int MaxRowsL, int MaxColsL, int MaxRowsR, int MaxColsR>
	static auto MulMM_Impl(const Eigen::Matrix<Scalar, RowsL, Match, Options, MaxRowsL, MaxColsL>& lhs, const Eigen::Matrix<Scalar, Match, ColsR, Options, MaxRowsR, MaxColsR>& rhs)
		-> Eigen::Matrix<Scalar, RowsL, ColsR>;

	template <class Mat>
	static Mat AddMM(const Mat& lhs, const Mat& rhs);

	//----------------------------------
	// Matrix unary operators
	//----------------------------------
	template <class Mat>
	static auto Transpose(const Mat& arg);
	
	template <class Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
	static auto Transpose_Impl(const Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>& arg)
		-> Eigen::Matrix<Scalar, Cols, Rows, Options>;

	template <class Mat>
	static Mat Inverse(const Mat& arg);

	template <class Mat>
	static auto Determinant(const Mat& arg);

	template <class Mat>
	static auto Trace(const Mat& arg);

	template <class Mat>
	static Mat Pow3M(const Mat& arg);

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


inline std::mt19937 EigenWrapper::rne;
inline std::uniform_real_distribution<float> EigenWrapper::rng(-1, 1);


template <class Vec>
Vec EigenWrapper::MulVV(const Vec& lhs, const Vec& rhs) {
	return lhs.cwiseProduct(rhs);
}

template <class Vec>
Vec EigenWrapper::AddVV(const Vec& lhs, const Vec& rhs) {
	return lhs.cwiseProduct(rhs);
}

template <class Vec>
Vec EigenWrapper::DivVV(const Vec& lhs, const Vec& rhs) {
	return lhs.cwiseProduct(rhs);
}

template <class Vec>
float EigenWrapper::Dot(const Vec& lhs, const Vec& rhs) {
	return lhs.dot(rhs);
}

template <class Vec>
Vec EigenWrapper::Cross(const Vec& lhs, const Vec& rhs) {
	return lhs.cross(rhs);
}

template <class Vec>
float EigenWrapper::NormV(const Vec& arg) {
	return arg.norm();
}

template <class Vec>
Vec EigenWrapper::NormalizeV(const Vec& arg) {
	return arg.normalized();
}

template <class MatL, class MatR>
auto EigenWrapper::MulMM(const MatL& lhs, const MatR& rhs) {
	return MulMM_Impl(lhs, rhs);
}

template <class Scalar, int RowsL, int Match, int ColsR, int Options, int MaxRowsL, int MaxColsL, int MaxRowsR, int MaxColsR>
auto EigenWrapper::MulMM_Impl(const Eigen::Matrix<Scalar, RowsL, Match, Options, MaxRowsL, MaxColsL>& lhs, const Eigen::Matrix<Scalar, Match, ColsR, Options, MaxRowsR, MaxColsR>& rhs)
	-> Eigen::Matrix<Scalar, RowsL, ColsR> {
	return lhs * rhs;
}

template <class Mat>
Mat EigenWrapper::AddMM(const Mat& lhs, const Mat& rhs) {
	return lhs + rhs;
}

template <class Mat>
auto EigenWrapper::Transpose(const Mat& arg) {
	return Transpose_Impl(arg);
}

template <class Scalar, int Rows, int Cols, int Options, int MaxRows, int MaxCols>
auto EigenWrapper::Transpose_Impl(const Eigen::Matrix<Scalar, Rows, Cols, Options, MaxRows, MaxCols>& arg) -> Eigen::Matrix<Scalar, Cols, Rows, Options> {
	return arg.transpose();
}

template <class Mat>
Mat EigenWrapper::Inverse(const Mat& arg) {
	return arg.inverse();
}

template <class Mat>
auto EigenWrapper::Determinant(const Mat& arg) {
	return arg.determinant();
}

template <class Mat>
auto EigenWrapper::Trace(const Mat& arg) {
	return arg.trace();
}

template <class Mat>
Mat EigenWrapper::Pow3M(const Mat& arg) {
	return arg * arg * arg;
}

template <class Vec>
void EigenWrapper::RandomVec(Vec& vec) {
	return RandomMat(vec);
}

template <class Mat>
void EigenWrapper::RandomMat(Mat& mat) {
	for (int j = 0; j < mat.cols(); ++j) {
		for (int i = 0; i < mat.rows(); ++i) {
			mat(i, j) = rng(rne);
		}
	}
}
