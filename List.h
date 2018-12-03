//
// Created by alexc on 11/11/2018.
//

#ifndef ITMO_E1_LIST_H
#define ITMO_E1_LIST_H

#include <iostream>
#include "string.h"
#include <iomanip>
#define SIZE 10 //Размер массива
#define ENDL -1 //Конец списка(используется для курсоров)


struct elem
{
    char name[20]; //Имя
    char adress[20]; //Адрес
    elem() {strcpy(name, ""); strcpy(adress, "");}; //Конструктор по умолчанию, инициализируем строки
    elem(char * n, char * a) {strcpy(name, n);strcpy(adress, a);}; //Конструктор с параметрами
};

namespace arrlist
{

    typedef int t_position; //тип позиции элемента

    struct node //Структура для фейкового элемента
    {
        elem data;//Данные
        int next;//Позиция следующего элемента
        node() {next = -1;}; //Конструктор по умолчанию
        node(elem d, int n):data(d),next(n) {}; //Конструктор с параметрами
    };

    class List
    {
    public:
        List();
        void insert(t_position p, elem x); //Вставка в список
        t_position endL(); //Вернуть последний элемент
        t_position firstL(); //Вернуть первый элемент
        t_position locate(elem x); //Вернуть позицию элемента x в списке
        elem retrieve(t_position p); //Вернуть элемент по позиции в списке
        t_position deleteEl(t_position p); //Удалить элемент списка по позиции
        t_position next(t_position p); //Вернуть следующий элемент, после позиции p
        t_position prev(t_position p); //Вернуть предыдущий элемент, до позиции p
    //    void makenull();
        void printList(); //Вывести список

    private:
        node _arr[SIZE]; //Массив структур node(для фейкового элемента)
        int _endl; //Последний элемент списка
        bool pos_exist(t_position p); //Существует ли позиция в списке
        void add_with_change(elem x, int p); //Добавить элемент x в позицию p со смещением
        t_position search_same_pos(elem x); //Поиск одинакового элемента в списке
        t_position delete_with_change(t_position p); //Удалить элемент в позиции p со смещением
        void add_to_tail(elem x); //Добавить в конец списка элемент x
    };
}

namespace slinkedlist {


    struct node //Узел списка
    {
        elem x; //Данные
        node * next; //Следующий элемент списка
        node() //Конструктор по умолчанию
        {
            next = this; //Следующий элемент, указывает на текущий узел, это сделано для фейкового элемента
        }
    };

    typedef node * t_position;

    class List {
    public:
        List();
        ~List();
        void insert(t_position p, elem x);//Вставка в список
        void printList();//Вывести список
        t_position endL();//Вернуть последний элемент
        t_position firstL();//Вернуть первый элемент
        t_position next(t_position position);//Вернуть следующий элемент, после позиции p
        t_position prev(t_position position);//Вернуть предыдущий элемент, до позиции p
        t_position locate(elem x);//Вернуть позицию элемента x в списке
        elem retrieve(t_position position);//Вернуть элемент по позиции в списке
        t_position deleteEl(t_position position);//Удалить элемент списка по позиции

    private:
        node * _head; //Голова списка
        bool position_exist(t_position position, node * list);//Существует ли позиция в списке
        node * add_to_tail(node * list, elem x);//Добавить элемент в хвост
        node * add_to_pos(node * list, t_position pos, elem x);//Добавить элемент x в позицию p
        node * deleteList(node * list);//Удалить список
        t_position search_same_pos(node * list, elem x);//Поиск одинакового элемента в списке
        elem search_same_el(node * list, t_position pos); //Поиск одинаковой позиции в списке
        node * delete_with_change(node * list, t_position pos);//Удалить элемент в позиции p со смещением
        node * get_prev_el(node * list, t_position pos); //Получить предыдущий элемент
        node * get_last_el(node * list); //Получить последний элемент
    };

}

namespace dlinkedlist
{

    struct node //Узел списка
    {
        elem x; //Данные
        node * next; //Следующий элемент
        node * prev; //Предыдущий элемент
        node() //Конструктор по умолчанию
        {
            next = this; //Следующий элемент указывает на текузий узел, сделано для фейкового элемента
            prev = this; //Предыдущий элемент указывает на текузий узел, сделано для фейкового элемента
        }
    };

    struct t_HT //Структура, содержашая голову и хвост списка, для удобной работы с двусвязным списком
    {
        node * head;
        node * tail;
    };

    typedef node * t_position; //Тип данных, указывающий на позицию

    class List {
    public:
        List();
        ~List();
        void insert(t_position p, elem x); //Вставка в список
        void printList();//Вывести список
        t_position endL();//Вернуть конец списка
        t_position firstL();//Вернуть первый элемент
        t_position next(t_position position);//Вернуть следующий элемент, после позиции p
        t_position prev(t_position position);//Вернуть предыдущий элемент, до позиции p
        t_position locate(elem x);//Вернуть позицию элемента x в списке
        elem retrieve(t_position position);//Вернуть элемент по позиции в списке
        t_position deleteEl(t_position position);//Удалить элемент списка по позиции

    private:
        t_HT _list; //Голова и хвост списка
        bool position_exist(t_position position, node * list);//Существует ли позиция в списке
        node * add_to_tail(node * list, elem x);//Добавить элемент в хвост
        node * add_to_pos(node * list, t_position pos, elem x);//Добавить элемент x в позицию p
        t_HT deleteList(t_HT list);//Удалить список
        t_position search_same_pos(node * list, elem x); //Поиск одинакового элемента в списке
        elem search_same_el(node * list, t_position pos); //Поиск одинаковой позиции в списке
        node * delete_with_change(node * list, t_position pos);//Удалить элемент в позиции p со смещением
    };

}

namespace cursorlist
{

    struct node //Элемент курсоров
    {
        elem data; //Данные
        int next; //Следующий элемент списка
        node() {next = -1;}; //Конструктор по умолчанию
        node(elem d, int n):data(d),next(n) {}; //Конструктор с параметрами
    };

    typedef int t_position; // Тип данных позиции для данного namespace'а

    class List
    {
    public:
        List();
        void insert(t_position p, elem x);//Вставка в список
        t_position endL();//Вернуть последний элемент
        t_position firstL();//Вернуть первый элемент
        t_position locate(elem x);//Вернуть позицию элемента x в списке
        elem retrieve(t_position p);//Вернуть элемент по позиции в списке
        t_position deleteEl(t_position p);//Удалить элемент списка по позиции
        t_position next(t_position p);//Вернуть следующий элемент, после позиции p
        t_position prev(t_position p);//Вернуть предыдущий элемент, до позиции p
//    void makenull();
        void printList();//Вывести список

    private:
        static node _arr[SIZE]; //Массив для списков, задан статически, чтобы данные сохранялись при добавлении других списков
        static t_position _space; //Позиция первого пустого элемента
        static void InitArr(); //Инициализация массива
        t_position _lpos; //Позиция первого элемента текущего списка
        void add_after(elem x); //Добавить элемент в конец списка
        bool pos_exist(t_position p); //Существует ли позиция
        t_position get_prev_el(t_position p); //Получить позицию предыдущего элемента, до p
        t_position get_next_el(t_position p); //Получить позицию следующего элемента, после p
        void add_with_change(elem x, t_position p); //Добавить элемент x в позицию p со смещением
        t_position search_same_pos(elem x); // Поиск одинакового элемента в списке
        elem search_same_el(t_position p); //Поиск одинаковой позиции в списке
        t_position delete_with_change(t_position p); //Удалить элемент в позиции p со смещением
    };

}

#endif //ITMO_E1_LIST_H
