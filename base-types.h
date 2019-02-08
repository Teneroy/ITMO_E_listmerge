//
// Created by alexc on 1/17/2019.
//

#ifndef ITMO_E_LISTMERGE_BASE_TYPES_H
#define ITMO_E_LISTMERGE_BASE_TYPES_H
struct elem
{
    char name[20]; //Имя
    char adress[20]; //Адрес
    elem() {name[0] = '\0'; adress[0] = '\0';}; //Конструктор по умолчанию, инициализируем строки
    elem(const char * n, const char * a) {strcpy(name, n);strcpy(adress, a);}; //Конструктор с параметрами
    bool operator == ( const elem &ob ) const
    {
        return strcmp(name, ob.name) == 0;
    };
    friend std::ostream& operator<< ( std::ostream& out, const elem& x )
    {
        out << x.name << " " << x.adress;
    }
};
#endif //ITMO_E_LISTMERGE_BASE_TYPES_H
