//==============================================================================
// This software is distributed under The Unlicense. 
// For more information, please refer to <http://unlicense.org/>
//==============================================================================

#pragma once

#include "Definitions.hpp"
#include <cmath>
#include <type_traits>


namespace mathter::traits {


	// Vector properties
	template <class VectorT>
	class VectorTraitsHelper {};

	template <class T_, int Dim_, bool Packed_>
	class VectorTraitsHelper<Vector<T_, Dim_, Packed_>> {
	public:
		using Type = T_;
		static constexpr int Dim = Dim_;
		static constexpr bool Packed = Packed_;
	};

	template <class VectorT>
	class VectorTraits : public VectorTraitsHelper<typename std::decay<VectorT>::type> {};


	// Matrix properties
	template <class MatrixT>
	class MatrixTraitsHelper {};

	template <class T_, int Rows_, int Columns_, eMatrixOrder Order_, eMatrixLayout Layout_, bool Packed_>
	class MatrixTraitsHelper<Matrix<T_, Rows_, Columns_, Order_, Layout_, Packed_>> {
	public:
		using Type = T_;
		static constexpr int Rows = Rows_;
		static constexpr int Columns = Columns_;
		static constexpr eMatrixOrder Order = Order_;
		static constexpr eMatrixLayout Layout = Layout_;
		static constexpr bool Packed = Packed_;
	};

	template <class MatrixT>
	class MatrixTraits : public MatrixTraitsHelper<typename std::decay<MatrixT>::type> {};


	template <eMatrixLayout Layout>
	class OppositeLayout {
	public:
		static constexpr eMatrixLayout value = (Layout == eMatrixLayout::ROW_MAJOR ? eMatrixLayout::COLUMN_MAJOR : eMatrixLayout::ROW_MAJOR);
	};


	// Common utility
	template <class T, class U>
	using MatMulElemT = decltype(T() * U() + T() + U());

	

	// Template metaprogramming utilities
	template <template <class> class Cond, class... T>
	struct All;

	template <template <class> class Cond, class Head, class... Rest>
	struct All<Cond, Head, Rest...> {
		static constexpr bool value = Cond<Head>::value && All<Cond, Rest...>::value;
	};

	template <template <class> class Cond>
	struct All<Cond> {
		static constexpr bool value = true;
	};


	template <template <class> class Cond, class... T>
	struct Any;

	template <template <class> class Cond, class Head, class... Rest>
	struct Any<Cond, Head, Rest...> {
		static constexpr bool value = Cond<Head>::value || Any<Cond, Rest...>::value;
	};

	template <template <class> class Cond>
	struct Any<Cond> {
		static constexpr bool value = false;
	};



	template <class... T>
	struct TypeList {};

	template <class Tl1, class Tl2>
	struct ConcatTypeList;

	template <class... T, class... U>
	struct ConcatTypeList<TypeList<T...>, TypeList<U...>> {
		using type = TypeList<T..., U...>;
	};

	template <class T, int N>
	struct RepeatType {
		using type = typename std::conditional<N <= 0, TypeList<>, typename ConcatTypeList<TypeList<T>, typename RepeatType<T, N - 1>::type>::type>::type;
	};


	// Decide if type is Scalar, Vector or Matrix.
	template <class Arg>
	struct IsVector {
		static constexpr bool value = false;
	};
	template <class T, int Dim, bool Packed>
	struct IsVector<Vector<T, Dim, Packed>> {
		static constexpr bool value = true;
	};
	template <class Arg>
	struct NotVector {
		static constexpr bool value = !IsVector<Arg>::value;
	};

	template <class Arg>
	struct IsSwizzle {
		static constexpr bool value = false;
	};
	template <class T, int... Indices>
	struct IsSwizzle<Swizzle<T, Indices...>> {
		static constexpr bool value = true;
	};
	template <class Arg>
	struct NotSwizzle {
		static constexpr bool value = !IsSwizzle<Arg>::value;
	};

	template <class Arg>
	struct IsVectorOrSwizzle {
		static constexpr bool value = IsVector<Arg>::value || IsSwizzle<Arg>::value;
	};

	template <class T>
	struct IsMatrix {
		static constexpr bool value = false;
	};
	template <class T, int Rows, int Columns, eMatrixOrder Order, eMatrixLayout Layout, bool Packed>
	struct IsMatrix<Matrix<T, Rows, Columns, Order, Layout, Packed>> {
		static constexpr bool value = true;
	};
	template <class T>
	struct NotMatrix {
		static constexpr bool value = !IsMatrix<T>::value;
	};

	template <class T>
	struct IsSubmatrix {
		static constexpr bool value = false;
	};
	template <class M, int Rows, int Columns>
	struct IsSubmatrix<SubmatrixHelper<M, Rows, Columns>> {
		static constexpr bool value = true;
	};
	template <class T>
	struct NotSubmatrix {
		static constexpr bool value = !IsSubmatrix<T>::value;
	};

	template <class Arg>
	struct IsQuaternion {
		static constexpr bool value = false;
	};
	template <class T, bool Packed>
	struct IsQuaternion<Quaternion<T, Packed>> {
		static constexpr bool value = true;
	};
	template <class Arg>
	struct NotQuaternion {
		static constexpr bool value = !IsQuaternion<Arg>::value;
	};


	template <class T>
	struct IsScalar {
		static constexpr bool value = !IsMatrix<T>::value && !IsVector<T>::value && !IsSwizzle<T>::value && !IsQuaternion<T>::value && !IsSubmatrix<T>::value;
	};

	// Dimension of an argument (add dynamically sized vectors later).
	template <class U, int Along = 0>
	struct DimensionOf {
		static constexpr int value = 1;
	};
	template <class T, int Dim, bool Packed>
	struct DimensionOf<Vector<T, Dim, Packed>, 0> {
		static constexpr int value = Dim;
	};
	template <class T, int... Indices>
	struct DimensionOf<Swizzle<T, Indices...>> {
		static constexpr int value = sizeof...(Indices);
	};

	// Sum dimensions of arguments.
	template <class... Rest>
	struct SumDimensions;

	template <class Head, class... Rest>
	struct SumDimensions<Head, Rest...> {
		static constexpr int value = DimensionOf<Head>::value > 0 ? DimensionOf<Head>::value + SumDimensions<Rest...>::value : DYNAMIC;
	};

	template <>
	struct SumDimensions<> {
		static constexpr int value = 0;
	};

	// Weather vector uses SIDM.
	template <class VectorDataT>
	struct HasSimd {
		template <class U>
		static std::false_type test(...) { return {}; }

		template <class U>
		static decltype(U::simd) test(int) { return {}; }


		static constexpr bool value = !std::is_same<std::false_type, decltype(test<VectorDataT>(0))>::value;
	};
}