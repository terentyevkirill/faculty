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

    /*СТРУКТУРЫ ДАННЫХ*/
    /*Структура "Данные о группе"*/
    struct Data {
        char faculty[MAX]; //факультет
        char group[MAX]; //название группы
        int students; //количество студентов
        int grants; //количество получающих стипенцию
        float note; //средний балл};
        char starosta[MAX]; //фамилия старосты
    };
    /*Структура "Узел"*/
    struct Node {
        Data *data;
        Node *next;
        Node *prev;
    };
    /*Структура "Список"*/
    struct LinkedList {
        int size;
        Node *head;
        Node *tail;
    };

    /*ОСНОВНЫЕ ПРОГРАММНЫЕ ФУНКЦИИ*/
    /*Создание списка*/
    LinkedList *CreateLinkedlist();
    /*Удаление списка*/
    void DeleteLinkedList (LinkedList **list);
    /*Провека на пустоту списка*/
    int ListIsEmpty(LinkedList *list);
    /*Ввод данных пользователем*/
    Data* DataInput(LinkedList *list);
    /*Проверка на отсутствие в списке вводимой группы*/
    int OriginalData (LinkedList *list, char group[]);
    /*удаление элемента по названию группы*/
    int DelElement(LinkedList *list);
    /*Добавление элемента*/
    int AddElement(LinkedList *list);
    /*Вставка элемента в конец списка*/
    void PushBack(LinkedList *list, Data *data);
    /*Вставка элемента в начало списка*/
    void PushFront (LinkedList *list, Data *data);
    /*Вставка элемента перед заданным узлом*/
    void PushBefore (LinkedList *list, Node *tmp, Data *data);
    /*Сортировка списка*/
    int InsertionSort (LinkedList **list);
    /*Поиск элемента по заданному параметру*/
    int FindElement(LinkedList *list);
    /*Вывод всего списка на экран*/
    void PrintLinkedList(LinkedList *list);
    /*Вывод введенных данных на экран*/
    void PrintData (Data *data);
    /*Вывод списка факультетов без повторений*/
    void FacultyList(LinkedList *list);
    /*подсчет количества студентов/стипендий на заданном факультете*/
    int NumberOfStudentsOrGrantsOnFaculty (LinkedList *list, int parameter);
    /*Вывод групп и фамилий старост, со средним баллом выше заданного*/
    int NoteHigher (LinkedList *list);
    /*Заголовок программы*/
    void Header();
    /*Меню*/
    void Menu();
    /*Выбор пункта меню*/
    int MenuChoice();
    /*Выход из программы*/
    int Exit();

    /*ФУНКЦИИ РАБОТЫ С ФАЙЛАМИ*/
    /*Вывод списка файлов из текущей папки на экран*/
    int ShowFiles();
    /*Начальный выбор файла с данными*/
    FILE *ChooseInputFile(FILE *f, char *filename);
    /*Открытие другого файла в процессе работы программы*/
    int OpenAnotherInputFile(FILE *f, char *filename, LinkedList **list);
    /*Непосредственно чтение данных из файла*/
    void ReadFromFile (FILE *f, LinkedList *list);
    /*Создание нового файла с данными*/
    FILE* CreateNewDatabase(FILE *f, char *filename);
    /*Сохранение*/
    int Save(FILE *f, LinkedList *list, char *filename);
    /*Непосредственно запись данных в файл*/
    void WriteInFile (FILE *f, LinkedList *list, char *filename);

    int main()
    {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        char filename[MAX]; //имя файла
        FILE *f;
        int choice; //навигация в меню
        Header();
        system("cls");
        cout << "\tДля работы с программой необходимо подключить файл с данными:"<<endl;
        f = ChooseInputFile(f, filename); //открываем файл для чтения
        LinkedList *list = CreateLinkedlist(); //создаем список
        if (fgetc(f) != EOF) //считываем данные из файла в список
            ReadFromFile(f, list);
        system("cls");
        /*работа в меню*/
        Menu();
        while(1){
            int flag = 0; //флаг для возврата в меню или повторного запуска функции
            int flag_exit = 0; //флаг подтверждения выхода из программы
            /*выбор пункта меню*/
            switch(MenuChoice()){
            case 1: //добавление элемента
                while(1){
                    flag = AddElement(list);
                    if (flag != 1)
                        break;
                }
                break;
            case 2: //удаление элемента
                while(1){
                    flag = DelElement(list);
                    if (flag != 1)
                        break;
                }
                break;
            case 3: //поиск элемента
                while(1){
                    flag = FindElement(list);
                    if (flag != 1)
                        break;
                }
                break;
            case 4: //вывод всего списка на экран
                system("cls");
                cout << "\tВывод всего списка"<<endl;
                PrintLinkedList(list);
                cout << "\tДля возврата в меню нажмите любую клавишу\n\t>>> ";
                choice = getch();
                flag = 2;
                break;
            case 5: //подсчет количества студентов
                while(1){
                    flag = NumberOfStudentsOrGrantsOnFaculty(list, 1);
                    if (flag != 1)
                        break;
                }
                break;
            case 6: //вывод групп с оценкой выше заданной
                while(1){
                    flag = NoteHigher(list);
                    if (flag != 1)
                        break;
                } break;
            case 7: //подсчет количества стипендий
                while(1){
                    flag = NumberOfStudentsOrGrantsOnFaculty(list, 2);
                    if (flag != 1)
                        break;
                }
                break;
            case 8: //сортировка списка по среднему баллу
                flag = InsertionSort(&list);
                break;
            case 9: //открыть другой файл
                while(1){
                    system("cls");
                    cout << "\tОкрыть файл с данными"<<endl;
                    flag = OpenAnotherInputFile(f, filename, &list);
                    if (flag != 1)
                        break;
                }
                break;
            case 10: //сохранение
                system("cls");
                if (ListIsEmpty(list))
                    cout << "\n\tСписок пуст, нет элементов для сохранения. Вы можете сохранить пустой список"<<endl;
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
                cout << "\tДо свидания!" << endl;
                cout << "\n\n\n\n\n\n\n\n\tКирилл Терентьев НАИ176 (2018)" << endl;
                break;
            }
            if (flag_exit == 2){
                cout << "\tОтмена выхода, возврат в меню."<<endl;
                system("cls");
                Menu();
                continue;
            }
        }
        fclose(f); //закрытие открытый файл
        DeleteLinkedList(&list); //удаление списка
        return 0; //завершение программы
    }
    /*++++++++++++++++++++++++
    /*СОЗДАНИЕ СПИСКА
    /*++++++++++++++++++++++++*/
    LinkedList *CreateLinkedlist(){
        LinkedList *tmp = new LinkedList;
        tmp->size = 0;
        tmp->head = tmp->tail = NULL;
        return tmp;
    }
    /*+++++++++++++++++++++++
    /*УДАЛЕНИЕ СПИСКА
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
    /*ПРОВЕРКА НА ПУСТОЙ СПИСОК
    /*return 0 - пустой, 1 - не пустой
    /*+++++++++++++++++++++++++++++++++*/
    int ListIsEmpty(LinkedList *list)
    {
        if (list->head == NULL)
            return 1;
        else return 0;
    }
    /*+++++++++++++++++++++++++++++++++++++++++++
    /*ВВОД ДАННЫХ ПОЛЬЗОВАТЕЛЕМ
    /*Возвращет структуру с введенными данными
    /*++++++++++++++++++++++++++++++++++++++++++*/
    Data* DataInput(LinkedList *list)
    {
        int i = 0; //счетчик
        int flag = 0; //флаг нахождения вводимой группы в списке
        int spaceflag; //флаг нахождения пробелов в введенных строках
        char group[MAX]; //группа
        char faculty[MAX]; //факультет
        char starosta [MAX]; //фамилия староста
        float nf; //средний балл
        int n; //проверка целочисленных значений (число студентов и стипендий)
        Data* data = new Data;
        cout << "\n\tВведите данные о группе:"<<endl;
        /*Ввод группы и проверка корректности*/
        cout << "\tВведите название группы (формат ввода - АИ172, НАИ176):"<<endl;
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
                cout << "\tОшибка ввода, повторите:" << endl;
                continue;
            }
            else {
                flag = OriginalData(list, group);
                if (flag == 1) {
                    cout << "\tГруппа "<<group<<" уже есть в списке, повторите ввод:"<<endl;
                    continue;
                }
                else break;
            }
        }
        strcpy(data->group, group);
        /*Ввод факультета и проверка корректности*/
        cout << "\tВведите название факультета (Формат ввода - ИИБРТ, ИКС):" << endl;
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
                cout << "\tОшибка ввода, повторите:" << endl;
                continue;
            } else break;
        }
        strcpy(data->faculty, faculty);
        /*Ввод числа студентов и проверка корректности*/
        cout << "\tВведите количество студентов (целое число):" << endl;
        while (1) {
            cout << "\t>>> ";
            n = 0;
            cin >> n;
            fflush(stdin);
            if (!cin || n < 0) {
                cout << "\tОшибка ввода, повторите:" << endl;
                cin.clear();
                continue;
                //while (cin.get() != '\n');
            }
            else break;
        } data->students = n;
        /*Ввод числа стипендий и проверка корректности*/
        cout << "\tВведите количество студентов, получающих стипендию (целое число):" << endl;
        while (1) {
            cout << "\t>>> ";
            fflush(stdin);
            n = 0;
            cin >> n;
            if (!cin || n < 0 || n > data->students) {
                if (n > data->students)
                    cout << "\tОшибка, введенное число больше количества студентов в группе, повторите ввод: " << endl;
                else
                    cout << "\tОшибка ввода, повторите:" << endl;
                cin.clear();
                continue;
            }
            else break;
        } data->grants = n;
        /*Ввод оценки и проверка корректности*/
        cout << "\tВведите средний балл группы (вещ. число от 0 до 100, формат ввода - х.хх) :" << endl;
        while (1) {
            cout << "\t>>> ";
            fflush(stdin);
            nf = 0.00; //для проверки вещ. значений
            cin >> nf;
            if (!cin || nf < 0 || nf > 100) {
                cout << "\tОшибка ввода, повторите:" << endl;
                cin.clear();
                while (cin.get() != '\n');
            }
            else break;
        } data->note = nf;
        /*Ввод фамилии староста и проверка корректности*/
        cout << "\tВведите фамилию старосты (без пробелов):" << endl;
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
                cout << "\tОшибка ввода, повторите:" << endl;
                continue;
            }
            else break;
        }
        strcpy(data->starosta, starosta);
        fflush(stdin);
        /*Вывод введенных данных на экран*/
        cout << "\tВвод данных о группе " << data->group << " завершен."<<endl;
        PrintData(data);
        return data;
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++++
    /*ПРОВЕРКА НА ОТСУТСВИЕ В СПИСКЕ ВВОДИМОЙ ГРУППЫ
    /*Возвращает 1, если такая группа уже есть в списке
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
    /*УДАЛЕНИЕ ГРУППЫ ИЗ СПИСКА
    /*return 1 - удалить еще, 2 - назад в меню
    /*++++++++++++++++++++++++++++++++++++++++++*/
    int DelElement(LinkedList *list)
    {
        system("cls");
        cout << "\tУдалить элемент\n"<<endl;
        int choice; //навигация
        int flag = 0; //флаг выбора
        char group[MAX]; //название удаляемой группы
        if (ListIsEmpty(list)){
            cout << "\tСписок пуст, нет элементов для удаления.\n"<<endl;
            cout << "\tНажмите любую клавишу для возврата в меню\n\t>>> ";
            getch();
            return 2;
        }
        Node *del = NULL;
        Node *tmp = NULL;
        tmp = list->head;
        cout << "\tВведите полное название группы для её удаления:"<<endl;
        cout<<"\t>>> ";
        fflush(stdin);
        gets(group);
        /*ищем совпадение по введенной группе в списке*/
        while(tmp){
            if (strcmp(tmp->data->group, group) == 0){
                del = tmp;
                break;
            }
            tmp = tmp->next;
        }
        /*если не найдена такая группа*/
        if(!del){
            cout << "\n\tПо Вашему запросу "<<group<<" не ничего не найдено. Хотите повторить ввод?"<<endl;
            cout << "\t[1] Да\n\t[2] Возврат в меню"<<endl;
            while(1){
                cout << "\t>>> ";
                fflush(stdin);
                switch(choice = getch()) {
                    case 49: cout <<"[1]"<<endl; return 1; break;
                    case 50: cout << "[2]"<<endl; return 2; break;
                    default: cout << "Повторите ввод"<<endl; continue;
                } break;
            }
        }
        /*Если найдена, удаляем*/
        if(del){
            cout << "\tПо Вашему запросу "<<group<<" найдено:"<<endl;
            PrintData(del->data); //выводим найденную группу на экран
            cout << "\n\tВы действительно хотите удалить этот элемент из списка? Вернуть удаленные данные невозможно!\n\t[1] Да\n\t[2] Возврат в меню"<<endl;
            while(1){
                cout << "\t>>> ";
                switch(choice = getch()) {
                    case 49: cout <<"[1]"<<endl; flag = 1; break;
                    case 50: cout << "[2]"<<endl; return 2; break;
                    default: cout << "Повторите ввод"<<endl; continue;
                } break;
            }
            if (flag == 1){ /*производим удаление из списка*/
                /*Если элемент не первый, делаем так, чтобы предыдущий перед ним
                элемент указывал на следующий после него*/
                if (del->prev)
                    del->prev->next = del->next;
                /*если элемент первый, то делаем следующий за ним головным*/
                if (!del->prev)
                    list->head = del->next;
                /*Если элемент не последний, делаем так, чтобы следующий после него
                элемент указывал на предыдущий перед ним */
                if (del->next)
                    del->next->prev = del->prev;
                /*Если элемнет последний, то делаем предыдущий перед ним хвостовым*/
                if (!del->next)
                    list->tail = del->prev;
                delete del;
                list->size--;
                cout << "\tЭлемент " << group << " успешно удален из списка."<<endl;
                if (!ListIsEmpty(list)){
                    cout << "\tХотите удалить еще один элемент?\n\t[1] Да\n\t[2] Возврат в меню"<<endl;
                    while(1){
                        cout<<"\t>>> ";
                        switch(choice = getch()) {
                            case 49: cout <<"[1]"<<endl; return 1; break; //продолжить удаление
                            case 50: cout << "[2]"<<endl; return 2; break; //возврат в меню
                            default: cout << "Повторите ввод"<<endl; continue;
                        } break;
                    }
                }
                else{
                    cout << "\n\tСписок пуст\n\tДля возврата в меню нажмите любую клавишу\n\t>>> ";
                    fflush(stdin);
                    choice = getch();
                    return 2;
                }
            }
        }
    }
    /*+++++++++++++++++++++++++++++++++++++++
    /*ДОБАВЛЕНИЕ ЭЛЕМЕНТА В СПИСОК
    /*return 1 - добавить еще, 2 - в меню
    /*+++++++++++++++++++++++++++++++++++++++*/
    int AddElement(LinkedList *list)
    {
        Data *data = new Data;
        int choice;
        int flag;
        system("cls");
        cout << "\t Добавить элемент"<<endl;
        while(1){
            data = DataInput(list);
            cout << "\tСохранить введенные данные?"<<endl<<"\t[1] Да"<<endl<<"\t[2] Нет"<<endl<<"\t>>> ";
            switch(choice = getch()){
                case 49: cout << "[1]"<<endl; flag = 1; break; //сохранить
                case 50: cout << "[2]"<<endl; flag = 0; break; //не сохранять
                default: cout << "Повторите ввод"<<endl; cout << "\t>>> "; continue;
            } break;
        }
        if (flag){
            PushBack(list, data); //записываем в конец списка
            cout<<"\tДанные сохранены"<<endl;
        }
        cout<<"\n\tХотите добавить другой элемент?"<<endl<<"\t[1] Да"<<endl<<"\t[2] Назад в меню"<<endl;
        while(1){
            cout << "\t>>> ";
            switch(choice = getch()) {
                case 49: cout <<"[1]"<<endl; return 1; break;
                case 50: cout <<"[2]"<<endl; return 2; break;
                default: cout << "Повторите ввод"<<endl; continue;
            } break;
        }
    }
    /*++++++++++++++++++++++++++++++++++++
    /*ДОБАВЛЕНИЕ ЭЛЕМЕНТА В КОНЕЦ СПИСКА
    /*++++++++++++++++++++++++++++++++++++*/
    void PushBack(LinkedList *list, Data *data) {
        Node *tmp = new Node;
        if (tmp == NULL){
            cout << "\tНе удалось добавить элемент в конец списка." << endl;
            exit(2);
        }
        tmp->data = data; //заполняем узел данными
        /*связываем хвост списка с новым элементом*/
        tmp->next = NULL;
        tmp->prev = list->tail;
        if (list->tail)
            list->tail->next = tmp;
        list->tail = tmp;
        /*если список пуст, то элемент становится и началом*/
        if (list->head == NULL)
            list->head = tmp;
        list->size++; //размер списка увеличивается
    }
    /*+++++++++++++++++++++++++++++++++++++
    /*ДОБАВЛЕНИЕ ЭЛЕМЕНТА В НАЧАЛО СПИСКА
    /*+++++++++++++++++++++++++++++++++++++*/
    void PushFront (LinkedList *list, Data *data){
        Node *tmp = new Node;
        if (tmp == NULL) {
            cout << "\tНе удалось добавить элемент в начало списка." << endl;
            exit(2);
        }
        tmp->data = data; //заполняем узел данными
        /*связываем голову списка с новым элементом*/
        tmp->next = list->head;
        tmp->prev = NULL;
        if (list->head)
            list->head->prev = tmp;
        list->head = tmp;
        /*если список пуст, то новый элемент становится и хвостом*/
        if (list->tail == NULL)
            list->tail = tmp;
        list->size++; //размер списка увеличивается
    }
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /*ВСТАВКА ЭЛЕМЕНТА ПЕРЕД ЗАДАННЫМ TMP
    /*Используется при сортировке (s_list - отсортированный список)
    /*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    void PushBefore (LinkedList *s_list, Node *tmp, Data *data)
    {
        if (tmp == NULL){
            cout << "\tОшибка выделения памяти." << endl;
            exit(2);
        }
        /*Если элемент tmp первый в списке, вставляем узел в начало*/
        if (!tmp->prev){
            PushFront(s_list, data);
            return;
        }
        /*узел ins будет вставляться перед tmp*/
        Node *ins = new Node;
        ins->data = data;
        ins->prev = tmp->prev;
        ins->prev->next = ins;
        ins->next = tmp;
        tmp->prev = ins;
        s_list->size++;
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++++++
    /*Сортировка вставками, сортируется исходный список
    /*return 2 - возврат в меню
    /*+++++++++++++++++++++++++++++++++++++++++++++++++*/
    int InsertionSort (LinkedList **list)
    {
        int flag = 0; //способ сортировка
        int choice; //навигация
        system("cls");
        cout << "\tСортировка по полю \"Средний балл\"\n" << endl;
        if (ListIsEmpty(*list)){
            cout << "\tСписок пуст" << endl;
            cout << "\n\tНажмите любую клавишу для возврата в меню...\n\t>>> ";
            fflush(stdin);
            getch();
            return 2;
        }
        cout << "\t[1] По возрастанию\n\t[2] По убыванию" << endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
                case 49: flag = 1; break; //по возрастанию
                case 50: flag = 2; break; //по убыванию
                default: cout << "Повторите ввод!" << endl; continue;
                }
            break;
        }
        LinkedList *s_list = CreateLinkedlist(); //отсортированный список
        Node *sorted = NULL; //узел отсортированного списка
        Node *unsorted = NULL; //узел исходного списка
        /*сортируем список по полю средний балл*/
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
        cout << "\tСортировка по полю \"Средний балл\"\n" << endl;
        if (flag == 1)
            cout << "\tОтсортированный по возрастанию список:" << endl;
        if (flag == 2)
            cout << "\tОтсортированный по убыванию список:" << endl;
        /*выводим отсортированный список на экран*/
        PrintLinkedList(s_list);
        cout << "\tХотите сохранить отсортированный список?\n\t[1] Да\n\t[2] Назад в меню" << endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
                case 49: //сохраняем отсортированный список
                    delete(*list);
                    *list = s_list;
                    cout << "\n\tОтсортированный список сохранен.\n"
                        << "\tНажмите любую клавишу, чтобы вернуться в меню...\n\t>>> " << endl;
                    getch();
                    return 2;
                    break;
                case 50: return 2; break;
                default: cout << "Повторите ввод!" << endl; continue;
            }
            break;
        }
    }
    /*++++++++++++++++++++++++++++++++++++++
    /*ПОИСК ПО ФАКУЛЬТЕТУ ИЛИ ПО ГРУППЕ
    /*return 1 - искать снова, 2 - в меню
    ++++++++++++++++++++++++++++++++++++++*/
    int FindElement(LinkedList *list)
    {
        char choice; //выбор варианта
        int flag = 0; //флаг выбора
        int found = 0; //флаг нахождения
        system("cls");
        cout << "\tПоиск элемента по введенному параметру (факультет, группа):"<< endl;
        if (ListIsEmpty(list)){
            cout << "\n\tСписок пуст\n"<<endl;
            cout << "\tНажмите любую клавишу для возврата в меню\n\t>>> ";
            choice = getch();
            return 2;
        }
        cout << "\n\t[1] Поиск элемента по факультету:\n\t[2] Поиск элемента по названию группы\n\t[3] Назад в меню"<<endl;
        while(1){
            cout << "\t>>> ";
            switch(choice = getch()){
            case 49: cout << "[1]" << endl; flag = 1; break; //поиск по факультету
            case 50: cout << "[2]" << endl; flag = 2; break; //поиск по группе
            case 51: cout << "[3]" << endl; return 2; break;
            default: cout << "Повторите ввод!" << endl; continue;
            }
            break;
        }
        char search[MAX];
        system("cls");
        if (flag == 1){
            cout << "\tПоиск элемента по факультету:\n\n";
            FacultyList(list);
            cout << "\tВведите название факультета:";
        }
        if (flag == 2){
            cout << "\tПоиск элемента по группам:\n\n";
            cout << "\tВведите название группы:";
        }
        /*ввод пользователем факультета или группы*/
        while (1) {
            cout << "\n\t>>> ";
            fflush(stdin);
            gets(search);
            if (strlen(search) == 0 || strlen(search) > 10) {
                cout << "\tОшибка ввода, повторите:" << endl;
                continue;
            } else break;
        }
        /*создается список нахождения*/
        LinkedList *foundlist = CreateLinkedlist();
        Node *tmp = new Node;
        tmp = list->head;
        while(tmp){
            if (flag == 1) //если ищем по факультетам
                if(strncmp(search, tmp->data->faculty, strlen(search)) == 0)
                    found = 1;
            if (flag == 2) //если ищем по группам
                if(strncmp(search, tmp->data->group, strlen(search)) == 0)
                    found = 1;
            if (found)
                PushBack(foundlist, tmp->data); //записываем найденный элемент в список
            tmp = tmp->next;
            found = 0;
        }
        if(!ListIsEmpty(foundlist)){
            cout << "\n\tПо вашему запросу \"" << search << "\" найдено " << foundlist->size <<" групп(ы):"<<endl;
            PrintLinkedList(foundlist);
        }
        else
            cout << "\n\tПо вашему запросу \"" << search << "\" ничего не найдено.\n" << endl;
        DeleteLinkedList(&foundlist);
        cout << "\tХотите повторить поиск?\n\t[1] Да\n\t[2] Назад в меню"<<endl;
        while(1){
            cout << "\t>>> ";
            switch(choice = getch()){
                case 49: cout << "[1]" << endl; return 1; break;
                case 50: cout << "[2]" << endl; return 2; break;
                default: cout << "Повторите ввод!" << endl; continue;
            }
            break;
        }
    }
    /*++++++++++++++++++++++++++++++++++++++++++++
    /*ВЫВОД ВСЕГО СПИСКА НА ЭКРАН В ВИДЕ ТАБЛИЦЫ
    /*+++++++++++++++++++++++++++++++++++++++++++*/
    void PrintLinkedList(LinkedList *list)
    {
        if (ListIsEmpty(list))
            cout << "\n\tСписок пуст"<<endl;
        else{
            Node *tmp = list->head;
            cout << "\n\t|-------------------------------------------------------------------------------------------------|"<<endl;
            cout << "\t|Группа  |Факультет  |Число студентов  |Число стипендий  |Средний балл  |Фамилия старосты         |" << endl;
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
    /*ВЫВОД НА ЭКРАН ВВЕДЕННЫХ ДАННЫХ
    /*ИЛИ ДАННЫХ ТОЛЬКО ИЗ ОДНОГО КОНКРЕТНОГО УЗЛА
    /*+++++++++++++++++++++++++++++++++++++++++++*/
    void PrintData (Data *data)
    {
        cout << "\t|-------------------------------------------------------------------------------------------------|"<<endl;
        cout << "\t|Группа  |Факультет  |Число студентов  |Число стипендий  |Средний балл  |Фамилия старосты         |" << endl;
        cout << "\t|-------------------------------------------------------------------------------------------------|"<<endl;
        cout << left << setfill(' ') << "\t|" << setw(8) << data->group << "|" << setw(11) << data->faculty << "|" << setw(17) <<
        data->students << "|" << setw(17) << data->grants << "|" << setw(14)
         << setprecision(2) << setiosflags(ios::fixed | ios::showpoint) << data->note <<"|"<< setw(25) << data->starosta <<"|" << endl;
        cout << "\t|-------------------------------------------------------------------------------------------------|"<<endl;
    }
    /*+++++++++++++++++++++++++++++++++++++++++++++
    /*ВЫВОД ФАКУЛЬТЕТОВ НА ЭКРАН БЕЗ ПОВТОРЕНИЙ
    +++++++++++++++++++++++++++++++++++++++++++++++*/
    void FacultyList(LinkedList *list)
    {
        int i = 0, count = 1, j; //счетчики
        int found; //флаг нахождения повторений
        char faculty_list[list->size][MAX]; //массив строк с названиями факультетов
        cout << "\tСписок факультетов:"<<endl;
        Node *tmp = new Node;
        tmp = list->head;
        /*копируем все факультеты из списка в массив*/
        while(tmp){
            strcpy(faculty_list[i], tmp->data->faculty);
            i++;
            tmp = tmp->next;
        }
        /*делаем выборку из массива и выводим ее на экран*/
        for (i = 0; i < list->size; i++){
            found = 0;
            for (j = i; j >= 0; j--){
                if(strcmp(faculty_list[i], faculty_list[j]) == 0)
                    found++;
            }
            if (found <= 1)
                cout << "\t" << count++ << ")" << faculty_list[i] << endl;
        }
        /*очищаем ДП*/
        delete(tmp);
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /*ПОДСЧЕТ ОБЩЕГО КОЛИЧЕСТВА СТУДЕНТОВ (parameter - 1) И СТИПЕНДИЙ (2)
    /*НА ЗАДАННОМ ФАКУЛЬТЕТЕ
    /*parameter - определяет искомую величину(1 или 2)
    /*
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    int NumberOfStudentsOrGrantsOnFaculty (LinkedList *list, int parameter)
    {
        int choice; //навигация
        int grants = 0; //число стипендий
        int students = 0; //число студентов
        char faculty[MAX]; //вводимое название факультета
        system("cls");
        if (parameter == 1)
            cout << "\tПодсчет общего количества студентов на заданном факультете\n" << endl;
        if (parameter == 2)
            cout << "\tПодсчет количества студентов, получающих стипендию на заданном факультете\n" << endl;
        if (ListIsEmpty(list)){
            cout << "\tСписок пуст.\n"<<endl;
            cout << "\tНажмите любую клавишу для возврата в меню\n\t>>> ";
            getch();
            return 2; //кнопка - возврат в меню
        }
        FacultyList(list); //вывод названий факультетов
        cout << "\n\tВведите название факультета из списка:" << endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            gets(faculty);
            if (strlen(faculty) == 0 || strlen(faculty) > 10){
                cout << "\tОшибка ввода, повторите:"<<endl;
                continue;
            } else break;
        }
        /*считаем количество студентов и стипендий на заданном факультете*/
        Node *tmp = new Node;
        tmp = list->head;
        while(tmp){
            if(strcmp(faculty, tmp->data->faculty) == 0){
                grants = grants + tmp->data->grants;
                students = students + tmp->data->students;
            }
            tmp = tmp->next;
        }
        delete(tmp); //очищаем ДП
        if (!grants) //если ничего не найдено
            cout << "\tПо вашему запросу \"" << faculty << "\" ничего не найдено." << endl;
        else
            if (parameter == 1) //вывод числа студентов
                cout << "\n\tНа факультете \"" << faculty << "\" учится " << students << " студентов.\n";
            if (parameter == 2) //вывод числа стипендий
                cout << "\n\tНа факультете \"" << faculty << "\" учится " << grants << " студентов, получающих стипендию.\n";
        cout << "\n\tХотите повторить поиск?\n\t[1] Да\n\t[2] Назад в меню"<<endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
                case 49: return 1; break;
                case 50: return 2; break;
                default: cout << "Повторите ввод!" << endl; continue;
            }
            break;
        }
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /*ВЫВОД ГРУПП И ИХ СТАРОСТ, ОЦЕНКИ КОТОРЫХ ВЫШЕ ЗАДАННОЙ
    /*return 1 - повторить поиск, 2 - возврат в меню
    /*++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    int NoteHigher (LinkedList *list)
    {
        int found = 0; //флаг нахождения подходящих под выборку групп
        int choice; //навигация
        float average_note = 0.00; //средний балл по всем группам
        float note = 0.00; // балл, вводимый пользователем
        system("cls");
        cout << "\tПоиск групп и фамилий старост, которые имеют средний балл больше заданного\n" << endl;
        if (ListIsEmpty(list)){
            cout << "\tСписок пуст" << endl;
            cout << "\n\tНажмите любую клавишу для возврата в меню\n\t>>> ";
            fflush(stdin);
            getch();
            return 2;
        }
        Node *tmp = new Node;
        tmp = list->head;
        /*подстчет среднего балла по всем группам*/
        while(tmp){
            average_note += tmp->data->note;
            tmp = tmp->next;
        }
        average_note = average_note/list->size;
        cout << "\tСредний балл по всем группам: " << setprecision(2) << setiosflags(ios::fixed | ios::showpoint) << average_note << endl;
        /*ввод балла пользователем*/
        cout << "\n\tВведите балл для поиска групп, имеющих средний балл выше Вами заданного\n"
            << "\t(формат ввода - вещественное число от 0 до 100)" << endl;
        while (1) {
            cout << "\t>>> ";
            fflush(stdin);
            cin >> note;
            if (!cin || note < 0 || note > 100) {
                cout << "\tОшибка ввода, повторите:" << endl;
                cin.clear();
                while (cin.get() != '\n');
            }
            else break;
        }
        /*вывод групп и фамилий их старост, имеющих средний балл выше заданного*/
        tmp = list->head;
        while(tmp) {
            if (tmp->data->note > note){
                found++;
                /*делаем оформление в виде таблицы*/
                if (found == 1){
                    cout << "\n\tГруппы и фамилии их старост, имеющие средний балл выше "
                        << setiosflags(ios::fixed | ios::showpoint) << note << ":" << endl;
                    cout << "\t---------------------------------------------------\n"
                        << "\t|Группа  |Средний балл  |Фамилия старосты         |\n"
                        <<  "\t---------------------------------------------------" << endl;
                }
                /*вывод данных о группах в виде таблицы*/
                cout << left << "\t|" << setw(8) << tmp->data->group << "|" << setw(14) << setprecision(2)
                 << setiosflags(ios::fixed | ios::showpoint)<< tmp->data->note << "|"
                 << setw(25) << tmp->data->starosta << "|" << endl;
            }
            tmp = tmp->next;
        }
        if (found)
            cout << "\t---------------------------------------------------" << endl;
        else
            cout << "\n\tГрупп со средним баллом выше " << setprecision(2)
                 << setiosflags(ios::fixed | ios::showpoint) << note << " не найдено." << endl;
        cout << "\n\tХотите повторить поиск?\n\t[1] Да\n\t[2] Назад в меню" << endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
                case 49: return 1; break;
                case 50: return 2; break;
                default: cout << "Повторите ввод!" << endl; continue;
            }
        }
    }
    /*+++++++++++++++++++++
    /*ЗАГОЛОВОК ПРОГРАММЫ
    /*++++++++++++++++++++*/
    void Header()
    {
        int skip;

        cout << "\n\n\t" << setfill('*') << setw(66) << "*\n"
            << "\t*\t\t\t КУРСОВАЯ РАБОТА \t\t\t*\n"
            << "\t*\t По предмету \"Алгоритмизация и программирование\" \t*\n"
            << "\t*\t\tТема: \"Динамические структуры данных\"  \t\t*\n"
            << "\t*\t\t      Студента группы НАИ-176    \t\t*\n"
            << "\t*\t\t\tТерентьева Кирилла\t\t\t*\n"
            << "\t" << setfill('*') << setw(66) << "*\n"
            << "\t*      Динамическая структура, которая содержит информацию:     *\n"
            << "\t* факультет, группа, количество студентов, количество студентов *\n"
            << "\t*   в группе, которые получают стипендию, ср.балл успеваемости  *\n"
            << "\t* \t \t    по группе, фамилия старосты.      \t \t*\n"
            << "\t*\t     Структура данных - двухсвязный список   \t\t*\n"
            << "\t" << setfill('*') << setw(66) << "*\n"
            << setfill(' ') << "\n\n\tДля начала работы нажмите любую клавишу\n\t>>> ";
        skip = _getch();
        system("cls");
    }
    /*++++++++++++++++++++++
    /*МЕНЮ ПРОГРАММЫ
    /*++++++++++++++++++++*/
    void Menu()
    {
        cout << "\tВыберите действие из списка и нажмите соответствующую ему клавишу:\n" << endl;
        cout << "\t[1] Добавить элемент\n"
            << "\t[2] Удалить элемент\n"
            << "\t[3] Поиск элемента по введенному параметру (факультет, группа)\n"
            << "\t[4] Вывод всего списка\n"
            << "\t[5] Подсчет общего количества студентов на заданном факультете\n"
            << "\t[6] Вывод групп и фамилий старост, которые имеют средний балл больше заданного\n"
            << "\t[7] Подсчет количества студентов, которые получают стипендию на заданном факультете\n"
            << "\t[8] Сортировка по полю \"Cредний балл\"\n"
            << "\t[9] Открыть файл с данными\n"
            << "\t[Esc] Сохранить и выйти" << endl;
    }
    /*++++++++++++++++++++++++++++++++++++++
    /*ВЫБОР ПУНКТА МЕНЮ
    /*ВОЗВРАЩАЕТ НОМЕР ВЫБРАННОГО ПУНКТА
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
                default: cout << "Повторите ввод!" << endl; continue;
            }
            break;
        }
    }
    /*+++++++++++++++++++++++++++++++++
    /*ВЫХОД ИЗ ПРОГРАММЫ
    /*return 1 - Выход, 2 - В меню
    /*++++++++++++++++++++++++++++++++*/
    int Exit()
    {
        int exit_check;
        system("cls");
        cout << "\tВыход" << endl;
        cout << "\n\tВы уверены, что хотите выйти из программы?\n\t[1] Да"<<endl<<"\t[2] Нет, вернуться в меню"<<endl;
        while(1){
            cout << "\t>>> ";
            switch(exit_check = getch()){
            case 49: cout << "[1] Да" << endl; return 1; break;
            case 50: cout << "[2] Возврат в меню"<<endl; return 2; break;
            default: cout << "Повторите ввод"<<endl; continue;
            }
            break;
        }
    }

    /*+++++++++++++++++++++++++++++++++++++++++++
    /*ВЫВОД ИМЁН ФАЙЛОВ В ТЕКУЩЕЙ ПАПКЕ НА ЭКРАН
    /*return 1 - создание нового файла
    /*return 2 - ввод названия существующего
    ++++++++++++++++++++++++++++++++++++++++++++*/
    int ShowFiles()
    {
        cout << "\tФайлы в текущей папке:\n" << endl;
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
            return 1; //создать новый файл
        }
        else return 2; //ввести название существующего
    }
    /*+++++++++++++++++++++++++++++++++++++++++
    /*ВЫБОР ФАЙЛА ДЛЯ НАЧАЛЬНОГО ЧТЕНИЯ
    /*НЕОБХОДИМО ДЛЯ РАБОТЫ С ПРОГРАММОЙ!
    /*Возвращает указатель на выбранный файл
    /*+++++++++++++++++++++++++++++++++++++++++*/
    FILE *ChooseInputFile(FILE *f, char *filename)
    {
        int flag; //флаг выбора
        char choice; //навигация
        while(1){
            flag = 0;
            cout << "\n\t[1] Открыть существующий файл\n\t[2] Создать новый файл"<<endl;
            while(1){
                cout << "\t>>> ";
                switch(choice = getch()){
                    case 49:  system("cls"); flag = ShowFiles(); break; //открыть существующий файл
                    case 50:  system("cls"); f = CreateNewDatabase(f, filename); break; //создать новый файл
                    default: cout << "Повторите ввод"<<endl; continue;
                }
                break;
            }
            /*Если пользователь захотел открыть существующий файл,
            /*но таковых не оказалось, создается новый файл*/
            if (flag == 1){
                system("cls");
                cout << "\tФайлов в текущей папке не найдено\n"<<endl;
                f = CreateNewDatabase(f, filename);
            }
            /*если найденны файлы*/
            if (flag == 2){
                cout << "\n\tВведите название файла из списка(*.txt):"<<endl;
                while(1){
                    cout << "\t>>> ";
                    fflush(stdin);
                    gets(filename);
                    if (strlen(filename) > 4 && !strcmp(filename + strlen(filename) - 4, ".txt"))
                        break;
                    else{
                        cout << "\tНекорректное имя файла, повторите ввод"<<endl;
                        continue;
                    }
                }
                if ((f = fopen(filename, "r")) == NULL){
                    system("cls");
                    cout << "\tОшибка открытия файла!"<<endl;
                    cout << "\n\tВозможно, Вы ввели название файла, которого нет в папке\n\tПовторите:\n"<<endl;
                    continue;
                }
                if (fgetc(f) == EOF){
                    system("cls");
                    cout << "\tОшибка открытия файла!" << endl;
                    cout << "\n\tВозможно, выбранный вами файл для чтения пуст\n\tПовторите:\n" << endl;
                    continue;
                }
            }
            if (f == NULL){
                cout << "\n\tВведенный Вами новый файл уже существует.\n\tПовторите:\n"<<endl;
                continue;
            }
            break;
        }
        return f;
    }
    /*++++++++++++++++++++++++++++++++++++++++++++++
    /*ОТКРЫТИЕ ДРУГОГО ФАЙЛА ДЛЯ ЧТЕНИЯ
    /*return 1 - запуск функции заново, 2 - в меню
    +++++++++++++++++++++++++++++++++++++++++++++++*/
    int OpenAnotherInputFile(FILE *f, char *filename, LinkedList **list)
    {
        char save_check[MAX]; //строка для подтвеждения записи в файл
        int choice; //навигация
        int flag = 0; //флаг выбора
        cout << "\n\tХотите сохранить текущие изменения в файле \""<<filename<<"\" перед открытием другого файла?\n\n"
            << "\t[1] Сохранить\n"
            << "\t[2] Открыть другой файл\n"
            << "\t[3] Назад в меню"<<endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
                /*Перейти к сохранению текущего файла*/
                case 49: flag = 1; break;
                /*открыть другой файл без сохранения*/
                case 50: flag = 2; break;
                case 51: return 2; break;
                default: cout << "Повторите ввод!"<<endl; continue;
            }
            break;
        }
        if (flag == 1){
            cout << "\n\tВведите \"ДА\" для подтверждения сохранения данных в файл \""<<filename<<"\":"<<endl;
            cout << "\t>>> ";
                fflush(stdin);
                gets(save_check);
                if (strcmp(save_check, "ДА") == 0){
                    /*Сохранение в открытый в начале работы файл*/
                    if ((f = fopen(filename, "w")) == NULL){
                            cout << "\tОшибка открытия файла для записи данных"<<endl;
                            exit(3);
                    }
                    WriteInFile(f, (*list), filename);
                    return 1;
                }
                else return 2;
        }
        if (flag == 2){
            system("cls");
            cout << "\tОткрыть другой файл для чтения:\n"<<endl;
            while(1){
                ShowFiles();
                cout << "\n\tВведите название файла из списка(*.txt):"<<endl;
                while(1){
                    cout << "\t>>> ";
                    fflush(stdin);
                    gets(filename);
                    if (strlen(filename) > 4 && !strcmp(filename + strlen(filename) - 4, ".txt"))
                        break;
                    else{
                        cout << "\tНекорректное имя файла, повторите ввод"<<endl;
                        continue;
                    }
                }
                if ((f = fopen(filename, "r")) == NULL){
                    system("cls");
                    cout << "\tОшибка открытия файла!"<<endl;
                    cout << "\n\tВы ввели название файла, которого нет в папке\n\tПовторите:\n"<<endl;
                    continue;
                }
                if (fgetc(f) == EOF){
                    system("cls");
                    cout << "\tОшибка открытия файла!" << endl;
                    cout << "\n\tВыбранный вами файл для чтения пуст\n\tПовторите:\n" << endl;
                    continue;
                }
                break;
            }
            /*создаем новый список для записи в него данных из файла*/
            DeleteLinkedList(list);
            *list = CreateLinkedlist();
            ReadFromFile(f, (*list));
            cout << "\n\tДанные из файла \"" << filename << "\" загружены в программу. Нажмите любую клавишу для перехода в меню:\n\t>>> ";
            fflush(stdin);
            choice = getch();
            return 2;
        }
    }
   /*++++++++++++++++++++++++++++++++++++++
    /*ЧТЕНИЕ ИСХОДНЫХ ДАННЫХ ИЗ ФАЙЛА
    ++++++++++++++++++++++++++++++++++++++*/
    void ReadFromFile (FILE *f, LinkedList *list)
    {
        Data *data;
        /*читаем строку из файла*/
        while((data = new Data) && fscanf(f, "%s %s %d %d %f %s ", data->group, data->faculty, &data->students, &data->grants, &data->note, data->starosta) != EOF){
            Node *tmp = new Node;
            tmp->data = data; //заполняем узел данными из файла
            /*связываем узел со списком*/
            tmp->next = NULL;
            tmp->prev = list->tail;
            if (list->tail)
                list->tail->next = tmp;
            list->tail = tmp;
            if (list->head == NULL)
                list->head = tmp;
            list->size++; //размер списка увеличивается
        }
        fclose(f);
    }
    /*++++++++++++++++++++++++++++++++++++++++
    /*СОЗДАНИЕ НОВОГО ФАЙЛА
    /*Возвращает указатель на созданный файл
    +++++++++++++++++++++++++++++++++++++++++*/
    FILE* CreateNewDatabase(FILE *f, char *filename)
    {
        cout << "\tСоздать новый файл\n"<<endl;
        cout << "\tВведите имя текстового файла (Формат - *.txt):"<<endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            gets(filename);
            //if(strlen(str) > 4 && !strcmp(str + strlen(str) - 4, ".csv"))
            if (strlen(filename) > 4 && !strcmp(filename + strlen(filename) - 4, ".txt"))
                break;
            else{
                cout << "\tНекорректное имя файла, повторите ввод"<<endl;
                continue;
            }
        }
        if ((f = fopen(filename, "r")) != NULL){
            f = NULL; //Если введенный файл уже существует
            return f;
        }
        if ((f = fopen(filename, "w")) == NULL){
            cout << "\n\tОшибка открытия файла для записи!"<<endl;
            exit(3);
        }
        return f;
    }
    /*++++++++++++++++++++++++++++++++++++++++++++
    /*СОХРАНЕНИЕ ДАННЫХ
    /*return 1 - выход из программы, 2 - в меню
    ++++++++++++++++++++++++++++++++++++++++++++*/
    int Save(FILE *f, LinkedList *list, char *filename)
    {
        int choice;
        char save_check[MAX];
        int flag = 0;
        cout << "\tСохранить и выйти"<<endl;
        cout << "\n\tХотите сохранить внесенные изменения в исходный файл \"" << filename <<"\" перед выходом?\n\tОТМЕНИТЬ ЭТО ДЕЙСТВИЕ БУДЕТ НЕВОЗМОЖНО!\n\t[1] Да\n\t[2] Назад в меню\n\t[3] Выход" << endl;
        while(1){
            cout << "\t>>> ";
            fflush(stdin);
            switch(choice = getch()){
            case 49:
                cout << "[1]" << endl;
                cout << "\n\tВведите слово \"ДА\" для подтверждения или что-то другое для возврата в меню:"<<endl;
                cout << "\t>>> ";
                fflush(stdin);
                gets(save_check);
                if (strcmp(save_check, "ДА") == 0)
                    flag = 1; //Сохранение в открытый в начале работы файл
                else{
                    system("cls");
                    return 2;
                }
               break;
            case 50: return 2;
                break;
            case 51: return 1;
                break;//Выход
            default:
                cout << "Повторите ввод!" << endl;
                continue;
            }
            break;
        }
        if (flag == 1){
            /*открываем исходный файл для записи*/
            if ((f = fopen(filename, "w")) == NULL){
                cout << "\tОшибка открытия файла для записи данных"<<endl;
                exit(3);
            }
            system("cls");
            cout << "\tСохранить и выйти"<<endl;
            WriteInFile(f, list, filename);
            fclose(f);
            return 1; //выход из программы
        }
    }
    /*++++++++++++++++++++++++++++++++++++++
    /*НЕПОСРЕДСТВЕННАЯ ЗАПИСЬ В ФАЙЛ
    ++++++++++++++++++++++++++++++++++++++*/
    void WriteInFile (FILE *f, LinkedList *list, char *filename)
    {
        Node *tmp = new Node;
        tmp = list->head;
        cout << "\n\tЗапись списка в файл \"" << filename << "\"..." << endl;
        /*запись списка в файл*/
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
        cout << "\tЗапись списка в файл \"" << filename << "\" завершена. Нажмите любую клавишу для продолжения...\n\t>>> " << endl;
        getch();
    }
