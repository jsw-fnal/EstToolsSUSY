#ifndef ESTTOOLS_LMPARAMETERS_HH_
#define ESTTOOLS_LMPARAMETERS_HH_

#include "../utils/EstHelper.hh"

namespace EstTools{

//const TString datadir = "4ifb";
//const TString lumistr = "4.32";

const TString datadir = ".";
const TString lumistr = "12.9";

TString getLumi(){return lumistr(TRegexp("[0-9]+.[0-9]"));}

// lumi and base weight
//const TString wgtvar = lumistr+"*weight*truePUWeight";
const TString wgtvar = lumistr+"*weight*truePUWeight*btagWeight";
const TString srmcwgt = wgtvar+"*(0.9*(met<250)+1.0*(met>250))";

// photon trigger eff.
const TString phowgt = wgtvar + "*qcdRespTailWeight";
//const TString phowgt = wgtvar+"*trigPhoWeight";

// No Lepton SF
//const TString lepvetowgt = wgtvar;
//const TString lepselwgt  = wgtvar;
//const TString vetoes = " && nvetolep==0 && nvetotau==0";

// Tag-and-Probe Lepton SF
const TString lepvetowgt = wgtvar + "*leptnpweightLM*lepvetoweightLM";
const TString lepselwgt  = wgtvar + "*leptnpweightLM";
const TString vetoes = " && nvetolep==0 && (nvetotau==0 || (ismc && npromptgentau>0))";

// 1LCR Lepton SF
//const TString lepvetowgt = wgtvar + "*lepvetoweight";
//const TString lepselwgt  = wgtvar + "*lepselweight";
//const TString vetoes = " && ((nvetolep==0 && nvetotau==0) || (ismc && (ngoodgenele>0 || ngoodgenmu>0 || npromptgentau>0)))";

// 1Lep LLB method
//bool ADD_LEP_TO_MET = false;
const TString revert_vetoes = " && nvetolep>0 && mtlepmet<100";

// MET+LEP LL method
bool ADD_LEP_TO_MET = true;
const TString lepcrsel = " && nvetolep==1 && mtlepmet<100 && origmet>100";
//const TString lepcrsel = " && nprimlep==1 && mtlepmet<100 && origmet>100";

// lepton trigger eff.
//const TString trigLepCR = " && (passtrige || passtrigmu)";
//const TString onelepcrwgt  = lepselwgt + "*trigEleWeight*trigMuWeight";

// OR with MET trigger
//const TString trigLepCR = " && (passtrige || passtrigmu || (passmetmht100 && failtriglep))";
//const TString onelepcrwgt  = lepselwgt + "*trigMetOrElWeight*trigMetOrMuWeight";

const TString trigLepCR = " && passtriglepOR";
const TString onelepcrwgt  = lepselwgt;

// qcd weights
const TString qcdwgt = wgtvar + "*qcdRespTailWeight";
const TString srqcdwgt = srmcwgt + "*qcdRespTailWeight";
//const TString qcdwgt = wgtvar;
const TString qcdvetowgt = lepvetowgt + "*qcdRespTailWeight";
//const TString qcdvetowgt = lepvetowgt;

// signal weights
//const TString sigwgt = lepvetowgt + "*btagFastSimWeight";
const TString sigwgt = lepvetowgt;

// triggers
const TString trigSR = " && (passmetmht100 || ismc)";
const TString trigPhoCR = " && passtrigphoOR && origmet<200";
const TString trigDiLepCR = " && passtrigdilepOR";
const TString datasel = " && passjson && passmetfilters && j1chEnFrac>0.1 && j1chEnFrac<0.99";

// ------------------------------------------------------------------------
// search regions and control regions

const TString baseline = "met>200 && met<450 && njets>=2 && njl>=1 && dphij1met>0.5 && dphij2met>0.15 && dphij3met>0.15 && metovsqrtht>10 && j1lpt>250 && dphij1lmet>2";
const TString baseNoDPhi = "met>200 && met<450 && njets>=2 && njl>=1 && metovsqrtht>10 && j1lpt>250 && dphij1lmet>2";
const TString dphi = " && dphij1met>0.5 && dphij2met>0.15 && dphij3met>0.15",
    dphi_invert = " && (dphij1met<0.1 || dphij2met<0.1 || dphij3met<0.1)";

std::vector<TString> srbins{
  "nb0_highboost_lownj", "nb0_highboost_highnj",
  "nb1_medboost_lowptb", "nb1_medboost_medptb",
  "nb1_highboost_lowptb", "nb1_highboost_medptb",
  "nb2_medboost_lowptb", "nb2_medboost_medptb",
  "nb2_highboost_lowptb", "nb2_highboost_medptb",
};

const TString mtb = "mtcsv12met<100",
    nb0 = "nbjets==0", nb1 = "nbjets>=1 && nlbjets==1", nb2 = "nbjets>=1 && nlbjets>=2",
    medboost = "j1lpt>250 && j1lpt<500", highboost = "j1lpt>500",
    lowptb = "csvj1pt<40", medptb = "csvj1pt>40 && csvj1pt<70",
    lowptb12 = "(csvj1pt+csvj2pt)<100", medptb12 = "(csvj1pt+csvj2pt)>100 && (csvj1pt+csvj2pt)<160",
    lownj = "njets>=2 && njets<=5", highnj = "njets>=6";

std::map<TString, TString> normMap{
  {"nb0", nb0},
  {"nb1", nb1},
  {"nb2", nb2}
};

std::map<TString, TString> srcuts{
  {"nb0_highboost_lownj",   addCuts({nb0, highboost, lownj})},
  {"nb0_highboost_highnj",  addCuts({nb0, highboost, highnj})},

  {"nb1_medboost_lowptb",   addCuts({mtb, nb1, medboost,  lowptb, "met<300"}) },
  {"nb1_medboost_medptb",   addCuts({mtb, nb1, medboost,  medptb, "met<300"}) },
  {"nb1_highboost_lowptb",  addCuts({mtb, nb1, highboost, lowptb}) },
  {"nb1_highboost_medptb",  addCuts({mtb, nb1, highboost, medptb}) },

  {"nb2_medboost_lowptb",   addCuts({mtb, nb2, medboost,  lowptb12, "met<300"}) },
  {"nb2_medboost_medptb",   addCuts({mtb, nb2, medboost,  medptb12, "met<300"}) },
  {"nb2_highboost_lowptb",  addCuts({mtb, nb2, highboost, lowptb12}) },
  {"nb2_highboost_medptb",  addCuts({mtb, nb2, highboost, medptb12}) },
};

std::map<TString, std::vector<int>> srMETbins{
  {"nb0_highboost_lownj",        {250, 350, 450}},
  {"nb0_highboost_highnj",       {250, 350, 450}},

  {"nb1_medboost_lowptb",        {200, 250, 300}},
  {"nb1_medboost_medptb",        {200, 250, 300}},
  {"nb1_highboost_lowptb",            {250, 350, 450}},
  {"nb1_highboost_medptb",            {250, 350, 450}},

  {"nb2_medboost_lowptb",        {200, 250, 300}},
  {"nb2_medboost_medptb",        {200, 250, 300}},
  {"nb2_highboost_lowptb",            {250, 350, 450}},
  {"nb2_highboost_medptb",            {250, 350, 450}},
};

const TString nlb0 = "nlbjets==0", nlb1 = "nlbjets==1", nlb2 = "nlbjets>=2";

std::map<TString, TString> phoNormMap{
  {"nb0", nlb0},
  {"nb1", nlb1},
  {"nb2", nlb2}
};

std::map<TString, TString> phocrCuts{
  {"nb0_highboost_lownj",   addCuts({nlb0, highboost, lownj})},
  {"nb0_highboost_highnj",  addCuts({nlb0, highboost, highnj})},

  {"nb1_medboost_lowptb",   addCuts({mtb, nlb1, medboost,  lowptb}) },
  {"nb1_medboost_medptb",   addCuts({mtb, nlb1, medboost,  medptb}) },
  {"nb1_highboost_lowptb",  addCuts({mtb, nlb1, highboost, lowptb}) },
  {"nb1_highboost_medptb",  addCuts({mtb, nlb1, highboost, medptb}) },

  {"nb2_medboost_lowptb",   addCuts({mtb, nlb2, medboost,  lowptb12}) },
  {"nb2_medboost_medptb",   addCuts({mtb, nlb2, medboost,  medptb12}) },
  {"nb2_highboost_lowptb",  addCuts({mtb, nlb2, highboost, lowptb12}) },
  {"nb2_highboost_medptb",  addCuts({mtb, nlb2, highboost, medptb12}) }

};

std::map<TString, std::vector<int>> phocrMETbins = srMETbins;

map<TString, Category> srCatMap(){
  map<TString, Category> cmap;
  for (auto &name : srbins){
    cmap[name] = Category(name, srcuts.at(name), name, BinInfo("met", "#slash{E}_{T}", srMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> phoCatMap(){
  map<TString, Category> cmap;
  for (auto &name : srbins){
    cmap[name] = Category(name, phocrCuts.at(name), name, BinInfo("met", "#slash{E}_{T}^{#gamma}", phocrMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> lepCatMap(){
  TString varlabel = ADD_LEP_TO_MET ? "p_{T}^{W}" : "#slash{E}_{T}";
  map<TString, Category> cmap;
  for (auto &name : srbins){
    cmap[name] = Category(name, srcuts.at(name), name, BinInfo("met", varlabel, srMETbins.at(name), "GeV"));
  }
  return cmap;
}

map<TString, Category> qcdCatMap(){
  return srCatMap();
}

map<TString, Category> zllCatMap{
  {"on-z",  Category("on-z",  "dilepmass > 80 && dilepmass < 100",                      "on Z",   BinInfo("met", "#slash{E}_{T}^{ll}", vector<double>{200, 1000}, "GeV"))},
  {"off-z", Category("off-z", "dilepmass > 20 && (dilepmass < 80 || dilepmass > 100)",  "off Z",  BinInfo("met", "#slash{E}_{T}^{ll}", vector<double>{200, 1000}, "GeV"))}
};


// ------------------------------------------------------------------------
// samples

BaseConfig phoConfig(){
  BaseConfig     config;

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/LowMET/LowMass/znunu";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("singlepho",   "Data",           datadir+"/photoncr/singlepho",  "1.0",  datasel + trigPhoCR);

  config.addSample("photon",      "Photon",         "photoncr/photon",     phowgt, datasel + trigPhoCR);
//  config.addSample("photon",      "Photon",         "photoncr/gjets",      phowgt, datasel + trigPhoCR);
  config.addSample("znunu-sr",    "Z#rightarrow#nu#nu",   "sr/znunu",      lepvetowgt, datasel + trigSR + vetoes);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = phoCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig zllConfig(){
  BaseConfig     config;

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/LowMET/LowMass/zllcr";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("dyll",      "Z#rightarrowll+jets",    "zllcr/zll",                      lepselwgt, datasel + trigDiLepCR);
  config.addSample("ttbar",     "t#bar{t}",               "zllcr/ttbar",                    lepselwgt, datasel + trigDiLepCR);
  config.addSample("doublelep", "Data",                   datadir+"/zllcr/doublelep",       "1.0",     datasel + trigDiLepCR);

  config.sel = baseline;
  config.catMaps = zllCatMap;
  for (auto &c : zllCatMap) config.categories.push_back(c.first);

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig lepConfig(){
  BaseConfig     config;

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/LowMET/LowMass/LLB";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  if (ADD_LEP_TO_MET){
    config.addSample("singlelep",   "Data",          datadir+"/lepcr/singlelep",       "1.0",     datasel + trigLepCR + lepcrsel);
    config.addSample("ttbar",       "t#bar{t}",      "lepcr/ttbar-mg",        onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("wjets",       "W+jets",        "lepcr/wjets-ht",        onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("tW",          "tW",            "lepcr/tW",              onelepcrwgt, datasel + trigLepCR + lepcrsel);
    config.addSample("ttW",         "ttW",           "lepcr/ttW",             onelepcrwgt, datasel + trigLepCR + lepcrsel);
//    config.addSample("qcd",         "QCD",           "lepcr/qcd",             onelepcrwgt, datasel + trigLepCR + lepcrsel);
  }else{
    config.addSample("singlelep",   "Data",          datadir+"/sr/met",    "1.0",     datasel + trigSR + revert_vetoes);
    config.addSample("ttbar",       "t#bar{t}",      "sr/ttbar-mg",        lepselwgt, datasel + trigSR + revert_vetoes);
    config.addSample("wjets",       "W+jets",        "sr/wjets-ht",        lepselwgt, datasel + trigSR + revert_vetoes);
    config.addSample("tW",          "tW",            "sr/tW",              lepselwgt, datasel + trigSR + revert_vetoes);
    config.addSample("ttW",         "ttW",           "sr/ttW",             lepselwgt, datasel + trigSR + revert_vetoes);
//    config.addSample("qcd",         "QCD",           "sr/qcd",             lepselwgt, datasel + trigSR + revert_vetoes);
  }

  config.addSample("ttbar-sr",       "t#bar{t}",      "sr/ttbar-mg",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("wjets-sr",       "W+jets",        "sr/wjets-ht",        lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("tW-sr",          "tW",            "sr/tW",              lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("ttW-sr",         "ttW",           "sr/ttW",             lepvetowgt, datasel + trigSR + vetoes);
//  config.addSample("qcd-sr",         "QCD",           "qcd-4bd/qcd",    lepvetowgt, datasel + trigSR + vetoes);
  config.addSample("rare-sr",        "Rare",          "sr/rare",            lepvetowgt, datasel + trigSR + vetoes);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = lepCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig qcdConfig(){
  BaseConfig     config;

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/LowMET/LowMass/QCD";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  // qcdcr
  config.addSample("data-cr",     "Data",          datadir+"/sr/met",             "1.0",         datasel + trigSR + vetoes + dphi_invert);
  config.addSample("qcd-cr",      "QCD",           "qcd-4bd/qcd",          qcdwgt,      datasel + trigSR + dphi_invert);

  config.addSample("qcd-withveto-cr",  "QCD",      "qcd-4bd/qcd",          qcdvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("qcd-withveto-sr",  "QCD",      "qcd-4bd/qcd",          qcdvetowgt,  datasel + trigSR + vetoes + dphi);

  // qcdcr: other bkg subtraction
  config.addSample("ttbar-cr",       "t#bar{t}",      "sr/ttbar-mg",     lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("wjets-cr",       "W+jets",        "sr/wjets-ht",     lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("tW-cr",          "tW",            "sr/tW",           lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("ttW-cr",         "ttW",           "sr/ttW",          lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);
  config.addSample("znunu-cr",       "Znunu",         "sr/znunu",        lepvetowgt,  datasel + trigSR + vetoes + dphi_invert);

  // onelepcr: norm correction for other bkg subtraction
  config.addSample("data-norm",      "Data",          datadir+"/sr/met",          "1.0",       datasel + trigSR + dphi + revert_vetoes);
  config.addSample("ttbar-norm",     "t#bar{t}",      "sr/ttbar-mg",     lepselwgt,   datasel + trigSR + dphi + revert_vetoes);
  config.addSample("wjets-norm",     "W+jets",        "sr/wjets-ht",     lepselwgt,   datasel + trigSR + dphi + revert_vetoes);
  config.addSample("tW-norm",        "tW",            "sr/tW",           lepselwgt,   datasel + trigSR + dphi + revert_vetoes);
  config.addSample("ttW-norm",       "ttW",           "sr/ttW",          lepselwgt,   datasel + trigSR + dphi + revert_vetoes);
  config.addSample("qcd-norm",       "QCD",           "qcd-4bd/qcd",     lepselwgt,   datasel + trigSR + dphi + revert_vetoes);

  // qcdsr
  config.addSample("qcd-sr",      "QCD",           "qcd-4bd/qcd",          srqcdwgt,      datasel + trigSR + dphi);

  config.sel = baseNoDPhi;
  config.categories = srbins;
  config.catMaps = srCatMap();
  config.crCatMaps = qcdCatMap();

  return config;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

BaseConfig sigConfig(){
  BaseConfig     config;

  config.inputdir = "/tmp/trees";
  config.outputdir = "/tmp/LowMET/LowMass/sig";
  config.header = "#sqrt{s} = 13 TeV, "+lumistr+" fb^{-1}";

  config.addSample("data-sr",        "Data",             datadir+"/sr/met",                    "1.0",  datasel + trigSR + vetoes);

//  config.addSample("T2fbd_375_355",  "T2-4bd(375,355)",  "signals/T2fbd_375_355",  sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2fbd_375_325",  "T2-4bd(375,325)",  "signals/T2fbd_375_325",  sigwgt, datasel + trigSR + vetoes);
//  config.addSample("T2fbd_375_295",  "T2-4bd(375,295)",  "signals/T2fbd_375_295",  sigwgt, datasel + trigSR + vetoes);

  config.sel = baseline;
  config.categories = srbins;
  config.catMaps = srCatMap();

  return config;
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

map<TString, BinInfo> varDict {
  {"norm",      BinInfo("met", "#slash{E}_{T}", vector<int>{0, 1000}, "GeV")},
  {"met",       BinInfo("met", "#slash{E}_{T}", vector<int>{250, 350, 450, 550, 650, 750, 1000}, "GeV")},
  {"metgx",       BinInfo("met", "#slash{E}_{T}^{(#gamma)}", vector<int>{250, 350, 450, 550, 650, 850}, "GeV")},
  {"metzg",       BinInfo("met", "#slash{E}_{T}^{#gamma/ll}", vector<int>{250, 350, 450, 550, 650, 850}, "GeV")},
  {"origmet",   BinInfo("origmet", "Original #slash{E}_{T}", 16, 0, 800, "GeV")},
  {"njets",     BinInfo("njets", "N_{j}", 8, -0.5, 7.5)},
  {"njl",       BinInfo("njl", "N_{j}^{ISR}", 4, 0.5, 4.5)},
  {"nlbjets",   BinInfo("nlbjets", "N_{B}^{loose}", 5, -0.5, 4.5)},
  {"nbjets",    BinInfo("nbjets",  "N_{B}^{medium}", 5, -0.5, 4.5)},
  {"dphij1met", BinInfo("dphij1met", "#Delta#phi(j_{1},#slash{E}_{T})", 30, 0, 3)},
  {"dphij2met", BinInfo("dphij2met", "#Delta#phi(j_{2},#slash{E}_{T})", 30, 0, 3)},
  {"metovsqrtht",BinInfo("metovsqrtht", "#slash{E}_{T}/#sqrt{H_{T}}", 10, 0, 20)},
  {"dphij1lmet",BinInfo("dphij1lmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", vector<double>{0, 2, 3})},
  {"dphij1lmet_fine",BinInfo("dphij1lmet", "#Delta#phi(j_{1}^{ISR},#slash{E}_{T})", 12, 0, 3)},
  {"mtcsv12met",BinInfo("mtcsv12met", "min(m_{T}(b_{1},#slash{E}_{T}),m_{T}(b_{2},#slash{E}_{T}))", 6, 0, 300)},
  {"leptonpt",  BinInfo("leptonpt", "p_{T}^{lep} [GeV]", 16, 0, 800)},
  {"leptonptovermet",  BinInfo("leptonpt/met", "p_{T}^{lep}/#slash{E}_{T}", 20, 0, 1.)},
  {"j1lpt",     BinInfo("j1lpt", "p_{T}(j_{1}^{ISR}) [GeV]", 10, 250, 750)},
  {"csvj1pt",   BinInfo("csvj1pt/1", "p_{T}(b_{1}) [GeV]", 8, 20, 100)}
};

}
#endif /* ESTTOOLS_LMPARAMETERS_HH_ */
