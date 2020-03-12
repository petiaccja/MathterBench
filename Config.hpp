#pragma once

#include "Kernel.hpp"

#include <string>

struct Result {
	std::string name;
	Measurement timing;
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
	
	auto pow3mat44 = &Wrapper::template Pow3M<typename Wrapper::Mat44>;


	std::vector<Result> results = {
		{ "Vec2 * Vec2", MeasureBinaryKernel(mulVec2, initVec2, initVec2) },
		{ "Vec3 * Vec3", MeasureBinaryKernel(mulVec3, initVec3, initVec3) },
		{ "Vec4 * Vec4", MeasureBinaryKernel(mulVec4, initVec4, initVec4) },

		{ "Vec2 + Vec2", MeasureBinaryKernel(addVec2, initVec2, initVec2) },
		{ "Vec3 + Vec3", MeasureBinaryKernel(addVec3, initVec3, initVec3) },
		{ "Vec4 + Vec4", MeasureBinaryKernel(addVec4, initVec4, initVec4) },

		{ "Vec2 / Vec2", MeasureBinaryKernel(divVec2, initVec2, initVec2) },
		{ "Vec3 / Vec3", MeasureBinaryKernel(divVec3, initVec3, initVec3) },
		{ "Vec4 / Vec4", MeasureBinaryKernel(divVec4, initVec4, initVec4) },


		{ "Mat22 * Mat22", MeasureBinaryKernel(mulMat22, initMat22, initMat22) },
		{ "Mat33 * Mat33", MeasureBinaryKernel(mulMat33, initMat33, initMat33) },
		{ "Mat44 * Mat44", MeasureBinaryKernel(mulMat44, initMat44, initMat44) },

		{ "Mat22 + Mat22", MeasureBinaryKernel(addMat22, initMat22, initMat22) },
		{ "Mat33 + Mat33", MeasureBinaryKernel(addMat33, initMat33, initMat33) },
		{ "Mat44 + Mat44", MeasureBinaryKernel(addMat44, initMat44, initMat44) },


		{ "Vec2 . Vec2", MeasureBinaryKernel(dot2, initVec2, initVec2) },
		{ "Vec3 . Vec3", MeasureBinaryKernel(dot3, initVec3, initVec3) },
		{ "Vec4 . Vec4", MeasureBinaryKernel(dot4, initVec4, initVec4) },
		{ "Vec3 x Vec3", MeasureBinaryKernel(cross, initVec3, initVec3) },


		{ "norm(Vec2)", MeasureUnaryKernel(norm2, initVec2) },
		{ "norm(Vec3)", MeasureUnaryKernel(norm3, initVec3) },
		{ "norm(Vec4)", MeasureUnaryKernel(norm4, initVec4) },

		{ "normalize(Vec2)", MeasureUnaryKernel(normalize2, initVec2) },
		{ "normalize(Vec3)", MeasureUnaryKernel(normalize3, initVec3) },
		{ "normalize(Vec4)", MeasureUnaryKernel(normalize4, initVec4) },


		{ "determinant(Mat22)", MeasureUnaryKernel(determinant2, initMat22) },
		{ "determinant(Mat33)", MeasureUnaryKernel(determinant3, initMat33) },
		{ "determinant(Mat44)", MeasureUnaryKernel(determinant4, initMat44) },

		{ "inverse(Mat22)", MeasureUnaryKernel(inverse2, initMat22) },
		{ "inverse(Mat33)", MeasureUnaryKernel(inverse3, initMat33) },
		{ "inverse(Mat44)", MeasureUnaryKernel(inverse4, initMat44) },

		{ "trace(Mat22)", MeasureUnaryKernel(trace2, initMat22) },
		{ "trace(Mat33)", MeasureUnaryKernel(trace3, initMat33) },
		{ "trace(Mat44)", MeasureUnaryKernel(trace4, initMat44) },

		{ "transpose(Mat22)", MeasureUnaryKernel(transpose22, initMat22) },
		{ "transpose(Mat33)", MeasureUnaryKernel(transpose33, initMat33) },
		{ "transpose(Mat44)", MeasureUnaryKernel(transpose44, initMat44) },
		
		{ "Mat44^3", MeasureUnaryKernel(pow3mat44, initMat44) },
	};

	return results;
}
