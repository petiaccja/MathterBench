#pragma once

#include "Kernel.hpp"

#include <string>

struct Result {
	std::string name;
	Timing timing;
};

template <class Wrapper>
std::vector<Result> Config() {
	// Initializers
	auto initVec2 = &Wrapper::template RandomVec<typename Wrapper::Vec2>;
	auto initVec3 = &Wrapper::template RandomVec<typename Wrapper::Vec3>;
	auto initVec4 = &Wrapper::template RandomVec<typename Wrapper::Vec4>;

	auto initMat22 = &Wrapper::template RandomMat<typename Wrapper::Mat22>;
	auto initMat33 = &Wrapper::template RandomMat<typename Wrapper::Mat33>;
	auto initMat44 = &Wrapper::template RandomMat<typename Wrapper::Mat44>;

	// Test: vector elementwise
	auto mulVec2 = &Wrapper::template MulVV<typename Wrapper::Vec2>;
	auto mulVec3 = &Wrapper::template MulVV<typename Wrapper::Vec3>;
	auto mulVec4 = &Wrapper::template MulVV<typename Wrapper::Vec4>;

	auto addVec2 = &Wrapper::template AddVV<typename Wrapper::Vec2>;
	auto addVec3 = &Wrapper::template AddVV<typename Wrapper::Vec3>;
	auto addVec4 = &Wrapper::template AddVV<typename Wrapper::Vec4>;

	auto divVec2 = &Wrapper::template DivVV<typename Wrapper::Vec2>;
	auto divVec3 = &Wrapper::template DivVV<typename Wrapper::Vec3>;
	auto divVec4 = &Wrapper::template DivVV<typename Wrapper::Vec4>;

	// Test: matrix-matrix
	auto mulMat22 = &Wrapper::template MulMM<typename Wrapper::Mat22, typename Wrapper::Mat22>;
	auto mulMat33 = &Wrapper::template MulMM<typename Wrapper::Mat33, typename Wrapper::Mat33>;
	auto mulMat44 = &Wrapper::template MulMM<typename Wrapper::Mat44, typename Wrapper::Mat44>;

	auto addMat22 = &Wrapper::template AddMM<typename Wrapper::Mat22>;
	auto addMat33 = &Wrapper::template AddMM<typename Wrapper::Mat33>;
	auto addMat44 = &Wrapper::template AddMM<typename Wrapper::Mat44>;

	// Test: dot & cross
	auto dot2 = &Wrapper::template Dot<typename Wrapper::Vec2>;
	auto dot3 = &Wrapper::template Dot<typename Wrapper::Vec3>;
	auto dot4 = &Wrapper::template Dot<typename Wrapper::Vec4>;
	auto cross = &Wrapper::template Cross<typename Wrapper::Vec3>;

	// Test: vector norm, normalize
	auto norm2 = &Wrapper::template NormV<typename Wrapper::Vec2>;
	auto norm3 = &Wrapper::template NormV<typename Wrapper::Vec3>;
	auto norm4 = &Wrapper::template NormV<typename Wrapper::Vec4>;

	auto normalize2 = &Wrapper::template NormalizeV<typename Wrapper::Vec2>;
	auto normalize3 = &Wrapper::template NormalizeV<typename Wrapper::Vec3>;
	auto normalize4 = &Wrapper::template NormalizeV<typename Wrapper::Vec4>;

	// Test: matrix functions
	auto determinant2 = &Wrapper::template Determinant<typename Wrapper::Mat22>;
	auto determinant3 = &Wrapper::template Determinant<typename Wrapper::Mat33>;
	auto determinant4 = &Wrapper::template Determinant<typename Wrapper::Mat44>;

	auto inverse2 = &Wrapper::template Inverse<typename Wrapper::Mat22>;
	auto inverse3 = &Wrapper::template Inverse<typename Wrapper::Mat33>;
	auto inverse4 = &Wrapper::template Inverse<typename Wrapper::Mat44>;

	auto trace2 = &Wrapper::template Trace<typename Wrapper::Mat22>;
	auto trace3 = &Wrapper::template Trace<typename Wrapper::Mat33>;
	auto trace4 = &Wrapper::template Trace<typename Wrapper::Mat44>;

	auto transpose22 = &Wrapper::template Transpose<typename Wrapper::Mat22>;
	auto transpose33 = &Wrapper::template Transpose<typename Wrapper::Mat33>;
	auto transpose44 = &Wrapper::template Transpose<typename Wrapper::Mat44>;


	constexpr size_t SIZE_SIMPLE = 1000;
	constexpr size_t REPS_SIMPLE = 1000;

	std::vector<Result> results = {
		{ "Vec2 * Vec2", BinaryKernel(mulVec2, initVec2, initVec2, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Vec3 * Vec3", BinaryKernel(mulVec3, initVec3, initVec3, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Vec4 * Vec4", BinaryKernel(mulVec4, initVec4, initVec4, SIZE_SIMPLE, REPS_SIMPLE) },

		{ "Vec2 + Vec2", BinaryKernel(addVec2, initVec2, initVec2, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Vec3 + Vec3", BinaryKernel(addVec3, initVec3, initVec3, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Vec4 + Vec4", BinaryKernel(addVec4, initVec4, initVec4, SIZE_SIMPLE, REPS_SIMPLE) },

		{ "Vec2 / Vec2", BinaryKernel(divVec2, initVec2, initVec2, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Vec3 / Vec3", BinaryKernel(divVec3, initVec3, initVec3, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Vec4 / Vec4", BinaryKernel(divVec4, initVec4, initVec4, SIZE_SIMPLE, REPS_SIMPLE) },


		{ "Mat22 * Mat22", BinaryKernel(mulMat22, initMat22, initMat22, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Mat33 * Mat33", BinaryKernel(mulMat33, initMat33, initMat33, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Mat44 * Mat44", BinaryKernel(mulMat44, initMat44, initMat44, SIZE_SIMPLE, REPS_SIMPLE) },

		{ "Mat22 + Mat22", BinaryKernel(addMat22, initMat22, initMat22, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Mat33 + Mat33", BinaryKernel(addMat33, initMat33, initMat33, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Mat44 + Mat44", BinaryKernel(addMat44, initMat44, initMat44, SIZE_SIMPLE, REPS_SIMPLE) },


		{ "Vec2 . Vec2", BinaryKernel(dot2, initVec2, initVec2, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Vec3 . Vec3", BinaryKernel(dot3, initVec3, initVec3, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Vec4 . Vec4", BinaryKernel(dot4, initVec4, initVec4, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "Vec3 x Vec3", BinaryKernel(cross, initVec3, initVec3, SIZE_SIMPLE, REPS_SIMPLE) },


		{ "norm(Vec2)", UnaryKernel(norm2, initVec2, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "norm(Vec3)", UnaryKernel(norm3, initVec3, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "norm(Vec4)", UnaryKernel(norm4, initVec4, SIZE_SIMPLE, REPS_SIMPLE) },

		{ "normalize(Vec2)", UnaryKernel(normalize2, initVec2, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "normalize(Vec3)", UnaryKernel(normalize3, initVec3, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "normalize(Vec4)", UnaryKernel(normalize4, initVec4, SIZE_SIMPLE, REPS_SIMPLE) },


		{ "determinant(Mat22)", UnaryKernel(determinant2, initMat22, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "determinant(Mat33)", UnaryKernel(determinant3, initMat33, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "determinant(Mat44)", UnaryKernel(determinant4, initMat44, SIZE_SIMPLE, REPS_SIMPLE) },

		{ "inverse(Mat22)", UnaryKernel(inverse2, initMat22, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "inverse(Mat33)", UnaryKernel(inverse3, initMat33, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "inverse(Mat44)", UnaryKernel(inverse4, initMat44, SIZE_SIMPLE, REPS_SIMPLE) },

		{ "trace(Mat22)", UnaryKernel(trace2, initMat22, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "trace(Mat33)", UnaryKernel(trace3, initMat33, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "trace(Mat44)", UnaryKernel(trace4, initMat44, SIZE_SIMPLE, REPS_SIMPLE) },

		{ "transpose(Mat22)", UnaryKernel(transpose22, initMat22, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "transpose(Mat33)", UnaryKernel(transpose33, initMat33, SIZE_SIMPLE, REPS_SIMPLE) },
		{ "transpose(Mat44)", UnaryKernel(transpose44, initMat44, SIZE_SIMPLE, REPS_SIMPLE) },
	};

	return results;
}
