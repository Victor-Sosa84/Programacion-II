//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitArchivosEstructIndex.h"
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
void __fastcall TForm1::FormCreate(TObject *Sender)
{   NomArch = "Alumnos.dat";
	ruta = "C:\\Users\\HP VICTUS\\Desktop\\Uni 2\\Sem 1 2025\\Programación II (INF210)\\Proyectos C++ RAD\\ArchivosEstructIndex Program2\\";
	//ruta = "E:\\RESPALDOS\\Uni 2\\Sem 1 2025\\Programación II (INF210)\\Proyectos C++ RAD\\ArchivosEstructIndex Program2\\";
	//ruta = "F:\\UNI\\Sem 1 2025\\Programación II (INF210)\\Proyectos C++ RAD\\ArchivosEstructIndex Program2\\";

	NomIdxCod = "AlumnosCod.idx";

	AnsiString nom = ruta + NomArch;
	//la primera vez va a fallar

	fstream f(nom.c_str(), ios::binary|ios::in);
	//Nota: 2do parametro si no hay nada por defecto es texto

	//solo ocurrirá para la primera vez
	if (f.fail()) {
	   f.close();
	   f.open(nom.c_str(), ios::binary|ios::out); //crear el archivo, out lo borra
	}
	f.close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{ //GUARDAR DATOS DE LA PANTALLA
  bool hallado = false;
  Registro reg, regB; //aqui se capturan los datos
  AnsiString auxiliar;

  reg.marca = 100; //campo nuevo

  reg.cod = StrToInt(Edit1->Text);

  reg.ci = StrToInt(Edit7->Text);  //campo nuevo

  auxiliar = Edit2->Text;
  strcpy(reg.nom, auxiliar.c_str()); //asigna a una variable el vector de caracteres

  auxiliar = Edit3->Text;
  strcpy(reg.dir, auxiliar.c_str());

  reg.fecha.día = StrToInt(Edit4->Text);
  reg.fecha.mes = StrToInt(Edit5->Text);
  reg.fecha.año = StrToInt(Edit6->Text);

  //buscar en el archivo el código
  AnsiString nom = ruta + NomArch;
  fstream f(nom.c_str(), ios::binary|ios::in|ios::out);
  while (!f.eof() && !hallado) {
	f.read((char*)&regB, sizeof(reg));
	if (!f.eof()) {
	  hallado = (regB.cod==reg.cod)&&(reg.marca==100);
	}
  }

  if (hallado) {
	f.seekg(-sizeof(reg),ios::cur);
  } else {
	f.close();
	f.open(nom.c_str(), ios::binary|ios::in|ios::out);
	f.seekg(0, ios::end);
  }


  //guardar los datos en el archivo
//  AnsiString nom = ruta + NomArch;
//  fstream f(nom.c_str(), ios::binary|ios::app);
  f.write((char *)&reg, sizeof(reg)); //sizeof tamaño en bytes de una variable
  f.close();

  //borrar la pantalla
  Edit1->Text ="000";
  Edit2->Text ="";
  Edit3->Text ="";
  Edit4->Text ="";
  Edit5->Text ="";
  Edit6->Text ="";
  Edit7->Text =""; //campo nuevo

  Edit1->SetFocus();
  ShowMessage("Registro Guardado Exitosamente");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{ Registro reg; AnsiString nom, linea;

  nom = ruta + NomArch;
  fstream f(nom.c_str(), ios::binary|ios::in);

  //evitar que se cree en otro lado
  nom = ruta + "Listado.txt";
  ofstream listado(nom.c_str());

  while (!f.eof()) {
	f.read((char *)&reg, sizeof(reg));
	if (!f.eof() && (reg.marca==100)) {
	  linea=reg.cod;
	  linea=linea+", "+reg.ci+", "+reg.nom+", "+reg.dir+", "+IntToStr(reg.fecha.día)+"/"+IntToStr(reg.fecha.mes)+"/"+IntToStr(reg.fecha.año);
	  for (Word i = 1; i <= linea.Length(); i++)
		  listado.put(linea[i]);
	  listado.put(10);
	}
  }
  f.close(); listado.close();

  ShowMessage("Listado Generado Exitosamente");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Exit(TObject *Sender)
{  Registro reg; AnsiString nom; bool hallado = false;

  nom = ruta + NomArch;
  fstream f(nom.c_str(), ios::binary|ios::in);

  while (!f.eof()) {
	 f.read((char *)&reg, sizeof(reg));
	 if (!f.eof()) {
		if (reg.cod==StrToInt(Edit1->Text) && reg.marca==100) {
		   Edit7->Text = reg.ci; //campo nuevo
		   Edit2->Text = reg.nom;
		   Edit3->Text = reg.dir;
		   Edit4->Text = reg.fecha.día;
		   Edit4->Text = reg.fecha.día;
		   Edit5->Text = reg.fecha.mes;
		   Edit6->Text = reg.fecha.año;
		   hallado = true;
		}
	 }
  }
  f.close();

  if (!hallado) {
	Edit2->Text ="";
	Edit3->Text ="";
	Edit4->Text ="";
	Edit5->Text ="";
	Edit6->Text ="";
	Edit7->Text =""; //campo nuevo
  }
}
//---------------------------------------------------------------------------

//copiar al archivo con la nueva estructura
void __fastcall TForm1::Button5Click(TObject *Sender)
{ Registro reg; RegistroOld regOld;
  AnsiString nom = ruta + NomArch;
  AnsiString nomNuevo = ruta + "AlumnosOld.dat";
  rename(nom.c_str(), nomNuevo.c_str()); //cambio de nombre de Alumnos a AlumnosOld
  fstream fi(nomNuevo.c_str(), ios::binary|ios::in); //leyendo AlumnosOld
  fstream fo(nom.c_str(), ios::binary|ios::out); //aqui se copia lo de AlumnosOld

  //copiando
  while (!fi.eof()) {
	fi.read((char*)&regOld, sizeof(regOld));
	if (!fi.eof()) {
	  reg.marca = 100; //100=no borrado, 150=borrado
	  reg.ci=0;
	  reg.cod = regOld.cod;
	  strcpy(reg.nom, regOld.nom);
	  strcpy(reg.dir, regOld.dir);
	  reg.fecha = regOld.fecha;

	  fo.write((char*)&reg, sizeof(reg));
	}
  }
  fi.close(); fo.close();

  ShowMessage("Reestructuración con Éxito, no vuelva a presionar este botón");
  Button5->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{  Registro reg; bool hallado = false;
   AnsiString nom = ruta + NomArch;
   fstream f(nom.c_str(), ios::binary|ios::in|ios::out);

   while (!f.eof()&& !hallado) {
	 f.read((char*)&reg, sizeof(reg));
	 if (!f.eof()) {
		hallado = (reg.cod==StrToInt(Edit1->Text)) && (reg.marca==100);
	 }
   }

   if (hallado) {
	  f.seekg(-sizeof(reg), ios::cur);
	  reg.marca = 150; //marca de borrado
	  f.write((char*)&reg, sizeof(reg));

	  //limpiar pantalla
      Edit1->Text ="000";
	  Edit2->Text ="";
	  Edit3->Text ="";
	  Edit4->Text ="";
	  Edit5->Text ="";
	  Edit6->Text ="";
	  Edit7->Text ="";
   }
   f.close();

   Edit1->SetFocus();
   ShowMessage("Registro Eliminado Éxitosamente");
}
//---------------------------------------------------------------------------

//limpia todos los edit
void __fastcall TForm1::Button3Click(TObject *Sender)
{   Edit1->Text = "000";
	Edit2->Text = "";
	Edit3->Text = "";
	Edit4->Text = "";
	Edit5->Text = "";
	Edit6->Text = "";
	Edit7->Text = "";

	Edit1->SetFocus();
}
//---------------------------------------------------------------------------

//crear el archivo índice por código
void __fastcall TForm1::Button6Click(TObject *Sender)
{  Registro reg; RegIdxCod regIdx;

   //para leer el alumnos.dat
   AnsiString nom = ruta + NomArch;
   fstream fi(nom.c_str(), ios::binary|ios::in);

   //para escribir en alumnoscod.idx
   nom = ruta + NomIdxCod;
   fstream fo(nom.c_str(), ios::binary|ios::out);

   while (!fi.eof()) {
	  regIdx.ref = fi.tellg();
	  fi.read((char*)&reg, sizeof(reg));
	  if (!fi.eof()) {
		 regIdx.cod = reg.cod;

		 fo.write((char*)&regIdx, sizeof(regIdx));
	  }
   }
   fi.close();
   fo.close();

   ShowMessage("Indexado por Código Exitosamente");
}
//---------------------------------------------------------------------------

//genera un listado de acuedo al índice por código
void __fastcall TForm1::Button7Click(TObject *Sender)
{  Registro reg; RegIdxCod regIdx; AnsiString nom, linea;

   nom = ruta + NomArch;
   fstream f(nom.c_str(), ios::binary|ios::in);

   nom = ruta + NomIdxCod;
   fstream fi(nom.c_str(), ios::binary|ios::in);

   nom = ruta + "Listado por Código.txt";
   ofstream listado(nom.c_str());

   if (!fi.fail()) {
	 while (!fi.eof()) { //recorrer el archivo índice
		fi.read((char*)&regIdx, sizeof(regIdx));
		if (!fi.eof()) {
		   f.seekg(regIdx.ref, ios::beg);
		   f.read((char*)&reg, sizeof(reg));
		   if (reg.marca==100) {
			 linea = reg.cod;
			 linea = linea + ", " + reg.ci + ", " + reg.nom + ", " + reg.dir + ", " + reg.fecha.día + "/" + reg.fecha.mes + "/" + reg.fecha.año;
			 for (Word i = 1; i <= linea.Length(); i++)
				listado.put(linea[i]);
			 listado.put(10);

			 /*linea=regIdx.cod; linea=linea+", ruta en la lista: "+regIdx.ref;
             for (Word i = 1; i <= linea.Length(); i++)
				listado.put(linea[i]);
			 listado.put(10); */
		   }
		}
	 }
	 f.close(); fi.close(); listado.close();
   }

   ShowMessage("Listado Por Código Generado Exitosamente");
}
//---------------------------------------------------------------------------

//inicia el proceso de navegación
void __fastcall TForm1::Button8Click(TObject *Sender)
{ Registro reg; RegIdxCod regIdx;

  Button8->Enabled = false; //botón inicia navegación
  Button9->Enabled = true; //botón avanzar
  Button11->Enabled = true; //botón finalizar navegación

  //inicializar y crear registro normal
  AnsiString nom = ruta + NomArch;
  fd = new fstream(nom.c_str(), ios::binary|ios::in);

  //inicializar y crear registro de índice por código
  nom = ruta + NomIdxCod;
  fi = new fstream(nom.c_str(), ios::binary|ios::in);

  if (!fi->fail()) {
	 //while (!fi->eof()) {
	  fi->read((char*)&regIdx, sizeof(regIdx)); //leer el indice por codigo
	  if (!fi->eof()) {
	   fd->seekg(regIdx.ref, ios::beg); //posicionar puntero
	   fd->read((char*)&reg, sizeof(reg));  //leer el registro desde el puntero
	   //mostrar en los edits
	   Edit1->Text = reg.cod;
	   Edit2->Text = reg.nom;
	   Edit3->Text = reg.dir;
	   Edit4->Text = reg.fecha.día;
	   Edit5->Text = reg.fecha.mes;
	   Edit6->Text = reg.fecha.año;
	   Edit7->Text = reg.ci;
	  }
	 //}
  }
}
//---------------------------------------------------------------------------

//finaliza el proceso de navegación
void __fastcall TForm1::Button9Click(TObject *Sender)
{ Button8->Enabled = true; //botón inicia navegación
  Button9->Enabled = false; //botón avanzar
  Button10->Enabled = false; //botón anterior
  Button11->Enabled = false; //botón finalizar navegación

  //finalizar y borrar variables fd y fi
  fd->close(); fi->close();
  delete(fd); delete(fi);
  Button3Click(Sender);
}
//---------------------------------------------------------------------------

//botón avanzar en la navegación (a mi modo xddd)
void __fastcall TForm1::Button11Click(TObject *Sender)
{ Button10->Enabled = true;

  Registro reg; RegIdxCod regIdx;
  AnsiString nom = ruta + NomIdxCod;

  //reiniciar la lectura del archivo
/*  fi->close();
  AnsiString nom = ruta + NomIdxCod;
  fi->open(nom.c_str(), ios::binary|ios::in);

  //calcular la ruta al registro
  Cardinal ref=0;
  while (!fi->eof() && regIdx.cod != StrToInt(Edit1->Text)) {
	fi->read((char*)&regIdx, sizeof(regIdx));
	if (!fi->eof()) {
	   ref = ref + sizeof(reg);
	}
  }   */

 // fi->seekg(sizeof(regIdx) ,ios::cur);
  fi->read((char*)&regIdx, sizeof(regIdx));

  //mostrar el registro
  if(!fi->eof()) {
	fd->seekg(regIdx.ref, ios::beg);
	fd->read((char*)&reg, sizeof(reg));

	Edit1->Text = reg.cod;
	Edit2->Text = reg.nom;
	Edit3->Text = reg.dir;
	Edit4->Text = reg.fecha.día;
	Edit5->Text = reg.fecha.mes;
	Edit6->Text = reg.fecha.año;
	Edit7->Text = reg.ci;
  } else {
	  Button11->Enabled = false;
      //posicionar puntero al final
	  fi->close();
	  fi->open(nom.c_str(), ios::binary|ios::in|ios::ate);
  }


  //deshabilitar el botón si llego al último registro
 /* fi->seekp(-sizeof(regIdx), ios::end);
  fi->read((char*)&regIdx, sizeof(regIdx));
  if (regIdx.cod == StrToInt(Edit1->Text))
	Button11->Enabled = false; */
}
//---------------------------------------------------------------------------

//botón retroceder en la navegación (a mi modo xdd)
void __fastcall TForm1::Button10Click(TObject *Sender)
{ Button11->Enabled = true;

  Registro reg; RegIdxCod regIdx;

  //reiniciar la lectura del archivo
  /*fi->close();
  AnsiString nom = ruta + NomIdxCod;
  fi->open(nom.c_str(), ios::binary|ios::in);

  //calcular la ruta al registro
  Cardinal ref=0;
  while (!fi->eof() && regIdx.cod != StrToInt(Edit1->Text)) {
	fi->read((char*)&regIdx, sizeof(regIdx));
	if (!fi->eof()) {
	   ref = ref + sizeof(reg);
	}
  }
  ref=ref-sizeof(reg)*2; */

  fi->seekg(-2*(sizeof(regIdx)), ios::cur);
   Cardinal p = fi->tellg();
  fi->read((char*)&regIdx, sizeof(regIdx));

   //mostrar el registro
  fd->seekg(regIdx.ref, ios::beg);
  fd->read((char*)&reg, sizeof(reg));

	Edit1->Text = reg.cod;
	Edit2->Text = reg.nom;
	Edit3->Text = reg.dir;
	Edit4->Text = reg.fecha.día;
	Edit5->Text = reg.fecha.mes;
	Edit6->Text = reg.fecha.año;
	Edit7->Text = reg.ci;
  if (p==0) {
	Button10->Enabled = false;
  }

  //deshabilitar el botón si llego al primer registro
 /* fi->seekp(0, ios::beg);
  fi->read((char*)&regIdx, sizeof(regIdx));
  if (regIdx.cod == StrToInt(Edit1->Text))
	Button10->Enabled = false;   */
}
//---------------------------------------------------------------------------

void AnsiToMayus(AnsiString &cad)
{ AnsiString mayusculas = "QWERTYUIOPASDFGHJKLZXCVBNMÑÁÉÍÓÚÜ";
  AnsiString minusculas = "qwertyuiopasdfghjklzxcvbnmñáéíóúü";
  for (Word i=1; i <= cad.Length(); i++) {
	 byte p = minusculas.Pos(cad[i]);
	 if (p>0) {
	   cad[i] = mayusculas[p];
	 }
  }
}

//Algoritmo para convertir el campo nombre a mayusculas
//usando el archivo índice por código
void __fastcall TForm1::Button12Click(TObject *Sender)
{ Registro reg; RegIdxCod regIdx; AnsiString nom;

  nom = ruta + NomArch; //archivo normal
  fstream fd(nom.c_str(), ios::binary|ios::in|ios::out);
  nom = ruta + NomIdxCod;  //archivo indice
  fstream fi(nom.c_str(), ios::binary|ios::in);

  if (!fi.fail()) {
	while (!fi.eof()) {
	   fi.read((char*)&regIdx, sizeof(regIdx));
	   if (!fi.eof()) {
		 fd.seekg(regIdx.ref); //por defecto 2do parametro es desde el inicio
		 fd.read((char*)&reg, sizeof(reg));
		 nom = reg.nom;
		 AnsiToMayus(nom);
		 strcpy(reg.nom, nom.c_str());
		 fd.seekg(regIdx.ref);
		 fd.write((char*)&reg, sizeof(reg));
	   }
	}
	fi.close();
  }
  fd.close();

  ShowMessage("Nombres Cambiados a Mayúsculas Exitosamente");
}
//---------------------------------------------------------------------------

//Algoritmo de ordenamiento por selection sort
void __fastcall TForm1::Button13Click(TObject *Sender)
{ RegIdxCod ri,rj; Cardinal i,j,k; //j=donde esta el mayor, con i recorro todo el archivo
								   //k=registro ultimo(?)
  AnsiString nom= ruta + NomIdxCod;
  fstream fi(nom.c_str(), ios::binary|ios::in|ios::out|ios::ate);
  if (!fi.fail()) {  //por si no existe el archivo indice
	 k = fi.tellg();
	 if (k>0) //por si el archivo tiene al menos un registro
	   k = k - sizeof(rj);
	 while (k>0) {
	   //busqueda del mayor desde 0 hasta k
	   j = 0; fi.seekg(j); fi.read((char*)&rj, sizeof(rj));
	   i = sizeof(rj);
	   while (i<=k) {
		 fi.seekg(i); fi.read((char*)&ri, sizeof(ri));
		 if (ri.cod > rj.cod) {
			j = i; rj = ri;
		 }
		 i = i + sizeof(ri);
	   }
	   if (k!=j) { //intercambiar el mayor(j)con el último (k), si es que el mayor no es el ultimo
		 fi.seekg(j); fi.write((char*)&ri, sizeof(ri));
		 fi.seekg(k); fi.write((char*)&rj, sizeof(rj));
	   }
	   k = k - sizeof(rj);
	 }
	 fi.close();
  }

  ShowMessage("Archivo Ordenado");
}
//---------------------------------------------------------------------------

//Algoritmo de busqueda binaria
void __fastcall TForm1::Button14Click(TObject *Sender)
{ Longint a,b,c; RegIdxCod regIdx; Registro reg; Word codigo; bool hallado;
  codigo = StrToInt(Edit1->Text);
  AnsiString nom = ruta + NomIdxCod;
  fstream fi(nom.c_str(), ios::binary|ios::in|ios::ate);  //ate para saber la posicion del ultimo registro
  if (!fi.fail()) {
	 //busqueda binaria
	 a = 0; b = fi.tellg(); b= b - sizeof(regIdx); hallado = false; //inicializar variables
	 while (a<=b && !hallado) {
		 c = ( ((a+b)/2)/sizeof(regIdx) ) * sizeof(regIdx); //punto medio
		 fi.seekg(c); fi.read((char*)&regIdx, sizeof(regIdx));
		 if (codigo==regIdx.cod)
		   hallado = true;
		 else if (codigo < regIdx.cod)
				 b = c - sizeof(regIdx);
		 else
			a = c + sizeof(regIdx);
	 }

	 //si lo encontro
	 if (hallado) {
		nom = ruta + NomArch;
		fstream fd(nom.c_str(), ios::binary|ios::in);
		fd.seekg(regIdx.ref); fd.read((char*)&reg, sizeof(reg));
		fd.close();
		Edit2->Text = reg.nom;
		Edit3->Text = reg.dir;
		Edit4->Text = reg.fecha.año;
		Edit5->Text = reg.fecha.mes;
		Edit6->Text = reg.fecha.día;
		Edit7->Text = reg.ci;
	 } else { //si no lo encontro
		Edit2->Text = "";
		Edit3->Text = "";
		Edit4->Text = "";
		Edit5->Text = "";
		Edit6->Text = "";
		Edit7->Text = "";
	 }
	 fi.close();
  }
}
//---------------------------------------------------------------------------

Fecha DiaMes( Fecha fecha )
{ bool bisiesto;
  if( fecha.mes == 4 || fecha.mes == 6 || fecha.mes == 9 || fecha.mes == 11)
   {
	 if( fecha.día == 30)
	{ fecha.día = 1;
	 fecha.mes = fecha.mes+1;
	}else
	 fecha.día = fecha.día + 1;
   }
  else if( fecha.mes == 1 || fecha.mes == 3 || fecha.mes==5 || fecha.mes == 7 ||fecha.mes == 8 || fecha.mes == 10 || fecha.mes == 12)
  {
	 if( fecha.día == 31)
	{ fecha.día = 1;
	  if( fecha.mes == 12)
	  {
	   fecha.año = fecha.año + 1;
	   fecha.mes = 1;
	  }
	  else
	  {
	   fecha.mes = fecha.mes + 1;
	  }
	}
	else
	fecha.día = fecha.día + 1;
  }
  else if( fecha.mes == 2)
   {
	bisiesto = (fecha.año % 4 == 0 && fecha.año % 100 !=0) ||  fecha.año % 400 == 0;
	if (bisiesto)
	   if (fecha.día == 29)
	   { fecha.mes = 3;
		 fecha.día = 1;
	   } else
		  fecha.día = fecha.día + 1;
	else
	   if(fecha.día == 28)
	   { fecha.mes = 3;
		 fecha.día = 1;
	   } else
		  fecha.día = fecha.día +1;
   }

  return fecha;
}

void __fastcall TForm1::Button15Click(TObject *Sender)
{
  Registro reg; AnsiString nom = ruta + NomArch;
  fstream f(nom.c_str(), ios::binary | ios::in | ios::out );
  Cardinal p = 0;
  while( !f.eof() )
  {
	f.seekg(p,ios::beg);
	f.read( (char*)&reg , sizeof(reg) );
	if( !f.eof() )
	{
	  reg.fecha = DiaMes( reg.fecha );
	  f.seekg( p , ios::beg);
	  f.write( (char*)&reg , sizeof(reg) );
	  p = p + sizeof(reg);
	}
  }
  f.close();
  ShowMessage( "Archivo Actualizado");
}
//---------------------------------------------------------------------------

