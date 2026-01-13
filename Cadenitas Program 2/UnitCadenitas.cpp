//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitCadenitas.h"
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
bool EsDigit(char c)
{
  return c>='0' && c<='9';
}

bool VerificarDigito(AnsiString x)
{ bool b = false;
  byte n = x.Length();
  if (n>0) { //caso general
	char z = x[n];
	x.Delete(n,1);
	b = EsDigit(z)? true : VerificarDigito(x);
  }
  return b;
}

int UltNum(AnsiString x)
{ int r; byte n = x.Length();
  //x = cadena, r = resultado, n = cant. caracteres

  if (n==0) //1er caso base
	r = 0;
  else if (n==1) //2do caso base
		 r = EsDigit(x[1])? StrToInt(x):0;
  else if ( !EsDigit(x[n-1]) && EsDigit(x[n]) ) //3er caso base si encontrando el ultimo digito del ultimo numero
		  r = StrToInt(x[n]);
  else {
	/* if (VerificarDigito(x.SubString(n/2,n/2)))
	   r = UltNum(x.SubString(n/2,n/2));
	else if (VerificarDigito(x.SubString(0,n/2-1)))
	   r = UltNum(x.SubString(0,n/2-1));
	else
	  r = 0; */

	char z = x[n];
	x.Delete(n,1);
	r = UltNum(x);
	r = EsDigit(z)? r*10+StrToInt(z) : r;
  }
  return r;
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  Edit2->Text = UltNum(Edit1->Text);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
   Edit2->Text = VerificarDigito(Edit1->Text)? "HAY DIGITOS" : "NO HAY DIGITOS";
}
//---------------------------------------------------------------------------
bool EsLetra(char c)
{ AnsiString let="qwertyuiopasdfghjklzxcvbnmñáéíóúQWERTYUIOPASDFGHJKLZXCVBNMÑÁÉÍÓÚ";
  return let.Pos(c)>0;
}

AnsiString PrimerPal(AnsiString x)
{ AnsiString y; Word n=x.Length();
  if (n<2) //casos bases, n=0 y n=1
	y = x==""? "" : ( EsLetra(x[1])? x:"");
  else { //caso general
	char z=x[1];
	x.Delete(1,1);
	y=PrimerPal(x);
	if (EsLetra(z))
	  y=EsLetra(x[1])? AnsiString(z)+y : z;
  }
  return y;
}

void ElimPrimerPal(AnsiString &x)
{ byte n = x.Length();
  if (n<2) //casos bases, n=0 y n=1
	x = n==0? "" : ( EsLetra(x[1])? "":x);
  else {
	char z = x[1];
	AnsiString aux = z;
	x.Delete(1,1);
	if (!(EsLetra(z) && !EsLetra(x[1]))) { //3er caso base
	  ElimPrimerPal(x);
	  if (!EsLetra(z))
		 x = aux + x;
	}
  }
}

AnsiString UltPal(AnsiString x)
{ AnsiString y; byte n=x.Length();
  if (n<2)
	y = n==0? "" : (EsLetra(x[1])? x : "");
  else {
	char z=x[n];
	x.Delete(n,1);
	y = UltPal(x);
	if (EsLetra(z))
	  y=EsLetra(x[n-1])? y+z : z;
  }
  return y;
}


//No funca xd
AnsiString CadenaMasLarga(AnsiString x)
{ AnsiString y; byte n=x.Length(); AnsiString ult= UltPal(x);
  if (n<2)
	y=x;
  else if (ult.Length() == x.Length())
		 y = x;
  else {
	AnsiString prueba = x;
	AnsiString aux = PrimerPal(prueba);
	ElimPrimerPal(prueba);
	y = CadenaMasLarga(prueba);
	if (y.Length()<aux.Length())
	  y = aux;
  }
  return y;
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
  Edit2->Text = CadenaMasLarga(Edit1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button5Click(TObject *Sender)
{
   Edit2->Text = PrimerPal(Edit1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
   AnsiString x = Edit1->Text;
   ElimPrimerPal(x);
   Edit2->Text = x ;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button6Click(TObject *Sender)
{
   Edit2->Text = UltPal(Edit1->Text);
}
//---------------------------------------------------------------------------

