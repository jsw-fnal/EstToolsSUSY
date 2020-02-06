#include "../utils/EstHelper.hh"
#include "SRParameters.hh"
#include "TRegexp.h"
#include "TLatex.h"
#include <functional>

using namespace EstTools;

void formatFinalPlots(TString inputFile="/uscms/home/mkilpatr/nobackup/CMSSW_10_2_9/src/Limits/SumOfBkg.root", TString outputName="getFinalPlot/"){

  RATIOPLOT_XTITLE_OFFSET = 1.35;
  RATIOPLOT_XLABEL_FONTSIZE = 0.128;
  RATIOPLOT_XLABEL_OFFSET = 0.00;
  PAD_SPLIT_Y = 0.34;
  PAD_BOTTOM_MARGIN = 0.4;


  vector<TString> bkgs = {"httz_stack_2", "hdiboson_stack_1", "hqcd_stack_3", "hznunu_stack_4", "httbar_stack_5"};
  vector<TString> mcs =  {"rare_mc",   "qcd_mc",   "znunu_mc",   "ttbarplusw_mc"};
  vector<TString> sigs = {"T2tt_1000_0"};
  TString data = "data";

  vector<TString> bkglabels = {"ttZ", "Rare", "QCD", "Z#rightarrow#nu#nu", "t#bar{t}/W"};
  vector<TString> siglabels = {"T2tt(1000,0)"};
  vector<TString> datalabel = {"Observed"};
  vector<double> ratioYmax = {2.999, 2.999, 2.999, 6.999, 2.999, 6.999};

  auto xlabels = convertBinRangesToLabels<int>(srbins, srMETbins);

  vector<TH1*> pred;
  vector<TH1*> hsigs;

  TFile *f = TFile::Open(inputFile);
  assert(f);
  for (auto &b : bkgs){
    TH1D* hist = convertToHist({(TH1*)f->Get(b)}, b, ";Search Region;Events", nullptr);
    pred.push_back(hist);
  }
  TH1D* total = convertToHist({(TH1*)f->Get("hpred")}, "hpred", ";Search Region;Events", nullptr);
  //TH1* hdata = (TH1*)f->Get(data);
  for (auto &s : sigs){
    TH1 *h = convertToHist({(TH1*)f->Get(s)}, s, ";Search Region;Events", nullptr);
    h->SetLineStyle(kDashed);
    hsigs.push_back(h);
  }

  prepHists(pred, false, false, true, {797, 391, 811, 623, 866});
  prepHists({total}, false, false, true, {kRed});
  //prepHists({hdata}, false, false, false, {kBlack});
  prepHists(hsigs, false, false, false, {kRed});
  //hdata->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");


  TFile *output = new TFile(outputName+"SumOfBkg.root", "RECREATE");
  for (auto *h : pred) h->Write();
  for (auto *s : hsigs) s->Write();
  //hdata->Write();
  total->Write();
  output->Close();



}