//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitMatrices.h"
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
void LlenarFila(TStringGrid *A, byte f, byte n)
// A= matriz, f=numero de fila, n = cantidad de datos en la fila
{
  if (n>0) { //caso general, caso base n=0 no se hace nada
	if (n==1)  //2do caso base
	  A->Cells[0][f]=f*A->ColCount + 1;
	else {
	  LlenarFila(A, f, n-1);
	  A->Cells[n-1][f] = StrToInt(A->Cells[n-2][f])+1;
	}
  }

}

void CargarFilas(TStringGrid *A, byte m, byte n)
{ if (m>0) { //caso general, caso base m=0 no se hace nada
	CargarFilas(A,m-1,n);
	LlenarFila(A,m-1,n);
  }

}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  StringGrid1->RowCount=StrToInt(Edit1->Text);
  StringGrid1->ColCount=StrToInt(Edit2->Text);
  CargarFilas(StringGrid1, StringGrid1->RowCount, StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void LlenarColum(TStringGrid *A, byte c, byte n)
{
  if (n>0) {
	if (n==1)
	  A->Cells[c][0]= c* A->RowCount +1;
	else {
	  LlenarColum(A,c,n-1);
	  A->Cells[c][n-1] = StrToInt(A->Cells[c][n-2]) +1;
	}
  }

}

void CargarColumnas(TStringGrid *A, byte m, byte n)
{ if (n>0) { //caso general, caso base n=0 no se hace nada
	CargarColumnas(A,m,n-1);
	LlenarColum(A, n-1, m);
  }

}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  StringGrid1->RowCount = StrToInt(Edit1->Text);
  StringGrid1->ColCount = StrToInt(Edit2->Text);
  CargarColumnas(StringGrid1, StringGrid1->RowCount, StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void LlenarL(TStringGrid *A, byte fc, byte n)
{ //A= matriz , f= fila y columna a llenar , n = cant datos
  if (n>0) { //caso general
	LlenarL(A,fc,n-1);
	A->Cells[n-1][fc] = fc+1;
	A->Cells[fc][n-1] = fc+1;
  }
}

void CargarFyC(TStringGrid *A, byte m)
{ //Pre condicion m=n
  if (m>0) {
	CargarFyC(A, m-1);
	LlenarL(A, m-1, m);
  }

}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
  StringGrid1->RowCount = StrToInt(Edit1->Text);
  StringGrid1->ColCount = StrToInt(Edit1->Text);
  CargarFyC(StringGrid1, StrToInt(Edit1->Text));
}
//---------------------------------------------------------------------------
void LlenarCir(TStringGrid *A, byte fa, byte fb, byte a, byte n, byte z)
{
  if (n>0) { //caso general, caso base n=0 no se hace nada
	LlenarCir(A, fa, fb, a, n-1, z);
	A->Cells[n+a-1][fa] = z;
	A->Cells[fa][n+a-1] = z;
	A->Cells[n+a-1][fb] = z;
	A->Cells[fb][n+a-1] = z;
  }
}

void CargarC(TStringGrid *A, byte fa, byte fb)
{ byte m = fb-fa+1;
  if (m>0) { //1 caso base m=0 no se hace nada
	if (m==1) // 2 caso base m=1 poner solo un uno
	  A->Cells[fa][fa] = 1;
	else { //caso general llenar el circulo
	  CargarC(A,fa+1,fb-1);
	  LlenarCir(A,fa,fb, fa, m,(m+1)/2 );
	}
  }

}

void __fastcall TForm1::Button4Click(TObject *Sender)
{ byte m= StrToInt(Edit1->Text);
  StringGrid1->RowCount = m;
  StringGrid1->ColCount = m;
  CargarC(StringGrid1 ,0 , m-1);
}
//---------------------------------------------------------------------------
void Magico(TStringGrid *A, byte m, byte z,byte &f, byte &c)
{ //Pre condicion m tiene que ser impar y z no puede ser 0
  if ((m%2==0) || (z==0))
	 throw new Exception("Error: No se puede calcular");
  else {
	if (z==1) {//caso base z=1
	  f= 0; c=m/2;
	  A->Cells[c][f]= 1;
	} else { //caso general
	  Magico(A, m, z-1,f,c);
	  if ((z-1)%m==0) //regla 2
		f++;
	  else {//regla 1
		c = (c+1)%m;
		if (f==0)
		  f = m-1;
		else
		  f--;
	  }
	  A->Cells[c][f]=z;
    }
  }

}

void __fastcall TForm1::Button5Click(TObject *Sender)
{  byte f,c ,m= StrToInt(Edit1->Text);
   if (m%2==0)
	  throw new Exception("Error: No existe cuadrado mágico de una matriz cuadrada par");
	  //Otra forma: ShowMessage("Error: No existe cuadrado mágico de una matriz cuadrada par");
   else {
	 StringGrid1->RowCount = m;
	 StringGrid1->ColCount = m;
	 Magico(StringGrid1 , m, m*m,f,c);
   }
}
//---------------------------------------------------------------------------

void Random(TStringGrid *A, byte n)
{ byte N= A->ColCount;
  if (n>0) {
	Random(A, n-1);
	A->Cells[(n-1)%N][(n-1)/N] = Random(10);
  }
}

void __fastcall TForm1::Button6Click(TObject *Sender)
{
  StringGrid1->RowCount = StrToInt(Edit1->Text);
  StringGrid1->ColCount = StrToInt(Edit2->Text);

  Random(StringGrid1 , StringGrid1->RowCount * StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
int Sumar(TStringGrid *A, byte n)
{
  //version clasica
  /* byte s,N= A->ColCount;
  if (n==0)
	s=0;
  else {
	 s= Sumar(A,n-1);
	 s= s + StrToInt(A->Cells[(n-1)%N][(n-1)/N]);
  }
  return s; */


  //version pro xddd
  return n==0? 0 : Sumar(A,n-1) + StrToInt(A->Cells[(n-1)%A->ColCount][(n-1)/A->ColCount]);
}

void __fastcall TForm1::Button7Click(TObject *Sender)
{
   Edit3->Text= Sumar(StringGrid1 , StringGrid1->RowCount * StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
int Mayor(TStringGrid *A, byte n)
{
  //version clasica
  /*int may;
  if (n==0)
	may=0;
  else {
	if (StrToInt(A->Cells[(n-1)%A->ColCount][(n-1)/A->ColCount])>Mayor(A, n-1))
	   may = StrToInt(A->Cells[(n-1)%A->ColCount][(n-1)/A->ColCount]);
  }
  return may; */

  //version pro xddd
  return n==0? 0 : ( StrToInt(A->Cells[(n-1)%A->ColCount][(n-1)/A->ColCount])>Mayor(A, n-1)? StrToInt(A->Cells[(n-1)%A->ColCount][(n-1)/A->ColCount]) : Mayor(A, n-1) );
}

void __fastcall TForm1::Button8Click(TObject *Sender)
{
   Edit3->Text= Mayor(StringGrid1 , StringGrid1->RowCount * StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void MayorAlFinal(TStringGrid *A, byte n)
{ String aux; byte N = A->ColCount;
  if (n>1) {
	MayorAlFinal(A,n-1);
	if ( A->Cells[(n-1)%N][(n-1)/N]< A->Cells[(n-2)%N][(n-2)/N]) {
	  aux = A->Cells[(n-1)%N][(n-1)/N];
	  A->Cells[(n-1)%N][(n-1)/N] = A->Cells[(n-2)%N][(n-2)/N];
	  A->Cells[(n-2)%N][(n-2)/N] = aux;
	}
  }
}

void __fastcall TForm1::Button9Click(TObject *Sender)
{
   MayorAlFinal(StringGrid1 , StringGrid1->RowCount * StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void BubbleSort(TStringGrid *A, byte n)
{
  if (n>0) {
	MayorAlFinal(A, n);
	BubbleSort(A, n-1);
  }
}

void __fastcall TForm1::Button10Click(TObject *Sender)
{
   BubbleSort(StringGrid1 , StringGrid1->RowCount * StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void CambiarFila(TStringGrid *A, byte f1, byte f2, byte n)
{
   if (n>0) {
	 CambiarFila(A, f1, f2, n-1);
	 String aux = A->Cells[n-1][f1];
	 A->Cells[n-1][f1] = A->Cells[n-1][f2];
	 A->Cells[n-1][f2] = aux;
   }
}

void InvertirPorFilas(TStringGrid *A, byte fa, byte fb)
{
  if (fa!=fb && fa<fb) {
	InvertirPorFilas(A, fa+1, fb-1);
	CambiarFila(A, fa, fb, A->ColCount);
  }
}

void Cargar1erParcial(TStringGrid *A, byte n)
{ byte N = A->ColCount;
  if (n>0) {
	  Cargar1erParcial(A, n-1);
	  //se necesita invertir
	  //A->Cells[(n-1)%N][(n-1)/N]=n;

	  //no se necesita invertir, empieza de abajo hacia arriba
	  A->Cells[(n-1)%N][(n-1)/N]=n;
  }
}


void __fastcall TForm1::Button11Click(TObject *Sender)
{
   StringGrid1->RowCount = StrToInt(Edit1->Text);
   StringGrid1->ColCount = StrToInt(Edit2->Text);
   Cargar1erParcial(StringGrid1, StringGrid1->RowCount*StringGrid1->ColCount);
  // InvertirPorFilas(StringGrid1, 0, StringGrid1->RowCount-1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button12Click(TObject *Sender)
{
   InvertirPorFilas(StringGrid1, 0, StringGrid1->RowCount-1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button13Click(TObject *Sender)
{
  CambiarFila(StringGrid1, StrToInt(Edit1->Text)-1, StrToInt(Edit2->Text)-1, StringGrid1->ColCount);
}
//---------------------------------------------------------------------------
void Carg1erParc(TStringGrid *A, byte f, byte c, byte &a)
{ // A = matriz, f = nro filas , c = nro columnas
  if (a<f) {
	a++;
	Carg1erParc(A,f+1,c,a);
	LlenarFila(A,f+1,c);
  }
}

void __fastcall TForm1::Button14Click(TObject *Sender)
{  byte a= 0;
   StringGrid1->RowCount = StrToInt(Edit1->Text);
   StringGrid1->ColCount = StrToInt(Edit2->Text);
   Carg1erParc(StringGrid1, StringGrid1->RowCount-1, StringGrid1->ColCount-1,a);
}
//---------------------------------------------------------------------------

