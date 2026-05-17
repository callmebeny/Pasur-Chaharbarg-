#include <vcl.h>
#pragma hdrstop
#include <Vcl.Imaging.pngimage.hpp>
#include "Unit2.h"

#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

// ...........................................................................

__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	localPlayerID = 0;
	isMyTurn = false;
	game = nullptr;

	TComponent* comps[] = {
		ImageTable1, ImageTable2, ImageTable3, ImageTable4, ImageTable5, ImageTable6, ImageTable7, ImageTable8,
		ImageP1_1, ImageP1_2, ImageP1_3, ImageP1_4, ImageP2_1, ImageP2_2, ImageP2_3, ImageP2_4
	};
	for(int i=0; i<16; i++) {
		TImage* img = dynamic_cast<TImage*>(comps[i]);
		if(img) img->Stretch = true;
	}

	TImage* Tables[] = {ImageTable1, ImageTable2, ImageTable3, ImageTable4, ImageTable5, ImageTable6, ImageTable7, ImageTable8};
	for(auto img : Tables) {
		if(img) {
			img->OnDragOver = TableImageDragOver;
			img->OnDragDrop = TableImageDragDrop;
		}
	}
}

// ...........................................................................

__fastcall TForm2::~TForm2() {
	if (BackgroundImage) delete BackgroundImage;
	if (game) delete game;
}

// ...........................................................................

void TForm2::UpdateUI() {
	if (!game) return;


	TImage* TableImg[8] = {ImageTable1, ImageTable2, ImageTable3, ImageTable4, ImageTable5, ImageTable6, ImageTable7, ImageTable8};
	vector<Card*>& table = game->getTable();

	for (int i = 0; i < 8; i++) {
		if (!TableImg[i]) continue;
		if (i < table.size()) {
			LoadPNGToImage(TableImg[i], table[i]->image);
			TableImg[i]->Visible = true;
			TableImg[i]->Tag = i;
		} else {
			TableImg[i]->Picture->Assign(NULL);
			TableImg[i]->Tag = -1;
		}
	}


	const vector<Card*>* myHandPtr = nullptr;
	const vector<Card*>* oppHandPtr = nullptr;

	if (localPlayerID == 1) {
		myHandPtr = &game->getPlayer1().getHand();
		oppHandPtr = &game->getPlayer2().getHand();
	} else {
		myHandPtr = &game->getPlayer2().getHand();
		oppHandPtr = &game->getPlayer1().getHand();
	}


	TImage* TopImg[4] = {ImageP1_1, ImageP1_2, ImageP1_3, ImageP1_4};
	for (int i = 0; i < 4; i++) {
		if (i < oppHandPtr->size()) LoadPNGToImage(TopImg[i], cardBackPath);
		else TopImg[i]->Picture->Assign(NULL);
	}


	TImage* BottomImg[4] = {ImageP2_1, ImageP2_2, ImageP2_3, ImageP2_4};
	for (int i = 0; i < 4; i++) {
		if (i < myHandPtr->size()) {
			LoadPNGToImage(BottomImg[i], (*myHandPtr)[i]->image);
			BottomImg[i]->Tag = i;
		} else {
			BottomImg[i]->Picture->Assign(NULL);
		}
	}


	int s1 = game->getPlayer1().calculateScore();
	int s2 = game->getPlayer2().calculateScore();
	if (LabelScoreP1) LabelScoreP1->Caption = "Adversar: " + IntToStr(localPlayerID == 1 ? s2 : s1);
	if (LabelScoreP2) LabelScoreP2->Caption = "Eu: " + IntToStr(localPlayerID == 1 ? s1 : s2);


	if (isMyTurn) this->Caption = "Paur - ESTE RANDUL TAU!";
	else this->Caption = "Pasur - Asteapta mutarea adversarului...";


	if (game->isGameOver()) {
		String winnerMsg = "";
		if (s1 > s2) winnerMsg = "Castigator: Player 1 (Host)!";
		else if (s2 > s1) winnerMsg = "Castigator: Player 2 (Client)!";
		else winnerMsg = "Egalitate!";

		String finalMsg = "JOC TERMINAT!\n\nScor P1: " + IntToStr(s1) + "\nScor P2: " + IntToStr(s2) + "\n\n" + winnerMsg;

		ShowMessage(finalMsg);
		isMyTurn = false;
	}
}

// ...........................................................................

void TForm2::SendMove(int handIndex, int tableIndex) {
	String cmd = "MOVE:" + IntToStr(handIndex) + "," + IntToStr(tableIndex);
	if (IdTCPServer1->Active) {
		TList* clients = IdTCPServer1->Contexts->LockList();
		try {
			for (int i = 0; i < clients->Count; i++) {
				TIdContext* ctx = (TIdContext*)clients->Items[i];
				ctx->Connection->IOHandler->WriteLn(cmd);
			}
		} __finally { IdTCPServer1->Contexts->UnlockList(); }
	}
	else if (IdTCPClient1->Connected()) {
		IdTCPClient1->IOHandler->WriteLn(cmd);
	}
}

// ...........................................................................

void TForm2::ProcessMove(String command) {
	if (command.Pos("MOVE:") == 1) {
		String params = command.SubString(6, command.Length());
		int commaPos = params.Pos(",");
		int hIdx = params.SubString(1, commaPos - 1).ToInt();
		int tIdx = params.SubString(commaPos + 1, params.Length()).ToInt();

		Player* opponent = (localPlayerID == 1) ? &game->getPlayer2() : &game->getPlayer1();

		game->attemptCapture(*opponent, hIdx, tIdx);
		game->nextRound();

		isMyTurn = true;
		UpdateUI();
	}
}

// ...........................................................................

void __fastcall TForm2::TableImageDragDrop(TObject *Sender, TObject *Source, int X, int Y) {
	if (!game || !isMyTurn) return;

	TImage* destImg = dynamic_cast<TImage*>(Sender);
	TImage* sourceImg = dynamic_cast<TImage*>(Source);

	if (destImg && sourceImg) {
		if (sourceImg->Name.Pos("P2") == 0) return;

		int tableIndex = destImg->Tag;
		int handIndex = sourceImg->Tag;
		Player* me = (localPlayerID == 1) ? &game->getPlayer1() : &game->getPlayer2();

		if (game->attemptCapture(*me, handIndex, tableIndex)) {
			game->nextRound();
			SendMove(handIndex, tableIndex);
			isMyTurn = false;
			UpdateUI();
		}
	}
}

// ...........................................................................

void __fastcall TForm2::TableImageDragOver(TObject *Sender, TObject *Source, int X, int Y, TDragState State, bool &Accept) {
	Accept = false;
	TImage* src = dynamic_cast<TImage*>(Source);
	if (src && src->Name.Pos("P2") > 0) Accept = true;
}

// ...........................................................................

void __fastcall TForm2::BtnHostClick(TObject *Sender) {
	IdTCPServer1->DefaultPort = 5000;
	try {
		IdTCPServer1->Active = true;
		localPlayerID = 1;
		isMyTurn = true;
		if (game) delete game;
		game = new Game("Host", "Client", 0);
		UpdateUI();
		BtnHost->Enabled = false; BtnJoin->Enabled = false;
	} catch (...) {}
}

// ...........................................................................

void __fastcall TForm2::IdTCPServer1Execute(TIdContext *AContext) {
	String cmd = AContext->Connection->IOHandler->ReadLn();
	TThread::Synchronize(nullptr, [=]() { ProcessMove(cmd); });
}

// ...........................................................................

void __fastcall TForm2::IdTCPServer1Connect(TIdContext *AContext) {
	int seed = 0;
	TThread::Synchronize(nullptr, [&](){ if(game) seed = game->getSeed(); });
	AContext->Connection->IOHandler->WriteLn("SEED:" + IntToStr(seed));
}

// ...........................................................................

void __fastcall TForm2::BtnJoinClick(TObject *Sender) {
	IdTCPClient1->Port = 5000;
	IdTCPClient1->Host = EditIP->Text;
	try {
		IdTCPClient1->Connect();
		localPlayerID = 2;
		isMyTurn = false;
		String response = IdTCPClient1->IOHandler->ReadLn();
		if (response.Pos("SEED:") == 1) {
			int s = response.SubString(6, response.Length()).ToInt();
			if (game) delete game;
			game = new Game("Host", "Client", s);
			UpdateUI();
		}
		BtnHost->Enabled = false; BtnJoin->Enabled = false;
		TThread::CreateAnonymousThread([=]() {
			while(IdTCPClient1->Connected()) {
				try {
					String line = IdTCPClient1->IOHandler->ReadLn();
					TThread::Synchronize(nullptr, [=](){ ProcessMove(line); });
				} catch(...) { return; }
			}
		})->Start();
	} catch (...) {}
}

// ...........................................................................

void __fastcall TForm2::FormPaint(TObject *Sender) {
	if (BackgroundImage) Canvas->StretchDraw(ClientRect, BackgroundImage);
}

// ...........................................................................

void TForm2::LoadPNGToImage(TImage* img, const std::string& path) {
	if (!img) return;
	TPngImage *png = new TPngImage();
	try { png->LoadFromFile(path.c_str()); img->Picture->Assign(png); }
	catch (...) { img->Picture->Assign(NULL); }
	delete png;
}

