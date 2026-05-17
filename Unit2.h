#ifndef Unit2H
#define Unit2H
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Game.h>
#include <IdAntiFreeze.hpp>
#include <IdAntiFreezeBase.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>
#include <IdContext.hpp>
#include <string>

//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:
	TImage *ImageP1_2;
	TImage *ImageP1_3;
	TImage *ImageP1_4;
	TImage *ImageTable1;
	TImage *ImageTable2;
	TImage *ImageTable3;
	TImage *ImageTable4;
	TImage *ImageP2_1;
	TImage *ImageP2_2;
	TImage *ImageP2_3;
	TImage *ImageP2_4;
	TImage *ImageP1_1;
	TImage *CardImage;
	TImage *ImageTable7;
	TImage *ImageTable8;
	TImage *ImageTable6;
	TImage *ImageTable5;
	TLabel *LabelScoreP1;
	TLabel *LabelScoreP2;
	TImage *Image1;
	TIdTCPServer *IdTCPServer1;
	TIdTCPClient *IdTCPClient1;
	TIdAntiFreeze *IdAntiFreeze1;
	TEdit *EditIP;
	TButton *BtnHost;
	TButton *BtnJoin;
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall TableImageDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept);
	void __fastcall TableImageDragDrop(TObject *Sender, TObject *Source, int X, int Y);
	void __fastcall BtnHostClick(TObject *Sender);
	void __fastcall BtnJoinClick(TObject *Sender);
	void __fastcall IdTCPServer1Execute(TIdContext *AContext);
	void __fastcall IdTCPServer1Connect(TIdContext *AContext);
private:
    Game *game;
	TPngImage *BackgroundImage;
    int localPlayerID;
	bool isMyTurn;
	void UpdateUI();
	void LoadPNGToImage(TImage* img, const std::string& path);
	void SendMove(int handIndex, int tableIndex);
	void ProcessMove(String command);
	const std::string cardBackPath = ExtractFilePath(Application->ExeName) + "Background\\card back black.png";

public:
	__fastcall TForm2(TComponent* Owner);
	__fastcall ~TForm2();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
