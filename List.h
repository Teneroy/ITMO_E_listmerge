//
// Created by alexc on 11/11/2018.
//

#ifndef ITMO_E1_LIST_H
#define ITMO_E1_LIST_H

#include <iostream>
#include "string.h"
#include <iomanip>
#define SIZE 10
#define ENDL -1

struct elem
{
    char name[20];
    char adress[20];
    elem() {strcpy(name, ""); strcpy(adress, "");};
    elem(char * n, char * a) {strcpy(name, n);strcpy(adress, a);};
};

namespace arrlist
{

    typedef int t_position;

    struct node
    {
        elem data;
        int next;
        node() {next = -1;};
        node(elem d, int n):data(d),next(n) {};
    };

    class List
    {
    public:
        List();
        void insert(t_position p, elem x);
        t_position endL();
        t_position firstL();
        t_position locate(elem x);
        elem retrieve(t_position p);
        t_position deleteEl(t_position p);
        t_position next(t_position p);
        t_position prev(t_position p);
    //    void makenull();
        void printList();

    private:
        node _arr[SIZE];
        int _endl;
        void print_arr();
        bool pos_exist(t_position p);
        void add_with_change(elem x, int p);
        t_position search_same_pos(elem x);
        t_position delete_with_change(t_position p);
        void add_to_tail(elem x);
    };
}

namespace slinkedlist {


    struct node
    {
        elem x;
        node * next;
        node()
        {
            next = this;
        }
    };

    typedef node * t_position;

    class List {
    public:
        List();
        ~List();
        void insert(t_position p, elem x);
        void printList();
        t_position endL();
        t_position firstL();
        t_position next(t_position position);
        t_position prev(t_position position);
        t_position locate(elem x);
        elem retrieve(t_position position);
        t_position deleteEl(t_position position);

    private:
        node * _head;
        bool position_exist(t_position position, node * list);
        node * add_to_tail(node * list, elem x);
        node * add_to_pos(node * list, t_position pos, elem x);
        node * deleteList(node * list);
        t_position search_same_pos(node * list, elem x);
        elem search_same_el(node * list, t_position pos);
        node * delete_with_change(node * list, t_position pos);
        node * get_prev_el(node * list, t_position pos);
        node * get_last_el(node * list);
    };

}

namespace dlinkedlist
{

    struct node
    {
        elem x;
        node * next;
        node * prev;
        node()
        {
            next = this;
            prev = this;
        }
    };

    struct t_HT
    {
        node * head;
        node * tail;
    };

    typedef node * t_position;

    class List {
    public:
        List();
        ~List();
        void insert(t_position p, elem x);
        void printList();
        t_position endL();
        t_position firstL();
        t_position next(t_position position);
        t_position prev(t_position position);
        t_position locate(elem x);
        elem retrieve(t_position position);
        t_position deleteEl(t_position position);

    private:
        t_HT _list;
        bool position_exist(t_position position, node * list);
        node * add_to_tail(node * list, elem x);
        node * add_to_pos(node * list, t_position pos, elem x);
        t_HT deleteList(t_HT list);
        t_position search_same_pos(node * list, elem x);
        elem search_same_el(node * list, t_position pos);
        node * delete_with_change(node * list, t_position pos);
    };

}

namespace cursorlist
{

    struct node
    {
        elem data;
        int next;
        node() {next = -1;};
        node(elem d, int n):data(d),next(n) {};
    };

    typedef int t_position;

    class List
    {
    public:
        List();
        void insert(t_position p, elem x);
        t_position endL();
        t_position firstL();
        t_position locate(elem x);
        elem retrieve(t_position p);
        t_position deleteEl(t_position p);
        t_position next(t_position p);
        t_position prev(t_position p);
//    void makenull();
        void printList();

    private:
        static node _arr[SIZE];
        static t_position _space;
        static void InitArr();
        int _lpos;
        void print_arr();
        void add_after(elem x);
        bool pos_exist(t_position p);
        t_position get_prev_el(t_position p);
        t_position get_next_el(t_position p);
        void add_with_change(elem x, t_position p);
        int search_same_pos(elem x);
        elem search_same_el(t_position p);
        t_position delete_with_change(t_position p);
    };

}

#endif //ITMO_E1_LIST_H
