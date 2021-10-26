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








int main(void)
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
    delete [] row_array ;
    return 0;
}
