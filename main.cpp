//
// Created by alexc on 11/11/2018.
//

#include <iostream>
#include <fstream>
#include "List.h"
using namespace cursorlist;

void readFile(List &l, const char * fname)
{
    std::ifstream myReadFile;
    myReadFile.open(fname);
    char name[20], address[20];
    if (myReadFile.is_open())
    {
        while (!myReadFile.eof())
        {
            myReadFile >> name;
            myReadFile >> address;
            l.insert(l.endL(), elem(name, address));
        }
        myReadFile.close();
    }
}

int main()
{
    List::InitArr();
    List obj;
    char fname[256];
    std::cout << "File name: ";
    std::cin >> fname;
    readFile(obj, fname);
    std::cout << "-------------------------------------------------------DATA:-------------------------------------------------------" << std::endl;
    obj.printList();
    std::cout << "_____________________________________________________________________________________________________________________" << std::endl;

    t_position q = obj.firstL();
    t_position p = obj.firstL();
    while (p != obj.endL())
    {
        q = obj.next(p);
        while(q != obj.endL())
        {
            if (obj.retrieve(p) == obj.retrieve(q))
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

    std::cout << "-------------------------------------------------------RESULT:-------------------------------------------------------" << std::endl;
    obj.printList();
    std::cout << "_____________________________________________________________________________________________________________________" << std::endl;
return 0;
}