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
				hData->Fill(data[j]*3.6/1000);
			}
		}
	}
}

int Analysis(int i)
{
	gStyle->SetOptStat(0);
	gStyle->SetLegendBorderSize(0);

	TCanvas *window = new TCanvas("windows", "Display data", 500, 500);
					 window->Divide(1,2);

	TString filename = Form("run%d.root", i);
	TFile* run = new TFile(filename);
	cout << "--> Loading " << filename << endl;

	if(run->IsOpen()) {

		TH1F *histoES = new TH1F("", "", 200, 0, 2500);

		TTree *SiSD = (TTree*) run->Get("SiSD");

		fillEnergyStrip(SiSD->GetBranch("StripSignal"), histoES);

		TString filenameCoeff = "./coeff.txt";
	  ifstream coeffFile(filenameCoeff);

	  TH1F *sum = new TH1F ("","", 32000,0 , 32000);

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

		Double_t rescaleSum, rescaleES;
		Double_t meanSum, meanES;

		TLegend* leg1 = new TLegend(0.1,0.75,0.5,0.9);
		TLegend* leg2 = new TLegend(0.1,0.75,0.5,0.9);

		window->cd(1);
		sum->GetXaxis()->SetRangeUser(100,2500);
		rescaleSum = sum->GetBinContent(sum->GetMaximumBin());
		meanSum = sum->GetBinCenter(sum->GetMaximumBin());
		sum->Scale(1/rescaleSum);
		sum -> GetXaxis() -> SetLabelSize(0.06);
		sum -> GetYaxis() -> SetLabelSize(0.06);
    sum -> GetXaxis() -> SetTitleSize(0.057);
    sum -> GetXaxis() -> SetTitleOffset(0.760);
		leg1->AddEntry(sum, "Experiment", "");
		leg1->AddEntry(sum, Form("Peak centroid = %d keV", Int_t(meanSum)), "");
		leg1->SetFillStyle(0);
		sum->Draw();
		leg1->Draw("SAME");

		window->cd(2);
		histoES->GetXaxis()->SetTitle("E (keV)");
		histoES->GetXaxis()->SetRangeUser(100,2500);
		rescaleES = histoES->GetBinContent(histoES->GetMaximumBin());
		meanES = histoES->GetBinCenter(histoES->GetMaximumBin());
		histoES->Scale(1/rescaleES);
		histoES->SetLineColor(kRed);
		histoES -> GetXaxis() -> SetLabelSize(0.06);
		histoES -> GetYaxis() -> SetLabelSize(0.06);
    histoES -> GetXaxis() -> SetTitleSize(0.057);
    histoES -> GetXaxis() -> SetTitleOffset(0.85);
		leg2->AddEntry(histoES, "Geant4 Simulation", "");
		leg2->AddEntry(histoES, Form("Peak centroid = %d keV", Int_t(meanES)), "");
		leg2->SetFillStyle(0);
		histoES->Draw();
		leg2->Draw("SAME");

		window->Modified();
		window->Update();

		cout << "(Press enter over the window, to continue)" << endl;
		window->WaitPrimitive(); // Wait a double click or pressing enter

		window->SaveAs("histo_simu.pdf");

		run->Close();

	} else cout << "ERROR" << endl;

	delete run;

	return 0;
}
