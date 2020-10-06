// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "bitfield.h"

TBitField::TBitField(int len)
{
 if (len > 0)
 {
  BitLen = len;
  MemLen = ceil((double)BitLen / 8 * sizeof(TELEM));
  pMem = nullptr;
  pMem = new TELEM[MemLen];
  if (pMem != nullptr)
   for (int i = 0; i < MemLen; i++)
    pMem[i] = 0;
  else
   throw - 1;
 }
 else
  throw - 1;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
 BitLen = bf.BitLen;
 MemLen = bf.MemLen;
 pMem = nullptr;
 pMem = new TELEM[MemLen];
 if (pMem != nullptr)
  for (int i = 0; i < MemLen; i++)
   pMem[i] = bf.pMem[i];
 else
  throw - 1;
}

TBitField::~TBitField()
{
 if (pMem == NULL || MemLen == NULL || Bitlen == NULL)
 {
  throuw("NULL_REFERENCE_EXEPTION");
 }
 delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
 if (n >= 0 && n < BitLen)
  return n / (sizeof(TELEM) * 8);
 else
  throw - 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
 if (n >= 0 && n < BitLen)
 {
  int tempBN = n % (8 * sizeof(TELEM));
  TELEM mask = 1 << tempBN;
  return mask;
 }
 else
  throw - 1;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
 return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
 if (n >= 0 && n < BitLen)
 {
  pMem[GetMemIndex(n)] |= GetMemMask(n);
 }
 else
  throw - 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
 if (n >= 0 && n < BitLen)
 {
  pMem[GetMemIndex(n)] &= ~GetMemMask(n);
 }
 else
  throw - 1;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
 if (n >= 0 && n < BitLen)
 {
  TELEM elem = GetMemIndex(n);
  TELEM mask = GetMemMask(n);
  return ((bool)(pMem[elem] & mask));
 }
 else
  throw - 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
 if (this != &bf)
 {
  BitLen = bf.BitLen;
  MemLen = bf.MemLen;
  delete[] pMem;
  pMem = new TELEM[MemLen];
  for (int i = 0; i < MemLen; i++)
   pMem[i] = bf.pMem[i];
 }
 return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
 bool res = 1;
 if (BitLen != bf.BitLen)
  res = 0;
 else
  for (int i = 0; i < MemLen; i++)
   if (pMem[i] != bf.pMem[i])
   {
    res = 0;
    break;
   }
 return res;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
 bool res = 1;
 if (BitLen == bf.BitLen)
  for (int i = 0; i < MemLen; i++)
   if (pMem[i] == bf.pMem[i])
    res = 0;
   else
   {
    res = 1;
    break;
   }
 return res;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
 int templen = BitLen;
 if (bf.BitLen > templen)
  templen = bf.BitLen;
 TBitField temp(templen);
 for (int i = 0; i < MemLen; i++)
  temp.pMem[i] = pMem[i];
 for (int i = 0; i < bf.MemLen; i++)
  temp.pMem[i] |= bf.pMem[i];
 return temp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
 int templen = BitLen;
 if (bf.BitLen > templen)
  templen = bf.BitLen;
 TBitField temp(templen);
 for (int i = 0; i < MemLen; i++)
  temp.pMem[i] = pMem[i];
 for (int i = 0; i < bf.MemLen; i++)
  temp.pMem[i] &= bf.pMem[i];
 return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
 int templen = BitLen;
 TBitField temp(templen);
 for (int i = 0; i < templen; i++)
  if (this->GetBit(i) == 0)
   temp.SetBit(i);
  else
   temp.ClrBit(i);
 return temp;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
 int k;
 cin >> k;
 while (k > -1)
 {
  bf.SetBit(k);
  cin >> k;
 }

 return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
 cout << "{";
 for (int k = 0; k < bf.BitLen; k++)
  cout << bf.GetBit(k);
 cout << "}" << endl;
 return ostr;
}