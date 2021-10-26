#ifndef LINK_LIST_H
#define LINK_LIST_H
#include <iostream>
using namespace std ;
template <typename Q>
class node
{
public:
    Q value ;
    long long columnindex ;
    node * next ;
    node (Q v , long long ci , node * n)
    {
        this->value = v ;
        this->columnindex = ci ;
        this->next = n ;
    }
};
//--------------------------------------------------------
template<typename  T>
class link_list
{
    node<T> *head ;
    node<T> *tail ;
    int size ;
public:
    link_list()
    {
        this->head = nullptr ;
        this->tail = nullptr ;
        this->size = 0 ;
    }
    void add_between (node<T> * prev , T v , long long colindex , node<T> *next)
    {
        node<T> * tt = new node<T> (v , colindex , next) ;
        prev->next = tt ;
        size ++ ;
    }
    void add_first (T v , long long colindex )
    {
        node<T> * tmp  = new  node<T> (v , colindex , this->head) ;
        if ( this->head == nullptr )
        {
            this->head = tmp ;
            this->tail = tmp ;
            this->size ++ ;
            return;
        }
        this->head = tmp ;
        this->size ++ ;
    }
    void add_last (T v , long long colindex )
    {
        if ( this->tail == nullptr )
        {
            this->add_first(v , colindex) ;
            return;
        }
        node<T> * tmp = new  node<T> (v , colindex , nullptr ) ;
        this->tail->next = tmp ;
        this->tail = tmp ;
        this->size ++ ;
    }
    int getsize ()
    {
        return this->size;
    }
    bool isempty ()
    {
        return (size==0);
    }
    T first_eleman ()
    {
        return head->value ;
    }
    T last_eleman ()
    {
        return tail->value ;
    }
    T remove_first ()
    {
        if ( this->head == nullptr )
            return  NULL ;
        T a = head->value ;
        node<T> * tmp = this->head ;
        this->head = this->head->next ;
        this->size -- ;
        delete  tmp ;
        tmp = nullptr ;
        if ( size == 0 )
        {
            this->tail = nullptr ;
            return a ;
        }
        return  a ;
    }
    T remove_last ()
    {
        if (this->tail == nullptr )
            return NULL ;
        T a = tail->value ;
        node<T> * tmp = this->tail ;
        this->size -- ;
        delete tmp ;
        tmp = head ;
        for (int i=0 ; i<this->size  ; i++)
            tmp = tmp->next ;
        this->tail = tmp ;
        if ( size == 0  )
        {
            this->tail == nullptr ;
            this->head = nullptr ;
            return a ;
        }
        this->tail->next = nullptr ;
        return a ;
    }
    T remove (node<T> * tmp )
    {
        if (isempty())
            return NULL;
        if (this->size == 1)
        {
            T data = tmp->value ;
            delete tmp ;
            head =nullptr ;
            tail = nullptr ;
            size -- ;
            return data ;
        }
        if (head == tmp)
        {
            head = tmp->next ;
            size -- ;
            T data = tmp->value ;
            delete  tmp ;
            return data;
        }
        node<T> *tt = head ;
        while (tt)
        {
            if (tt->next == tmp)
            {
                tt->next = tmp->next ;
                size-- ;
                T data = tmp->value ;
                delete tmp ;
                return data ;
            }
            tt = tt->next ;
        }
        return NULL ;
    }
    node<T> *getHead() const
    {
        return head;
    }
    void setHead(node<T> *newHead)
    {
        head = newHead ;
    }
    node<T> *getTail() const
    {
        return tail;
    }
    void setTail(node<T> *newTail)
    {
        tail = newTail ;
    }
    ~link_list()
    {
        if ( this->head != nullptr && this->tail != nullptr )
        {
            while ( this->head )
            {
                node<T> * tp = this->head ;
                this->head = tp->next ;
                delete  tp ;
                tp = nullptr ;
            }
            this->size = 0 ;
            this->head = nullptr ;
            this->head = nullptr ;
        }
    }
};
#endif // LINK_LIST_H
