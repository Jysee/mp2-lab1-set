// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


TBitField::TBitField(int len)
{
	if (len <= 0)
	{
		throw exception("Creating BitField with negative or zero lenght");
	}
	this->BitLen = len;
	this->MemLen = (len / (sizeof(TELEM) * 8));
	if (this->MemLen * sizeof(TELEM) * 8 < len)
	{
		MemLen++;
	}
	this->pMem = new TELEM[MemLen]();
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = new TELEM[MemLen];
	copy(bf.pMem, bf.pMem + MemLen, this->pMem);
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return (TELEM)1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen)
	{
		throw "wrong number";
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)
	{
		throw "wrong number";
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen)
	{
		throw "wrong number";
	}
	TELEM data = pMem[GetMemIndex(n)];
	data &= GetMemMask(n);
	if (data != 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (this == &bf)
	{
		return *this;
	}
	TELEM* data = new TELEM[bf.MemLen];
	copy(bf.pMem, bf.pMem + bf.MemLen, data);
	delete[] pMem;
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	pMem = data;
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return 0;
	}
	else
	{
		for (size_t i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				return 0;
			}
		}
		return 1;
	}
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (*this == bf)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	TBitField data(*this);
	if (this->BitLen < bf.BitLen)
	{
		data = bf;
	}
	for (size_t i = 0; i < min(MemLen, bf.MemLen); i++)
	{
		data.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return data;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField data(*this);
	if (this->BitLen < bf.BitLen)
	{
		data = bf;
	}
	for (size_t i = 0; i < min(MemLen, bf.MemLen); i++)
	{
		data.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return data;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField data(BitLen);
	for (size_t i = 0; i < MemLen; i++)
	{
		data.pMem[i] = ~this->pMem[i];
	}
	if (MemLen * sizeof(TELEM) * 8 != BitLen)
	{
		data.pMem[MemLen - 1] &= ~((~(TELEM)0) << (this->BitLen % (sizeof(TELEM) * 8)));
	}
	cout << data;
	return data;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	TELEM elem;
	for (size_t i = 0; i < bf.BitLen; i++)
	{
		istr >> elem;
		if (elem == (TELEM)1)
		{
			bf.SetBit(i);
		}
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (size_t i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}