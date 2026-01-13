//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <cmath>

#include "UnitPruebas.h"
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
bool Capicua(Cardinal x)
{ bool es;
  if (x<10)  //caso base n=1
	es=true;
  else { //caso general
	 byte ult = x % 10;
	byte prim = x/ ( pow(10,(log10(x)+1)-1) ) ;
	x = x % Cardinal( pow(10,(log10(x)+1)-1) ) / 10;
	es = Capicua(x) && (ult==prim);

    //no salio xd
	//es = Capicua( x % Cardinal( pow(10,(log10(x)+1)-1) ) / 10 ) && ((x % 10) == (x/ ( pow(10,(log10(x)+1)-1) )) );
  }
  return es;
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  //version clasica
  /* if (Capicua(StrToInt(Edit1->Text)))
	Edit2->Text="ES CAPICUA";
  else
	Edit2->Text="NO ES CAPICUA"; */

  //version pro xdd
  Edit2->Text = Capicua(StrToInt(Edit1->Text)) ? "ES CAPICUA" : "NO ES CAPICUA";
}
//---------------------------------------------------------------------------
Cardinal Factorial(byte x)
{
  //version clasica
  /* Cardinal y;
  if (x<3) { //casos bases n=0, n=1, n=2
	if (x==0)
	  y=1;
	else
	  y=x;
  } else {
	y=x*Factorial(x-1);
  }
  return y; */

  //version pro xdd
  return x<3? (x==0? 1 : x) : x*Factorial(x-1);
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  Edit2->Text=Factorial(StrToInt(Edit1->Text));
}
//---------------------------------------------------------------------------

