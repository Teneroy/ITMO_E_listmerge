//
// Created by alexc on 11/11/2018.
//

#include <iostream>
#include "string.h"
#include "List.h"

int main()
{
    /*ARRAY LIST*/
    arrlist::List obj;
    elem x("Alexey", "Brianceva 12");
    elem y("Leonid", "Rudneva 22");
    elem z("Igor", "Kultura 11");
    obj.insert(0, x);
    obj.insert(1, y);
    obj.insert(2, z);
    obj.insert(3, y);
    obj.insert(4, z);
    obj.insert(0, y);
    obj.insert(4, x);
    obj.printList();

    elem temp, temp2;
    arrlist::t_position q = 0;
    arrlist::t_position p = obj.firstL();
    while (p != obj.endL())
    {
        q = obj.next(p);
        while(q != obj.endL())
        {
            temp = obj.retrieve(p);
            temp2 = obj.retrieve(q);
            if (strcmp(temp.name, temp2.name) == 0 && strcmp(temp.adress, temp2.adress) == 0 )
            {
                q = obj.deleteEl(q);
            }
            else
            {
                q = obj.next(q);
            }
        }
        p = obj.next(p);
    }

    /*SINGLE LINKED LIST*/
    slinkedlist::List ob;
    slinkedlist::t_position pos = ob.firstL();
    ob.insert(pos, z);
    pos = ob.next(pos);
    ob.insert(pos, x);
    pos = ob.next(pos);
    ob.insert(pos, y);
    pos = ob.next(pos);
    ob.insert(pos, z);
    ob.insert(pos, y);
    pos = ob.next(pos);
    ob.insert(pos, z);
    ob.printList();
    slinkedlist::t_position j = nullptr;
    slinkedlist::t_position i = ob.firstL();
    while (i != ob.endL())
    {
        j = ob.next(i);
        while(j != ob.endL())
        {
            temp = ob.retrieve(i);
            temp2 = ob.retrieve(j);
            if (strcmp(temp.name, temp2.name) == 0 && strcmp(temp.adress, temp2.adress) == 0 )
            {
                j = ob.deleteEl(j);
            }
            else
            {
                j = ob.next(j);
            }
        }
        i = ob.next(i);
    }


    /*DOUBLE LINKED LIST*/
    dlinkedlist::List obd;
    dlinkedlist::t_position pos_d = obd.firstL();
    obd.insert(pos_d, z);
    pos_d = obd.next(pos_d);
    obd.insert(pos_d, x);
    pos_d = obd.next(pos_d);
    obd.insert(pos_d, y);
    pos_d = obd.next(pos_d);
    obd.insert(pos_d, z);
    obd.insert(pos_d, y);
    pos_d = obd.next(pos_d);
    obd.insert(pos_d, z);

    dlinkedlist::t_position qd = nullptr; //добавить конструтор по умолчанию?
    dlinkedlist::t_position pd = obd.firstL();
    while (pd != obd.endL())
    {
        qd = obd.next(pd);
        while(qd != obd.endL())
        {
            temp = obd.retrieve(pd);
            temp2 = obd.retrieve(qd);
            if (strcmp(temp.name, temp2.name) == 0 && strcmp(temp.adress, temp2.adress) == 0 )
            {
                qd = obd.deleteEl(qd);
            }
            else
            {
                qd = obd.next(qd);
            }
        }
        pd = obd.next(pd);
    }

    /*CURSOR LIST*/
    cursorlist::List obc;
    obc.insert(-1, x);
    obc.insert(0, y);
    obc.insert(0, z);
    obc.insert(-1, z);
    obc.insert(-1, z);
    obc.printList();

    cursorlist::t_position qc = 0;
    cursorlist::t_position pc = obj.firstL();
    while (pc != obc.endL())
    {
        qc = obc.next(pc);
        while(qc != obc.endL())
        {
            temp = obc.retrieve(pc);
            temp2 = obc.retrieve(qc);
            if (strcmp(temp.name, temp2.name) == 0 && strcmp(temp.adress, temp2.adress) == 0 )
            {
                qc = obc.deleteEl(qc);
            }
            else
            {
                qc = obc.next(qc);
            }
        }
        pc = obc.next(pc);
    }

    std::cout << std::endl;
    std::cout << "-------------------------------------------------------RESULT:-------------------------------------------------------" << std::endl;
    std::cout << "______________________________________________________ARRAY REALIZATION______________________________________________" << std::endl;
    obj.printList();
    std::cout << "_____________________________________________________________________________________________________________________" << std::endl;
    std::cout << "_______________________________________________SINGLE LINKED LIST REALIZATION________________________________________" << std::endl;
    ob.printList();
    std::cout << "_____________________________________________________________________________________________________________________" << std::endl;
    std::cout << "_______________________________________________DOUBLE LINKED LIST REALIZATION________________________________________" << std::endl;
    obd.printList();
    std::cout << "_____________________________________________________________________________________________________________________" << std::endl;
    std::cout << "____________________________________________________CURSORS REALIZATION______________________________________________" << std::endl;
    obc.printList();
    std::cout << "_____________________________________________________________________________________________________________________" << std::endl;
    std::cout << "---------------------------------------------------------------------------------------------------------------------" << std::endl;

return 0;
}