#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 12500
#define MAXRC 100
const int ERROR = -1;
const int OVERFLOW = 1;
const int OK = 0;

// 定义三元组结构，用于存储非零元素的信息
typedef struct {
    int i, j;  // 非零元的行列下标
    int ele;   // 非零元的值
} Triple;

// 定义稀疏矩阵结构
typedef struct {
    Triple data[MAXSIZE];  // 存储非零元的数组
    int rops[MAXRC];       // 各行第一个非零元的位置表
    int mu, nu, tu;        // 矩阵的行数、列数和非零元个数
} TSMatrix;

int createTSMatrix(TSMatrix *matrix, int mu, int nu) {
    if (mu <= 0 || nu <= 0) {
        return ERROR;
    }
    matrix->mu = mu; // 设置行数
    matrix->nu = nu; // 设置列数
    matrix->tu = 0;  // 初始化非零元素个数
    return OK; // 返回成功
}

// 插入非零元素
int insertElement(TSMatrix *matrix, int i, int j, int value) {
    // 检查行列下标是否有效
    if (i < 0 || i >= matrix->mu || j < 0 || j >= matrix->nu) {
        return ERROR; // 返回错误
    }
    // 检查非零元素个数是否超过最大值
    if (matrix->tu >= MAXSIZE) {
        return OVERFLOW; // 返回溢出
    }
    // 插入新元素
    matrix->data[matrix->tu].i = i;
    matrix->data[matrix->tu].j = j;
    matrix->data[matrix->tu].ele = value;
    matrix->tu++; // 更新非零元素个数
    return OK;
}


// 矩阵相加
int addTSMatrix(const TSMatrix *A, const TSMatrix *B, TSMatrix *C) {
    if (A->mu != B->mu || A->nu != B->nu) {
        return ERROR; // 矩阵大小不一致，返回错误
    }

    // 初始化结果矩阵C
    createTSMatrix(C, A->mu, A->nu);

    int i = 0, j = 0; // 用于遍历A和B中的非零元素

    // 遍历A和B中的所有非零元素
    while (i < A->tu && j < B->tu) {
        // 如果A和B的行列下标相同，进行相加
        if(A->data[i].i == B->data[j].i && A->data[i].j == B->data[j].j){
            int sum = A->data[i].ele + B->data[j].ele;
            if (sum != 0) { // 只插入非零结果
                insertElement(C, A->data[i].i, A->data[i].j, sum);
            }
            i++;
            j++;
        // A的元素在B的元素的前面
        }else if(A->data[i].i < B->data[j].i || A->data[i].i == B->data[j].i && A->data[i].j < B->data[j].j) {
            insertElement(C, A->data[i].i, A->data[i].j, A->data[i].ele);
            i++;
        // 否则 插入B
        }else{
            insertElement(C, B->data[i].i, B->data[i].j, B->data[i].ele);
            j++;
        }

        // 插入A剩余的元素
        while (i < A->tu) {
            insertElement(C, A->data[i].i, A->data[i].j, A->data[i].ele);
            i++;
        }

        // 插入B剩余的元素
        while (j < B->tu) {
            insertElement(C, B->data[j].i, B->data[j].j, B->data[j].ele);
            j++;
        }

        return OK; // 返回成功
    }
}


// 矩阵相乘
int multTSMatrix(const TSMatrix *M, const TSMatrix *N, TSMatrix *Q) {
    int tp, brow, t, ctemp[MAXRC];  // ctemp 数组用于临时存储乘积结果的数组，每次遍历都需要清空

    // 检查矩阵 M 和 N 的行数不等，则不能做矩阵乘运算
    if (M->nu != N->mu) {
        return ERROR;
    }

    // 初始化结果矩阵 Q
    Q->mu = M->mu;  // 结果矩阵的行数等于 M 的行数
    Q->nu = N->nu;  // 结果矩阵的列数等于 N 的列数
    Q->tu = 0;      // 初始化非零元素个数为 0

    // 初始化结果矩阵 Q 的行指针
    for (int i = 0; i < Q->mu; ++i) Q->rops[i] = 0;

    // 结果不为零矩阵
    if (M->tu * N->tu != 0) {
        // 处理 M 每一行
        for (int ar = 1; ar <= M->mu; ++ar) {
            // 当前行各元素的累加器清零
            for (int col = 0; col < Q->nu; ++col) {
                ctemp[col] = 0; // 清零临时存储数组
            }

            // Q 的 rops 记录当前行的第一个非零元素的位置
            Q->rops[ar] = Q->tu + 1;

            // 获取当前行在 M 中的非零元素的结束位置
            tp = (ar < M->mu - 1) ? M->rops[ar + 1] : M->tu;

            // 对当前行每一个非零元
            for (int p = M->rops[ar]; p < tp; ++p) {
                brow = M->data[p].j; // 取该非0元素的列数，便于去N中找对应的做乘积的非0元素

                // 获取 N 中对应行的非零元素结束位置
                t = (brow < N->mu) ? N->rops[brow + 1] : N->tu;

                // 对于 N 中对应行的每个非零元素，计算乘积并累加到 ctemp 中
                for (int q = N->rops[brow]; q < t; ++q) {
                    int ccol = N->data[q].j; // 获取 N 中非零元素的列索引
                    ctemp[ccol] += M->data[p].ele * N->data[q].ele; // 累加结果
                }
            }

            // 将 ctemp 中的非零值更新到结果矩阵 Q 中
            for (int col = 0; col < Q->nu; ++col) {
                if (ctemp[col]) { // 如果该列有非零值
                    if (++Q->tu > MAXSIZE) return ERROR; // 检查是否超过最大容量
                    Q->data[Q->tu] = (Triple){ar, col, ctemp[col]}; // 存储非零元
                }
            }
        }
    }
    return OK; // 返回成功
}


// 显示稀疏矩阵
void displayTSMatrix(const TSMatrix *matrix) {
    printf("稀疏矩阵: \n");
    printf("行数: %d, 列数: %d, 非零元素个数: %d\n", matrix->mu, matrix->nu, matrix->tu);
    printf("行 列 值\n");
    for (int k = 0; k < matrix->tu; k++) {
        printf("%d %d %d\n", matrix->data[k].i, matrix->data[k].j, matrix->data[k].ele);
    }
}


// 稀疏矩阵的转置
int transposeTSMatrixSr(const TSMatrix *matrix, TSMatrix *transposed) {
    createTSMatrix(transposed, matrix->nu, matrix->mu); // 转置矩阵的行列互换
    for (int k = 0; k < matrix->tu; k++) {
        // 插入转置矩阵的元素
        insertElement(transposed, matrix->data[k].j, matrix->data[k].i, matrix->data[k].ele);
    }
    return OK; // 返回成功
}

// 普通的矩阵转置
int transposeTSMatrix(TSMatrix *M, TSMatrix *T){
    int q = 0;   // 关于转置矩阵的指针
    // 重排三元组次序
    T->mu = M->nu, T->nu = M->mu, T->tu = M->tu;
    if(T->tu){
        // 外层循环遍历每一列 col（从 1 到 M->nu），内层循环遍历每一个非零元素（从 1 到 M->tu）
        for(int col = 0; col < M->nu; ++col){
            for(int p = 0; p < M->tu; ++p){
                // 判断当前非零元素的列索引 M->data[p].j 是否与当前遍历的列索引 col 相等
                if(M->data[p].j == col){
                    T->data[q].i = M->data[p].j;
                    T->data[q].j = M->data[p].i;
                    T->data[q].ele = M->data[p].ele;
                    ++q;
                }
            }
        }
    }
    return OK;
}


// 快速转置
int FastTransposeTSMatrix(TSMatrix *M, TSMatrix *T){
    // num指明矩阵M中第col列非零元的个数，cpot用于记录转置矩阵T中每列第一个非零元素的存储位置
    int num[1250], cpot[1250];
    T->mu = M->nu, T->nu = M->mu, T->tu = M->tu;
    if(T->tu){
        for(int col = 0; col < M->nu; ++col)  num[col] = 0;    // 初始化为0
        for(int t = 0; t < M->tu; ++t) ++num[M->data[t].j];   // 求M每一行有多少非零元素

        cpot[0] = 0;  // 初始化第一个非0元的序号，第1列的起始位置为1
        // 求第col列中第一个非零元在转置矩阵中的位置
        for(int col = 1; col < M->nu; ++col) cpot[col] = cpot[col - 1] + num[col - 1];

        // p遍历原矩阵M的非零元素
        for(int p = 0; p < M->tu; ++p){
            // col为当前元素所在列，q找到在转置矩阵中的插入位置
            int col = M->data[p].j;   // 此时M对应三元组中的非0元的所在列
            int q = cpot[col];      // q为当前非零元应当放置的序号位置
            T->data[q].i = M->data[p].j;
            T->data[q].j = M->data[p].i;
            T->data[q].ele = M->data[p].ele;
            // 对应下一个此列中非0元的序号
            ++cpot[col];
            //cpot[col]最后一直加到等于cpot[col + 1],第col列也就不会有更多的非0元了
        }
    }
    return OK;
}


// 主函数示例
int main() {
    TSMatrix matrixA, matrixB, matrixC, transposedMatrix; // 创建稀疏矩阵对象
    // 创建矩阵A
    if (createTSMatrix(&matrixA, 3, 3) != OK) {
        printf("创建矩阵A失败！\n");
        return 1; // 结束程序
    }
    // 插入一些非零元素到矩阵A
    insertElement(&matrixA, 0, 1, 5);
    insertElement(&matrixA, 1, 2, 3);
    insertElement(&matrixA, 2, 1, 7);

    // 创建矩阵B
    if (createTSMatrix(&matrixB, 3, 3) != OK) {
        printf("创建矩阵B失败！\n");
        return 1; // 结束程序
    }
    // 插入一些非零元素到矩阵B
    insertElement(&matrixB, 0, 0, 2);
    insertElement(&matrixB, 1, 1, 4);
    insertElement(&matrixB, 2, 1, 1);

    // 显示矩阵A和B
    printf("矩阵A:\n");
    displayTSMatrix(&matrixA);

    printf("矩阵B:\n");
    displayTSMatrix(&matrixB);

    // 计算矩阵A和B的和
    if (addTSMatrix(&matrixA, &matrixB, &matrixC) == OK) {
        printf("矩阵A和B的和:\n");
        displayTSMatrix(&matrixC);
    } else {
        printf("矩阵A和B的和计算失败！\n");
    }

    // 计算矩阵A的转置
    if (transposeTSMatrix(&matrixA, &transposedMatrix) == OK) {
        printf("矩阵A的转置:\n");
        displayTSMatrix(&transposedMatrix); // 显示转置矩阵
    }

    // 使用快速转置计算
    TSMatrix fastTransposedMatrix;
    if (FastTransposeTSMatrix(&matrixA, &fastTransposedMatrix) == OK) {
        printf("矩阵A的快速转置:\n");
        displayTSMatrix(&fastTransposedMatrix); // 显示快速转置矩阵
    }

    // 计算矩阵乘法
    TSMatrix M, N, Q;

    // 初始化矩阵 M (3x3)
    M.mu = 3;
    M.nu = 3;
    M.tu = 4; // 非零元素个数
    M.rops[0] = 0; // 第0行非零元开始位置
    M.rops[1] = 2; // 第1行非零元开始位置
    M.rops[2] = 2; // 第2行非零元开始位置
    M.rops[3] = 4; // 第3行非零元开始位置

    // 设定非零元素
    M.data[0] = (Triple){0, 0, 1}; // M[0][0] = 1
    M.data[1] = (Triple){0, 1, 2}; // M[0][1] = 2
    M.data[2] = (Triple){1, 1, 3}; // M[1][1] = 3
    M.data[3] = (Triple){2, 0, 4}; // M[2][0] = 4

    // 初始化矩阵 N (3x2)
    N.mu = 3;
    N.nu = 2;
    N.tu = 3; // 非零元素个数
    N.rops[0] = 0; // 第0行非零元开始位置
    N.rops[1] = 1; // 第1行非零元开始位置
    N.rops[2] = 2; // 第2行非零元开始位置
    N.rops[3] = 3; // 第3行非零元开始位置

    // 设定非零元素
    N.data[0] = (Triple){0, 0, 5}; // N[0][0] = 5
    N.data[1] = (Triple){1, 1, 6}; // N[1][1] = 6
    N.data[2] = (Triple){2, 0, 7}; // N[2][0] = 7

    // 执行矩阵乘法
    int result = multTSMatrix(&M, &N, &Q);

    // 输出结果
    if (result == OK) {
        printf("Matrix Q (Result of M * N):\n");
        for (int i = 0; i < Q.tu; ++i) {
            printf("Q[%d][%d] = %d\n", Q.data[i + 1].i, Q.data[i + 1].j, Q.data[i + 1].ele);
        }
    }


    return 0; // 成功结束程序
}