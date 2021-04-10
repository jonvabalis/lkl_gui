#pragma once
#include "wx/wx.h"
#include <wx/simplebook.h>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
//#include <stdio.h>
#include <cstdio>

using namespace std;

void EiluciuSk(string failas, int &x);
void RungtyniuSk(string failas, int &rungtyniu_sk);
void ID_sk(string failas, int ID, int &x, int &ID_pradzia);
wxString BeTarpu(wxString nice);

class lklMain : public wxFrame
{
public:
	lklMain();
	~lklMain();


	//int ZaidejoListID;
	//int *pointeris = &ZaidejoListID;

	wxStaticText *m_titulinisText1;
	wxStaticText *m_titulinisText2;

	wxRadioButton *m_radioKomandos;
	wxRadioButton *m_radioVarzybos;

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

	void OnRadioClicked(wxCommandEvent &evt);

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
class SkaitytiVarzybos
{
private:

	vector<int> ID;

	vector<string> KomandaPav1;
	vector<string> KomandaPav2;

	vector<string> Data;

	vector<string> Vieta;

	vector<vector<vector<string>>> Komanda1;
	vector<vector<vector<string>>> Komanda2;

public:
	void Skaityti(string komandos, string data, string vieta, string rezultatai)
	{
		string nuskaitytas;
		int eilsk, rungtyniu_sk, ID_pradzios_ind;


		EiluciuSk(komandos, eilsk);
		ifstream fd1(komandos);

		for (int i = 0; i < eilsk; i++)
		{
			getline(fd1, nuskaitytas, '|');
			ID.push_back(stoi(nuskaitytas));

			getline(fd1, nuskaitytas, '|');
			KomandaPav1.push_back(nuskaitytas);

			getline(fd1, nuskaitytas, '|');
			KomandaPav2.push_back(nuskaitytas);
		}

		fd1.close();


		EiluciuSk(data, eilsk);
		ifstream fd2(data);

		for (int i = 0; i < eilsk; i++)
		{
			getline(fd2, nuskaitytas, '|');
			getline(fd2, nuskaitytas, '|');
			Data.push_back(nuskaitytas);
		}

		fd2.close();


		EiluciuSk(vieta, eilsk);
		ifstream fd3(vieta);

		for (int i = 0; i < eilsk; i++)
		{
			getline(fd3, nuskaitytas, '|');
			getline(fd3, nuskaitytas, '|');
			Vieta.push_back(nuskaitytas);
		}

		fd3.close();


		RungtyniuSk(rezultatai, rungtyniu_sk);
		ifstream fd4(rezultatai);

		for (int h = 0; h < rungtyniu_sk; h++)
		{
			vector<vector<string>> Komanda1Info;
			vector<vector<string>> Komanda2Info;

			ID_sk(rezultatai, ID[h], eilsk, ID_pradzios_ind);
			for (int i = ID_pradzios_ind; i < eilsk + ID_pradzios_ind; i++)
			{
				string tempkomanda;
				vector<string> ZaidejasInfo;

				getline(fd4, nuskaitytas, '|');
				getline(fd4, tempkomanda, '|');

				for (int j = 0; j < 17; j++)
				{
					getline(fd4, nuskaitytas, '|');
					ZaidejasInfo.push_back(nuskaitytas);
				}

				if (BeTarpu(KomandaPav1[h]) == tempkomanda)
					Komanda1Info.push_back(ZaidejasInfo);
				if (BeTarpu(KomandaPav2[h]) == tempkomanda)
					Komanda2Info.push_back(ZaidejasInfo);
			}

			Komanda1.push_back(Komanda1Info);
			Komanda2.push_back(Komanda2Info);
		}

		fd4.close();
	};

	int getID(int i) {
		return this->ID[i];
	};
	string getPavadinimas1(int i) {
		return this->KomandaPav1[i];
	};
	string getPavadinimas2(int i) {
		return this->KomandaPav2[i];
	};
	string getData(int i) {
		return this->Data[i];
	};
	string getVieta(int i) {
		return this->Vieta[i];
	};
	vector<vector<string>> getKomanda1(int i) {
		return this->Komanda1[i];
	};
	vector<vector<string>> getKomanda2(int i) {
		return this->Komanda2[i];
	};
	int getPavadinimasSize() {
		return this->KomandaPav1.size();
	};
};
class Varzybos
{
private:

	int ID;

	string KomandaPav1;
	string KomandaPav2;

	string Data;

	string Vieta;

	vector<vector<string>> Komanda1;
	vector<vector<string>> Komanda2;

public:

	void setID(int i) {
		ID = i;
	};
	void setPavadinimas1(string pavadinimas) {
		KomandaPav1 = pavadinimas;
	};
	void setPavadinimas2(string pavadinimas) {
		KomandaPav2 = pavadinimas;
	};
	void setData(string data) {
		Data = data;
	};
	void setVieta(string vieta) {
		Vieta = vieta;
	};
	void setKomanda1(vector<vector<string>> komanda1) {
		Komanda1 = komanda1;
	};
	void setKomanda2(vector<vector<string>> komanda2) {
		Komanda2 = komanda2;
	};

	int getID() {
		return this->ID;
	};
	string getPavadinimas1() {
		return this->KomandaPav1;
	};
	string getPavadinimas2() {
		return this->KomandaPav2;
	};
	string getData() {
		return this->Data;
	};
	string getVieta() {
		return this->Vieta;
	};
	string getKomandaInfo1(int j, int i) {
		return this->Komanda1[j][i];
	}; //zaidejas j, statsai i
	string getKomandaInfo2(int j, int i) {
		return this->Komanda2[j][i];
	}; //zaidejas j, statsai i
	int getKomandaSk1() {
		return this->Komanda1.size();
	};
	int getKomandaSk2() {
		return this->Komanda2.size();
	};

	//kad vektorius patenkintas butu
	Varzybos(string pavadinimas1)
	{
		this->KomandaPav1 = pavadinimas1;
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