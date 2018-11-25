//
// Created by alexc on 11/11/2018.
//

#include "List.h"

arrlist::node fake_a; //Фэйковый элемент для массива, возвращается при ошибке(fake.next, если нужно вернуть позицию, fake.data, если объект)

arrlist::List::List()
{
    for(int i = 0; i < SIZE; i++)
    {
        _arr[i] = node(); //Инициализируем массив, пустыми узлами(в data пустые строки, в next -1)
    }
    _endl = 0; //Конец списка, обозначает, что список пустой
}

//Вывести список
void arrlist::List::printList()
{
    std::cout << std::setw(25) << "<index>";
    std::cout << std::setw(25) << "<data>" << std::endl;
    for (int i = 0; i < _endl; ++i)
    {
        std::cout << std::setw(25) << i;
        std::cout << std::setw(25) << _arr[i].data.name << " " << _arr[i].data.adress << std::endl;
    }
}

//Вставка в список
void arrlist::List::insert(t_position p, elem x)
{
    if(p == _endl) // Если позиция равна концу списка, то добавляем в список, после последнего элемента
    {
        add_to_tail(x);
    } else if(pos_exist(p)) //Если позиция существует
    {
        add_with_change(x, p); //Добавляем в позицию, смещая остальные элементы списка, на соседнюю позицию
    } else
    {
        std::cout << "position does not exist" << std::endl; //Выводим предупреждение, что пользователь вставляет элемент в несуществующую позицию
    }
}

//Вернуть последний элемент
arrlist::t_position arrlist::List::endL()
{
    return _endl; //Возвращаем позицию конца списка
}

//Вернуть первый элемент
arrlist::t_position arrlist::List::firstL()
{
    return 0; //Возвращаем позицию первого элемента, он всегда на нулевой позиции
}

//Вернуть следующий элемент, после позиции p
arrlist::t_position arrlist::List::next(t_position p)
{
    if(pos_exist(p)) //Если позиция существует
    {
        return p + 1; //Вернуть следующую позицию, после текущей
    } else
    {
        return _endl; //Вернуть конец списка, если ее не существует
        //Это сделано, чтобы, если мы дойдем до конца списка, мы могли спокойно выйти из цикла в main
    }
}

//Вернуть предыдущий элемент, до позиции p
arrlist::t_position arrlist::List::prev(t_position p)
{
    if(pos_exist(p)) //Если позиция существует
    {
        return p - 1; //Возвращаем предыдущую позицию, до текущей
    } else
    {
        return fake_a.next; //Возвращаем объект ошибки
    }
}

//Вернуть элемент по позиции в списке
elem arrlist::List::retrieve(t_position p)
{
    if(pos_exist(p)) //Если позиция существует
    {
        return _arr[p].data; //Возвращаем elem по позиции
    } else
    {
        return fake_a.data; //Возвращаем данные с фэйкового элемента
    }
}

//Вернуть позицию элемента x в списке
arrlist::t_position arrlist::List::locate(elem x)
{
    int pos = search_same_pos(x); //Ищем нужную позицию по элементу
    if(pos != -1) //Если позиция существует
    {
        return pos; //Возвращаем позицию
    } else
    {
        return fake_a.next; //Возвращаем фэйковый элемент
    }
}

//Удалить элемент списка по позиции
arrlist::t_position arrlist::List::deleteEl(t_position p)
{
    if(pos_exist(p)) //Если позиция существует
    {
        return delete_with_change(p); //Удаляем элемент и возвращаем позицию, после текущего
    } else
    {
        return fake_a.next; //Возвращаем позицию фэйкового  элемента
    }
}

//Добавить в конец списка элемент x
void arrlist::List::add_to_tail(elem x)
{
    _arr[_endl].data = x; //Записываем данные в хвост
    _endl++; //Увеличиваем конец списка на 1
}

//Удалить элемент в позиции p со смещением
arrlist::t_position arrlist::List::delete_with_change(t_position p)
{
    for (int i = p; i < _endl; ++i)
    {
        _arr[i] = _arr[i + 1]; //Записываем в текущий элемент, следующий за им, таким образом смещая все элементы влево
        if(i == _endl) //Если мы дошли до последнего элемента списка
        {
            _arr[i].data = elem("", ""); //Заполняем последний элемент пустыми данными
        }
    }
    _endl--; //Уменьшаем конец списка на 1
    return p + 1; //Возвращаем позицию, после текущей
}

//Добавить элемент x в позицию p со смещением
void arrlist::List::add_with_change(elem x, int p)
{
    for(int i = _endl - 1; i >= p; --i) //Гоним с конца списка
    {
        _arr[i + 1] = _arr[i]; //Заполняем последующий элемент текущим, для смешения
    }
    _arr[p].data = x; //Вставляем эдемент в позицию
    _endl++; //Увеличиваем конец списка на 1
}

//Существует ли позиция в списке
bool arrlist::List::pos_exist(t_position p)
{
    if(p <= _endl && p >= 0) //Если p входит в промежуток [0;_endl], то такая позиция существует
    {
        return true;
    } else
    {
        return false;
    }
}

//Поиск одинакового элемента в списке
arrlist::t_position arrlist::List::search_same_pos(elem x)
{
    for(int i = 0; i < _endl; i++)
    {
        if(_arr[i].data.name == x.name && _arr[i].data.adress == x.adress) //Если данные обоих элементов равны
        {
            return i; //Возвращаем текущую позицию
        }
    }
    return fake_a.next; //Если во всем списке, ничего не нашли, возвращаем позицию фэйкового элемента
}


/*SINGLE LINKED LIST*/

slinkedlist::node fake;

slinkedlist::List::List()
{
    _head = nullptr;
}

slinkedlist::List::~List()
{
    _head = deleteList(_head);
}

void slinkedlist::List::insert(t_position p, elem x)
{
    if(_head == nullptr)
    {
        _head = new node;
        _head -> x = x;
        _head -> next = nullptr;
    } else if(p == nullptr)
    {
        _head = add_to_tail(_head, x);
    } else if(position_exist(p, _head))
    {
        _head = add_to_pos(_head, p, x);
    } else
    {
        std::cout << "position does not exist" << std::endl;
    }
}

slinkedlist::t_position slinkedlist::List::endL()
{
    return nullptr;
}

slinkedlist::t_position slinkedlist::List::firstL()
{
    return _head;
}

slinkedlist::t_position slinkedlist::List::next(t_position position)
{
    if(position == nullptr)
    {
        return nullptr;
    }
    if(!position_exist(position, _head))
    {
        return fake.next;
    }
    return position -> next;
}

slinkedlist::t_position slinkedlist::List::prev(t_position position)
{
    if(position == nullptr)
    {
        return get_last_el(_head);
    }
    if(!position_exist(position, _head))
    {
        return get_prev_el(_head, position);
    }
    return fake.next;
}

slinkedlist::t_position slinkedlist::List::locate(elem x)
{
    node * temp = search_same_pos(_head, x);
    if(temp == nullptr)
    {
        return fake.next;
    } else
    {
        return temp;
    }
}

elem slinkedlist::List::retrieve(t_position position)
{
    return search_same_el(_head, position);
}

slinkedlist::t_position slinkedlist::List::deleteEl(t_position position)
{
    if(position_exist(position, _head))
    {
        node * next = position -> next;
        _head = delete_with_change(_head, position);
        return next;
    } else
    {
        return fake.next;
    }
}

void slinkedlist::List::printList()
{
    node * temp = _head;
    std::cout << std::setw(25) << "<data>" << std::endl;
    while(temp != nullptr)
    {
        std::cout << std::setw(25) << temp -> x.name << " "  << temp -> x.adress << std::endl;
        temp = temp -> next;
    }
}

slinkedlist::node * slinkedlist::List::get_prev_el(node * list, t_position pos)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp -> next == pos)
        {
            return temp;
        }
        temp = temp -> next;
    }
    return nullptr;
}

slinkedlist::node * slinkedlist::List::get_last_el(node * list)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp -> next == nullptr)
        {
            return temp;
        }
    }
    return nullptr;
}

slinkedlist::node * slinkedlist::List::delete_with_change(node * list, t_position pos)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp -> next == pos)
        {
            temp -> next = pos -> next;
            delete pos;
            return list;
        }
        temp = temp -> next;
    }
    return nullptr;
}

elem slinkedlist::List::search_same_el(node * list, t_position pos)
{
    node * temp = list;
    while(temp != nullptr)
    {
        if(pos == temp)
        {
            return temp -> x;
        }
        temp = temp -> next;
    }
    return fake.x;
}

slinkedlist::t_position slinkedlist::List::search_same_pos(node * list, elem x)
{
    node * temp = list;
    while(temp != nullptr)
    {
        if(x.adress == temp -> x.adress && x.name == temp -> x.name)
        {
            return temp;
        }
        temp = temp -> next;
    }
    return nullptr;
}

slinkedlist::node * slinkedlist::List::deleteList(node * list)
{
    node * temp1;
    node * temp2 = list;
    while (temp2 != nullptr)
    {
        temp1 = temp2;
        temp2 = temp2 -> next;
        delete temp1;
    }
    list = nullptr;
    return list;
}

bool slinkedlist::List::position_exist(t_position position, node * list)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp == position)
        {
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

slinkedlist::node * slinkedlist::List::add_to_tail(node * list, elem x)
{
    node * temp1 = list;
    node * temp2 = temp1 -> next;
    while (temp2 != nullptr)
    {
        temp1 = temp1 -> next;
        temp2 = temp2 -> next;
    }
    temp1 -> next = new node;
    temp1 -> next -> x = x;
    temp1 -> next -> next = nullptr;
    return list;
}

slinkedlist::node * slinkedlist::List::add_to_pos(node * list, t_position pos, elem x)
{
    node * temp2 = new node();
    temp2 -> x = x;
    temp2 -> next = pos -> next;
    pos -> next = temp2;
    return list;
}

dlinkedlist::node fake_d;

dlinkedlist::List::List()
{
    _list.head = _list.tail = nullptr;
}

dlinkedlist::List::~List()
{
    _list = deleteList(_list);
}

void dlinkedlist::List::insert(t_position p, elem x)
{
    if(_list.head == nullptr)
    {
        node * temp = new node;
        temp -> next = nullptr;
        temp -> x = x;
        temp -> prev = nullptr;
        _list.head = _list.tail = temp;
    } else if(p == nullptr)
    {
        _list.tail = add_to_tail(_list.tail, x);
    } else if(position_exist(p, _list.head))
    {
        _list.head = add_to_pos(_list.head, p, x);
    } else
    {
        std::cout << "position does not exist" << std::endl;
    }
}

dlinkedlist::t_position dlinkedlist::List::endL()
{
    return nullptr;
}

dlinkedlist::t_position dlinkedlist::List::firstL()
{
    return _list.head;
}

dlinkedlist::t_position dlinkedlist::List::next(t_position position)
{
    if(position == nullptr)
    {
        return nullptr;
    }
    if(!position_exist(position, _list.head))
    {
        return fake_d.next;
    }
    return position -> next;
}

dlinkedlist::t_position dlinkedlist::List::prev(t_position position)
{
    if(position == nullptr)
    {
        return _list.tail;
    }
    if(!position_exist(position, _list.head))
    {
        return fake_d.next;
    }
    return position -> prev;
}

dlinkedlist::t_position dlinkedlist::List::locate(elem x)
{
    return search_same_pos(_list.head, x);
}

elem dlinkedlist::List::retrieve(t_position position)
{
    return search_same_el(_list.head, position);
}

dlinkedlist::t_position dlinkedlist::List::deleteEl(t_position position)
{
    if(position_exist(position, _list.head))
    {
        node * next = position -> next;
        _list.head = delete_with_change(_list.head, position);
        return next;
    } else
    {
        std::cout << "position does not exist" << std::endl;
        return fake_d.next;
    }
}

void dlinkedlist::List::printList()
{
    node * temp = _list.head;
    std::cout << std::setw(25) << "<data>" << std::endl;
    while(temp != nullptr)
    {
        std::cout << std::setw(25) << temp -> x.name << " " << temp -> x.adress << std::endl;
        temp = temp -> next;
    }
}

dlinkedlist::node * dlinkedlist::List::delete_with_change(node * list, t_position pos)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp -> next == pos)
        {
            temp -> next = pos -> next;
            if(pos -> next != nullptr)
                pos -> next -> prev = temp;
            delete pos;
            return list;
        }
        temp = temp -> next;
    }
    return nullptr;
}

elem dlinkedlist::List::search_same_el(node * list, t_position pos)
{
    node * temp = list;
    while(temp != nullptr)
    {
        if(pos == temp)
        {
            return temp -> x;
        }
        temp = temp -> next;
    }
    return fake_d.x;
}

dlinkedlist::t_position dlinkedlist::List::search_same_pos(node * list, elem x)
{
    node * temp = list;
    while(temp != nullptr)
    {
        if(x.adress == temp -> x.adress && x.name == temp -> x.name)
        {
            return temp;
        }
        temp = temp -> next;
    }
    return fake_d.next;
}

dlinkedlist::t_HT dlinkedlist::List::deleteList(t_HT list)
{
    node * temp1;
    node * temp2 = list.head;
    while (temp2 != nullptr)
    {
        temp1 = temp2;
        temp2 = temp2 -> next;
        delete temp1;
    }
    list.head = list.tail = nullptr;
    return list;
}

bool dlinkedlist::List::position_exist(t_position position, node * list)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp == position)
        {
            return true;
        }
        temp = temp -> next;
    }
    return false;
}

dlinkedlist::node * dlinkedlist::List::add_to_tail(node * list, elem x)
{
    node * temp_t = new node();
    temp_t -> x = x;
    temp_t -> next = nullptr;
    temp_t -> prev = list;
    list -> next = temp_t;
    return temp_t;
}

dlinkedlist::node * dlinkedlist::List::add_to_pos(node * list, t_position pos, elem x)
{
    node * temp2 = new node();
    temp2 -> x = x;
    temp2 -> next = pos -> next;
    temp2 -> prev = pos;
    pos -> next = temp2;
    return list;
}

cursorlist::node fake_c;

int cursorlist::List::_space = -1;
cursorlist::node cursorlist::List::_arr[SIZE];

void cursorlist::List::InitArr()
{
    for (int i = 0; i < SIZE; i++)
    {
        if(i != SIZE - 1) {
            List::_arr[i].next = i + 1;
        } else {
            List::_arr[i].next = -1;
        }
    }
    List::_space = 0;
}

cursorlist::List::List()
{
    _lpos = ENDL;
    if(List::_space == -1)
    {
        List::InitArr();
    }
}

void cursorlist::List::printList()
{
    print_arr();
}

void cursorlist::List::insert(t_position p, elem x)
{
    if(p == ENDL)
    {
        if(_lpos != ENDL)
        {
            int p_pos = get_prev_el(-1);
            List::_arr[p_pos].next = List::_space;
        }
        add_after(x);
    } else if(pos_exist(p))
    {
        add_with_change(x, p);
    } else
    {
        std::cout << "position " << p << "does not exist" << std::endl;
    }
}

cursorlist::t_position cursorlist::List::next(t_position p)
{
    return get_next_el(p);
}

cursorlist::t_position cursorlist::List::prev(t_position p)
{
    return get_prev_el(p);
}

cursorlist::t_position cursorlist::List::firstL()
{
    return _lpos;
}

cursorlist::t_position cursorlist::List::endL()
{
    return ENDL;
}

cursorlist::t_position cursorlist::List::locate(elem x)
{
    return search_same_pos(x);
}

elem cursorlist::List::retrieve(t_position p)
{
    return search_same_el(p);
}

cursorlist::t_position cursorlist::List::deleteEl(t_position p)
{
    if(pos_exist(p))
    {
        return delete_with_change(p);
    } else
    {
        return fake_c.next;
    }
}

cursorlist::t_position cursorlist::List::delete_with_change(t_position p)
{
    if(_lpos == p)
    {
        int next = List::_arr[p].next;
        _lpos = List::_arr[p].next;
        List::_arr[p].next = List::_space;
        strcpy(List::_arr[p].data.name, "");
        strcpy(List::_arr[p].data.adress, "");
        List::_space = p;
        return next;
    } else
    {
        int prev = get_prev_el(p);
        int next = List::_arr[p].next;
        List::_arr[prev].next = List::_arr[p].next;
        List::_arr[p].next = List::_space;
        List::_space = p;
        strcpy(List::_arr[p].data.name, "");
        strcpy(List::_arr[p].data.adress, "");
        return next;
    }
}

elem cursorlist::List::search_same_el(t_position p)
{
    node iter = List::_arr[_lpos];
    int i = _lpos;
    while(i != -1)
    {
        if(i == p)
        {
            return iter.data;
        }
        i = iter.next;
        iter = List::_arr[iter.next];
    }
    return fake_c.data;
}

cursorlist::t_position cursorlist::List::search_same_pos(elem x)
{
    node iter = List::_arr[_lpos];
    int i = _lpos;
    while(i != -1)
    {
        if(x.adress == iter.data.adress && x.name == iter.data.name)
        {
            return i;
        }
        i = iter.next;
        iter = List::_arr[iter.next];
    }
    return fake_c.next;
}

void cursorlist::List::add_with_change(elem x, t_position p)
{
    if(List::_space != -1)
    {
        node temp(x,List::_space);
        int next_space = List::_arr[List::_space].next;
        List::_arr[List::_space] = List::_arr[p];
        List::_arr[p] = temp;
        List::_space = next_space;
    } else
    {
        std::cout << "no space elements" << std::endl;
    }
}

cursorlist::t_position cursorlist::List::get_prev_el(t_position p)
{
    node iter = List::_arr[_lpos];
    int i = _lpos;
    while(i != -1)
    {
        if(iter.next == p)
        {
            return i;
        }
        i = iter.next;
        iter = List::_arr[iter.next];
    }
    return fake_c.next;
}

cursorlist::t_position cursorlist::List::get_next_el(t_position p)
{
    node iter = List::_arr[_lpos];
    int i = _lpos;
    while(i != -1)
    {
        if(i == p)
        {
            return iter.next;
        }
        i = iter.next;
        iter = List::_arr[iter.next];
    }
    return fake_c.next;
}

void cursorlist::List::add_after(elem x)
{
    int next_space = List::_arr[List::_space].next;
    node temp(x, -1);
    List::_arr[List::_space] = temp;
    if(_lpos == ENDL)
    {
        _lpos = List::_space;
    }
    List::_space = next_space;
}

bool cursorlist::List::pos_exist(t_position p)
{
    node iter = List::_arr[_lpos];
    int i = _lpos;
    while(i != -1)
    {
        if(i == p)
        {
            return true;
        }
        i = iter.next;
        iter = List::_arr[iter.next];
    }
    return false;
}

void cursorlist::List::print_arr()
{
    std::cout << std::setw(25) << "<index>";
    std::cout << std::setw(25) << "<data>";
    std::cout << std::setw(25) << "<next>" << std::endl;
    for (int i = 0; i < SIZE; ++i)
    {
        std::cout << std::setw(25) << i << " " << std::setw(25) << List::_arr[i].data.adress << " " << std::setw(25) << List::_arr[i].next << std::endl;
    }
}

