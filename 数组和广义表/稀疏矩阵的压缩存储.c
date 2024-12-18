#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 12500
#define MAXRC 100
const int ERROR = -1;
const int OVERFLOW = 1;
const int OK = 0;

// ������Ԫ��ṹ�����ڴ洢����Ԫ�ص���Ϣ
typedef struct {
    int i, j;  // ����Ԫ�������±�
    int ele;   // ����Ԫ��ֵ
} Triple;

// ����ϡ�����ṹ
typedef struct {
    Triple data[MAXSIZE];  // �洢����Ԫ������
    int rops[MAXRC];       // ���е�һ������Ԫ��λ�ñ�
    int mu, nu, tu;        // ����������������ͷ���Ԫ����
} TSMatrix;

int createTSMatrix(TSMatrix *matrix, int mu, int nu) {
    if (mu <= 0 || nu <= 0) {
        return ERROR;
    }
    matrix->mu = mu; // ��������
    matrix->nu = nu; // ��������
    matrix->tu = 0;  // ��ʼ������Ԫ�ظ���
    return OK; // ���سɹ�
}

// �������Ԫ��
int insertElement(TSMatrix *matrix, int i, int j, int value) {
    // ��������±��Ƿ���Ч
    if (i < 0 || i >= matrix->mu || j < 0 || j >= matrix->nu) {
        return ERROR; // ���ش���
    }
    // ������Ԫ�ظ����Ƿ񳬹����ֵ
    if (matrix->tu >= MAXSIZE) {
        return OVERFLOW; // �������
    }
    // ������Ԫ��
    matrix->data[matrix->tu].i = i;
    matrix->data[matrix->tu].j = j;
    matrix->data[matrix->tu].ele = value;
    matrix->tu++; // ���·���Ԫ�ظ���
    return OK;
}


// �������
int addTSMatrix(const TSMatrix *A, const TSMatrix *B, TSMatrix *C) {
    if (A->mu != B->mu || A->nu != B->nu) {
        return ERROR; // �����С��һ�£����ش���
    }

    // ��ʼ���������C
    createTSMatrix(C, A->mu, A->nu);

    int i = 0, j = 0; // ���ڱ���A��B�еķ���Ԫ��

    // ����A��B�е����з���Ԫ��
    while (i < A->tu && j < B->tu) {
        // ���A��B�������±���ͬ���������
        if(A->data[i].i == B->data[j].i && A->data[i].j == B->data[j].j){
            int sum = A->data[i].ele + B->data[j].ele;
            if (sum != 0) { // ֻ���������
                insertElement(C, A->data[i].i, A->data[i].j, sum);
            }
            i++;
            j++;
        // A��Ԫ����B��Ԫ�ص�ǰ��
        }else if(A->data[i].i < B->data[j].i || A->data[i].i == B->data[j].i && A->data[i].j < B->data[j].j) {
            insertElement(C, A->data[i].i, A->data[i].j, A->data[i].ele);
            i++;
        // ���� ����B
        }else{
            insertElement(C, B->data[i].i, B->data[i].j, B->data[i].ele);
            j++;
        }

        // ����Aʣ���Ԫ��
        while (i < A->tu) {
            insertElement(C, A->data[i].i, A->data[i].j, A->data[i].ele);
            i++;
        }

        // ����Bʣ���Ԫ��
        while (j < B->tu) {
            insertElement(C, B->data[j].i, B->data[j].j, B->data[j].ele);
            j++;
        }

        return OK; // ���سɹ�
    }
}


// �������
int multTSMatrix(const TSMatrix *M, const TSMatrix *N, TSMatrix *Q) {
    int tp, brow, t, ctemp[MAXRC];  // ctemp ����������ʱ�洢�˻���������飬ÿ�α�������Ҫ���

    // ������ M �� N ���������ȣ����������������
    if (M->nu != N->mu) {
        return ERROR;
    }

    // ��ʼ��������� Q
    Q->mu = M->mu;  // ���������������� M ������
    Q->nu = N->nu;  // ���������������� N ������
    Q->tu = 0;      // ��ʼ������Ԫ�ظ���Ϊ 0

    // ��ʼ��������� Q ����ָ��
    for (int i = 0; i < Q->mu; ++i) Q->rops[i] = 0;

    // �����Ϊ�����
    if (M->tu * N->tu != 0) {
        // ���� M ÿһ��
        for (int ar = 1; ar <= M->mu; ++ar) {
            // ��ǰ�и�Ԫ�ص��ۼ�������
            for (int col = 0; col < Q->nu; ++col) {
                ctemp[col] = 0; // ������ʱ�洢����
            }

            // Q �� rops ��¼��ǰ�еĵ�һ������Ԫ�ص�λ��
            Q->rops[ar] = Q->tu + 1;

            // ��ȡ��ǰ���� M �еķ���Ԫ�صĽ���λ��
            tp = (ar < M->mu - 1) ? M->rops[ar + 1] : M->tu;

            // �Ե�ǰ��ÿһ������Ԫ
            for (int p = M->rops[ar]; p < tp; ++p) {
                brow = M->data[p].j; // ȡ�÷�0Ԫ�ص�����������ȥN���Ҷ�Ӧ�����˻��ķ�0Ԫ��

                // ��ȡ N �ж�Ӧ�еķ���Ԫ�ؽ���λ��
                t = (brow < N->mu) ? N->rops[brow + 1] : N->tu;

                // ���� N �ж�Ӧ�е�ÿ������Ԫ�أ�����˻����ۼӵ� ctemp ��
                for (int q = N->rops[brow]; q < t; ++q) {
                    int ccol = N->data[q].j; // ��ȡ N �з���Ԫ�ص�������
                    ctemp[ccol] += M->data[p].ele * N->data[q].ele; // �ۼӽ��
                }
            }

            // �� ctemp �еķ���ֵ���µ�������� Q ��
            for (int col = 0; col < Q->nu; ++col) {
                if (ctemp[col]) { // ��������з���ֵ
                    if (++Q->tu > MAXSIZE) return ERROR; // ����Ƿ񳬹��������
                    Q->data[Q->tu] = (Triple){ar, col, ctemp[col]}; // �洢����Ԫ
                }
            }
        }
    }
    return OK; // ���سɹ�
}


// ��ʾϡ�����
void displayTSMatrix(const TSMatrix *matrix) {
    printf("ϡ�����: \n");
    printf("����: %d, ����: %d, ����Ԫ�ظ���: %d\n", matrix->mu, matrix->nu, matrix->tu);
    printf("�� �� ֵ\n");
    for (int k = 0; k < matrix->tu; k++) {
        printf("%d %d %d\n", matrix->data[k].i, matrix->data[k].j, matrix->data[k].ele);
    }
}


// ϡ������ת��
int transposeTSMatrixSr(const TSMatrix *matrix, TSMatrix *transposed) {
    createTSMatrix(transposed, matrix->nu, matrix->mu); // ת�þ�������л���
    for (int k = 0; k < matrix->tu; k++) {
        // ����ת�þ����Ԫ��
        insertElement(transposed, matrix->data[k].j, matrix->data[k].i, matrix->data[k].ele);
    }
    return OK; // ���سɹ�
}

// ��ͨ�ľ���ת��
int transposeTSMatrix(TSMatrix *M, TSMatrix *T){
    int q = 0;   // ����ת�þ����ָ��
    // ������Ԫ�����
    T->mu = M->nu, T->nu = M->mu, T->tu = M->tu;
    if(T->tu){
        // ���ѭ������ÿһ�� col���� 1 �� M->nu�����ڲ�ѭ������ÿһ������Ԫ�أ��� 1 �� M->tu��
        for(int col = 0; col < M->nu; ++col){
            for(int p = 0; p < M->tu; ++p){
                // �жϵ�ǰ����Ԫ�ص������� M->data[p].j �Ƿ��뵱ǰ������������ col ���
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


// ����ת��
int FastTransposeTSMatrix(TSMatrix *M, TSMatrix *T){
    // numָ������M�е�col�з���Ԫ�ĸ�����cpot���ڼ�¼ת�þ���T��ÿ�е�һ������Ԫ�صĴ洢λ��
    int num[1250], cpot[1250];
    T->mu = M->nu, T->nu = M->mu, T->tu = M->tu;
    if(T->tu){
        for(int col = 0; col < M->nu; ++col)  num[col] = 0;    // ��ʼ��Ϊ0
        for(int t = 0; t < M->tu; ++t) ++num[M->data[t].j];   // ��Mÿһ���ж��ٷ���Ԫ��

        cpot[0] = 0;  // ��ʼ����һ����0Ԫ����ţ���1�е���ʼλ��Ϊ1
        // ���col���е�һ������Ԫ��ת�þ����е�λ��
        for(int col = 1; col < M->nu; ++col) cpot[col] = cpot[col - 1] + num[col - 1];

        // p����ԭ����M�ķ���Ԫ��
        for(int p = 0; p < M->tu; ++p){
            // colΪ��ǰԪ�������У�q�ҵ���ת�þ����еĲ���λ��
            int col = M->data[p].j;   // ��ʱM��Ӧ��Ԫ���еķ�0Ԫ��������
            int q = cpot[col];      // qΪ��ǰ����ԪӦ�����õ����λ��
            T->data[q].i = M->data[p].j;
            T->data[q].j = M->data[p].i;
            T->data[q].ele = M->data[p].ele;
            // ��Ӧ��һ�������з�0Ԫ�����
            ++cpot[col];
            //cpot[col]���һֱ�ӵ�����cpot[col + 1],��col��Ҳ�Ͳ����и���ķ�0Ԫ��
        }
    }
    return OK;
}


// ������ʾ��
int main() {
    TSMatrix matrixA, matrixB, matrixC, transposedMatrix; // ����ϡ��������
    // ��������A
    if (createTSMatrix(&matrixA, 3, 3) != OK) {
        printf("��������Aʧ�ܣ�\n");
        return 1; // ��������
    }
    // ����һЩ����Ԫ�ص�����A
    insertElement(&matrixA, 0, 1, 5);
    insertElement(&matrixA, 1, 2, 3);
    insertElement(&matrixA, 2, 1, 7);

    // ��������B
    if (createTSMatrix(&matrixB, 3, 3) != OK) {
        printf("��������Bʧ�ܣ�\n");
        return 1; // ��������
    }
    // ����һЩ����Ԫ�ص�����B
    insertElement(&matrixB, 0, 0, 2);
    insertElement(&matrixB, 1, 1, 4);
    insertElement(&matrixB, 2, 1, 1);

    // ��ʾ����A��B
    printf("����A:\n");
    displayTSMatrix(&matrixA);

    printf("����B:\n");
    displayTSMatrix(&matrixB);

    // �������A��B�ĺ�
    if (addTSMatrix(&matrixA, &matrixB, &matrixC) == OK) {
        printf("����A��B�ĺ�:\n");
        displayTSMatrix(&matrixC);
    } else {
        printf("����A��B�ĺͼ���ʧ�ܣ�\n");
    }

    // �������A��ת��
    if (transposeTSMatrix(&matrixA, &transposedMatrix) == OK) {
        printf("����A��ת��:\n");
        displayTSMatrix(&transposedMatrix); // ��ʾת�þ���
    }

    // ʹ�ÿ���ת�ü���
    TSMatrix fastTransposedMatrix;
    if (FastTransposeTSMatrix(&matrixA, &fastTransposedMatrix) == OK) {
        printf("����A�Ŀ���ת��:\n");
        displayTSMatrix(&fastTransposedMatrix); // ��ʾ����ת�þ���
    }

    // �������˷�
    TSMatrix M, N, Q;

    // ��ʼ������ M (3x3)
    M.mu = 3;
    M.nu = 3;
    M.tu = 4; // ����Ԫ�ظ���
    M.rops[0] = 0; // ��0�з���Ԫ��ʼλ��
    M.rops[1] = 2; // ��1�з���Ԫ��ʼλ��
    M.rops[2] = 2; // ��2�з���Ԫ��ʼλ��
    M.rops[3] = 4; // ��3�з���Ԫ��ʼλ��

    // �趨����Ԫ��
    M.data[0] = (Triple){0, 0, 1}; // M[0][0] = 1
    M.data[1] = (Triple){0, 1, 2}; // M[0][1] = 2
    M.data[2] = (Triple){1, 1, 3}; // M[1][1] = 3
    M.data[3] = (Triple){2, 0, 4}; // M[2][0] = 4

    // ��ʼ������ N (3x2)
    N.mu = 3;
    N.nu = 2;
    N.tu = 3; // ����Ԫ�ظ���
    N.rops[0] = 0; // ��0�з���Ԫ��ʼλ��
    N.rops[1] = 1; // ��1�з���Ԫ��ʼλ��
    N.rops[2] = 2; // ��2�з���Ԫ��ʼλ��
    N.rops[3] = 3; // ��3�з���Ԫ��ʼλ��

    // �趨����Ԫ��
    N.data[0] = (Triple){0, 0, 5}; // N[0][0] = 5
    N.data[1] = (Triple){1, 1, 6}; // N[1][1] = 6
    N.data[2] = (Triple){2, 0, 7}; // N[2][0] = 7

    // ִ�о���˷�
    int result = multTSMatrix(&M, &N, &Q);

    // ������
    if (result == OK) {
        printf("Matrix Q (Result of M * N):\n");
        for (int i = 0; i < Q.tu; ++i) {
            printf("Q[%d][%d] = %d\n", Q.data[i + 1].i, Q.data[i + 1].j, Q.data[i + 1].ele);
        }
    }


    return 0; // �ɹ���������
}