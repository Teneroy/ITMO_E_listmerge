//
// Created by alexc on 11/11/2018.
//

#include "List.h"

arrlist::node fake_a; //Фэйковый элемент для массива, возвращается при ошибке(fake.next, если нужно вернуть позицию, fake.data, если объект)

arrlist::List::List()
{
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
    {//Добавить в конец списка элемент x
        _arr[_endl].data = x; //Записываем данные в хвост
        _endl++; //Увеличиваем конец списка на 1
    } else if(pos_exist(p)) //Если позиция существует
    {//Добавляем в позицию, смещая остальные элементы списка, на соседнюю позицию
        for(int i = _endl - 1; i >= p; --i) //Гоним с конца списка
        {
            _arr[i + 1] = _arr[i]; //Заполняем последующий элемент текущим, для смешения
        }
        _arr[p].data = x; //Вставляем эдемент в позицию
        _endl++; //Увеличиваем конец списка на 1
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
    } else //Если позиции не существует вообще
    {
        return fake_a.next; //Возвращаем позицию фейкового элемента
    }
}

//Вернуть предыдущий элемент, до позиции p
arrlist::t_position arrlist::List::prev(t_position p)
{
    if(pos_exist(p) && p != 0) //Если позиция существует
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

//Заполнить массив пустыми значениями
void arrlist::List::makenull()
{
    _endl = 0;
}

//Удалить элемент списка по позиции
arrlist::t_position arrlist::List::deleteEl(t_position p)
{
    if(pos_exist(p)) //Если позиция существует
    {//Удаляем элемент и возвращаем позицию, после текущего
        for (int i = p; i < _endl; ++i)
        {
            _arr[i] = _arr[i + 1]; //Записываем в текущий элемент, следующий за им, таким образом смещая все элементы влево
        }
        _endl--; //Уменьшаем конец списка на 1
        return p; //Возвращаем позицию текущего элемента, тк все уже сместили
    } else
    {
        return fake_a.next; //Возвращаем позицию фэйкового  элемента
    }
}

//Существует ли позиция в списке
bool arrlist::List::pos_exist(t_position p)
{
    return p <= _endl && p >= 0; //Если p входит в промежуток [0;_endl], то такая позиция существует
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
    return -1; //Если во всем списке, ничего не нашли, возвращаем -1
}


/*SINGLE LINKED LIST*/

slinkedlist::node fake; //Фэйковый элемент для односвязного списка, возвращается при ошибке(fake.next, если нужно вернуть позицию, fake.data, если объект)

slinkedlist::List::List()
{
    _head = nullptr;
}

slinkedlist::List::~List()
{
    _head = deleteList(_head); //Удаляем список
}

//Вставка в список
void slinkedlist::List::insert(t_position p, elem x)
{
    if(_head == nullptr) //Если список пуст
    {
        _head = new node; //Добавляем новую голову
        _head -> x = x;
        _head -> next = nullptr;
    } else if(p == endL()) //Если позиция равна концу списка
    {
        _head = add_to_tail(_head, x);  //Добавляем элемент в хвост
    } else if(position_exist(p, _head)) //Если позиция существует
    {
        _head = add_to_pos(_head, p, x); //Добавляем элемент в текущую позицию
    } else
    {
        std::cout << "position does not exist" << std::endl; //Выводим сообщение об ошибке
    }
}

//Вернуть последний элемент
slinkedlist::t_position slinkedlist::List::endL()
{
    return nullptr; //Возвращаем нулевой указатель
}

//Вернуть первый элемент
slinkedlist::t_position slinkedlist::List::firstL()
{
    return _head; //Возвращаем указатель на голову
}

//Вернуть следующий элемент, после позиции p
slinkedlist::t_position slinkedlist::List::next(t_position position)
{
    if(position == nullptr) //Если позиция равна концу строки
    {
        return nullptr; //Возвращаем конец строки
    }
    if(!position_exist(position, _head)) //Если позиции не существует
    {
        return fake.next; //Возвращаем адрес фейкового элемента
    }
    return position -> next; //Если позиция удовлетворяет всем условиям, возвращаем указатель на следующий элемент списка
}

//Вернуть предыдущий элемент, до позиции p
slinkedlist::t_position slinkedlist::List::prev(t_position position)
{
    if(position == nullptr)//Если позиция равна концу строки
    {
        return get_last_el(_head); //Вернуть последний элемент
    }
    if(!position_exist(position, _head)) //Если позиции не существует
    {
        return fake.next; //Возвращаем адрес фейкового элемента
    }
    return get_prev_el(_head, position); //Если позиция удовлетворяет всем условиям, возвращаем указатель на предыдущий элемент списка
}

//Вернуть позицию элемента x в списке
slinkedlist::t_position slinkedlist::List::locate(elem x)
{
    node * temp = search_same_pos(_head, x); //Ищем позицию одинаковых элементов
    if(temp == nullptr) //Если ничего не нашли
    {
        return fake.next; //Возвращаем адрес фейкового элемента
    } else //Если нашли позицию
    {
        return temp; //Возвращаем позицию
    }
}

//Вернуть элемент по позиции в списке
elem slinkedlist::List::retrieve(t_position position)
{
   t_position temp = get_prev_el(_head, position);
   if(temp != nullptr || position == _head)
   {
       return position -> x;//Вернуть элемент по позиции
   } else
   {
       return fake.x;
   }
}

//Удалить элемент списка по позиции
slinkedlist::t_position slinkedlist::List::deleteEl(t_position position)
{
    if(position_exist(position, _head)) //Если позиция существует
    {
        node * next = position -> next; // Записываем позицию, после последнего
        _head = delete_with_change(_head, position); //Удаляем со смещением
        return next; //Возвращаем позицию, после текущего элемента
    } else
    {
        return fake.next; //Возвращаем адрес фэйкового элемента
    }
}

//Вывести список
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

//Удаление списка
void slinkedlist::List::makenull()
{
    _head = deleteList(_head);
}

//Получить предыдущий элемент
slinkedlist::node * slinkedlist::List::get_prev_el(node * list, t_position pos)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp -> next == pos) //Если указатель на следующий элемент равен позиции
        {
            return temp; //Вернуть текущую позицию
        }
        temp = temp -> next;
    }
    return nullptr; //Если позиции не нашли вернуть нулевой указатель
}

//Получить последний элемент
slinkedlist::node * slinkedlist::List::get_last_el(node * list)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp -> next == nullptr) //Если следуюзий элемент равен концу строки
        {
            return temp; //Возвращаем текущий элемент
        }
    }
    return nullptr; //Если элемента нет, то возвращаем нулевой указатель
}

//Удалить элемент в позиции p со смещением
slinkedlist::node * slinkedlist::List::delete_with_change(node * list, t_position pos)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp -> next == pos) //Если следующий элемент равен позиции удаляемого элемента
        {
            temp -> next = pos -> next; //Записываем в следкющий элемент, элемент, после удаляемого
            delete pos; //Удаляем элемент в позиции pos
            return list; //Возвращаем список
        }
        temp = temp -> next;
    }
    return nullptr; //Если позиции нет, возвращаем нулевой указатель
}

//Поиск одинакового элемента в списке
slinkedlist::t_position slinkedlist::List::search_same_pos(node * list, elem x)
{
    node * temp = list;
    while(temp != nullptr)
    {
        if(x.adress == temp -> x.adress && x.name == temp -> x.name) //Данные совпадают
        {
            return temp; //Возвращаем позицию
        }
        temp = temp -> next;
    }
    return nullptr;
}

//Удалить список
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

//Существует ли позиция в списке
bool slinkedlist::List::position_exist(t_position position, node * list)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp == position) //Если поиции совпали
        {
            return true; //Позиция существует
        }
        temp = temp -> next;
    }
    return false; //Дошли до конца и не нашли, позиции нет
}

//Добавить элемент в хвост
slinkedlist::node * slinkedlist::List::add_to_tail(node * list, elem x)
{
    node * temp1 = list; //Указатель на голову
    node * temp2 = temp1 -> next; //Указатель на второй элемент
    while (temp2 != nullptr)
    {
        temp1 = temp1 -> next;//Доходим до предпоследнего элемента
        temp2 = temp2 -> next;
    }
    temp1 -> next = new node; //Добавляем элемент в конец
    temp1 -> next -> x = x;
    temp1 -> next -> next = nullptr;
    return list;
}

//Добавить элемент x в позицию p
slinkedlist::node * slinkedlist::List::add_to_pos(node * list, t_position pos, elem x)
{
    node * temp2 = new node(); //Выделяем память
    temp2 -> x = x; //Присапиваем значение
    temp2 -> next = pos -> next; //Следующий элемент равен следующий элемент позиции
    pos -> next = temp2; //Следующий элемент позиции равен новому элементу
    return list; //Возвращаем указатель на голову
}

dlinkedlist::node fake_d; //Фэйковый элемент для двусвязного списка, возвращается при ошибке(fake.next, если нужно вернуть позицию, fake.data, если объект)

dlinkedlist::List::List()
{
    _list.head = _list.tail = nullptr;
}

dlinkedlist::List::~List()
{
    _list = deleteList(_list); //Удаляем список
}

//Вставка в список
void dlinkedlist::List::insert(t_position p, elem x)
{
    if(_list.head == nullptr)//Если список пуст
    {
        node * temp = new node;//Добавляем новую голову
        temp -> next = nullptr;
        temp -> x = x;
        temp -> prev = nullptr;
        _list.head = _list.tail = temp;
    } else if(p == nullptr)//Если позиция равна концу списка
    {
        _list.tail = add_to_tail(_list.tail, x);//Добавляем элемент в хвост
    } else if(position_exist(p, _list.head))//Если позиция существует
    {
        _list.head = add_to_pos(_list.head, p, x);//Добавляем элемент в текущую позицию
    } else
    {
        std::cout << "position does not exist" << std::endl;//Выводим сообщение об ошибке
    }
}

//Вернуть последний элемент
dlinkedlist::t_position dlinkedlist::List::endL()
{
    return nullptr; //Возвращаем нулевой указатель
}

//Вернуть первый элемент
dlinkedlist::t_position dlinkedlist::List::firstL()
{
    return _list.head;//Возвращаем указатель на голову
}

//Вернуть следующий элемент, после позиции p
dlinkedlist::t_position dlinkedlist::List::next(t_position position)
{
    if(position == nullptr)//Если позиция равна концу строки
    {
        return nullptr;//Возвращаем конец строки
    }
    if(!position_exist(position, _list.head))//Если позиции не существует
    {
        return fake_d.next;//Возвращаем адрес фейкового элемента
    }
    return position -> next;//Если позиция удовлетворяет всем условиям, возвращаем указатель на следующий элемент списка
}

//Вернуть предыдущий элемент, до позиции p
dlinkedlist::t_position dlinkedlist::List::prev(t_position position)
{
    if(position == nullptr)//Если позиция равна концу строки
    {
        return _list.tail;//Вернуть последний элемент
    }
    if(!position_exist(position, _list.head))//Если позиции не существует
    {
        return fake_d.next;//Возвращаем адрес фейкового элемента
    }
    return position -> prev;//Если позиция удовлетворяет всем условиям, возвращаем указатель на предыдущий элемент списка
}

//Вернуть позицию элемента x в списке
dlinkedlist::t_position dlinkedlist::List::locate(elem x)
{
    return search_same_pos(_list.head, x);//Вернуть позицию по элементу, все проверки внутри функции
}

//Вернуть элемент по позиции в списке
elem dlinkedlist::List::retrieve(t_position position)
{
    if(position_exist(position, _list.head))
    {
        return position -> x;//Вернуть элемент по позиции
    } else
    {
        return fake.x;
    }
}

//Удалить элемент списка по позиции
dlinkedlist::t_position dlinkedlist::List::deleteEl(t_position position)
{
    if(position_exist(position, _list.head))//Если позиция существует
    {
        node * next = position -> next;// Записываем позицию, после последнего
        _list.head = delete_with_change(_list.head, position);//Удаляем со смещением
        return next; //Возвращаем позицию, после текущего элемента
    } else
    {
        std::cout << "position does not exist" << std::endl;
        return fake_d.next;//Возвращаем адрес фэйкового элемента
    }
}

//Вывести список
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

//Удаление списка
void dlinkedlist::List::makenull()
{
    _list = deleteList(_list);
}

//Удалить элемент в позиции p со смещением
dlinkedlist::node * dlinkedlist::List::delete_with_change(node * list, t_position pos)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp -> next == pos)//Если следующий элемент равен позиции удаляемого элемента
        {
            temp -> next = pos -> next;//Записываем в следкющий элемент, элемент, после удаляемого
            if(pos -> next != nullptr)  //Если следующий элемент не является концом списка
                pos -> next -> prev = temp; //Присваиваем указателю на предыдущий элемент следующего текушую позицию
            delete pos;//Удаляем элемент в позиции pos
            return list;//Возвращаем список
        }
        temp = temp -> next;
    }
    return nullptr;//Если позиции нет, возвращаем нулевой указатель
}

//Поиск одинакового элемента в списке
dlinkedlist::t_position dlinkedlist::List::search_same_pos(node * list, elem x)
{
    node * temp = list;
    while(temp != nullptr)
    {
        if(x.adress == temp -> x.adress && x.name == temp -> x.name)//Данные совпадают
        {
            return temp;//Возвращаем позицию
        }
        temp = temp -> next;
    }
    return fake_d.next;
}

//Удалить список
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

//Существует ли позиция в списке
bool dlinkedlist::List::position_exist(t_position position, node * list)
{
    node * temp = list;
    while (temp != nullptr)
    {
        if(temp == position)//Если поиции совпали
        {
            return true;//Позиция существует
        }
        temp = temp -> next;
    }
    return false;//Дошли до конца и не нашли, позиции нет
}

//Добавить элемент в хвост(передаем ХВОСТ! в качестве параметра)
dlinkedlist::node * dlinkedlist::List::add_to_tail(node * list, elem x)
{
    node * temp_t = new node();
    temp_t -> x = x;
    temp_t -> next = nullptr;
    temp_t -> prev = list;
    list -> next = temp_t;
    return temp_t;
}

//Добавить элемент x в позицию p
dlinkedlist::node * dlinkedlist::List::add_to_pos(node * list, t_position pos, elem x)
{
    node * temp2 = new node();//Выделяем память
    temp2 -> x = x;//Присапиваем хначение
    temp2 -> next = pos -> next;//Следующий элемент равен следующий элемент позиции
    temp2 -> prev = pos;//Предыдущий элемент равен позиции
    pos -> next = temp2;//Следующий элемент позиции равен новому элементу
    return list;//Возвращаем указатель на голову
}

cursorlist::node fake_c; //Фэйковый элемент для курсоров, возвращается при ошибке(fake.next, если нужно вернуть позицию, fake.data, если объект)

int cursorlist::List::_space = -1; //Инициализируем статическую переменную SPACE, давая ей значение неинициализированного списка
cursorlist::node cursorlist::List::_arr[SIZE];

void cursorlist::List::InitArr() //Инициализация массива списком пустых
{
    for (int i = 0; i < SIZE; i++)
    {
        if(i != SIZE - 1) { //Если не конец строки
            List::_arr[i].next = i + 1; //Указываем на следующи элемент
        } else {
            List::_arr[i].next = -1; //Указываем на конец списка
        }
    }
    List::_space = 0; //Устанавливаем позицию первого элемента списка пустых
}

cursorlist::List::List()
{
    _lpos = ENDL; //Позиция текущего списка, указывает на конец
    if(List::_space == -1) //Если список пустых не инициализирован
    {
        List::InitArr(); //Инициализируем список пустых
    }
}

//Вывести список
void cursorlist::List::printList()
{
    std::cout << std::setw(25) << "<index>";
    std::cout << std::setw(25) << "<data>";
    std::cout << std::setw(25) << "<next>" << std::endl;
    for (int i = 0; i < SIZE; ++i)
    {
        std::cout << std::setw(25) << i << " " << std::setw(25) << List::_arr[i].data.adress << " " << std::setw(25) << List::_arr[i].next << std::endl;
    }
}

//Вставка в список
void cursorlist::List::insert(t_position p, elem x)
{
    if(p == ENDL) //Если позиция равна концу строки
    {
        if(_lpos != ENDL) //Если список не пуст
        {
            int p_pos = get_prev_el(-1); //Получаем позицию последнего элемента
            List::_arr[p_pos].next = List::_space; //Указываем на первый пустой элемент
        }
        add_after(x); //Добавляем элемент в конец списка
    } else if(pos_exist(p)) //Если позиция существует
    {
        add_with_change(x, p); //Добавляем элемент в позицию со смещением
    } else
    {
        std::cout << "position " << p << "does not exist" << std::endl; //Просто выводим сообщение об ошибке
    }
}

//Вернуть следующий элемент, после позиции p
cursorlist::t_position cursorlist::List::next(t_position p)
{
    return get_next_el(p); //Вернуть следующий элемент, после позиции p, все проверки в функции
}

//Вернуть предыдущий элемент, до позиции p
cursorlist::t_position cursorlist::List::prev(t_position p)
{
    t_position temp = get_prev_el(p);
    if(temp == -1)
    {
        return fake_c.next;
    }
    return temp;//Вернуть предыдущий элемент, до позиции p, все проверки в функции
}

//Вернуть первый элемент
cursorlist::t_position cursorlist::List::firstL()
{
    return _lpos; //Возвращаем позицию первого элемента
}

//Вернуть конец списка
cursorlist::t_position cursorlist::List::endL()
{
    return ENDL; //Возвращаем конец списка
}

//Вернуть позицию элемента x в списке
cursorlist::t_position cursorlist::List::locate(elem x)
{
    t_position temp = search_same_pos(x);
    if(temp == -1)
    {
        return fake_c.next;
    } else
    {
        return temp;//Возвращаем позицию одинакового элемента(если он есть), все проверки в функции
    }
}

//Вернуть элемент по позиции в списке
elem cursorlist::List::retrieve(t_position p)
{
    t_position temp = get_prev_el(p);
    if(temp != -1 || p == _lpos)
    {
        return List::_arr[p].data;//Возвращаем элемент на одинаковой позиции(если она есть), все проверки в функции
    } else
    {
        return fake_c.data;
    }
}

//Удалить элемент списка по позиции
cursorlist::t_position cursorlist::List::deleteEl(t_position p)
{
    if(pos_exist(p)) //Существует ли позиция
    {
        return delete_with_change(p);//Удаляем элемент в позиции p со смещением
    } else
    {
        return fake_c.next; //Возвращаем позицию фэйкового элемента
    }
}

//Удаление списка
void cursorlist::List::makenull()
{
    node iter = List::_arr[_lpos];//Записываем в итератор, первый элемент списка
    int i = _lpos;//i является началом списка
    while(i != ENDL)
    {
        List::_arr[i].next = _space; //Завязываем элемент на список пустых
        List::_space = i; //Новый первый элемент списка пустых - это текущий
        i = iter.next;
        iter = List::_arr[iter.next];
    }
}

//Удалить элемент в позиции p со смещением
cursorlist::t_position cursorlist::List::delete_with_change(t_position p)
{
    int next = List::_arr[p].next; //Записываем позицию следуюзего элемента, чтобы вернуть нужную позицию по условии функции
    if(_lpos == p) //Если позиция равна началу списка
    {
        _lpos = List::_arr[p].next; //Обновляем позицию первого элемента
    } else
    {
        int prev = get_prev_el(p); //Записываем позицию предыдущего элемента
        List::_arr[prev].next = List::_arr[p].next; //Прошлый элемент, теперь указывает в переменной next на элемент через один
    }
    List::_arr[p].next = List::_space; //Позиция следующего элемента теперь указывает на первый из списка пустых
    List::_space = p;//Первый элемент в списке пустых, теперь равен позиции
    strcpy(List::_arr[p].data.name, ""); //Зануляем данные
    strcpy(List::_arr[p].data.adress, "");//Зануляем данные
    return next; // Возвращаем позицию следующего элемента, после удаляемого
}

// Поиск одинакового элемента в списке
cursorlist::t_position cursorlist::List::search_same_pos(elem x)
{
    node iter = List::_arr[_lpos]; //Записываем в итератор, первый элемент списка
    int i = _lpos; //i является началом списка
    while(i != ENDL)
    {
        if(x.adress == iter.data.adress && x.name == iter.data.name)//Если текущие данные равны с данными объекта x
        {
            return i; //Вернуть текущую позицию
        }
        i = iter.next;
        iter = List::_arr[iter.next];
    }
    return fake_c.next; //Если ничего не нашли, возврашаем позицию фейкового объекта
}

//Добавить элемент x в позицию p со смещением
void cursorlist::List::add_with_change(elem x, t_position p)
{
    if(List::_space != ENDL) // Если есть свободные элементы в списке пустых
    {
        node temp(x,List::_space); //Содаем буфферный элемент дл вставки
        int next_space = List::_arr[List::_space].next; //Записываем второй элемент списка пустых
        List::_arr[List::_space] = List::_arr[p]; //Добавляем существующий элемент с нашей позицией на свободную позицию
        List::_arr[p] = temp; //Вставляем элемент в позицию
        List::_space = next_space; //Устанавливаем новое значение списка пустых
    } else
    {
        std::cout << "no space elements" << std::endl; //Выводим сообщение, что свободных элементов нет
    }
}

//Получить позицию предыдущего элемента, до p
cursorlist::t_position cursorlist::List::get_prev_el(t_position p)
{
    node iter = List::_arr[_lpos];//Записываем в итератор, первый элемент списка
    int i = _lpos;//i является началом списка
    while(i != ENDL)
    {
        if(iter.next == p) //Если позиция следуюзего элемента равна текущей
        {
            return i;//Вернуть текущую позицию
        }
        i = iter.next;
        iter = List::_arr[iter.next];
    }
    return -1;//fake_c.next; //Если ничего не нашли, возврашаем позицию фейкового объекта
}

//Получить позицию следующего элемента, после p
cursorlist::t_position cursorlist::List::get_next_el(t_position p)
{
    node iter = List::_arr[_lpos];//Записываем в итератор, первый элемент списка
    int i = _lpos;//i является началом списка
    while(i != ENDL)
    {
        if(i == p)//Если текущая позиция равна сравниваемой
        {
            return iter.next; //Возвращаем позицию следующего объкета
        }
        i = iter.next;
        iter = List::_arr[iter.next];
    }
    return -1; //Если ничего не нашли, возврашаем позицию фейкового объекта
}

//Добавить элемент в конец списка
void cursorlist::List::add_after(elem x)
{
    int next_space = List::_arr[List::_space].next; //Записываем позицию 2го пустого элемента
    node temp(x, ENDL); //Создаем буферный объект для вставки
    List::_arr[List::_space] = temp; //Вставляем в свободную позицию
    if(_lpos == ENDL) //Если это первый элемент в списке
    {
        _lpos = List::_space; //Обнавляем первый элемент списка
    }
    List::_space = next_space; //Обновляем первый элемент списка пустых
}

//Существует ли позиция
bool cursorlist::List::pos_exist(t_position p)
{
    node iter = List::_arr[_lpos];//Записываем в итератор, первый элемент списка
    int i = _lpos;//i является началом списка
    while(i != ENDL)
    {
        if(i == p)//Если текущая позиция равна сравниваемой
        {
            return true; //Позиция существует
        }
        i = iter.next;
        iter = List::_arr[iter.next];
    }
    return false; //Если ничего не нашли, пройдя по всему списку, то позиции не существует
}


