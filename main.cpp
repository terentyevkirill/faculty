    #include <iostream>
    #include <iomanip>
    #include <stdio.h>
    #include <fstream>
    #include <cstdio>
    #include <cstring>
    #include <cstdlib>
    #include <Windows.h>
    #include <conio.h>
    #include <cctype>
    #include <io.h>
    #define MAX 50
    using namespace std;

    /*��������� ������*/
    /*��������� "������ � ������"*/
    struct Data {
        char faculty[MAX]; //���������
        char group[MAX]; //�������� ������
        int students; //���������� ���������
        int grants; //���������� ���������� ���������
        float note; //������� ����};
        char starosta[MAX]; //������� ��������
    };
    /*��������� "����"*/
    struct Node {
        Data *data;
        Node *next;
        Node *prev;
    };
    /*��������� "������"*/
    struct LinkedList {
        int size;
        Node *head;
        Node *tail;
    };

    /*�������� ����������� �������*/
    /*�������� ������*/
    LinkedList *CreateLinkedlist();
    /*�������� ������*/
    void DeleteLinkedList (LinkedList **list);
    /*������� �� ������� ������*/
    int ListIsEmpty(LinkedList *list);
    /*���� ������ �������������*/
    Data* DataInput(LinkedList *list);
    /*�������� �� ���������� � ������ �������� ������*/
    int OriginalData (LinkedList *list, char group[]);
    /*�������� �������� �� �������� ������*/
    int DelElement(LinkedList *list);
    /*���������� ��������*/
    int AddElement(LinkedList *list);
    /*������� �������� � ����� ������*/
    void PushBack(LinkedList *list, Data *data);
    /*������� �������� � ������ ������*/
    void PushFront (LinkedList *list, Data *data);
    /*������� �������� ����� �������� �����*/
    void PushBefore (LinkedList *list, Node *tmp, Data *data);
    /*���������� ������*/
    int InsertionSort (LinkedList **list);
    /*����� �������� �� ��������� ���������*/
    int FindElement(LinkedList *list);
    /*����� ����� ������ �� �����*/
    void PrintLinkedList(LinkedList *list);
    /*����� ��������� ������ �� �����*/
    void PrintData (Data *data);
    /*����� ������ ����������� ��� ����������*/
    void FacultyList(LinkedList *list);
    /*������� ���������� ���������/��������� �� �������� ����������*/
    int NumberOfStudentsOrGrantsOnFaculty (LinkedList *list, int parameter);
    /*����� ����� � ������� �������, �� ������� ������ ���� ���������*/
    int NoteHigher (LinkedList *list);
    /*��������� ���������*/
    void Header();
    /*����*/
    void Menu();
    /*����� ������ ����*/
    int MenuChoice();
    /*����� �� ���������*/
    int Exit();

    /*������� ������ � �������*/
    /*����� ������ ������ �� ������� ����� �� �����*/
    int ShowFiles();
    /*��������� ����� ����� � �������*/
    FILE *ChooseInputFile(FILE *f, char *filename);
    /*�������� ������� ����� � �������� ������ ���������*/
    int OpenAnotherInputFile(FILE *f, char *filename, LinkedList **list);
    /*��������������� ������ ������ �� �����*/
    void ReadFromFile (FILE *f, LinkedList *list);
    /*�������� ������ ����� � �������*/
    FILE* CreateNewDatabase(FILE *f, char *filename);
    /*����������*/
    int Save(FILE *f, LinkedList *list, char *filename);
    /*��������������� ������ ������ � ����*/
    void WriteInFile (FILE *f, LinkedList *list, char *filename);

    int main()
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        char filename[MAX]; //��� �����
        FILE *f;
        int choice; //��������� � ����
        Header();
        system("cls");
        cout << "\t��� ������ � ���������� ���������� ���������� ���� � �������:"<<endl;
        f = ChooseInputFile(f, filename); //��������� ���� ��� ������
        LinkedList *list = CreateLinkedlist(); //������� ������
        if (fgetc(f) != EOF) //��������� ������ �� ����� � ������
            ReadFromFile(f, list);
        system("cls");
        /*������ � ����*/
        Menu();
        while(1){
            int flag = 0; //���� ��� �������� � ���� ��� ���������� ������� �������
            int flag_exit = 0; //���� ������������� ������ �� ���������
            /*����� ������ ����*/
            switch(MenuChoice()){
            case 1: //���������� ��������
                while(1){
                    flag = AddElement(list);
                    if (flag != 1)
                        break;
                }
                break;
            case 2: //�������� ��������
                while(1){
                    flag = DelElement(list);
                    if (flag != 1)
                        break;
                }
                break;
            case 3: //����� ��������
                while(1){
                    flag = FindElement(list);
                    if (flag != 1)
                        break;
                }
                break;
            case 4: //����� ����� ������ �� �����
                system("cls");
                cout << "\t����� ����� ������"<<endl;
                PrintLinkedList(list);
                cout << "\t��� �������� � ���� ������� ����� �������\n\t>>> ";
                choice = getch();
                flag = 2;
                break;
            case 5: //������� ���������� ���������
                while(1){
                    flag = NumberOfStudentsOrGrantsOnFaculty(list, 1);
                    if (flag != 1)
                        break;
                }
                break;
            case 6: //����� ����� � ������� ���� ��������
                while(1){
                    flag = NoteHigher(list);
                    if (flag != 1)
                        break;
                } break;
            case 7: //������� ���������� ���������
                while(1){
                    flag = NumberOfStudentsOrGrantsOnFaculty(list, 2);
                    if (flag != 1)
                        break;
                }
                break;
            case 8: //���������� ������ �� �������� �����
                flag = InsertionSort(&list);
                break;
            case 9: //������� ������ ����
                while(1){
                    system("cls");
                    cout << "\t������ ���� � �������"<<endl;
                    flag = OpenAnotherInputFile(f, filename, &list);
                    if (flag != 1)
                        break;
                }
                break;
            case 10: //����������
                system("cls");
                if (ListIsEmpty(list))
                    cout << "\n\t������ ����, ��� ��������� ��� ����������. �� ������ ��������� ������ ������"<<endl;
                flag = Save(f, list, filename);
                break;
            }
            if (flag == 1){
                flag_exit = Exit();
            }
            if (flag == 2){
                system("cls");
                Menu();
                continue;
            }
            if (flag_exit == 1){
                cout << "\t�� ��������!" << endl;
                cout << "\n\n\n\n\n\n\n\n\t������ ��������� ���176 (2018)" << endl;
                break;
            }
            if (flag_exit == 2){
                cout << "\t������ ������, ������� � ����."<<endl;
                system("cls");
                Menu();
                continue;
            }
        }
        fclose(f); //�������� �������� ����
        DeleteLinkedList(&list); //�������� ������
        return 0; //���������� ���������
    }
    /*++++++++++++++++++++++++
    /*�������� ������
    /*++++++++++++++++++++++++*/
    LinkedList *CreateLinkedlist(){
        LinkedList *tmp = new LinkedList;
        tmp->size = 0;
        tmp->head = tmp->tail = NULL;
        return tmp;
    }
    /*+++++++++++++++++++++++
    /*�������� ������
    /*++++++++++++++++++++++++*/
    void DeleteLinkedList (LinkedList **list) {
        Node *tmp = (*list)->head;
        Node *next = NULL;
        while (tmp) {
            next = tmp->next;
            delete tmp;
            tmp = next;
        }
        delete (*list);
        (*list) = NULL;
    }
    /*++++++++++++++++++++++++++++++++++
    /*�������� �� ������ ������
    /*return 0 - ������, 1 - �� ������
    /*+++++++++++++++++++++++++++++++++*/
    int ListIsEmpty(LinkedList *list)
    {
        if (list->head == NULL)
            return 1;
        else return 0;
    }
    /*+++++++++++++++++++++++++++++++++++++++++++
    /*���� ������ �������������
    /*��������� ��������� � ���������� �������
    /*++++++++++++++++++++++++++++++++++++++++++*/
    Data* DataInput(LinkedList *list)
    {
        int i = 0; //�������
        int flag = 0; //���� ���������� �������� ������ � ������
        int spaceflag; //���� ���������� �������� � ��������� �������
        char group[MAX]; //������
        char faculty[MAX]; //���������
        char starosta [MAX]; //������� ��������
        float nf; //������� ����
        int n; //�������� ������������� �������� (����� ��������� � ���������)
        Data* data = new Data;
        cout << "\n\t������� ������ � ������:"<<endl;
        /*���� ������ � �������� ������������*/
        cout << "\t������� �������� ������ (������ ����� - ��172, ���176):"<<endl;
        while (1){
            cout<<"\t>>>";
            fflush(stdin);
            gets(group);
            int length = strlen(group);
            spaceflag = 0;
            for(i = 0; i < strlen(group); i++){
                if (isspace(group[i])){
                    spaceflag = 1;
                }
            }
            if (spaceflag || strlen(group) == 0 || strlen(group) < 5 || strlen(group) > 6 || !isdigit(group[length-1]) || !isdigit(group[length-2]) || !isdigit(group[length-3])) {
                cout << "\t������ �����, ���������:" << endl;
                continue;
            }
            else {
                flag = OriginalData(list, group);
                if (flag == 1) {
                    cout << "\t������ "<<group<<" ��� ���� � ������, ��������� ����:"<<endl;
                    continue;
                }
                else break;
            }
        }
        strcpy(data->group, group);
        /*���� ���������� � �������� ������������*/
        cout << "\t������� �������� ���������� (������ ����� - �����, ���):" << endl;
        while (1) {
            cout << "\t>>> ";
            fflush(stdin);
            gets(faculty);
            spaceflag = 0;
            for(i = 0; i < strlen(faculty); i++){
                if (isspace(faculty[i])){
                    spaceflag = 1;
                }
            }
            if (spaceflag || strlen(faculty) == 0 || strlen(faculty) > 10) {
                cout << "\t������ �����, ���������:" << endl;
                continue;
            } else break;
        }
        strcpy(data->faculty, faculty);
        /*���� ����� ��������� � �������� ������������*/
        cout << "\t������� ���������� ��������� (����� �����):" << endl;
        while (1) {
            cout << "\t>>> ";
            n = 0;
            cin >> n;
            fflush(stdin);
            if (!cin || n < 0) {
                cout << "\t������ �����, ���������:" << endl;
                cin.clear();
                continue;
                //while (cin.get() != '\n');
            }
            else break;
        } data->students = n;
        /*���� ����� ��������� � �������� ������������*/
        cout << "\t������� ���������� ���������, ���������� ��������� (����� �����):" << endl;
        while (1) {
            cout << "\t>>> ";
            fflush(stdin);
            n = 0;
            cin >> n;
            if (!cin || n < 0 || n > data->students) {
                if (n > data->students)
                    cout << "\t������, ��������� ����� ������ ���������� ��������� � ������, ��������� ����: " << endl;
                else
                    cout << "\t������ �����, ���������:" << endl;
                cin.clear();
                continue;
            }
            else break;
        } data->grants = n;
        /*���� ������ � �������� ������������*/
        cout << "\t������� ������� ���� ������ (���. ����� �� 0 �� 100, ������ ����� - �.��) :" << endl;
        while (1) {
            cout << "\t>>> ";
            fflush(stdin);
            nf = 0.00; //��� �������� ���. ��������
            cin >> nf;
            if (!cin || nf < 0 || nf > 100) {
                cout << "\t������ �����, ���������:" << endl;
                cin.clear();
                while (cin.get() != '\n');
            }
            else break;
        } data->note = nf;
        /*���� ������� �������� � �������� ������������*/
        cout << "\t������� ������� �������� (��� ��������):" << endl;
        while (1) {
            cout << "\t>>> ";
            fflush(stdin);
            gets(starosta);
            spaceflag = 0;
            for(i = 0; i < strlen(starosta); i++){
                if (isspace(starosta[i])){
                    spaceflag = 1;
                }
            }
            if (spaceflag || strlen(starosta) == 0) {
                cout << "\t������ �����, ���������:" << endl;
                continue;
            }
            else break;
        }
        strcpy(data->starosta, starosta);
        fflush(stdin);
        /*����� ��������� ������ �� �����*/
        cout << "\t���� ������ � ������ " << data->group << " ��������."<<endl;
        PrintData(data);
        return data;
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++++
    /*�������� �� ��������� � ������ �������� ������
    /*���������� 1, ���� ����� ������ ��� ���� � ������
    /*+++++++++++++++++++++++++++++++++++++++++++++++++*/
    int OriginalData (LinkedList *list, char group[MAX])
    {
        int flag = 0;
        Node *tmp = NULL;
        tmp = list->head;
        while (tmp){
            if(strcmp(group, tmp->data->group) == 0)
                flag = 1;
            tmp = tmp->next;
        }
        return flag;
    }
    /*+++++++++++++++++++++++++++++++++++++++++
    /*�������� ������ �� ������
    /*return 1 - ������� ���, 2 - ����� � ����
    /*++++++++++++++++++++++++++++++++++++++++++*/
    int DelElement(LinkedList *list)
    {
        system("cls");
        cout << "\t������� �������\n"<<endl;
        int choice; //���������
        int flag = 0; //���� ������
        char group[MAX]; //�������� ��������� ������
        if (ListIsEmpty(list)){
            cout << "\t������ ����, ��� ��������� ��� ��������.\n"<<endl;
            cout << "\t������� ����� ������� ��� �������� � ����\n\t>>> ";
            getch();
            return 2;
        }
        Node *del = NULL;
        Node *tmp = NULL;
        tmp = list->head;
        cout << "\t������� ������ �������� ������ ��� � ��������:"<<endl;
        cout<<"\t>>> ";
        fflush(stdin);
        gets(group);
        /*���� ���������� �� ��������� ������ � ������*/
        while(tmp){
            if (strcmp(tmp->data->group, group) == 0){
                del = tmp;
                break;
            }
            tmp = tmp->next;
        }
        /*���� �� ������� ����� ������*/
        if(!del){
            cout << "\n\t�� ������ ������� "<<group<<" �� ������ �� �������. ������ ��������� ����?"<<endl;
            cout << "\t[1] ��\n\t[2] ������� � ����"<<endl;
            while(1){
                cout << "\t>>> ";
                fflush(stdin);
                switch(choice = getch()) {
                    case 49: cout <<"[1]"<<endl; return 1; break;
                    case 50: cout << "[2]"<<endl; return 2; break;
                    default: cout << "��������� ����"<<endl; continue;
                } break;
            }
        }
        /*���� �������, �������*/
        if(del){
            cout << "\t�� ������ ������� "<<group<<" �������:"<<endl;
            PrintData(del->data); //������� ��������� ������ �� �����
            cout << "\n\t�� ������������� ������ ������� ���� ������� �� ������? ������� ��������� ������ ����������!\n\t[1] ��\n\t[2] ������� � ����"<<endl;
            while(1){
                cout << "\t>>> ";
                switch(choice = getch()) {
                    case 49: cout <<"[1]"<<endl; flag = 1; break;
                    case 50: cout << "[2]"<<endl; return 2; break;
                    default: cout << "��������� ����"<<endl; continue;
                } break;
            }
            if (flag == 1){ /*���������� �������� �� ������*/
                /*���� ������� �� ������, ������ ���, ����� ���������� ����� ���
                ������� �������� �� ��������� ����� ����*/
                if (del->prev)
                    del->prev->next = del->next;
                /*���� ������� ������, �� ������ ��������� �� ��� ��������*/
                if (!del->prev)
                    list->head = del->next;
                /*���� ������� �� ���������, ������ ���, ����� ��������� ����� ����
                ������� �������� �� ���������� ����� ��� */
                if (del->next)
                    del->next->prev = del->prev;
                /*���� ������� ���������, �� ������ ���������� ����� ��� ���������*/
                if (!del->next)
                    list->tail = del->prev;
                delete del;
                list->size--;
                cout << "\t������� " << group << " ������� ������ �� ������."<<endl;
                if (!ListIsEmpty(list)){
                    cout << "\t������ ������� ��� ���� �������?\n\t[1] ��\n\t[2] ������� � ����"<<endl;
                    while(1){
                        cout<<"\t>>> ";
                        switch(choice = getch()) {
                            case 49: cout <<"[1]"<<endl; return 1; break; //���������� ��������
                            case 50: cout << "[2]"<<endl; return 2; break; //������� � ����
                            default: cout << "��������� ����"<<endl; continue;
                        } break;
                    }
                }
                else{
                    cout << "\n\t������ ����\n\t��� �������� � ���� ������� ����� �������\n\t>>> ";
                    fflush(stdin);
                    choice = getch();
                    return 2;
                }
            }
        }
    }
    /*+++++++++++++++++++++++++++++++++++++++
    /*���������� �������� � ������
    /*return 1 - �������� ���, 2 - � ����
    /*+++++++++++++++++++++++++++++++++++++++*/
    int AddElement(LinkedList *list)
    {
        Data *data = new Data;
        int choice;
        int flag;
        system("cls");
        cout << "\t �������� �������"<<endl;
        while(1){
            data = DataInput(list);
            cout << "\t��������� ��������� ������?"<<endl<<"\t[1] ��"<<endl<<"\t[2] ���"<<endl<<"\t>>> ";
            switch(choice = getch()){
                case 49: cout << "[1]"<<endl; flag = 1; break; //���������
                case 50: cout << "[2]"<<endl; flag = 0; break; //�� ���������
                default: cout << "��������� ����"<<endl; cout << "\t>>> "; continue;
            } break;
        }
        if (flag){
            PushBack(list, data); //���������� � ����� ������
            cout<<"\t������ ���������"<<endl;
        }
        cout<<"\n\t������ �������� ������ �������?"<<endl<<"\t[1] ��"<<endl<<"\t[2] ����� � ����"<<endl;
        while(1){
            cout << "\t>>> ";
            switch(choice = getch()) {
                case 49: cout <<"[1]"<<endl; return 1; break;
                case 50: cout <<"[2]"<<endl; return 2; break;
                default: cout << "��������� ����"<<endl; continue;
            } break;
        }
    }
    /*++++++++++++++++++++++++++++++++++++
    /*���������� �������� � ����� ������
    /*++++++++++++++++++++++++++++++++++++*/
    void PushBack(LinkedList *list, Data *data) {
        Node *tmp = new Node;
        if (tmp == NULL){
            cout << "\t�� ������� �������� ������� � ����� ������." << endl;
            exit(2);
        }
        tmp->data = data; //��������� ���� �������
        /*��������� ����� ������ � ����� ���������*/
        tmp->next = NULL;
        tmp->prev = list->tail;
        if (list->tail)
            list->tail->next = tmp;
        list->tail = tmp;
        /*���� ������ ����, �� ������� ���������� � �������*/
        if (list->head == NULL)
            list->head = tmp;
        list->size++; //������ ������ �������������
    }
    /*+++++++++++++++++++++++++++++++++++++
    /*���������� �������� � ������ ������
    /*+++++++++++++++++++++++++++++++++++++*/
    void PushFront (LinkedList *list, Data *data){
        Node *tmp = new Node;
        if (tmp == NULL) {
            cout << "\t�� ������� �������� ������� � ������ ������." << endl;
            exit(2);
        }
        tmp->data = data; //��������� ���� �������
        /*��������� ������ ������ � ����� ���������*/
        tmp->next = list->head;
        tmp->prev = NULL;
        if (list->head)
            list->head->prev = tmp;
        list->head = tmp;
        /*���� ������ ����, �� ����� ������� ���������� � �������*/
        if (list->tail == NULL)
            list->tail = tmp;
        list->size++; //������ ������ �������������
    }
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /*������� �������� ����� �������� TMP
    /*������������ ��� ���������� (s_list - ��������������� ������)
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    void PushBefore (LinkedList *s_list, Node *tmp, Data *data)
    {
        if (tmp == NULL){
            cout << "\t������ ��������� ������." << endl;
            exit(2);
        }
        /*���� ������� tmp ������ � ������, ��������� ���� � ������*/
        if (!tmp->prev){
            PushFront(s_list, data);
            return;
        }
        /*���� ins ����� ����������� ����� tmp*/
        Node *ins = new Node;
        ins->data = data;
        ins->prev = tmp->prev;
        ins->prev->next = ins;
        ins->next = tmp;
        tmp->prev = ins;
        s_list->size++;
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++++++
    /*���������� ���������, ����������� �������� ������
    /*return 2 - ������� � ����
    /*+++++++++++++++++++++++++++++++++++++++++++++++++*/
    int InsertionSort (LinkedList **list)
    {
        int flag = 0; //������ ����������
        int choice; //���������
        system("cls");
        cout << "\t���������� �� ���� \"������� ����\"\n" << endl;
        if (ListIsEmpty(*list)){
            cout << "\t������ ����" << endl;
            cout << "\n\t������� ����� ������� ��� �������� � ����...\n\t>>> ";
            fflush(stdin);
            getch();
            return 2;
        }
        cout << "\t[1] �� �����������\n\t[2] �� ��������" << endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
                case 49: flag = 1; break; //�� �����������
                case 50: flag = 2; break; //�� ��������
                default: cout << "��������� ����!" << endl; continue;
                }
            break;
        }
        LinkedList *s_list = CreateLinkedlist(); //��������������� ������
        Node *sorted = NULL; //���� ���������������� ������
        Node *unsorted = NULL; //���� ��������� ������
        /*��������� ������ �� ���� ������� ����*/
        unsorted = (*list)->head;
        while(unsorted) {
            sorted = s_list->head;
            if (flag == 1)
                while (sorted && (unsorted->data->note > sorted->data->note))
                    sorted = sorted->next;
            if (flag == 2)
                while (sorted && (unsorted->data->note < sorted->data->note))
                    sorted = sorted->next;
            if (sorted)
                PushBefore(s_list, sorted, unsorted->data);
            else
                PushBack(s_list, unsorted->data);
            unsorted = unsorted->next;
        }
        system("cls");
        cout << "\t���������� �� ���� \"������� ����\"\n" << endl;
        if (flag == 1)
            cout << "\t��������������� �� ����������� ������:" << endl;
        if (flag == 2)
            cout << "\t��������������� �� �������� ������:" << endl;
        /*������� ��������������� ������ �� �����*/
        PrintLinkedList(s_list);
        cout << "\t������ ��������� ��������������� ������?\n\t[1] ��\n\t[2] ����� � ����" << endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
                case 49: //��������� ��������������� ������
                    delete(*list);
                    *list = s_list;
                    cout << "\n\t��������������� ������ ��������.\n"
                        << "\t������� ����� �������, ����� ��������� � ����...\n\t>>> " << endl;
                    getch();
                    return 2;
                    break;
                case 50: return 2; break;
                default: cout << "��������� ����!" << endl; continue;
            }
            break;
        }
    }
    /*++++++++++++++++++++++++++++++++++++++
    /*����� �� ���������� ��� �� ������
    /*return 1 - ������ �����, 2 - � ����
    ++++++++++++++++++++++++++++++++++++++*/
    int FindElement(LinkedList *list)
    {
        char choice; //����� ��������
        int flag = 0; //���� ������
        int found = 0; //���� ����������
        system("cls");
        cout << "\t����� �������� �� ���������� ��������� (���������, ������):"<< endl;
        if (ListIsEmpty(list)){
            cout << "\n\t������ ����\n"<<endl;
            cout << "\t������� ����� ������� ��� �������� � ����\n\t>>> ";
            choice = getch();
            return 2;
        }
        cout << "\n\t[1] ����� �������� �� ����������:\n\t[2] ����� �������� �� �������� ������\n\t[3] ����� � ����"<<endl;
        while(1){
            cout << "\t>>> ";
            switch(choice = getch()){
            case 49: cout << "[1]" << endl; flag = 1; break; //����� �� ����������
            case 50: cout << "[2]" << endl; flag = 2; break; //����� �� ������
            case 51: cout << "[3]" << endl; return 2; break;
            default: cout << "��������� ����!" << endl; continue;
            }
            break;
        }
        char search[MAX];
        system("cls");
        if (flag == 1){
            cout << "\t����� �������� �� ����������:\n\n";
            FacultyList(list);
            cout << "\t������� �������� ����������:";
        }
        if (flag == 2){
            cout << "\t����� �������� �� �������:\n\n";
            cout << "\t������� �������� ������:";
        }
        /*���� ������������� ���������� ��� ������*/
        while (1) {
            cout << "\n\t>>> ";
            fflush(stdin);
            gets(search);
            if (strlen(search) == 0 || strlen(search) > 10) {
                cout << "\t������ �����, ���������:" << endl;
                continue;
            } else break;
        }
        /*��������� ������ ����������*/
        LinkedList *foundlist = CreateLinkedlist();
        Node *tmp = new Node;
        tmp = list->head;
        while(tmp){
            if (flag == 1) //���� ���� �� �����������
                if(strncmp(search, tmp->data->faculty, strlen(search)) == 0)
                    found = 1;
            if (flag == 2) //���� ���� �� �������
                if(strncmp(search, tmp->data->group, strlen(search)) == 0)
                    found = 1;
            if (found)
                PushBack(foundlist, tmp->data); //���������� ��������� ������� � ������
            tmp = tmp->next;
            found = 0;
        }
        if(!ListIsEmpty(foundlist)){
            cout << "\n\t�� ������ ������� \"" << search << "\" ������� " << foundlist->size <<" �����(�):"<<endl;
            PrintLinkedList(foundlist);
        }
        else
            cout << "\n\t�� ������ ������� \"" << search << "\" ������ �� �������.\n" << endl;
        DeleteLinkedList(&foundlist);
        cout << "\t������ ��������� �����?\n\t[1] ��\n\t[2] ����� � ����"<<endl;
        while(1){
            cout << "\t>>> ";
            switch(choice = getch()){
                case 49: cout << "[1]" << endl; return 1; break;
                case 50: cout << "[2]" << endl; return 2; break;
                default: cout << "��������� ����!" << endl; continue;
            }
            break;
        }
    }
    /*++++++++++++++++++++++++++++++++++++++++++++
    /*����� ����� ������ �� ����� � ���� �������
    /*+++++++++++++++++++++++++++++++++++++++++++*/
    void PrintLinkedList(LinkedList *list)
    {
        if (ListIsEmpty(list))
            cout << "\n\t������ ����"<<endl;
        else{
            Node *tmp = list->head;
            cout << "\n\t|-------------------------------------------------------------------------------------------------|"<<endl;
            cout << "\t|������  |���������  |����� ���������  |����� ���������  |������� ����  |������� ��������         |" << endl;
            cout << "\t|-------------------------------------------------------------------------------------------------|"<<endl;
            while (tmp) {
                cout << left << setfill(' ') << "\t|" << setw(8) << tmp->data->group << "|" << setw(11) << tmp->data->faculty << "|" << setw(17) <<
                tmp->data->students << "|" << setw(17) << tmp->data->grants << "|" << setw(14) << setprecision(2) << setiosflags(ios::fixed | ios::showpoint)
                << tmp->data->note <<"|"<< setw(25) << tmp->data->starosta <<"|" << endl;
                tmp = tmp->next;
            }
            cout << "\t|-------------------------------------------------------------------------------------------------|"<<endl;
        }
        cout << endl;
    }
    /*+++++++++++++++++++++++++++++++++++++++++++
    /*����� �� ����� ��������� ������
    /*��� ������ ������ �� ������ ����������� ����
    /*+++++++++++++++++++++++++++++++++++++++++++*/
    void PrintData (Data *data)
    {
        cout << "\t|-------------------------------------------------------------------------------------------------|"<<endl;
        cout << "\t|������  |���������  |����� ���������  |����� ���������  |������� ����  |������� ��������         |" << endl;
        cout << "\t|-------------------------------------------------------------------------------------------------|"<<endl;
        cout << left << setfill(' ') << "\t|" << setw(8) << data->group << "|" << setw(11) << data->faculty << "|" << setw(17) <<
        data->students << "|" << setw(17) << data->grants << "|" << setw(14)
         << setprecision(2) << setiosflags(ios::fixed | ios::showpoint) << data->note <<"|"<< setw(25) << data->starosta <<"|" << endl;
        cout << "\t|-------------------------------------------------------------------------------------------------|"<<endl;
    }
    /*+++++++++++++++++++++++++++++++++++++++++++++
    /*����� ����������� �� ����� ��� ����������
    +++++++++++++++++++++++++++++++++++++++++++++++*/
    void FacultyList(LinkedList *list)
    {
        int i = 0, count = 1, j; //��������
        int found; //���� ���������� ����������
        char faculty_list[list->size][MAX]; //������ ����� � ���������� �����������
        cout << "\t������ �����������:"<<endl;
        Node *tmp = new Node;
        tmp = list->head;
        /*�������� ��� ���������� �� ������ � ������*/
        while(tmp){
            strcpy(faculty_list[i], tmp->data->faculty);
            i++;
            tmp = tmp->next;
        }
        /*������ ������� �� ������� � ������� �� �� �����*/
        for (i = 0; i < list->size; i++){
            found = 0;
            for (j = i; j >= 0; j--){
                if(strcmp(faculty_list[i], faculty_list[j]) == 0)
                    found++;
            }
            if (found <= 1)
                cout << "\t" << count++ << ")" << faculty_list[i] << endl;
        }
        /*������� ��*/
        delete(tmp);
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /*������� ������ ���������� ��������� (parameter - 1) � ��������� (2)
    /*�� �������� ����������
    /*parameter - ���������� ������� ��������(1 ��� 2)
    /*
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    int NumberOfStudentsOrGrantsOnFaculty (LinkedList *list, int parameter)
    {
        int choice; //���������
        int grants = 0; //����� ���������
        int students = 0; //����� ���������
        char faculty[MAX]; //�������� �������� ����������
        system("cls");
        if (parameter == 1)
            cout << "\t������� ������ ���������� ��������� �� �������� ����������\n" << endl;
        if (parameter == 2)
            cout << "\t������� ���������� ���������, ���������� ��������� �� �������� ����������\n" << endl;
        if (ListIsEmpty(list)){
            cout << "\t������ ����.\n"<<endl;
            cout << "\t������� ����� ������� ��� �������� � ����\n\t>>> ";
            getch();
            return 2; //������ - ������� � ����
        }
        FacultyList(list); //����� �������� �����������
        cout << "\n\t������� �������� ���������� �� ������:" << endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            gets(faculty);
            if (strlen(faculty) == 0 || strlen(faculty) > 10){
                cout << "\t������ �����, ���������:"<<endl;
                continue;
            } else break;
        }
        /*������� ���������� ��������� � ��������� �� �������� ����������*/
        Node *tmp = new Node;
        tmp = list->head;
        while(tmp){
            if(strcmp(faculty, tmp->data->faculty) == 0){
                grants = grants + tmp->data->grants;
                students = students + tmp->data->students;
            }
            tmp = tmp->next;
        }
        delete(tmp); //������� ��
        if (!grants) //���� ������ �� �������
            cout << "\t�� ������ ������� \"" << faculty << "\" ������ �� �������." << endl;
        else
            if (parameter == 1) //����� ����� ���������
                cout << "\n\t�� ���������� \"" << faculty << "\" ������ " << students << " ���������.\n";
            if (parameter == 2) //����� ����� ���������
                cout << "\n\t�� ���������� \"" << faculty << "\" ������ " << grants << " ���������, ���������� ���������.\n";
        cout << "\n\t������ ��������� �����?\n\t[1] ��\n\t[2] ����� � ����"<<endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
                case 49: return 1; break;
                case 50: return 2; break;
                default: cout << "��������� ����!" << endl; continue;
            }
            break;
        }
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /*����� ����� � �� �������, ������ ������� ���� ��������
    /*return 1 - ��������� �����, 2 - ������� � ����
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    int NoteHigher (LinkedList *list)
    {
        int found = 0; //���� ���������� ���������� ��� ������� �����
        int choice; //���������
        float average_note = 0.00; //������� ���� �� ���� �������
        float note = 0.00; // ����, �������� �������������
        system("cls");
        cout << "\t����� ����� � ������� �������, ������� ����� ������� ���� ������ ���������\n" << endl;
        if (ListIsEmpty(list)){
            cout << "\t������ ����" << endl;
            cout << "\n\t������� ����� ������� ��� �������� � ����\n\t>>> ";
            fflush(stdin);
            getch();
            return 2;
        }
        Node *tmp = new Node;
        tmp = list->head;
        /*�������� �������� ����� �� ���� �������*/
        while(tmp){
            average_note += tmp->data->note;
            tmp = tmp->next;
        }
        average_note = average_note/list->size;
        cout << "\t������� ���� �� ���� �������: " << setprecision(2) << setiosflags(ios::fixed | ios::showpoint) << average_note << endl;
        /*���� ����� �������������*/
        cout << "\n\t������� ���� ��� ������ �����, ������� ������� ���� ���� ���� ���������\n"
            << "\t(������ ����� - ������������ ����� �� 0 �� 100)" << endl;
        while (1) {
            cout << "\t>>> ";
            fflush(stdin);
            cin >> note;
            if (!cin || note < 0 || note > 100) {
                cout << "\t������ �����, ���������:" << endl;
                cin.clear();
                while (cin.get() != '\n');
            }
            else break;
        }
        /*����� ����� � ������� �� �������, ������� ������� ���� ���� ���������*/
        tmp = list->head;
        while(tmp) {
            if (tmp->data->note > note){
                found++;
                /*������ ���������� � ���� �������*/
                if (found == 1){
                    cout << "\n\t������ � ������� �� �������, ������� ������� ���� ���� "
                        << setiosflags(ios::fixed | ios::showpoint) << note << ":" << endl;
                    cout << "\t---------------------------------------------------\n"
                        << "\t|������  |������� ����  |������� ��������         |\n"
                        <<  "\t---------------------------------------------------" << endl;
                }
                /*����� ������ � ������� � ���� �������*/
                cout << left << "\t|" << setw(8) << tmp->data->group << "|" << setw(14) << setprecision(2)
                 << setiosflags(ios::fixed | ios::showpoint)<< tmp->data->note << "|"
                 << setw(25) << tmp->data->starosta << "|" << endl;
            }
            tmp = tmp->next;
        }
        if (found)
            cout << "\t---------------------------------------------------" << endl;
        else
            cout << "\n\t����� �� ������� ������ ���� " << setprecision(2)
                 << setiosflags(ios::fixed | ios::showpoint) << note << " �� �������." << endl;
        cout << "\n\t������ ��������� �����?\n\t[1] ��\n\t[2] ����� � ����" << endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
                case 49: return 1; break;
                case 50: return 2; break;
                default: cout << "��������� ����!" << endl; continue;
            }
        }
    }
    /*+++++++++++++++++++++
    /*��������� ���������
    /*++++++++++++++++++++*/
    void Header()
    {
        int skip;

        cout << "\n\n\t" << setfill('*') << setw(66) << "*\n"
            << "\t*\t\t\t �������� ������ \t\t\t*\n"
            << "\t*\t �� �������� \"�������������� � ����������������\" \t*\n"
            << "\t*\t\t����: \"������������ ��������� ������\"  \t\t*\n"
            << "\t*\t\t      �������� ������ ���-176    \t\t*\n"
            << "\t*\t\t\t���������� �������\t\t\t*\n"
            << "\t" << setfill('*') << setw(66) << "*\n"
            << "\t*      ������������ ���������, ������� �������� ����������:     *\n"
            << "\t* ���������, ������, ���������� ���������, ���������� ��������� *\n"
            << "\t*   � ������, ������� �������� ���������, ��.���� ������������  *\n"
            << "\t* \t \t    �� ������, ������� ��������.      \t \t*\n"
            << "\t*\t     ��������� ������ - ����������� ������   \t\t*\n"
            << "\t" << setfill('*') << setw(66) << "*\n"
            << setfill(' ') << "\n\n\t��� ������ ������ ������� ����� �������\n\t>>> ";
        skip = _getch();
        system("cls");
    }
    /*++++++++++++++++++++++
    /*���� ���������
    /*++++++++++++++++++++*/
    void Menu()
    {
        cout << "\t�������� �������� �� ������ � ������� ��������������� ��� �������:\n" << endl;
        cout << "\t[1] �������� �������\n"
            << "\t[2] ������� �������\n"
            << "\t[3] ����� �������� �� ���������� ��������� (���������, ������)\n"
            << "\t[4] ����� ����� ������\n"
            << "\t[5] ������� ������ ���������� ��������� �� �������� ����������\n"
            << "\t[6] ����� ����� � ������� �������, ������� ����� ������� ���� ������ ���������\n"
            << "\t[7] ������� ���������� ���������, ������� �������� ��������� �� �������� ����������\n"
            << "\t[8] ���������� �� ���� \"C������ ����\"\n"
            << "\t[9] ������� ���� � �������\n"
            << "\t[Esc] ��������� � �����" << endl;
    }
    /*++++++++++++++++++++++++++++++++++++++
    /*����� ������ ����
    /*���������� ����� ���������� ������
    /*+++++++++++++++++++++++++++++++++++*/
    int MenuChoice()
    {
        while (1){
            cout << "\t>>> ";
            switch (getch()){
                case 49: return 1; break;
                case 50: return 2; break;
                case 51: return 3; break;
                case 52: return 4; break;
                case 53: return 5; break;
                case 54: return 6; break;
                case 55: return 7; break;
                case 56: return 8; break;
                case 57: return 9; break;
                case 27: return 10; break;
                default: cout << "��������� ����!" << endl; continue;
            }
            break;
        }
    }
    /*+++++++++++++++++++++++++++++++++
    /*����� �� ���������
    /*return 1 - �����, 2 - � ����
    /*++++++++++++++++++++++++++++++++*/
    int Exit()
    {
        int exit_check;
        system("cls");
        cout << "\t�����" << endl;
        cout << "\n\t�� �������, ��� ������ ����� �� ���������?\n\t[1] ��"<<endl<<"\t[2] ���, ��������� � ����"<<endl;
        while(1){
            cout << "\t>>> ";
            switch(exit_check = getch()){
            case 49: cout << "[1] ��" << endl; return 1; break;
            case 50: cout << "[2] ������� � ����"<<endl; return 2; break;
            default: cout << "��������� ����"<<endl; continue;
            }
            break;
        }
    }

    /*+++++++++++++++++++++++++++++++++++++++++++
    /*����� �̨� ������ � ������� ����� �� �����
    /*return 1 - �������� ������ �����
    /*return 2 - ���� �������� �������������
    ++++++++++++++++++++++++++++++++++++++++++++*/
    int ShowFiles()
    {
        cout << "\t����� � ������� �����:\n" << endl;
        int flag = 0;
        WIN32_FIND_DATA FindFileData;
        HANDLE hf;
        hf = FindFirstFile(".\\*.txt",&FindFileData);
        if(hf != INVALID_HANDLE_VALUE){
            do{
                flag = 1;
                cout << "\t" << FindFileData.cFileName << endl;
            }
            while(FindNextFile(hf, &FindFileData) != 0);
            FindClose(hf);
        }
        if (!flag){
            return 1; //������� ����� ����
        }
        else return 2; //������ �������� �������������
    }
    /*+++++++++++++++++++++++++++++++++++++++++
    /*����� ����� ��� ���������� ������
    /*���������� ��� ������ � ����������!
    /*���������� ��������� �� ��������� ����
    /*+++++++++++++++++++++++++++++++++++++++++*/
    FILE *ChooseInputFile(FILE *f, char *filename)
    {
        int flag; //���� ������
        char choice; //���������
        while(1){
            flag = 0;
            cout << "\n\t[1] ������� ������������ ����\n\t[2] ������� ����� ����"<<endl;
            while(1){
                cout << "\t>>> ";
                switch(choice = getch()){
                    case 49:  system("cls"); flag = ShowFiles(); break; //������� ������������ ����
                    case 50:  system("cls"); f = CreateNewDatabase(f, filename); break; //������� ����� ����
                    default: cout << "��������� ����"<<endl; continue;
                }
                break;
            }
            /*���� ������������ ������� ������� ������������ ����,
            /*�� ������� �� ���������, ��������� ����� ����*/
            if (flag == 1){
                system("cls");
                cout << "\t������ � ������� ����� �� �������\n"<<endl;
                f = CreateNewDatabase(f, filename);
            }
            /*���� �������� �����*/
            if (flag == 2){
                cout << "\n\t������� �������� ����� �� ������(*.txt):"<<endl;
                while(1){
                    cout << "\t>>> ";
                    fflush(stdin);
                    gets(filename);
                    if (strlen(filename) > 4 && !strcmp(filename + strlen(filename) - 4, ".txt"))
                        break;
                    else{
                        cout << "\t������������ ��� �����, ��������� ����"<<endl;
                        continue;
                    }
                }
                if ((f = fopen(filename, "r")) == NULL){
                    system("cls");
                    cout << "\t������ �������� �����!"<<endl;
                    cout << "\n\t��������, �� ����� �������� �����, �������� ��� � �����\n\t���������:\n"<<endl;
                    continue;
                }
                if (fgetc(f) == EOF){
                    system("cls");
                    cout << "\t������ �������� �����!" << endl;
                    cout << "\n\t��������, ��������� ���� ���� ��� ������ ����\n\t���������:\n" << endl;
                    continue;
                }
            }
            if (f == NULL){
                cout << "\n\t��������� ���� ����� ���� ��� ����������.\n\t���������:\n"<<endl;
                continue;
            }
            break;
        }
        return f;
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++
    /*�������� ������� ����� ��� ������
    /*return 1 - ������ ������� ������, 2 - � ����
    +++++++++++++++++++++++++++++++++++++++++++++++*/
    int OpenAnotherInputFile(FILE *f, char *filename, LinkedList **list)
    {
        char save_check[MAX]; //������ ��� ������������ ������ � ����
        int choice; //���������
        int flag = 0; //���� ������
        cout << "\n\t������ ��������� ������� ��������� � ����� \""<<filename<<"\" ����� ��������� ������� �����?\n\n"
            << "\t[1] ���������\n"
            << "\t[2] ������� ������ ����\n"
            << "\t[3] ����� � ����"<<endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
                /*������� � ���������� �������� �����*/
                case 49: flag = 1; break;
                /*������� ������ ���� ��� ����������*/
                case 50: flag = 2; break;
                case 51: return 2; break;
                default: cout << "��������� ����!"<<endl; continue;
            }
            break;
        }
        if (flag == 1){
            cout << "\n\t������� \"��\" ��� ������������� ���������� ������ � ���� \""<<filename<<"\":"<<endl;
            cout << "\t>>> ";
                fflush(stdin);
                gets(save_check);
                if (strcmp(save_check, "��") == 0){
                    /*���������� � �������� � ������ ������ ����*/
                    if ((f = fopen(filename, "w")) == NULL){
                            cout << "\t������ �������� ����� ��� ������ ������"<<endl;
                            exit(3);
                    }
                    WriteInFile(f, (*list), filename);
                    return 1;
                }
                else return 2;
        }
        if (flag == 2){
            system("cls");
            cout << "\t������� ������ ���� ��� ������:\n"<<endl;
            while(1){
                ShowFiles();
                cout << "\n\t������� �������� ����� �� ������(*.txt):"<<endl;
                while(1){
                    cout << "\t>>> ";
                    fflush(stdin);
                    gets(filename);
                    if (strlen(filename) > 4 && !strcmp(filename + strlen(filename) - 4, ".txt"))
                        break;
                    else{
                        cout << "\t������������ ��� �����, ��������� ����"<<endl;
                        continue;
                    }
                }
                if ((f = fopen(filename, "r")) == NULL){
                    system("cls");
                    cout << "\t������ �������� �����!"<<endl;
                    cout << "\n\t�� ����� �������� �����, �������� ��� � �����\n\t���������:\n"<<endl;
                    continue;
                }
                if (fgetc(f) == EOF){
                    system("cls");
                    cout << "\t������ �������� �����!" << endl;
                    cout << "\n\t��������� ���� ���� ��� ������ ����\n\t���������:\n" << endl;
                    continue;
                }
                break;
            }
            /*������� ����� ������ ��� ������ � ���� ������ �� �����*/
            DeleteLinkedList(list);
            *list = CreateLinkedlist();
            ReadFromFile(f, (*list));
            cout << "\n\t������ �� ����� \"" << filename << "\" ��������� � ���������. ������� ����� ������� ��� �������� � ����:\n\t>>> ";
            fflush(stdin);
            choice = getch();
            return 2;
        }
    }
   /*++++++++++++++++++++++++++++++++++++++
    /*������ �������� ������ �� �����
    ++++++++++++++++++++++++++++++++++++++*/
    void ReadFromFile (FILE *f, LinkedList *list)
    {
        Data *data;
        /*������ ������ �� �����*/
        while((data = new Data) && fscanf(f, "%s %s %d %d %f %s ", data->group, data->faculty, &data->students, &data->grants, &data->note, data->starosta) != EOF){
            Node *tmp = new Node;
            tmp->data = data; //��������� ���� ������� �� �����
            /*��������� ���� �� �������*/
            tmp->next = NULL;
            tmp->prev = list->tail;
            if (list->tail)
                list->tail->next = tmp;
            list->tail = tmp;
            if (list->head == NULL)
                list->head = tmp;
            list->size++; //������ ������ �������������
        }
        fclose(f);
    }
    /*++++++++++++++++++++++++++++++++++++++++
    /*�������� ������ �����
    /*���������� ��������� �� ��������� ����
    +++++++++++++++++++++++++++++++++++++++++*/
    FILE* CreateNewDatabase(FILE *f, char *filename)
    {
        cout << "\t������� ����� ����\n"<<endl;
        cout << "\t������� ��� ���������� ����� (������ - *.txt):"<<endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            gets(filename);
            //if(strlen(str) > 4 && !strcmp(str + strlen(str) - 4, ".csv"))
            if (strlen(filename) > 4 && !strcmp(filename + strlen(filename) - 4, ".txt"))
                break;
            else{
                cout << "\t������������ ��� �����, ��������� ����"<<endl;
                continue;
            }
        }
        if ((f = fopen(filename, "r")) != NULL){
            f = NULL; //���� ��������� ���� ��� ����������
            return f;
        }
        if ((f = fopen(filename, "w")) == NULL){
            cout << "\n\t������ �������� ����� ��� ������!"<<endl;
            exit(3);
        }
        return f;
    }
    /*++++++++++++++++++++++++++++++++++++++++++++
    /*���������� ������
    /*return 1 - ����� �� ���������, 2 - � ����
    ++++++++++++++++++++++++++++++++++++++++++++*/
    int Save(FILE *f, LinkedList *list, char *filename)
    {
        int choice;
        char save_check[MAX];
        int flag = 0;
        cout << "\t��������� � �����"<<endl;
        cout << "\n\t������ ��������� ��������� ��������� � �������� ���� \"" << filename <<"\" ����� �������?\n\t�������� ��� �������� ����� ����������!\n\t[1] ��\n\t[2] ����� � ����\n\t[3] �����" << endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
            case 49:
                cout << "[1]" << endl;
                cout << "\n\t������� ����� \"��\" ��� ������������� ��� ���-�� ������ ��� �������� � ����:"<<endl;
                cout << "\t>>> ";
                fflush(stdin);
                gets(save_check);
                if (strcmp(save_check, "��") == 0)
                    flag = 1; //���������� � �������� � ������ ������ ����
                else{
                    system("cls");
                    return 2;
                }
               break;
            case 50: return 2;
                break;
            case 51: return 1;
                break;//�����
            default:
                cout << "��������� ����!" << endl;
                continue;
            }
            break;
        }
        if (flag == 1){
            /*��������� �������� ���� ��� ������*/
            if ((f = fopen(filename, "w")) == NULL){
                cout << "\t������ �������� ����� ��� ������ ������"<<endl;
                exit(3);
            }
            system("cls");
            cout << "\t��������� � �����"<<endl;
            WriteInFile(f, list, filename);
            fclose(f);
            return 1; //����� �� ���������
        }
    }
    /*++++++++++++++++++++++++++++++++++++++
    /*���������������� ������ � ����
    ++++++++++++++++++++++++++++++++++++++*/
    void WriteInFile (FILE *f, LinkedList *list, char *filename)
    {
        Node *tmp = new Node;
        tmp = list->head;
        cout << "\n\t������ ������ � ���� \"" << filename << "\"..." << endl;
        /*������ ������ � ����*/
        while(tmp){
            fprintf(f, "%10s ", tmp->data->group);
            fprintf(f, "%12s ", tmp->data->faculty);
            fprintf(f, "%5d ", tmp->data->students);
            fprintf(f, "%5d ", tmp->data->grants);
            fprintf(f, "%5.2f ", tmp->data->note);
            fprintf(f, "%20s \n", tmp->data->starosta);
            tmp = tmp->next;
        }
        fclose(f);
        cout << "\t������ ������ � ���� \"" << filename << "\" ���������. ������� ����� ������� ��� �����������...\n\t>>> " << endl;
        getch();
    }
