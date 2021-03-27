#pragma once
#include "wx/wx.h"
#include <wx/simplebook.h>
#include <string>
#include <vector>
#include <fstream>
//#include <stdio.h>
#include <cstdio>

using namespace std;


class lklMain : public wxFrame
{
public:
	lklMain();
	~lklMain();


	//int ZaidejoListID;
	//int *pointeris = &ZaidejoListID;

	wxStaticText *m_titulinisText1;
	wxStaticText *m_titulinisText2;

	wxTextCtrl *m_titulinisTextCtrl;

	wxChoice *m_komandaChoice;

	wxListBox *m_titulinisList;

	wxButton *m_titulinisButton1;
	wxButton *m_titulinisButton2;



	/*wxButton *m_btn1 = nullptr;
	wxTextCtrl *m_txt1 = nullptr;
	wxListBox *m_list1 = nullptr;

	void OnButtonClicked(wxCommandEvent &evt);*/


	void OnQuit(wxCommandEvent &event);
	void OnAbout(wxCommandEvent& event);


	void OnTitulinisButton1Clicked(wxCommandEvent &evt);


	void OnKomandaChoice(wxCommandEvent &evt);
	void OnZaidejasKeistiID(wxCommandEvent &evt);

	void OnButton1Clicked(wxCommandEvent &evt);
	void OnButton2Clicked(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};
class ZaidKomentaras : public wxFrame
{
private:
	ZaidKomentaras *m_frameKomentaras = nullptr;

	wxBoxSizer *Komentaras;
	wxSizer *KomentarasInfo;

	wxStaticText *m_Zaidejas;
	wxString stringZaidejas;

	wxStaticText *m_Komanda;
	wxString stringKomanda;

	wxStaticText *m_Treneris;
	wxString stringTreneris;

	wxStaticText *m_Komentaras;
	wxString stringKomentaras;

	wxButton *m_Redaguoti;
	wxButton *m_Prideti;

	wxTextCtrl *m_RedaguotiCtrl;
	wxTextCtrl *m_PridetiCtrl;

public:
	ZaidKomentaras();

	void OnZaidejasClicked(wxCommandEvent &evt);
	void OnPridetiClicked(wxCommandEvent &evt);
	void OnRedaguotiClicked(wxCommandEvent &evt);

};





//--------------------------------------------------------------------
//																	 |
//--------------------------------------------------------------------


class SkaitytiKomandos
{
private:
	vector<string> PavadinimaiTemp;
	vector<string> TreneriaiTemp;
	vector<vector<string>> ZaidejaiTemp;
	//string ZaidejaiTemp[maxz][maxk]; // padaryti kad skaitytu vektoriun 222 eiluteje // skaito, nice
	vector<int> zaidSk;


public:
	void Skaityti(string failas, int x)
	{
		ifstream fd(failas);

		string szaidSk;
		string nuskaitytas;


		if (x == 0) // kai x == 0, nuskaitomos komandos
		{
			int i = 0;

			while (!fd.eof())
			{
				getline(fd, nuskaitytas);

				PavadinimaiTemp.push_back(nuskaitytas);

				i++;
			}
		}
		if (x == 1) // kai x == 1, nuskaitomi treneriai 
		{
			int i = 0;

			while (!fd.eof())
			{
				getline(fd, nuskaitytas);

				TreneriaiTemp.push_back(nuskaitytas);

				i++;
			}
		}
		if (x == 2) // kai x == 2, nuskaitomi zaidejai
		{
			int i = 0;

			while (!fd.eof())
			{
				getline(fd, szaidSk, ',');
				zaidSk.push_back(stoi(szaidSk)); // kad butu int, o ne string tipo

				vector<string> Nice;

				for (int j = 0; j < zaidSk[i]; j++)
				{
					getline(fd, nuskaitytas, ','); // padaryti kad skaitytu vektoriun

					Nice.push_back(nuskaitytas);
				}
				ZaidejaiTemp.push_back(Nice);
				fd.ignore(80, '\n');

				i++;
			}
		}

		fd.close();
	};

	string getPavadinimas(int i) {
		return this->PavadinimaiTemp[i];
	};
	string getTreneris(int i) {
		return this->TreneriaiTemp[i];
	};
	string getZaidejai(int j, int i) {
		return this->ZaidejaiTemp[j][i];
	}; // zaidejai j, komandos i
	int getPavadinimasSize() {
		return this->PavadinimaiTemp.size(); // cia tipo ziuriu kiek issaugota komandu pavadinimu, tai kiek viso komandu
	};
	int getKomandosZaidejaiSize(int i) {
		return zaidSk[i];
	};
};

class Komandos
{
private:
	string Treneris;
	vector<string> Zaidejai;
	string Pavadinimas;
	int zaidSk;

public:
	void Spausdinti();

	void setPavadinimas(string pavadinimas) {
		Pavadinimas = pavadinimas;
	};
	void setTreneris(string treneris) {
		Treneris = treneris;
	};
	void setZaidejai(string zaidejas) {
		Zaidejai.push_back(zaidejas);
	};
	void setZaidejaiSk(int sk) {
		zaidSk = sk;
	};

	string getPavadinimas() {
		return this->Pavadinimas;
	};
	string getTreneris() {
		return this->Treneris;
	};
	string getZaidejai(int j) {
		return this->Zaidejai[j];
	};
	int getZaidejaiSk() {
		return this->zaidSk;
	};

	Komandos(string pav) //konstruktorius
	{
		this->Pavadinimas = pav;
	}
};


/*class lklMainOnButton1 : public wxFrame
{
public:
	lklMainOnButton1();
	~lklMainOnButton1();
};*/

/*
void Nuskaitymas(SkaitytiKomandos &Komanda, Komandos &VisosKomandos)
{

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
}
*/