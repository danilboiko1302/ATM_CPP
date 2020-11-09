/// Created by Danylo Boiko on 4/4/2020.

#ifndef OOP_10_BOIKO_SEQUENCE_H
#define OOP_10_BOIKO_SEQUENCE_H
#include "Array.h"
#include <cassert>
template< typename Elem>
class Sequence{
public:
    class BadSeq;
    explicit Sequence(size_t capacity=_default);
    ~Sequence();
    Sequence& show();
    size_t capacity() const;
    size_t sizes() const;
    bool empty() const;
    bool full() const;
    Sequence& clear();
    const Elem& operator[](size_t index) const;
    Elem& operator[](  size_t index);
    Sequence& add(const Elem& elem);
    Sequence& insert(const Elem& elem,  size_t index);
    Sequence& cut();
    Sequence& cutFirst();
    Sequence& remove(size_t index);
    bool contains(const Elem & elem);

private:
    size_t _size;
    static const size_t _default=0;
    Array<Elem> * _allocator;
    void reduce(size_t times=2);
    void enlarge(size_t times=2);
    Sequence& doInsert(const Elem& elem, size_t index);
    Sequence& doRemove(size_t index);
    Sequence (const Sequence&);
    Sequence& operator=(const Sequence&);
};
template< typename Elem>
Sequence<Elem>::Sequence(const size_t capacity):_size(0),_allocator((new Array<Elem>(capacity))){
    //cout<<"Sequence created"<<endl;
}
template< typename Elem>
Sequence<Elem>::~Sequence(){
   // cout<<"Sequence deleted"<<endl;
}

template<typename Elem>
size_t Sequence<Elem>::capacity() const {
    return (*_allocator).size();
}
template<typename Elem>
size_t Sequence<Elem>::sizes() const {return _size;}

template<typename Elem>
bool Sequence<Elem>::empty() const  {return (sizes()==0);}

template<typename Elem>
bool Sequence<Elem>::full() const {return sizes()==capacity();}

template<typename Elem>
Sequence<Elem> &Sequence<Elem>::clear(){_size=0;

    return *this;}
template<typename Elem>
const Elem& Sequence<Elem>::operator[](const size_t index) const {
    if(empty())
        throw BadSeq("Try to manipulate the empty sequence");
    if(index>_size)
        throw BadSeq("Try to access a non existing element of the sequence");
    return  (*_allocator)[index];
}
template<typename Elem>
Elem& Sequence<Elem>::operator[](const size_t index) {
    if(empty())
        throw BadSeq("Try to manipulate the empty sequence");
    if(index>_size)
        throw BadSeq("Try to access a non existing element of the sequence");
    return  (*_allocator)[index];
}
template<typename Elem>
Sequence<Elem>& Sequence<Elem>::add(const Elem& elem) {
    return doInsert(elem, _size);
}
template<typename Elem>
Sequence<Elem>& Sequence<Elem>::insert(const Elem& elem, const size_t index) {
    if(_size<index) throw BadSeq("Try to insert after a non existing element of the sequence");
    return doInsert(elem, index);
}
template<typename Elem>
Sequence<Elem>& Sequence<Elem>::doInsert(const Elem& elem, size_t index) {

    if(_size+1>capacity())
        enlarge();
    ++_size;
    for (size_t i=_size-1; i>index; --i)
        (*_allocator)[i]= (*_allocator)[i-1];
    (*_allocator)[index]=elem;

    return *this;
}
template<typename Elem>
Sequence<Elem>& Sequence<Elem>::cut() {
    return doRemove(_size); // Видалити елемент із кінця
}
template<typename Elem>
Sequence<Elem>& Sequence<Elem>::remove(const size_t index) {
// Перевірити допустимість індексу
    if((_size<index)||(index==0))
        throw BadSeq("Try to delete a non existing element of the sequence");
    return doRemove(index); // Видалити елемент за індексом
}
template<typename Elem>
Sequence<Elem>& Sequence<Elem>::doRemove(size_t index) {
    if(empty())
        throw BadSeq("Try to manipulate the empty sequence");
    if(_size*2<capacity())
        reduce();
// Зменшити розмір послідовності

// Зсунути залишок послідовності ліворуч

    for (size_t i=index; (i<_size)&&(i>0); ++i)
        (*_allocator)[i-1]=  (*_allocator)[i];
    --_size;
    return *this;
}

template<typename Elem>
bool Sequence<Elem>::contains(const Elem &elem) {
    for(size_t i = 0; i<_allocator->size();++i){
        if((*_allocator)[i] == elem){
            return true;
        }
    }
    return false;
}

template<typename Elem>
Sequence<Elem>& Sequence<Elem>::show() {
    cout<<"Sequence: ";
    for(size_t i = 0; i<_size;++i){
        cout<<((*_allocator)[i])<<" ";
    }
    cout<<endl;
    return *this;
}
template< typename Elem>
class Sequence<Elem>::BadSeq{
private:
    const string _error;
public:
    explicit BadSeq(string a);
    ~BadSeq();
    void diagnose() const;
};

template<typename Elem>
void Sequence<Elem>::enlarge(size_t times) {
    Array<Elem> temp((*_allocator));
    delete  _allocator;
    _allocator = new Array<Elem>(temp.size()*2+1);
    for(size_t i = 0; i<temp.size();++i){
        (*_allocator)[i] =temp[i] ;
    }

}

template<typename Elem>
void Sequence<Elem>::reduce(size_t times) {
    Array<Elem> temp((*_allocator));
    delete  _allocator;
    _allocator = new Array<Elem>(temp.size()/2);
    for(size_t i = 0; i<temp.size()/2;++i){
        (*_allocator)[i] =temp[i] ;
    }
}

template<typename Elem>
Sequence<Elem> &Sequence<Elem>::cutFirst() {
    return remove(1);
}

template<typename Elem>
Sequence<Elem>::BadSeq::BadSeq(string a):_error(a) {

}

template<typename Elem>
Sequence<Elem>::BadSeq::~BadSeq() {

}

template<typename Elem>
void Sequence<Elem>::BadSeq::diagnose() const {
    cerr<<_error;
    cerr<<endl;
    return;
}

#endif //OOP_10_BOIKO_SEQUENCE_H
