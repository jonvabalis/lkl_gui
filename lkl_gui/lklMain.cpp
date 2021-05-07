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
	EVT_RADIOBUTTON(10020, OnRadioClicked)
	EVT_RADIOBUTTON(10021, OnRadioClicked)
wxEND_EVENT_TABLE()

//EVT_BUTTON(10001, OnButton1Clicked)
//EVT_LISTBOX(10004, OnButton2Clicked)
//EVT_BUTTON(10002, OnButton2Clicked)

int KomandaListID;
int ZaidejoListID;
int KomandaID;
vector<int> KomanduID;

int VarzybaListID;
int VarzybaID;
vector<int> VarzybuID;
wxString VarzybaInfo;


wxString BeTarpu(wxString nice);
string BeEilutesLuzio(string nice);
void EiluciuSk(string failas, int &x);
void RungtyniuSk(string failas, int &rungtyniu_sk);
void ID_sk(string failas, int ID, int &x, int &ID_pradzia);
int Naudingumas(vector<Varzybos> VisosVarzybos, int kind, int zind, int x);
string Double1SkPoKablelio(double sk);
int Ind_varzybose(vector<Komandos> VisosKomandos, int kind, int zind, vector<Varzybos> VisosVarzybos, int vind);


lklMain::lklMain() : wxFrame(nullptr, wxID_ANY, L"Lietuvos krep\u0161inio lygos informacin\u0117 sistema", wxPoint(30, 30), wxSize(800, 750))
{
	//ikonele
	SetIcon(wxIcon("aaaaaaaa"));

	//background spalva
	SetBackgroundColour(wxColour(168, 240, 187));



	//------------------------------

	SkaitytiKomandos Komanda;
	vector<Komandos> VisosKomandos;

	Komanda.Skaityti("Komandos.txt", 0);
	Komanda.Skaityti("Treneriai.txt", 1);
	Komanda.Skaityti("Zaidejai.txt", 2);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		VisosKomandos.push_back(Komandos(Komanda.getPavadinimas(i)));

		VisosKomandos[i].setID(Komanda.getID(i));

		VisosKomandos[i].setTreneris(Komanda.getTreneris(i));

		for (int j = 0; j < Komanda.getKomandosZaidejaiSize(i); j++)
			VisosKomandos[i].setZaidejai(Komanda.getZaidejai(i, j));

		VisosKomandos[i].setZaidejaiSk(Komanda.getKomandosZaidejaiSize(i));
	}

	//------------------------------




	//meniu eilute
	wxMenu *fileMenu = new wxMenu;
	wxMenu *helpMenu = new wxMenu;
	wxMenu *iterpimasMenu = new wxMenu;
	wxMenu *redagavimasMenu = new wxMenu;
	wxMenu *pasalinimasMenu = new wxMenu;

	helpMenu->Append(wxID_ABOUT, wxT("&Apie...\tF1"),
		wxT("Kad su\u017Einotum daugiau naudingos informacijos"));

	fileMenu->Append(wxID_EXIT, wxT("&Atsisveikinti\tAlt - X"),
		wxT("Atsisveikinti su programos langu"));

	iterpimasMenu->Append(10031, wxT("&\u012eterpti komandas"),
		wxT("\u012eterpti komandas"));
	
	iterpimasMenu->Append(10032, wxT("&\u012eterpti \u017eaid\u0117jus"),
		wxT("\u012eterpti \u017eaid\u0117jus"));

	iterpimasMenu->Append(10033, wxT("&\u012eterpti var\u017eybas"),
		wxT("\u012eterpti var\u017eybas"));

	pasalinimasMenu->Append(10041, wxT("&Pa\u0161alinti komandas"),
		wxT("Pa\u0161alinti komandas"));

	pasalinimasMenu->Append(10042, wxT("&Pa\u0161alinti \u017eaid\u0117jus"),
		wxT("Pa\u0161alinti \u017eaid\u0117jus"));

	pasalinimasMenu->Append(10043, wxT("&Pa\u0161alinti var\u017eybas"),
		wxT("Pa\u0161alinti var\u017eybas"));

	redagavimasMenu->Append(10051, wxT("&Redaguoti komandas"),
		wxT("Redaguoti komandas"));



	wxMenuBar *menuBar = new wxMenuBar();
	menuBar->Append(fileMenu, wxT("&Failas"));
	menuBar->Append(iterpimasMenu, wxT("&\u012eterpimas"));
	menuBar->Append(redagavimasMenu, wxT("&Redagavimas"));
	menuBar->Append(pasalinimasMenu, wxT("&Pa\u0161alinimas"));
	menuBar->Append(helpMenu, wxT("&Pagalba"));

	//prikabinti menu
	SetMenuBar(menuBar);

	// statuso eilute
	CreateStatusBar(2);
	SetStatusText(wxT("Naudojiesi Lietuvos krep\u0161inio lygos informacine sistema!"));



	SetFont(wxFont(32, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));

	
	m_titulinisText1 = new wxStaticText(this, -1, L"Sveiki atvyk\u0119!");
	m_titulinisText2 = new wxStaticText(this, -1, L"Pasirinkite k\u0105 norite daryti:");



	SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	//m_titulinisTextCtrl = new wxTextCtrl(this, wxID_ANY);// SetSize(300, -1));

	m_radioKomandos = new wxRadioButton(this, 10020, L"\u017di\u016Br\u0117ti komandas", wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
	m_radioVarzybos = new wxRadioButton(this, 10021, L"\u017di\u016Br\u0117ti var\u017eybas", wxDefaultPosition, wxDefaultSize, 0);
	m_radioKomandos->SetValue(true);

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


	wxSizer *TitulinisRadio = new wxBoxSizer(wxHORIZONTAL);
	wxSizer *TitulinisRadio2 = new wxBoxSizer(wxHORIZONTAL);

	TitulinisRadio->Add(m_radioKomandos, 0, wxEXPAND | wxLEFT | wxRIGHT, 42);
	TitulinisRadio->Add(m_radioVarzybos, 0, wxEXPAND | wxLEFT | wxRIGHT, 42);

	TitulinisRadio2->Add(TitulinisRadio, 0, wxEXPAND | wxALL, 7);


	wxSizer *TitulinisTextCtrl = new wxBoxSizer(wxVERTICAL); //tipo TextCtrl, bet dabar jau wxChoice

	TitulinisTextCtrl->Add(TitulinisRadio2, 0, wxALIGN_CENTRE_HORIZONTAL);
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
	KomanduID.clear();

	//cia i wxChoice surasau krepsinio komandas, kurias galesiu rinktis
	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		wxKomanda = wxString::FromUTF8(VisosKomandos[i].getPavadinimas());

		m_komandaChoice->AppendString(wxKomanda);

		KomanduID.push_back(VisosKomandos[i].getID());
	}


	m_titulinisButton2->Connect(10002, wxEVT_BUTTON, wxCommandEventHandler(ZaidKomentaras::OnZaidejasClicked), nullptr, this);
}

ZaidKomentaras::ZaidKomentaras() : wxFrame(nullptr, wxID_ANY, L"Komentaras apie krep\u0161inink\u0105", wxPoint(30, 160), wxSize(855, 480))
{
	//ikonele
	SetIcon(wxIcon("aaaaaaaa"));

	//background spalva
	SetBackgroundColour(wxColour(99, 255, 140));


	wxString temp = L"\u017Daid\u0117jo ID: ";
	wxString temp2 = ", o komandos ID: ";
	temp << ZaidejoListID << temp2 << KomandaID;
	wxStaticText *m_txt = new wxStaticText(this, -1, temp);


	SkaitytiKomandos Komanda;
	vector<Komandos> VisosKomandos;

	Komanda.Skaityti("Komandos.txt", 0);
	Komanda.Skaityti("Treneriai.txt", 1);
	Komanda.Skaityti("Zaidejai.txt", 2);

	for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
	{
		VisosKomandos.push_back(Komandos(Komanda.getPavadinimas(i)));

		VisosKomandos[i].setID(Komanda.getID(i));

		VisosKomandos[i].setTreneris(Komanda.getTreneris(i));

		for (int j = 0; j < Komanda.getKomandosZaidejaiSize(i); j++)
			VisosKomandos[i].setZaidejai(Komanda.getZaidejai(i, j));

		VisosKomandos[i].setZaidejaiSk(Komanda.getKomandosZaidejaiSize(i));
	}

	SkaitytiVarzybos Varzyba;
	vector<Varzybos> VisosVarzybos;

	Varzyba.Skaityti("VarzybuKomandos.txt", "VarzybuDatos.txt", "VarzybuVietos.txt", "VarzybuRezultatai.txt");

	for (int i = 0; i < Varzyba.getPavadinimasSize(); i++)
	{
		//1 komandos pavadinimas
		//VisosVarzybos[i].setPavadinimas1(Varzyba.getPavadinimas1(i));
		VisosVarzybos.push_back(Varzybos(Varzyba.getPavadinimas1(i)));

		//2komandos pavadinimas
		VisosVarzybos[i].setPavadinimas2(Varzyba.getPavadinimas2(i));

		//ID
		VisosVarzybos[i].setID(Varzyba.getID(i));

		//data
		VisosVarzybos[i].setData(Varzyba.getData(i));

		//vieta
		VisosVarzybos[i].setVieta(Varzyba.getVieta(i));

		//1 komandos zaidejai ir ju statistikos
		VisosVarzybos[i].setKomanda1(Varzyba.getKomanda1(i));

		//2 komandos zaidejai ir ju statistikos
		VisosVarzybos[i].setKomanda2(Varzyba.getKomanda2(i));
	}

	
	//konvertuoju i wxString kad programa suprastu lietuviskus simbolius
	stringZaidejas = wxString::FromUTF8(VisosKomandos[KomandaID].getZaidejai(ZaidejoListID));
	stringKomanda = wxString::FromUTF8(VisosKomandos[KomandaID].getPavadinimas());
	stringTreneris = wxString::FromUTF8(VisosKomandos[KomandaID].getTreneris());
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

	SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	StatistikaTable = new wxDataViewListCtrl(this, wxID_ANY);


	Komentaras = new wxBoxSizer(wxVERTICAL);
	KomentarasInfo = new wxBoxSizer(wxVERTICAL);

	//KomentarasInfo->Add(m_txt, 1, wxEXPAND | wxLEFT, 30);
	KomentarasInfo->Add(m_Zaidejas, 0, wxEXPAND | wxLEFT, 15);
	KomentarasInfo->Add(m_Komanda, 0, wxEXPAND | wxLEFT, 15);
	KomentarasInfo->Add(m_Treneris, 0, wxEXPAND | wxLEFT | wxBOTTOM, 15);
	KomentarasInfo->Add(m_Komentaras, 1, wxEXPAND | wxLEFT, 15);
	KomentarasInfo->Add(StatistikaTable, 1, wxEXPAND | wxLEFT, 15);

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


	wxVector<wxVariant> Lentele;

	StatistikaTable->AppendTextColumn("", wxDATAVIEW_CELL_INERT, 85, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn(L"Minut\u0117s", wxDATAVIEW_CELL_INERT, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("2PM%", wxDATAVIEW_CELL_INERT, 70, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("3PM%", wxDATAVIEW_CELL_INERT, 70, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("FTM%", wxDATAVIEW_CELL_INERT, 60, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("REB", wxDATAVIEW_CELL_INERT, 46, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("AS", wxDATAVIEW_CELL_INERT, 35, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("ST", wxDATAVIEW_CELL_INERT, 35, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("TO", wxDATAVIEW_CELL_INERT, 35, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("BS", wxDATAVIEW_CELL_INERT, 35, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("RBS", wxDATAVIEW_CELL_INERT, 46, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("PF", wxDATAVIEW_CELL_INERT, 35, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("RF", wxDATAVIEW_CELL_INERT, 35, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("PTS", wxDATAVIEW_CELL_INERT, 46, wxALIGN_CENTER);
	StatistikaTable->AppendTextColumn("EFF", wxDATAVIEW_CELL_INERT, 46, wxALIGN_CENTER);


	int ZaidejoDuom[18] = { 0 }, varzybuzaide = 0;

	for (int i = 0; i < Varzyba.getPavadinimasSize(); i++)
	{
		//int zind = Ind_varzybose(VisosKomandos, KomandaID, ZaidejoListID, VisosVarzybos, i);

		if (VisosKomandos[KomandaID].getPavadinimas() == VisosVarzybos[i].getPavadinimas1())
		{
			char minutes[2], sekundes[2];
			int zind = Ind_varzybose(VisosKomandos, KomandaID, ZaidejoListID, VisosVarzybos, i);

			if (zind != -69)//jei zaidejas nedalyvavo rungtynese
			{
				minutes[0] = VisosVarzybos[i].getKomandaInfo1(zind, 1)[0];
				if (VisosVarzybos[i].getKomandaInfo1(zind, 1)[1] != ':')
					minutes[1] = VisosVarzybos[i].getKomandaInfo1(zind, 1)[1];

				if (VisosVarzybos[i].getKomandaInfo1(zind, 1)[1] != ':')
				{
					sekundes[0] = VisosVarzybos[i].getKomandaInfo1(zind, 1)[3];
					sekundes[1] = VisosVarzybos[i].getKomandaInfo1(zind, 1)[4];
				}
				else if (VisosVarzybos[i].getKomandaInfo1(zind, 1)[1] == ':')
				{
					sekundes[0] = VisosVarzybos[i].getKomandaInfo1(zind, 1)[2];
					sekundes[1] = VisosVarzybos[i].getKomandaInfo1(zind, 1)[3];
				}

				ZaidejoDuom[0] += 60 * stoi(minutes);
				ZaidejoDuom[1] += stoi(sekundes);

				for (int j = 2; j < 17; j++)
				{
					ZaidejoDuom[j] += stoi(VisosVarzybos[i].getKomandaInfo1(zind, j));
				}

				ZaidejoDuom[17] += Naudingumas(VisosVarzybos, i, zind, 0);

				varzybuzaide++;
			}
		}
		if (VisosKomandos[KomandaID].getPavadinimas() == VisosVarzybos[i].getPavadinimas2())
		{
			char minutes[2], sekundes[2];
			int zind = Ind_varzybose(VisosKomandos, KomandaID, ZaidejoListID, VisosVarzybos, i); //WTF???

			if (zind != -69)
			{
				minutes[0] = VisosVarzybos[i].getKomandaInfo2(zind, 1)[0];
				if (VisosVarzybos[i].getKomandaInfo2(zind, 1)[1] != ':')
					minutes[1] = VisosVarzybos[i].getKomandaInfo2(zind, 1)[1];

				if (VisosVarzybos[i].getKomandaInfo2(zind, 1)[1] != ':')
				{
					sekundes[0] = VisosVarzybos[i].getKomandaInfo2(zind, 1)[3];
					sekundes[1] = VisosVarzybos[i].getKomandaInfo2(zind, 1)[4];
				}
				else if (VisosVarzybos[i].getKomandaInfo2(zind, 1)[1] == ':')
				{
					sekundes[0] = VisosVarzybos[i].getKomandaInfo2(zind, 1)[2];
					sekundes[1] = VisosVarzybos[i].getKomandaInfo2(zind, 1)[3];
				}

				ZaidejoDuom[0] += 60 * stoi(minutes);
				ZaidejoDuom[1] += stoi(sekundes);

				for (int j = 2; j < 17; j++)
				{
					ZaidejoDuom[j] += stoi(VisosVarzybos[i].getKomandaInfo2(zind, j));
				}

				ZaidejoDuom[17] += Naudingumas(VisosVarzybos, i, zind, 1);

				varzybuzaide++;
			}
		}
	}


	Lentele.clear();

	Lentele.push_back(wxVariant("Vidurkiai"));

	if (varzybuzaide != 0)
	{
		//minutes
		if ((ZaidejoDuom[0] + ZaidejoDuom[1]) / varzybuzaide % 60 < 10)
			Lentele.push_back(wxVariant(to_string((ZaidejoDuom[0] + ZaidejoDuom[1]) / varzybuzaide / 60) + ":0" + to_string((ZaidejoDuom[0] + ZaidejoDuom[1]) / varzybuzaide % 60)));
		else Lentele.push_back(wxVariant(to_string((ZaidejoDuom[0] + ZaidejoDuom[1]) / varzybuzaide / 60) + ':' + to_string((ZaidejoDuom[0] + ZaidejoDuom[1]) / varzybuzaide % 60)));

		//2PM-A
		if (ZaidejoDuom[3] != 0)
			Lentele.push_back(wxVariant(to_string(ZaidejoDuom[2] * 100 / ZaidejoDuom[3]) + '%'));
		else Lentele.push_back(wxVariant("0%"));
		//3PM-A
		if (ZaidejoDuom[5] != 0)
			Lentele.push_back(wxVariant(to_string(ZaidejoDuom[4] * 100 / ZaidejoDuom[5]) + '%'));
		else Lentele.push_back(wxVariant("0%"));
		//FTM-A
		if (ZaidejoDuom[7] != 0)
			Lentele.push_back(wxVariant(to_string(ZaidejoDuom[6] * 100 / ZaidejoDuom[7]) + '%'));
		else Lentele.push_back(wxVariant("0%"));
		//REB
		Lentele.push_back(wxVariant(Double1SkPoKablelio((double)ZaidejoDuom[8] / varzybuzaide)));
		//AS
		Lentele.push_back(wxVariant(Double1SkPoKablelio((double)ZaidejoDuom[9] / varzybuzaide)));
		//ST
		Lentele.push_back(wxVariant(Double1SkPoKablelio((double)ZaidejoDuom[10] / varzybuzaide)));
		//TO
		Lentele.push_back(wxVariant(Double1SkPoKablelio((double)ZaidejoDuom[11] / varzybuzaide)));
		//BS
		Lentele.push_back(wxVariant(Double1SkPoKablelio((double)ZaidejoDuom[12] / varzybuzaide)));
		//RBS
		Lentele.push_back(wxVariant(Double1SkPoKablelio((double)ZaidejoDuom[13] / varzybuzaide)));
		//PF
		Lentele.push_back(wxVariant(Double1SkPoKablelio((double)ZaidejoDuom[14] / varzybuzaide)));
		//RF
		Lentele.push_back(wxVariant(Double1SkPoKablelio((double)ZaidejoDuom[15] / varzybuzaide)));
		//PTS
		Lentele.push_back(wxVariant(Double1SkPoKablelio((double)ZaidejoDuom[16] / varzybuzaide)));
		//EFF
		Lentele.push_back(wxVariant(Double1SkPoKablelio((double)ZaidejoDuom[17] / varzybuzaide)));
	}
	else
		for (int i = 0; i < 14; i++)
			Lentele.push_back(wxVariant("-"));

	StatistikaTable->AppendItem(Lentele);
	/*for (int i = 0; i < VisosVarzybos[VarzybaID].getKomandaSk1(); i++)
	{
		Lentele.clear();

		//zaidejas
		Lentele.push_back(wxVariant(wxString::FromUTF8(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 0))));
		//minutes
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 1)));
		//2PM-A
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 2) + '-' + VisosVarzybos[VarzybaID].getKomandaInfo1(i, 3)));
		//3PM-A
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 4) + '-' + VisosVarzybos[VarzybaID].getKomandaInfo1(i, 5)));
		//FTM-A
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 6) + '-' + VisosVarzybos[VarzybaID].getKomandaInfo1(i, 7)));
		//REB
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 8)));
		//AS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 9)));
		//ST
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 10)));
		//TO
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 11)));
		//BS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 12)));
		//RBS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 13)));
		//PF
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 14)));
		//RF
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 15)));
		//PTS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 16)));
		//EFF
		Lentele.push_back(wxVariant(to_string(Naudingumas(VisosVarzybos, VarzybaID, i, 0))));

		StatistikaTable->AppendItem(Lentele);
	}*/


}

VarzybaFrame::VarzybaFrame() : wxFrame(nullptr, wxID_ANY, L"Var\u017eyb\u0173 protokolas apie krep\u0161ininkus", wxPoint(30, 30), wxSize(1400, 985))
{
	//ikonele
	SetIcon(wxIcon("aaaaaaaa"));

	//background spalva
	SetBackgroundColour(wxColour(17, 209, 39));


	wxString temp = L"Var\u017eyb\u0173 ID: ";
	temp << VarzybaID;
	wxStaticText *m_txt = new wxStaticText(this, -1, temp);


	SkaitytiVarzybos Varzyba;
	vector<Varzybos> VisosVarzybos;

	Varzyba.Skaityti("VarzybuKomandos.txt", "VarzybuDatos.txt", "VarzybuVietos.txt", "VarzybuRezultatai.txt");

	for (int i = 0; i < Varzyba.getPavadinimasSize(); i++)
	{
		//1 komandos pavadinimas
		//VisosVarzybos[i].setPavadinimas1(Varzyba.getPavadinimas1(i));
		VisosVarzybos.push_back(Varzybos(Varzyba.getPavadinimas1(i)));

		//2komandos pavadinimas
		VisosVarzybos[i].setPavadinimas2(Varzyba.getPavadinimas2(i));

		//ID
		VisosVarzybos[i].setID(Varzyba.getID(i));

		//data
		VisosVarzybos[i].setData(Varzyba.getData(i));

		//vieta
		VisosVarzybos[i].setVieta(Varzyba.getVieta(i));

		//1 komandos zaidejai ir ju statistikos
		VisosVarzybos[i].setKomanda1(Varzyba.getKomanda1(i));

		//2 komandos zaidejai ir ju statistikos
		VisosVarzybos[i].setKomanda2(Varzyba.getKomanda2(i));
	}

	//kad rasciau rungtyniu zaideja
	int max_eff = Naudingumas(VisosVarzybos, VarzybaID, 0, 0), komandos_ind = 0, zaidejo_ind = 0;

	for (int i = 0; i < VisosVarzybos[VarzybaID].getKomandaSk1(); i++)
	{
		if (max_eff < Naudingumas(VisosVarzybos, VarzybaID, i, 0))
		{
			max_eff = Naudingumas(VisosVarzybos, VarzybaID, i, 0);
			komandos_ind = 0;
			zaidejo_ind = i;
		}
	}
	for (int i = 0; i < VisosVarzybos[VarzybaID].getKomandaSk2(); i++)
	{
		if (max_eff < Naudingumas(VisosVarzybos, VarzybaID, i, 1))
		{
			max_eff = Naudingumas(VisosVarzybos, VarzybaID, i, 1);
			komandos_ind = 1;
			zaidejo_ind = i;
		}
	}

	//konvertuoju i wxString kad programa suprastu lietuviskus simbolius
	stringKomanda1 = wxString::FromUTF8(VisosVarzybos[VarzybaID].getPavadinimas1());
	stringKomanda2 = wxString::FromUTF8(VisosVarzybos[VarzybaID].getPavadinimas2());
	stringData = wxString::FromUTF8(VisosVarzybos[VarzybaID].getData());
	stringVieta = wxString::FromUTF8(VisosVarzybos[VarzybaID].getVieta());


	SetFont(wxFont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	m_VarzybaInfo = new wxStaticText(this, -1, VarzybaInfo);


	SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	m_Data = new wxStaticText(this, -1, "Data: " + stringData);
	m_Vieta = new wxStaticText(this, -1, "Vieta: " + stringVieta);

	if (komandos_ind == 0)
	{
		m_RungtyniuZaidejas = new wxStaticText(this, -1, L"Rungtyni\u0173 \u017eaid\u0117jas: " + wxString::FromUTF8(VisosVarzybos[VarzybaID].getKomandaInfo1(zaidejo_ind, 0)));

		SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL));
		m_RungtyniuZaidejasInfo = new wxStaticText(this, -1, VisosVarzybos[VarzybaID].getKomandaInfo1(zaidejo_ind, 16) + " ta\u0161kai, " +
			VisosVarzybos[VarzybaID].getKomandaInfo1(zaidejo_ind, 8) + " atk. kam., " +
			VisosVarzybos[VarzybaID].getKomandaInfo1(zaidejo_ind, 9) + " rez. perd. ir " +
			to_string(Naudingumas(VisosVarzybos, VarzybaID, zaidejo_ind, 0)) + " naud. balai");
	}
	if (komandos_ind == 1)
	{
		m_RungtyniuZaidejas = new wxStaticText(this, -1, L"Rungtyni\u0173 \u017eaid\u0117jas: " + wxString::FromUTF8(VisosVarzybos[VarzybaID].getKomandaInfo2(zaidejo_ind, 0)));

		SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL));
		m_RungtyniuZaidejasInfo = new wxStaticText(this, -1, VisosVarzybos[VarzybaID].getKomandaInfo2(zaidejo_ind, 16) + " ta\u0161kai, " +
			VisosVarzybos[VarzybaID].getKomandaInfo2(zaidejo_ind, 8) + " atk. kam., " +
			VisosVarzybos[VarzybaID].getKomandaInfo2(zaidejo_ind, 9) + " rez. perd. ir " +
			to_string(Naudingumas(VisosVarzybos, VarzybaID, zaidejo_ind, 1)) + " naud. balai");
	}

	/*SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL));
	m_Komentaras = new wxStaticText(this, -1, stringKomentaras);
	m_Komentaras->Wrap(m_Komentaras->GetClientSize().x);*/

	SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	m_Komanda1 = new wxStaticText(this, -1, stringKomanda1);
	SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	KomandaTable1 = new wxDataViewListCtrl(this, wxID_ANY);

	SetFont(wxFont(16, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	m_Komanda2 = new wxStaticText(this, -1, stringKomanda2);
	SetFont(wxFont(12, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	KomandaTable2 = new wxDataViewListCtrl(this, wxID_ANY);


	VarzybaSizer = new wxBoxSizer(wxVERTICAL);
	VarzybaSizer2 = new wxBoxSizer(wxVERTICAL);
	VarzybaSizer3 = new wxBoxSizer(wxVERTICAL);
	VarzybaSizer4 = new wxBoxSizer(wxVERTICAL);

	VarzybaSizer2->Add(m_VarzybaInfo, 0, wxEXPAND | wxLEFT | wxTOP, 30);
	VarzybaSizer2->Add(m_Data, 0, wxEXPAND | wxLEFT, 30);
	VarzybaSizer2->Add(m_Vieta, 1, wxEXPAND | wxLEFT, 30);

	VarzybaSizer3->Add(m_RungtyniuZaidejas, 1, wxLEFT, 15);
	VarzybaSizer3->Add(m_RungtyniuZaidejasInfo, 1, wxLEFT, 15);

	VarzybaSizer4->Add(m_Komanda1, 0, wxEXPAND | wxLEFT | wxTOP, 15);
	VarzybaSizer4->Add(KomandaTable1, 1, wxEXPAND | wxLEFT | wxRIGHT, 15);
	VarzybaSizer4->Add(m_Komanda2, 0, wxEXPAND | wxLEFT | wxTOP, 15);
	VarzybaSizer4->Add(KomandaTable2, 1, wxEXPAND | wxLEFT | wxRIGHT, 15);

	VarzybaSizer->Add(VarzybaSizer2, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxBOTTOM, 15);
	VarzybaSizer->Add(VarzybaSizer3, 0, wxEXPAND | wxLEFT, 30);
	VarzybaSizer->Add(VarzybaSizer4, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 30);
	this->SetSizer(VarzybaSizer);


	wxVector<wxVariant> Lentele;

	KomandaTable1->AppendTextColumn(L"\u017Daid\u0117jas", wxDATAVIEW_CELL_INERT, 185);
	KomandaTable1->AppendTextColumn(L"Minut\u0117s", wxDATAVIEW_CELL_INERT, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("2PM-A", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("3PM-A", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("FTM-A", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("REB", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("AS", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("ST", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("TO", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("BS", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("RBS", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("PF", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("RF", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("PTS", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable1->AppendTextColumn("EFF", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);


	for (int i = 0; i < VisosVarzybos[VarzybaID].getKomandaSk1(); i++)
	{
		Lentele.clear();
		
		//zaidejas
		Lentele.push_back(wxVariant(wxString::FromUTF8(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 0))));
		//minutes
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 1)));
		//2PM-A
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 2) + '-' + VisosVarzybos[VarzybaID].getKomandaInfo1(i, 3)));
		//3PM-A
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 4) + '-' + VisosVarzybos[VarzybaID].getKomandaInfo1(i, 5)));
		//FTM-A
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 6) + '-' + VisosVarzybos[VarzybaID].getKomandaInfo1(i, 7)));
		//REB
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 8)));
		//AS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 9)));
		//ST
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 10)));
		//TO
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 11)));
		//BS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 12)));
		//RBS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 13)));
		//PF
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 14)));
		//RF
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 15)));
		//PTS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo1(i, 16)));
		//EFF
		Lentele.push_back(wxVariant(to_string(Naudingumas(VisosVarzybos, VarzybaID, i, 0))));

		KomandaTable1->AppendItem(Lentele);
	}

	KomandaTable2->AppendTextColumn(L"\u017Daid\u0117jas", wxDATAVIEW_CELL_INERT, 185);
	KomandaTable2->AppendTextColumn(L"Minut\u0117s", wxDATAVIEW_CELL_INERT, wxCOL_WIDTH_AUTOSIZE, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("2PM-A", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("3PM-A", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("FTM-A", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("REB", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("AS", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("ST", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("TO", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("BS", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("RBS", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("PF", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("RF", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("PTS", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);
	KomandaTable2->AppendTextColumn("EFF", wxDATAVIEW_CELL_INERT, -1, wxALIGN_CENTER);


	for (int i = 0; i < VisosVarzybos[VarzybaID].getKomandaSk2(); i++)
	{
		Lentele.clear();

		//zaidejas
		Lentele.push_back(wxVariant(wxString::FromUTF8(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 0))));
		//minutes
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 1)));
		//2PM-A
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 2) + '-' + VisosVarzybos[VarzybaID].getKomandaInfo2(i, 3)));
		//3PM-A
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 4) + '-' + VisosVarzybos[VarzybaID].getKomandaInfo2(i, 5)));
		//FTM-A
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 6) + '-' + VisosVarzybos[VarzybaID].getKomandaInfo2(i, 7)));
		//REB
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 8)));
		//AS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 9)));
		//ST
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 10)));
		//TO
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 11)));
		//BS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 12)));
		//RBS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 13)));
		//PF
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 14)));
		//RF
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 15)));
		//PTS
		Lentele.push_back(wxVariant(VisosVarzybos[VarzybaID].getKomandaInfo2(i, 16)));
		//EFF
		Lentele.push_back(wxVariant(to_string(Naudingumas(VisosVarzybos, VarzybaID, i, 1))));

		KomandaTable2->AppendItem(Lentele);
	}
}

lklMain::~lklMain()
{
}

void lklMain::OnKomandaChoice(wxCommandEvent &evt)
{
	m_titulinisList->Clear();

	
	if (m_radioKomandos->GetValue() == true)
	{
		SkaitytiKomandos Komanda;
		vector<Komandos> VisosKomandos;

		Komanda.Skaityti("Komandos.txt", 0);
		Komanda.Skaityti("Treneriai.txt", 1);
		Komanda.Skaityti("Zaidejai.txt", 2);

		for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
		{
			VisosKomandos.push_back(Komandos(Komanda.getPavadinimas(i)));

			VisosKomandos[i].setID(Komanda.getID(i));

			VisosKomandos[i].setTreneris(Komanda.getTreneris(i));

			for (int j = 0; j < Komanda.getKomandosZaidejaiSize(i); j++)
				VisosKomandos[i].setZaidejai(Komanda.getZaidejai(i, j));

			VisosKomandos[i].setZaidejaiSk(Komanda.getKomandosZaidejaiSize(i));
		}


		wxString wxName;

		KomandaListID = m_komandaChoice->GetSelection();
		KomandaID = KomanduID[KomandaListID];

		for (int i = 0; i < VisosKomandos[KomandaID].getZaidejaiSk(); i++)
		{
			wxName = wxString::FromUTF8(VisosKomandos[KomandaID].getZaidejai(i));

			m_titulinisList->AppendString(wxName);
		}
	}
	else if (m_radioVarzybos->GetValue() == true)
	{
		VarzybuID.clear();

		SkaitytiKomandos Komanda;
		vector<Komandos> VisosKomandos;

		Komanda.Skaityti("Komandos.txt", 0);

		for (int i = 0; i < Komanda.getPavadinimasSize(); i++)
		{
			VisosKomandos.push_back(Komandos(Komanda.getPavadinimas(i)));
		}

		SkaitytiVarzybos Varzyba;
		vector<Varzybos> VisosVarzybos;

		int komandosID = KomanduID[m_komandaChoice->GetSelection()];

		Varzyba.Skaityti("VarzybuKomandos.txt", "VarzybuDatos.txt", "VarzybuVietos.txt", "VarzybuRezultatai.txt");

		for (int i = 0; i < Varzyba.getPavadinimasSize(); i++)
		{
			//1 komandos pavadinimas
			//VisosVarzybos[i].setPavadinimas1(Varzyba.getPavadinimas1(i));
			VisosVarzybos.push_back(Varzybos(Varzyba.getPavadinimas1(i)));

			//2komandos pavadinimas
			VisosVarzybos[i].setPavadinimas2(Varzyba.getPavadinimas2(i));

			//ID
			VisosVarzybos[i].setID(Varzyba.getID(i));

			//data
			//VisosVarzybos[i].setData(Varzyba.getData(i));

			//vieta
			//VisosVarzybos[i].setVieta(Varzyba.getVieta(i));

			//1 komandos zaidejai ir ju statistikos
			VisosVarzybos[i].setKomanda1(Varzyba.getKomanda1(i));

			//2 komandos zaidejai ir ju statistikos
			VisosVarzybos[i].setKomanda2(Varzyba.getKomanda2(i));
		}
		
		for (int i = 0; i < Varzyba.getPavadinimasSize(); i++)
		{
			if (VisosKomandos[komandosID].getPavadinimas() == VisosVarzybos[i].getPavadinimas1())
			{
				int rez1 = 0, rez2 = 0;

				for (int j = 0; j < VisosVarzybos[i].getKomandaSk1(); j++)
				{
					rez1 += stoi(VisosVarzybos[i].getKomandaInfo1(j, 16));
				}
				for (int j = 0; j < VisosVarzybos[i].getKomandaSk2(); j++)
				{
					rez2 += stoi(VisosVarzybos[i].getKomandaInfo2(j, 16));
				}
				
				VarzybuID.push_back(VisosVarzybos[i].getID());
				m_titulinisList->AppendString(wxString::FromUTF8(VisosVarzybos[i].getPavadinimas1() + ' ' + to_string(rez1) + ':' + to_string(rez2) + ' ' + VisosVarzybos[i].getPavadinimas2()));
			}

			if (VisosKomandos[komandosID].getPavadinimas() == VisosVarzybos[i].getPavadinimas2())
			{
				int rez1 = 0, rez2 = 0;

				for (int j = 0; j < VisosVarzybos[i].getKomandaSk1(); j++)
				{
					rez1 += stoi(VisosVarzybos[i].getKomandaInfo1(j, 16));
				}
				for (int j = 0; j < VisosVarzybos[i].getKomandaSk2(); j++)
				{
					rez2 += stoi(VisosVarzybos[i].getKomandaInfo2(j, 16));
				}

				VarzybuID.push_back(VisosVarzybos[i].getID());
				m_titulinisList->AppendString(wxString::FromUTF8(VisosVarzybos[i].getPavadinimas1() + ' ' + to_string(rez1) + ':' + to_string(rez2) + ' ' + VisosVarzybos[i].getPavadinimas2()));
			}
		}
	}

	Layout();
	Refresh();
	Update();

	evt.Skip();
}
void lklMain::OnRadioClicked(wxCommandEvent &evt)
{
	m_titulinisList->Clear();
	m_komandaChoice->SetSelection(-1);


	SkaitytiVarzybos Varzyba;
	vector<Varzybos> VisosVarzybos;

	if (m_radioVarzybos->GetValue() == true)
	{
		VarzybuID.clear();

		m_titulinisButton2->Disconnect(10002, wxEVT_BUTTON, wxCommandEventHandler(ZaidKomentaras::OnZaidejasClicked), nullptr, this);
		m_titulinisButton2->Connect(10002, wxEVT_BUTTON, wxCommandEventHandler(VarzybaFrame::OnVarzybaClicked), nullptr, this);

		Varzyba.Skaityti("VarzybuKomandos.txt", "VarzybuDatos.txt", "VarzybuVietos.txt", "VarzybuRezultatai.txt");

		for (int i = 0; i < Varzyba.getPavadinimasSize(); i++)
		{
			//1 komandos pavadinimas
			//VisosVarzybos[i].setPavadinimas1(Varzyba.getPavadinimas1(i));
			VisosVarzybos.push_back(Varzybos(Varzyba.getPavadinimas1(i)));

			//2komandos pavadinimas
			VisosVarzybos[i].setPavadinimas2(Varzyba.getPavadinimas2(i));

			//ID
			VisosVarzybos[i].setID(Varzyba.getID(i));

			//data
			VisosVarzybos[i].setData(Varzyba.getData(i));

			//vieta
			VisosVarzybos[i].setVieta(Varzyba.getVieta(i));

			//1 komandos zaidejai ir ju statistikos
			VisosVarzybos[i].setKomanda1(Varzyba.getKomanda1(i));

			//2 komandos zaidejai ir ju statistikos
			VisosVarzybos[i].setKomanda2(Varzyba.getKomanda2(i));
		}
		

		for (int i = 0; i < Varzyba.getPavadinimasSize(); i++)
		{
			int rez1 = 0, rez2 = 0;


			for (int j = 0; j < VisosVarzybos[i].getKomandaSk1(); j++)
			{
				rez1 += stoi(VisosVarzybos[i].getKomandaInfo1(j, 16));
			}
			for (int j = 0; j < VisosVarzybos[i].getKomandaSk2(); j++)
			{
				rez2 += stoi(VisosVarzybos[i].getKomandaInfo2(j, 16));
			}

			VarzybuID.push_back(VisosVarzybos[i].getID());
			m_titulinisList->AppendString(wxString::FromUTF8(VisosVarzybos[i].getPavadinimas1() + ' ' + to_string(rez1) + ':' + to_string(rez2) + ' ' + VisosVarzybos[i].getPavadinimas2()));
		}
	}
	else if (m_radioKomandos->GetValue() == true)
	{
		m_titulinisButton2->Disconnect(10002, wxEVT_BUTTON, wxCommandEventHandler(VarzybaFrame::OnVarzybaClicked), nullptr, this);
		m_titulinisButton2->Connect(10002, wxEVT_BUTTON, wxCommandEventHandler(ZaidKomentaras::OnZaidejasClicked), nullptr, this);
	}

	evt.Skip();
}
void lklMain::OnButton1Clicked(wxCommandEvent &evt)
{
	if (m_radioKomandos->GetValue() == true)
	{
		ZaidejoListID = m_titulinisList->GetSelection();

		wxString temp = "GetSelection() returns: ";
		temp << ZaidejoListID;
		wxStaticText *m_txt = new wxStaticText(this, -1, temp);
		//m_titulinisList->AppendString(temp);
	}
	else if (m_radioVarzybos->GetValue() == true)
	{
		VarzybaListID = m_titulinisList->GetSelection();
		VarzybaID = VarzybuID[VarzybaListID];
		VarzybaInfo = m_titulinisList->GetString(VarzybaListID);

		wxString temp = "GetString() var\u017eyboms returns: ";
		temp << VarzybaID << ", " << VarzybaInfo;
		wxStaticText *m_txt = new wxStaticText(this, -1, temp);
	}

	evt.Skip();
}
/*void lklMain::OnButton2Clicked(wxCommandEvent &evt)
{
	//m_titulinisList->Clear();

	ZaidejoListID = m_titulinisList->GetSelection();

	wxString temp = "GetSelection() returns: ";
	temp << ZaidejoListID;
	wxStaticText *m_txt = new wxStaticText(this, -1, temp);
	//m_titulinisList->AppendString(temp);

	evt.Skip();
}*/
void lklMain::OnZaidejasKeistiID(wxCommandEvent &evt)
{
	ZaidejoListID = m_titulinisList->GetSelection();
	evt.Skip();
}

void ZaidKomentaras::OnZaidejasClicked(wxCommandEvent &evt)
{
	m_frameKomentaras = new ZaidKomentaras();
	m_frameKomentaras->Show(true);

	evt.Skip();
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

void VarzybaFrame::OnVarzybaClicked(wxCommandEvent &evt)
{
	m_frameVarzyba = new VarzybaFrame();
	m_frameVarzyba->Show(true);

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
void EiluciuSk(string failas, int &x)
{
	string nice;
	x = 0;

	ifstream fdk(failas);

	while (getline(fdk, nice))
	{
		x++;
	}

	fdk.close();
}
void RungtyniuSk(string failas, int &rungtyniu_sk)
{
	string nice, nice2;
	int ind = -1, visoEil;
	rungtyniu_sk = 0;

	EiluciuSk(failas, visoEil);
	ifstream fdk1(failas);

	for (int i = 0; i < visoEil; i++)
	{
		getline(fdk1, nice, '|');

		nice2 = "";
		for (size_t j = 0; j < nice.size(); j++)
			if (nice[j] != '\n')
				nice2 += nice[j];

		if (stoi(nice2) != ind)
		{
			rungtyniu_sk++;
			ind = stoi(nice2);
		}

		for (int j = 0; j < 18; j++)
			getline(fdk1, nice, '|');
	}

	fdk1.close();
}
void ID_sk(string failas, int ID, int &x, int &ID_pradzia)
{
	string nice, nice2;
	int visoEil, arjau = 0;
	x = 0;

	EiluciuSk(failas, visoEil);
	ifstream fdk2(failas);

	for (int i = 0; i < visoEil; i++)
	{
		getline(fdk2, nice, '|');

		nice2 = "";
		for (size_t j = 0; j < nice.size(); j++)
			if (nice[j] != '\n')
				nice2 += nice[j];

		if (stoi(nice2) == ID && arjau == 0)
		{
			ID_pradzia = i;
			arjau = 1;
		}

		if (stoi(nice2) == ID)
			x++;

		for (int j = 0; j < 18; j++)
			getline(fdk2, nice, '|');
	}

	fdk2.close();
}
int Naudingumas(vector<Varzybos> VisosVarzybos, int kind, int zind, int x)
{
	int EFF;

	if (x == 0)
	{
		EFF = stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 16)) -
			(stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 3)) - stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 2))) -
			(stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 5)) - stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 4))) -
			(stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 7)) - stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 6))) +
			stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 8)) +
			stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 9)) +
			stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 10)) -
			stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 11)) +
			stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 12)) -
			stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 13)) -
			stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 14)) +
			stoi(VisosVarzybos[kind].getKomandaInfo1(zind, 15));
	}
	if (x == 1)
	{
		EFF = stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 16)) -
			(stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 3)) - stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 2))) -
			(stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 5)) - stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 4))) -
			(stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 7)) - stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 6))) +
			stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 8)) +
			stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 9)) +
			stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 10)) -
			stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 11)) +
			stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 12)) -
			stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 13)) -
			stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 14)) +
			stoi(VisosVarzybos[kind].getKomandaInfo2(zind, 15));
	}

	return EFF;
}
string Double1SkPoKablelio(double sk)
{
	ostringstream sstream;
	string nice, nice2;

	sstream << fixed << setprecision(1) << sk;
	nice = sstream.str();
	sstream.clear();

	return nice;
}
int Ind_varzybose(vector<Komandos> VisosKomandos, int kind, int zind, vector<Varzybos> VisosVarzybos, int vind)
{
	int varzzind = -69; //zaidejo indeksas varzybose

	string komanda = VisosKomandos[kind].getPavadinimas();
	string zaidejas = VisosKomandos[kind].getZaidejai(zind);


	if (komanda == VisosVarzybos[vind].getPavadinimas1())
	{
		for (int i = 0; i < VisosVarzybos[vind].getKomandaSk1(); i++)
		{
			if (VisosVarzybos[vind].getKomandaInfo1(i, 0) == zaidejas)
			{
				varzzind = i;
				i = VisosVarzybos[vind].getKomandaSk1() + 1;
			}
		}
	}
	else if (komanda == VisosVarzybos[vind].getPavadinimas2())
	{
		for (int i = 0; i < VisosVarzybos[vind].getKomandaSk2(); i++)
		{
			if (VisosVarzybos[vind].getKomandaInfo2(i, 0) == zaidejas)
			{
				varzzind = i;
				i = VisosVarzybos[vind].getKomandaSk2() + 1;
			}
		}
	}

	return varzzind;
}