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
int main(void)
{

    return 0;
}
