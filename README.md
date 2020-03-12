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
|Vec2 * Vec2|6.259|7.640|
|Vec3 * Vec3|6.337|10.554|
|Vec4 * Vec4|6.352|6.260|
|Vec2 + Vec2|6.265|7.451|
|Vec3 + Vec3|6.332|10.546|
|Vec4 + Vec4|6.327|6.260|
|Vec2 / Vec2|12.487|7.461|
|Vec3 / Vec3|6.352|10.416|
|Vec4 / Vec4|6.366|6.265|
|Mat22 * Mat22|7.180|166.093|
|Mat33 * Mat33|16.918|338.400|
|Mat44 * Mat44|27.828|29.014|
|Mat22 + Mat22|22.317|6.261|
|Mat33 + Mat33|16.862|12.680|
|Mat44 + Mat44|17.583|16.499|
|Vec2 . Vec2|5.368|6.260|
|Vec3 . Vec3|6.261|6.268|
|Vec4 . Vec4|7.152|5.369|
|Vec3 x Vec3|7.165|12.334|
|norm(Vec2)|13.415|7.152|
|norm(Vec3)|13.419|7.222|
|norm(Vec4)|14.311|7.152|
|normalize(Vec2)|22.673|18.761|
|normalize(Vec3)|20.851|31.131|
|normalize(Vec4)|22.372|12.555|
|determinant(Mat22)|110.332|7.153|
|determinant(Mat33)|207.674|9.988|
|determinant(Mat44)|349.262|30.830|
|inverse(Mat22)|364.728|21.416|
|inverse(Mat33)|833.125|64.698|
|inverse(Mat44)|1880.083|65.716|
|trace(Mat22)|6.258|6.258|
|trace(Mat33)|6.258|5.368|
|trace(Mat44)|5.369|5.370|
|transpose(Mat22)|20.527|20.521|
|transpose(Mat33)|24.989|31.728|
|transpose(Mat44)|31.245|31.236|
|Mat44^3|48.097|61.315|

Relative times:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|1.000|1.221|
|Vec3 * Vec3|1.000|1.665|
|Vec4 * Vec4|1.015|1.000|
|Vec2 + Vec2|1.000|1.189|
|Vec3 + Vec3|1.000|1.665|
|Vec4 + Vec4|1.011|1.000|
|Vec2 / Vec2|1.674|1.000|
|Vec3 / Vec3|1.000|1.640|
|Vec4 / Vec4|1.016|1.000|
|Mat22 * Mat22|1.000|23.131|
|Mat33 * Mat33|1.000|20.002|
|Mat44 * Mat44|1.000|1.043|
|Mat22 + Mat22|3.565|1.000|
|Mat33 + Mat33|1.330|1.000|
|Mat44 + Mat44|1.066|1.000|
|Vec2 . Vec2|1.000|1.166|
|Vec3 . Vec3|1.000|1.001|
|Vec4 . Vec4|1.332|1.000|
|Vec3 x Vec3|1.000|1.721|
|norm(Vec2)|1.876|1.000|
|norm(Vec3)|1.858|1.000|
|norm(Vec4)|2.001|1.000|
|normalize(Vec2)|1.209|1.000|
|normalize(Vec3)|1.000|1.493|
|normalize(Vec4)|1.782|1.000|
|determinant(Mat22)|15.425|1.000|
|determinant(Mat33)|20.791|1.000|
|determinant(Mat44)|11.329|1.000|
|inverse(Mat22)|17.031|1.000|
|inverse(Mat33)|12.877|1.000|
|inverse(Mat44)|28.609|1.000|
|trace(Mat22)|1.000|1.000|
|trace(Mat33)|1.166|1.000|
|trace(Mat44)|1.000|1.000|
|transpose(Mat22)|1.000|1.000|
|transpose(Mat33)|1.000|1.270|
|transpose(Mat44)|1.000|1.000|
|Mat44^3|1.000|1.275|



## GCC 9

TODO

## Clang 9

Clock cycles per operation:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|18.740|8.210|
|Vec3 * Vec3|7.254|11.811|
|Vec4 * Vec4|7.257|6.761|
|Vec2 + Vec2|18.741|8.172|
|Vec3 + Vec3|7.158|11.804|
|Vec4 + Vec4|7.258|6.312|
|Vec2 / Vec2|18.734|8.245|
|Vec3 / Vec3|7.165|11.788|
|Vec4 / Vec4|7.288|6.738|
|Mat22 * Mat22|7.923|8.150|
|Mat33 * Mat33|21.796|34.728|
|Mat44 * Mat44|30.289|30.268|
|Mat22 + Mat22|7.261|6.655|
|Mat33 + Mat33|16.817|13.974|
|Mat44 + Mat44|17.389|18.618|
|Vec2 . Vec2|7.157|7.154|
|Vec3 . Vec3|7.162|7.154|
|Vec4 . Vec4|7.152|7.153|
|Vec3 x Vec3|8.054|14.461|
|norm(Vec2)|7.156|6.252|
|norm(Vec3)|7.151|7.174|
|norm(Vec4)|8.086|6.425|
|normalize(Vec2)|21.410|18.738|
|normalize(Vec3)|14.237|25.782|
|normalize(Vec4)|15.161|12.636|
|determinant(Mat22)|100.888|6.263|
|determinant(Mat33)|192.117|12.495|
|determinant(Mat44)|266.781|30.068|
|inverse(Mat22)|189.279|23.194|
|inverse(Mat33)|809.793|49.459|
|inverse(Mat44)|1592.698|67.626|
|trace(Mat22)|5.368|5.368|
|trace(Mat33)|5.376|6.258|
|trace(Mat44)|6.275|6.271|
|transpose(Mat22)|7.153|6.348|
|transpose(Mat33)|24.986|25.310|
|transpose(Mat44)|31.242|31.309|
|Mat44^3|49.491|47.438|

Relative times:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|2.282|1.000|
|Vec3 * Vec3|1.000|1.628|
|Vec4 * Vec4|1.073|1.000|
|Vec2 + Vec2|2.293|1.000|
|Vec3 + Vec3|1.000|1.649|
|Vec4 + Vec4|1.150|1.000|
|Vec2 / Vec2|2.272|1.000|
|Vec3 / Vec3|1.000|1.645|
|Vec4 / Vec4|1.082|1.000|
|Mat22 * Mat22|1.000|1.029|
|Mat33 * Mat33|1.000|1.593|
|Mat44 * Mat44|1.001|1.000|
|Mat22 + Mat22|1.091|1.000|
|Mat33 + Mat33|1.203|1.000|
|Mat44 + Mat44|1.000|1.071|
|Vec2 . Vec2|1.000|1.000|
|Vec3 . Vec3|1.001|1.000|
|Vec4 . Vec4|1.000|1.000|
|Vec3 x Vec3|1.000|1.796|
|norm(Vec2)|1.144|1.000|
|norm(Vec3)|1.000|1.003|
|norm(Vec4)|1.258|1.000|
|normalize(Vec2)|1.143|1.000|
|normalize(Vec3)|1.000|1.811|
|normalize(Vec4)|1.200|1.000|
|determinant(Mat22)|16.109|1.000|
|determinant(Mat33)|15.376|1.000|
|determinant(Mat44)|8.873|1.000|
|inverse(Mat22)|8.161|1.000|
|inverse(Mat33)|16.373|1.000|
|inverse(Mat44)|23.551|1.000|
|trace(Mat22)|1.000|1.000|
|trace(Mat33)|1.000|1.164|
|trace(Mat44)|1.001|1.000|
|transpose(Mat22)|1.127|1.000|
|transpose(Mat33)|1.000|1.013|
|transpose(Mat44)|1.000|1.002|
|Mat44^3|1.043|1.000|