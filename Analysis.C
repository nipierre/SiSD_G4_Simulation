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

void fillEnergyStrip(TBranch *dataBranch, TH1F *hData)
{
	if(dataBranch == NULL) return;

	Float_t data[16];
	dataBranch->SetMakeClass(1);
	dataBranch->SetAddress(&data);

	Int_t nbEntries = dataBranch->GetEntries();
	for(Int_t i = 0; i < nbEntries; i++) {

		dataBranch->GetEntry(i);
		for(Int_t j = 3; j < 12; j++) {

			if(data[j] > 100) {
				hData->Fill(data[j]*3.6/1000+684);
			}
		}
	}
	//if (hData->Integral()!=0) hData->Scale(1/hData->Integral()); // Normalization
}

int Analysis(int i)
{
	TCanvas *window = new TCanvas("windows", "Display data", 1000, 650);
					 window->Divide(2,1);

	TString filename = Form("run%d.root", i);
	TFile* run = new TFile(filename);
	cout << "--> Loading " << filename << endl;

	if(run->IsOpen()) {

		TH2F *histoXY = new TH2F("XY", "Position (X,Y)", 100, -25, 25, 100, -25, 25);
		TH1F *histoES = new TH1F("ES", "Energy spectrum", 50, 0, 2500);

		TTree *SiSD = (TTree*) run->Get("SiSD");

		fillTH2F(SiSD->GetBranch("xPos"), SiSD->GetBranch("yPos"), histoXY);
		fillEnergyStrip(SiSD->GetBranch("StripSignal"), histoES);

		TString filenameCoeff = "./coeff.txt";
	  ifstream coeffFile(filenameCoeff);

	  TH1F *sum = new TH1F ("sum","somme", 32000,0 , 32000);

	  for(Int_t l=0; l<32000; l++) {

	    sum -> SetBinContent(l,0);

	  }


	  for(Int_t i=3; i<12; i++)
		{
			TString filename = "CardGLIB_histo_"+TString::Itoa(i,10)+".asc";
			ifstream file(filename);

			if(file)
			{
					TH1F *tmp = new TH1F("tmp", "tmp", 32000, 0, 32000);
					TString dummy;
					Double_t a,b;
					if(coeffFile.good()) {

					coeffFile >> dummy;
					coeffFile >> dummy;
					coeffFile >> dummy;
					coeffFile >> a;
					coeffFile >> b;
			}

			Int_t counter = 0;
			for(Int_t k = 0; k<32000; k++)
			{
				file >> counter;
				tmp->SetBinContent(TMath::Nint(a*k+b), counter);
			}

			sum -> Add(sum,tmp);

			}
		}

		window->cd(1);
		histoXY->GetXaxis()->SetTitle("X (mm)");
		histoXY->GetYaxis()->SetTitle("Y (mm)");
		histoXY->Draw("LEGO");

		window->cd(2);
		histoES->GetXaxis()->SetTitle("Energy (keV)");
		histoES->GetYaxis()->SetTitle("# of Hits");
		histoES->GetYaxis()->SetRangeUser(0,1250);

		histoES->Draw();

		sum->GetXaxis()->SetRangeUser(100,2500);
		sum->Draw("SAME");

		window->Modified();
		window->Update();

		cout << "(Press enter over the window, to continue)" << endl;
		window->WaitPrimitive(); // Wait a double click or pressing enter

		run->Close();

	} else cout << "ERROR" << endl;

	delete run;

	return 0;
}
