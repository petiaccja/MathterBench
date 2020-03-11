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

**Calculations**: An array for each of the left hand operand, right hand operand, and result is preallocated. The operation is executed in sequence for each element of the arrays. This is repeated several times.

# Tables

### MSVC 19

Clock cycles per operation:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|16.540|8.883|
|Vec3 * Vec3|7.235|11.477|
|Vec4 * Vec4|7.049|7.125|
|Vec2 + Vec2|7.614|8.632|
|Vec3 + Vec3|6.943|14.031|
|Vec4 + Vec4|7.055|6.707|
|Vec2 / Vec2|14.226|8.865|
|Vec3 / Vec3|6.942|11.608|
|Vec4 / Vec4|7.021|6.801|
|Mat22 * Mat22|35.542|193.698|
|Mat33 * Mat33|33.863|480.133|
|Mat44 * Mat44|45.160|31.393|
|Mat22 + Mat22|31.228|6.871|
|Mat33 + Mat33|20.346|13.826|
|Mat44 + Mat44|27.113|28.994|
|Vec2 . Vec2|6.651|11.111|
|Vec3 . Vec3|5.734|12.309|
|Vec4 . Vec4|6.650|9.587|
|Vec3 x Vec3|27.726|23.312|
|norm(Vec2)|14.858|9.478|
|norm(Vec3)|14.441|7.785|
|norm(Vec4)|14.377|6.689|
|normalize(Vec2)|24.228|20.437|
|normalize(Vec3)|24.471|35.863|
|normalize(Vec4)|25.366|13.804|
|determinant(Mat22)|185.463|6.692|
|determinant(Mat33)|311.563|13.330|
|determinant(Mat44)|632.230|36.075|
|inverse(Mat22)|438.344|24.035|
|inverse(Mat33)|1198.225|108.170|
|inverse(Mat44)|2457.401|128.114|
|trace(Mat22)|6.597|7.400|
|trace(Mat33)|6.290|10.773|
|trace(Mat44)|8.864|13.760|
|transpose(Mat22)|25.965|28.514|
|transpose(Mat33)|37.438|33.057|
|transpose(Mat44)|46.616|37.226|

Relative times:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|1.862|1.000|
|Vec3 * Vec3|1.000|1.586|
|Vec4 * Vec4|1.000|1.011|
|Vec2 + Vec2|1.000|1.134|
|Vec3 + Vec3|1.000|2.021|
|Vec4 + Vec4|1.052|1.000|
|Vec2 / Vec2|1.605|1.000|
|Vec3 / Vec3|1.000|1.672|
|Vec4 / Vec4|1.032|1.000|
|Mat22 * Mat22|1.000|5.450|
|Mat33 * Mat33|1.000|14.179|
|Mat44 * Mat44|1.439|1.000|
|Mat22 + Mat22|4.545|1.000|
|Mat33 + Mat33|1.472|1.000|
|Mat44 + Mat44|1.000|1.069|
|Vec2 . Vec2|1.000|1.670|
|Vec3 . Vec3|1.000|2.147|
|Vec4 . Vec4|1.000|1.442|
|Vec3 x Vec3|1.189|1.000|
|norm(Vec2)|1.568|1.000|
|norm(Vec3)|1.855|1.000|
|norm(Vec4)|2.150|1.000|
|normalize(Vec2)|1.185|1.000|
|normalize(Vec3)|1.000|1.466|
|normalize(Vec4)|1.838|1.000|
|determinant(Mat22)|27.714|1.000|
|determinant(Mat33)|23.372|1.000|
|determinant(Mat44)|17.525|1.000|
|inverse(Mat22)|18.238|1.000|
|inverse(Mat33)|11.077|1.000|
|inverse(Mat44)|19.181|1.000|
|trace(Mat22)|1.000|1.122|
|trace(Mat33)|1.000|1.713|
|trace(Mat44)|1.000|1.552|
|transpose(Mat22)|1.000|1.098|
|transpose(Mat33)|1.133|1.000|
|transpose(Mat44)|1.252|1.000|



## GCC 9

TODO

## Clang 9

Clock cycles per operation:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|20.233|9.075|
|Vec3 * Vec3|7.257|14.418|
|Vec4 * Vec4|7.992|9.569|
|Vec2 + Vec2|23.016|9.187|
|Vec3 + Vec3|7.262|12.809|
|Vec4 + Vec4|10.717|7.682|
|Vec2 / Vec2|22.652|8.743|
|Vec3 / Vec3|7.885|13.753|
|Vec4 / Vec4|8.308|8.733|
|Mat22 * Mat22|14.296|19.332|
|Mat33 * Mat33|26.839|56.623|
|Mat44 * Mat44|40.470|58.262|
|Mat22 + Mat22|12.302|18.746|
|Mat33 + Mat33|18.324|20.632|
|Mat44 + Mat44|32.082|26.609|
|Vec2 . Vec2|12.433|8.760|
|Vec3 . Vec3|15.800|10.342|
|Vec4 . Vec4|12.787|11.790|
|Vec3 x Vec3|38.264|19.814|
|norm(Vec2)|9.562|9.552|
|norm(Vec3)|10.087|7.886|
|norm(Vec4)|12.039|6.726|
|normalize(Vec2)|32.798|20.972|
|normalize(Vec3)|23.150|29.883|
|normalize(Vec4)|26.389|14.166|
|determinant(Mat22)|134.329|6.525|
|determinant(Mat33)|292.913|12.740|
|determinant(Mat44)|433.465|33.808|
|inverse(Mat22)|247.847|25.516|
|inverse(Mat33)|978.178|55.277|
|inverse(Mat44)|2203.311|74.222|
|trace(Mat22)|5.714|6.772|
|trace(Mat33)|6.658|5.598|
|trace(Mat44)|7.702|7.450|
|transpose(Mat22)|7.599|7.667|
|transpose(Mat33)|39.613|29.337|
|transpose(Mat44)|52.284|34.322|

Relative times:

| |Mathter|Eigen|
|:---|---:|---:|
|Vec2 * Vec2|2.229|1.000|
|Vec3 * Vec3|1.000|1.987|
|Vec4 * Vec4|1.000|1.197|
|Vec2 + Vec2|2.505|1.000|
|Vec3 + Vec3|1.000|1.764|
|Vec4 + Vec4|1.395|1.000|
|Vec2 / Vec2|2.591|1.000|
|Vec3 / Vec3|1.000|1.744|
|Vec4 / Vec4|1.000|1.051|
|Mat22 * Mat22|1.000|1.352|
|Mat33 * Mat33|1.000|2.110|
|Mat44 * Mat44|1.000|1.440|
|Mat22 + Mat22|1.000|1.524|
|Mat33 + Mat33|1.000|1.126|
|Mat44 + Mat44|1.206|1.000|
|Vec2 . Vec2|1.419|1.000|
|Vec3 . Vec3|1.528|1.000|
|Vec4 . Vec4|1.085|1.000|
|Vec3 x Vec3|1.931|1.000|
|norm(Vec2)|1.001|1.000|
|norm(Vec3)|1.279|1.000|
|norm(Vec4)|1.790|1.000|
|normalize(Vec2)|1.564|1.000|
|normalize(Vec3)|1.000|1.291|
|normalize(Vec4)|1.863|1.000|
|determinant(Mat22)|20.588|1.000|
|determinant(Mat33)|22.992|1.000|
|determinant(Mat44)|12.821|1.000|
|inverse(Mat22)|9.713|1.000|
|inverse(Mat33)|17.696|1.000|
|inverse(Mat44)|29.685|1.000|
|trace(Mat22)|1.000|1.185|
|trace(Mat33)|1.189|1.000|
|trace(Mat44)|1.034|1.000|
|transpose(Mat22)|1.000|1.009|
|transpose(Mat33)|1.350|1.000|
|transpose(Mat44)|1.523|1.000|