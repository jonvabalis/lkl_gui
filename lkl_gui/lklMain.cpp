#include "lklMain.h"
#include <wx/icon.h>
#include <wx/intl.h>
#include <wx/listbox.h>
#include <wx/checkbox.h>




wxBEGIN_EVENT_TABLE(lklMain, wxFrame)
	EVT_MENU(wxID_ABOUT, OnAbout)
	EVT_MENU(wxID_EXIT, OnQuit)
	EVT_CHOICE(10003, OnKomandaChoice)
	EVT_BUTTON(10001, OnButton1Clicked)
wxEND_EVENT_TABLE()

//EVT_BUTTON(10001, OnButton1Clicked)
//EVT_LISTBOX(10004, OnButton2Clicked)
//EVT_BUTTON(10002, OnButton2Clicked)

int komandaID;
int ZaidejoListID;

wxString BeTarpu(wxString nice);
string BeEilutesLuzio(string nice);
wxString SSuVarnelePakeitimas(wxString nice);


lklMain::lklMain() : wxFrame(nullptr, wxID_ANY, L"Lietuvos krep\u0161inio lygos informacin\u0117 sistema", wxPoint(30, 30), wxSize(800, 700))
{
	//ikonele
	SetIcon(wxIcon("aaaaaaaa"));

	//background spalva
	SetBackgroundColour(wxColour(168, 240, 187));



	//------------------------------

	SkaitytiKomandos Komanda;
	vector<Komandos> VisosKomandos;


	Komanda.Skaityti("Komandos.txt", 0);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		VisosKomandos.push_back(Komandos(Komanda.getPavadinimas(i)));

	}
	

	Komanda.Skaityti("Treneriai.txt", 1);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		VisosKomandos[i].setTreneris(Komanda.getTreneris(i));
	}


	Komanda.Skaityti("Zaidejai.txt", 2);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		for (int j = 0; j < Komanda.getKomandosZaidejaiSize(i); j++)
		{
			// kazkodel apsikeite vietom del dvimacio vektorio nuskaitymo 227-229
			VisosKomandos[i].setZaidejai(Komanda.getZaidejai(i, j));
		}

		VisosKomandos[i].setZaidejaiSk(Komanda.getKomandosZaidejaiSize(i));
	}

	//------------------------------




	//meniu eilute
	wxMenu *fileMenu = new wxMenu;

	wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(wxID_ABOUT, wxT("&Apie...\tF1"),
		wxT("Kad su\u017Einotum daugiau naudingos informacijos"));

	fileMenu->Append(wxID_EXIT, wxT("&Atsisveikinti\tAlt - X"),
		wxT("Atsisveikinti su programos langu"));


	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, wxT("&Failas"));
	menuBar->Append(helpMenu, wxT("&Pagalba"));

	// ... and attach this menu bar to the frame
	SetMenuBar(menuBar);

	// statuso eilute
	CreateStatusBar(2);
	SetStatusText(wxT("Naudojiesi Lietuvos krep\u0161inio lygos informacine sistema!"));



	SetFont(wxFont(32, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	
	m_titulinisText1 = new wxStaticText(this, -1, L"Sveiki atvyk\u0119!");
	m_titulinisText2 = new wxStaticText(this, -1, L"Pasirinkite k\u0105 norite daryti:");



	SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	//m_titulinisTextCtrl = new wxTextCtrl(this, wxID_ANY);// SetSize(300, -1));

	m_komandaChoice = new wxChoice(this, 10003, wxDefaultPosition, wxSize(1920, 50));

	m_titulinisList = new wxListBox(this, 10004, wxDefaultPosition, wxSize(-1, 184));

	m_titulinisButton1 = new wxButton(this, 10001, L"Patvirtinti pasirinkim\u0105");
	m_titulinisButton2 = new wxButton(this, 10002, L"Rodyti informacij\u0105");



	wxBoxSizer *Titulinis = new wxBoxSizer(wxVERTICAL);
	wxSizer *TitulinisText = new wxBoxSizer(wxVERTICAL);

	TitulinisText->Add(m_titulinisText1, 0, wxALIGN_CENTRE_HORIZONTAL);
	TitulinisText->Add(m_titulinisText2, 0, wxALIGN_CENTRE_HORIZONTAL);

	Titulinis->Add(TitulinisText, 0, wxEXPAND | wxALL, 42);
	//TitulinisText->AddStretchSpacer(1);


	wxSizer *TitulinisTextCtrl = new wxBoxSizer(wxVERTICAL); //tipo TextCtrl, bet dabar jau wxChoice

	//m_titulinisTextCtrl->SetSize(690, -1);
	TitulinisTextCtrl->Add(m_komandaChoice, 0);// , wxEXPAND | wxBOTTOM, 20);//  wxEXPAND | wxBOTTOM  ;wxALIGN_CENTER_HORIZONTAL);
	


	//wxSizer *TitulinisList = new wxBoxSizer(wxVERTICAL);
	
	//TitulinisList->Add(m_titulinisTextCtrl, 2);// wxALIGN_CENTER_HORIZONTAL);
	TitulinisTextCtrl->Add(m_titulinisList, 1, wxEXPAND);// , 20 ?? wxALIGN_CENTER_HORIZONTAL, 20);
	
	Titulinis->Add(TitulinisTextCtrl, 1, wxEXPAND | wxLEFT | wxRIGHT, 42);
	
	//TitulinisList->Add(TitulinisTextCtrl, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 42);
	
	//Titulinis->Add(TitulinisTextCtrl, 1, wxEXPAND | wxLEFT | wxRIGHT, 42);
	//Titulinis->Add(TitulinisList, 1, wxEXPAND | wxRIGHT | wxLEFT, 42);


	/*wxSizer *TitulinisButton = new wxBoxSizer(wxHORIZONTAL);

	TitulinisButton->Add(m_titulinisButton1, 1, wxEXPAND | wxRIGHT, 20);
	TitulinisButton->Add(m_titulinisButton2, 1, wxEXPAND, 0);
	*/

	wxBoxSizer *TitulinisButtonGrid = new wxBoxSizer(wxHORIZONTAL);
	wxSizer *TitulinisButton = new wxBoxSizer(wxVERTICAL);

	TitulinisButton->Add(m_titulinisButton1, 1, wxEXPAND | wxLEFT, 300);
	TitulinisButton->Add(m_titulinisButton2, 1, wxEXPAND | wxLEFT, 300);

	TitulinisButtonGrid->Add(TitulinisButton, 1, wxEXPAND);// , 2, wxEXPAND | wxALL, 42);

	Titulinis->Add(TitulinisButtonGrid, 2, wxEXPAND | wxALL, 42);
	this->SetSizer(Titulinis);

	


	wxString wxKomanda;

	//cia i wxChoice surasau krepsinio komandas, kurias galesiu rinktis
	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		wxKomanda = wxString::FromUTF8(VisosKomandos[i].getPavadinimas());
		
		m_komandaChoice->AppendString(wxKomanda);
	}

	
	//ZaidejoListID = m_titulinisList->GetSelection();
	
	m_titulinisButton2->Connect(10002, wxEVT_BUTTON, wxCommandEventHandler(ZaidKomentaras::OnZaidejasClicked), nullptr, this);
}

ZaidKomentaras::ZaidKomentaras() : wxFrame(nullptr, wxID_ANY, L"Komentaras apie krep\u0161inink\u0105", wxPoint(30, 180), wxSize(800, 400))
{
	//ikonele
	SetIcon(wxIcon("aaaaaaaa"));

	//background spalva
	SetBackgroundColour(wxColour(99, 255, 140));


	//lklMain *lkl;

	wxString temp = "Zaidejo ID: ";
	wxString temp2 = ", o komandos ID: ";

	temp << ZaidejoListID << temp2 << komandaID;


	wxStaticText *m_txt = new wxStaticText(this, -1, temp);




	SkaitytiKomandos Komanda;
	vector<Komandos> VisosKomandos;


	Komanda.Skaityti("Komandos.txt", 0);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		VisosKomandos.push_back(Komandos(Komanda.getPavadinimas(i)));

	}

	Komanda.Skaityti("Treneriai.txt", 1);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		VisosKomandos[i].setTreneris(Komanda.getTreneris(i));
	}

	Komanda.Skaityti("Zaidejai.txt", 2);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		for (int j = 0; j < Komanda.getKomandosZaidejaiSize(i); j++)
		{
			// kazkodel apsikeite vietom del dvimacio vektorio nuskaitymo 227-229
			VisosKomandos[i].setZaidejai(Komanda.getZaidejai(i, j));
		}

		VisosKomandos[i].setZaidejaiSk(Komanda.getKomandosZaidejaiSize(i));
	}

	


	//konvertuoju i wxString kad programa suprastu lietuviskus simbolius
	stringZaidejas = wxString::FromUTF8(VisosKomandos[komandaID].getZaidejai(ZaidejoListID));
	stringKomanda = wxString::FromUTF8(VisosKomandos[komandaID].getPavadinimas());
	stringTreneris = wxString::FromUTF8(VisosKomandos[komandaID].getTreneris());
	//stringKomentaras = wxString::FromUTF8();


	ifstream fd("Komentarai.txt");

	//kad zaidejo reiksme nebutu panaudojama is naujo
	string nuskaitytas_vardas = "42069_nice";
	string nuskaitytas_komentaras = "ni46209ce";
	string nuskaitytas_bkomentaras = "ecin96";
	wxString tempZaidejas = BeTarpu(stringZaidejas);

	while (!fd.eof())
	{
		getline(fd, nuskaitytas_vardas, '|');

		if (wxString::FromUTF8(nuskaitytas_vardas) == tempZaidejas)
		{
			getline(fd, nuskaitytas_komentaras, '|');

			fd.ignore(80, '\n');

			break;
		}
		else
			getline(fd, nuskaitytas_bkomentaras, '|');
		fd.ignore(80, '\n');
	}
	fd.close();

	if(nuskaitytas_komentaras != "ni46209ce")
		stringKomentaras = wxString::FromUTF8(nuskaitytas_komentaras);
	else if(nuskaitytas_komentaras == "ni46209ce")
		stringKomentaras = L"Deja, bet komentaras apie \u0161\u012F krep\u0161inink\u0105 n\u0117ra prid\u0117tas. Nor\u0117tum\u0117te prid\u0117ti? ";



	SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	m_Zaidejas = new wxStaticText(this, -1, stringZaidejas);

	SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	m_Komanda = new wxStaticText(this, -1, "Komanda: " + stringKomanda);
	m_Treneris = new wxStaticText(this, -1, "Treneris: " + stringTreneris);

	SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL));
	m_Komentaras = new wxStaticText(this, -1, stringKomentaras);
	m_Komentaras->Wrap(m_Komentaras->GetClientSize().x);


	Komentaras = new wxBoxSizer(wxVERTICAL);
	KomentarasInfo = new wxBoxSizer(wxVERTICAL);

	//KomentarasInfo->Add(m_txt, 1, wxEXPAND | wxLEFT, 30);
	KomentarasInfo->Add(m_Zaidejas, 0, wxEXPAND | wxLEFT, 15);
	KomentarasInfo->Add(m_Komanda, 0, wxEXPAND | wxLEFT, 15);
	KomentarasInfo->Add(m_Treneris, 0, wxEXPAND | wxLEFT | wxBOTTOM, 15);
	KomentarasInfo->Add(m_Komentaras, 1, wxEXPAND | wxLEFT, 15);

	if (nuskaitytas_komentaras != "ni46209ce")
	{
		SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

		m_Redaguoti = new wxButton(this, 10010, "Redaguoti");
		m_RedaguotiCtrl = new wxTextCtrl(this, 10013, stringKomentaras);

		KomentarasInfo->Add(m_RedaguotiCtrl, 0, wxEXPAND | wxALL, 30);
		KomentarasInfo->Add(m_Redaguoti, 0, wxEXPAND | wxLEFT, 15);

		m_Redaguoti->Connect(10010, wxEVT_BUTTON, wxCommandEventHandler(ZaidKomentaras::OnRedaguotiClicked), nullptr, this);
	}
	else if (nuskaitytas_komentaras == "ni46209ce")
	{
		SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

		m_Prideti = new wxButton(this, 10011, L"Prid\u0117ti");
		m_PridetiCtrl = new wxTextCtrl(this, 10012);

		m_PridetiCtrl->SetHint(L"Komentar\u0105 ra\u0161ykite \u010Dia");

		KomentarasInfo->Add(m_PridetiCtrl, 0, wxEXPAND | wxALL, 30);
		KomentarasInfo->Add(m_Prideti, 0, wxEXPAND | wxLEFT, 15);

		m_Prideti->Connect(10011, wxEVT_BUTTON, wxCommandEventHandler(ZaidKomentaras::OnPridetiClicked), nullptr, this);
	}
	Komentaras->Add(KomentarasInfo, 1, wxEXPAND | wxALL, 30);
	this->SetSizer(Komentaras);


}


lklMain::~lklMain()
{
}

/*void lklMain::OnButton1Clicked(wxCommandEvent &evt)
{
	m_list1->AppendString(m_txt1->GetValue());
	evt.Skip();
}*/
/*void lklMain::OnTitulinisButton1Clicked(wxCommandEvent &evt)
{
	SkaitytiKomandos Komanda;
	vector<Komandos> VisosKomandos;


	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		//fr2 << VisosKomandos[i].getPavadinimas() << endl;


		m_titulinisList->AppendString(VisosKomandos[i].getPavadinimas());
	}

	evt.Skip();
}*/

void lklMain::OnKomandaChoice(wxCommandEvent &evt)
{
	m_titulinisList->Clear();

	SkaitytiKomandos Komanda;
	vector<Komandos> VisosKomandos;



	Komanda.Skaityti("Komandos.txt", 0);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		VisosKomandos.push_back(Komandos(Komanda.getPavadinimas(i)));
	}


	Komanda.Skaityti("Treneriai.txt", 1);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		VisosKomandos[i].setTreneris(Komanda.getTreneris(i));
	}


	Komanda.Skaityti("Zaidejai.txt", 2);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		for (int j = 0; j < Komanda.getKomandosZaidejaiSize(i); j++)
		{
			// kazkodel apsikeite vietom del dvimacio vektorio nuskaitymo 227-229
			VisosKomandos[i].setZaidejai(Komanda.getZaidejai(i, j));
		}

		VisosKomandos[i].setZaidejaiSk(Komanda.getKomandosZaidejaiSize(i));
	}



	wxString wxName;

	komandaID = m_komandaChoice->GetSelection();

	for (int i = 0; i < VisosKomandos[komandaID].getZaidejaiSk(); i++)
	{
		wxName = wxString::FromUTF8(VisosKomandos[komandaID].getZaidejai(i));

		m_titulinisList->AppendString(wxName);
	}

	Layout();
	Refresh();
	Update();

	evt.Skip();
}
void lklMain::OnButton1Clicked(wxCommandEvent &evt)
{
	ZaidejoListID = m_titulinisList->GetSelection();

	wxString temp = "GetSelection() returns: ";
	temp << ZaidejoListID;
	wxStaticText *m_txt = new wxStaticText(this, -1, temp);
	//m_titulinisList->AppendString(temp);

	evt.Skip();
}
void lklMain::OnButton2Clicked(wxCommandEvent &evt)
{
	//m_titulinisList->Clear();

	ZaidejoListID = m_titulinisList->GetSelection();

	wxString temp = "GetSelection() returns: ";
	temp << ZaidejoListID;
	wxStaticText *m_txt = new wxStaticText(this, -1, temp);
	//m_titulinisList->AppendString(temp);

	evt.Skip();
}
void lklMain::OnZaidejasKeistiID(wxCommandEvent &evt)
{
	ZaidejoListID = m_titulinisList->GetSelection();
	evt.Skip();
}
void ZaidKomentaras::OnZaidejasClicked(wxCommandEvent &evt)
{
	m_frameKomentaras = new ZaidKomentaras();
	m_frameKomentaras->Show(true);
}
void ZaidKomentaras::OnPridetiClicked(wxCommandEvent &evt)
{
	ofstream fr("Komentarai.txt", ios::app);
	
	wxString ivestas;
	ivestas = m_PridetiCtrl->GetValue();

	fr << BeTarpu(stringZaidejas).ToUTF8() << '|' << ivestas << " |\n";

	fr.close();
	m_Prideti->Enable(false);

	evt.Skip();
}
void ZaidKomentaras::OnRedaguotiClicked(wxCommandEvent &evt)
{
	ifstream fd("Komentarai.txt");
	ofstream fr("Komentarai2.txt");

	string tempeilute;
	string tempeilute2;
	int eilsk = 0;
	wxString neweilute = BeTarpu(stringZaidejas) << '|' << m_RedaguotiCtrl->GetValue() << " |\n";

	//padalinta i dvi dalis, nes getline() kaip nauja eilute kazkodel perskaitydavo ir '\n'
	while (getline(fd, tempeilute))
	{
		eilsk++;
	}
	fd.close();
	fd.open("Komentarai.txt");

	for (int i = 0; i < eilsk; i++)
	{
		getline(fd, tempeilute2, '|');
		if (BeEilutesLuzio(tempeilute2) == BeTarpu(stringZaidejas).ToUTF8())
		{
			getline(fd, tempeilute2, '|');
			fr << neweilute;
		}
		else if (BeEilutesLuzio(tempeilute2) != BeTarpu(stringZaidejas).ToUTF8())
		{
			fr << BeEilutesLuzio(tempeilute2) << '|';

			getline(fd, tempeilute2, '|');

			fr << BeEilutesLuzio(tempeilute2) << "|\n";
		}
	}

	fr.close();
	fd.close();

	remove("Komentarai.txt");
	rename("Komentarai2.txt", "Komentarai.txt");

	m_Redaguoti->Enable(false);

	evt.Skip();
}
void lklMain::OnAbout(wxCommandEvent& event) 
{
	wxString msg;

	msg.Printf(wxT("Sveikas krep\u0161ininke! Sukurta naudojant %s"),
		wxVERSION_STRING);

	wxMessageBox(msg, wxT("Apie program\u0105"),
		wxOK | wxICON_INFORMATION, this);
}

void lklMain::OnQuit(wxCommandEvent &event)
{// Destroyinam frame'a
	Close();
}
wxString BeTarpu(wxString nice)
{
	wxString be_tarpu;
	for (size_t i = 0; i < nice.length(); i++)
	{
		if (nice[i] != ' ')
			be_tarpu += nice[i];
	}
	return be_tarpu;
}
string BeEilutesLuzio(string nice)
{
	string be_luzio;
	for (size_t i = 0; i < nice.length(); i++)
	{
		if (nice[i] != '\n')
			be_luzio += nice[i];
	}
	return be_luzio;
}