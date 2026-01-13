//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitEjercicios.h"
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
char Mayus(char c)
{ AnsiString min="qwertyuiopasdfghjklzxcvbnmñáéíúó";
  AnsiString may="QWERTYUIOPASDFGHJKLZXCVBNMÑÁÉÍÓÚ";
  byte p=min.Pos(c);
  if (p>0)
	c=may[p];
  return c;
}

bool EsPalindrome(AnsiString x)
{ bool es; Word n=x.Length();
  if (n<2) //caso base n<2
	es=true;
  else { //caso general
	char z1=x[1];
	char z2=x[n];
	x.Delete(n,1);
	x.Delete(1,1);
	es = EsPalindrome(x);
	if (Mayus(z1)==Mayus(z2) && EsPalindrome(x))
	  es=true;
	else es=false;
  }
  return es;
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  if (EsPalindrome(Edit1->Text))
	Edit2->Text="ES PALINDROMO";
  else
	Edit2->Text="NO ES PALINDROMO";
}
//---------------------------------------------------------------------------
Cardinal StrToNum2(AnsiString x) //eliminar los 2 primeros (cuidado con numeros grandes)
{ Cardinal y; Word n=x.Length();
  if (n<2) //casos bases, n=0 y n=1
	if (n==0)
	  y=0;
	else if (isdigit(x[1]))
		   y=x[1]-48;
		 else
		   y=0;
  else { //caso general
	char z1=x[1];
	char z2=x[2];
	x.Delete(1,2);
	y=StrToNum2(x);

	Cardinal lon;
	if (y==0)
	  lon=0;
	else
	  lon=log10(y)+1;

	bool z22=isdigit(z2);
	bool z11=isdigit(z1);

	Cardinal pot=pow(10,lon);

	if (z22)
	  y=(z2-48)*pot+y;
	if (z11 && z22)
	  y=(z1-48)*(pot*10)+y;
	else if (z11 && !z22)
			y=(z1-48)*pot+y;
  }
  return y;
}

Cardinal StrToNum(AnsiString x)
{ Cardinal y; Word n=x.Length();
  if (x=="") //caso base
	y=0;
  else { //caso general
	char z=x[n];
	x.Delete(n,1);
	y=StrToNum(x);
	if (isdigit(z))
	  y=y*10+(z-48);
  }
  return y;
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  Edit2->Text=StrToNum(Edit1->Text);
}
//---------------------------------------------------------------------------
bool EsLetra(char c)
{
  AnsiString let="qwertyuiopasdfghjklzxcvbnmñáéíóúQWERTYUIOPASDFGHJKLZXCVBNMÑÁÉÍÓÚ";
  return let.Pos(c)>0;

}

AnsiString PrimerPal(AnsiString x)
{ AnsiString y; Word n=x.Length();
  if (n<2) //casos bases, n=0 y n=1
	if (x=="")
		y="";
	else y= EsLetra(x[1])? x: "";

         //version anterior
		 /*if (EsLetra(x[1]))
		   y=x;
		 else
		   y=""; */
  else { //caso general
	char z=x[1];
	x.Delete(1,1);
	y=PrimerPal(x);
	if (EsLetra(z))
	  y = EsLetra(x[1])? AnsiString(z)+y : z;

	  //version anterior
	  /*if (EsLetra(x[1]))
		y=AnsiString(z)+y;
	  else
		y=z; */
  }
  return y;
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
   Edit2->Text=PrimerPal(Edit1->Text);
}
//---------------------------------------------------------------------------
