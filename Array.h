/// Created by Danylo Boiko on 4/4/2020.

#ifndef OOP_09_BOIKO_ARRAY_H
#define OOP_09_BOIKO_ARRAY_H

#include <iostream>
using namespace std;
template< typename Elem>
class Array{
private:
    size_t _len;
    Elem * _allocator;
public:
    Array<Elem>(const Array&);
    Array& operator=(const Array&);
    class BadArray;
    explicit Array<Elem>(size_t cap = 10);
    ~Array();
    Elem& operator[](size_t index);
    const Elem& operator[](size_t index) const;
    size_t size() const;

    bool operator==(const Array&) const;
};



template< typename Elem>
Array<Elem>::Array(size_t cap ): _len(cap), _allocator(new Elem[_len]){
   // cout<<"Created Array"<<endl;
}
template< typename Elem>
Array<Elem>::Array(const Array & a): _len(a.size()), _allocator(new Elem[_len]) {
    for(size_t i = 0; i<_len;++i){
        _allocator[i] = a._allocator[i];
    }
   // cout<<"Copied Array"<<endl;
}
template< typename Elem>
Array< Elem>& Array< Elem>::operator=(const Array & a) {
    _len = a._len;
     Elem *temp  =  new Elem[_len];
    for(size_t i = 0; i<_len;++i){
        temp[i] = a._allocator[i];
    }
    delete [] _allocator;
    _allocator = new Elem[_len];
    for(size_t i = 0; i<_len;++i){
        _allocator[i] = temp[i];
    }
  //  cout<<"Copied Array"<<endl;
    return *this;
}
template< typename Elem>
Elem& Array< Elem>::operator[](const size_t index) {
    if(index<0 || index>=_len) throw BadArray("Wrong index");
    return _allocator[index];
}
template< typename Elem>
const Elem &Array< Elem>::operator[](const size_t index) const {
    if(index<0 || index>=_len) throw BadArray("Wrong index");
    return _allocator[index];
}


template< typename Elem>
size_t Array< Elem>::size() const {
    return _len;
}

template< typename Elem>
Array< Elem>::~Array() {
    delete[] _allocator;
}
    template< typename Elem>
class Array< Elem>::BadArray{
    private:
        const string _error;
    public:
        explicit BadArray(string a);
        ~BadArray();
        void diagnose() const;

};

template< typename Elem>
bool Array< Elem>::operator==(const Array & a) const {
    if(_len != a._len)
        return false;
    for(size_t i = 0; i<_len; ++i){
        if(_allocator[i] != a._allocator[i])
            return false;
    }
    return true;
}


template< typename Elem>
Array< Elem>::BadArray::BadArray(string a):_error(a) {
}

template< typename Elem>
Array< Elem>::BadArray::~BadArray() {

}

template< typename Elem>
void Array< Elem>::BadArray::diagnose() const  {
    cerr<<_error;
    cerr<<endl;
    return;
}


template< typename Elem>
ostream& operator<<(ostream& os, const Array< Elem>& ar) {
    char chr=' ';
    os<<"Array of "<<ar.size()<<':';
    for(size_t i=0; i<ar.size(); i++) {
        os<<chr<<ar[i];
    }
    os<<'.';
    return os;
}
#endif //OOP_09_BOIKO_ARRAY_H
