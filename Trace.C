void fillTH1F(TBranch *dataBranch, TH1F *hData)
{
	if(dataBranch == NULL) return;

	Double_t data;
	dataBranch->SetMakeClass(1);
	dataBranch->SetAddress(&data);

	Int_t nbEntries = dataBranch->GetEntries();
	for(Int_t i = 0; i < nbEntries; i++) {

		dataBranch->GetEntry(i);
		hData->Fill(data);
	}

	//if (hData->Integral()!=0) hData->Scale(1/hData->Integral()); // Normalization
}

void fillTH2F(TBranch *dataBranch1, TBranch *dataBranch2, TH2F *hData)
{
	if(dataBranch1 == NULL || dataBranch2 == NULL) return;

	Float_t data1, data2;
	dataBranch1->SetMakeClass(1);
	dataBranch1->SetAddress(&data1);
	dataBranch2->SetMakeClass(1);
	dataBranch2->SetAddress(&data2);

	Int_t nbEntries = dataBranch2->GetEntries();
	for(Int_t i = 0; i < nbEntries; i++) {

		dataBranch1->GetEntry(i);
		dataBranch2->GetEntry(i);
		hData->Fill(data1, data2);
	}
	//if (hData->Integral()!=0) hData->Scale(1/hData->Integral()); // Normalization
}

void fillEnergyStrip(TBranch *dataBranch, TH2F *hData)
{
	if(dataBranch == NULL) return;

	Float_t data[16];
	dataBranch->SetMakeClass(1);
	dataBranch->SetAddress(&data);

	Int_t nbEntries = dataBranch->GetEntries();
	for(Int_t i = 0; i < nbEntries; i++) {

		dataBranch->GetEntry(i);
		for(Int_t j = 0; j < 16; j++) {

			if(data[j] > 100) {
				hData->Fill(data[j]*3.6/1000, j+1);
			}
		}
	}
	//if (hData->Integral()!=0) hData->Scale(1/hData->Integral()); // Normalization
}

int Trace()
{
	TCanvas *window = new TCanvas("windows", "Display data", 1000, 650);
					 window->Divide(2,1);


	ifstream file("run0.root");
	int nbFiles = 0;
	for(int i = 0; file.is_open(); i++) {

		file.close();

		file.open(Form("run%d.root", i+1));

		if(!file.is_open())
		  nbFiles = i+1;
	}

	for(int i = 0; i < nbFiles; i++) {

			TString filename = Form("run%d.root", i);
			TFile* run = new TFile(filename);
			cout << "--> Loading " << filename << endl;

			if(run->IsOpen()) {

				TH2F *histoXY = new TH2F("XY", "Position (X,Y)", 100, -25, 25, 100, -25, 25);
				TH2F *histoES = new TH2F("ES", "Strip vs Energy", 50, 0, 2500, 16, 1, 17);

				TTree *SiSD = (TTree*) run->Get("SiSD");

				fillTH2F(SiSD->GetBranch("xPos"), SiSD->GetBranch("yPos"), histoXY);
				fillEnergyStrip(SiSD->GetBranch("StripSignal"), histoES);

				window->cd(1);
				histoXY->GetXaxis()->SetTitle("X (mm)");
				histoXY->GetYaxis()->SetTitle("Y (mm)");
				histoXY->Draw("LEGO");

				window->cd(2);
				histoES->GetXaxis()->SetTitle("Energy (keV)");
				histoES->GetYaxis()->SetTitle("Strip No");
				histoES->Draw("LEGO");

				window->Modified();
				window->Update();

				cout << "(Press enter over the window, to continue)" << endl;
				window->WaitPrimitive(); // Wait a double click or pressing enter

				run->Close();

			} else cout << "ERROR" << endl;

			delete run;
			run = NULL;
	}

	return 0;
}
