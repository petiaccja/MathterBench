# Introduction

A benchmark to compare mathematics libraries for game development. Below you can find tables with the performance of various operation math operations. You can use the tables to compare the performance of the libraries or to check if a library supports a feature.

Libraries included:

- [Mathter](https://github.com/petiaccja/Mathter)
- [Eigen](http://eigen.tuxfamily.org)

Planning to include:

- [CML](https://github.com/demianmnave/CML/wiki/The-Configurable-Math-Library)
- [GLM](https://github.com/g-truc/glm)
- [mathfu](https://github.com/google/mathfu)
- ... anything else? Make an issue to let me know.

**DISCLAIMER**: Mathter is my own library. The comparison is not rigged in any way to favor Mathter (or any other library for that matter).

# Method

**Compiler flags**: CMake default for Release builds (without debug info).

**Test machine**: My computer with an Intel Xeon 1230v2 4C/8T @3.3GHz. I used Windows 10.

**Interference**: The process is run with admin priviliges and sets itself to real-time priority on both Windows and Linux. On Windows, it additionally restricts processor affinity to the first core to prevent rescheduling.

**Calculations**: There are two operations tested: binary and unary. For example, dot product and cross product are binary, matrix inverse is unary. Two or three arrays are prealloacted, which contain the one or two operands and the results. (I.e. the first operands are in their own contiguous array, and so on.) The array sizes range from 200 to 1000, and they are filled with random data. To do a *repetition*, the unary or binary operation is executed for each pair or triplet in the arrays. On the same dataset (without initializing the arrays again), a few hundred *repetitions* are executed. The amount of time it takes to do the repetitions is measured with ```chrono::high_resolution_clock```, and the number of cycles is measured with ```RDTSC```. This procedure is executed 500 times to collect 500 samples, and the fastest of the samples is selected to be shown in the tables below. The per-operation values are calculated as ```total_time / (arrayLen*repCount)```. The time for the random initialization is excluded.

**Limitations**: The number in the tables represent instruction throughput, not latency. This is because many of the same operations are executed in a sequence, so the CPU may overlap these operations. Measuring operations in isolation would be very difficult and probably not accurate. Nonetheless, in a real application usually you do multiple of these operations right after the other, so the primary interest is throughput.

# Tables

### MSVC 19

Clock cycles per operation:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|7.562|7.873|
|Vec3 * Vec3|6.507|10.700|
|Vec4 * Vec4|6.441|6.434|
|Vec2 + Vec2|6.439|7.887|
|Vec3 + Vec3|6.716|10.985|
|Vec4 + Vec4|6.672|6.434|
|Vec2 / Vec2|13.201|7.646|
|Vec3 / Vec3|6.767|10.845|
|Vec4 / Vec4|6.596|6.434|
|Mat22 * Mat22|7.393|174.224|
|Mat33 * Mat33|18.546|352.986|
|Mat44 * Mat44|29.357|30.137|
|Mat22 + Mat22|23.591|6.434|
|Mat33 + Mat33|17.584|13.262|
|Mat44 + Mat44|18.500|16.598|
|Vec2 . Vec2|5.369|6.620|
|Vec3 . Vec3|6.434|6.450|
|Vec4 . Vec4|7.356|5.518|
|Vec3 x Vec3|7.563|12.711|
|norm(Vec2)|13.798|6.448|
|norm(Vec3)|13.797|7.351|
|norm(Vec4)|13.922|6.441|
|normalize(Vec2)|23.308|19.287|
|normalize(Vec3)|21.468|32.022|
|normalize(Vec4)|23.078|12.902|
|determinant(Mat22)|6.618|6.435|
|determinant(Mat33)|7.967|10.170|
|determinant(Mat44)|43.830|31.560|
|inverse(Mat22)|15.731|22.014|
|inverse(Mat33)|36.390|63.819|
|inverse(Mat44)|124.970|69.545|
|trace(Mat22)|5.518|5.518|
|trace(Mat33)|5.517|6.615|
|trace(Mat44)|7.351|7.350|
|transpose(Mat22)|21.696|21.092|
|transpose(Mat33)|25.684|27.768|
|transpose(Mat44)|32.115|33.023|
|Mat44^3|49.932|64.721|

Relative times:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|1.000|1.041|
|Vec3 * Vec3|1.000|1.644|
|Vec4 * Vec4|1.001|1.000|
|Vec2 + Vec2|1.000|1.225|
|Vec3 + Vec3|1.000|1.636|
|Vec4 + Vec4|1.037|1.000|
|Vec2 / Vec2|1.727|1.000|
|Vec3 / Vec3|1.000|1.603|
|Vec4 / Vec4|1.025|1.000|
|Mat22 * Mat22|1.000|23.565|
|Mat33 * Mat33|1.000|19.033|
|Mat44 * Mat44|1.000|1.027|
|Mat22 + Mat22|3.667|1.000|
|Mat33 + Mat33|1.326|1.000|
|Mat44 + Mat44|1.115|1.000|
|Vec2 . Vec2|1.000|1.233|
|Vec3 . Vec3|1.000|1.002|
|Vec4 . Vec4|1.333|1.000|
|Vec3 x Vec3|1.000|1.681|
|norm(Vec2)|2.140|1.000|
|norm(Vec3)|1.877|1.000|
|norm(Vec4)|2.161|1.000|
|normalize(Vec2)|1.208|1.000|
|normalize(Vec3)|1.000|1.492|
|normalize(Vec4)|1.789|1.000|
|determinant(Mat22)|1.028|1.000|
|determinant(Mat33)|1.000|1.277|
|determinant(Mat44)|1.389|1.000|
|inverse(Mat22)|1.000|1.399|
|inverse(Mat33)|1.000|1.754|
|inverse(Mat44)|1.797|1.000|
|trace(Mat22)|1.000|1.000|
|trace(Mat33)|1.000|1.199|
|trace(Mat44)|1.000|1.000|
|transpose(Mat22)|1.029|1.000|
|transpose(Mat33)|1.000|1.081|
|transpose(Mat44)|1.000|1.028|
|Mat44^3|1.000|1.296|



## GCC 9

TODO

## Clang 9

Clock cycles per operation:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|19.260|8.464|
|Vec3 * Vec3|7.353|12.430|
|Vec4 * Vec4|7.353|7.046|
|Vec2 + Vec2|19.263|8.736|
|Vec3 + Vec3|7.355|12.444|
|Vec4 + Vec4|7.161|6.535|
|Vec2 / Vec2|19.265|8.401|
|Vec3 / Vec3|7.354|12.063|
|Vec4 / Vec4|7.355|7.202|
|Mat22 * Mat22|8.312|8.494|
|Mat33 * Mat33|22.987|35.525|
|Mat44 * Mat44|31.144|31.819|
|Mat22 + Mat22|7.634|6.663|
|Mat33 + Mat33|17.499|14.637|
|Mat44 + Mat44|21.793|18.780|
|Vec2 . Vec2|7.364|7.564|
|Vec3 . Vec3|7.354|7.375|
|Vec4 . Vec4|7.354|7.361|
|Vec3 x Vec3|8.520|14.907|
|norm(Vec2)|7.352|6.426|
|norm(Vec3)|7.562|7.384|
|norm(Vec4)|8.324|6.522|
|normalize(Vec2)|22.633|19.295|
|normalize(Vec3)|15.053|27.102|
|normalize(Vec4)|15.600|13.391|
|determinant(Mat22)|5.519|5.525|
|determinant(Mat33)|9.657|12.673|
|determinant(Mat44)|43.814|30.957|
|inverse(Mat22)|23.840|24.520|
|inverse(Mat33)|35.573|51.379|
|inverse(Mat44)|120.971|69.648|
|trace(Mat22)|5.675|5.519|
|trace(Mat33)|5.596|6.433|
|trace(Mat44)|6.457|6.455|
|transpose(Mat22)|7.360|6.437|
|transpose(Mat33)|25.714|26.053|
|transpose(Mat44)|33.022|32.322|
|Mat44^3|52.354|48.769|

Relative times:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|2.276|1.000|
|Vec3 * Vec3|1.000|1.690|
|Vec4 * Vec4|1.044|1.000|
|Vec2 + Vec2|2.205|1.000|
|Vec3 + Vec3|1.000|1.692|
|Vec4 + Vec4|1.096|1.000|
|Vec2 / Vec2|2.293|1.000|
|Vec3 / Vec3|1.000|1.640|
|Vec4 / Vec4|1.021|1.000|
|Mat22 * Mat22|1.000|1.022|
|Mat33 * Mat33|1.000|1.545|
|Mat44 * Mat44|1.000|1.022|
|Mat22 + Mat22|1.146|1.000|
|Mat33 + Mat33|1.196|1.000|
|Mat44 + Mat44|1.160|1.000|
|Vec2 . Vec2|1.000|1.027|
|Vec3 . Vec3|1.000|1.003|
|Vec4 . Vec4|1.000|1.001|
|Vec3 x Vec3|1.000|1.750|
|norm(Vec2)|1.144|1.000|
|norm(Vec3)|1.024|1.000|
|norm(Vec4)|1.276|1.000|
|normalize(Vec2)|1.173|1.000|
|normalize(Vec3)|1.000|1.800|
|normalize(Vec4)|1.165|1.000|
|determinant(Mat22)|1.000|1.001|
|determinant(Mat33)|1.000|1.312|
|determinant(Mat44)|1.415|1.000|
|inverse(Mat22)|1.000|1.028|
|inverse(Mat33)|1.000|1.444|
|inverse(Mat44)|1.737|1.000|
|trace(Mat22)|1.028|1.000|
|trace(Mat33)|1.000|1.150|
|trace(Mat44)|1.000|1.000|
|transpose(Mat22)|1.143|1.000|
|transpose(Mat33)|1.000|1.013|
|transpose(Mat44)|1.022|1.000|
|Mat44^3|1.074|1.000|