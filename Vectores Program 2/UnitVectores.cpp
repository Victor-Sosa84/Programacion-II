//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitVectores.h"
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
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	StringGrid1->ColCount =StrToInt(Edit1->Text); //Dimensionar
}
//---------------------------------------------------------------------------
void CargarRandom(TStringGrid *v, byte n)  //*v es un puntero
{ if (n==0) //caso base
	  v->ColCount=0;
  else { //caso general
	CargarRandom(v,n-1);
	v->Cells[n-1][0]=Random(10);
	v->ColCount=n;
  }
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	CargarRandom(StringGrid1, StrToInt(Edit1->Text));
}
//---------------------------------------------------------------------------
int Suma(TStringGrid *v, byte n)  //menos el último
{ int s;
  if (n==0) //caso base
	s=0;
  else { //caso general
	s=Suma(v,n-1);
	s=s+StrToInt(v->Cells[n-1][0]);
  }
  return s;
}

int Suma2(TStringGrid *v, byte n)  //menos los 2 últimos
{ int s;
  if (n<2) {//caso base
	if (n==0)
	  s=0;
	else
	  s=StrToInt(v->Cells[n-1][0]);
  }else { //caso general
	s=Suma(v,n-2);
	s=s+StrToInt(v->Cells[n-2][0])+StrToInt(v->Cells[n-1][0]);
  }
  return s;
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
   Edit2->Text=Suma(StringGrid1, StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void Invertir(TStringGrid *v, byte a, byte b)
{ byte n=b-a+1;
  if (n>1) {
	String aux = v->Cells[a][0];
	v->Cells[a][0]=v->Cells[b][0];
	v->Cells[b][0]=aux;
	Invertir(v,a+1,b-1);
  }
}

void __fastcall TForm1::Button4Click(TObject *Sender)
{
  Invertir(StringGrid1, 0, StringGrid1->ColCount-1);
}
//---------------------------------------------------------------------------
bool BusBin(TStringGrid *v, int x, byte a, byte b)
{ bool esta; byte n=b-a+1;
  if (n==0) //1 caso base
	esta = false;
  else if (n==1) //2 caso base
		  esta = x==v->Cells[a][0];
  else { //caso general
	byte c=(a+b)/2;
	if (x==v->Cells[c][0])
	  esta = true;
	else if (x<v->Cells[c][0])
			esta = BusBin(v,x,a,c-1);
		 else
			esta = BusBin(v,x,c+1,b);
  }
  return esta;
}

void __fastcall TForm1::Button5Click(TObject *Sender)
{
   if (BusBin(StringGrid1, StrToInt(Edit1->Text) , 0, StringGrid1->ColCount-1))
	 Edit2->Text= "EL DATO ESTA";
   else
	 Edit2->Text="EL DATO NO ESTA";
}
//---------------------------------------------------------------------------
byte PosMayor(TStringGrid *v,byte n)
{ byte p;
  if (n==0) //precondicion
	throw new Exception("Error: Vector Vacío");
  else if (n==1)
		 p=0;
  else {
	p = PosMayor(v,n-1);
	if ( StrToInt(v->Cells[p][0]) < StrToInt(v->Cells[n-1][0]) )
	  p = n-1 ;
  }
  return p;
}

void __fastcall TForm1::Button6Click(TObject *Sender)
{
  Edit2->Text= PosMayor(StringGrid1, StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void MayorAlFinal(TStringGrid *v, byte n)
{ //caso base n=0 no se hace nada
  if (n>1) { //caso general
	MayorAlFinal(v,n-1);
	if (StrToInt(v->Cells[n-2][0])>StrToInt(v->Cells[n-1][0])) {
	  String aux = v->Cells[n-2][0];
	  v->Cells[n-2][0] = v->Cells[n-1][0];
	  v->Cells[n-1][0] = aux;
	}
  }
}

void __fastcall TForm1::Button7Click(TObject *Sender)
{
   MayorAlFinal(StringGrid1, StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void BubbleSort(TStringGrid *v, byte n)
{
  if (n==0) //pre condicion
	throw new Exception("Error: Vector vacío");
  else if (n>1) { //caso general, caso base n=1 no se hace nada
	byte p = PosMayor(v, n);
	if (p != n-1) {
	  String aux = v->Cells[p][0];
	  v->Cells[p][0] = v->Cells[n-1][0];
	  v->Cells[n-1][0] = aux;
	}
	BubbleSort(v, n-1);
  }
}

void __fastcall TForm1::Button8Click(TObject *Sender)
{
  BubbleSort(StringGrid1, StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void SelectionSort(TStringGrid *v, byte n)
{
  if (n==0) //pre condicion
	throw new Exception("Error: Vector vacío");
  else if (n>1) { //caso general, caso base n=1 no se hace nada
	MayorAlFinal(v,n);
	SelectionSort(v,n-1);
  }
}

void __fastcall TForm1::Button9Click(TObject *Sender)
{
   SelectionSort(StringGrid1, StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void Cargar1234(TStringGrid *v, byte n)
{ //v = vector, n = cant. datos
  if (n>0) {
	Cargar1234(v, n-1);
	v->Cells[n-1][0] = n%4==1? 1 : (n%4==2? 2 : (n%4==3? 3 : 4) ) ;
  }
}

void __fastcall TForm1::Button10Click(TObject *Sender)
{
   StringGrid1->ColCount = StrToInt(Edit1->Text);
   Cargar1234(StringGrid1, StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
AnsiString CargarACadena(TStringGrid *v, byte n)
{
  //Version pro xdd
  return n==0? "" : ( n==1? v->Cells[0][0] : v->Cells[n-1][0] + "," + CargarACadena(v, n-1) );

  //Version Clasica
 /*  AnsiString x; if (n==0)
	x = "";
  else if (n==1)
		  x = v->Cells[0][0];
  else {
	x = v->Cells[n-1][0] + "," + CargarACadena(v, n-1);
  }
  return x; */
}

void __fastcall TForm1::Button11Click(TObject *Sender)
{
  Edit1->Text = CargarACadena(StringGrid1, StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
bool Palindromo(TStringGrid *v, byte a, byte b)
{ bool es; byte n =  b-a+1;
  if (n==0)
	es = false;
  else if (n==1)
		  es = true;
  else {
	es = Palindromo(v,a+1,b-1) && v->Cells[a][0]==v->Cells[b][0];
  }
  return es;
}
void __fastcall TForm1::Button12Click(TObject *Sender)
{
  Edit2->Text = Palindromo(StringGrid1, 0 , StringGrid1->ColCount-1)? "ES PALINDROMO" : "NO ES PALINDROMO" ;
}
//---------------------------------------------------------------------------

