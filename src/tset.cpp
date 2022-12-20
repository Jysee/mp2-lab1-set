// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    this->MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{
    this->MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf)
{
    this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return TBitField(this->BitField);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (BitField.GetBit(Elem))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    if (this == &s)
    {
        return *this;
    }
    this->BitField = s.BitField;
    this->MaxPower = s.MaxPower;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    if ((this->MaxPower == s.MaxPower) && (this->BitField == s.BitField))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    if ((this->MaxPower == s.MaxPower) && (this->BitField == s.BitField))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

TSet TSet::operator+(const TSet& s) // объединение
{
    size_t size = this->MaxPower;
    if (this->MaxPower < s.MaxPower)
    {
        size = s.MaxPower;
    }
    TSet result(size);
    result.BitField = this->BitField | s.BitField;
    return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet result(*this);
    result.BitField.SetBit(Elem);
    return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet result(*this);
    result.BitField.ClrBit(Elem);
    return result;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    size_t size = this->MaxPower;
    if (this->MaxPower < s.MaxPower)
    {
        size = s.MaxPower;
    }
    TSet result(size);
    result.BitField = this->BitField & s.BitField;
    return result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet result(this->MaxPower);
    result.BitField = ~this->BitField;
    return result;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    char sym = ' ';
    size_t tmp;
    while (sym != '.')
    {
        istr >> tmp >> sym;
        if (tmp < s.MaxPower && tmp >= 0)
            s.InsElem(tmp);
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    for (size_t i = 0; i < s.GetMaxPower(); i++)
    {
        if (s.IsMember(i))
            ostr << "Index:" << i << endl;
    }
    return ostr;
}