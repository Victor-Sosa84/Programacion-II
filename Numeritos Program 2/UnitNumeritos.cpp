//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitNumeritos.h"
#include <cmath>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void ElimDigImp(Cardinal &x)
{ if (x<10) {
	if (x%2==1)
	  x=0;
  }
  else {
	Byte y=x%10;
	x=x/10;
	ElimDigImp(x);
	if (y%2==0)
	  x=x*10+y;
  }
}


void __fastcall TForm1::Button1Click(TObject *Sender)
{ Cardinal x;
  x=StrToInt(Edit1->Text);
  ElimDigImp(x);
  Label1->Caption = x;

}
//---------------------------------------------------------------------------
void DigMayMen(Cardinal x, byte &M, byte&m)
{
  if (x<10) {
	m=x;
	M=x;
  }
  else {
	byte y=x%10;
	DigMayMen(x/10,M,m);
	if (y<m) {
	  m=y;
	} else {
	  if (y>M)
		M=y;
	}
  }
}


void __fastcall TForm1::Button2Click(TObject *Sender)
{ byte a,b;
  DigMayMen(StrToInt(Edit1->Text),a,b);
  Label1->Caption = a;
  Label2->Caption = b;
}
//---------------------------------------------------------------------------
byte Mayor(Word x)
{  byte may;
   // x = numero , var. de recursion = cant. digitos, may = almacena el mayor
   if (x<10) //caso base 1 digito
	  may = x;
   else { //caso general
	   may = Mayor(x / 10);
	   if ( x % 10 > may )
		   may = x %10;
	   x = x / 10;
   }
   return may;
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
  Label1->Caption = Mayor(StrToInt(Edit1->Text));
}
//---------------------------------------------------------------------------
void MoverMayor(Cardinal &x)
{ byte n=log10(x)+1;
  if (n>1) { //caso general
	Cardinal y = x / 10;
	MoverMayor(y);
	x = y *10 + x%10;
	if (y%10>x%10) {
	  byte ult=x%10; byte penult= x/10%10;
	  x= x / 100;
	  x= (x*10+ult) * 10 + penult;
	}
  }
}

void __fastcall TForm1::Button4Click(TObject *Sender)
{
   Cardinal x;
   x =StrToInt(Edit1->Text);
   MoverMayor(x);
   Label1->Caption = x;
}
//---------------------------------------------------------------------------
byte CantDigPares(Cardinal x)
{ byte c;
  if (x<10)
	c=0;
  else {
	c =CantDigPares(x/10);
	c = (x%10)%2==1? (((x/10)%10)%2==0 ? c+1: c) : c;
  }
  return c;
}

void __fastcall TForm1::Button5Click(TObject *Sender)
{
  Label1->Caption = CantDigPares(StrToInt(Edit1->Text));
}
//---------------------------------------------------------------------------

byte CantCerosAlFinal(Cardinal x)
{ byte c = 0;
  if (x<10)
	c = x==0? 1 : 0;
  else {
	if (x%10==0) {
	  c = CantCerosAlFinal(x/10);
	  c = x%10==0? c+1 : c;
	}
  }
  return c;
}

void MayorAlFinal(Cardinal &x)
{
  if (x>9) {
	 byte y = x%10;
	 x = x/10;
	 MayorAlFinal(x);
	 byte z = x%10;
	 if (z>y)
	   x = (x/10*10+y)*10+z;
	 else
	   x = x*10+y;
  }
}

void Ordenar(Cardinal &x)
{
  if (x>10) {
	MayorAlFinal(x);
	byte y = x%10;
	x = x/10;
	Ordenar(x);
	x=x*10+y;
  }
}

void __fastcall TForm1::Button6Click(TObject *Sender)
{
  Cardinal x = StrToInt(Edit1->Text);
  byte c= CantCerosAlFinal(x);
  x = x / pow(10,c);
  byte n1= log10(x)+1;
  Ordenar(x);
  byte n2 = log10(x)+1;
  byte resto = n1-n2;
  AnsiString ceros = pow(10,resto+c) ;
  ceros.Delete(1,1);
  Label1->Caption = ceros + x;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button7Click(TObject *Sender)
{
  Label1->Caption = CantCerosAlFinal(StrToInt(Edit1->Text));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button8Click(TObject *Sender)
{
   Cardinal y = StrToInt(Edit1->Text);
  MayorAlFinal(y);
  Label2->Caption = y;
}
//---------------------------------------------------------------------------

