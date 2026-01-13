//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitArchivosTexto.h"
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
{  AnsiString nom; char x;
   if (OpenTextFileDialog1->Execute()) {  //abre el archivo
	  Edit1->Text = OpenTextFileDialog1->FileName; //nombre de la ruta del archivo

	  nom = Edit1->Text; //ruta del archivo en 'nom'
	  Edit2->Text="";
	  ifstream f(nom.c_str()); //clase ifstream solo lectura, solo admite cadenas de tipo vector de caracteres
							   // .c_str() convierte un string en un vector de caracteres
	  //incluir la libreria fstream en la unidad .h

	  if (!f.fail()) { // metodo de ifstream que devuelve true si fallo al abrir el archivo
		while (!f.eof()) {//metodo de ifstream que devuelve true si llego al final del archivo
		   x=f.get(); //metodo de ifstream que lee un caracter (desde el primero)

		   if (!f.eof()) {
              //colocar su codigo ascii de cada caracter en el archivo
			  Edit2->Text = Edit2->Text + IntToStr(x) + ",";
		   }
		}
		f.close(); //cierra el archivo
	  }

   }
}
//---------------------------------------------------------------------------
bool EsVocal(char c)
{ AnsiString vocales = "aeoiuAEOIUáéíóúÁÉÍÓÚÜü";
  return vocales.Pos(c) > 0;
}

Cardinal CantVocales(AnsiString nom)
{ Cardinal c = 0; char x;
  ifstream f(nom.c_str());
  if (!f.fail()) {
	while (!f.eof()) {
	  x = f.get();
	  if (!f.eof()) {
		 EsVocal(x)? c++ : c ;
	  }
	}
	f.close();
  }
  return c;
}

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  if (OpenTextFileDialog1->Execute()) {
	Edit3->Text = CantVocales(OpenTextFileDialog1->FileName);
  }
}
//---------------------------------------------------------------------------
bool EsLetra(char c)
{ AnsiString letras = "qwertyuiopasdfghjklzxcvbnmñQWERTYUIOPASDFGHJKLZXCVBNMÑáéíóúÁÉÍÓÚüÜ";
  return letras.Pos(c) > 0 ;
}

Cardinal CantPalabras(AnsiString nom)
{ Cardinal c = 0; char x; bool b = true;
  ifstream f(nom.c_str());
  if (!f.fail()) {
	while (!f.eof()) {
	  x = f.get();
	  if (!f.eof()) {
		if (EsLetra(x)) {
		   if (b) {
			 c++; b=false;
		   }
		} else
			b = true;
	  }
	}
	f.close();
  }
  return c;
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
  if (OpenTextFileDialog1->Execute())
	Edit3->Text=CantPalabras(OpenTextFileDialog1->FileName);
}
//---------------------------------------------------------------------------
void CantPalabrasPorLinea(AnsiString nom)
{ Cardinal n, c = 0; char x; bool b = true; AnsiString linea;
  ifstream fi(nom.c_str());
  ofstream fo("Resultado.txt");
  if (!fi.fail()) {
	while (!fi.eof()) {
	  x = fi.get();
	  if (!fi.eof()) {
		if (EsLetra(x)) {
		   if (b) {
			 c++; b=false;
		   }
		} else if (x==10) { //verificar si es EOL
				  //grabar el caracter
				  linea = c; n = linea.Length();
				  for (Word i=1; i <= n; i++)
					 fo.put(linea[i]);

				  fo.put(10); //grabar el ENTER

				  c = 0; b = true;
			   } else
				  b = true;
	  }
	}
	linea = c; n = linea.Length();
	for (Word i=1; i <= n; i++)
	   fo.put(linea[i]);
	fo.close();
	fi.close();
  }

  ShowMessage("Resultado.txt generado con éxito.");
}

void __fastcall TForm1::Button4Click(TObject *Sender)
{
  if (OpenTextFileDialog1->Execute())
	CantPalabrasPorLinea(OpenTextFileDialog1->FileName);
}
//---------------------------------------------------------------------------
void ToMayus(char &c)
{ AnsiString Mayusculas = "QWERTYUIOPASDFGHJKLZXCVBNMÑÁÉÍÓÚÜ";
  AnsiString Minusculas = "qwertyuiopasdfghjklzxcvbnmñáéíóúü";
  if (Minusculas.Pos(c) > 0)
	c = Mayusculas[Minusculas.Pos(c)];
}

void ToMinus(char &c)
{ AnsiString Mayusculas = "QWERTYUIOPASDFGHJKLZXCVBNMÑÁÉÍÓÚÜ";
  AnsiString Minusculas = "qwertyuiopasdfghjklzxcvbnmñáéíóúü";
  if (Mayusculas.Pos(c) > 0)
	c = Minusculas[Mayusculas.Pos(c)];
}

void Modificar(AnsiString nom)
{ char x; boolean bandera = true;
  ifstream fi(nom.c_str());
  ofstream fo("temporal.txt");
  if (!fi.fail()) {
	while (!fi.eof()) {
	  x = fi.get();
	  if (!fi.eof()) {
		if (EsLetra(x)) {
		   if (bandera==true) {
			 ToMayus(x);
			 bandera = false;
		   } else {
			 ToMinus(x);
		   }
		} else {
		   bandera = true;
		}
		fo.put(x);
	  }
	}
	fi.close();
	fo.close();
	remove(nom.c_str()); //eliminar el archivo
	rename("temporal.txt",nom.c_str()); //cambiar nombre del archivo
  }
}

void __fastcall TForm1::Button5Click(TObject *Sender)
{
  if (OpenTextFileDialog1->Execute())
	Modificar(OpenTextFileDialog1->FileName);
}
//---------------------------------------------------------------------------
void AlinDerecha(AnsiString nom)
{ char x; Word longActual, longMayor; AnsiString linea = "";
  ifstream fi(nom.c_str());
  ofstream fo("temporal.txt");

  if (!fi.fail()) {

	//1 FASE: DETERMINAR LINEA MÁS LARGA
	longActual = 0 ; longMayor = 0;
	while (!fi.eof()) {
	  x = fi.get();
	  if (fi.eof() || x==10) {
		 if (longActual > longMayor)
			longMayor = longActual;
		 longActual = 0;
	  } else {
		longActual++;
      }
	}
	fi.close();

    //2 FASE: CAMBIAR LA ALINEACIÓN A LA LÍNEA MÁS LARGA (AUMENTAR ESPACIOS)
	fi.open(nom.c_str()); //Abre denuevo el archivo, puntero al inicio
	AnsiString Espacios;
	while (!fi.eof()) {
	   x = fi.get();
	   if (fi.eof() || x==10) {
		  Espacios = longMayor - linea.Length();
		  for (Word i=1; i<=Espacios; i++) //aumentar los espacios
			  linea = " " + linea;
		  //Nota: Para alinear al centro, calcular los espacios dentro del for
		  for (Word i=1; i<=linea.Length(); i++) //grabar la linea
			  fo.put(linea[i]);
		  if (!fi.eof()) //grabar fin de linea
			fo.put(10);
		  linea = ""; //resetear la linea
	   } else {
		  linea = linea + x; //recolectar caracteres en la linea
       }
	}

	fi.close();
	fo.close();
	remove(nom.c_str());
	rename("temporal.txt",nom.c_str());
  }
}

void __fastcall TForm1::Button6Click(TObject *Sender)
{
  if (OpenTextFileDialog1->Execute())
	AlinDerecha(OpenTextFileDialog1->FileName);
}
//---------------------------------------------------------------------------

//verificar si es numero
bool EsNumero(char c)
{  AnsiString Numeros = "0123456789";
   return Numeros.Pos(c) > 0;
}

//cambiar numero por su literal
//version pro xd
AnsiString NumToLiteral(int num)
{ AnsiString numeros[10] = {"cero","uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve"} ;
  return numeros[num];
}

//version larga xdd
/*AnsiString NumToLiteral(char num)
{  AnsiString Literal;
   if (num == '0')
	  Literal = "cero";
   if (num == '1')
	  Literal = "uno";
   if (num == '2')
	  Literal = "dos";
   if (num == '3')
	  Literal = "tres";
   if (num == '4')
	  Literal = "cuatro";
   if (num == '5')
	  Literal = "cinco";
   if (num == '6')
	  Literal = "seis";
   if (num == '7')
	  Literal = "siete";
   if (num == '8')
	  Literal = "ocho";
   if (num == '9')
	  Literal = "nueve";
   return Literal;
} */

//Modificar un Archivo de texto de forma que se reemplace cada caracter numerico (digito)
//por su literal
void ModifiToLiteral(AnsiString nom)
{
  char x; AnsiString aux;
  ifstream fi(nom.c_str());
  ofstream fo("temporal6.txt");

  if (!fi.fail()) {
	 while (!fi.eof()) {
		x=fi.get();
		if (!fi.eof()) {
		   if (EsNumero(x)) { //si es numero convierte a literal y graba
			  aux = NumToLiteral(StrToInt(x)); //version pro xd
			  //aux = NumToLiteral(x); //para la version larga xd
			  for (Word i = 1; i <= aux.Length(); i++)
				 fo.put(aux[i]);
		   } else  //si no es numero solo graba
			  fo.put(x);
		}
	 }
	 fi.close(); fo.close();
	 //efecto de modificar
	 remove(nom.c_str());
	 rename("temporal6.txt",nom.c_str());
  }
}

//llamada
void __fastcall TForm1::Button7Click(TObject *Sender)
{  if (OpenTextFileDialog1->Execute())
	ModifiToLiteral(OpenTextFileDialog1->FileName);

   ShowMessage("Numeros fueron cambiados a literal");
}
//---------------------------------------------------------------------------


