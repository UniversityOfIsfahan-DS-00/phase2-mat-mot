#include <iostream>
#include <QString>
#include "link_list.h"
#include <dirent.h>
#include <QStringList>
#include <QFile>
#include <QDebug>
#include <QTextStream>
#include <QVector>
#include <string.h>
#define ll long long
using namespace std ;
string selected_file ;
long long row ;
long long col ;
void label_print (QString tmp )//----------------design
{
    cout << (char)201 ;
    for (int i=0 ; i<98 ; i++ )
        cout << (char) 205 ;
    cout << (char) 187 << endl ;
    cout << (char) 186 ;
    for (int i=0 ; i<98 ; i++ )
        cout << (char) 32 ;
    cout << (char) 186 << endl ;
    cout << (char) 186 ;
    for (int i=0 ; i<98 ; i++ )
    {
        if (i == (98 - tmp.length())/2 )
        {
            cout << tmp.toStdString() ;
            i+= tmp.length() ;
        }
        cout << (char) 32 ;
    }
    cout << (char) 186 << endl ;
    cout << (char) 186 ;
    for (int i=0 ; i<98 ; i++ )
        cout << (char) 32 ;
    cout << (char) 186 << endl ;
    cout << (char) 200 ;
    for (int i=0 ; i<98 ; i++ )
        cout << (char) 205 ;
    cout << (char) 188 << endl ;
}
bool load_part ()
{
    QStringList pathlist , dirlist ;
    QString path = __FILE__  ;
    path +=  "\\.." ;
    char p[200] = {0} ;
    for (int i=0 ; i<path.length() ; i++)
        p [i] = path[i].toLatin1() ;
    DIR *dir;
    struct dirent *diread;
    if ((dir = opendir(p) ) != nullptr)
    {
        while ((diread = readdir(dir)) != nullptr)
        {
            dirlist.append(diread->d_name) ;
        }
        closedir (dir);
    } else
        perror ("opendir");
    for (int i=0 ; i<dirlist.size() ;i++ )
        if (dirlist.at(i).contains(".csv"))
            pathlist.append(dirlist.at(i)) ;
    system("cls") ;
    label_print("load");
    cout << "please choose which file opened for process !? " << endl ;
    cout << "notice : if there is no file name in falowing list please check the format of file (only format that support is .csv ) ! \n" ;
    cout << "for exit the program enter 0 .\n" ;
    for (int i=0 ;i<pathlist.size();i++ )
        cout << i+1 << ". " << pathlist.at(i).toStdString() << endl ;
    cout << "enter the number of file ! : " ;
    int fselect ;
    cin >> fselect ;
    if (fselect==0)
        return true;
    path += "\\" + pathlist.at(fselect-1) ;
    selected_file = pathlist.at(fselect-1).toStdString() ;
    try
    {
        QString tmp ;
        for ( int i=0 ; i < (int) selected_file.length() ;i++)
            if (selected_file[i] == '(')
            {
                i++ ;
                while (selected_file[i] != ')')
                {
                    tmp += selected_file[i] ;
                    i ++ ;
                }
            }
        dirlist = tmp.split(",") ;
        row = dirlist.at(0).toLongLong() ;
        col = dirlist.at(1).toLongLong() ;
    }
    catch (...)
    {
        cout << "posibly file name was wrong file name should be like name(row,col).csv check first then reopen program !\n" ;
    }
    cout << "please wait ....\n" ;
    return false;
}
void load_from_file (long long * row_array)
{
    string path = __FILE__ ;
    path += "\\..\\"  +  selected_file ;
    QFile mat (QString::fromStdString( path )) ;
    if (!mat.open(QIODevice::ReadOnly | QFile::Text) && mat.exists())
    {
        qInfo() << mat.errorString() << __LINE__ << "\n" ;
        cout << "file does not work please close and re open program !\n" ;
        return ;
    }
    QTextStream matqts (&mat) ;
    matqts.seek(0) ;
    int i =0 ;
    while (!matqts.atEnd())
    {
        QString line = matqts.readLine() ;
        QStringList index = line.split(QLatin1Char(',')) ;
        link_list<ll> * tmp = (link_list<ll>*) row_array[i] ;
        for (int k=0 ; k<index.size() ; k++)
        {
            if (index.at(k) != '0')
                tmp->add_last(index.at(k).toLongLong() , k) ;
        }
        i++ ;
    }
    mat.close() ;
}
void insert (ll row , ll col , ll value , ll*row_list )
{
    link_list<ll> *tmp = (link_list<ll>*) row_list[row] ;
    if (tmp->isempty())
    {
        tmp->add_first(value , col);
        cout << "insert was successful !\n" ;
        return;
    }
    if (tmp->getHead()->columnindex >= col )
    {
        tmp->add_first(value , col) ;
        cout << "insert was successful !\n" ;
        return;
    }
    else if (tmp->getTail()->columnindex < col )
    {
        tmp->add_last(value , col) ;
        cout << "insert was successful !\n" ;
        return;
    }
    else
    {
        node<ll> * tt = tmp->getHead() ;
        while (tt)
        {
            if (tt->columnindex < col && col > tt->next->value)
            {
                tmp->add_between(tt , value , col , tt->next) ;
                cout << "insert was successful !\n" ;
                return;
            }
            tt = tt->next ;
        }

    }
    cout << "insert was not successful !\n" ;
}
void delete_node (ll row , ll col , ll *row_list)
{
    link_list<ll> *tmp = (link_list<ll>*) row_list[row] ;
    if (tmp->isempty())
    {
        cout << "delete was not successful !\n" ;
        return;
    }
    node<ll> *tt = tmp->getHead() ;
    while (tt)
    {
        if (tt->columnindex == col)
        {
            tmp->remove(tt) ;
            cout << "delete was successful !\n" ;
            return;
        }
        tt = tt->next ;
    }
    cout << "delete was not successful !\n" ;
}
void search (ll value , ll*row_list)
{
    for (ll i=0 ; i <row ; i++)
    {
        link_list<ll> *tmp = (link_list<ll>*) row_list[i] ;
        node<ll> * tt = tmp->getHead() ;
        while (tt)
        {
            if (tt->value == value )
            {
                cout << "your searched value location is : " << i << "," << tt->columnindex << "\n" ;
                return;
            }
            tt = tt->next ;
        }
    }
    cout << "your searched value doesn't exist !\n" ;
}
void update (ll row , ll col , ll value , ll* row_list)
{
    link_list<ll> *tmp = (link_list<ll>*) row_list[row] ;
    node<ll> *tt = tmp->getHead() ;
    while (tt)
    {
        if (tt->columnindex == col )
        {
            tt->value = value ;
            cout << "update was successful !\n" ;
            return;
        }
        tt = tt->next ;
    }
    cout << "update wasn't successful !\n" ;
}


bool process_part (ll * row_list)
{
    int i ;
    while (true)
    {
        system("cls") ;
        label_print("process") ;
        QString hint ;
        hint += "code table :\n0. for insert the node.\n1. for delet the node.\n2. for search a node in matrix.\n" ;
        hint += "3. for update the node.\n4. for print a matrix in two diffrente ways.\n5. for save change to file.\n" ;
        hint += "6. for trun back and choose other file (careful may your change doesn't apply).\n7. for exit and close program.\n" ;
        cout << hint.toStdString() << "enter you code : ";
        cin >> i ;
        ll row , col , value ;
        if (i==0)
        {
            system("cls") ;
            label_print("process") ;
            cout << "please enter row & col & value in right order to continue !\n" ;
            cin >> row >> col >> value ;
            insert (row , col , value , row_list) ;
            system("pause") ;
        }
        else if (i==1)
        {
            system("cls") ;
            label_print("process") ;
            cout << "please enter row & col of node that you want to deleted !\n" ;
            cin >> row >> col ;
            delete_node ( row , col ,row_list ) ;
            system("pause") ;
        }
        else if (i==2)
        {
            system("cls") ;
            label_print("process") ;
            cout << "please enter value that you want to search !\n" ;
            cin >> value ;
            search (value , row_list) ;
            system("pause");
        }
        else if (i==3)
        {
            system("cls") ;
            label_print("process") ;
            cout << "please enter row & col & value of node that you want to updated !\n" ;
            cin >> row >> col >> value ;
            update(row,col,value,row_list) ;
            system("pause");
        }
        else if (i==4)
        {
            system("cls") ;
            label_print("process") ;
            cout << "for print matrix orginaly with full index enter 0\nandfor print matrix in compress mode with few index enter 1: \n" ;
            cin >> row ;
            //print ((bool)row , row_list) ;
            system("pause");
        }
        else if (i==5)
        {
            system("cls") ;
            label_print("process") ;
            //save_to_file (row_list) ;
            system("pause") ;
        }
        else if (i==6)
        {
            return true;
        }
        else if (i==7)
        {
            return false;
        }
    }
}
int main(void)
{
    while (true)
    {
        if (load_part())
        {
            return 0;
        }
        long long * row_array = new long long [row] ;
        for (ll i=0 ; i<row ;i++)
        {
            link_list<ll> * tmp = new link_list<ll> () ;
            row_array[i] = (long long) tmp ;
        }
        load_from_file (row_array) ;
        if (!process_part (row_array) )
        {
            delete [] row_array ;
            return 0;
        }
        delete [] row_array ;
    }
    return 0;
}
