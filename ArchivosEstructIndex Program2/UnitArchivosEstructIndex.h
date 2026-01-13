//---------------------------------------------------------------------------

#ifndef UnitArchivosEstructIndexH
#define UnitArchivosEstructIndexH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <fstream>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TEdit *Edit4;
	TEdit *Edit5;
	TEdit *Edit6;
	TLabel *Label6;
	TEdit *Edit7;
	TButton *Button5;
	TButton *Button6;
	TButton *Button7;
	TButton *Button8;
	TButton *Button9;
	TButton *Button10;
	TButton *Button11;
	TButton *Button12;
	TButton *Button13;
	TButton *Button14;
	TButton *Button15;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button7Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button11Click(TObject *Sender);
	void __fastcall Button10Click(TObject *Sender);
	void __fastcall Button12Click(TObject *Sender);
	void __fastcall Button13Click(TObject *Sender);
	void __fastcall Button14Click(TObject *Sender);
	void __fastcall Button15Click(TObject *Sender);
private:	// User declarations

	//VARIABLES LOCALES
	AnsiString NomArch;
	AnsiString ruta;

	AnsiString NomIdxCod;
	fstream *fd, *fi; //datos e índice por código
                      //fd = datos, fi = índice

public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};

//ESTRUCTURA DE LA TABLA
struct Fecha{
	byte día;
	byte mes;
	Word año;
}; //4 bytes
struct RegistroOld{
	Word cod;
	char nom[21];
	char dir[21];
	Fecha fecha;
}; //48 bytes;

struct Registro{ //estructura nueva
	byte marca; //para marcar los registros borrados
	Cardinal ci;
	Word cod;
	char nom[31];
	char dir[31];
	Fecha fecha;
}; //76 bytes;

struct RegIdxCod{ //estructura de indice por código
	Word cod;
	Cardinal ref;
};

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
