// ���þ�̬һά����
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100 // ���崮����󳤶�

// ���Ľṹ�嶨��
typedef struct {
    char str[MAX_LENGTH]; // �ַ����飬���ڴ洢�ַ���
    int length;           // ��ǰ���ĳ���
} String;

// ��ʼ����
void initString(String *s) {
    s->str[0] = '\0'; // ����Ϊ�մ�
    s->length = 0;    // ����Ϊ0
}

// ���봮
void inputString(String *s) {
    printf("�������ַ��������%d���ַ�����", MAX_LENGTH - 1);
    fgets(s->str, MAX_LENGTH, stdin); // �ӱ�׼�����ȡ�ַ���
    s->str[strcspn(s->str, "\n")] = '\0'; // ȥ�����з�
    s->length = strlen(s->str); // ���´��ĳ���
}

// �����
void outputString(const String *s) {
    printf("��ǰ�ַ���Ϊ��%s\n", s->str);
}

// ���Ӵ�
void concatString(String *s1, const String *s2) {
    // ������Ӻ�ĳ����Ƿ񳬹��������
    if (s1->length + s2->length < MAX_LENGTH) {
        // ��s2�����ݸ��Ƶ�s1��ĩβ
        int i = s1->length; // ��s1��ĩβ��ʼ
        for (int j = 0; j < s2->length; j++) {
            s1->str[i++] = s2->str[j]; // ����ַ�����
        }
        s1->str[i] = '\0'; // ����ַ���������־
        s1->length += s2->length; // ���³���
    } else {
        printf("���Ӻ���ַ������ȳ���������ƣ�\n");
    }
}

// �Ƚϴ�
int compareString(const String *s1, const String *s2) {
    int i = 0;
    // ���������ַ������Ƚ��ַ�
    while (i < s1->length && i < s2->length) {
        if (s1->str[i] != s2->str[i]) {
            return s1->str[i] - s2->str[i]; // �����ַ��Ĳ�ֵ
        }
        i++;
    }
    // ���s1�ĳ��ȴ���s2����s1����s2�����s2�ĳ��ȴ���s1����s1С��s2
    return s1->length - s2->length;
}

// ��������S�е�pos���ַ�֮�����T��ȵ��ִ���λ��
int index(String *s, String *t, int pos) {
    // �������
    if (s == NULL || t == NULL || pos < 1) {
        return -1; // ����-1��ʾ��Ч����
    }

    int n = s->length; // �����ĳ���
    int m = t->length; // �Ӵ��ĳ���

    // posΪ1-based������תΪ0-based����
    pos--;

    // ��posλ�ÿ�ʼ��������
    for (int i = pos; i <= n - m; i++) {
        // �Ƚϵ�ǰ�Ӵ���T
        if (strncmp(s->str + i, t->str, m) == 0) {
            return i; // ����ƥ�����ʼ����
        }
    }

    return -1; // ���δ�ҵ�ƥ�䣬�򷵻�-1
}


// ��sub���ش�s�ĵ�pos���ַ��𳤶�Ϊlen���ִ�,���Ӵ�
String Substring(String *sub, String s, int pos, int len){
    if (pos < 1 || pos > s.length || len < 0 || (pos + len - 1) > s.length) {
        sub->length = 0;
        sub->str[0] = '\0'; // ��Ϊ���ַ���
        return *sub; // ���ؿ��Ӵ�
    }
    for(int i = 1; i <= len; i++){
        sub->str[i] = s.str[pos + i - 1];
    }

    // ����ַ���������
    sub->str[len] = '\0';
    sub->length = len; // �����Ӵ��ĳ���

    return *sub; // �����Ӵ�
}

int main() {
    String str1, str2;

    // ��ʼ����
    initString(&str1);
    initString(&str2);

    // ���봮
    inputString(&str1);
    inputString(&str2);

    // �����
    outputString(&str1);
    outputString(&str2);

    // ���Ӵ�
    concatString(&str1, &str2);
    printf("���Ӻ���ַ���Ϊ��%s\n", str1.str);

    // �Ƚϴ�
    int cmpResult = compareString(&str1, &str2);
    if (cmpResult == 0) {
        printf("�����ַ�����ȡ�\n");
    } else if (cmpResult < 0) {
        printf("��һ���ַ���С�ڵڶ����ַ�����\n");
    } else {
        printf("��һ���ַ������ڵڶ����ַ�����\n");
    }

    // ʾ���ַ�������
    String s = {"hello world", 11};
    String t = {"hello", 5};
    int pos = 1; // �ӵ�8���ַ���ʼ����

    int result = index(&s, &t, pos);

    if (result != -1) {
        printf("Substring found at position: %d\n", result + 1); // ���1-based����
    } else {
        printf("Substring not found.\n");
    }


    String s1, sub;
    initString(&s1);
    initString(&sub);
    strcpy(s1.str, "Hello, World!"); // ��ʼ���ַ���
    s.length = strlen(s1.str); // ���㳤��

    int pos1 = 2; // �Ӵ���ʼλ��
    int len = 5; // �Ӵ�����

    Substring(&sub, s1, pos1, len); // ��ȡ�Ӵ�

    printf("�Ӵ�: %s\n", sub.str); // ����Ӵ�
    printf("�Ӵ�����: %d\n", sub.length); // ����Ӵ�����


    return 0;
}
