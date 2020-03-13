# Introduction

A benchmark to compare mathematics libraries for game development. Below you can find tables with the performance of various operation math operations. You can use the tables to compare the performance of the libraries or to check if a library supports a feature.

Libraries included:

- [Mathter](https://github.com/petiaccja/Mathter)
- [Eigen](http://eigen.tuxfamily.org)
- [GLM](https://github.com/g-truc/glm)

Planning to include:

- [CML](https://github.com/demianmnave/CML/wiki/The-Configurable-Math-Library)
- [mathfu](https://github.com/google/mathfu)
- ... anything else? Make an issue to let me know.

**DISCLAIMER**: Mathter is my own library. The comparison is not rigged in any way to favor Mathter (or any other library for that matter).

**GLM**: GLM_FORCE_INTRINSICS is defined before including any headers. Let me know if I'm missing anything.

**Flags**: march=native on GCC & Clang; /arch:AVX on MSVC. MSVC will fail if your CPU does not support AVX, you can change the CMakeLists.txt to fix it.

# Method

**Compiler flags**: CMake default for Release builds (without debug info).

**Test machine**: My computer with an Intel Xeon 1230v2 4C/8T @3.3GHz. I used Windows 10.

**Interference**: The process is run with admin priviliges and sets itself to real-time priority on both Windows and Linux. On Windows, it additionally restricts processor affinity to the first core to prevent rescheduling.

**Calculations**: There are two operations tested: binary and unary. For example, dot product and cross product are binary, matrix inverse is unary. Two or three arrays are prealloacted, which contain the one or two operands and the results. (I.e. the first operands are in their own contiguous array, and so on.) The array sizes range from 200 to 1000, and they are filled with random data. To do a *repetition*, the unary or binary operation is executed for each pair or triplet in the arrays. On the same dataset (without initializing the arrays again), a few hundred *repetitions* are executed. The amount of time it takes to do the repetitions is measured with ```chrono::high_resolution_clock```, and the number of cycles is measured with ```RDTSC```. This procedure is executed 500 times to collect 500 samples, and the fastest of the samples is selected to be shown in the tables below. The per-operation values are calculated as ```total_time / (arrayLen*repCount)```. The time for the random initialization is excluded.

**Limitations**: The number in the tables represent instruction throughput, not latency. This is because many of the same operations are executed in a sequence, so the CPU may overlap these operations. Measuring operations in isolation would be very difficult and probably not accurate. Nonetheless, in a real application usually you do multiple of these operations right after the other, so the primary interest is throughput.

# Tables

### MSVC 19

Clock cycles per operation:

| |Mathter|Eigen|GLM|
|:---|---:|---:|---:|
|Vec2 * Vec2|7.566|8.518|18.344|
|Vec3 * Vec3|6.662|10.936|20.293|
|Vec4 * Vec4|6.697|6.617|23.854|
|Vec2 + Vec2|6.621|8.277|18.343|
|Vec3 + Vec3|6.753|10.658|20.291|
|Vec4 + Vec4|6.637|6.442|23.852|
|Vec2 / Vec2|13.201|8.507|18.343|
|Vec3 / Vec3|6.684|10.951|20.237|
|Vec4 / Vec4|6.644|6.623|26.154|
|Mat22 * Mat22|7.569|299.100|25.685|
|Mat33 * Mat33|19.399|701.188|42.379|
|Mat44 * Mat44|26.765|28.648|78.082|
|Mat22 + Mat22|23.589|6.434|36.688|
|Mat33 + Mat33|18.022|12.826|28.451|
|Mat44 + Mat44|19.639|20.444|35.945|
|Vec2 . Vec2|7.561|6.435|6.432|
|Vec3 . Vec3|6.622|7.162|7.153|
|Vec4 . Vec4|6.620|6.436|8.535|
|Vec3 x Vec3|7.571|13.628|22.068|
|norm(Vec2)|15.125|7.352|14.707|
|norm(Vec3)|14.186|6.308|13.802|
|norm(Vec4)|14.348|6.437|15.328|
|normalize(Vec2)|23.101|19.479|28.082|
|normalize(Vec3)|21.578|26.443|31.354|
|normalize(Vec4)|22.176|12.905|31.558|
|determinant(Mat22)|6.622|6.434|6.618|
|determinant(Mat33)|7.909|10.176|9.829|
|determinant(Mat44)|48.065|28.655|28.722|
|inverse(Mat22)|15.950|22.012|28.464|
|inverse(Mat33)|35.786|76.008|40.805|
|inverse(Mat44)|122.641|220.747|119.920|
|trace(Mat22)|5.675|5.518|N/A|
|trace(Mat33)|5.629|5.517|N/A|
|trace(Mat44)|6.620|5.521|N/A|
|transpose(Mat22)|21.697|21.091|25.482|
|transpose(Mat33)|26.416|26.979|24.220|
|transpose(Mat44)|33.033|31.246|30.213|
|Mat44^3|49.267|59.609|156.504|

Relative times:

| |Mathter|Eigen|GLM|
|:---|---:|---:|---:|
|Vec2 * Vec2|1.000|1.126|2.425|
|Vec3 * Vec3|1.000|1.642|3.046|
|Vec4 * Vec4|1.012|1.000|3.605|
|Vec2 + Vec2|1.000|1.250|2.770|
|Vec3 + Vec3|1.000|1.578|3.005|
|Vec4 + Vec4|1.030|1.000|3.702|
|Vec2 / Vec2|1.552|1.000|2.156|
|Vec3 / Vec3|1.000|1.638|3.028|
|Vec4 / Vec4|1.003|1.000|3.949|
|Mat22 * Mat22|1.000|39.515|3.393|
|Mat33 * Mat33|1.000|36.146|2.185|
|Mat44 * Mat44|1.000|1.070|2.917|
|Mat22 + Mat22|3.666|1.000|5.702|
|Mat33 + Mat33|1.405|1.000|2.218|
|Mat44 + Mat44|1.000|1.041|1.830|
|Vec2 . Vec2|1.175|1.000|1.000|
|Vec3 . Vec3|1.000|1.081|1.080|
|Vec4 . Vec4|1.029|1.000|1.326|
|Vec3 x Vec3|1.000|1.800|2.915|
|norm(Vec2)|2.057|1.000|2.000|
|norm(Vec3)|2.249|1.000|2.188|
|norm(Vec4)|2.229|1.000|2.381|
|normalize(Vec2)|1.186|1.000|1.442|
|normalize(Vec3)|1.000|1.225|1.453|
|normalize(Vec4)|1.718|1.000|2.445|
|determinant(Mat22)|1.029|1.000|1.029|
|determinant(Mat33)|1.000|1.287|1.243|
|determinant(Mat44)|1.677|1.000|1.002|
|inverse(Mat22)|1.000|1.380|1.785|
|inverse(Mat33)|1.000|2.124|1.140|
|inverse(Mat44)|1.023|1.841|1.000|
|trace(Mat22)|1.029|1.000|N/A|
|trace(Mat33)|1.020|1.000|N/A|
|trace(Mat44)|1.199|1.000|N/A|
|transpose(Mat22)|1.029|1.000|1.208|
|transpose(Mat33)|1.091|1.114|1.000|
|transpose(Mat44)|1.093|1.034|1.000|
|Mat44^3|1.000|1.210|3.177|



## GCC 9

TODO

## Clang 9

Clock cycles per operation:

| |Mathter|Eigen|GLM|
|:---|---:|---:|---:|
|Vec2 * Vec2|19.265|8.375|19.260|
|Vec3 * Vec3|7.523|12.119|19.806|
|Vec4 * Vec4|7.485|7.353|7.396|
|Vec2 + Vec2|19.260|8.394|19.260|
|Vec3 + Vec3|8.422|12.106|18.800|
|Vec4 + Vec4|8.417|7.353|7.388|
|Vec2 / Vec2|19.258|8.205|19.263|
|Vec3 / Vec3|7.355|12.101|19.257|
|Vec4 / Vec4|7.352|7.355|7.412|
|Mat22 * Mat22|8.285|23.209|27.168|
|Mat33 * Mat33|18.482|36.822|43.942|
|Mat44 * Mat44|27.946|26.413|32.336|
|Mat22 + Mat22|8.274|8.408|7.395|
|Mat33 + Mat33|17.330|14.708|14.888|
|Mat44 + Mat44|17.926|19.175|20.566|
|Vec2 . Vec2|6.617|7.353|7.353|
|Vec3 . Vec3|6.435|7.369|7.484|
|Vec4 . Vec4|7.352|6.434|7.356|
|Vec3 x Vec3|9.191|14.969|21.425|
|norm(Vec2)|7.356|6.435|6.596|
|norm(Vec3)|7.216|7.364|7.250|
|norm(Vec4)|7.973|6.462|8.087|
|normalize(Vec2)|22.009|20.061|22.638|
|normalize(Vec3)|14.845|26.847|22.323|
|normalize(Vec4)|15.596|13.573|17.384|
|determinant(Mat22)|5.517|5.368|5.371|
|determinant(Mat33)|9.326|12.006|11.689|
|determinant(Mat44)|42.481|29.955|25.246|
|inverse(Mat22)|23.840|22.932|24.760|
|inverse(Mat33)|29.423|49.052|41.517|
|inverse(Mat44)|105.909|170.865|140.095|
|trace(Mat22)|5.517|5.471|N/A|
|trace(Mat33)|5.576|5.549|N/A|
|trace(Mat44)|7.370|6.468|N/A|
|transpose(Mat22)|7.222|6.435|6.434|
|transpose(Mat33)|25.714|12.699|9.548|
|transpose(Mat44)|32.145|31.290|33.024|
|Mat44^3|49.456|44.291|58.138|

Relative times:

| |Mathter|Eigen|GLM|
|:---|---:|---:|---:|
|Vec2 * Vec2|2.300|1.000|2.300|
|Vec3 * Vec3|1.000|1.611|2.633|
|Vec4 * Vec4|1.018|1.000|1.006|
|Vec2 + Vec2|2.295|1.000|2.295|
|Vec3 + Vec3|1.000|1.438|2.232|
|Vec4 + Vec4|1.145|1.000|1.005|
|Vec2 / Vec2|2.347|1.000|2.348|
|Vec3 / Vec3|1.000|1.645|2.618|
|Vec4 / Vec4|1.000|1.000|1.008|
|Mat22 * Mat22|1.000|2.801|3.279|
|Mat33 * Mat33|1.000|1.992|2.378|
|Mat44 * Mat44|1.058|1.000|1.224|
|Mat22 + Mat22|1.119|1.137|1.000|
|Mat33 + Mat33|1.178|1.000|1.012|
|Mat44 + Mat44|1.000|1.070|1.147|
|Vec2 . Vec2|1.000|1.111|1.111|
|Vec3 . Vec3|1.000|1.145|1.163|
|Vec4 . Vec4|1.143|1.000|1.143|
|Vec3 x Vec3|1.000|1.629|2.331|
|norm(Vec2)|1.143|1.000|1.025|
|norm(Vec3)|1.000|1.021|1.005|
|norm(Vec4)|1.234|1.000|1.251|
|normalize(Vec2)|1.097|1.000|1.128|
|normalize(Vec3)|1.000|1.808|1.504|
|normalize(Vec4)|1.149|1.000|1.281|
|determinant(Mat22)|1.028|1.000|1.000|
|determinant(Mat33)|1.000|1.287|1.253|
|determinant(Mat44)|1.683|1.187|1.000|
|inverse(Mat22)|1.040|1.000|1.080|
|inverse(Mat33)|1.000|1.667|1.411|
|inverse(Mat44)|1.000|1.613|1.323|
|trace(Mat22)|1.008|1.000|N/A|
|trace(Mat33)|1.005|1.000|N/A|
|trace(Mat44)|1.139|1.000|N/A|
|transpose(Mat22)|1.123|1.000|1.000|
|transpose(Mat33)|2.693|1.330|1.000|
|transpose(Mat44)|1.027|1.000|1.055|
|Mat44^3|1.117|1.000|1.313|