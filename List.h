//
// Created by alexc on 11/11/2018.
//
#pragma once
#ifndef ITMO_E1_LIST_H
#define ITMO_E1_LIST_H

#include <iostream>
#include "string.h"
#include <iomanip>
//#define SIZE 10 //Размер массива
//#define ENDL -1 //Конец списка(используется для курсоров)


#include "base-types.h"

namespace arrlist //Реализация списков на массиве
{
    enum{SIZE = 10, ERR = -1};

    typedef int t_position; //тип позиции элемента

    struct node //Структура для фейкового элемента
    {
        elem  data;//Данные
        int next;//Позиция следующего элемента
        node() {next = -1;}; //Конструктор по умолчанию
    };

    class List
    {
    public:
        List();
        void insert(t_position p, const elem &x); //Вставка в список
        t_position endL() const; //Вернуть последний элемент
        t_position firstL() const; //Вернуть первый элемент
        t_position locate(const elem &x) const; //Вернуть позицию элемента x в списке
        elem retrieve(t_position p) const; //Вернуть элемент по позиции в списке
        t_position deleteEl(t_position p); //Удалить элемент списка по позиции
        t_position next(t_position p) const; //Вернуть следующий элемент, после позиции p
        t_position prev(t_position p) const; //Вернуть предыдущий элемент, до позиции p
        void makenull(); //Заполнить массив пустыми значениями
        void printList() const; //Вывести список
        static void InitArr();
    private:
        elem _arr[SIZE]; //Массив структур node(для фейкового элемента)
        int _endl; //Последний элемент списка
        bool pos_exist(t_position p) const; //Существует ли позиция в списке
        t_position search_same_pos(const elem &x) const; //Поиск по значению
    };
}

namespace slinkedlist { //Реализация списков на односвязном списке

    struct node //Узел списка
    {
        elem  x; //Данные
        node * next; //Следующий элемент списка
        node() //Конструктор по умолчанию
        {
            next = this; //Следующий элемент, указывает на текущий узел, это сделано для фейкового элемента
        };
        node(elem d, node * n):x(d),next(n) {};
    };

    typedef node * t_position;

    class List {
    public:
        List();
        ~List();
        void insert(t_position p, const elem &x);//Вставка в список
        void printList() const;//Вывести список
        t_position endL() const;//Вернуть последний элемент
        t_position firstL() const;//Вернуть первый элемент
        t_position next(t_position position) const;//Вернуть следующий элемент, после позиции p
        t_position prev(t_position position) const;//Вернуть предыдущий элемент, до позиции p
        t_position locate(const elem &x) const;//Вернуть позицию элемента x в списке
        elem& retrieve(t_position position) const;//Вернуть элемент по позиции в списке
        t_position deleteEl(t_position position);//Удалить элемент списка по позиции
        void makenull(); //Удаление списка
        static void InitArr();
    private:
        node * _head; //Голова списка
        node * add_to_pos(node * list, t_position pos, const elem &x);//Добавить элемент x в позицию p
        node * deleteList(node * list);//Удалить список
        t_position search_same_pos(node * list, const elem &x) const;//Поиск элемента в списке
        node * get_prev_el(node * list, t_position pos) const; //Получить предыдущий элемент
    };

}

namespace dlinkedlist //Реализация списков на двусвязном списке
{

    struct node //Узел списка
    {
        elem  x; //Данные
        node * next; //Следующий элемент
        node * prev; //Предыдущий элемент
        node() //Конструктор по умолчанию
        {
            next = this; //Следующий элемент указывает на текузий узел, сделано для фейкового элемента
            prev = this; //Предыдущий элемент указывает на текузий узел, сделано для фейкового элемента
        };
        node(elem d, node * n, node * p):x(d),next(n),prev(p) {};
    };

    typedef node * t_position; //Тип данных, указывающий на позицию

    class List {
    public:
        List();
        ~List();
        void insert(t_position p, const elem &x); //Вставка в список
        void printList() const;//Вывести список
        t_position endL() const;//Вернуть конец списка
        t_position firstL() const;//Вернуть первый элемент
        t_position next(t_position position) const;//Вернуть следующий элемент, после позиции p
        t_position prev(t_position position) const;//Вернуть предыдущий элемент, до позиции p
        t_position locate(const elem &x) const;//Вернуть позицию элемента x в списке
        elem& retrieve(t_position position) const;//Вернуть элемент по позиции в списке
        t_position deleteEl(t_position position);//Удалить элемент списка по позиции
        void makenull(); //Удаление списка
        static void InitArr();
    private:
        node * _head;//Голова списка
        node * _tail;//Хвост списка
        bool position_exist(t_position position, node * list) const;//Существует ли позиция в списке
        node * add_to_tail(node * list, const elem &x);//Добавить элемент в хвост
        node * add_to_pos(node * list, t_position pos, const elem &x);//Добавить элемент x в позицию p
        node * deleteList(node * head, node * tail);//Удалить список
        t_position search_same_pos(node * list, const elem &x) const; //Поиск элемента в списке
    };

}

namespace cursorlist //Реализация списков на курсорах
{

    enum {ENDL = -1, SIZE = 10, ERR = -1};

    struct node //Элемент курсоров
    {
        elem  data; //Данные
        int next; //Следующий элемент списка
        node() {next = -1;}; //Конструктор по умолчанию
        node(elem  d, int n):data(d),next(n) {}; //Конструктор с параметрами
    };

    typedef int t_position; // Тип данных позиции для данного namespace'а

    class List
    {
    public:
        List();
        void insert(t_position p, const elem &x);//Вставка в список
        t_position endL() const;//Вернуть последний элемент
        t_position firstL() const;//Вернуть первый элемент
        t_position locate(const elem &x) const;//Вернуть позицию элемента x в списке
        elem& retrieve(t_position p) const;//Вернуть элемент по позиции в списке
        t_position deleteEl(t_position p);//Удалить элемент списка по позиции
        t_position next(t_position p) const;//Вернуть следующий элемент, после позиции p
        t_position prev(t_position p) const;//Вернуть предыдущий элемент, до позиции p
        void makenull(); //Удаление списка
        void printList() const;//Вывести список
        static void InitArr(); //Инициализация массива
    private:
        static node _arr[SIZE]; //Массив для списков, задан статически, чтобы данные сохранялись при добавлении других списков
        static t_position _space; //Позиция первого пустого элемента
        t_position _lpos; //Позиция первого элемента текущего списка
        void add_after(const elem &x); //Добавить элемент в конец списка
        t_position get_prev_el(t_position p) const; //Получить позицию предыдущего элемента, до p
        void add_with_change(const elem &x, t_position p); //Добавить элемент x в позицию p
        t_position search_same_pos(const elem &x) const; // Поиск элемента в списке
    };

}

#endif //ITMO_E1_LIST_H
