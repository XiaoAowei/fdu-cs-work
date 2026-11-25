#include "matrix.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 

const char *matrix_status_str(MatrixStatus status) {
  switch (status) {
    case MATRIX_OK:
      return "success";
    case MATRIX_ERR_NULL_PTR:
      return "null pointer";
    case MATRIX_ERR_INVALID_ARG:
      return "invalid argument";
    case MATRIX_ERR_NO_MEMORY:
      return "out of memory";
    case MATRIX_ERR_INDEX:
      return "index out of range";
    case MATRIX_ERR_SHAPE:
      return "shape mismatch";
    case MATRIX_ERR_SINGULAR:
      return "singular matrix";
  }
  return "unknown status";
}

static MatrixStatus check_matrix(const Matrix *A) {
  return (!A || !A->data) ? MATRIX_ERR_NULL_PTR : MATRIX_OK;
}

static MatrixStatus check_same_shape(const Matrix *A, const Matrix *B) {
  if (check_matrix(A) != MATRIX_OK || check_matrix(B) != MATRIX_OK) {
    return MATRIX_ERR_NULL_PTR;
  }
  if (A->rows != B->rows || A->cols != B->cols) {
    return MATRIX_ERR_SHAPE;
  }
  return MATRIX_OK;
}

MatrixStatus matrix_create(Matrix *A, size_t rows, size_t cols) {
  if (!A) {
    return MATRIX_ERR_NULL_PTR;
  }
  if (A->data || !rows || !cols) {
    return MATRIX_ERR_INVALID_ARG;
  }
  if (rows > SIZE_MAX / cols || rows * cols > SIZE_MAX / sizeof(double)) {
    return MATRIX_ERR_INVALID_ARG;
  }
  double *data = calloc(rows * cols, sizeof(*data));
  if (!data) {
    return MATRIX_ERR_NO_MEMORY;
  }
  A->rows = rows;
  A->cols = cols;
  A->data = data;
  return MATRIX_OK;
}

void matrix_free(Matrix *A) {
  if (!A) {
    return;
  }
  free(A->data);
  *A = (Matrix){0};
}

MatrixStatus matrix_set(Matrix *A, size_t i, size_t j, double value) {
  if (check_matrix(A) != MATRIX_OK) {
    return MATRIX_ERR_NULL_PTR;
  }
  if (i >= A->rows || j >= A->cols) {
    return MATRIX_ERR_INDEX;
  }
  A->data[i * A->cols + j] = value;
  return MATRIX_OK;
}

MatrixStatus matrix_get(const Matrix *A, size_t i, size_t j, double *value) {
  if (check_matrix(A) != MATRIX_OK || !value) {
    return MATRIX_ERR_NULL_PTR;
  }
  if (i >= A->rows || j >= A->cols) {
    return MATRIX_ERR_INDEX;
  }
  *value = A->data[i * A->cols + j];
  return MATRIX_OK;
}

MatrixStatus matrix_print(const Matrix *A) {
  if (check_matrix(A) != MATRIX_OK) {
    return MATRIX_ERR_NULL_PTR;
  }
  for (size_t i = 0; i < A->rows; ++i) {
    for (size_t j = 0; j < A->cols; ++j) {
      if (j) {
        putchar(' ');
      }
      printf("%g", A->data[i * A->cols + j]);
    }
    putchar('\n');
  }
  return MATRIX_OK;
}

MatrixStatus matrix_deep_copy(const Matrix *A, Matrix *B) {
  MatrixStatus status = check_same_shape(A, B);
  if (status != MATRIX_OK) {
    return status;
  }
  if (A == B) {
    return MATRIX_ERR_INVALID_ARG;
  }
  memcpy(B->data, A->data, A->rows * A->cols * sizeof(double));
  return MATRIX_OK;
}

MatrixStatus matrix_identity(Matrix *A) {
  if (check_matrix(A) != MATRIX_OK) {
    return MATRIX_ERR_NULL_PTR;
  }
  if (A->rows != A->cols) {
    return MATRIX_ERR_SHAPE;
  }
  for (size_t i = 0; i < A->rows; ++i) {
    for (size_t j = 0; j < A->cols; ++j) {
      A->data[i * A->cols + j] = (i == j) ? 1.0 : 0.0;
    }
  }
  return MATRIX_OK;
}

static MatrixStatus check_three(const Matrix *A, const Matrix *B, Matrix *C) {
  if (!A || !B || !C || !A->data || !B->data || !C->data) {
    return MATRIX_ERR_NULL_PTR;
  }
  if (C == A || C == B) {
    return MATRIX_ERR_INVALID_ARG;
  }
  if (A->rows != B->rows || A->cols != B->cols ||
      A->rows != C->rows || A->cols != C->cols) {
    return MATRIX_ERR_SHAPE;
  }
  return MATRIX_OK;
}

MatrixStatus matrix_add(const Matrix *A, const Matrix *B, Matrix *C) {
  MatrixStatus status = check_three(A, B, C);
  if (status != MATRIX_OK) {
    return status;
  }
  size_t n = A->rows * A->cols;
  for (size_t i = 0; i < n; ++i) {
    C->data[i] = A->data[i] + B->data[i];
  }
  return MATRIX_OK;
}

MatrixStatus matrix_sub(const Matrix *A, const Matrix *B, Matrix *C) {
  MatrixStatus status = check_three(A, B, C);
  if (status != MATRIX_OK) {
    return status;
  }
  size_t n = A->rows * A->cols;
  for (size_t i = 0; i < n; ++i) {
    C->data[i] = A->data[i] - B->data[i];
  }
  return MATRIX_OK;
}

MatrixStatus matrix_scalar_mul(const Matrix *A, double k, Matrix *B) {
  MatrixStatus status = check_same_shape(A, B);
  if (status != MATRIX_OK) {
    return status;
  }
  if (A == B) {
    return MATRIX_ERR_INVALID_ARG;
  }
  size_t n = A->rows * A->cols;
  for (size_t i = 0; i < n; ++i) {
    B->data[i] = k * A->data[i];
  }
  return MATRIX_OK;
}

MatrixStatus matrix_transpose(const Matrix *A, Matrix *B) {
  if (!A || !B || !A->data || !B->data) {
    return MATRIX_ERR_NULL_PTR;
  }
  if (A == B) {
    return MATRIX_ERR_INVALID_ARG;
  }
  if (B->rows != A->cols || B->cols != A->rows) {
    return MATRIX_ERR_SHAPE;
  }
  for (size_t i = 0; i < A->rows; ++i) {
    for (size_t j = 0; j < A->cols; ++j) {
      B->data[j * B->cols + i] = A->data[i * A->cols + j];
    }
  }
  return MATRIX_OK;
}

MatrixStatus matrix_mul(const Matrix *A, const Matrix *B, Matrix *C) {
  if (!A || !B || !C || !A->data || !B->data || !C->data) {
    return MATRIX_ERR_NULL_PTR;
  }
  if (C == A || C == B) {
    return MATRIX_ERR_INVALID_ARG;
  }
  if (A->cols != B->rows || C->rows != A->rows || C->cols != B->cols) {
    return MATRIX_ERR_SHAPE;
  }
  for (size_t i = 0; i < C->rows; ++i) {
    for (size_t j = 0; j < C->cols; ++j) {
      double sum = 0.0;
      for (size_t k = 0; k < A->cols; ++k) {
        sum += A->data[i * A->cols + k] * B->data[k * B->cols + j];
      }
      C->data[i * C->cols + j] = sum;
    }
  }
  return MATRIX_OK;
}

/* Student exercise: implement Gaussian elimination with partial pivoting. */
MatrixStatus matrix_det(const Matrix *A, double *det) {
	//定义一个叫 matrix_det 的函数，用来算行列式。
//A 是你传进来的矩阵，det 是用来装结果的“空盒子”（指针）
   if (!A || !A->data || !det) {
    return MATRIX_ERR_NULL_PTR;
  }
  //如果连矩阵都没有（!A），或者矩阵里没存数据（!A->data），
  //或者没给装结果的盒子（!det），直接返回“空指针错误”。这是保护程序，防止乱读内存。
  if (A->rows != A->cols) {
    return MATRIX_ERR_SHAPE;
  }

  size_t n = A->rows;
  //把方阵的边长（阶数）记作 n。

  /* 复制到临时矩阵，避免修改原矩阵 */
  Matrix T = {0};
  MatrixStatus st = matrix_create(&T, n, n);
  //matrix_create 是你代码里已经写好的一个函数，
  //它的作用就是向电脑要一块内存，用来存一个全新的矩阵。


  if (st != MATRIX_OK) {
    return st;
  }
  //return st;：把刚才那个失败的原因（比如“内存不够”的错误码）
  //直接原封不动地报告给调用你的测试程序。告诉它：“不好意思，我没借到内存，算不了了”。
  memcpy(T.data, A->data, n * n * sizeof(double));
  //把原矩阵 A 里面的数据，原封不动地拷贝到临时矩阵 T 里。
  //现在 T 就是 A 的替身了，后续消元都在 T 上折腾。
  //memcpy(目的地, 来源地, 复印多少字节);

  double result = 1.0;
  int sign = 1;   /* 行交换次数的奇偶性 */
  //result 用来存行列式的值，一开始设为 1。

//sign 用来记录正负号。行列式有个性质：每交换一次两行，行列式的值就要乘上 -1。
for (size_t col = 0; col < n; ++col) {
   	//col 代表当前正在处理的列（从第 0 列到第 n-1 列）
    /* 在当前列 col 及下方选绝对值最大的行 */
    size_t pivot = col;
    double max_abs = fabs(T.data[col * n + col]);
    //max_abs 是这列当前的最大绝对值。fabs 就是求绝对值
    //获取当前列的主元（对角线上的元素）的绝对值。
    //T.data[i * n + j] 代表的是第 i 行、第 j 列的元素。

//在这里，行号是 col，列号也是 col。
//所以 T.data[col * n + col] 找到的正是 第 col 行、第 col 列的元素。
    for (size_t r = col + 1; r < n; ++r) {
      double v = fabs(T.data[r * n + col]);
      if (v > max_abs) {
        max_abs = v;
        pivot = r;
      }
      //往下遍历每一行（r），看看有没有更大的数。

//如果发现下面的数比当前记录的最大值还大，就把最大值更新，
//并记住这个更大的数在哪一行（把 pivot 变成那一行）。
    }

    /* 主元视为零 -> 奇异，行列式为 0 */
    if (max_abs < MATRIX_EPSILON) {
      result = 0.0;
      goto done;
    }
    //如果最大绝对值都极小了（小于 MATRIX_EPSILON，你头文件里定义的是 1e-10），电脑就认为它是 0。

//如果这一列全是 0，说明这个矩阵是“奇异矩阵”（没有逆矩阵），
//它的行列式就是 0。于是直接把 result 设成 0，跳转（goto done）到收尾阶段。

     /* 交换行，符号翻转 */
    if (pivot != col) {
    	//如果之前选出的最大数不在当前行（pivot != col），就得把它所在的行换到上面来。
      for (size_t c = 0; c < n; ++c) {
        double tmp = T.data[col * n + c];
        T.data[col * n + c] = T.data[pivot * n + c];
        T.data[pivot * n + c] = tmp;
      }
      //两行的每个数据都互换 
      sign = -sign;
    }

    double piv = T.data[col * n + col];
    //主元是现在被换到对角线上那个绝对值最大的数 
    result *= piv;  
	//每处理完一列（确定了一个主元），我们就把这个主元乘进 result 里。
	//等所有列都循环完了，result 里装的就是所有主元的乘积，这也就是行列式的值了。
	 /* 累乘主元 */

    /* 用当前行消去下方各行在当前列的元素 */
    for (size_t r = col + 1; r < n; ++r) {
      double factor = T.data[r * n + col] / piv;
      if (factor == 0.0) {
        continue;
      }
      T.data[r * n + col] = 0.0;
      for (size_t c = col + 1; c < n; ++c) {
        T.data[r * n + c] -= factor * T.data[col * n + c];
        //这一行的所有数据消元 
      }
      /*factor：看当前行（第 r 行）这一列的元素，是主元的几倍。
if (factor == 0.0) continue;：如果这一列已经是 0 了，就不用管了，直接看下一行。
T.data[r * n + col] = 0.0;：直接把要消掉的这个位置变成 0。
接着一个内层循环，把 r 行后面的每个元素，减去 factor 倍的当前行（col 行）的元素
//。减完，下面的行在 col 这一列就变成 0 了。
*/
    }
  }
result *= (double)sign;
//result=result*sign 

done:
  matrix_free(&T);
  *det = result;
  return MATRIX_OK;
  //done: 这是一个“标签”，之前那个提前跳转的 goto done 就会直接跳到这里。

//matrix_free(&T);：我们用 matrix_create 借来的临时矩阵 T，
//用完了必须还给系统（释放内存），不然就内存泄漏了。

//*det = result;：把算出来的最终结果，放进你一开始传进来的 det 指针里。

//return MATRIX_OK;：告诉调用者：我算完了，一切顺利！
}
 

/* Student exercise: implement Gauss-Jordan elimination with partial pivoting. */
MatrixStatus matrix_inv(const Matrix *A, Matrix *A_inv) {
  if (!A || !A->data || !A_inv || !A_inv->data) {
    return MATRIX_ERR_NULL_PTR;
  }
  if (A == A_inv) {
    return MATRIX_ERR_INVALID_ARG;
  }
  if (A->rows != A->cols) {
    return MATRIX_ERR_SHAPE;
  }
  if (A_inv->rows != A->rows || A_inv->cols != A->cols) {
    return MATRIX_ERR_SHAPE;
  }

  size_t n = A->rows;
  //记录矩阵的边长 n

  /* 增广矩阵 [A | I]，尺寸 n x (2n) */
  Matrix aug = {0};
  MatrixStatus st = matrix_create(&aug, n, 2 * n);
  //在内存里申请一个 nn 行、2n
//2n 列的新矩阵 aug（aug 是 augmented 的缩写，意为“增广”）。
  if (st != MATRIX_OK) {
    return st;
  }

  /* 填充左半 A，右半 I */
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      aug.data[i * (2 * n) + j] = A->data[i * n + j];
      aug.data[i * (2 * n) + (n + j)] = (i == j) ? 1.0 : 0.0;
    }
  }

  for (size_t col = 0; col < n; ++col) {
    /* 选主元：当前列及下方绝对值最大 */
    size_t pivot = col;
    double max_abs = fabs(aug.data[col * (2 * n) + col]);
    for (size_t r = col + 1; r < n; ++r) {
      double v = fabs(aug.data[r * (2 * n) + col]);
      if (v > max_abs) {
        max_abs = v;
        pivot = r;
      }
    }

    if (max_abs < MATRIX_EPSILON) {
      matrix_free(&aug);
      return MATRIX_ERR_SINGULAR;
    }

    /* 交换行 */
    if (pivot != col) {
      for (size_t c = 0; c < 2 * n; ++c) {
        double tmp = aug.data[col * (2 * n) + c];
        aug.data[col * (2 * n) + c] = aug.data[pivot * (2 * n) + c];
        aug.data[pivot * (2 * n) + c] = tmp;
      }
    }

    /* 主元行除以主元，使主元为 1 */
    double piv = aug.data[col * (2 * n) + col];
    for (size_t c = 0; c < 2 * n; ++c) {
      aug.data[col * (2 * n) + c] /= piv;
    }

    /* 用该行消去其他所有行在当前列的元素 */
    for (size_t r = 0; r < n; ++r) {
      if (r == col) {
        continue;
      }
      double factor = aug.data[r * (2 * n) + col];
      if (factor == 0.0) {
        continue;
      }
      for (size_t c = 0; c < 2 * n; ++c) {
        aug.data[r * (2 * n) + c] -= factor * aug.data[col * (2 * n) + c];
      }
    }
  }

  /* 右半部分即 A^-1，拷回输出 */
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      A_inv->data[i * n + j] = aug.data[i * (2 * n) + (n + j)];
    }
  }

  matrix_free(&aug);
  return MATRIX_OK;
}


