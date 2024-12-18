#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 20

typedef int KeyType;
typedef int InfoType;


typedef struct{
    KeyType  key;     // �ؼ�����
    InfoType otherinfo; // ����������
}RedType;    // ��¼����

typedef struct{
    RedType  r[MAXSIZE+1];  //r[0]���û����ڱ�
    int       length;      // ˳�����
}SqList;    // ˳�������


// ��ӡ˳����е�Ԫ�أ����ڲ��Բ鿴������
void printList(SqList L) {
    for (int i = 1; i <= L.length; i++) {
        printf("%d ", L.r[i].key);
    }
    printf("\n");
}


// ��������
void InsertSort(SqList *list){
    int i, j;
    for(i = 2; i <= list->length; i++){
        // ����һ��Ԫ���ں������ǰ��Ĵ���Ҫ����,��Ҫ�������뵽ǰ�������򲿷��к��ʵ�λ��
        if(list->r[i].key < list->r[i - 1].key){
            // ��������Ԫ���ݴ浽�ڱ�λ��
            list->r[0] = list->r[i];
            // ����ǰλ�ã�����Ϊi����Ԫ������ǰһ��Ԫ�أ�����Ϊi - 1�����ǵ�,�ڳ��˵�ǰλ����׼��������ʵ�Ԫ�ء�
            list->r[i] = list->r[i - 1];
            // �ӵ�ǰԪ�ص�ǰһ��λ�ã�����Ϊi - 1����ʼ����ǰ����Ƚ�Ԫ�أ�������ڱ�С�����ϵذѽϴ��Ԫ��������
            for(j = i - 1; list->r[0].key < list->r[j].key; --j){
                list->r[j + 1] = list->r[j];
            }
            list->r[j + 1] = list->r[0];
        }
    }
}



// �۰��������
void binaryInsertSort(SqList* l){
    for (int i = 1; i < l->length; i++){
        RedType temp = l->r[i];  // �ݴ�������Ԫ��
        // ���ֲ���
        int left = 0, right = i - 1;
        // ���ֲ��Һ��ʵĲ���λ��
        while (left <= right) {
            int mid = (left + right) / 2;
            if (l->r[mid].key > temp.key) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        int j;
        // [left,i-1]�ε�Ԫ������ƶ����ڳ�����λ��
        for (j = i; j >= left + 1; j--) {
            l->r[j] = l->r[j - 1];
        }

        l->r[left] = temp;  // ���ݴ��Ԫ�ز��뵽����λ��
    }
}



// ϣ������
// ϣ�������ǽ����ݷ��飬���ռ��Ϊgap����Ϊһ�飬��ÿһ����в�������,���ӶȲ��ȶ�
// �Ը������gap���з����������
void shell(SqList* l, int gap) {
    // �Ӽ�� gap ��Ӧ��λ�ÿ�ʼ����˳���
    for (int i = gap; i < l->length; i++) {
        RedType temp = l->r[i];
        int j;
        // �ڵ�ǰ�����ڽ��в�������
        for (j = i; j >= gap && l->r[j - gap].key > temp.key; j -= gap) {
            l->r[j] = l->r[j - gap];
        }
        l->r[j] = temp;
    }
}

// ϣ������������
void shellSort(SqList* l) {
    int len = l->length;
    int gap = len / 2;  // ��ʼ��������Ϊ���ȵ�һ��
    while (gap > 0) {
        shell(l, gap);  // ��Ե�ǰ�������з����������
        gap /= 2;  // ��С����
    }
}



// ð������
void bubbleSort(SqList* l) {
    // ��� for ѭ�����ƱȽϵ�������һ����Ҫ���� l->length - 1 �ֱȽ�,ÿһ�ֱȽ϶��ܰѵ�ǰδ���򲿷ֵ����Ԫ�� ������ �������
    for (int i = 0; i < l->length - 1; i++) {
        // �ڲ� for ѭ��������ÿһ��������Ԫ�������Ƚ�,�������ǰһ��Ԫ�أ�l->r[j]���Ĺؼ��ִ��ں�һ��Ԫ�أ�l->r[j + 1]���Ĺؼ���
        for (int j = 0; j < l->length - 1 - i; j++) {
            if (l->r[j].key > l->r[j + 1].key) {
                // ��������Ԫ�ص�λ��
                RedType temp = l->r[j];
                l->r[j] = l->r[j + 1];
                l->r[j + 1] = temp;
            }
        }
    }
}



// ��������
// ���ֺ�����ѡ��һ����׼Ԫ�أ��������Ϊ�����֣����С�ڵ��ڻ�׼���ұߴ��ڻ�׼
int partition(SqList* l, int low, int high) {
    RedType temp;
    KeyType pivot = l->r[low].key;  // һ��ѡ�ӱ��һ����¼�������¼
    // �ӱ�����˽�������м�ɨ��
    while(low < high){
        // ��ָ��ָ��ıȻ�׼ֵ������ȷ��high--���м���
        while(low < high && l->r[high].key >= pivot){
            --high;
        }
        // �����������ָ��ָ���Ԫ��С�ڻ�׼ֵ����Ҫ����˳�򣬺���ָ��ָ���Ԫ�ػ�λ��
        temp = l->r[high];
        l->r[high] = l->r[low];
        l->r[low] = temp;

        // ��ָ��ָ��ıȻ�׼ֵС������ȷ��low++���м���
        while (low < high && l->r[low].key <= pivot) {
            low++;
        }
        // �����������ָ��ָ���Ԫ�ش��ڻ�׼ֵ����Ҫ����˳�򣬺���ָ��ָ���Ԫ�ػ�λ��
        temp = l->r[low];
        l->r[low] = l->r[high];
        l->r[low] = temp;
    }
    return low;
}

// �Ľ��棬��0�ſռ�洢���ѽ�����Ϊ��ֵ
int partition2(SqList* l, int low, int high){
    KeyType pivot;
    l->r[0] = l->r[low];    // ���ӱ�ĵ�һ����¼�������¼
    pivot = l->r[low].key;  //�����¼�ؼ���

    while(low < high){
        while(low < high && l->r[high].key >= pivot){
            --high;
        }
        l->r[low] = l->r[high];  // ���������¼С�ļ�¼�ŵ��Ͷ�

        while (low < high && l->r[low].key <= pivot) {
            ++low;
        }
        l->r[high] = l->r[low];//���������¼��ļ�¼�ŵ��߶�
    }
    l->r[low] = l->r[0];   //�����¼��λ
    return low;    //��������λ��
}

// ��������ݹ麯��
void quickSortRecursive(SqList* l, int low, int high) {
    if (low < high) {
        // ͨ��һ������Ҫ��������ݷָ�ɶ����������֣�����һ���ֵ��������ݶ�С�ڻ�׼ֵ����һ�����������ݶ����ڻ�׼ֵ
        int pivotIndex = partition(l, low, high);
        // ���������ٴεݹ�ֱ������
        quickSortRecursive(l, low, pivotIndex - 1);
        quickSortRecursive(l, pivotIndex + 1, high);
    }
}
void quickSortRecursive2(SqList* l, int low, int high) {
    if (low < high) {
        int pivotIndex = partition2(l, low, high);
        quickSortRecursive(l, low, pivotIndex - 1);
        quickSortRecursive(l, pivotIndex + 1, high);
    }
}

// �ǵݹ��
// ����˳���������Ԫ�ص�λ��
void swap(RedType* a, RedType* b) {
    RedType temp = *a;
    *a = *b;
    *b = temp;
}

// ���ֺ�����ѡ��һ����׼Ԫ�أ��������Ϊ�����֣����С�ڵ��ڻ�׼���ұߴ��ڻ�׼
int partition3(SqList* l, int low, int high) {
    KeyType pivot = l->r[high].key;  // ѡ�����һ��Ԫ����Ϊ��׼
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (l->r[j].key <= pivot) {
            i++;
            swap(&l->r[i], &l->r[j]);
        }
    }
    swap(&l->r[i + 1], &l->r[high]);
    return i + 1;
}

// ��������ǵݹ��
void quickSortNonRecursive(SqList* l) {
    int stack[MAXSIZE];  // ������ģ��ջ
    int top = -1;  // ջ��ָ���ʼ��Ϊ -1����ʾջΪ��

    stack[++top] = 0;
    stack[++top] = l->length - 1;

    while (top >= 0) {
        int high = stack[top--];
        int low = stack[top--];

        if (low < high) {
            int pivotIndex = partition3(l, low, high);

            // ����벿����������ѹ��ջ
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;

            // ���Ұ벿����������ѹ��ջ
            stack[++top] = pivotIndex + 1;
            stack[++top] = high;
        }
    }
}


// ��ѡ������
void simpleSelectSort(SqList *l){
    // ���forѭ���������������,һ����Ҫ����l->length - 1��
    // ÿһ���ȼ��赱ǰλ��i��Ԫ�ص���С�ģ���¼ΪminIndex
    for (int i = 1; i < l->length; i++) {
        int minIndex = i;
        // ��i + 1λ�ÿ�ʼ�������ʣ��Ԫ��
        for (int j = i + 1; j <= l->length; j++) {
            // ��������б�l->r[minIndex]��С��Ԫ�أ�����
            if (l->r[j].key < l->r[minIndex].key) {
                minIndex = j;
            }
        }
        // �ڲ�ѭ�����������minIndex������i��˵���ҵ��˸�С��Ԫ�أ���Ҫ����������Ԫ�ص�λ��
        if (minIndex!= i) {
            RedType temp = l->r[i];
            l->r[i] = l->r[minIndex];
            l->r[minIndex] = temp;
        }
    }
}


// ��������غ���
// ��������Ѻ���
// low ��ʾ��ǰҪ�����������ĸ��ڵ�������Ҳ���Ǵ�����ڵ㿪ʼ����������Ϊ��������ʹ�������������ʡ�
// high ��ʾ��ǰ�ѣ�Ҳ�������������в���Ѳ������ǲ���Ԫ�أ������һ��Ԫ�ص����������ڽ綨������Χ��
void adjustHeap(SqList* l, int low, int high) {
    RedType rc = l->r[low];     // ������ڵ��ֵ
    // i = 2 * low ��ʾ�Ӹ��ڵ� low �����ӽڵ㿪ʼ
    // ÿ��ѭ�� i *= 2 ��Ϊ�˲��ϻ�ȡ��һ����ӽڵ㣬������ȫ���������ڵ� i �����ӽڵ��������� 2 * i
    for (int i = 2 * low; i <= high; i *= 2) {
        // �Ƚϵ�ǰ�ڵ� i �����ӽڵ�����ӽڵ��ֵ��С
        if (i < high && l->r[i].key < l->r[i + 1].key) {
            // ������ӽڵ�i + 1���󣬾ͽ� i ��1 ����Ϊ���ӽڵ������
            i += 1;
        }
        // ���rc���ڵ��ֵ���ڵ��ڵ�ǰ�Ƚϵ��ӽڵ��ֵ�����������������ˣ�ֱ�� break ����ѭ����
        if (rc.key >= l->r[i].key) {
            break;
        }
        // �ӽڵ��ֵ���󣬾ͽ��ϴ���ӽڵ��ֵ���Ƶ����ڵ�λ�ã�ͬʱ��������
        l->r[low] = l->r[i];
        low = i;
    }
    // ����������ĸ��ڵ��ֵ��rc���ŵ����ʵ�λ��
    l->r[low] = rc;
}

// ������������
void heapSort(SqList* l) {
    // ��һ���������й����ɴ���ѣ�������һ�����µ�������ɸѡ�Ĺ���
    // �����һ����Ҷ�ӽڵ㿪ʼ��������ǰ��ÿ����Ҷ�ӽڵ���õ����ѵĲ�����ֱ�����������������ѵ�����
    for (int i = l->length / 2; i > 0; i--) {
        // ������ȫ�����������һ����Ҷ�ӽڵ����������ͨ�� length / 2������ȡ����������
        adjustHeap(l, i, l->length);
    }

    // ����Ѷ�Ԫ�غ����Ϊ�¶�
    for (int i = l->length; i > 1; i--) {
        // ����ѹ����ú󣬶Ѷ�Ԫ�أ�����Ϊ 1���������������е����ֵ
        // ��ʱ���Ѷ�Ԫ����������һ��Ԫ�ؽ���λ�ã�Ҳ���ǰ����ֵ�ŵ��������������λ�ã�
        RedType temp = l->r[1];
        l->r[1] = l->r[i];
        l->r[i] = temp;
        // Ȼ���ʣ�µ� n - 1 ��Ԫ�����µ�����һ���µĴ���ѣ��ظ�������̣�ֱ��������������
        adjustHeap(l, 1, i - 1);
    }
}


// �鲢������غ���

// �ϲ������������������
void merge(SqList *L, int low, int mid, int high) {
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;

    // ������ʱ����������������
    RedType *L1 = (RedType *)malloc((n1 + 1) * sizeof(RedType));
    RedType *L2 = (RedType *)malloc((n2 + 1) * sizeof(RedType));

    // ��ԭ�����ж�Ӧ���ָ��Ƶ���ʱ����
    for (i = 0; i < n1; i++)
        L1[i] = L->r[low + i];
    for (j = 0; j < n2; j++)
        L2[j] = L->r[mid + 1 + j];

    // �����ڱ����������Ƚ�
    L1[n1].key = 1000000;  // �������һ���ϴ�ֵ��Ϊ�ڱ���ʵ��Ӧ�ÿɸ������ݷ�Χ��������
    L2[n2].key = 1000000;

    i = 0;
    j = 0;
    k = low;
    // �ϲ�������ʱ���鵽ԭ������
    while (i < n1 && j < n2) {
        if (L1[i].key <= L2[j].key) {
            L->r[k] = L1[i];
            i++;
        } else {
            L->r[k] = L2[j];
            j++;
        }
        k++;
    }

    // ����ʣ��Ԫ�أ����У�
    while (i < n1) {
        L->r[k] = L1[i];
        i++;
        k++;
    }
    while (j < n2) {
        L->r[k] = L2[j];
        j++;
        k++;
    }

    free(L1);
    free(L2);
}

// �鲢����ݹ麯��
void mergeSort(SqList *L, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(L, low, mid);
        mergeSort(L, mid + 1, high);
        merge(L, low, mid, high);
    }
}


int main() {
    SqList list;
    list.length = 7;
    list.r[1].key = 5;
    list.r[2].key = 3;
    list.r[3].key = 4;
    list.r[4].key = 6;
    list.r[5].key = 2;
    list.r[6].key = 4;

    printf("����ǰ��˳���Ԫ��: ");
    printList(list);

    InsertSort(&list);
    printf("����������˳���Ԫ��: ");
    printList(list);

    SqList list2 = list;  // ����һ�������۰�����������
    binaryInsertSort(&list2);
    printf("�۰����������˳���Ԫ��: ");
    printList(list2);

    SqList list3 = list;  // ����һ������ϣ���������
    shellSort(&list3);
    printf("ϣ��������˳���Ԫ��: ");
    printList(list3);

    SqList list4 = list;  // ����һ������ð���������
    bubbleSort(&list4);
    printf("ð��������˳���Ԫ��: ");
    printList(list4);

    SqList list5 = list;  // ����һ�����ڿ������򣨵ݹ�棩����
    quickSortRecursive(&list5, 1, list5.length);
    printf("�������򣨵ݹ�棩���˳���Ԫ��: ");
    printList(list5);

    SqList list6 = list;  // ����һ�����ڿ������򣨵ݹ�棩�Ľ� ����
    quickSortRecursive2(&list6, 1, list5.length );
    printf("�������򣨵ݹ�棩�Ľ� ���˳���Ԫ��: ");
    printList(list6);

    SqList list7 = list;  // ����һ�����ڿ������򣨷ǵݹ�棩����
    quickSortNonRecursive(&list7);
    printf("�������򣨷ǵݹ�棩���˳���Ԫ��: ");
    printList(list7);

    SqList list8 = list;  // ����һ�����ڼ�ѡ���������
    simpleSelectSort(&list8);
    printf("��ѡ��������˳���Ԫ��: ");
    printList(list8);

    SqList list9 = list;  // ����һ�����ڶ��������
    heapSort(&list9);
    printf("��������˳���Ԫ��: ");
    printList(list9);

    SqList list10 = list;  // ����һ�����ڹ鲢�������
    mergeSort(&list10, 1, list10.length);
    printf("�鲢������˳���Ԫ��: ");
    printList(list10);


    return 0;
}