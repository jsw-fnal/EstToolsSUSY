#! /usr/bin/python

'''
Calculate the full (stat.+syst.) uncertainty of the background prediction.
Predicted yields and stat. uncertainties (MC stat. and CR data stat.) are taken from the output of background prediction macro.
[see: AnalysisMethods/macros/0LepSearchRegions/getZeroLeptonPrediction.C] 
Syst. uncertainties are calculate based on the config files for datacard production.
[see: Limits/Datacards/setup/values_0l_unc_*.conf] 
'''

import os
import math
import json
import argparse
import ROOT as rt
from ROOT import TGraphAsymmErrors
import numpy as np
rt.gROOT.SetBatch(True)

uncdir = '/uscms/home/mkilpatr/nobackup/CMSSW_9_4_10/src/AnalysisMethods/EstTools/SUSYNano19/uncertainties_LowMET_031320/'

uncfiles=[
uncdir + 'values_unc_LowMET_ll.conf',
 ]

#all_bin_unc_file = 'values_0l_unc_all.conf'
all_bin_unc_file = ''

all_samples=('ttbarplusw',)
graph_names=('Graph_from_ttbarplusw_pred_gr',)
table_header='Search region & \\met [GeV]  &  Lost lepton  &  \\znunu  & ttZ & Diboson & QCD  &  total SM  &  $N_{\\rm data}$  \\\\ \n'

pred_total_name = 'Graph_from_pred_total_gr'

# ordered bin list
binlist=(
    "bin_lm_nb0_nivf0_highptisr_nj2to5_met400_MET_pt250toinf",
    "bin_lm_nb0_nivf0_highptisr_nj6_met400_MET_pt250toinf",
    "bin_lm_nb0_nivf1_highptisr_nj2to5_met400_MET_pt250toinf",
    "bin_lm_nb0_nivf1_highptisr_nj6_met400_MET_pt250toinf",
    "bin_lm_nb1_nivf0_lowmtb_lowptisr_lowptb_met300_MET_pt250toinf",
    "bin_lm_nb1_nivf0_lowmtb_lowptisr_medptb_met300_MET_pt250toinf",
    "bin_lm_nb1_nivf0_lowmtb_highptisr_lowptb_met400_MET_pt250toinf",
    "bin_lm_nb1_nivf0_lowmtb_highptisr_medptb_met400_MET_pt250toinf",
    "bin_lm_nb1_nivf1_lowmtb_medptisr_lowptb_met300_MET_pt250toinf",
    "bin_lm_nb2_lowmtb_lowptisr_lowptb12_met300_MET_pt250toinf",
    "bin_lm_nb2_lowmtb_lowptisr_medptb12_met300_MET_pt250toinf",
    "bin_lm_nb2_lowmtb_lowptisr_highptb12_nj7_met300_MET_pt250toinf",
    "bin_lm_nb2_lowmtb_highptisr_lowptb12_met400_MET_pt250toinf",
    "bin_lm_nb2_lowmtb_highptisr_medptb12_met400_MET_pt250toinf",
    "bin_lm_nb2_lowmtb_highptisr_highptb12_nj7_met400_MET_pt250toinf",
    "bin_lmVal_nb0_lowmtb_nivf0_MET_pt250toinf",
    "bin_lmVal_nb0_lowmtb_nivf1_MET_pt250toinf",
    "bin_lmVal_nbgeq1_lowmtb_nivf0_MET_pt250toinf",
    "bin_lmVal_nbgeq1_lowmtb_nivf1_MET_pt250toinf",
    "bin_hmVal_nb1_lowmtb_nj7_nrtgeq1_MET_pt250to400",
    "bin_hmVal_nb1_lowmtb_nj7_nrtgeq1_MET_pt400toinf",
    "bin_hmVal_nb2_lowmtb_nj7_nrtgeq1_MET_pt250to400",
    "bin_hmVal_nb2_lowmtb_nj7_nrtgeq1_MET_pt400toinf",
    "bin_hmVal_nb1_highmtb_nj5_nt0_nrt0_nw0_MET_pt250to400",
    "bin_hmVal_nb1_highmtb_nj5_nt0_nrt0_nw0_MET_pt400toinf",
    "bin_hmVal_nb2_highmtb_nj5_nt0_nrt0_nw0_MET_pt250to400",
    "bin_hmVal_nb2_highmtb_nj5_nt0_nrt0_nw0_MET_pt400toinf",
    "bin_hmVal_nb1_highmtb_nt1_nrt0_nw0_MET_pt250to400",
    "bin_hmVal_nb1_highmtb_nt1_nrt0_nw0_MET_pt400toinf",
    "bin_hmVal_nb1_highmtb_nt0_nrt0_nw1_MET_pt250to400",
    "bin_hmVal_nb1_highmtb_nt0_nrt0_nw1_MET_pt400toinf",
    "bin_hmVal_nb1_highmtb_nt0_nrt1_nw0_MET_pt250to400",
    "bin_hmVal_nb1_highmtb_nt0_nrt1_nw0_MET_pt400toinf",
    "bin_hmVal_nb1_highmtb_nrtntnwgeq2_MET_pt250to400",
    "bin_hmVal_nb1_highmtb_nrtntnwgeq2_MET_pt400toinf",
    "bin_hmVal_nb2_highmtb_nt1_nrt0_nw0_MET_pt250to400",
    "bin_hmVal_nb2_highmtb_nt1_nrt0_nw0_MET_pt400toinf",
    "bin_hmVal_nb2_highmtb_nt0_nrt0_nw1_MET_pt250to400",
    "bin_hmVal_nb2_highmtb_nt0_nrt0_nw1_MET_pt400toinf",
    "bin_hmVal_nb2_highmtb_nt0_nrt1_nw0_MET_pt250to400",
    "bin_hmVal_nb2_highmtb_nt0_nrt1_nw0_MET_pt400toinf",
    "bin_hmVal_nb2_highmtb_nrtntnwgeq2_MET_pt250to400",
    "bin_hmVal_nb2_highmtb_nrtntnwgeq2_MET_pt400toinf"
)


labelMap = {
    'lowptisr': r'($300\leq\ptisr<500$\,GeV)',
    'ntgeq1': r'($\nt\geq1$)',
    'nt2': r'($\nt=2$)',
    'nivf0': r'($\nsv=0$)',
    'nivf1': r'($\nsv\geq1$)',
    'nw2': r'($\nw=2$)',
    'nj2to5': r'($2\leq\nj\leq5$)',
    'nb2': r'($\nb\geq2$)',
    'nbeq2': r'($\nb=2$)',
    'nb3': r'($\nb\geq3$)',
    'nb1': r'($\nb=1$)',
    'nbgeq1': r'($\nb\geq1$)',
    'nb0': r'($\nb=0$)',
    'nrt2': r'($\nrt=2$)',
    'medptisr': r'($\ptisr\geq300$\,GeV)',
    'highptisr': r'($\ptisr\geq500$\,GeV)',
    'nj5': r'($\nj\geq5$)',
    'nj7': r'($\nj\geq7$)',
    'highptb': r'($\ptb\geq70$\,GeV)',
    'hm': r'(high \dm)',
    'hmVal': r'(high \dm)',
    'nw0': r'($\nw=0$)',
    'nwgeq1': r'($\nw\geq1$)',
    'nw1': r'($\nw=1$)',
    'nrt0': r'($\nrt=0$)',
    'nrt1': r'($\nrt=1$)',
    'lowptb': r'($\ptb<40$\,GeV)',
    'medptb': r'($40<\ptb<70$\,GeV)',
    'nt0': r'($\nt=0$)',
    'lm': r'(low \dm)',
    'lmVal': r'(low \dm)',
    'lowptb12': r'($\ptbonetwo<80$\,GeV)',
    'highptb12': r'($\ptbonetwo\geq140$\,GeV)',
    'lowmtb': r'($\mtb<175$~\GeV)',
    'highmtb': r'($\mtb\geq175$~\GeV)',
    'nt1': r'($\nt=1$)',
    'medptb12': r'($80<\ptbonetwo<140$\,GeV)',
    'nrtgeq1': r'($\nrt\geq1$)',
    'nj6': r'($\nj\geq6$)',
    'nrtntnwgeq2': r'($(\nt+\nrt+\nw)\geq2$)',
    'nrtntnwgeq3': r'($(\nt+\nrt+\nw)\geq3$)',
    'htlt1000':    r'($\Ht<1000$)',
    'htgt1000':    r'($\Ht\geq1000$)',
    'ht1000to1500':r'($1000\leq\Ht<1500$)',
    'htgt1500':    r'($\Ht\geq1500$)',
    'htlt1300':    r'($\Ht<1300$)',
    'htgt1300':    r'($\Ht\geq1300$)',
    'lmNoDPhi':    r'(low $\Delta m$)',
    'hmNoDPhi':    r'(high $\Delta m$)',
    'met400':	  r'(#slash{E}_{T} < 400)',
    'met300':	  r'(#slash{E}_{T} < 300)',
    }


def addAsymm(e, asymm):
    print e, asymm
    e_low = math.sqrt(e[0]*e[0] + asymm[0]*asymm[0])
    e_up  = math.sqrt(e[1]*e[1] + asymm[1]*asymm[1])
    return (e_low, e_up)

def sumUncLogNorm(unc_list, p):
# syst_histo[systemaitc][bintype][region][direction]
    log_syst_up_sum = 0.
    log_syst_down_sum = 0.
    #print(unc_list)
    #print(p)
    if p == 0: return [0,0]
    for err in unc_list:
        p_up    = err[1]
        p_down  = err[0]
        if p_up == 0 or p_down == 0: continue
        log_syst_up     = p_up / p
        log_syst_down   = p_down / p
        # If both systematics go the same direction, need to symmetrize
        # Because all the nuisance parameters are log-normal, symmetrize by dividing by the geometric mean
        if ((log_syst_up > 1) and (log_syst_down > 1)) or ((log_syst_up < 1) and (log_syst_down < 1)):
            geometric_mean = np.sqrt(log_syst_up * log_syst_down)
            log_syst_up   /= geometric_mean
            log_syst_down /= geometric_mean
        # Because all the nuisance parameters are log-normal, sum the log of the ratios in quadrature
        # Sum (the square of the log of) all the ratios that are greater than 1
        # Sum (the square of the log of) all the ratios that are less than 1
        # Then at the end, take the exponential of the square root of each sum to get the total systematic ratio
        if log_syst_up > 1 or log_syst_down < 1:
            log_syst_up_sum     += np.log(log_syst_up)**2
            log_syst_down_sum   += np.log(log_syst_down)**2
        else:
            log_syst_up_sum     += np.log(log_syst_down)**2
            log_syst_down_sum   += np.log(log_syst_up)**2
        log_syst_up_total   = np.exp( np.sqrt(log_syst_up_sum))
        log_syst_down_total = np.exp(-np.sqrt(log_syst_down_sum)) # Minus sign is needed because this is the *down* ratio
        log_final_up   = log_syst_up_total
        log_final_down = log_syst_down_total
    #print "pred={0}, log_final_up={1}, log_final_down={2}".format(p, log_final_up, log_final_down)
    return [p - log_final_down*p, log_final_up*p - p]

def sumUnc(unc_list):
    '''Add uncertainties in quadrature.'''
    return math.sqrt(sum(err*err for err in unc_list))


# relUnc[type][bin][sample] : percentage syst. uncertainty of each 'type' per 'bin' per 'sample'
# absUnc[bin][type] : absolute uncertainty per 'bin' of each 'type'
# yields[bin][sample] : predicted bkg yields per bin per sample 
# statUnc[bin] : stat. (MC + data CR) unc. per bin [asymmetric errors]
# systUnc[bin] : syst. unc. per bin
# fullUnc[bin] : full unc. per bin

relUnc={}
absUnc={}
absUnc_pieces={'ttbarplusw':{}, 'znunu':{}, 'qcd':{}, 'ttZ':{}, 'diboson':{}}
yields={}
yields_total={}
yields_data={}
statUnc={} #asymm
statUnc_pieces={} #asymm 
systUnc={}
systUnc_pieces={'ttbarplusw':{}, 'znunu':{}, 'qcd':{}, 'ttZ':{}, 'diboson':{}}
fullUnc={} #asymm
fullUnc_pieces={'ttbarplusw':{}, 'znunu':{}, 'qcd':{}, 'ttZ':{}, 'diboson':{}} #asymm
allVals = {}

def readRelUnc(config_path):
    '''Read in percentage syst. uncertainty from the config files.'''
    for unc_fn in uncfiles:
        with open(os.path.join(config_path, unc_fn), 'r') as f:
	    isUp, isDown = False, False
            for line in f.readlines():
                try:
                    bin, type_, sample, value = line.split()
                except ValueError:
                    continue
                if bin not in binlist or sample not in all_samples:
                    # ignore CR syst., e.g., "bin_onelepcr_250_5_1_0_0"
                    continue
		if "Up" in type_:
                    isUp = True
                    isDown = False
		if "Down" in type_:
                    isUp = False
                    isDown = True
                type = type_.strip("_Up")
                type = type_.strip("_Down")
                if type not in relUnc:
                    relUnc[type] = {}
                if bin not in relUnc[type]:
                    relUnc[type][bin] = {}
                if sample in all_samples:
                    if isUp:
                        up = float(value)
                    elif isDown:
                        down = float(value)
                        relUnc[type][bin][sample] = (down, up)
                        isUp, isDown = False, False
                    else:
                        up = float(value)-1 if float(value) > 1 else 1 - float(value)
                        down = float(value)-1 if float(value) > 1 else 1 - float(value)
                        relUnc[type][bin][sample] = (1-down, 1+up)

    # for all bin uncs
    if all_bin_unc_file != '':
        with open(os.path.join(config_path, all_bin_unc_file), 'r') as f:
            for line in f.readlines():
                try:
                    bin, type, sample, value = line.split()
                except ValueError:
                    continue
                for samp in all_samples:
                    if samp not in sample:
                        continue
                    print 'adding unc %s for %s'%(type, samp)                    
                    if type not in relUnc:
                        relUnc[type] = {}
                    # bin=='all' in config file
                    for bin in binlist:
                        if bin not in relUnc[type]:
                            relUnc[type][bin] = {sample : (float(value)-1, float(value)-1)}

    # if a type of unc. is not define for some samples/bins, then fill zero
    for type in relUnc:
        for bin in binlist:
            if bin not in relUnc[type]:
                # for bin-specific unc. (e.g., qcd-tf) : set other bins to 0
                relUnc[type][bin] = {sample: (1.0,1.0) for sample in all_samples}
            else:
                for sample in all_samples:
                    # for sample specific unc.: set other samples to 0
                    if sample not in relUnc[type][bin]:
                        relUnc[type][bin][sample] = (1.0, 1.0)

def readYields(pred_file):
    ''' Read in predicted bkg yields and the stat. unc. 
    
    pred_file -- input root file 
    '''
    f = rt.TFile(pred_file)
    for hname, sample in zip(graph_names, all_samples):
        h = f.Get(hname)
        for ibin in xrange(0, h.GetN()):
            bin = binlist[ibin]
            if bin not in yields:
                yields[bin] = {}
                yields_total[bin] = 0.
                statUnc_pieces[bin] = {}
            y = h.GetY()[ibin]
            e_up = h.GetErrorYhigh(ibin)
            e_low = h.GetErrorYlow(ibin)
            yields[bin][sample] = y
            yields_total[bin]  += y
            if sample == 'rare': statUnc_pieces[bin][sample] = (min(e_up,y), min(e_up,y))  # don't want MC stat unc > 100%
            else :               statUnc_pieces[bin][sample] = (e_low, e_up)
    h = f.Get('data')
    for ibin in xrange(0, h.GetNbinsX()):
        bin = binlist[ibin]
        yields_data[bin] = (h.GetBinContent(ibin+1), h.GetBinError(ibin+1))
    # get total pred (w/ asymmetric errors)
    h = f.Get(pred_total_name)
    for ibin in xrange(0, h.GetN()):
        bin = binlist[ibin]
        e_up = h.GetErrorYhigh(ibin)
        e_low = h.GetErrorYlow(ibin)
        statUnc[bin] = (e_low, e_up)
    f.Close()

def calcAbsUnc():
    ''' Calculate syst. uncertainty.
    For uncertainties of the same type, add linearly for each bin.
    For uncertainties of different types, add in quadrature for each bin.
    '''
    absUnc = {bin:{} for bin in binlist}
    for sample in all_samples: absUnc_pieces[sample] = {bin:{} for bin in binlist}
    for bin in binlist:
        absUnc[bin] = {type: [0, 0] for type in relUnc.keys()}
        for sample in all_samples: absUnc_pieces[sample][bin] = {type:[0, 0] for type in relUnc.keys()}
        for type in relUnc:
            for sample in all_samples:
                # Add the same type of unc. linearly
                tempUnc_down, tempUnc_up = relUnc[type][bin][sample][0] * yields[bin][sample], relUnc[type][bin][sample][1] * yields[bin][sample]
                absUnc[bin][type][0]                += tempUnc_down
                absUnc_pieces[sample][bin][type][0] += tempUnc_down
                absUnc[bin][type][1]                += tempUnc_up
                absUnc_pieces[sample][bin][type][1] += tempUnc_up
		
    for bin in absUnc:
        # Add different types of unc. in quadrature
        #systUnc[bin] = sumUnc(absUnc[bin].values())
        systUnc[bin] = sumUncLogNorm(absUnc[bin].values(), yields_total[bin])
        fullUnc[bin] = addAsymm(systUnc[bin], statUnc[bin])
        for sample in all_samples:
            systUnc_pieces[sample][bin] = sumUncLogNorm(absUnc_pieces[sample][bin].values(), yields[bin][sample])
            fullUnc_pieces[sample][bin] = addAsymm(systUnc_pieces[sample][bin], statUnc_pieces[bin][sample])
            

def writeFullUnc(pred_file):
    ''' Update the input root file, add a hist with total prediction and full uncertainty. '''
    f = rt.TFile(pred_file, 'UPDATE')
    h = TGraphAsymmErrors(f.Get(pred_total_name).Clone('bkgtotal_unc_sr'))
    h_pieces = {}
    for hname, sample in zip(graph_names, all_samples):
        h_pieces[sample] = TGraphAsymmErrors(f.Get(hname).Clone(sample+'_unc_sr'))
    print "%30s %10s %16s" % ('bin', 'total pred', 'total unc.')
    for ibin in xrange(0, h.GetN()):
        bin = binlist[ibin]
        val = h.GetY()[ibin]
        e_low, e_up = fullUnc[bin]
        h.SetPointEYlow(ibin, e_low)
        h.SetPointEYhigh(ibin, e_up)
        print "%30s %10.2f +%8.2f -%8.2f" % (bin, val, e_up, e_low)
        allVals[bin] = {'bkg':(val,e_low,e_up)}
        for sample in all_samples:
            val = yields[bin][sample]
            e_low, e_up = fullUnc_pieces[sample][bin]
            h_pieces[sample].SetPointEYlow(ibin, e_low)
            h_pieces[sample].SetPointEYhigh(ibin, e_up)
            allVals[bin][sample] = (val,e_low,e_up)  
    h.Write('bkgtotal_unc_sr', rt.TObject.kOverwrite)
    for sample in all_samples : h_pieces[sample].Write(sample+'_unc_sr', rt.TObject.kOverwrite)
    f.Close()

def makeYieldTable(output='pred_sr.tex'):
    ''' Make a Latex-formatted table with each bkg plus unc, total bkg plus unc, and observed data for every bin. '''
    print '\nprinting yield table...\n'
    s  = beginTable()
    s += table_header
    s += '\\hline\n'
    s += makeTable()
    s += endTable(135,182)
    print s
    with open(output, 'w') as f:
        print >> f, s
   
def beginTable():
    '''Add a break between the bins to fit on each page'''
    s  = '\\begin{table}[!h]\n'
    s += '\\begin{center}\n'
    s += '\\resizebox*{0.6\\textwidth}{!}{\n'
    s += '\\begin{tabular}{|c||c||c|c|c|c|c|c|}'
    s += '\\hline\n'
    return s

def endTable(ibini, ibinf):
    '''Add a break between the bins to fit on each page'''
    label='tab:pred-lm'
    if ibini == 53:
        label='tab:pred-hm-1'
    elif ibini == 94:
        label='tab:pred-hm-2'
    elif ibini == 135:
        label='tab:pred-hm-3'
    s  = '\\hline\n'
    s += '\\end{tabular}}\n'
    s += '\\caption[' + label + ']{The SM prediction for Run 2 with \datalumi for each background in the analysis for bins ' + str(ibini) + '--' + str(ibinf) + '. The Rare prediction is a combination of ttZ and diboson MC.}\n'
    s += '\\end{center}\n'
    s += '\\end{table}\n'
    return s


def makeTable():
    ''' Put together the table chunk for the given nj,nb,mtb,nt mega-bin. '''
    sections=[]
    s=''
    ibin=0
    ibini=0
    for bin in binlist: 
        sec, met= bin.lstrip('bin_').rsplit('_', 1)
        if sec not in sections:
            sections.append(sec)
            s += chunkHeader(sec)
        xlow, xhigh = met.lstrip('met_pt').split('to')
        metlabel = r'$>%s$'%xlow if xhigh=='inf' else '$-$'.join([xlow, xhigh])
        s += '%d & '%ibin
        ibin = ibin+1
        s += metlabel
        for bkg in list(all_samples)+['bkg']:
            if bkg == 'diboson': continue
            n, e_low, e_up = allVals[bin][bkg]
            if bkg == 'ttZ':
                n1, e1_low, e1_up = allVals[bin]["diboson"]
                n += n1
                e_low = sumUnc([e_low, e1_low])
                e_up  = sumUnc([e_up, e1_up])
            s += formatPrediction(n,e_low,e_up)
        n, e = yields_data[bin]
        s += ' & ' + str(int(n))
        s += ' \\\\ \n'
        if ibin == 53 or ibin == 94 or ibin == 135:
	    s += endTable(ibini, ibin-1)
            s += beginTable()
            s += table_header
	    ibini=ibin
    return s

# formats the prediction nEvents +/- error
def formatPrediction(n,e_low,e_up):
    if n>=10:
        n = str(int(round(n,0)))
        e_low = str(int(round(e_low,0)))
        e_up  = str(int(round(e_up,0)))
    elif n>=1:
        n = str(round(n,1))
        e_low = str(round(e_low,1))
        e_up  = str(round(e_up,1))
    else:
        n = str(round(n,2))
        e_low = str(round(e_low,2))
        e_up  = str(round(e_up,2))
    if n=='0.0':
        if e_up=='0.0':
            return ' & $<$0.01'
        return ' & $<$' + e_up
    if e_low==e_up:
        return ' & $ %s\\pm%s $ ' %(n, e_up)
    else:
        return ' & $ %s\,^{+%s}_{-%s} $ ' %(n, e_up, e_low)


# puts together the bin header for bins of nJets, mtb, nTop (no selection on nB)
def chunkHeader(sec):
    ''' Put together the mega-bin chunk header. '''
    cats = sec.split('_')
    labs = [labelMap[c] for c in cats]
    ncolumn = len(all_samples)+3
    s  = '\\hline\n'
    s += '\\multicolumn{'+str(ncolumn)+'}{c}{'
    s += ', '.join(labs)
    s += '} \\\\ \n'
    s += '\\hline\n' 
    return s


def main():
    parser = argparse.ArgumentParser('Calculate the full (stat.+syst.) uncertainty of the background prediction.')
    parser.add_argument('predfile',
        default='srpred.root',
        help='Input prediction file. Default: %(default)s'
    )
    parser.add_argument('-c', '--configdir',
        dest='configdir',
        default='syst',
        help='Uncertainties configs directory. Default: %(default)s'
    )
    parser.add_argument('-t', '--printTable',
        dest='printTable',
        action='store_true',
        help='print the full bkg prediction table: %(default)s'
    )
    args = parser.parse_args()
    
    readRelUnc(args.configdir)
    readYields(args.predfile)
    calcAbsUnc()
    writeFullUnc(args.predfile)
    if args.printTable : makeYieldTable()


if __name__=='__main__':
    main()
