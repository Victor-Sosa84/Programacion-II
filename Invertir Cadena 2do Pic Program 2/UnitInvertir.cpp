//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitInvertir.h"
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

//FUNCIONES

AnsiString Inverso(AnsiString x) //Eliminar el primero
{ AnsiString y;
  if (x=="") {
	  y="";
  } else {
	char z=x[1];
	x.Delete(1,1);
	y=Inverso(x);
	y=y+z;
  }
  return y;
}

AnsiString Inverso2(AnsiString x)  //Eliminar el ultimo
{ AnsiString y;
  if (x=="") {
	  y="";
  } else {
	char z=x[x.Length()];
	AnsiString aux=z;
	x.Delete(x.Length(),1);
	y=Inverso2(x);
	y=aux+y;
  }
  return y;
}

//PROCESOS

void Invertir3(AnsiString &x) //Eliminar los 2 primeros
{
  if (x.Length()>1) {
	AnsiString y=x.SubString(1,2);
	x.Delete(1,2);
	Invertir3(x);
	x=x+y[2]+y[1];
  }

  /*
  if (x.Length()<2) {

  } else {
	AnsiString y=x.SubString(1,2);
	x.Delete(1,2);
	Invertir3(x);
	x=x+y[2]+y[1];
  }
  */
}

void Invertir4(AnsiString &x) //Eliminar los 2 últimos
{
	byte n=x.Length();
	if (n>1) {
		AnsiString y=x.SubString(n-1,2);
		x.Delete(n-1,2);
		Invertir4(x);
		AnsiString aux="";
		aux=aux+y[2]+y[1];
		x=aux+x;
	}
}

void Invertir5(AnsiString &x) //Eliminar el primero y el último
{
  byte n=x.Length();
  if (n>1) {
	AnsiString y=x[1];
	AnsiString z=x[n];
	x=x.SubString(2,n-2);
	Invertir5(x);
	AnsiString aux=z;
	x=z+x+y;
  }
}

void Invertir6(AnsiString &x)
{
   byte n=x.Length();
   if (n>1) {
	   AnsiString y=x.SubString(1,n/2);
	   x.Delete(1,n/2);
	   Invertir6(x);
	   Invertir6(y);
	   x=x+y;
   }
}

void Invertir7(AnsiString &x)
{
	byte n=x.Length();
	if (n>1) {
	   AnsiString y=x.SubString(1,(n+1)/2);
	   x.Delete(1,(n+1)/2);
	   Invertir7(x);
	   Invertir7(y);
	   x=x+y;
	}
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   //Llamada para el proceso
   AnsiString x;
   x=Edit1->Text;
   Invertir7(x);
   Label1->Caption=x;


   //Llamada para la función
   //Label1->Caption=Inverso2(Edit1->Text);
}
//---------------------------------------------------------------------------
