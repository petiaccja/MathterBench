#pragma once

#define GLM_FORCE_INTRINSICS
#include "../Libraries/glm/glm.hpp"

#include <random>
#include <stdexcept>

class GLMWrapper {
public:
	//----------------------------------
	// Types
	//----------------------------------
	using Vec2 = glm::vec2;
	using Vec3 = glm::vec3;
	using Vec4 = glm::vec4;

	using Mat22 = glm::mat2x2;
	using Mat33 = glm::mat3x3;
	using Mat44 = glm::mat4x4;

	using Quat = glm::quat;

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


inline std::mt19937 GLMWrapper::rne;
inline std::uniform_real_distribution<float> GLMWrapper::rng(-1, 1);


template <class Vec>
Vec GLMWrapper::MulVV(const Vec& lhs, const Vec& rhs) {
	return lhs * rhs;
}

template <class Vec>
Vec GLMWrapper::AddVV(const Vec& lhs, const Vec& rhs) {
	return lhs + rhs;
}

template <class Vec>
Vec GLMWrapper::DivVV(const Vec& lhs, const Vec& rhs) {
	return lhs / rhs;
}

template <class Vec>
float GLMWrapper::Dot(const Vec& lhs, const Vec& rhs) {
	return glm::dot(lhs, rhs);
}

template <class Vec>
Vec GLMWrapper::Cross(const Vec& lhs, const Vec& rhs) {
	return glm::cross(lhs, rhs);
}

template <class Vec>
float GLMWrapper::NormV(const Vec& arg) {
	return glm::length(arg);
}

template <class Vec>
Vec GLMWrapper::NormalizeV(const Vec& arg) {
	return glm::normalize(arg);
}

template <class MatL, class MatR>
auto GLMWrapper::MulMM(const MatL& lhs, const MatR& rhs) {
	return lhs * rhs;
}

template <class Mat>
auto GLMWrapper::AddMM(const Mat& lhs, const Mat& rhs) {
	return lhs + rhs;
}

template <class Mat>
auto GLMWrapper::Transpose(const Mat& arg) {
	return glm::transpose(arg);
}

template <class Mat>
Mat GLMWrapper::Inverse(const Mat& arg) {
	return glm::inverse(arg);
}

template <class Mat>
auto GLMWrapper::Determinant(const Mat& arg) {
	return glm::determinant(arg);
}

template <class Mat>
auto GLMWrapper::Trace(const Mat& arg) {
	throw std::invalid_argument("not supported");
}

template <class Mat>
Mat GLMWrapper::Pow3M(const Mat& arg) {
	return arg * arg * arg;
}

template <class Vec>
void GLMWrapper::RandomVec(Vec& vec) {
	for (size_t i = 0; i < sizeof(vec)/sizeof(vec.x); ++i) {
		vec[i] = rng(rne);
	}
}

template <class Mat>
void GLMWrapper::RandomMat(Mat& mat) {
	using Scalar = std::decay_t<decltype(mat[0][0])>;
	auto p = reinterpret_cast<Scalar*>(&mat);
	for (size_t i = 0; i < sizeof(mat)/sizeof(Scalar); ++i) {		
		p[i] = rng(rne);		
	}
}
