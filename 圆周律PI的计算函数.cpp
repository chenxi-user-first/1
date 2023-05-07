#include<iostream>
#include<cstdio>
#include<cstdlib>

using namespace std;

#define MORE 5

typedef struct listnode {
    int data;
    listnode* pre;
    listnode* next;
}listnode, * list;


void main_calculate(list Temp_storage, list Final_result);
void Multiplication(list Temp_storage, int molecule);
void Divide(list Temp_storage, int denominator);
void Add(list Temp_storage, list Final_result);

list Initialize_List()
{
    list temp;
    temp = (list)malloc(sizeof(listnode));
    temp->data = 2;
    temp->pre = temp;
    temp->next = temp;
    return temp;
}

void Extend_List(list p, int n, int data1)
{
    for (int i = 0; i < n + MORE; i++)
    {
        listnode* l, * temp;
        l = p;
        if (l == NULL) {
            return;
        }
        l = l->pre;
        temp = (list)malloc(sizeof(listnode));
        temp->data = data1;
        temp->next = l->next;
        temp->pre = l;
        l->next->pre = temp;
        l->next = temp;
    }
}

void Destroy_List(list p)
{
    list temp;
    temp = p->next;
    while (temp != p) {
        p->next = temp->next;
        free(temp);
        temp = p->next;
    }
    p->pre = p;
    free(p);
    p = NULL;
}

char* transition(list l, int n)
{
    char* f = (char*)malloc((n + 2) * sizeof(char));
    int i = 0;
    f[i++] = l->data + '0';
    f[i++] = '.';
    for (l = l->next; i < n + 2; i++, l = l->next)
    {
        f[i] = l->data + '0';
    }
    f[i] = '\0';
    return f;
}



int main()
{
    int n;
    cin >> n;
    list Temp_storage;//��ÿһ�������̩��չ��ʽ������
    list Final_result;//�������Ǹ���͵õ��Ż�������ս��
    Temp_storage = Initialize_List();
    Extend_List(Temp_storage, n, 0);
    Final_result = Initialize_List();
    Extend_List(Final_result, n, 0);
    main_calculate(Temp_storage, Final_result);
    char* result = transition(Final_result, n);
    printf("%s", result);
    Destroy_List(Temp_storage);
    Destroy_List(Final_result);
    return 0;
}


void main_calculate(list Temp_storage, list Final_result)
{
    for (int j = 1, k = 3; j < 2000; j++) {//���ѭ��Խ����������Խ���ԣ��õ�������Խ��׼
        Multiplication(Temp_storage, j);
        Divide(Temp_storage, k);
        Add(Temp_storage, Final_result);
        k += 2;
    }
}

void Multiplication(list Temp_storage, int molecule) {
    int temp, ret = 0;
    list p;
    p = Temp_storage->pre;

    while (p != Temp_storage) {//�߾����㷨 ���߾��������Ե;�����
        temp = p->data * molecule + ret;
        p->data = temp % 10;
        ret = temp / 10;
        p = p->pre;
    }
    p->data += ret;
}

void Divide(list Temp_storage, int denominator) {
    int temp, ret = 0;
    list p;
    p = Temp_storage;
    while (1) {//�߾����㷨 ���߾��������Ե;�����
        temp = p->data + ret * 10;
        ret = temp % denominator;  //����
        p->data = temp / denominator;
        p = p->next;
        if (p == Temp_storage)
            break;
    }
}

void Add(list Temp_storage, list Final_result) {
    int temp, ret = 0;//�߾��ȼӷ����߾��ȼӸ߾���
    list p, q;
    p = Temp_storage->pre;
    q = Final_result->pre;
    while (1) {
        temp = p->data + q->data + ret;
        ret = temp / 10;
        q->data = temp % 10;
        p = p->pre;
        q = q->pre;
        if (p == Temp_storage->pre)  break;
    }
}


