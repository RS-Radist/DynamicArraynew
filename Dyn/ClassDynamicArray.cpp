//
//  ClassDynamicArray.cpp
//  Задание №6
//
//  Created by MacBook on 27.10.17.
//  Copyright © 2017 Задание №6. All rights reserved.
//

#include "ClassDynamicArray.hpp"
#include <stdio.h>
#include <iostream>
#include "UniTest.h"

template <typename T>
bool DynamicArray<T>::IsArraysEqual(const DynamicArray<T>& one, const DynamicArray<T>& two)
{
    if(one.GetSize() != two.GetSize())
        return false;
    
    for (int i =0; i<one.GetSize(); ++i)
    {
        if(one[i]!=two[i])
            return false;
    }
    return true;
}
template <typename T>
DynamicArray <T>::DynamicArray(size_t size): size(size), current_idx(0)
{
    ar = new T [size]; // выделение памяти .  ar = new int
}
template <typename T>
DynamicArray <T>::DynamicArray(const DynamicArray& obj)
{
    current_idx=obj.current_idx;
    size = obj.current_idx;
    ar = new T [obj.current_idx];
    if (!ar)
    {
        std::cerr << "Error allocation mamory!\n";
        return;
    }
    //exit(1); ///  Завершение с кодом ошибки ,
    for (int i=0;i<obj.current_idx;++i)
        ar[i]=obj.ar[i];
}
template <typename T>
int DynamicArray <T>::Get (size_t index)
{
    if (index>=size)
    {
        return ar[0];
    }
    return ar[index];
}
template <typename T>
void DynamicArray <T>:: Push (T a)
{
    current_idx += 1;  // добавление + 1 // реальнjuj размерf массива
    if(current_idx < size) // проверка размера
    {
        ar[current_idx-1] = a; //
        return;
    }
    T * numberTemp;                             ////
    numberTemp=new T [size + 1];                //// ВЫУЧИТЬ
    memcpy(numberTemp, ar, sizeof(T) * size);   ////
    numberTemp[size] = a;                         ////
    size += 1; ////
    delete[] ar;////
    ar = numberTemp;////
}
template <typename T>
size_t DynamicArray <T>::GetSize() const
{
    return current_idx;
}
template <typename T>
size_t DynamicArray<T>::GetCapacity() const
{
    return size;
}
template <typename T>
T DynamicArray <T>:: GetR() const
{
    return * ar;
}

template <typename T>
DynamicArray <T>& DynamicArray<T>::operator=(const DynamicArray <T>& obj)
{
    T* temp = new T[obj.current_idx];
    if(!temp)
    {
        std::cerr << "Error allocation\n";
        return *this;
    }
    if(this->ar)
        delete[] this->ar;
    this->size = obj.current_idx;
    this->current_idx=obj.current_idx;
    this->ar = temp;
    
    for (int i=0;i<obj.current_idx;++i)
        this->ar[i]=obj.ar[i];
    return *this;
}






template <typename T>
DynamicArray <T> operator+(const DynamicArray<T>& l, const DynamicArray<T>& r)
{
    DynamicArray <T> ret(l + r.GetSize());// создаем объект массив и выделяем память размером current_idx + r.current_idx
    memcpy(r.GetR(),l.GetR(), sizeof(T) * l.GetSize());// копируем кол-во байт из ar в ret.ar
    memcpy(ret.GetR()+l.GetSize(), r.GetR(), sizeof(T) * r.GetSize());//докапируем в ret.ar+current_idx из r.ar
    ret.GetCapacity() = l.GetSize() + r.GetSize() + 1; //
    ret.GetSize() = ret.GetCapacity() - 1;
    return ret;
}




template <typename T>
DynamicArray <T> operator+(const DynamicArray <T>& l,T x)
{
    DynamicArray <T> ret(l.current_idx+1);
    memcpy(ret.ar,l.ar, sizeof(T) * l.current_idx);
    memcpy(ret.ar+l.current_idx, &x, sizeof(T));
    ret.current_idx = ret.size;
    return ret;
}

template <typename T>
DynamicArray <T> operator-(const DynamicArray <T> & l,const DynamicArray <T>& r)
{
    DynamicArray <T>temp;
    for(size_t i = 0; i < l.GetCapacity(); ++i)
    {
        size_t j = 0;
        for(; j < r.GetCapacity(); ++j)
        {
            if(l[i] == r[j])
                break;
        }
        if(j != r.GetCapacity())
        {
            temp.Push(l[i]);
        }
    }
    return temp;
}
template <typename T>
DynamicArray <T> operator/(const DynamicArray <T> & l,const DynamicArray <T> & r)
{
    if(l.current_idx != r.current_idx)
        return l;
    DynamicArray <T>ret(l.current_idx);
    for (int i=0;i<l.current_idx;++i)
    {
        ret[i] /= r[i];
    }
    return ret;
}
template <typename T>
DynamicArray <T> operator-(const DynamicArray <T>& l,T x)
{
    DynamicArray <T> ret(l);
    for (int i=0;i<l.current_idx;++i)
    {
        ret[i] = l[i]-x;
    }
    return ret;
}
template <typename T>
DynamicArray <T> operator*(const DynamicArray<T>& l,T x)
{
    DynamicArray <T> ret(l);
    for (int i=0;i<l.current_idx;++i)
    {
        ret[i] = l.ar[i]*x;
    }
    return ret;
}
template <typename T>
DynamicArray <T> operator*(const DynamicArray <T> & l,const DynamicArray <T> & r)
{
    if(l.current_idx != r.current_idx)
        return *l.ar;
    DynamicArray <T> ret(l);
    for (int i=0;i<l.current_idx;++i)
    {
        ret[i] *= r.ar[i];
    }
    return ret;
}
template <typename T>
DynamicArray <T> operator/(const DynamicArray <T> & l,T x)
{
    DynamicArray <T> ret(l);
    for (int i=0;i<l.current_idx;++i)
    {
        ret[i] = l.ar[i]/x;
    }
    return ret;
}


template <typename T>
bool operator==(const DynamicArray <T>& l,const DynamicArray <T>& r) 
{
    
    return DynamicArray<T>::IsArraysEqual(const DynamicArray<T>& one, const DynamicArray<T>& two);
}
template <typename T>
T & DynamicArray <T>::operator[](int idx) //
{
    if(idx > this->current_idx)
    {
        std::cerr << "Index out of range\n";
    }
    return ar[idx];
}
template <typename T>
const T & DynamicArray<T>::operator[](int idx) const//
{
    if(idx > this->current_idx)
    {
        std::cerr << "Index out of range\n";
    }
    return ar[idx];
}
template <typename T>
DynamicArray<T> & DynamicArray<T>::operator++()
{
    for (int i = 0;i<current_idx;++i)
    {
        this->ar[i]+=1;
    }
    return *this;
}
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator--()
{
    for (int i = 0;i<current_idx;++i)
    {
        this->ar[i]-=1;
    }
    return *this;
}
template <typename T>
DynamicArray<T> DynamicArray<T>::operator++(int)
{
    DynamicArray <T> tmp(*this); // copy
    operator++();
    return tmp;
}
template <typename T>
DynamicArray <T> DynamicArray<T>::operator--(int)
{
    DynamicArray<T> tmp(*this); // copy
    operator--();
    return tmp;
}
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator/=(T x)
{
    for (int i =0;i<this->current_idx;++i)
    {
        this->ar[i]/=x;
    }
    return *this;
}
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator+=(T x)
{
    for (int i = 0;i<this->current_idx;++i)
    {
        this->ar[i]+=x;
    }
    return *this;
}
template <typename T>
DynamicArray <T> & DynamicArray<T>::operator+=(const DynamicArray<T>& x)
{
    if(this->current_idx != x.current_idx)
        return *this;
    for (int i=0;i < this->current_idx;++i)
    {
        this->ar[i]+=x[i];
    }
    return *this;
}
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator-=(T x)
{
    for (int i =0;i<this->current_idx;++i)
    {
        this->ar[i]-=x;
    }
    return *this;
}
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator*=(T x)
{
    for (int i =0;i<this->current_idx;++i)
    {
        this->ar[i]*=x;
    }
    return *this;
}
template <typename T>
DynamicArray <T> & DynamicArray <T>::operator-=(const DynamicArray <T> & x)
{
    if(this->current_idx != x.current_idx)
        return *this;
    for (int i=0;i < this->current_idx;++i)
    {
        this->ar[i]-=x[i];
    }
    return *this;
}
template <typename T>
DynamicArray <T> & DynamicArray <T> ::operator/=(const DynamicArray <T> & x)
{
    if(this->current_idx != x.current_idx)
        return *this;
    for (int i=0;i < this->current_idx;++i)
    {
        this->ar[i]/=x[i];
    }
    return *this;
}
template <typename T>
DynamicArray <T> & DynamicArray<T> ::operator*=(const DynamicArray<T> & x)
{
    if(this->current_idx != x.current_idx)
        return *this;
    for (int i=0;i < this->current_idx;++i)
    {
        this->ar[i]*=x.ar[i];
    }
    return *this;
}
template <typename T>
void* DynamicArray<T>::operator new[](size_t size)
{
    DynamicArray<T>* ptr = (DynamicArray<T>*)malloc(size);
    if (ptr)
    {
        std::cout << size << " Memmory allocated\n";
    }
    else
    {
        std::cout << "Error memory allocation\n";
    }
    return ptr;
}
template <typename T>
void DynamicArray<T>::operator delete[](void* ptr)
{
    free(ptr);
    std::cout << "Memory delete\n";
}
        
        
template class DynamicArray<int>;
template class DynamicArray<double>;
template class DynamicArray<float>;
template class DynamicArray<char>;
        
bool IsArraysEqual(const DynamicArray<int>& one, const DynamicArray<int>& two);
bool IsArraysEqual(const DynamicArray<double>& one, const DynamicArray<double>& two);
bool IsArraysEqual(const DynamicArray<float>& one, const DynamicArray<float>& two);
bool IsArraysEqual(const DynamicArray<char>& one, const DynamicArray<char>& two);
        
template bool operator==(const DynamicArray<int>& l,const DynamicArray<int>& r);
template bool operator==(const DynamicArray<char>& l,const DynamicArray <char>& r);
template bool operator==(const DynamicArray<double>& l,const DynamicArray <double>& r);
template bool operator==(const DynamicArray<float>& l,const DynamicArray <float>& r);

template DynamicArray <int> operator+(const DynamicArray<int>& l, const DynamicArray<int>& r);
template DynamicArray <char> operator+(const DynamicArray<char>& l, const DynamicArray<char>& r);
template DynamicArray <float> operator+(const DynamicArray<float>& l, const DynamicArray<float>& r);
template DynamicArray <double> operator+(const DynamicArray<double>& l, const DynamicArray<double>& r);
template DynamicArray <size_t> operator+(const DynamicArray<size_t>& l, const DynamicArray<size_t>& r);

template DynamicArray <int> operator+(const DynamicArray <int>& l,int x);
template DynamicArray <char> operator+(const DynamicArray <char>& l,char x);
template DynamicArray <double> operator+(const DynamicArray <double>& l,double x);
template DynamicArray <float> operator+(const DynamicArray <float>& l,float x);

template DynamicArray <int> operator-(const DynamicArray <int> & l,const DynamicArray <int>& r);
template DynamicArray <char> operator-(const DynamicArray <char> & l,const DynamicArray <char>& r);
template DynamicArray <float> operator-(const DynamicArray <float> & l,const DynamicArray <float>& r);
template DynamicArray <double> operator-(const DynamicArray <double> & l,const DynamicArray <double>& r);
        
template DynamicArray <int> operator-(const DynamicArray <int>& l,int x);
template DynamicArray <char> operator-(const DynamicArray <char>& l,char x);
template DynamicArray <double> operator-(const DynamicArray <double>& l,double x);
template DynamicArray <float> operator-(const DynamicArray <float>& l,float x);
        
template DynamicArray <int> operator/(const DynamicArray <int> & l,const DynamicArray <int> & r);
template DynamicArray <char> operator/(const DynamicArray <char> & l,const DynamicArray <char> & r);
template DynamicArray <float> operator/(const DynamicArray <float> & l,const DynamicArray <float> & r);
template DynamicArray <double> operator/(const DynamicArray <double> & l,const DynamicArray <double> & r);
        
template DynamicArray <int> operator/(const DynamicArray <int> & l,int x);
template DynamicArray <double> operator/(const DynamicArray <double> & l,double x);
template DynamicArray <float> operator/(const DynamicArray <float> & l,float x);
template DynamicArray <char> operator/(const DynamicArray <char> & l,char x);

        
template DynamicArray <int> operator*(const DynamicArray<int>& l,int x);
template DynamicArray <char> operator*(const DynamicArray<char>& l,char x);
template DynamicArray <double> operator*(const DynamicArray<double>& l,double x);
template DynamicArray <float> operator*(const DynamicArray<float>& l,float x);
        
template DynamicArray <int> operator*(const DynamicArray <int> & l,const DynamicArray <int> & r);
template DynamicArray <char> operator*(const DynamicArray <char> & l,const DynamicArray <char> & r);
template DynamicArray <double> operator*(const DynamicArray <double> & l,const DynamicArray <double> & r);
template DynamicArray <float> operator*(const DynamicArray <float> & l,const DynamicArray <float> & r);
        
template int & DynamicArray <int>::operator[](int idx);
template const int & DynamicArray<int>::operator[](int idx) const;
        
template DynamicArray<int> & DynamicArray<int>::operator++();
template DynamicArray<char> & DynamicArray<char>::operator++();
template DynamicArray<double> & DynamicArray<double>::operator++();
template DynamicArray<float> & DynamicArray<float>::operator++();
        
template DynamicArray<int> & DynamicArray<int>::operator--();
template DynamicArray<char> & DynamicArray<char>::operator--();
template DynamicArray<double> & DynamicArray<double>::operator--();
template DynamicArray<float> & DynamicArray<float>::operator--();
        
template DynamicArray<int> DynamicArray<int>::operator++(int);
template DynamicArray <int> DynamicArray<int>::operator--(int);
      
template DynamicArray<int>& DynamicArray<int>::operator/=(int x);
template DynamicArray<char>& DynamicArray<char>::operator/=(char x);
template DynamicArray<double>& DynamicArray<double>::operator/=(double x);
template DynamicArray<float>& DynamicArray<float>::operator/=(float x);
        
template DynamicArray<int>& DynamicArray<int>::operator+=(int x);
template DynamicArray<char>& DynamicArray<char>::operator+=(char x);
template DynamicArray<double>& DynamicArray<double>::operator+=(double x);
template DynamicArray<float>& DynamicArray<float>::operator+=(float x);
        
template DynamicArray <int> & DynamicArray<int>::operator+=(const DynamicArray<int>& x);
template DynamicArray <char> & DynamicArray<char>::operator+=(const DynamicArray<char>& x);
template DynamicArray <double> & DynamicArray<double>::operator+=(const DynamicArray<double>& x);
template DynamicArray <float> & DynamicArray<float>::operator+=(const DynamicArray<float>& x);
        
template  DynamicArray<int>& DynamicArray<int>::operator-=(int x);
template  DynamicArray<char>& DynamicArray<char>::operator-=(char x);
template  DynamicArray<float>& DynamicArray<float>::operator-=(float x);
template  DynamicArray<double>& DynamicArray<double>::operator-=(double x);

template DynamicArray<int>& DynamicArray<int>::operator*=(int x);
template DynamicArray<char>& DynamicArray<char>::operator*=(char x);
template DynamicArray<double>& DynamicArray<double>::operator*=(double x);
template DynamicArray<float>& DynamicArray<float>::operator*=(float x);
        
template DynamicArray <int> & DynamicArray <int>::operator-=(const DynamicArray <int> & x);
template DynamicArray <char> & DynamicArray <char>::operator-=(const DynamicArray <char> & x);
template DynamicArray <double> & DynamicArray <double>::operator-=(const DynamicArray <double> & x);
template DynamicArray <float> & DynamicArray <float>::operator-=(const DynamicArray <float> & x);
        
template DynamicArray <int> & DynamicArray <int> ::operator/=(const DynamicArray <int> & x);
template DynamicArray <double> & DynamicArray <double> ::operator/=(const DynamicArray <double> & x);
template DynamicArray <float> & DynamicArray <float> ::operator/=(const DynamicArray <float> & x);
template DynamicArray <char> & DynamicArray <char> ::operator/=(const DynamicArray <char> & x);
        
template DynamicArray <int> & DynamicArray<int> ::operator*=(const DynamicArray<int> & x);
template DynamicArray <char> & DynamicArray<char> ::operator*=(const DynamicArray<char> & x);
template DynamicArray <double> & DynamicArray<double> ::operator*=(const DynamicArray<double> & x);
template DynamicArray <float> & DynamicArray<float> ::operator*=(const DynamicArray<float> & x);
        
template void* DynamicArray<int>::operator new[](size_t size);
template void* DynamicArray<double>::operator new[](size_t size);
template void* DynamicArray<float>::operator new[](size_t size);
template void* DynamicArray<char>::operator new[](size_t size);

template void DynamicArray<int>::operator delete[](void* ptr);
template void DynamicArray<double>::operator delete[](void* ptr);
template void DynamicArray<float>::operator delete[](void* ptr);
template void DynamicArray<char>::operator delete[](void* ptr);
        
        
        
        
        
