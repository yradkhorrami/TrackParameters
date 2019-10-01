#include <iostream>
#include <TString.h>
#include <TH1F.h>
#include <TH1I.h>
#include <TH1D.h>
#include <TF1.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TObjArray.h>
#include <TEventList.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TPaveStats.h>
#include <TGraphErrors.h>
#include <TLatex.h>

using namespace std;

void Track_Parameters()
{

ildStyle->SetOptStat(001111111);

string file_dir = "/afs/desy.de/group/flc/pool/radkhory/TrackParameters/";
string plot_dir = "/afs/desy.de/group/flc/pool/radkhory/TrackParameters/Analysis/macro/Plots/";
TFile *file =  TFile::Open((file_dir + "TrkParameters.root").c_str(), "READONLY");
string input_tree_name = "TrackParameters";
TTree *tree = (TTree*)file->Get(input_tree_name.c_str());
int nEntries = tree->GetEntries();

float p_min = 4;
float p_max = 1000;
int true_pdg = 321;

float r_cut = 100000;
float rho_cut = 100000;
float weight_cut = 0.0;


float fit_min = -2.;
float fit_max = 2.;

float residual_min = -0.05;
float residual_max = 0.05;
float uncertainty_min = 0.;
float uncertainty_max = 0.05;
float pull_min = -5.;
float pull_max = 5.;

string true_par;
string par;
string apar;
string plot_init = "";
string momentum_stat = "";
float TextSize = 0.025;

int mom_min = p_min;
int mom_max = p_max;
string moment = "";
if (p_min == 0 && p_max >= 100)
{
	momentum_stat = "_all_P";
	moment = "All p";
}
else if (p_min == 0 && p_max < 3)
{
	momentum_stat = ("_P_less_than_"+to_string(mom_max)+"_GeV").c_str();
	moment = ("p#leq "+to_string(mom_max)).c_str();
}
else if (p_min != 0 && p_min < 3 && p_max < 10)
{
	momentum_stat = ("_P_between_"+to_string(mom_min)+"_and_"+to_string(mom_max)+"_GeV").c_str();
	moment = (to_string(mom_min)+" #leq p#leq "+to_string(mom_max)).c_str();
}
else if (p_min > 3 && p_max >= 100)
{
	momentum_stat = ("_P_greater_than_"+to_string(mom_min)+"_GeV").c_str();
	moment = ("p#geq "+to_string(mom_min)).c_str();
}
char header_moment[moment.size() + 1];
strcpy(header_moment, moment.c_str());
if (true_pdg == 11)
{
	true_par = "m_{e^{#pm}}";
	par = "m_{e^{-}}";
	apar = "m_{e^{+}}";
	plot_init = "Electron";
}
if (true_pdg == 13)
{
	true_par = "m_{#mu^{#pm}}";
	par = "m_{#mu^{-}}";
	apar = "m_{#mu^{+}}";
	plot_init = "Muon";
}
if (true_pdg == 321)
{
	true_par = "m_{K^{#pm}}";
	par = "m_{K^{+}}";
	apar = "m_{K^{-}}";
	plot_init = "Kaon";
}
if (true_pdg == 2212)
{
	true_par = "m_{p}";
	par = "m_{p^{+}}";
	apar = "m_{p^{-}}";
	plot_init = "Proton";
}
string type = ("True " + plot_init + "s").c_str();
char header_par[type.size() + 1];
strcpy(header_par, type.c_str());
int radi_cut = r_cut;
string r3D = ("r_{3D} #leq "+to_string(radi_cut)).c_str();
char header_r3D[r3D.size() + 1];
strcpy(header_r3D, r3D.c_str());
int _rho_cut = rho_cut;
string r2D = ("r_{2D} #leq "+to_string(_rho_cut)).c_str();
char header_r2D[r2D.size() + 1];
strcpy(header_r2D, r2D.c_str());
string wei_cut = to_string(weight_cut).substr(0,to_string(weight_cut).find(".")+2+1);
string wei = ("weight #geq "+wei_cut).c_str();
char header_wei[wei.size() + 1];
strcpy(header_wei, wei.c_str());

char true_particle[true_par.size() + 1];
strcpy(true_particle, true_par.c_str());
char particle[par.size() + 1];
strcpy(particle, par.c_str());
char anti_particle[apar.size() + 1];
strcpy(anti_particle, apar.c_str());

string type_all = ("All " + plot_init + "s").c_str();
char par_type_all[type_all.size() + 1];
strcpy(par_type_all, type_all.c_str());

string type_par = (plot_init + "s").c_str();
char par_type_par[type_par.size() + 1];
strcpy(par_type_par, type_par.c_str());

string type_Apar = ("anti-" + plot_init + "s").c_str();
char par_type_Apar[type_Apar.size() + 1];
strcpy(par_type_Apar, type_Apar.c_str());

TH1* hist_momentum = new TH1F("hist_momentum", "; p [GeV]; # tracks" , 100,0,20);
hist_momentum->SetLineColor(4); hist_momentum->SetLineWidth(1);
TH1* hist_momentum_Par = new TH1F("hist_momentum_Par", "; p [GeV]; # tracks" , 100,0,20);
hist_momentum_Par->SetLineColor(1); hist_momentum_Par->SetLineWidth(1);
TH1* hist_momentum_aPar = new TH1F("hist_momentum_aPar", "; p [GeV]; # tracks" , 100,0,20);
hist_momentum_aPar->SetLineColor(6); hist_momentum_aPar->SetLineWidth(1);

TH1* hist_residual_d0_pion_mass = new TH1F("hist_residual_d0_pion_mass", "; d_{0} residual; # tracks" , 100,residual_min,residual_max);
hist_residual_d0_pion_mass->SetLineColor(2); hist_residual_d0_pion_mass->SetLineWidth(1);
TH1* hist_residual_d0_true_mass = new TH1F("hist_residual_d0_true_mass", "; d_{0} residual; # tracks" , 100,residual_min,residual_max);
hist_residual_d0_true_mass->SetLineColor(4); hist_residual_d0_true_mass->SetLineWidth(1);
TH1* hist_residual_d0_true_mass_Par = new TH1F("hist_residual_d0_true_mass_Par", "; d_{0} residual; # tracks" , 100,residual_min,residual_max);
hist_residual_d0_true_mass_Par->SetLineColor(1); hist_residual_d0_true_mass_Par->SetLineWidth(1);
TH1* hist_residual_d0_true_mass_aPar = new TH1F("hist_residual_d0_true_mass_aPar", "; d_{0} residual; # tracks" , 100,residual_min,residual_max);
hist_residual_d0_true_mass_aPar->SetLineColor(6); hist_residual_d0_true_mass_aPar->SetLineWidth(1);
TH1* hist_residual_Omega_pion_mass = new TH1F("hist_residual_Omega_pion_mass", "; Omega residual; # tracks" , 100,residual_min,residual_max);
hist_residual_Omega_pion_mass->SetLineColor(2); hist_residual_Omega_pion_mass->SetLineWidth(1);
TH1* hist_residual_Omega_true_mass = new TH1F("hist_residual_Omega_true_mass", "; Omega residual; # tracks" , 100,residual_min,residual_max);
hist_residual_Omega_true_mass->SetLineColor(4); hist_residual_Omega_true_mass->SetLineWidth(1);
TH1* hist_residual_Omega_true_mass_Par = new TH1F("hist_residual_Omega_true_mass_Par", "; Omega residual; # tracks" , 100,residual_min,residual_max);
hist_residual_Omega_true_mass_Par->SetLineColor(1); hist_residual_Omega_true_mass_Par->SetLineWidth(1);
TH1* hist_residual_Omega_true_mass_aPar = new TH1F("hist_residual_Omega_true_mass_aPar", "; Omega residual; # tracks" , 100,residual_min,residual_max);
hist_residual_Omega_true_mass_aPar->SetLineColor(6); hist_residual_Omega_true_mass_aPar->SetLineWidth(1);
TH1* hist_residual_Phi_pion_mass = new TH1F("hist_residual_Phi_pion_mass", "; Phi residual; # tracks" , 100,residual_min,residual_max);
hist_residual_Phi_pion_mass->SetLineColor(2); hist_residual_Phi_pion_mass->SetLineWidth(1);
TH1* hist_residual_Phi_true_mass = new TH1F("hist_residual_Phi_true_mass", "; Phi residual; # tracks" , 100,residual_min,residual_max);
hist_residual_Phi_true_mass->SetLineColor(4); hist_residual_Phi_true_mass->SetLineWidth(1);
TH1* hist_residual_Phi_true_mass_Par = new TH1F("hist_residual_Phi_true_mass_Par", "; Phi residual; # tracks" , 100,residual_min,residual_max);
hist_residual_Phi_true_mass_Par->SetLineColor(1); hist_residual_Phi_true_mass_Par->SetLineWidth(1);
TH1* hist_residual_Phi_true_mass_aPar = new TH1F("hist_residual_Phi_true_mass_aPar", "; Phi residual; # tracks" , 100,residual_min,residual_max);
hist_residual_Phi_true_mass_aPar->SetLineColor(6); hist_residual_Phi_true_mass_aPar->SetLineWidth(1);
TH1* hist_residual_tanLambda_pion_mass = new TH1F("hist_residual_tanLambda_pion_mass", "; tanLambda residual; # tracks" , 100,residual_min,residual_max);
hist_residual_tanLambda_pion_mass->SetLineColor(2); hist_residual_tanLambda_pion_mass->SetLineWidth(1);
TH1* hist_residual_tanLambda_true_mass = new TH1F("hist_residual_tanLambda_true_mass", "; tanLambda residual; # tracks" , 100,residual_min,residual_max);
hist_residual_tanLambda_true_mass->SetLineColor(4); hist_residual_tanLambda_true_mass->SetLineWidth(1);
TH1* hist_residual_tanLambda_true_mass_Par = new TH1F("hist_residual_tanLambda_true_mass_Par", "; tanLambda residual; # tracks" , 100,residual_min,residual_max);
hist_residual_tanLambda_true_mass_Par->SetLineColor(1); hist_residual_tanLambda_true_mass_Par->SetLineWidth(1);
TH1* hist_residual_tanLambda_true_mass_aPar = new TH1F("hist_residual_tanLambda_true_mass_aPar", "; tanLambda residual; # tracks" , 100,residual_min,residual_max);
hist_residual_tanLambda_true_mass_aPar->SetLineColor(6); hist_residual_tanLambda_true_mass_aPar->SetLineWidth(1);
TH1* hist_residual_z0_pion_mass = new TH1F("hist_residual_z0_pion_mass", "; z_{0} residual; # tracks" , 100,residual_min,residual_max);
hist_residual_z0_pion_mass->SetLineColor(2); hist_residual_z0_pion_mass->SetLineWidth(1);
TH1* hist_residual_z0_true_mass = new TH1F("hist_residual_z0_true_mass", "; z_{0} residual; # tracks" , 100,residual_min,residual_max);
hist_residual_z0_true_mass->SetLineColor(4); hist_residual_z0_true_mass->SetLineWidth(1);
TH1* hist_residual_z0_true_mass_Par = new TH1F("hist_residual_z0_true_mass_Par", "; z_{0} residual; # tracks" , 100,residual_min,residual_max);
hist_residual_z0_true_mass_Par->SetLineColor(1); hist_residual_z0_true_mass_Par->SetLineWidth(1);
TH1* hist_residual_z0_true_mass_aPar = new TH1F("hist_residual_z0_true_mass_aPar", "; z_{0} residual; # tracks" , 100,residual_min,residual_max);
hist_residual_z0_true_mass_aPar->SetLineColor(6); hist_residual_z0_true_mass_aPar->SetLineWidth(1);

TH1* hist_uncertainty_d0_pion_mass = new TH1F("hist_uncertainty_d0_pion_mass", "; d_{0} uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_d0_pion_mass->SetLineColor(2); hist_uncertainty_d0_pion_mass->SetLineWidth(1);
TH1* hist_uncertainty_d0_true_mass = new TH1F("hist_uncertainty_d0_true_mass", "; d_{0} uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_d0_true_mass->SetLineColor(4); hist_uncertainty_d0_true_mass->SetLineWidth(1);
TH1* hist_uncertainty_d0_true_mass_Par = new TH1F("hist_uncertainty_d0_true_mass_Par", "; d_{0} uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_d0_true_mass_Par->SetLineColor(1); hist_uncertainty_d0_true_mass_Par->SetLineWidth(1);
TH1* hist_uncertainty_d0_true_mass_aPar = new TH1F("hist_uncertainty_d0_true_mass_aPar", "; d_{0} uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_d0_true_mass_aPar->SetLineColor(6); hist_uncertainty_d0_true_mass_aPar->SetLineWidth(1);
TH1* hist_uncertainty_Omega_pion_mass = new TH1F("hist_uncertainty_Omega_pion_mass", "; Omega uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_Omega_pion_mass->SetLineColor(2); hist_uncertainty_Omega_pion_mass->SetLineWidth(1);
TH1* hist_uncertainty_Omega_true_mass = new TH1F("hist_uncertainty_Omega_true_mass", "; Omega uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_Omega_true_mass->SetLineColor(4); hist_uncertainty_Omega_true_mass->SetLineWidth(1);
TH1* hist_uncertainty_Omega_true_mass_Par = new TH1F("hist_uncertainty_Omega_true_mass_Par", "; Omega uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_Omega_true_mass_Par->SetLineColor(1); hist_uncertainty_Omega_true_mass_Par->SetLineWidth(1);
TH1* hist_uncertainty_Omega_true_mass_aPar = new TH1F("hist_uncertainty_Omega_true_mass_aPar", "; Omega uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_Omega_true_mass_aPar->SetLineColor(6); hist_uncertainty_Omega_true_mass_aPar->SetLineWidth(1);
TH1* hist_uncertainty_Phi_pion_mass = new TH1F("hist_uncertainty_Phi_pion_mass", "; Phi uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_Phi_pion_mass->SetLineColor(2); hist_uncertainty_Phi_pion_mass->SetLineWidth(1);
TH1* hist_uncertainty_Phi_true_mass = new TH1F("hist_uncertainty_Phi_true_mass", "; Phi uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_Phi_true_mass->SetLineColor(4); hist_uncertainty_Phi_true_mass->SetLineWidth(1);
TH1* hist_uncertainty_Phi_true_mass_Par = new TH1F("hist_uncertainty_Phi_true_mass_Par", "; Phi uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_Phi_true_mass_Par->SetLineColor(1); hist_uncertainty_Phi_true_mass_Par->SetLineWidth(1);
TH1* hist_uncertainty_Phi_true_mass_aPar = new TH1F("hist_uncertainty_Phi_true_mass_aPar", "; Phi uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_Phi_true_mass_aPar->SetLineColor(6); hist_uncertainty_Phi_true_mass_aPar->SetLineWidth(1);
TH1* hist_uncertainty_tanLambda_pion_mass = new TH1F("hist_uncertainty_tanLambda_pion_mass", "; tanLambda uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_tanLambda_pion_mass->SetLineColor(2); hist_uncertainty_tanLambda_pion_mass->SetLineWidth(1);
TH1* hist_uncertainty_tanLambda_true_mass = new TH1F("hist_uncertainty_tanLambda_true_mass", "; tanLambda uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_tanLambda_true_mass->SetLineColor(4); hist_uncertainty_tanLambda_true_mass->SetLineWidth(1);
TH1* hist_uncertainty_tanLambda_true_mass_Par = new TH1F("hist_uncertainty_tanLambda_true_mass_Par", "; tanLambda uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_tanLambda_true_mass_Par->SetLineColor(1); hist_uncertainty_tanLambda_true_mass_Par->SetLineWidth(1);
TH1* hist_uncertainty_tanLambda_true_mass_aPar = new TH1F("hist_uncertainty_tanLambda_true_mass_aPar", "; tanLambda uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_tanLambda_true_mass_aPar->SetLineColor(6); hist_uncertainty_tanLambda_true_mass_aPar->SetLineWidth(1);
TH1* hist_uncertainty_z0_pion_mass = new TH1F("hist_uncertainty_z0_pion_mass", "; z_{0} uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_z0_pion_mass->SetLineColor(2); hist_uncertainty_z0_pion_mass->SetLineWidth(1);
TH1* hist_uncertainty_z0_true_mass = new TH1F("hist_uncertainty_z0_true_mass", "; z_{0} uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_z0_true_mass->SetLineColor(4); hist_uncertainty_z0_true_mass->SetLineWidth(1);
TH1* hist_uncertainty_z0_true_mass_Par = new TH1F("hist_uncertainty_z0_true_mass_Par", "; z_{0} uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_z0_true_mass_Par->SetLineColor(1); hist_uncertainty_z0_true_mass_Par->SetLineWidth(1);
TH1* hist_uncertainty_z0_true_mass_aPar = new TH1F("hist_uncertainty_z0_true_mass_aPar", "; z_{0} uncertainty; # tracks" , 100,uncertainty_min,uncertainty_max);
hist_uncertainty_z0_true_mass_aPar->SetLineColor(6); hist_uncertainty_z0_true_mass_aPar->SetLineWidth(1);

TH1* hist_pull_d0_pion_mass = new TH1F("hist_pull_d0_pion_mass", "; d_{0} Pull; # tracks" , 100,pull_min,pull_max);
hist_pull_d0_pion_mass->SetLineColor(2); hist_pull_d0_pion_mass->SetLineWidth(1);
TH1* hist_pull_d0_true_mass = new TH1F("hist_pull_d0_true_mass", "; d_{0} Pull; # tracks" , 100,pull_min,pull_max);
hist_pull_d0_true_mass->SetLineColor(4); hist_pull_d0_true_mass->SetLineWidth(1);
TH1* hist_pull_d0_true_mass_Par = new TH1F("hist_pull_d0_true_mass_Par", "; d_{0} Pull; # tracks" , 100,pull_min,pull_max);
hist_pull_d0_true_mass_Par->SetLineColor(1); hist_pull_d0_true_mass_Par->SetLineWidth(1);
TH1* hist_pull_d0_true_mass_aPar = new TH1F("hist_pull_d0_true_mass_aPar", "; d_{0} Pull; # tracks" , 100,pull_min,pull_max);
hist_pull_d0_true_mass_aPar->SetLineColor(6); hist_pull_d0_true_mass_aPar->SetLineWidth(1);
TH1* hist_pull_Omega_pion_mass = new TH1F("hist_pull_Omega_pion_mass", "; Omega pull; # tracks" , 100,pull_min,pull_max);
hist_pull_Omega_pion_mass->SetLineColor(2); hist_pull_Omega_pion_mass->SetLineWidth(1);
TH1* hist_pull_Omega_true_mass = new TH1F("hist_pull_Omega_true_mass", "; Omega pull; # tracks" , 100,pull_min,pull_max);
hist_pull_Omega_true_mass->SetLineColor(4); hist_pull_Omega_true_mass->SetLineWidth(1);
TH1* hist_pull_Omega_true_mass_Par = new TH1F("hist_pull_Omega_true_mass_Par", "; Omega pull; # tracks" , 100,pull_min,pull_max);
hist_pull_Omega_true_mass_Par->SetLineColor(1); hist_pull_Omega_true_mass_Par->SetLineWidth(1);
TH1* hist_pull_Omega_true_mass_aPar = new TH1F("hist_pull_Omega_true_mass_aPar", "; Omega pull; # tracks" , 100,pull_min,pull_max);
hist_pull_Omega_true_mass_aPar->SetLineColor(6); hist_pull_Omega_true_mass_aPar->SetLineWidth(1);
TH1* hist_pull_Phi_pion_mass = new TH1F("hist_pull_Phi_pion_mass", "; Phi pull; # tracks" , 100,pull_min,pull_max);
hist_pull_Phi_pion_mass->SetLineColor(2); hist_pull_Phi_pion_mass->SetLineWidth(1);
TH1* hist_pull_Phi_true_mass = new TH1F("hist_pull_Phi_true_mass", "; Phi pull; # tracks" , 100,pull_min,pull_max);
hist_pull_Phi_true_mass->SetLineColor(4); hist_pull_Phi_true_mass->SetLineWidth(1);
TH1* hist_pull_Phi_true_mass_Par = new TH1F("hist_pull_Phi_true_mass_Par", "; Phi pull; # tracks" , 100,pull_min,pull_max);
hist_pull_Phi_true_mass_Par->SetLineColor(1); hist_pull_Phi_true_mass_Par->SetLineWidth(1);
TH1* hist_pull_Phi_true_mass_aPar = new TH1F("hist_pull_Phi_true_mass_aPar", "; Phi pull; # tracks" , 100,pull_min,pull_max);
hist_pull_Phi_true_mass_aPar->SetLineColor(6); hist_pull_Phi_true_mass_aPar->SetLineWidth(1);
TH1* hist_pull_tanLambda_pion_mass = new TH1F("hist_pull_tanLambda_pion_mass", "; tanLambda pull; # tracks" , 100,pull_min,pull_max);
hist_pull_tanLambda_pion_mass->SetLineColor(2); hist_pull_tanLambda_pion_mass->SetLineWidth(1);
TH1* hist_pull_tanLambda_true_mass = new TH1F("hist_pull_tanLambda_true_mass", "; tanLambda pull; # tracks" , 100,pull_min,pull_max);
hist_pull_tanLambda_true_mass->SetLineColor(4); hist_pull_tanLambda_true_mass->SetLineWidth(1);
TH1* hist_pull_tanLambda_true_mass_Par = new TH1F("hist_pull_tanLambda_true_mass_Par", "; tanLambda pull; # tracks" , 100,pull_min,pull_max);
hist_pull_tanLambda_true_mass_Par->SetLineColor(1); hist_pull_tanLambda_true_mass_Par->SetLineWidth(1);
TH1* hist_pull_tanLambda_true_mass_aPar = new TH1F("hist_pull_tanLambda_true_mass_aPar", "; tanLambda pull; # tracks" , 100,pull_min,pull_max);
hist_pull_tanLambda_true_mass_aPar->SetLineColor(6); hist_pull_tanLambda_true_mass_aPar->SetLineWidth(1);
TH1* hist_pull_z0_pion_mass = new TH1F("hist_pull_z0_pion_mass", "; z_{0} pull; # tracks" , 100,pull_min,pull_max);
hist_pull_z0_pion_mass->SetLineColor(2); hist_pull_z0_pion_mass->SetLineWidth(1);
TH1* hist_pull_z0_true_mass = new TH1F("hist_pull_z0_true_mass", "; z_{0} pull; # tracks" , 100,pull_min,pull_max);
hist_pull_z0_true_mass->SetLineColor(4); hist_pull_z0_true_mass->SetLineWidth(1);
TH1* hist_pull_z0_true_mass_Par = new TH1F("hist_pull_z0_true_mass_Par", "; z_{0} pull; # tracks" , 100,pull_min,pull_max);
hist_pull_z0_true_mass_Par->SetLineColor(1); hist_pull_z0_true_mass_Par->SetLineWidth(1);
TH1* hist_pull_z0_true_mass_aPar = new TH1F("hist_pull_z0_true_mass_aPar", "; z_{0} pull; # tracks" , 100,pull_min,pull_max);
hist_pull_z0_true_mass_aPar->SetLineColor(6); hist_pull_z0_true_mass_aPar->SetLineWidth(1);


vector<int> *track_PDG{};
vector<float> *momentum{};
vector<float> *vertex_radius{};
vector<float> *vertex_rho{};
vector<float> *highest_weight{};

vector<float> *residual_d0_pion_mass{};
vector<float> *residual_Omega_pion_mass{};
vector<float> *residual_Phi_pion_mass{};
vector<float> *residual_tanLambda_pion_mass{};
vector<float> *residual_z0_pion_mass{};
vector<float> *residual_d0_true_mass{};
vector<float> *residual_Omega_true_mass{};
vector<float> *residual_Phi_true_mass{};
vector<float> *residual_tanLambda_true_mass{};
vector<float> *residual_z0_true_mass{};

vector<float> *uncertainty_d0_pion_mass{};
vector<float> *uncertainty_Omega_pion_mass{};
vector<float> *uncertainty_Phi_pion_mass{};
vector<float> *uncertainty_tanLambda_pion_mass{};
vector<float> *uncertainty_z0_pion_mass{};
vector<float> *uncertainty_d0_true_mass{};
vector<float> *uncertainty_Omega_true_mass{};
vector<float> *uncertainty_Phi_true_mass{};
vector<float> *uncertainty_tanLambda_true_mass{};
vector<float> *uncertainty_z0_true_mass{};

vector<float> *pull_d0_pion_mass{};
vector<float> *pull_Omega_pion_mass{};
vector<float> *pull_Phi_pion_mass{};
vector<float> *pull_tanLambda_pion_mass{};
vector<float> *pull_z0_pion_mass{};
vector<float> *pull_d0_true_mass{};
vector<float> *pull_Omega_true_mass{};
vector<float> *pull_Phi_true_mass{};
vector<float> *pull_tanLambda_true_mass{};
vector<float> *pull_z0_true_mass{};

tree->SetBranchAddress("track_PDG",&track_PDG);
tree->SetBranchAddress("mcp_momentum",&momentum);
tree->SetBranchAddress("vertex_radius",&vertex_radius);
tree->SetBranchAddress("vertex_rho",&vertex_rho);
tree->SetBranchAddress("highest_weight",&highest_weight);

tree->SetBranchAddress("residual_d0_pion_mass",&residual_d0_pion_mass);
tree->SetBranchAddress("residual_Omega_pion_mass",&residual_Omega_pion_mass);
tree->SetBranchAddress("residual_Phi_pion_mass",&residual_Phi_pion_mass);
tree->SetBranchAddress("residual_tanLambda_pion_mass",&residual_tanLambda_pion_mass);
tree->SetBranchAddress("residual_z0_pion_mass",&residual_z0_pion_mass);
tree->SetBranchAddress("residual_d0_true_mass",&residual_d0_true_mass);
tree->SetBranchAddress("residual_Omega_true_mass",&residual_Omega_true_mass);
tree->SetBranchAddress("residual_Phi_true_mass",&residual_Phi_true_mass);
tree->SetBranchAddress("residual_tanLambda_true_mass",&residual_tanLambda_true_mass);
tree->SetBranchAddress("residual_z0_true_mass",&residual_z0_true_mass);

tree->SetBranchAddress("uncertainty_d0_pion_mass",&uncertainty_d0_pion_mass);
tree->SetBranchAddress("uncertainty_Omega_pion_mass",&uncertainty_Omega_pion_mass);
tree->SetBranchAddress("uncertainty_Phi_pion_mass",&uncertainty_Phi_pion_mass);
tree->SetBranchAddress("uncertainty_tanLambda_pion_mass",&uncertainty_tanLambda_pion_mass);
tree->SetBranchAddress("uncertainty_z0_pion_mass",&uncertainty_z0_pion_mass);
tree->SetBranchAddress("uncertainty_d0_true_mass",&uncertainty_d0_true_mass);
tree->SetBranchAddress("uncertainty_Omega_true_mass",&uncertainty_Omega_true_mass);
tree->SetBranchAddress("uncertainty_Phi_true_mass",&uncertainty_Phi_true_mass);
tree->SetBranchAddress("uncertainty_tanLambda_true_mass",&uncertainty_tanLambda_true_mass);
tree->SetBranchAddress("uncertainty_z0_true_mass",&uncertainty_z0_true_mass);

tree->SetBranchAddress("pull_d0_pion_mass",&pull_d0_pion_mass);
tree->SetBranchAddress("pull_Omega_pion_mass",&pull_Omega_pion_mass);
tree->SetBranchAddress("pull_Phi_pion_mass",&pull_Phi_pion_mass);
tree->SetBranchAddress("pull_tanLambda_pion_mass",&pull_tanLambda_pion_mass);
tree->SetBranchAddress("pull_z0_pion_mass",&pull_z0_pion_mass);
tree->SetBranchAddress("pull_d0_true_mass",&pull_d0_true_mass);
tree->SetBranchAddress("pull_Omega_true_mass",&pull_Omega_true_mass);
tree->SetBranchAddress("pull_Phi_true_mass",&pull_Phi_true_mass);
tree->SetBranchAddress("pull_tanLambda_true_mass",&pull_tanLambda_true_mass);
tree->SetBranchAddress("pull_z0_true_mass",&pull_z0_true_mass);


for (int i = 0; i < nEntries; i++)
{
	tree->GetEntry(i);
	for (int track_i = 0; track_i < (track_PDG->size()); track_i++)
	{
		if ((vertex_radius->at(track_i) >= r_cut) || (vertex_rho->at(track_i) >= rho_cut) || (highest_weight->at(track_i) < weight_cut))
			continue;

		if (track_PDG->at(track_i) == true_pdg)
		{
			hist_momentum->Fill(momentum->at(track_i));
			hist_momentum_Par->Fill(momentum->at(track_i));
		}
		if (track_PDG->at(track_i) == -1 * true_pdg)
		{
			hist_momentum->Fill(momentum->at(track_i));
			hist_momentum_aPar->Fill(momentum->at(track_i));
		}
		if (momentum->at(track_i) >= p_min && momentum->at(track_i) <= p_max)
		{
			if (track_PDG->at(track_i) == true_pdg)
			{
				hist_residual_d0_pion_mass->Fill(residual_d0_pion_mass->at(track_i));
				hist_residual_Omega_pion_mass->Fill(residual_Omega_pion_mass->at(track_i));
				hist_residual_Phi_pion_mass->Fill(residual_Phi_pion_mass->at(track_i));
				hist_residual_tanLambda_pion_mass->Fill(residual_tanLambda_pion_mass->at(track_i));
				hist_residual_z0_pion_mass->Fill(residual_z0_pion_mass->at(track_i));
				hist_residual_d0_true_mass->Fill(residual_d0_true_mass->at(track_i));
				hist_residual_Omega_true_mass->Fill(residual_Omega_true_mass->at(track_i));
				hist_residual_Phi_true_mass->Fill(residual_Phi_true_mass->at(track_i));
				hist_residual_tanLambda_true_mass->Fill(residual_tanLambda_true_mass->at(track_i));
				hist_residual_z0_true_mass->Fill(residual_z0_true_mass->at(track_i));
				hist_residual_d0_true_mass_Par->Fill(residual_d0_true_mass->at(track_i));
				hist_residual_Omega_true_mass_Par->Fill(residual_Omega_true_mass->at(track_i));
				hist_residual_Phi_true_mass_Par->Fill(residual_Phi_true_mass->at(track_i));
				hist_residual_tanLambda_true_mass_Par->Fill(residual_tanLambda_true_mass->at(track_i));
				hist_residual_z0_true_mass_Par->Fill(residual_z0_true_mass->at(track_i));

				hist_uncertainty_d0_pion_mass->Fill(uncertainty_d0_pion_mass->at(track_i));
				hist_uncertainty_Omega_pion_mass->Fill(uncertainty_Omega_pion_mass->at(track_i));
				hist_uncertainty_Phi_pion_mass->Fill(uncertainty_Phi_pion_mass->at(track_i));
				hist_uncertainty_tanLambda_pion_mass->Fill(uncertainty_tanLambda_pion_mass->at(track_i));
				hist_uncertainty_z0_pion_mass->Fill(uncertainty_z0_pion_mass->at(track_i));
				hist_uncertainty_d0_true_mass->Fill(uncertainty_d0_true_mass->at(track_i));
				hist_uncertainty_Omega_true_mass->Fill(uncertainty_Omega_true_mass->at(track_i));
				hist_uncertainty_Phi_true_mass->Fill(uncertainty_Phi_true_mass->at(track_i));
				hist_uncertainty_tanLambda_true_mass->Fill(uncertainty_tanLambda_true_mass->at(track_i));
				hist_uncertainty_z0_true_mass->Fill(uncertainty_z0_true_mass->at(track_i));
				hist_uncertainty_d0_true_mass_Par->Fill(uncertainty_d0_true_mass->at(track_i));
				hist_uncertainty_Omega_true_mass_Par->Fill(uncertainty_Omega_true_mass->at(track_i));
				hist_uncertainty_Phi_true_mass_Par->Fill(uncertainty_Phi_true_mass->at(track_i));
				hist_uncertainty_tanLambda_true_mass_Par->Fill(uncertainty_tanLambda_true_mass->at(track_i));
				hist_uncertainty_z0_true_mass_Par->Fill(uncertainty_z0_true_mass->at(track_i));

				hist_pull_d0_pion_mass->Fill(pull_d0_pion_mass->at(track_i));
				hist_pull_Omega_pion_mass->Fill(pull_Omega_pion_mass->at(track_i));
				hist_pull_Phi_pion_mass->Fill(pull_Phi_pion_mass->at(track_i));
				hist_pull_tanLambda_pion_mass->Fill(pull_tanLambda_pion_mass->at(track_i));
				hist_pull_z0_pion_mass->Fill(pull_z0_pion_mass->at(track_i));
				hist_pull_d0_true_mass->Fill(pull_d0_true_mass->at(track_i));
				hist_pull_Omega_true_mass->Fill(pull_Omega_true_mass->at(track_i));
				hist_pull_Phi_true_mass->Fill(pull_Phi_true_mass->at(track_i));
				hist_pull_tanLambda_true_mass->Fill(pull_tanLambda_true_mass->at(track_i));
				hist_pull_z0_true_mass->Fill(pull_z0_true_mass->at(track_i));
				hist_pull_d0_true_mass_Par->Fill(pull_d0_true_mass->at(track_i));
				hist_pull_Omega_true_mass_Par->Fill(pull_Omega_true_mass->at(track_i));
				hist_pull_Phi_true_mass_Par->Fill(pull_Phi_true_mass->at(track_i));
				hist_pull_tanLambda_true_mass_Par->Fill(pull_tanLambda_true_mass->at(track_i));
				hist_pull_z0_true_mass_Par->Fill(pull_z0_true_mass->at(track_i));
			}

			if (track_PDG->at(track_i) == -1 * true_pdg)
			{
				hist_residual_d0_pion_mass->Fill(residual_d0_pion_mass->at(track_i));
				hist_residual_Omega_pion_mass->Fill(residual_Omega_pion_mass->at(track_i));
				hist_residual_Phi_pion_mass->Fill(residual_Phi_pion_mass->at(track_i));
				hist_residual_tanLambda_pion_mass->Fill(residual_tanLambda_pion_mass->at(track_i));
				hist_residual_z0_pion_mass->Fill(residual_z0_pion_mass->at(track_i));
				hist_residual_d0_true_mass->Fill(residual_d0_true_mass->at(track_i));
				hist_residual_Omega_true_mass->Fill(residual_Omega_true_mass->at(track_i));
				hist_residual_Phi_true_mass->Fill(residual_Phi_true_mass->at(track_i));
				hist_residual_tanLambda_true_mass->Fill(residual_tanLambda_true_mass->at(track_i));
				hist_residual_z0_true_mass->Fill(residual_z0_true_mass->at(track_i));
				hist_residual_d0_true_mass_aPar->Fill(residual_d0_true_mass->at(track_i));
				hist_residual_Omega_true_mass_aPar->Fill(residual_Omega_true_mass->at(track_i));
				hist_residual_Phi_true_mass_aPar->Fill(residual_Phi_true_mass->at(track_i));
				hist_residual_tanLambda_true_mass_aPar->Fill(residual_tanLambda_true_mass->at(track_i));
				hist_residual_z0_true_mass_aPar->Fill(residual_z0_true_mass->at(track_i));

				hist_uncertainty_d0_pion_mass->Fill(uncertainty_d0_pion_mass->at(track_i));
				hist_uncertainty_Omega_pion_mass->Fill(uncertainty_Omega_pion_mass->at(track_i));
				hist_uncertainty_Phi_pion_mass->Fill(uncertainty_Phi_pion_mass->at(track_i));
				hist_uncertainty_tanLambda_pion_mass->Fill(uncertainty_tanLambda_pion_mass->at(track_i));
				hist_uncertainty_z0_pion_mass->Fill(uncertainty_z0_pion_mass->at(track_i));
				hist_uncertainty_d0_true_mass->Fill(uncertainty_d0_true_mass->at(track_i));
				hist_uncertainty_Omega_true_mass->Fill(uncertainty_Omega_true_mass->at(track_i));
				hist_uncertainty_Phi_true_mass->Fill(uncertainty_Phi_true_mass->at(track_i));
				hist_uncertainty_tanLambda_true_mass->Fill(uncertainty_tanLambda_true_mass->at(track_i));
				hist_uncertainty_z0_true_mass->Fill(uncertainty_z0_true_mass->at(track_i));
				hist_uncertainty_d0_true_mass_aPar->Fill(uncertainty_d0_true_mass->at(track_i));
				hist_uncertainty_Omega_true_mass_aPar->Fill(uncertainty_Omega_true_mass->at(track_i));
				hist_uncertainty_Phi_true_mass_aPar->Fill(uncertainty_Phi_true_mass->at(track_i));
				hist_uncertainty_tanLambda_true_mass_aPar->Fill(uncertainty_tanLambda_true_mass->at(track_i));
				hist_uncertainty_z0_true_mass_aPar->Fill(uncertainty_z0_true_mass->at(track_i));

				hist_pull_d0_pion_mass->Fill(pull_d0_pion_mass->at(track_i));
				hist_pull_Omega_pion_mass->Fill(pull_Omega_pion_mass->at(track_i));
				hist_pull_Phi_pion_mass->Fill(pull_Phi_pion_mass->at(track_i));
				hist_pull_tanLambda_pion_mass->Fill(pull_tanLambda_pion_mass->at(track_i));
				hist_pull_z0_pion_mass->Fill(pull_z0_pion_mass->at(track_i));
				hist_pull_d0_true_mass->Fill(pull_d0_true_mass->at(track_i));
				hist_pull_Omega_true_mass->Fill(pull_Omega_true_mass->at(track_i));
				hist_pull_Phi_true_mass->Fill(pull_Phi_true_mass->at(track_i));
				hist_pull_tanLambda_true_mass->Fill(pull_tanLambda_true_mass->at(track_i));
				hist_pull_z0_true_mass->Fill(pull_z0_true_mass->at(track_i));
				hist_pull_d0_true_mass_aPar->Fill(pull_d0_true_mass->at(track_i));
				hist_pull_Omega_true_mass_aPar->Fill(pull_Omega_true_mass->at(track_i));
				hist_pull_Phi_true_mass_aPar->Fill(pull_Phi_true_mass->at(track_i));
				hist_pull_tanLambda_true_mass_aPar->Fill(pull_tanLambda_true_mass->at(track_i));
				hist_pull_z0_true_mass_aPar->Fill(pull_z0_true_mass->at(track_i));
			}
		}
	}
}

TCanvas *can_residual_d0 = new TCanvas("can_residual_d0", "", 1600,1200);
hist_residual_d0_pion_mass->Draw();
hist_residual_d0_true_mass->Draw("sames");
hist_residual_d0_true_mass_Par->Draw("sames");
hist_residual_d0_true_mass_aPar->Draw("sames");
gPad->Update();
TPaveStats *tps_residual_d0_pion_mass = (TPaveStats*)hist_residual_d0_pion_mass->FindObject("stats");
TPaveStats *tps_residual_d0_true_mass = (TPaveStats*)hist_residual_d0_true_mass->FindObject("stats");
TPaveStats *tps_residual_d0_true_mass_Par = (TPaveStats*)hist_residual_d0_true_mass_Par->FindObject("stats");
TPaveStats *tps_residual_d0_true_mass_aPar = (TPaveStats*)hist_residual_d0_true_mass_aPar->FindObject("stats");
tps_residual_d0_pion_mass->SetTextColor(2); tps_residual_d0_pion_mass->SetLineColor(2);
tps_residual_d0_true_mass->SetTextColor(4); tps_residual_d0_true_mass->SetLineColor(4);
tps_residual_d0_true_mass_Par->SetTextColor(1); tps_residual_d0_true_mass_Par->SetLineColor(1);
tps_residual_d0_true_mass_aPar->SetTextColor(6); tps_residual_d0_true_mass_aPar->SetLineColor(6);
tps_residual_d0_pion_mass->SetX1NDC(0.72); tps_residual_d0_pion_mass->SetX2NDC(0.88); tps_residual_d0_pion_mass->SetY1NDC(0.8); tps_residual_d0_pion_mass->SetY2NDC(0.9);
double X1 = tps_residual_d0_pion_mass->GetX1NDC(); double X2 = tps_residual_d0_pion_mass->GetX2NDC(); double Y1 = tps_residual_d0_pion_mass->GetY1NDC(); double Y2 = tps_residual_d0_pion_mass->GetY2NDC();
tps_residual_d0_true_mass->SetX1NDC(X1); tps_residual_d0_true_mass->SetX2NDC(X2); tps_residual_d0_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_residual_d0_true_mass->SetY2NDC(Y1);
tps_residual_d0_true_mass_Par->SetX1NDC(1-X2+0.1); tps_residual_d0_true_mass_Par->SetX2NDC(1-X1+0.1); tps_residual_d0_true_mass_Par->SetY1NDC(Y1); tps_residual_d0_true_mass_Par->SetY2NDC(Y2);
tps_residual_d0_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_residual_d0_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_residual_d0_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_residual_d0_true_mass_aPar->SetY2NDC(Y1);
tps_residual_d0_pion_mass->Draw("same");
tps_residual_d0_true_mass->Draw("same");
tps_residual_d0_true_mass_Par->Draw("same");
tps_residual_d0_true_mass_aPar->Draw("same");
TLegend *leg_residual_d0=new TLegend(0.65,0.50,0.85,0.70);
leg_residual_d0->SetNColumns(2);
leg_residual_d0->SetTextSize(TextSize);
leg_residual_d0->SetHeader(header_par,"C");
leg_residual_d0->AddEntry("",header_moment,"");
leg_residual_d0->AddEntry("",header_wei,"");
leg_residual_d0->AddEntry("",header_r3D,"");
leg_residual_d0->AddEntry("",header_r2D,"");
leg_residual_d0->AddEntry(hist_residual_d0_pion_mass,"m_{#pi}","l");
leg_residual_d0->AddEntry(hist_residual_d0_true_mass,true_particle,"l");
leg_residual_d0->AddEntry(hist_residual_d0_true_mass_Par,particle,"l");
leg_residual_d0->AddEntry(hist_residual_d0_true_mass_aPar,anti_particle,"l");
leg_residual_d0->Draw("same");
can_residual_d0->Update();
can_residual_d0->SaveAs((plot_dir+plot_init+"_residual_d0"+momentum_stat+".pdf").c_str());
can_residual_d0->SaveAs((plot_dir+plot_init+"_residual_d0"+momentum_stat+".C").c_str());


TCanvas *can_residual_Omega = new TCanvas("can_residual_Omega", "", 1600,1200);
hist_residual_Omega_pion_mass->Draw();
hist_residual_Omega_true_mass->Draw("sames");
hist_residual_Omega_true_mass_Par->Draw("sames");
hist_residual_Omega_true_mass_aPar->Draw("sames");
gPad->Update();
TPaveStats *tps_residual_Omega_pion_mass = (TPaveStats*)hist_residual_Omega_pion_mass->FindObject("stats");
TPaveStats *tps_residual_Omega_true_mass = (TPaveStats*)hist_residual_Omega_true_mass->FindObject("stats");
TPaveStats *tps_residual_Omega_true_mass_Par = (TPaveStats*)hist_residual_Omega_true_mass_Par->FindObject("stats");
TPaveStats *tps_residual_Omega_true_mass_aPar = (TPaveStats*)hist_residual_Omega_true_mass_aPar->FindObject("stats");
tps_residual_Omega_pion_mass->SetTextColor(2); tps_residual_Omega_pion_mass->SetLineColor(2);
tps_residual_Omega_true_mass->SetTextColor(4); tps_residual_Omega_true_mass->SetLineColor(4);
tps_residual_Omega_true_mass_Par->SetTextColor(1); tps_residual_Omega_true_mass_Par->SetLineColor(1);
tps_residual_Omega_true_mass_aPar->SetTextColor(6); tps_residual_Omega_true_mass_aPar->SetLineColor(6);
tps_residual_Omega_pion_mass->SetX1NDC(0.72); tps_residual_Omega_pion_mass->SetX2NDC(0.88); tps_residual_Omega_pion_mass->SetY1NDC(0.8); tps_residual_Omega_pion_mass->SetY2NDC(0.9);
X1 = tps_residual_Omega_pion_mass->GetX1NDC(); X2 = tps_residual_Omega_pion_mass->GetX2NDC(); Y1 = tps_residual_Omega_pion_mass->GetY1NDC(); Y2 = tps_residual_Omega_pion_mass->GetY2NDC();
tps_residual_Omega_true_mass->SetX1NDC(X1); tps_residual_Omega_true_mass->SetX2NDC(X2); tps_residual_Omega_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_residual_Omega_true_mass->SetY2NDC(Y1);
tps_residual_Omega_true_mass_Par->SetX1NDC(1-X2+0.1); tps_residual_Omega_true_mass_Par->SetX2NDC(1-X1+0.1); tps_residual_Omega_true_mass_Par->SetY1NDC(Y1); tps_residual_Omega_true_mass_Par->SetY2NDC(Y2);
tps_residual_Omega_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_residual_Omega_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_residual_Omega_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_residual_Omega_true_mass_aPar->SetY2NDC(Y1);
tps_residual_Omega_pion_mass->Draw("same");
tps_residual_Omega_true_mass->Draw("same");
tps_residual_Omega_true_mass_Par->Draw("same");
tps_residual_Omega_true_mass_aPar->Draw("same");
TLegend *leg_residual_Omega=new TLegend(0.65,0.50,0.85,0.70);
leg_residual_Omega->SetNColumns(2);
leg_residual_Omega->SetTextSize(TextSize);
leg_residual_Omega->SetHeader(header_par,"C");
leg_residual_Omega->AddEntry("",header_moment,"");
leg_residual_Omega->AddEntry("",header_wei,"");
leg_residual_Omega->AddEntry("",header_r3D,"");
leg_residual_Omega->AddEntry("",header_r2D,"");
leg_residual_Omega->AddEntry(hist_residual_Omega_pion_mass,"m_{#pi}","l");
leg_residual_Omega->AddEntry(hist_residual_Omega_true_mass,true_particle,"l");
leg_residual_Omega->AddEntry(hist_residual_Omega_true_mass_Par,particle,"l");
leg_residual_Omega->AddEntry(hist_residual_Omega_true_mass_aPar,anti_particle,"l");
leg_residual_Omega->Draw("same");
can_residual_Omega->Update();
can_residual_Omega->SaveAs((plot_dir+plot_init+"_residual_Omega"+momentum_stat+".pdf").c_str());
can_residual_Omega->SaveAs((plot_dir+plot_init+"_residual_Omega"+momentum_stat+".C").c_str());


TCanvas *can_residual_Phi = new TCanvas("can_residual_Phi", "", 1600,1200);
hist_residual_Phi_pion_mass->Draw();
hist_residual_Phi_true_mass->Draw("sames");
hist_residual_Phi_true_mass_Par->Draw("sames");
hist_residual_Phi_true_mass_aPar->Draw("sames");
gPad->Update();
TPaveStats *tps_residual_Phi_pion_mass = (TPaveStats*)hist_residual_Phi_pion_mass->FindObject("stats");
TPaveStats *tps_residual_Phi_true_mass = (TPaveStats*)hist_residual_Phi_true_mass->FindObject("stats");
TPaveStats *tps_residual_Phi_true_mass_Par = (TPaveStats*)hist_residual_Phi_true_mass_Par->FindObject("stats");
TPaveStats *tps_residual_Phi_true_mass_aPar = (TPaveStats*)hist_residual_Phi_true_mass_aPar->FindObject("stats");
tps_residual_Phi_pion_mass->SetTextColor(2); tps_residual_Phi_pion_mass->SetLineColor(2);
tps_residual_Phi_true_mass->SetTextColor(4); tps_residual_Phi_true_mass->SetLineColor(4);
tps_residual_Phi_true_mass_Par->SetTextColor(1); tps_residual_Phi_true_mass_Par->SetLineColor(1);
tps_residual_Phi_true_mass_aPar->SetTextColor(6); tps_residual_Phi_true_mass_aPar->SetLineColor(6);
tps_residual_Phi_pion_mass->SetX1NDC(0.72); tps_residual_Phi_pion_mass->SetX2NDC(0.88); tps_residual_Phi_pion_mass->SetY1NDC(0.8); tps_residual_Phi_pion_mass->SetY2NDC(0.9);
X1 = tps_residual_Phi_pion_mass->GetX1NDC(); X2 = tps_residual_Phi_pion_mass->GetX2NDC(); Y1 = tps_residual_Phi_pion_mass->GetY1NDC(); Y2 = tps_residual_Phi_pion_mass->GetY2NDC();
tps_residual_Phi_true_mass->SetX1NDC(X1); tps_residual_Phi_true_mass->SetX2NDC(X2); tps_residual_Phi_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_residual_Phi_true_mass->SetY2NDC(Y1);
tps_residual_Phi_true_mass_Par->SetX1NDC(1-X2+0.1); tps_residual_Phi_true_mass_Par->SetX2NDC(1-X1+0.1); tps_residual_Phi_true_mass_Par->SetY1NDC(Y1); tps_residual_Phi_true_mass_Par->SetY2NDC(Y2);
tps_residual_Phi_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_residual_Phi_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_residual_Phi_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_residual_Phi_true_mass_aPar->SetY2NDC(Y1);
tps_residual_Phi_pion_mass->Draw("same");
tps_residual_Phi_true_mass->Draw("same");
tps_residual_Phi_true_mass_Par->Draw("same");
tps_residual_Phi_true_mass_aPar->Draw("same");
TLegend *leg_residual_Phi=new TLegend(0.65,0.50,0.85,0.70);
leg_residual_Phi->SetNColumns(2);
leg_residual_Phi->SetTextSize(TextSize);
leg_residual_Phi->SetHeader(header_par,"C");
leg_residual_Phi->AddEntry("",header_moment,"");
leg_residual_Phi->AddEntry("",header_wei,"");
leg_residual_Phi->AddEntry("",header_r3D,"");
leg_residual_Phi->AddEntry("",header_r2D,"");
leg_residual_Phi->AddEntry(hist_residual_Phi_pion_mass,"m_{#pi}","l");
leg_residual_Phi->AddEntry(hist_residual_Phi_true_mass,true_particle,"l");
leg_residual_Phi->AddEntry(hist_residual_Phi_true_mass_Par,particle,"l");
leg_residual_Phi->AddEntry(hist_residual_Phi_true_mass_aPar,anti_particle,"l");
leg_residual_Phi->Draw("same");
can_residual_Phi->Update();
can_residual_Phi->SaveAs((plot_dir+plot_init+"_residual_Phi"+momentum_stat+".pdf").c_str());
can_residual_Phi->SaveAs((plot_dir+plot_init+"_residual_Phi"+momentum_stat+".C").c_str());


TCanvas *can_residual_tanLambda = new TCanvas("can_residual_tanLambda", "", 1600,1200);
hist_residual_tanLambda_pion_mass->Draw();
hist_residual_tanLambda_true_mass->Draw("sames");
hist_residual_tanLambda_true_mass_Par->Draw("sames");
hist_residual_tanLambda_true_mass_aPar->Draw("sames");
gPad->Update();
TPaveStats *tps_residual_tanLambda_pion_mass = (TPaveStats*)hist_residual_tanLambda_pion_mass->FindObject("stats");
TPaveStats *tps_residual_tanLambda_true_mass = (TPaveStats*)hist_residual_tanLambda_true_mass->FindObject("stats");
TPaveStats *tps_residual_tanLambda_true_mass_Par = (TPaveStats*)hist_residual_tanLambda_true_mass_Par->FindObject("stats");
TPaveStats *tps_residual_tanLambda_true_mass_aPar = (TPaveStats*)hist_residual_tanLambda_true_mass_aPar->FindObject("stats");
tps_residual_tanLambda_pion_mass->SetTextColor(2); tps_residual_tanLambda_pion_mass->SetLineColor(2);
tps_residual_tanLambda_true_mass->SetTextColor(4); tps_residual_tanLambda_true_mass->SetLineColor(4);
tps_residual_tanLambda_true_mass_Par->SetTextColor(1); tps_residual_tanLambda_true_mass_Par->SetLineColor(1);
tps_residual_tanLambda_true_mass_aPar->SetTextColor(6); tps_residual_tanLambda_true_mass_aPar->SetLineColor(6);
tps_residual_tanLambda_pion_mass->SetX1NDC(0.72); tps_residual_tanLambda_pion_mass->SetX2NDC(0.88); tps_residual_tanLambda_pion_mass->SetY1NDC(0.8); tps_residual_tanLambda_pion_mass->SetY2NDC(0.9);
X1 = tps_residual_tanLambda_pion_mass->GetX1NDC(); X2 = tps_residual_tanLambda_pion_mass->GetX2NDC(); Y1 = tps_residual_tanLambda_pion_mass->GetY1NDC(); Y2 = tps_residual_tanLambda_pion_mass->GetY2NDC();
tps_residual_tanLambda_true_mass->SetX1NDC(X1); tps_residual_tanLambda_true_mass->SetX2NDC(X2); tps_residual_tanLambda_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_residual_tanLambda_true_mass->SetY2NDC(Y1);
tps_residual_tanLambda_true_mass_Par->SetX1NDC(1-X2+0.1); tps_residual_tanLambda_true_mass_Par->SetX2NDC(1-X1+0.1); tps_residual_tanLambda_true_mass_Par->SetY1NDC(Y1); tps_residual_tanLambda_true_mass_Par->SetY2NDC(Y2);
tps_residual_tanLambda_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_residual_tanLambda_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_residual_tanLambda_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_residual_tanLambda_true_mass_aPar->SetY2NDC(Y1);
tps_residual_tanLambda_pion_mass->Draw("same");
tps_residual_tanLambda_true_mass->Draw("same");
tps_residual_tanLambda_true_mass_Par->Draw("same");
tps_residual_tanLambda_true_mass_aPar->Draw("same");
TLegend *leg_residual_tanLambda=new TLegend(0.65,0.50,0.85,0.70);
leg_residual_tanLambda->SetNColumns(2);
leg_residual_tanLambda->SetTextSize(TextSize);
leg_residual_tanLambda->SetHeader(header_par,"C");
leg_residual_tanLambda->AddEntry("",header_moment,"");
leg_residual_tanLambda->AddEntry("",header_wei,"");
leg_residual_tanLambda->AddEntry("",header_r3D,"");
leg_residual_tanLambda->AddEntry("",header_r2D,"");
leg_residual_tanLambda->AddEntry(hist_residual_tanLambda_pion_mass,"m_{#pi}","l");
leg_residual_tanLambda->AddEntry(hist_residual_tanLambda_true_mass,true_particle,"l");
leg_residual_tanLambda->AddEntry(hist_residual_tanLambda_true_mass_Par,particle,"l");
leg_residual_tanLambda->AddEntry(hist_residual_tanLambda_true_mass_aPar,anti_particle,"l");
leg_residual_tanLambda->Draw("same");
can_residual_tanLambda->Update();
can_residual_tanLambda->SaveAs((plot_dir+plot_init+"_residual_tanLambda"+momentum_stat+".pdf").c_str());
can_residual_tanLambda->SaveAs((plot_dir+plot_init+"_residual_tanLambda"+momentum_stat+".C").c_str());


TCanvas *can_residual_z0 = new TCanvas("can_residual_z0", "", 1600,1200);
hist_residual_z0_pion_mass->Draw();
hist_residual_z0_true_mass->Draw("sames");
hist_residual_z0_true_mass_Par->Draw("sames");
hist_residual_z0_true_mass_aPar->Draw("sames");
gPad->Update();
TPaveStats *tps_residual_z0_pion_mass = (TPaveStats*)hist_residual_z0_pion_mass->FindObject("stats");
TPaveStats *tps_residual_z0_true_mass = (TPaveStats*)hist_residual_z0_true_mass->FindObject("stats");
TPaveStats *tps_residual_z0_true_mass_Par = (TPaveStats*)hist_residual_z0_true_mass_Par->FindObject("stats");
TPaveStats *tps_residual_z0_true_mass_aPar = (TPaveStats*)hist_residual_z0_true_mass_aPar->FindObject("stats");
tps_residual_z0_pion_mass->SetTextColor(2); tps_residual_z0_pion_mass->SetLineColor(2);
tps_residual_z0_true_mass->SetTextColor(4); tps_residual_z0_true_mass->SetLineColor(4);
tps_residual_z0_true_mass_Par->SetTextColor(1); tps_residual_z0_true_mass_Par->SetLineColor(1);
tps_residual_z0_true_mass_aPar->SetTextColor(6); tps_residual_z0_true_mass_aPar->SetLineColor(6);
tps_residual_z0_pion_mass->SetX1NDC(0.72); tps_residual_z0_pion_mass->SetX2NDC(0.88); tps_residual_z0_pion_mass->SetY1NDC(0.8); tps_residual_z0_pion_mass->SetY2NDC(0.9);
X1 = tps_residual_z0_pion_mass->GetX1NDC(); X2 = tps_residual_z0_pion_mass->GetX2NDC(); Y1 = tps_residual_z0_pion_mass->GetY1NDC(); Y2 = tps_residual_z0_pion_mass->GetY2NDC();
tps_residual_z0_true_mass->SetX1NDC(X1); tps_residual_z0_true_mass->SetX2NDC(X2); tps_residual_z0_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_residual_z0_true_mass->SetY2NDC(Y1);
tps_residual_z0_true_mass_Par->SetX1NDC(1-X2+0.1); tps_residual_z0_true_mass_Par->SetX2NDC(1-X1+0.1); tps_residual_z0_true_mass_Par->SetY1NDC(Y1); tps_residual_z0_true_mass_Par->SetY2NDC(Y2);
tps_residual_z0_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_residual_z0_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_residual_z0_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_residual_z0_true_mass_aPar->SetY2NDC(Y1);
tps_residual_z0_pion_mass->Draw("same");
tps_residual_z0_true_mass->Draw("same");
tps_residual_z0_true_mass_Par->Draw("same");
tps_residual_z0_true_mass_aPar->Draw("same");
TLegend *leg_residual_z0=new TLegend(0.65,0.50,0.85,0.70);
leg_residual_z0->SetNColumns(2);
leg_residual_z0->SetTextSize(TextSize);
leg_residual_z0->SetHeader(header_par,"C");
leg_residual_z0->AddEntry("",header_moment,"");
leg_residual_z0->AddEntry("",header_wei,"");
leg_residual_z0->AddEntry("",header_r3D,"");
leg_residual_z0->AddEntry("",header_r2D,"");
leg_residual_z0->AddEntry(hist_residual_z0_pion_mass,"m_{#pi}","l");
leg_residual_z0->AddEntry(hist_residual_z0_true_mass,true_particle,"l");
leg_residual_z0->AddEntry(hist_residual_z0_true_mass_Par,particle,"l");
leg_residual_z0->AddEntry(hist_residual_z0_true_mass_aPar,anti_particle,"l");
leg_residual_z0->Draw("same");
can_residual_z0->Update();
can_residual_z0->SaveAs((plot_dir+plot_init+"_residual_z0"+momentum_stat+".pdf").c_str());
can_residual_z0->SaveAs((plot_dir+plot_init+"_residual_z0"+momentum_stat+".C").c_str());



TCanvas *can_uncertainty_d0 = new TCanvas("can_uncertainty_d0", "", 1600,1200);
hist_uncertainty_d0_pion_mass->Draw();
hist_uncertainty_d0_true_mass->Draw("sames");
hist_uncertainty_d0_true_mass_Par->Draw("sames");
hist_uncertainty_d0_true_mass_aPar->Draw("sames");
gPad->Update();
TPaveStats *tps_uncertainty_d0_pion_mass = (TPaveStats*)hist_uncertainty_d0_pion_mass->FindObject("stats");
TPaveStats *tps_uncertainty_d0_true_mass = (TPaveStats*)hist_uncertainty_d0_true_mass->FindObject("stats");
TPaveStats *tps_uncertainty_d0_true_mass_Par = (TPaveStats*)hist_uncertainty_d0_true_mass_Par->FindObject("stats");
TPaveStats *tps_uncertainty_d0_true_mass_aPar = (TPaveStats*)hist_uncertainty_d0_true_mass_aPar->FindObject("stats");
tps_uncertainty_d0_pion_mass->SetTextColor(2); tps_uncertainty_d0_pion_mass->SetLineColor(2);
tps_uncertainty_d0_true_mass->SetTextColor(4); tps_uncertainty_d0_true_mass->SetLineColor(4);
tps_uncertainty_d0_true_mass_Par->SetTextColor(1); tps_uncertainty_d0_true_mass_Par->SetLineColor(1);
tps_uncertainty_d0_true_mass_aPar->SetTextColor(6); tps_uncertainty_d0_true_mass_aPar->SetLineColor(6);
tps_uncertainty_d0_pion_mass->SetX1NDC(0.72); tps_uncertainty_d0_pion_mass->SetX2NDC(0.88); tps_uncertainty_d0_pion_mass->SetY1NDC(0.8); tps_uncertainty_d0_pion_mass->SetY2NDC(0.9);
X1 = tps_uncertainty_d0_pion_mass->GetX1NDC(); X2 = tps_uncertainty_d0_pion_mass->GetX2NDC(); Y1 = tps_uncertainty_d0_pion_mass->GetY1NDC(); Y2 = tps_uncertainty_d0_pion_mass->GetY2NDC();
tps_uncertainty_d0_true_mass->SetX1NDC(X1); tps_uncertainty_d0_true_mass->SetX2NDC(X2); tps_uncertainty_d0_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_uncertainty_d0_true_mass->SetY2NDC(Y1);
tps_uncertainty_d0_true_mass_Par->SetX1NDC(1-X2+0.1); tps_uncertainty_d0_true_mass_Par->SetX2NDC(1-X1+0.1); tps_uncertainty_d0_true_mass_Par->SetY1NDC(Y1); tps_uncertainty_d0_true_mass_Par->SetY2NDC(Y2);
tps_uncertainty_d0_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_uncertainty_d0_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_uncertainty_d0_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_uncertainty_d0_true_mass_aPar->SetY2NDC(Y1);
tps_uncertainty_d0_pion_mass->Draw("same");
tps_uncertainty_d0_true_mass->Draw("same");
tps_uncertainty_d0_true_mass_Par->Draw("same");
tps_uncertainty_d0_true_mass_aPar->Draw("same");
TLegend *leg_uncertainty_d0=new TLegend(0.65,0.50,0.85,0.70);
leg_uncertainty_d0->SetNColumns(2);
leg_uncertainty_d0->SetTextSize(TextSize);
leg_uncertainty_d0->SetHeader(header_par,"C");
leg_uncertainty_d0->AddEntry("",header_moment,"");
leg_uncertainty_d0->AddEntry("",header_wei,"");
leg_uncertainty_d0->AddEntry("",header_r3D,"");
leg_uncertainty_d0->AddEntry("",header_r2D,"");
leg_uncertainty_d0->AddEntry(hist_uncertainty_d0_pion_mass,"m_{#pi}","l");
leg_uncertainty_d0->AddEntry(hist_uncertainty_d0_true_mass,true_particle,"l");
leg_uncertainty_d0->AddEntry(hist_uncertainty_d0_true_mass_Par,particle,"l");
leg_uncertainty_d0->AddEntry(hist_uncertainty_d0_true_mass_aPar,anti_particle,"l");
leg_uncertainty_d0->Draw("same");
can_uncertainty_d0->Update();
can_uncertainty_d0->SaveAs((plot_dir+plot_init+"_uncertainty_d0"+momentum_stat+".pdf").c_str());
can_uncertainty_d0->SaveAs((plot_dir+plot_init+"_uncertainty_d0"+momentum_stat+".C").c_str());


TCanvas *can_uncertainty_Omega = new TCanvas("can_uncertainty_Omega", "", 1600,1200);
hist_uncertainty_Omega_pion_mass->Draw();
hist_uncertainty_Omega_true_mass->Draw("sames");
hist_uncertainty_Omega_true_mass_Par->Draw("sames");
hist_uncertainty_Omega_true_mass_aPar->Draw("sames");
gPad->Update();
TPaveStats *tps_uncertainty_Omega_pion_mass = (TPaveStats*)hist_uncertainty_Omega_pion_mass->FindObject("stats");
TPaveStats *tps_uncertainty_Omega_true_mass = (TPaveStats*)hist_uncertainty_Omega_true_mass->FindObject("stats");
TPaveStats *tps_uncertainty_Omega_true_mass_Par = (TPaveStats*)hist_uncertainty_Omega_true_mass_Par->FindObject("stats");
TPaveStats *tps_uncertainty_Omega_true_mass_aPar = (TPaveStats*)hist_uncertainty_Omega_true_mass_aPar->FindObject("stats");
tps_uncertainty_Omega_pion_mass->SetTextColor(2); tps_uncertainty_Omega_pion_mass->SetLineColor(2);
tps_uncertainty_Omega_true_mass->SetTextColor(4); tps_uncertainty_Omega_true_mass->SetLineColor(4);
tps_uncertainty_Omega_true_mass_Par->SetTextColor(1); tps_uncertainty_Omega_true_mass_Par->SetLineColor(1);
tps_uncertainty_Omega_true_mass_aPar->SetTextColor(6); tps_uncertainty_Omega_true_mass_aPar->SetLineColor(6);
tps_uncertainty_Omega_pion_mass->SetX1NDC(0.72); tps_uncertainty_Omega_pion_mass->SetX2NDC(0.88); tps_uncertainty_Omega_pion_mass->SetY1NDC(0.8); tps_uncertainty_Omega_pion_mass->SetY2NDC(0.9);
X1 = tps_uncertainty_Omega_pion_mass->GetX1NDC(); X2 = tps_uncertainty_Omega_pion_mass->GetX2NDC(); Y1 = tps_uncertainty_Omega_pion_mass->GetY1NDC(); Y2 = tps_uncertainty_Omega_pion_mass->GetY2NDC();
tps_uncertainty_Omega_true_mass->SetX1NDC(X1); tps_uncertainty_Omega_true_mass->SetX2NDC(X2); tps_uncertainty_Omega_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_uncertainty_Omega_true_mass->SetY2NDC(Y1);
tps_uncertainty_Omega_true_mass_Par->SetX1NDC(1-X2+0.1); tps_uncertainty_Omega_true_mass_Par->SetX2NDC(1-X1+0.1); tps_uncertainty_Omega_true_mass_Par->SetY1NDC(Y1); tps_uncertainty_Omega_true_mass_Par->SetY2NDC(Y2);
tps_uncertainty_Omega_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_uncertainty_Omega_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_uncertainty_Omega_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_uncertainty_Omega_true_mass_aPar->SetY2NDC(Y1);
tps_uncertainty_Omega_pion_mass->Draw("same");
tps_uncertainty_Omega_true_mass->Draw("same");
tps_uncertainty_Omega_true_mass_Par->Draw("same");
tps_uncertainty_Omega_true_mass_aPar->Draw("same");
TLegend *leg_uncertainty_Omega=new TLegend(0.65,0.50,0.85,0.70);
leg_uncertainty_Omega->SetNColumns(2);
leg_uncertainty_Omega->SetTextSize(TextSize);
leg_uncertainty_Omega->SetHeader(header_par,"C");
leg_uncertainty_Omega->AddEntry("",header_moment,"");
leg_uncertainty_Omega->AddEntry("",header_wei,"");
leg_uncertainty_Omega->AddEntry("",header_r3D,"");
leg_uncertainty_Omega->AddEntry("",header_r2D,"");
leg_uncertainty_Omega->AddEntry(hist_uncertainty_Omega_pion_mass,"m_{#pi}","l");
leg_uncertainty_Omega->AddEntry(hist_uncertainty_Omega_true_mass,true_particle,"l");
leg_uncertainty_Omega->AddEntry(hist_uncertainty_Omega_true_mass_Par,particle,"l");
leg_uncertainty_Omega->AddEntry(hist_uncertainty_Omega_true_mass_aPar,anti_particle,"l");
leg_uncertainty_Omega->Draw("same");
can_uncertainty_Omega->Update();
can_uncertainty_Omega->SaveAs((plot_dir+plot_init+"_uncertainty_Omega"+momentum_stat+".pdf").c_str());
can_uncertainty_Omega->SaveAs((plot_dir+plot_init+"_uncertainty_Omega"+momentum_stat+".C").c_str());


TCanvas *can_uncertainty_Phi = new TCanvas("can_uncertainty_Phi", "", 1600,1200);
hist_uncertainty_Phi_pion_mass->Draw();
hist_uncertainty_Phi_true_mass->Draw("sames");
hist_uncertainty_Phi_true_mass_Par->Draw("sames");
hist_uncertainty_Phi_true_mass_aPar->Draw("sames");
gPad->Update();
TPaveStats *tps_uncertainty_Phi_pion_mass = (TPaveStats*)hist_uncertainty_Phi_pion_mass->FindObject("stats");
TPaveStats *tps_uncertainty_Phi_true_mass = (TPaveStats*)hist_uncertainty_Phi_true_mass->FindObject("stats");
TPaveStats *tps_uncertainty_Phi_true_mass_Par = (TPaveStats*)hist_uncertainty_Phi_true_mass_Par->FindObject("stats");
TPaveStats *tps_uncertainty_Phi_true_mass_aPar = (TPaveStats*)hist_uncertainty_Phi_true_mass_aPar->FindObject("stats");
tps_uncertainty_Phi_pion_mass->SetTextColor(2); tps_uncertainty_Phi_pion_mass->SetLineColor(2);
tps_uncertainty_Phi_true_mass->SetTextColor(4); tps_uncertainty_Phi_true_mass->SetLineColor(4);
tps_uncertainty_Phi_true_mass_Par->SetTextColor(1); tps_uncertainty_Phi_true_mass_Par->SetLineColor(1);
tps_uncertainty_Phi_true_mass_aPar->SetTextColor(6); tps_uncertainty_Phi_true_mass_aPar->SetLineColor(6);
tps_uncertainty_Phi_pion_mass->SetX1NDC(0.72); tps_uncertainty_Phi_pion_mass->SetX2NDC(0.88); tps_uncertainty_Phi_pion_mass->SetY1NDC(0.8); tps_uncertainty_Phi_pion_mass->SetY2NDC(0.9);
X1 = tps_uncertainty_Phi_pion_mass->GetX1NDC(); X2 = tps_uncertainty_Phi_pion_mass->GetX2NDC(); Y1 = tps_uncertainty_Phi_pion_mass->GetY1NDC(); Y2 = tps_uncertainty_Phi_pion_mass->GetY2NDC();
tps_uncertainty_Phi_true_mass->SetX1NDC(X1); tps_uncertainty_Phi_true_mass->SetX2NDC(X2); tps_uncertainty_Phi_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_uncertainty_Phi_true_mass->SetY2NDC(Y1);
tps_uncertainty_Phi_true_mass_Par->SetX1NDC(1-X2+0.1); tps_uncertainty_Phi_true_mass_Par->SetX2NDC(1-X1+0.1); tps_uncertainty_Phi_true_mass_Par->SetY1NDC(Y1); tps_uncertainty_Phi_true_mass_Par->SetY2NDC(Y2);
tps_uncertainty_Phi_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_uncertainty_Phi_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_uncertainty_Phi_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_uncertainty_Phi_true_mass_aPar->SetY2NDC(Y1);
tps_uncertainty_Phi_pion_mass->Draw("same");
tps_uncertainty_Phi_true_mass->Draw("same");
tps_uncertainty_Phi_true_mass_Par->Draw("same");
tps_uncertainty_Phi_true_mass_aPar->Draw("same");
TLegend *leg_uncertainty_Phi=new TLegend(0.65,0.50,0.85,0.70);
leg_uncertainty_Phi->SetNColumns(2);
leg_uncertainty_Phi->SetTextSize(TextSize);
leg_uncertainty_Phi->SetHeader(header_par,"C");
leg_uncertainty_Phi->AddEntry("",header_moment,"");
leg_uncertainty_Phi->AddEntry("",header_wei,"");
leg_uncertainty_Phi->AddEntry("",header_r3D,"");
leg_uncertainty_Phi->AddEntry("",header_r2D,"");
leg_uncertainty_Phi->AddEntry(hist_uncertainty_Phi_pion_mass,"m_{#pi}","l");
leg_uncertainty_Phi->AddEntry(hist_uncertainty_Phi_true_mass,true_particle,"l");
leg_uncertainty_Phi->AddEntry(hist_uncertainty_Phi_true_mass_Par,particle,"l");
leg_uncertainty_Phi->AddEntry(hist_uncertainty_Phi_true_mass_aPar,anti_particle,"l");
leg_uncertainty_Phi->Draw("same");
can_uncertainty_Phi->Update();
can_uncertainty_Phi->SaveAs((plot_dir+plot_init+"_uncertainty_Phi"+momentum_stat+".pdf").c_str());
can_uncertainty_Phi->SaveAs((plot_dir+plot_init+"_uncertainty_Phi"+momentum_stat+".C").c_str());


TCanvas *can_uncertainty_tanLambda = new TCanvas("can_uncertainty_tanLambda", "", 1600,1200);
hist_uncertainty_tanLambda_pion_mass->Draw();
hist_uncertainty_tanLambda_true_mass->Draw("sames");
hist_uncertainty_tanLambda_true_mass_Par->Draw("sames");
hist_uncertainty_tanLambda_true_mass_aPar->Draw("sames");
gPad->Update();
TPaveStats *tps_uncertainty_tanLambda_pion_mass = (TPaveStats*)hist_uncertainty_tanLambda_pion_mass->FindObject("stats");
TPaveStats *tps_uncertainty_tanLambda_true_mass = (TPaveStats*)hist_uncertainty_tanLambda_true_mass->FindObject("stats");
TPaveStats *tps_uncertainty_tanLambda_true_mass_Par = (TPaveStats*)hist_uncertainty_tanLambda_true_mass_Par->FindObject("stats");
TPaveStats *tps_uncertainty_tanLambda_true_mass_aPar = (TPaveStats*)hist_uncertainty_tanLambda_true_mass_aPar->FindObject("stats");
tps_uncertainty_tanLambda_pion_mass->SetTextColor(2); tps_uncertainty_tanLambda_pion_mass->SetLineColor(2);
tps_uncertainty_tanLambda_true_mass->SetTextColor(4); tps_uncertainty_tanLambda_true_mass->SetLineColor(4);
tps_uncertainty_tanLambda_true_mass_Par->SetTextColor(1); tps_uncertainty_tanLambda_true_mass_Par->SetLineColor(1);
tps_uncertainty_tanLambda_true_mass_aPar->SetTextColor(6); tps_uncertainty_tanLambda_true_mass_aPar->SetLineColor(6);
tps_uncertainty_tanLambda_pion_mass->SetX1NDC(0.72); tps_uncertainty_tanLambda_pion_mass->SetX2NDC(0.88); tps_uncertainty_tanLambda_pion_mass->SetY1NDC(0.8); tps_uncertainty_tanLambda_pion_mass->SetY2NDC(0.9);
X1 = tps_uncertainty_tanLambda_pion_mass->GetX1NDC(); X2 = tps_uncertainty_tanLambda_pion_mass->GetX2NDC(); Y1 = tps_uncertainty_tanLambda_pion_mass->GetY1NDC(); Y2 = tps_uncertainty_tanLambda_pion_mass->GetY2NDC();
tps_uncertainty_tanLambda_true_mass->SetX1NDC(X1); tps_uncertainty_tanLambda_true_mass->SetX2NDC(X2); tps_uncertainty_tanLambda_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_uncertainty_tanLambda_true_mass->SetY2NDC(Y1);
tps_uncertainty_tanLambda_true_mass_Par->SetX1NDC(1-X2+0.1); tps_uncertainty_tanLambda_true_mass_Par->SetX2NDC(1-X1+0.1); tps_uncertainty_tanLambda_true_mass_Par->SetY1NDC(Y1); tps_uncertainty_tanLambda_true_mass_Par->SetY2NDC(Y2);
tps_uncertainty_tanLambda_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_uncertainty_tanLambda_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_uncertainty_tanLambda_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_uncertainty_tanLambda_true_mass_aPar->SetY2NDC(Y1);
tps_uncertainty_tanLambda_pion_mass->Draw("same");
tps_uncertainty_tanLambda_true_mass->Draw("same");
tps_uncertainty_tanLambda_true_mass_Par->Draw("same");
tps_uncertainty_tanLambda_true_mass_aPar->Draw("same");
TLegend *leg_uncertainty_tanLambda=new TLegend(0.65,0.50,0.85,0.70);
leg_uncertainty_tanLambda->SetNColumns(2);
leg_uncertainty_tanLambda->SetTextSize(TextSize);
leg_uncertainty_tanLambda->SetHeader(header_par,"C");
leg_uncertainty_tanLambda->AddEntry("",header_moment,"");
leg_uncertainty_tanLambda->AddEntry("",header_wei,"");
leg_uncertainty_tanLambda->AddEntry("",header_r3D,"");
leg_uncertainty_tanLambda->AddEntry("",header_r2D,"");
leg_uncertainty_tanLambda->AddEntry(hist_uncertainty_tanLambda_pion_mass,"m_{#pi}","l");
leg_uncertainty_tanLambda->AddEntry(hist_uncertainty_tanLambda_true_mass,true_particle,"l");
leg_uncertainty_tanLambda->AddEntry(hist_uncertainty_tanLambda_true_mass_Par,particle,"l");
leg_uncertainty_tanLambda->AddEntry(hist_uncertainty_tanLambda_true_mass_aPar,anti_particle,"l");
leg_uncertainty_tanLambda->Draw("same");
can_uncertainty_tanLambda->Update();
can_uncertainty_tanLambda->SaveAs((plot_dir+plot_init+"_uncertainty_tanLambda"+momentum_stat+".pdf").c_str());
can_uncertainty_tanLambda->SaveAs((plot_dir+plot_init+"_uncertainty_tanLambda"+momentum_stat+".C").c_str());


TCanvas *can_uncertainty_z0 = new TCanvas("can_uncertainty_z0", "", 1600,1200);
hist_uncertainty_z0_pion_mass->Draw();
hist_uncertainty_z0_true_mass->Draw("sames");
hist_uncertainty_z0_true_mass_Par->Draw("sames");
hist_uncertainty_z0_true_mass_aPar->Draw("sames");
gPad->Update();
TPaveStats *tps_uncertainty_z0_pion_mass = (TPaveStats*)hist_uncertainty_z0_pion_mass->FindObject("stats");
TPaveStats *tps_uncertainty_z0_true_mass = (TPaveStats*)hist_uncertainty_z0_true_mass->FindObject("stats");
TPaveStats *tps_uncertainty_z0_true_mass_Par = (TPaveStats*)hist_uncertainty_z0_true_mass_Par->FindObject("stats");
TPaveStats *tps_uncertainty_z0_true_mass_aPar = (TPaveStats*)hist_uncertainty_z0_true_mass_aPar->FindObject("stats");
tps_uncertainty_z0_pion_mass->SetTextColor(2); tps_uncertainty_z0_pion_mass->SetLineColor(2);
tps_uncertainty_z0_true_mass->SetTextColor(4); tps_uncertainty_z0_true_mass->SetLineColor(4);
tps_uncertainty_z0_true_mass_Par->SetTextColor(1); tps_uncertainty_z0_true_mass_Par->SetLineColor(1);
tps_uncertainty_z0_true_mass_aPar->SetTextColor(6); tps_uncertainty_z0_true_mass_aPar->SetLineColor(6);
tps_uncertainty_z0_pion_mass->SetX1NDC(0.72); tps_uncertainty_z0_pion_mass->SetX2NDC(0.88); tps_uncertainty_z0_pion_mass->SetY1NDC(0.8); tps_uncertainty_z0_pion_mass->SetY2NDC(0.9);
X1 = tps_uncertainty_z0_pion_mass->GetX1NDC(); X2 = tps_uncertainty_z0_pion_mass->GetX2NDC(); Y1 = tps_uncertainty_z0_pion_mass->GetY1NDC(); Y2 = tps_uncertainty_z0_pion_mass->GetY2NDC();
tps_uncertainty_z0_true_mass->SetX1NDC(X1); tps_uncertainty_z0_true_mass->SetX2NDC(X2); tps_uncertainty_z0_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_uncertainty_z0_true_mass->SetY2NDC(Y1);
tps_uncertainty_z0_true_mass_Par->SetX1NDC(1-X2+0.1); tps_uncertainty_z0_true_mass_Par->SetX2NDC(1-X1+0.1); tps_uncertainty_z0_true_mass_Par->SetY1NDC(Y1); tps_uncertainty_z0_true_mass_Par->SetY2NDC(Y2);
tps_uncertainty_z0_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_uncertainty_z0_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_uncertainty_z0_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_uncertainty_z0_true_mass_aPar->SetY2NDC(Y1);
tps_uncertainty_z0_pion_mass->Draw("same");
tps_uncertainty_z0_true_mass->Draw("same");
tps_uncertainty_z0_true_mass_Par->Draw("same");
tps_uncertainty_z0_true_mass_aPar->Draw("same");
TLegend *leg_uncertainty_z0=new TLegend(0.65,0.50,0.85,0.70);
leg_uncertainty_z0->SetNColumns(2);
leg_uncertainty_z0->SetTextSize(TextSize);
leg_uncertainty_z0->SetHeader(header_par,"C");
leg_uncertainty_z0->AddEntry("",header_moment,"");
leg_uncertainty_z0->AddEntry("",header_wei,"");
leg_uncertainty_z0->AddEntry("",header_r3D,"");
leg_uncertainty_z0->AddEntry("",header_r2D,"");
leg_uncertainty_z0->AddEntry(hist_uncertainty_z0_pion_mass,"m_{#pi}","l");
leg_uncertainty_z0->AddEntry(hist_uncertainty_z0_true_mass,true_particle,"l");
leg_uncertainty_z0->AddEntry(hist_uncertainty_z0_true_mass_Par,particle,"l");
leg_uncertainty_z0->AddEntry(hist_uncertainty_z0_true_mass_aPar,anti_particle,"l");
leg_uncertainty_z0->Draw("same");
can_uncertainty_z0->Update();
can_uncertainty_z0->SaveAs((plot_dir+plot_init+"_uncertainty_z0"+momentum_stat+".pdf").c_str());
can_uncertainty_z0->SaveAs((plot_dir+plot_init+"_uncertainty_z0"+momentum_stat+".C").c_str());

ildStyle->SetOptStat(0);

TCanvas *can_momentum = new TCanvas("can_momentum", "", 1600,1200);
hist_momentum->Draw();
hist_momentum_Par->Draw("sames");
hist_momentum_aPar->Draw("sames");
TLegend *leg_momentum = new TLegend(0.65,0.50,0.85,0.70);
leg_momentum->SetHeader("p dist.","C");
leg_momentum->AddEntry("",header_wei,"");
leg_momentum->AddEntry("",header_r3D,"");
leg_momentum->AddEntry("",header_r2D,"");
leg_momentum->AddEntry(hist_momentum,par_type_all,"l");
leg_momentum->AddEntry(hist_momentum_Par,par_type_par,"l");
leg_momentum->AddEntry(hist_momentum_aPar,par_type_Apar,"l");
leg_momentum->Draw("same");
can_momentum->Update();
can_momentum->SaveAs((plot_dir+plot_init+"_momentum.pdf").c_str());
can_momentum->SaveAs((plot_dir+plot_init+"_momentum.C").c_str());



gStyle->SetOptFit(1);
ildStyle->SetOptStat(001111111);

//gStyle->SetOptStat(000111111);
int y_max = 0;

TCanvas *can_pull_d0 = new TCanvas("can_pull_d0", "", 1600,1200);
hist_pull_d0_pion_mass->Draw();
hist_pull_d0_true_mass->Draw("sames");
hist_pull_d0_true_mass_Par->Draw("sames");
hist_pull_d0_true_mass_aPar->Draw("sames");
hist_pull_d0_pion_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_d0_pion_mass->GetFunction("gaus")->SetLineColor(2); hist_pull_d0_pion_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_d0_pion_mass->GetFunction("gaus")->SetLineWidth(1);
hist_pull_d0_true_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_d0_true_mass->GetFunction("gaus")->SetLineColor(4); hist_pull_d0_true_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_d0_true_mass->GetFunction("gaus")->SetLineWidth(1);
hist_pull_d0_true_mass_Par->Fit("gaus","","",fit_min,fit_max); hist_pull_d0_true_mass_Par->GetFunction("gaus")->SetLineColor(1); hist_pull_d0_true_mass_Par->GetFunction("gaus")->SetLineStyle(2); hist_pull_d0_true_mass_Par->GetFunction("gaus")->SetLineWidth(1);
hist_pull_d0_true_mass_aPar->Fit("gaus","","",fit_min,fit_max); hist_pull_d0_true_mass_aPar->GetFunction("gaus")->SetLineColor(6); hist_pull_d0_true_mass_aPar->GetFunction("gaus")->SetLineStyle(2); hist_pull_d0_true_mass_aPar->GetFunction("gaus")->SetLineWidth(1);
y_max = 1.1 * hist_pull_d0_pion_mass->GetMaximum();
hist_pull_d0_pion_mass->GetYaxis()->SetRangeUser(0, y_max);
TLine *l_n1_d0 = new TLine(-1,0,-1,y_max); l_n1_d0->SetLineColor(1); l_n1_d0->SetLineStyle(3); l_n1_d0->SetLineWidth(1);
TLine *l_p1_d0 = new TLine(1,0,1,y_max); l_p1_d0->SetLineColor(1); l_p1_d0->SetLineStyle(3); l_p1_d0->SetLineWidth(1);
TLine *l_0_d0 = new TLine(0,0,0,y_max); l_0_d0->SetLineColor(1); l_0_d0->SetLineStyle(3); l_0_d0->SetLineWidth(1);

l_n1_d0->Draw("same");
l_p1_d0->Draw("same");
l_0_d0->Draw("same");

gPad->Update();
TPaveStats *tps_pull_d0_pion_mass = (TPaveStats*)hist_pull_d0_pion_mass->FindObject("stats");
TPaveStats *tps_pull_d0_true_mass = (TPaveStats*)hist_pull_d0_true_mass->FindObject("stats");
TPaveStats *tps_pull_d0_true_mass_Par = (TPaveStats*)hist_pull_d0_true_mass_Par->FindObject("stats");
TPaveStats *tps_pull_d0_true_mass_aPar = (TPaveStats*)hist_pull_d0_true_mass_aPar->FindObject("stats");
tps_pull_d0_pion_mass->SetTextColor(2); tps_pull_d0_pion_mass->SetLineColor(2);
tps_pull_d0_true_mass->SetTextColor(4); tps_pull_d0_true_mass->SetLineColor(4);
tps_pull_d0_true_mass_Par->SetTextColor(1); tps_pull_d0_true_mass_Par->SetLineColor(1);
tps_pull_d0_true_mass_aPar->SetTextColor(6); tps_pull_d0_true_mass_aPar->SetLineColor(6);
tps_pull_d0_pion_mass->SetX1NDC(0.72); tps_pull_d0_pion_mass->SetX2NDC(0.88); tps_pull_d0_pion_mass->SetY1NDC(0.75); tps_pull_d0_pion_mass->SetY2NDC(0.9);
X1 = tps_pull_d0_pion_mass->GetX1NDC(); X2 = tps_pull_d0_pion_mass->GetX2NDC(); Y1 = tps_pull_d0_pion_mass->GetY1NDC(); Y2 = tps_pull_d0_pion_mass->GetY2NDC();
tps_pull_d0_true_mass->SetX1NDC(X1); tps_pull_d0_true_mass->SetX2NDC(X2); tps_pull_d0_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_pull_d0_true_mass->SetY2NDC(Y1);
tps_pull_d0_true_mass_Par->SetX1NDC(1-X2+0.1); tps_pull_d0_true_mass_Par->SetX2NDC(1-X1+0.1); tps_pull_d0_true_mass_Par->SetY1NDC(Y1); tps_pull_d0_true_mass_Par->SetY2NDC(Y2);
tps_pull_d0_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_pull_d0_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_pull_d0_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_pull_d0_true_mass_aPar->SetY2NDC(Y1);
tps_pull_d0_pion_mass->Draw("same");
tps_pull_d0_true_mass->Draw("same");
tps_pull_d0_true_mass_Par->Draw("same");
tps_pull_d0_true_mass_aPar->Draw("same");
TLegend *leg_pull_d0=new TLegend(0.65,2 * Y1 - Y2 - 0.2,0.85,2 * Y1 - Y2);
leg_pull_d0->SetNColumns(2);
leg_pull_d0->SetTextSize(TextSize);
leg_pull_d0->SetHeader(header_par,"C");
leg_pull_d0->AddEntry("",header_moment,"");
leg_pull_d0->AddEntry("",header_wei,"");
leg_pull_d0->AddEntry("",header_r3D,"");
leg_pull_d0->AddEntry("",header_r2D,"");
leg_pull_d0->AddEntry(hist_pull_d0_pion_mass,"m_{#pi}","l");
leg_pull_d0->AddEntry(hist_pull_d0_true_mass,true_particle,"l");
leg_pull_d0->AddEntry(hist_pull_d0_true_mass_Par,particle,"l");
leg_pull_d0->AddEntry(hist_pull_d0_true_mass_aPar,anti_particle,"l");
leg_pull_d0->Draw("same");
can_pull_d0->Update();
can_pull_d0->SaveAs((plot_dir+plot_init+"_pull_d0"+momentum_stat+".pdf").c_str());
can_pull_d0->SaveAs((plot_dir+plot_init+"_pull_d0"+momentum_stat+".C").c_str());


TCanvas *can_pull_Omega = new TCanvas("can_pull_Omega", "", 1600,1200);
hist_pull_Omega_pion_mass->Draw();
hist_pull_Omega_true_mass->Draw("sames");
hist_pull_Omega_true_mass_Par->Draw("sames");
hist_pull_Omega_true_mass_aPar->Draw("sames");
hist_pull_Omega_pion_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_Omega_pion_mass->GetFunction("gaus")->SetLineColor(2); hist_pull_Omega_pion_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_Omega_pion_mass->GetFunction("gaus")->SetLineWidth(1);
hist_pull_Omega_true_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_Omega_true_mass->GetFunction("gaus")->SetLineColor(4); hist_pull_Omega_true_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_Omega_true_mass->GetFunction("gaus")->SetLineWidth(1);
hist_pull_Omega_true_mass_Par->Fit("gaus","","",fit_min,fit_max); hist_pull_Omega_true_mass_Par->GetFunction("gaus")->SetLineColor(1); hist_pull_Omega_true_mass_Par->GetFunction("gaus")->SetLineStyle(2); hist_pull_Omega_true_mass_Par->GetFunction("gaus")->SetLineWidth(1);
hist_pull_Omega_true_mass_aPar->Fit("gaus","","",fit_min,fit_max); hist_pull_Omega_true_mass_aPar->GetFunction("gaus")->SetLineColor(6); hist_pull_Omega_true_mass_aPar->GetFunction("gaus")->SetLineStyle(2); hist_pull_Omega_true_mass_aPar->GetFunction("gaus")->SetLineWidth(1);
y_max = 1.1 * hist_pull_Omega_pion_mass->GetMaximum();
hist_pull_Omega_pion_mass->GetYaxis()->SetRangeUser(0, y_max);
TLine *l_n1_Omega = new TLine(-1,0,-1,y_max); l_n1_Omega->SetLineColor(1); l_n1_Omega->SetLineStyle(3); l_n1_Omega->SetLineWidth(1);
TLine *l_p1_Omega = new TLine(1,0,1,y_max); l_p1_Omega->SetLineColor(1); l_p1_Omega->SetLineStyle(3); l_p1_Omega->SetLineWidth(1);
TLine *l_0_Omega = new TLine(0,0,0,y_max); l_0_Omega->SetLineColor(1); l_0_Omega->SetLineStyle(3); l_0_Omega->SetLineWidth(1);

l_n1_Omega->Draw("same");
l_p1_Omega->Draw("same");
l_0_Omega->Draw("same");

gPad->Update();
TPaveStats *tps_pull_Omega_pion_mass = (TPaveStats*)hist_pull_Omega_pion_mass->FindObject("stats");
TPaveStats *tps_pull_Omega_true_mass = (TPaveStats*)hist_pull_Omega_true_mass->FindObject("stats");
TPaveStats *tps_pull_Omega_true_mass_Par = (TPaveStats*)hist_pull_Omega_true_mass_Par->FindObject("stats");
TPaveStats *tps_pull_Omega_true_mass_aPar = (TPaveStats*)hist_pull_Omega_true_mass_aPar->FindObject("stats");
tps_pull_Omega_pion_mass->SetTextColor(2); tps_pull_Omega_pion_mass->SetLineColor(2);
tps_pull_Omega_true_mass->SetTextColor(4); tps_pull_Omega_true_mass->SetLineColor(4);
tps_pull_Omega_true_mass_Par->SetTextColor(1); tps_pull_Omega_true_mass_Par->SetLineColor(1);
tps_pull_Omega_true_mass_aPar->SetTextColor(6); tps_pull_Omega_true_mass_aPar->SetLineColor(6);
tps_pull_Omega_pion_mass->SetX1NDC(0.72); tps_pull_Omega_pion_mass->SetX2NDC(0.88); tps_pull_Omega_pion_mass->SetY1NDC(0.75); tps_pull_Omega_pion_mass->SetY2NDC(0.9);
X1 = tps_pull_Omega_pion_mass->GetX1NDC(); X2 = tps_pull_Omega_pion_mass->GetX2NDC(); Y1 = tps_pull_Omega_pion_mass->GetY1NDC(); Y2 = tps_pull_Omega_pion_mass->GetY2NDC();
tps_pull_Omega_true_mass->SetX1NDC(X1); tps_pull_Omega_true_mass->SetX2NDC(X2); tps_pull_Omega_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_pull_Omega_true_mass->SetY2NDC(Y1);
tps_pull_Omega_true_mass_Par->SetX1NDC(1-X2+0.1); tps_pull_Omega_true_mass_Par->SetX2NDC(1-X1+0.1); tps_pull_Omega_true_mass_Par->SetY1NDC(Y1); tps_pull_Omega_true_mass_Par->SetY2NDC(Y2);
tps_pull_Omega_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_pull_Omega_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_pull_Omega_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_pull_Omega_true_mass_aPar->SetY2NDC(Y1);
tps_pull_Omega_pion_mass->Draw("same");
tps_pull_Omega_true_mass->Draw("same");
tps_pull_Omega_true_mass_Par->Draw("same");
tps_pull_Omega_true_mass_aPar->Draw("same");
TLegend *leg_pull_Omega=new TLegend(0.65,2 * Y1 - Y2 - 0.2,0.85,2 * Y1 - Y2);
leg_pull_Omega->SetNColumns(2);
leg_pull_Omega->SetTextSize(TextSize);
leg_pull_Omega->SetHeader(header_par,"C");
leg_pull_Omega->AddEntry("",header_moment,"");
leg_pull_Omega->AddEntry("",header_wei,"");
leg_pull_Omega->AddEntry("",header_r3D,"");
leg_pull_Omega->AddEntry("",header_r2D,"");
leg_pull_Omega->AddEntry(hist_pull_Omega_pion_mass,"m_{#pi}","l");
leg_pull_Omega->AddEntry(hist_pull_Omega_true_mass,true_particle,"l");
leg_pull_Omega->AddEntry(hist_pull_Omega_true_mass_Par,particle,"l");
leg_pull_Omega->AddEntry(hist_pull_Omega_true_mass_aPar,anti_particle,"l");
leg_pull_Omega->Draw("same");
can_pull_Omega->Update();
can_pull_Omega->SaveAs((plot_dir+plot_init+"_pull_Omega"+momentum_stat+".pdf").c_str());
can_pull_Omega->SaveAs((plot_dir+plot_init+"_pull_Omega"+momentum_stat+".C").c_str());


TCanvas *can_pull_Phi = new TCanvas("can_pull_Phi", "", 1600,1200);
hist_pull_Phi_pion_mass->Draw();
hist_pull_Phi_true_mass->Draw("sames");
hist_pull_Phi_true_mass_Par->Draw("sames");
hist_pull_Phi_true_mass_aPar->Draw("sames");
hist_pull_Phi_pion_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_Phi_pion_mass->GetFunction("gaus")->SetLineColor(2); hist_pull_Phi_pion_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_Phi_pion_mass->GetFunction("gaus")->SetLineWidth(1);
hist_pull_Phi_true_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_Phi_true_mass->GetFunction("gaus")->SetLineColor(4); hist_pull_Phi_true_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_Phi_true_mass->GetFunction("gaus")->SetLineWidth(1);
hist_pull_Phi_true_mass_Par->Fit("gaus","","",fit_min,fit_max); hist_pull_Phi_true_mass_Par->GetFunction("gaus")->SetLineColor(1); hist_pull_Phi_true_mass_Par->GetFunction("gaus")->SetLineStyle(2); hist_pull_Phi_true_mass_Par->GetFunction("gaus")->SetLineWidth(1);
hist_pull_Phi_true_mass_aPar->Fit("gaus","","",fit_min,fit_max); hist_pull_Phi_true_mass_aPar->GetFunction("gaus")->SetLineColor(6); hist_pull_Phi_true_mass_aPar->GetFunction("gaus")->SetLineStyle(2); hist_pull_Phi_true_mass_aPar->GetFunction("gaus")->SetLineWidth(1);
y_max = 1.1 * hist_pull_Phi_pion_mass->GetMaximum();
hist_pull_Phi_pion_mass->GetYaxis()->SetRangeUser(0, y_max);
TLine *l_n1_Phi = new TLine(-1,0,-1,y_max); l_n1_Phi->SetLineColor(1); l_n1_Phi->SetLineStyle(3); l_n1_Phi->SetLineWidth(1);
TLine *l_p1_Phi = new TLine(1,0,1,y_max); l_p1_Phi->SetLineColor(1); l_p1_Phi->SetLineStyle(3); l_p1_Phi->SetLineWidth(1);
TLine *l_0_Phi = new TLine(0,0,0,y_max); l_0_Phi->SetLineColor(1); l_0_Phi->SetLineStyle(3); l_0_Phi->SetLineWidth(1);

l_n1_Phi->Draw("same");
l_p1_Phi->Draw("same");
l_0_Phi->Draw("same");

gPad->Update();
TPaveStats *tps_pull_Phi_pion_mass = (TPaveStats*)hist_pull_Phi_pion_mass->FindObject("stats");
TPaveStats *tps_pull_Phi_true_mass = (TPaveStats*)hist_pull_Phi_true_mass->FindObject("stats");
TPaveStats *tps_pull_Phi_true_mass_Par = (TPaveStats*)hist_pull_Phi_true_mass_Par->FindObject("stats");
TPaveStats *tps_pull_Phi_true_mass_aPar = (TPaveStats*)hist_pull_Phi_true_mass_aPar->FindObject("stats");
tps_pull_Phi_pion_mass->SetTextColor(2); tps_pull_Phi_pion_mass->SetLineColor(2);
tps_pull_Phi_true_mass->SetTextColor(4); tps_pull_Phi_true_mass->SetLineColor(4);
tps_pull_Phi_true_mass_Par->SetTextColor(1); tps_pull_Phi_true_mass_Par->SetLineColor(1);
tps_pull_Phi_true_mass_aPar->SetTextColor(6); tps_pull_Phi_true_mass_aPar->SetLineColor(6);
tps_pull_Phi_pion_mass->SetX1NDC(0.72); tps_pull_Phi_pion_mass->SetX2NDC(0.88); tps_pull_Phi_pion_mass->SetY1NDC(0.75); tps_pull_Phi_pion_mass->SetY2NDC(0.9);
X1 = tps_pull_Phi_pion_mass->GetX1NDC(); X2 = tps_pull_Phi_pion_mass->GetX2NDC(); Y1 = tps_pull_Phi_pion_mass->GetY1NDC(); Y2 = tps_pull_Phi_pion_mass->GetY2NDC();
tps_pull_Phi_true_mass->SetX1NDC(X1); tps_pull_Phi_true_mass->SetX2NDC(X2); tps_pull_Phi_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_pull_Phi_true_mass->SetY2NDC(Y1);
tps_pull_Phi_true_mass_Par->SetX1NDC(1-X2+0.1); tps_pull_Phi_true_mass_Par->SetX2NDC(1-X1+0.1); tps_pull_Phi_true_mass_Par->SetY1NDC(Y1); tps_pull_Phi_true_mass_Par->SetY2NDC(Y2);
tps_pull_Phi_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_pull_Phi_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_pull_Phi_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_pull_Phi_true_mass_aPar->SetY2NDC(Y1);
tps_pull_Phi_pion_mass->Draw("same");
tps_pull_Phi_true_mass->Draw("same");
tps_pull_Phi_true_mass_Par->Draw("same");
tps_pull_Phi_true_mass_aPar->Draw("same");
TLegend *leg_pull_Phi=new TLegend(0.65,2 * Y1 - Y2 - 0.2,0.85,2 * Y1 - Y2);
leg_pull_Phi->SetNColumns(2);
leg_pull_Phi->SetTextSize(TextSize);
leg_pull_Phi->SetHeader(header_par,"C");
leg_pull_Phi->AddEntry("",header_moment,"");
leg_pull_Phi->AddEntry("",header_wei,"");
leg_pull_Phi->AddEntry("",header_r3D,"");
leg_pull_Phi->AddEntry("",header_r2D,"");
leg_pull_Phi->AddEntry(hist_pull_Phi_pion_mass,"m_{#pi}","l");
leg_pull_Phi->AddEntry(hist_pull_Phi_true_mass,true_particle,"l");
leg_pull_Phi->AddEntry(hist_pull_Phi_true_mass_Par,particle,"l");
leg_pull_Phi->AddEntry(hist_pull_Phi_true_mass_aPar,anti_particle,"l");
leg_pull_Phi->Draw("same");
can_pull_Phi->Update();
can_pull_Phi->SaveAs((plot_dir+plot_init+"_pull_Phi"+momentum_stat+".pdf").c_str());
can_pull_Phi->SaveAs((plot_dir+plot_init+"_pull_Phi"+momentum_stat+".C").c_str());


TCanvas *can_pull_tanLambda = new TCanvas("can_pull_tanLambda", "", 1600,1200);
hist_pull_tanLambda_pion_mass->Draw();
hist_pull_tanLambda_true_mass->Draw("sames");
hist_pull_tanLambda_true_mass_Par->Draw("sames");
hist_pull_tanLambda_true_mass_aPar->Draw("sames");
hist_pull_tanLambda_pion_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_tanLambda_pion_mass->GetFunction("gaus")->SetLineColor(2); hist_pull_tanLambda_pion_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_tanLambda_pion_mass->GetFunction("gaus")->SetLineWidth(1);
hist_pull_tanLambda_true_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_tanLambda_true_mass->GetFunction("gaus")->SetLineColor(4); hist_pull_tanLambda_true_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_tanLambda_true_mass->GetFunction("gaus")->SetLineWidth(1);
hist_pull_tanLambda_true_mass_Par->Fit("gaus","","",fit_min,fit_max); hist_pull_tanLambda_true_mass_Par->GetFunction("gaus")->SetLineColor(1); hist_pull_tanLambda_true_mass_Par->GetFunction("gaus")->SetLineStyle(2); hist_pull_tanLambda_true_mass_Par->GetFunction("gaus")->SetLineWidth(1);
hist_pull_tanLambda_true_mass_aPar->Fit("gaus","","",fit_min,fit_max); hist_pull_tanLambda_true_mass_aPar->GetFunction("gaus")->SetLineColor(6); hist_pull_tanLambda_true_mass_aPar->GetFunction("gaus")->SetLineStyle(2); hist_pull_tanLambda_true_mass_aPar->GetFunction("gaus")->SetLineWidth(1);
y_max = 1.1 * hist_pull_tanLambda_pion_mass->GetMaximum();
hist_pull_tanLambda_pion_mass->GetYaxis()->SetRangeUser(0, y_max);
TLine *l_n1_tanLambda = new TLine(-1,0,-1,y_max); l_n1_tanLambda->SetLineColor(1); l_n1_tanLambda->SetLineStyle(3); l_n1_tanLambda->SetLineWidth(1);
TLine *l_p1_tanLambda = new TLine(1,0,1,y_max); l_p1_tanLambda->SetLineColor(1); l_p1_tanLambda->SetLineStyle(3); l_p1_tanLambda->SetLineWidth(1);
TLine *l_0_tanLambda = new TLine(0,0,0,y_max); l_0_tanLambda->SetLineColor(1); l_0_tanLambda->SetLineStyle(3); l_0_tanLambda->SetLineWidth(1);

l_n1_tanLambda->Draw("same");
l_p1_tanLambda->Draw("same");
l_0_tanLambda->Draw("same");

gPad->Update();
TPaveStats *tps_pull_tanLambda_pion_mass = (TPaveStats*)hist_pull_tanLambda_pion_mass->FindObject("stats");
TPaveStats *tps_pull_tanLambda_true_mass = (TPaveStats*)hist_pull_tanLambda_true_mass->FindObject("stats");
TPaveStats *tps_pull_tanLambda_true_mass_Par = (TPaveStats*)hist_pull_tanLambda_true_mass_Par->FindObject("stats");
TPaveStats *tps_pull_tanLambda_true_mass_aPar = (TPaveStats*)hist_pull_tanLambda_true_mass_aPar->FindObject("stats");
tps_pull_tanLambda_pion_mass->SetTextColor(2); tps_pull_tanLambda_pion_mass->SetLineColor(2);
tps_pull_tanLambda_true_mass->SetTextColor(4); tps_pull_tanLambda_true_mass->SetLineColor(4);
tps_pull_tanLambda_true_mass_Par->SetTextColor(1); tps_pull_tanLambda_true_mass_Par->SetLineColor(1);
tps_pull_tanLambda_true_mass_aPar->SetTextColor(6); tps_pull_tanLambda_true_mass_aPar->SetLineColor(6);
tps_pull_tanLambda_pion_mass->SetX1NDC(0.72); tps_pull_tanLambda_pion_mass->SetX2NDC(0.88); tps_pull_tanLambda_pion_mass->SetY1NDC(0.75); tps_pull_tanLambda_pion_mass->SetY2NDC(0.9);
X1 = tps_pull_tanLambda_pion_mass->GetX1NDC(); X2 = tps_pull_tanLambda_pion_mass->GetX2NDC(); Y1 = tps_pull_tanLambda_pion_mass->GetY1NDC(); Y2 = tps_pull_tanLambda_pion_mass->GetY2NDC();
tps_pull_tanLambda_true_mass->SetX1NDC(X1); tps_pull_tanLambda_true_mass->SetX2NDC(X2); tps_pull_tanLambda_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_pull_tanLambda_true_mass->SetY2NDC(Y1);
tps_pull_tanLambda_true_mass_Par->SetX1NDC(1-X2+0.1); tps_pull_tanLambda_true_mass_Par->SetX2NDC(1-X1+0.1); tps_pull_tanLambda_true_mass_Par->SetY1NDC(Y1); tps_pull_tanLambda_true_mass_Par->SetY2NDC(Y2);
tps_pull_tanLambda_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_pull_tanLambda_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_pull_tanLambda_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_pull_tanLambda_true_mass_aPar->SetY2NDC(Y1);
tps_pull_tanLambda_pion_mass->Draw("same");
tps_pull_tanLambda_true_mass->Draw("same");
tps_pull_tanLambda_true_mass_Par->Draw("same");
tps_pull_tanLambda_true_mass_aPar->Draw("same");
TLegend *leg_pull_tanLambda=new TLegend(0.65,2 * Y1 - Y2 - 0.2,0.85,2 * Y1 - Y2);
leg_pull_tanLambda->SetNColumns(2);
leg_pull_tanLambda->SetTextSize(TextSize);
leg_pull_tanLambda->SetHeader(header_par,"C");
leg_pull_tanLambda->AddEntry("",header_moment,"");
leg_pull_tanLambda->AddEntry("",header_wei,"");
leg_pull_tanLambda->AddEntry("",header_r3D,"");
leg_pull_tanLambda->AddEntry("",header_r2D,"");
leg_pull_tanLambda->AddEntry(hist_pull_tanLambda_pion_mass,"m_{#pi}","l");
leg_pull_tanLambda->AddEntry(hist_pull_tanLambda_true_mass,true_particle,"l");
leg_pull_tanLambda->AddEntry(hist_pull_tanLambda_true_mass_Par,particle,"l");
leg_pull_tanLambda->AddEntry(hist_pull_tanLambda_true_mass_aPar,anti_particle,"l");
leg_pull_tanLambda->Draw("same");
can_pull_tanLambda->Update();
can_pull_tanLambda->SaveAs((plot_dir+plot_init+"_pull_tanLambda"+momentum_stat+".pdf").c_str());
can_pull_tanLambda->SaveAs((plot_dir+plot_init+"_pull_tanLambda"+momentum_stat+".C").c_str());


TCanvas *can_pull_z0 = new TCanvas("can_pull_z0", "", 1600,1200);
hist_pull_z0_pion_mass->Draw();
hist_pull_z0_true_mass->Draw("sames");
hist_pull_z0_true_mass_Par->Draw("sames");
hist_pull_z0_true_mass_aPar->Draw("sames");
hist_pull_z0_pion_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_z0_pion_mass->GetFunction("gaus")->SetLineColor(2); hist_pull_z0_pion_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_z0_pion_mass->GetFunction("gaus")->SetLineWidth(1);
hist_pull_z0_true_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_z0_true_mass->GetFunction("gaus")->SetLineColor(4); hist_pull_z0_true_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_z0_true_mass->GetFunction("gaus")->SetLineWidth(1);
hist_pull_z0_true_mass_Par->Fit("gaus","","",fit_min,fit_max); hist_pull_z0_true_mass_Par->GetFunction("gaus")->SetLineColor(1); hist_pull_z0_true_mass_Par->GetFunction("gaus")->SetLineStyle(2); hist_pull_z0_true_mass_Par->GetFunction("gaus")->SetLineWidth(1);
hist_pull_z0_true_mass_aPar->Fit("gaus","","",fit_min,fit_max); hist_pull_z0_true_mass_aPar->GetFunction("gaus")->SetLineColor(6); hist_pull_z0_true_mass_aPar->GetFunction("gaus")->SetLineStyle(2); hist_pull_z0_true_mass_aPar->GetFunction("gaus")->SetLineWidth(1);
y_max = 1.1 * hist_pull_z0_pion_mass->GetMaximum();
hist_pull_z0_pion_mass->GetYaxis()->SetRangeUser(0, y_max);
TLine *l_n1_z0 = new TLine(-1,0,-1,y_max); l_n1_z0->SetLineColor(1); l_n1_z0->SetLineStyle(3); l_n1_z0->SetLineWidth(1);
TLine *l_p1_z0 = new TLine(1,0,1,y_max); l_p1_z0->SetLineColor(1); l_p1_z0->SetLineStyle(3); l_p1_z0->SetLineWidth(1);
TLine *l_0_z0 = new TLine(0,0,0,y_max); l_0_z0->SetLineColor(1); l_0_z0->SetLineStyle(3); l_0_z0->SetLineWidth(1);

l_n1_z0->Draw("same");
l_p1_z0->Draw("same");
l_0_z0->Draw("same");

gPad->Update();
TPaveStats *tps_pull_z0_pion_mass = (TPaveStats*)hist_pull_z0_pion_mass->FindObject("stats");
TPaveStats *tps_pull_z0_true_mass = (TPaveStats*)hist_pull_z0_true_mass->FindObject("stats");
TPaveStats *tps_pull_z0_true_mass_Par = (TPaveStats*)hist_pull_z0_true_mass_Par->FindObject("stats");
TPaveStats *tps_pull_z0_true_mass_aPar = (TPaveStats*)hist_pull_z0_true_mass_aPar->FindObject("stats");
tps_pull_z0_pion_mass->SetTextColor(2); tps_pull_z0_pion_mass->SetLineColor(2);
tps_pull_z0_true_mass->SetTextColor(4); tps_pull_z0_true_mass->SetLineColor(4);
tps_pull_z0_true_mass_Par->SetTextColor(1); tps_pull_z0_true_mass_Par->SetLineColor(1);
tps_pull_z0_true_mass_aPar->SetTextColor(6); tps_pull_z0_true_mass_aPar->SetLineColor(6);
tps_pull_z0_pion_mass->SetX1NDC(0.72); tps_pull_z0_pion_mass->SetX2NDC(0.88); tps_pull_z0_pion_mass->SetY1NDC(0.75); tps_pull_z0_pion_mass->SetY2NDC(0.9);
X1 = tps_pull_z0_pion_mass->GetX1NDC(); X2 = tps_pull_z0_pion_mass->GetX2NDC(); Y1 = tps_pull_z0_pion_mass->GetY1NDC(); Y2 = tps_pull_z0_pion_mass->GetY2NDC();
tps_pull_z0_true_mass->SetX1NDC(X1); tps_pull_z0_true_mass->SetX2NDC(X2); tps_pull_z0_true_mass->SetY1NDC(Y1-(Y2-Y1)); tps_pull_z0_true_mass->SetY2NDC(Y1);
tps_pull_z0_true_mass_Par->SetX1NDC(1-X2+0.1); tps_pull_z0_true_mass_Par->SetX2NDC(1-X1+0.1); tps_pull_z0_true_mass_Par->SetY1NDC(Y1); tps_pull_z0_true_mass_Par->SetY2NDC(Y2);
tps_pull_z0_true_mass_aPar->SetX1NDC(1-X2+0.1); tps_pull_z0_true_mass_aPar->SetX2NDC(1-X1+0.1); tps_pull_z0_true_mass_aPar->SetY1NDC(Y1-(Y2-Y1)); tps_pull_z0_true_mass_aPar->SetY2NDC(Y1);
tps_pull_z0_pion_mass->Draw("same");
tps_pull_z0_true_mass->Draw("same");
tps_pull_z0_true_mass_Par->Draw("same");
tps_pull_z0_true_mass_aPar->Draw("same");
TLegend *leg_pull_z0=new TLegend(0.65,2 * Y1 - Y2 - 0.2,0.85,2 * Y1 - Y2);
leg_pull_z0->SetNColumns(2);
leg_pull_z0->SetTextSize(TextSize);
leg_pull_z0->SetHeader(header_par,"C");
leg_pull_z0->AddEntry("",header_moment,"");
leg_pull_z0->AddEntry("",header_wei,"");
leg_pull_z0->AddEntry("",header_r3D,"");
leg_pull_z0->AddEntry("",header_r2D,"");
leg_pull_z0->AddEntry(hist_pull_z0_pion_mass,"m_{#pi}","l");
leg_pull_z0->AddEntry(hist_pull_z0_true_mass,true_particle,"l");
leg_pull_z0->AddEntry(hist_pull_z0_true_mass_Par,particle,"l");
leg_pull_z0->AddEntry(hist_pull_z0_true_mass_aPar,anti_particle,"l");
leg_pull_z0->Draw("same");
can_pull_z0->Update();
can_pull_z0->SaveAs((plot_dir+plot_init+"_pull_z0"+momentum_stat+".pdf").c_str());
can_pull_z0->SaveAs((plot_dir+plot_init+"_pull_z0"+momentum_stat+".C").c_str());

}
