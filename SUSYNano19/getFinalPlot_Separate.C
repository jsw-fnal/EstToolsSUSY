#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <string.h>
#include <functional>

using namespace EstTools;

void getFinalPlot_Separate(TString inputDir="19May2020_Run2Unblind_dev_v6", TString outputName="getFinalPlot_Separate/pred_binnum_"){

  RATIOPLOT_XTITLE_OFFSET = 1.35;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.00;
  PAD_SPLIT_Y = 0.34;
  PAD_BOTTOM_MARGIN = 0.4;
  if(inputDir.Contains("2016")) lumistr = "35.815165";

  TString inputFile = "/eos/uscms/store/user/lpcsusyhad/Stop_production/LimitInputs/" + inputDir + "/SearchBinsPlot/";

  vector<TString> bkgs = {"httz", "hRare", "hqcd", "hznunu", "httbar"};
  vector<TString> sigs = {"T2tt_1000_0"};
  TString data = "hdata";

  vector<TString> bkglabels = {"ttZ", "Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> siglabels = {"T2tt(1000,0)"};
  vector<TString> datalabel = {"Observed"};

  vector<TString> split = {"lm",
			   "hm_nb1_bins",
			   "hm_nbeq2",
			   "hm_nb3"
			   };
  vector<TString> splitlabels = {
      "Low #Deltam",
      "High #Deltam, N_{b}=1 #geq 2, (N_{t}, N_{res}, N_{W})",
      "High #Deltam, N_{b}=2, (N_{t}, N_{res}, N_{W})",
      "High #Deltam, N_{b} #geq 3, (N_{t}, N_{res}, N_{W})"
  };

  vector<double> ratioYmax = {2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999, 2.999};

  TLatex tl, tv;
  tl.SetTextSize(0.025);
  tl.SetTextAlign(31);
  tv.SetTextSize(0.025);
  tv.SetTextAlign(31);
  tv.SetTextAngle(90);
  vector<std::function<void()>> drawRegionLabels {
//    [&tl](){},
//    [&tl](){},
//    [&tl](){},
//    [&tl](){},

    [&tl](){ tl.DrawLatexNDC(0.345, 0.73, "N_{b}=0,p_{T}^{ISR}#geq500"); 
	     tl.DrawLatexNDC(0.2425, 0.70, "N_{SV}=0"); 
	     tl.DrawLatexNDC(0.35, 0.70, "N_{SV}#geq1"); 
	     tl.DrawLatexNDC(0.57, 0.73, "N_{b}=1"); 
	     tl.DrawLatexNDC(0.54, 0.70, "N_{SV}=0");
	     tl.DrawLatexNDC(0.62, 0.67, "p_{T}^{ISR}[300,500)     p_{T}^{ISR}#geq500"); 
	     tl.DrawLatexNDC(0.68, 0.70, "N_{SV}#geq1"); 
	     tl.DrawLatexNDC(0.85, 0.73, "N_{b}=2"); 
	     tl.DrawLatexNDC(0.92, 0.70, "p_{T}^{ISR}[300,500)       p_{T}^{ISR}#geq500");},
    [&tl](){ tl.DrawLatexNDC(0.26, 0.73, "M_{T}^{b} < 175"); 
	     tl.DrawLatexNDC(0.277, 0.70, "N_{b}=1    N_{b}#geq2"); 
	     tl.DrawLatexNDC(0.37, 0.73, "(0, 0, 0)"); 
	     tl.DrawLatexNDC(0.39, 0.70, "N_{b}=1    N_{b}#geq2"); 
	     tl.DrawLatexNDC(0.5, 0.70, "(#geq1, 0, 0)"); 
	     tl.DrawLatexNDC(0.63, 0.70, "(0, 0, #geq1)"); 
	     tl.DrawLatexNDC(0.78, 0.70, "(0, #geq1, 0)");},
    [&tl](){ tl.DrawLatexNDC(0.27, 0.70, "(1, 0, 0)"); 
	     tl.DrawLatexNDC(0.39, 0.70, "(0, 0, 1)"); 
	     tl.DrawLatexNDC(0.55, 0.70, "(0, 1, 0)");},
    [&tl](){ tl.DrawLatexNDC(0.32, 0.70, "(1, 0, 0)");
	     tl.DrawLatexNDC(0.47, 0.70, "(0, 0, 1)");
	     tl.DrawLatexNDC(0.63, 0.70, "(0, 1, 0)");},
  };

  vector<std::function<void()>> drawRegionLabelsVertical {
    [&tv](){},
//    [&tv](){},
//    [&tv](){},
//    [&tv](){},

    [&tv](){ tv.DrawLatexNDC(0.89, 0.73, "(#geq1, #geq1, 0)"); 
	     tv.DrawLatexNDC(0.92, 0.73, "(#geq1, 0, #geq1)"); 
	     tv.DrawLatexNDC(0.95, 0.73, "(0, #geq1, #geq1)");},
    [&tv](){ tv.DrawLatexNDC(0.68, 0.70, "(1, 0, 1)"); 
	     tv.DrawLatexNDC(0.75, 0.70, "(1, 1, 0)"); 
	     tv.DrawLatexNDC(0.815, 0.70, "(0, 1, 1)"); 
	     tv.DrawLatexNDC(0.845, 0.70, "(2, 0, 0)"); 
	     tv.DrawLatexNDC(0.875, 0.70, "(0, 0, 2)"); 
	     tv.DrawLatexNDC(0.92, 0.70, "(0, 2, 0)"); 
	     tv.DrawLatexNDC(0.985, 0.70, "(N_{t} + N_{res} + N_{W})#geq3");},
    [&tv](){ tv.DrawLatexNDC(0.74, 0.70, "(1, 0, 1)"); 
	     tv.DrawLatexNDC(0.78, 0.70, "(1, 1, 0)"); 
	     tv.DrawLatexNDC(0.82, 0.70, "(0, 1, 1)"); 
	     tv.DrawLatexNDC(0.845, 0.70, "(2, 0, 0)"); 
	     tv.DrawLatexNDC(0.875, 0.70, "(0, 0, 2)"); 
	     tv.DrawLatexNDC(0.91, 0.70, "(0, 2, 0)"); 
	     tv.DrawLatexNDC(0.985, 0.70, "(N_{t} + N_{res} + N_{W})#geq3");},
  };

  vector<std::function<void(TCanvas *)>> drawVerticalLines {
//    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); },
//    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); },
//    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); },
//    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); },

    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(8,   LOG_YMIN, 8,   2000); 
								    drawLine(16,  LOG_YMIN, 16,  20000); 
								    drawLine(24,  LOG_YMIN, 24,  2000); 
								    drawLine(32,  LOG_YMIN, 32,  2000); 
								    drawLine(35,  LOG_YMIN, 35,  20000); 
								    drawLine(44,  LOG_YMIN, 44,  2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(57, LOG_YMIN, 57, 2000); 
								    drawLine(61, LOG_YMIN, 61, 20000); 
								    drawLine(65, LOG_YMIN, 65, 2000); 
								    drawLine(69, LOG_YMIN, 69, 20000); 
								    drawLine(78, LOG_YMIN, 78, 20000); 
								    drawLine(84, LOG_YMIN, 84, 20000); 
								    drawLine(99, LOG_YMIN, 99, 20000); 
								    drawLine(101, LOG_YMIN, 101, 2000); 
								    drawLine(103, LOG_YMIN, 103, 2000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(114, LOG_YMIN, 114, 20000); 
								    drawLine(120, LOG_YMIN, 120, 20000); 
								    drawLine(135, LOG_YMIN, 135, 20000); 
								    drawLine(137, LOG_YMIN, 137, 20000); 
								    drawLine(143, LOG_YMIN, 143, 20000); 
								    drawLine(145, LOG_YMIN, 145, 20000); 
								    drawLine(147, LOG_YMIN, 147, 20000); 
								    drawLine(148, LOG_YMIN, 148, 20000); 
								    drawLine(152, LOG_YMIN, 152, 20000); c->cd(); },
    [](TCanvas *c){ ((TPad*)c->GetListOfPrimitives()->At(0))->cd(); drawLine(162, LOG_YMIN, 162, 20000); 
								    drawLine(165, LOG_YMIN, 165, 20000); 
								    drawLine(174, LOG_YMIN, 174, 20000); 
								    drawLine(175, LOG_YMIN, 175, 20000); 
								    drawLine(177, LOG_YMIN, 177, 20000); 
								    drawLine(178, LOG_YMIN, 178, 20000); 
								    drawLine(179, LOG_YMIN, 179, 20000); 
								    drawLine(180, LOG_YMIN, 180, 20000); 
								    drawLine(182, LOG_YMIN, 182, 20000); c->cd(); },
  };

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

  vector<TH1*> pred;
  vector<TH1*> hsigs;

  TString suffix = "";
  if(inputDir.Contains("2016")) suffix = "_2016";
  TFile *ttz = TFile::Open(inputFile + "TTZ_final_sb" + suffix + ".root");
  assert(ttz);
  TH1D* httZ = convertToHist({(TH1*)ttz->Get("Prediction")}, "ttZ_pred", ";Search Region;Events", nullptr);
  pred.push_back(httZ);

  TFile *r = TFile::Open(inputFile + "Rare_final_sb" + suffix + ".root");
  assert(r);
  TH1D* hRare = convertToHist({(TH1*)r->Get("Prediction")}, "Rare_pred", ";Search Region;Events", nullptr);
  pred.push_back(hRare);

  TFile *q = TFile::Open(inputFile + "SearchBins_QCDResidMET.root");
  assert(q);
  TH1D* hqcd = convertToHist({(TH1*)q->Get("QCD")}, "qcd_pred", ";Search Region;Events", nullptr);
  pred.push_back(hqcd);

  if(!inputDir.Contains("2016")) suffix = "_Run2";

  TFile *z = TFile::Open(inputFile + "searchBinsZinv_combined" + suffix + ".root");
  assert(z);
  TH1D* hznunu = convertToHist({(TH1*)z->Get("Prediction")}, "znunu_pred", ";Search Region;Events", nullptr);
  pred.push_back(hznunu);

  if(inputDir.Contains("2016")) suffix = "_2016";
  else suffix = "";
  TFile *f = TFile::Open("getFinalPlot" + suffix + "/SumOfBkg.root");
  assert(f);
  TH1D* httbar = convertToHist({(TH1*)f->Get("httbar")}, "httbar_pred", ";Search Region;Events", nullptr);
  pred.push_back(httbar);
  TH1D* hznunu_aux = convertToHist({(TH1*)f->Get("hznunu")}, "hznunu_pred", ";Search Region;Events", nullptr); // KH hack: this is a hack which we should be careful with

  TH1* hdata = (TH1*)f->Get(data);

  //get all of the uncertainties
  TH1D* ttbar_up_unc = (TH1D*)f->Get("ttbarplusw_syst_up");
  TH1D* ttbar_dn_unc = (TH1D*)f->Get("ttbarplusw_syst_dn");
  TH1D* znunu_up_unc = (TH1D*)f->Get("znunu_syst_up");
  TH1D* znunu_dn_unc = (TH1D*)f->Get("znunu_syst_dn");
  TH1D* ttZ_up_unc = (TH1D*)ttz->Get("Total_Up");
  TH1D* ttZ_dn_unc = (TH1D*)ttz->Get("Total_Down");
  TH1D* Rare_up_unc = (TH1D*)r->Get("Total_Up");
  TH1D* Rare_dn_unc = (TH1D*)r->Get("Total_Down");
  TH1D* qcd_up_unc = (TH1D*)q->Get("Tot_Up");
  TH1D* qcd_dn_unc = (TH1D*)q->Get("Tot_Down");
  //TH1D* znunu_up_unc = (TH1D*)z->Get("Total_Up");
  //TH1D* znunu_dn_unc = (TH1D*)z->Get("Total_Down");

  TGraphAsymmErrors* unc = (TGraphAsymmErrors*)f->Get("ttbarplusw_unc_sr")->Clone("bkgtotal_unc_sr");
  TH1D* nominal = (TH1D*)httbar->Clone("Total_Prediction");
  for (int ibin = 0; ibin < unc->GetN(); ++ibin){
    int ibin_hist = ibin+1;
    //Systematics
    double unc_up = ((ttbar_up_unc->GetBinContent(ibin_hist)-1)*httbar->GetBinContent(ibin_hist))*((ttbar_up_unc->GetBinContent(ibin_hist)-1)*httbar->GetBinContent(ibin_hist));
    double unc_dn = ((1-ttbar_dn_unc->GetBinContent(ibin_hist))*httbar->GetBinContent(ibin_hist))*((1-ttbar_dn_unc->GetBinContent(ibin_hist))*httbar->GetBinContent(ibin_hist));
    unc_up += ((ttZ_up_unc->GetBinContent(ibin_hist)-1)*httZ->GetBinContent(ibin_hist))*((ttZ_up_unc->GetBinContent(ibin_hist)-1)*httZ->GetBinContent(ibin_hist));
    unc_dn += ((1-ttZ_dn_unc->GetBinContent(ibin_hist))*httZ->GetBinContent(ibin_hist))*((1-ttZ_dn_unc->GetBinContent(ibin_hist))*httZ->GetBinContent(ibin_hist));
    unc_up += ((Rare_up_unc->GetBinContent(ibin_hist)-1)*hRare->GetBinContent(ibin_hist))*((Rare_up_unc->GetBinContent(ibin_hist)-1)*hRare->GetBinContent(ibin_hist));
    unc_dn += ((1-Rare_dn_unc->GetBinContent(ibin_hist))*hRare->GetBinContent(ibin_hist))*((1-Rare_dn_unc->GetBinContent(ibin_hist))*hRare->GetBinContent(ibin_hist));
    unc_up += ((qcd_up_unc->GetBinContent(ibin_hist)-1)*hqcd->GetBinContent(ibin_hist))*((qcd_up_unc->GetBinContent(ibin_hist)-1)*hqcd->GetBinContent(ibin_hist));
    unc_dn += ((1-qcd_dn_unc->GetBinContent(ibin_hist))*hqcd->GetBinContent(ibin_hist))*((1-qcd_dn_unc->GetBinContent(ibin_hist))*hqcd->GetBinContent(ibin_hist));
    unc_up += ((znunu_up_unc->GetBinContent(ibin_hist)-1)*hznunu->GetBinContent(ibin_hist))*((znunu_up_unc->GetBinContent(ibin_hist)-1)*hznunu->GetBinContent(ibin_hist));
    unc_dn += ((1-znunu_dn_unc->GetBinContent(ibin_hist))*hznunu->GetBinContent(ibin_hist))*((1-znunu_dn_unc->GetBinContent(ibin_hist))*hznunu->GetBinContent(ibin_hist));

    //Statistical
    // ttbar:
    unc_up += httbar->GetBinError(ibin_hist)*httbar->GetBinError(ibin_hist);
    if(httbar->GetBinContent(ibin_hist) != 0)
      unc_dn += httbar->GetBinError(ibin_hist)*httbar->GetBinError(ibin_hist);
    else unc_dn += 0.; //
    // qcd:
    unc_up += hqcd->GetBinError(ibin_hist)*hqcd->GetBinError(ibin_hist);
    unc_dn += hqcd->GetBinError(ibin_hist)*hqcd->GetBinError(ibin_hist);
    // znunu:
    if(hznunu->GetBinContent(ibin_hist) != 0){
      unc_up += hznunu_aux->GetBinError(ibin_hist)*hznunu_aux->GetBinError(ibin_hist);
      unc_dn += hznunu_aux->GetBinError(ibin_hist)*hznunu_aux->GetBinError(ibin_hist);
    } else{
      unc_up += hznunu_aux->GetBinError(ibin_hist)*hznunu_aux->GetBinError(ibin_hist); //KH hack: when histograms from Caleb get this error correctly, use it.
      unc_dn += 0.;
    }
    unc_up += httZ->GetBinError(ibin_hist)*httZ->GetBinError(ibin_hist);
    unc_dn += httZ->GetBinError(ibin_hist)*httZ->GetBinError(ibin_hist);
    unc_up += hRare->GetBinError(ibin_hist)*hRare->GetBinError(ibin_hist);
    unc_dn += hRare->GetBinError(ibin_hist)*hRare->GetBinError(ibin_hist);

    //Nominal
    double pred = nominal->GetBinContent(ibin_hist);
    pred += hqcd->GetBinContent(ibin_hist);
    pred += hznunu->GetBinContent(ibin_hist);
    pred += hRare->GetBinContent(ibin_hist);
    pred += httZ->GetBinContent(ibin_hist);

    cout << "bin: " << ibin << " pred: " << pred << " up: " << TMath::Sqrt(unc_up) << " dn: " << TMath::Sqrt(unc_dn) << endl;

    unc->SetPoint(ibin, unc->GetX()[ibin], pred);
    unc->SetPointEYhigh(ibin, TMath::Sqrt(unc_up));
    unc->SetPointEYlow(ibin,  TMath::Sqrt(unc_dn));
  }

  for (auto &s : sigs){
    TH1 *h = convertToHist({(TH1*)f->Get(s)}, s, ";Search Region;Events", nullptr);
    h->SetLineStyle(kDashed);
    hsigs.push_back(h);
  }
  TH1* pull;
  if(hdata){
    pull = getPullHist(hdata, unc);
  }

  prepHists(pred, false, false, true, {797, 391, 811, 623, 866});
  if(hdata) prepHists({hdata}, false, false, false, {kBlack});
  if(hdata) prepHists({pull}, false, false, false, {kRed});
  prepHists(hsigs, false, false, false, {kRed});

  auto catMap = srCatMap();
  for (unsigned ireg = 0; ireg < split.size(); ++ireg){
    auto &region = split.at(ireg);
    int xlow = 0, xhigh = 0;
    bool isfirst = true;
    int ibin = 0;
    for (auto &cat_name : srbins){
      auto nbins = catMap.at(cat_name).bin.nbins;
      if (cat_name.Contains(TRegexp(region)) || 
	 (TString(region).Contains("hm_nb1_bins") && (cat_name.Contains("hm_nb1") || cat_name.Contains("highmtb_nt0_nrt0_nw0") || cat_name.Contains("lowmtb_nj7_nrtgeq1"))) //hm_nb1_bins
         ){
        if (isfirst){
          isfirst = false;
          xlow = ibin;
          xhigh = xlow + nbins;
        }else{
          xhigh += nbins;
        }
      }
      ibin += nbins;
    }


    if (region.Contains("lm")) {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 10.0;}
    else {LOG_YMIN = 0.01; PLOT_MAX_YSCALE = 1.0;}

    auto leg = prepLegends({hdata}, datalabel, "LP");
    appendLegends(leg, pred, bkglabels, "F");
    appendLegends(leg, hsigs, siglabels, "L");
//    appendLegends(leg, {hDataRawMC}, {"Simulation", "L"});
  //  leg->SetTextSize(0.03);
    setLegend(leg, 2, 0.52, 0.71, 0.94, 0.87);

    TCanvas* c = drawStackAndRatio(pred, hdata, leg, true, "N_{obs}/N_{exp}", 0, ratioYmax[ireg], xlow, xhigh, hsigs, unc);
    c->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    drawTLatexNDC(splitlabels.at(ireg), 0.195, 0.78, 0.025);
    drawRegionLabels.at(ireg)();
    drawRegionLabelsVertical.at(ireg)();
    drawVerticalLines.at(ireg)(c);
    TString basename = outputName + "_" + region;
    basename.ReplaceAll("nb[0-9]", "");
    c->Print(basename+".pdf");
    c->Print(basename +".C");
  }

  if(hdata){
    double mean  = pull->GetMean();
    double StdDev = pull->GetStdDev();
    TString fitString = "#splitline{Mean = " + to_string(mean) + "}{StdDev = " + to_string(StdDev) + "}";
    std::function<void(TCanvas*)> plotextra   = [&](TCanvas *c){ c->cd(); drawTLatexNDC(fitString, 0.2, 0.72); };
    auto c_pull = drawCompMatt({pull}, 0, -1., &plotextra);
    c_pull->SetCanvasSize(800, 600);
    gStyle->SetOptStat(0);
    TString basename = outputName + "_pull";
    c_pull->Print(basename+".pdf");
    c_pull->Print(basename +".C");
  }

  TFile *output = new TFile(outputName + "getFinalPlot_Nano.root", "RECREATE");
  for (auto *h : pred) h->Write();
  for (auto *s : hsigs) s->Write();
  if(hdata) pull->Write();
  if(hdata) hdata->Write();
  output->Close();

}
