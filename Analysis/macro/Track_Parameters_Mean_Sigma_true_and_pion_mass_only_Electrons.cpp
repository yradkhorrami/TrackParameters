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

void Track_Parameters_Mean_Sigma_true_and_pion_mass_only_Electrons()
{

	gStyle->SetOptFit(1);
	ildStyle->SetOptStat(001111111);
	float leg_TextSize = 0.04;
	float leg_X1 = 0.4; float leg_Y1 = 0.60; float leg_X2 = 0.90; float leg_Y2 = 0.90;
//	LEGEND settings for all particles in addition with electrons
/*
	float d0_Mean_min = -0.5; float d0_Mean_max = 0.5; float d0_Sigma_min = 0.5; float d0_Sigma_max = 1.5;
	float Phi_Mean_min = -0.5; float Phi_Mean_max = 0.5; float Phi_Sigma_min = 0.5; float Phi_Sigma_max = 1.5;
	float Omega_Mean_min = -0.5; float Omega_Mean_max = 2; float Omega_Sigma_min = 0.8; float Omega_Sigma_max = 2;
	float tanLambda_Mean_min = -0.5; float tanLambda_Mean_max = 0.5; float tanLambda_Sigma_min = 0.5; float tanLambda_Sigma_max = 1.5;
	float z0_Mean_min = -0.5; float z0_Mean_max = 0.5; float z0_Sigma_min = 0.5; float z0_Sigma_max = 1.5;
	vector<int> mom = {1,3,5,10,15,25,50,100};
*/

//	LEGEND settings for all particles with p = 1 GeV
/*
	float d0_Mean_min = -0.2; float d0_Mean_max = 0.2; float d0_Sigma_min = 0.9; float d0_Sigma_max = 1.8;
	float Phi_Mean_min = -0.1; float Phi_Mean_max = 0.4; float Phi_Sigma_min = 0.8; float Phi_Sigma_max = 1.8;
	float Omega_Mean_min = -0.3; float Omega_Mean_max = 7.5; float Omega_Sigma_min = 1.0; float Omega_Sigma_max = 3.0;
	float tanLambda_Mean_min = -0.2; float tanLambda_Mean_max = 0.2; float tanLambda_Sigma_min = 0.8; float tanLambda_Sigma_max = 1.7;
	float z0_Mean_min = -0.3; float z0_Mean_max = 0.3; float z0_Sigma_min = 0.9; float z0_Sigma_max = 1.9;
	vector<int> mom = {1};
*/

//	LEGEND settings for Only electrons with p = 1 , 3 and 5 GeV
/*
	float d0_Mean_min = -0.2; float d0_Mean_max = 0.2; float d0_Sigma_min = 0.9; float d0_Sigma_max = 1.8;
	float Phi_Mean_min = -0.1; float Phi_Mean_max = 0.4; float Phi_Sigma_min = 0.8; float Phi_Sigma_max = 1.8;
	float Omega_Mean_min = -0.3; float Omega_Mean_max = 7.5; float Omega_Sigma_min = 1.0; float Omega_Sigma_max = 3.0;
	float tanLambda_Mean_min = -0.2; float tanLambda_Mean_max = 0.2; float tanLambda_Sigma_min = 0.8; float tanLambda_Sigma_max = 1.7;
	float z0_Mean_min = -0.3; float z0_Mean_max = 0.3; float z0_Sigma_min = 0.9; float z0_Sigma_max = 1.9;
	vector<int> mom = {1,3,5};
*/

//	LEGEND settings for all particles with p > 1 GeV

	float d0_Mean_min = 0.06; float d0_Mean_max = 0.5; float d0_Sigma_min = 1.0; float d0_Sigma_max = 1.5;
	float Phi_Mean_min = -0.4; float Phi_Mean_max = 0.2; float Phi_Sigma_min = 1.0; float Phi_Sigma_max = 1.6;
	float Omega_Mean_min = -0.20; float Omega_Mean_max = 2.3; float Omega_Sigma_min = 1.25; float Omega_Sigma_max = 2.85;
	float tanLambda_Mean_min = -0.25; float tanLambda_Mean_max = 0.35; float tanLambda_Sigma_min = 0.85; float tanLambda_Sigma_max = 1.4;
	float z0_Mean_min = -0.05; float z0_Mean_max = 0.35; float z0_Sigma_min = 0.9; float z0_Sigma_max = 1.5;
	vector<int> mom = {1,3,5,10,15};
	vector<int> color_code = {6,2,1,8,4};


	string file_dir = "/nfs/dust/ilc/user/radkhory/calib_samples/TrackerSamples/ParticleGun/FitFiles/";
	string plot_dir = "/afs/desy.de/group/flc/pool/radkhory/TrackParameters/Analysis/macro/Plots/Pulls_vs_angle_mom/Mean_Sigma/Electrons/";
	string input_tree_name = "TrackParameters";

	vector<int> angle = {15,25,35,45,55,65,75,85};
//	vector<int> angle = {15,25,35};
	vector<int> true_pdg = {11};
//	vector<int> true_pdg = {11,13};
//	vector<int> color_code = {6,2,1,8,4};
	vector<int> charge = {-1,-1,1,1,1};
	vector<int> marker_code = {34,21,20,22,23};
	vector<int> marker_code_pion = {28,25,24,26,32};
	vector<string> true_par = {"e^{-} (m_{e})","#mu^{-} (m_{#mu})","#pi^{+} (m_{#pi})","K^{+} (m_{K})","p^{+} (m_{p})"};
	vector<string> pion_par = {"e^{-} (m_{#pi})","#mu^{-} (m_{#pi})","#pi^{+} (m_{#pi})","K^{+} (m_{#pi})","p^{+} (m_{#pi})"};
	vector<string> file_init = {"Electrons","Muons","Pions","Kaons","Protons"};
	int pid = 0;

	double angles[angle.size()];

	float p_min = 0;
	float p_max = 1;

	float r_cut = 10;
	float rho_cut = 10;
	float weight_cut = 0.9;


	float fit_min = -2.;
	float fit_max = 2.;

	float residual_min = -0.05; float residual_max = 0.05;
	float uncertainty_min = 0.; float uncertainty_max = 0.05;
	float pull_min = -5.; float pull_max = 5.;
	double X1 = 0; double X2 = 0; double Y1 = 0; double Y2 = 0;
	int y_max = 0;
	float TextSize = 0.025;

	string par_pion = "#pi^{#pm}";
	string plot_init = "";

	int radi_cut = r_cut; string r3D = ("r_{3D} #leq "+to_string(radi_cut)).c_str(); char header_r3D[r3D.size() + 1]; strcpy(header_r3D, r3D.c_str());
	int _rho_cut = rho_cut; string r2D = ("r_{2D} #leq "+to_string(_rho_cut)).c_str(); char header_r2D[r2D.size() + 1]; strcpy(header_r2D, r2D.c_str());
	string wei_cut = to_string(weight_cut).substr(0,to_string(weight_cut).find(".")+2+1); string wei = ("weight #geq "+wei_cut).c_str(); char header_wei[wei.size() + 1]; strcpy(header_wei, wei.c_str());

	vector<int> *track_PDG{};
	vector<float> *momentum{};
	vector<float> *vertex_radius{};
	vector<float> *vertex_rho{};
	vector<float> *highest_weight{};

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

	vector<float> *mcp_d0{};
	vector<float> *mcp_Omega{};
	vector<float> *mcp_Phi{};
	vector<float> *mcp_z0{};
	vector<float> *mcp_tanLambda{};

	vector<float> *rec_d0_true_mass{};
	vector<float> *rec_Omega_true_mass{};
	vector<float> *rec_Phi_true_mass{};
	vector<float> *rec_z0_true_mass{};
	vector<float> *rec_tanLambda_true_mass{};

	vector<float> *rec_d0_pion_mass{};
	vector<float> *rec_Omega_pion_mass{};
	vector<float> *rec_Phi_pion_mass{};
	vector<float> *rec_z0_pion_mass{};
	vector<float> *rec_tanLambda_pion_mass{};

	double d0_pion_mass_Mean[angle.size()]; double d0_pion_mass_Mean_Err[angle.size()];
	double d0_pion_mass_Sigma[angle.size()]; double d0_pion_mass_Sigma_Err[angle.size()];
	double d0_true_mass_Mean[angle.size()]; double d0_true_mass_Mean_Err[angle.size()];
	double d0_true_mass_Sigma[angle.size()]; double d0_true_mass_Sigma_Err[angle.size()];

	double Phi_pion_mass_Mean[angle.size()]; double Phi_pion_mass_Mean_Err[angle.size()];
	double Phi_pion_mass_Sigma[angle.size()]; double Phi_pion_mass_Sigma_Err[angle.size()];
	double Phi_true_mass_Mean[angle.size()]; double Phi_true_mass_Mean_Err[angle.size()];
	double Phi_true_mass_Sigma[angle.size()]; double Phi_true_mass_Sigma_Err[angle.size()];

	double Omega_pion_mass_Mean[angle.size()]; double Omega_pion_mass_Mean_Err[angle.size()];
	double Omega_pion_mass_Sigma[angle.size()]; double Omega_pion_mass_Sigma_Err[angle.size()];
	double Omega_true_mass_Mean[angle.size()]; double Omega_true_mass_Mean_Err[angle.size()];
	double Omega_true_mass_Sigma[angle.size()]; double Omega_true_mass_Sigma_Err[angle.size()];

	double tanLambda_pion_mass_Mean[angle.size()]; double tanLambda_pion_mass_Mean_Err[angle.size()];
	double tanLambda_pion_mass_Sigma[angle.size()]; double tanLambda_pion_mass_Sigma_Err[angle.size()];
	double tanLambda_true_mass_Mean[angle.size()]; double tanLambda_true_mass_Mean_Err[angle.size()];
	double tanLambda_true_mass_Sigma[angle.size()]; double tanLambda_true_mass_Sigma_Err[angle.size()];

	double z0_pion_mass_Mean[angle.size()]; double z0_pion_mass_Mean_Err[angle.size()];
	double z0_pion_mass_Sigma[angle.size()]; double z0_pion_mass_Sigma_Err[angle.size()];
	double z0_true_mass_Mean[angle.size()]; double z0_true_mass_Mean_Err[angle.size()];
	double z0_true_mass_Sigma[angle.size()]; double z0_true_mass_Sigma_Err[angle.size()];

	TMultiGraph *multi_d0_Mean = new TMultiGraph("multi_d0_Mean",""); TLegend *legend_d0_Mean = new TLegend(leg_X1,leg_Y1,leg_X2,leg_Y2); legend_d0_Mean->SetTextSize(leg_TextSize);
	TMultiGraph *multi_d0_Sigma = new TMultiGraph("multi_d0_Sigma",""); TLegend *legend_d0_Sigma = new TLegend(leg_X1,leg_Y1,leg_X2,leg_Y2); legend_d0_Sigma->SetTextSize(leg_TextSize);
	TGraphErrors *graph_d0_Mean_true_mass[mom.size()];
	TGraphErrors *graph_d0_Sigma_true_mass[mom.size()];
	TGraphErrors *graph_d0_Mean_pion_mass[mom.size()];
	TGraphErrors *graph_d0_Sigma_pion_mass[mom.size()];
	TMultiGraph *multi_Phi_Mean = new TMultiGraph("multi_Phi_Mean",""); TLegend *legend_Phi_Mean = new TLegend(leg_X1,leg_Y1,leg_X2,leg_Y2); legend_Phi_Mean->SetTextSize(leg_TextSize);
	TMultiGraph *multi_Phi_Sigma = new TMultiGraph("multi_Phi_Sigma",""); TLegend *legend_Phi_Sigma = new TLegend(leg_X1,leg_Y1,leg_X2,leg_Y2); legend_Phi_Sigma->SetTextSize(leg_TextSize);
	TGraphErrors *graph_Phi_Mean_true_mass[mom.size()];
	TGraphErrors *graph_Phi_Sigma_true_mass[mom.size()];
	TGraphErrors *graph_Phi_Mean_pion_mass[mom.size()];
	TGraphErrors *graph_Phi_Sigma_pion_mass[mom.size()];
	TMultiGraph *multi_Omega_Mean = new TMultiGraph("multi_Omega_Mean",""); TLegend *legend_Omega_Mean = new TLegend(leg_X1,leg_Y1,leg_X2,leg_Y2); legend_Omega_Mean->SetTextSize(leg_TextSize);
	TMultiGraph *multi_Omega_Sigma = new TMultiGraph("multi_Omega_Sigma",""); TLegend *legend_Omega_Sigma = new TLegend(leg_X1,leg_Y1,leg_X2,leg_Y2); legend_Omega_Sigma->SetTextSize(leg_TextSize);
	TGraphErrors *graph_Omega_Mean_true_mass[mom.size()];
	TGraphErrors *graph_Omega_Sigma_true_mass[mom.size()];
	TGraphErrors *graph_Omega_Mean_pion_mass[mom.size()];
	TGraphErrors *graph_Omega_Sigma_pion_mass[mom.size()];
	TMultiGraph *multi_tanLambda_Mean = new TMultiGraph("multi_tanLambda_Mean",""); TLegend *legend_tanLambda_Mean = new TLegend(leg_X1,leg_Y1,leg_X2,leg_Y2); legend_tanLambda_Mean->SetTextSize(leg_TextSize);
	TMultiGraph *multi_tanLambda_Sigma = new TMultiGraph("multi_tanLambda_Sigma",""); TLegend *legend_tanLambda_Sigma = new TLegend(leg_X1,leg_Y1,leg_X2,leg_Y2); legend_tanLambda_Sigma->SetTextSize(leg_TextSize);
	TGraphErrors *graph_tanLambda_Mean_true_mass[mom.size()];
	TGraphErrors *graph_tanLambda_Sigma_true_mass[mom.size()];
	TGraphErrors *graph_tanLambda_Mean_pion_mass[mom.size()];
	TGraphErrors *graph_tanLambda_Sigma_pion_mass[mom.size()];
	TMultiGraph *multi_z0_Mean = new TMultiGraph("multi_z0_Mean",""); TLegend *legend_z0_Mean = new TLegend(leg_X1,leg_Y1,leg_X2,leg_Y2); legend_z0_Mean->SetTextSize(leg_TextSize);
	TMultiGraph *multi_z0_Sigma = new TMultiGraph("multi_z0_Sigma",""); TLegend *legend_z0_Sigma = new TLegend(leg_X1,leg_Y1,leg_X2,leg_Y2); legend_z0_Sigma->SetTextSize(leg_TextSize);
	TGraphErrors *graph_z0_Mean_true_mass[mom.size()];
	TGraphErrors *graph_z0_Sigma_true_mass[mom.size()];
	TGraphErrors *graph_z0_Mean_pion_mass[mom.size()];
	TGraphErrors *graph_z0_Sigma_pion_mass[mom.size()];

		string head_d0_Mean = "#mu (d0 pull)";
		char header_d0_Mean[head_d0_Mean.size() + 1];
		strcpy(header_d0_Mean, head_d0_Mean.c_str());
		string head_d0_Sigma = "#sigma (d0 pull)";
		char header_d0_Sigma[head_d0_Sigma.size() + 1];
		strcpy(header_d0_Sigma, head_d0_Sigma.c_str());

		string head_Phi_Mean = "#mu (#Phi pull)";
		char header_Phi_Mean[head_Phi_Mean.size() + 1];
		strcpy(header_Phi_Mean, head_Phi_Mean.c_str());
		string head_Phi_Sigma = "#sigma (#Phi pull)";
		char header_Phi_Sigma[head_Phi_Sigma.size() + 1];
		strcpy(header_Phi_Sigma, head_Phi_Sigma.c_str());

		string head_Omega_Mean = "#mu (#Omega pull)";
		char header_Omega_Mean[head_Omega_Mean.size() + 1];
		strcpy(header_Omega_Mean, head_Omega_Mean.c_str());
		string head_Omega_Sigma = "#sigma (#Omega pull)";
		char header_Omega_Sigma[head_Omega_Sigma.size() + 1];
		strcpy(header_Omega_Sigma, head_Omega_Sigma.c_str());

		string head_tanLambda_Mean = "#mu (tan #lambda pull)";
		char header_tanLambda_Mean[head_tanLambda_Mean.size() + 1];
		strcpy(header_tanLambda_Mean, head_tanLambda_Mean.c_str());
		string head_tanLambda_Sigma = "#sigma (tan #lambda pull)";
		char header_tanLambda_Sigma[head_tanLambda_Sigma.size() + 1];
		strcpy(header_tanLambda_Sigma, head_tanLambda_Sigma.c_str());

		string head_z0_Mean = "#mu (z0 pull)";
		char header_z0_Mean[head_z0_Mean.size() + 1];
		strcpy(header_z0_Mean, head_z0_Mean.c_str());
		string head_z0_Sigma = "#sigma (z0 pull)";
		char header_z0_Sigma[head_z0_Sigma.size() + 1];
		strcpy(header_z0_Sigma, head_z0_Sigma.c_str());

	for (int mom_iter = 0; mom_iter < mom.size(); mom_iter++)
	{
			string true_part = (true_par[0]+" "+to_string(mom[mom_iter])+" GeV").c_str();
			char true_particle[true_part.size() + 1];
			strcpy(true_particle, true_part.c_str());

			string pion_part = (pion_par[0]+" "+to_string(mom[mom_iter])+" GeV").c_str();
			char pion_particle[pion_part.size() + 1];
			strcpy(pion_particle, pion_part.c_str());


		for (int par_iter = 0; par_iter < true_pdg.size(); par_iter++)
		{
			TGraphErrors *currentGraph_Mean = 0;
			TGraphErrors *currentGraph_Sigma = 0;
			for (int angle_iter = 0; angle_iter < angle.size(); angle_iter++)
			{
				angles[angle_iter] = angle[angle_iter];
				char particle_type[true_par[par_iter].size() + 1]; ; strcpy(particle_type, true_par[par_iter].c_str());
				std::vector<TObject*> deletionPool;

				TFile *file =  TFile::Open((file_dir + file_init[par_iter] + "_Angle_" + to_string(angle[angle_iter]) + "_Mom_" + to_string(mom[mom_iter]) + "_Refit_TrackParameters.root").c_str(), "READONLY");
				TTree *tree = (TTree*)file->Get(input_tree_name.c_str());
				int nEntries = tree->GetEntries();

				string type = ("True " + file_init[par_iter] + " , #theta = " + to_string(angle[angle_iter]) + "^{o} , p = " + to_string(mom[mom_iter]) + " GeV").c_str();
				char header_par[type.size() + 1];
				strcpy(header_par, type.c_str());

				TH1* hist_pull_d0_pion_mass = new TH1F("hist_pull_d0_pion_mass", "; d_{0} Pull; # tracks" , 200,2*pull_min,2*pull_max);
				hist_pull_d0_pion_mass->SetLineColor(2); hist_pull_d0_pion_mass->SetLineWidth(1);
				deletionPool.push_back(hist_pull_d0_pion_mass);
				TH1* hist_pull_d0_true_mass = new TH1F("hist_pull_d0_true_mass", "; d_{0} Pull; # tracks" , 200,2*pull_min,2*pull_max);
				hist_pull_d0_true_mass->SetLineColor(4); hist_pull_d0_true_mass->SetLineWidth(1);
				deletionPool.push_back(hist_pull_d0_true_mass);

				TH1* hist_pull_Omega_pion_mass = new TH1F("hist_pull_Omega_pion_mass", "; Omega pull; # tracks" , 200,2*pull_min,2*pull_max);
				hist_pull_Omega_pion_mass->SetLineColor(2); hist_pull_Omega_pion_mass->SetLineWidth(1);
				deletionPool.push_back(hist_pull_Omega_pion_mass);
				TH1* hist_pull_Omega_true_mass = new TH1F("hist_pull_Omega_true_mass", "; Omega pull; # tracks" , 200,2*pull_min,2*pull_max);
				hist_pull_Omega_true_mass->SetLineColor(4); hist_pull_Omega_true_mass->SetLineWidth(1);
				deletionPool.push_back(hist_pull_Omega_true_mass);

				TH1* hist_pull_Phi_pion_mass = new TH1F("hist_pull_Phi_pion_mass", "; Phi pull; # tracks" , 200,2*pull_min,2*pull_max);
				hist_pull_Phi_pion_mass->SetLineColor(2); hist_pull_Phi_pion_mass->SetLineWidth(1);
				deletionPool.push_back(hist_pull_Phi_pion_mass);
				TH1* hist_pull_Phi_true_mass = new TH1F("hist_pull_Phi_true_mass", "; Phi pull; # tracks" , 200,2*pull_min,2*pull_max);
				hist_pull_Phi_true_mass->SetLineColor(4); hist_pull_Phi_true_mass->SetLineWidth(1);
				deletionPool.push_back(hist_pull_Phi_true_mass);

				TH1* hist_pull_tanLambda_pion_mass = new TH1F("hist_pull_tanLambda_pion_mass", "; tanLambda pull; # tracks" , 200,2*pull_min,2*pull_max);
				hist_pull_tanLambda_pion_mass->SetLineColor(2); hist_pull_tanLambda_pion_mass->SetLineWidth(1);
				deletionPool.push_back(hist_pull_tanLambda_pion_mass);
				TH1* hist_pull_tanLambda_true_mass = new TH1F("hist_pull_tanLambda_true_mass", "; tanLambda pull; # tracks" , 200,2*pull_min,2*pull_max);
				hist_pull_tanLambda_true_mass->SetLineColor(4); hist_pull_tanLambda_true_mass->SetLineWidth(1);
				deletionPool.push_back(hist_pull_tanLambda_true_mass);

				TH1* hist_pull_z0_pion_mass = new TH1F("hist_pull_z0_pion_mass", "; z_{0} Pull; # tracks" , 200,2*pull_min,2*pull_max);
				hist_pull_z0_pion_mass->SetLineColor(2); hist_pull_z0_pion_mass->SetLineWidth(1);
				deletionPool.push_back(hist_pull_z0_pion_mass);
				TH1* hist_pull_z0_true_mass = new TH1F("hist_pull_z0_true_mass", "; z_{0} Pull; # tracks" , 200,2*pull_min,2*pull_max);
				hist_pull_z0_true_mass->SetLineColor(4); hist_pull_z0_true_mass->SetLineWidth(1);
				deletionPool.push_back(hist_pull_z0_true_mass);

				tree->SetBranchAddress("track_PDG",&track_PDG);
				tree->SetBranchAddress("mcp_momentum",&momentum);
				tree->SetBranchAddress("vertex_radius",&vertex_radius);
				tree->SetBranchAddress("vertex_rho",&vertex_rho);
				tree->SetBranchAddress("highest_weight",&highest_weight);

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

				/*
				tree->SetBranchAddress("mcp_d0",&mcp_d0);
				tree->SetBranchAddress("mcp_Omega",&mcp_Omega);
				tree->SetBranchAddress("mcp_Phi",&mcp_Phi);
				tree->SetBranchAddress("mcp_z0",&mcp_z0);
				tree->SetBranchAddress("mcp_tanLambda",&mcp_tanLambda);

				tree->SetBranchAddress("rec_d0_true_mass",&rec_d0_true_mass);
				tree->SetBranchAddress("rec_Omega_true_mass",&rec_Omega_true_mass);
				tree->SetBranchAddress("rec_Phi_true_mass",&rec_Phi_true_mass);
				tree->SetBranchAddress("rec_z0_true_mass",&rec_z0_true_mass);
				tree->SetBranchAddress("rec_tanLambda_true_mass",&rec_tanLambda_true_mass);

				tree->SetBranchAddress("rec_d0_pion_mass",&rec_d0_pion_mass);
				tree->SetBranchAddress("rec_Omega_pion_mass",&rec_Omega_pion_mass);
				tree->SetBranchAddress("rec_Phi_pion_mass",&rec_Phi_pion_mass);
				tree->SetBranchAddress("rec_z0_pion_mass",&rec_z0_pion_mass);
				tree->SetBranchAddress("rec_tanLambda_pion_mass",&rec_tanLambda_pion_mass);
				*/

				for (int i = 0; i < nEntries; i++)
				{
					tree->GetEntry(i);
					for (int track_i = 0; track_i < (track_PDG->size()); track_i++)
					{
//						if ((vertex_radius->at(track_i) >= r_cut) || (vertex_rho->at(track_i) >= rho_cut) || (highest_weight->at(track_i) < weight_cut) || abs(track_PDG->at(track_i)) != true_pdg)
//							continue;

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
					}
				}

				TCanvas *can_pull_d0 = new TCanvas("can_pull_d0", "", 1600,1200); deletionPool.push_back(can_pull_d0);
				hist_pull_d0_true_mass->Draw(); fit_min=hist_pull_d0_true_mass->GetMean()-2; fit_max=hist_pull_d0_true_mass->GetMean()+2;
				hist_pull_d0_true_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_d0_true_mass->GetFunction("gaus")->SetLineColor(4); hist_pull_d0_true_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_d0_true_mass->GetFunction("gaus")->SetLineWidth(1);
				TF1 *func_pull_d0_true_mass = (TF1*)hist_pull_d0_true_mass->GetListOfFunctions()->FindObject("gaus");
				hist_pull_d0_pion_mass->Draw("sames"); fit_min=hist_pull_d0_pion_mass->GetMean()-2; fit_max=hist_pull_d0_pion_mass->GetMean()+2;
				hist_pull_d0_pion_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_d0_pion_mass->GetFunction("gaus")->SetLineColor(2); hist_pull_d0_pion_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_d0_pion_mass->GetFunction("gaus")->SetLineWidth(1);
				d0_true_mass_Mean[angle_iter] = hist_pull_d0_true_mass->GetFunction("gaus")->GetParameter(1); d0_true_mass_Mean_Err[angle_iter] = hist_pull_d0_true_mass->GetFunction("gaus")->GetParError(1);
				d0_true_mass_Sigma[angle_iter] = hist_pull_d0_true_mass->GetFunction("gaus")->GetParameter(2); d0_true_mass_Sigma_Err[angle_iter] = hist_pull_d0_true_mass->GetFunction("gaus")->GetParError(2);
				d0_pion_mass_Mean[angle_iter] = hist_pull_d0_pion_mass->GetFunction("gaus")->GetParameter(1); d0_pion_mass_Mean_Err[angle_iter] = hist_pull_d0_pion_mass->GetFunction("gaus")->GetParError(1);
				d0_pion_mass_Sigma[angle_iter] = hist_pull_d0_pion_mass->GetFunction("gaus")->GetParameter(2); d0_pion_mass_Sigma_Err[angle_iter] = hist_pull_d0_pion_mass->GetFunction("gaus")->GetParError(2);
				y_max = 1.2 * hist_pull_d0_true_mass->GetMaximum();
				hist_pull_d0_true_mass->GetYaxis()->SetRangeUser(0, y_max);
				TLine *l_n1_d0 = new TLine(-1,0,-1,y_max); l_n1_d0->SetLineColor(1); l_n1_d0->SetLineStyle(3); l_n1_d0->SetLineWidth(1); deletionPool.push_back(l_n1_d0);
				TLine *l_p1_d0 = new TLine(1,0,1,y_max); l_p1_d0->SetLineColor(1); l_p1_d0->SetLineStyle(3); l_p1_d0->SetLineWidth(1); deletionPool.push_back(l_p1_d0);
				TLine *l_0_d0 = new TLine(0,0,0,y_max); l_0_d0->SetLineColor(1); l_0_d0->SetLineStyle(3); l_0_d0->SetLineWidth(1); deletionPool.push_back(l_0_d0);

				l_n1_d0->Draw("same");
				l_p1_d0->Draw("same");
				l_0_d0->Draw("same");

				hist_pull_d0_true_mass->GetXaxis()->SetRangeUser(pull_min,pull_max);

				gPad->Update();
				TPaveStats *tps_pull_d0_pion_mass = (TPaveStats*)hist_pull_d0_pion_mass->FindObject("stats");
				TPaveStats *tps_pull_d0_true_mass = (TPaveStats*)hist_pull_d0_true_mass->FindObject("stats");
				tps_pull_d0_pion_mass->SetTextColor(2); tps_pull_d0_pion_mass->SetLineColor(2);
				tps_pull_d0_true_mass->SetTextColor(4); tps_pull_d0_true_mass->SetLineColor(4);
				tps_pull_d0_pion_mass->SetX1NDC(0.72); tps_pull_d0_pion_mass->SetX2NDC(0.88); tps_pull_d0_pion_mass->SetY1NDC(0.70); tps_pull_d0_pion_mass->SetY2NDC(0.9);
				X1 = tps_pull_d0_pion_mass->GetX1NDC(); X2 = tps_pull_d0_pion_mass->GetX2NDC(); Y1 = tps_pull_d0_pion_mass->GetY1NDC(); Y2 = tps_pull_d0_pion_mass->GetY2NDC();
				tps_pull_d0_true_mass->SetX1NDC(1-X2+0.1); tps_pull_d0_true_mass->SetX2NDC(1-X1+0.1); tps_pull_d0_true_mass->SetY1NDC(Y1); tps_pull_d0_true_mass->SetY2NDC(Y2);
				tps_pull_d0_pion_mass->Draw("same");
				tps_pull_d0_true_mass->Draw("same");
				TLegend *leg_pull_d0=new TLegend(X1 , 2 * Y1 - Y2 , X2 , Y1);  deletionPool.push_back(leg_pull_d0);
				leg_pull_d0->SetTextSize(TextSize);
				leg_pull_d0->SetNColumns(2);
				leg_pull_d0->SetHeader(header_par,"C");
				leg_pull_d0->AddEntry("",header_r3D,"");
				leg_pull_d0->AddEntry("",header_r2D,"");
				leg_pull_d0->AddEntry(hist_pull_d0_pion_mass,"#pi","l");
				leg_pull_d0->AddEntry(hist_pull_d0_true_mass,particle_type,"l");
				leg_pull_d0->Draw("same");
				can_pull_d0->Update();
				can_pull_d0->SaveAs((plot_dir+"Pulls/"+file_init[par_iter]+"_pull_d0_mom_"+to_string(mom[mom_iter])+"_Angle_"+to_string(angle[angle_iter])+".pdf").c_str());
//				can_pull_d0->SaveAs((plot_dir+"Pulls/"+file_init[par_iter]+"_pull_d0_mom_"+to_string(mom[mom_iter])+"_Angle_"+to_string(angle[angle_iter])+".C").c_str());

				TCanvas *can_pull_Phi = new TCanvas("can_pull_Phi", "", 1600,1200);  deletionPool.push_back(can_pull_Phi);
				hist_pull_Phi_true_mass->Draw(); fit_min=hist_pull_Phi_true_mass->GetMean()-2; fit_max=hist_pull_Phi_true_mass->GetMean()+2;
				hist_pull_Phi_true_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_Phi_true_mass->GetFunction("gaus")->SetLineColor(4); hist_pull_Phi_true_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_Phi_true_mass->GetFunction("gaus")->SetLineWidth(1);
				hist_pull_Phi_pion_mass->Draw("sames"); fit_min=hist_pull_Phi_pion_mass->GetMean()-2; fit_max=hist_pull_Phi_pion_mass->GetMean()+2;
				hist_pull_Phi_pion_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_Phi_pion_mass->GetFunction("gaus")->SetLineColor(2); hist_pull_Phi_pion_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_Phi_pion_mass->GetFunction("gaus")->SetLineWidth(1);
				Phi_true_mass_Mean[angle_iter] = hist_pull_Phi_true_mass->GetFunction("gaus")->GetParameter(1); Phi_true_mass_Mean_Err[angle_iter] = hist_pull_Phi_true_mass->GetFunction("gaus")->GetParError(1);
				Phi_true_mass_Sigma[angle_iter] = hist_pull_Phi_true_mass->GetFunction("gaus")->GetParameter(2); Phi_true_mass_Sigma_Err[angle_iter] = hist_pull_Phi_true_mass->GetFunction("gaus")->GetParError(2);
				Phi_pion_mass_Mean[angle_iter] = hist_pull_Phi_pion_mass->GetFunction("gaus")->GetParameter(1); Phi_pion_mass_Mean_Err[angle_iter] = hist_pull_Phi_pion_mass->GetFunction("gaus")->GetParError(1);
				Phi_pion_mass_Sigma[angle_iter] = hist_pull_Phi_pion_mass->GetFunction("gaus")->GetParameter(2); Phi_pion_mass_Sigma_Err[angle_iter] = hist_pull_Phi_pion_mass->GetFunction("gaus")->GetParError(2);
				y_max = 1.2 * hist_pull_Phi_true_mass->GetMaximum();
				hist_pull_Phi_true_mass->GetYaxis()->SetRangeUser(0, y_max);
				TLine *l_n1_Phi = new TLine(-1,0,-1,y_max); l_n1_Phi->SetLineColor(1); l_n1_Phi->SetLineStyle(3); l_n1_Phi->SetLineWidth(1);  deletionPool.push_back(l_n1_Phi);
				TLine *l_p1_Phi = new TLine(1,0,1,y_max); l_p1_Phi->SetLineColor(1); l_p1_Phi->SetLineStyle(3); l_p1_Phi->SetLineWidth(1);  deletionPool.push_back(l_p1_Phi);
				TLine *l_0_Phi = new TLine(0,0,0,y_max); l_0_Phi->SetLineColor(1); l_0_Phi->SetLineStyle(3); l_0_Phi->SetLineWidth(1);  deletionPool.push_back(l_0_Phi);

				l_n1_Phi->Draw("same");
				l_p1_Phi->Draw("same");
				l_0_Phi->Draw("same");

				hist_pull_Phi_true_mass->GetXaxis()->SetRangeUser(pull_min,pull_max);

				gPad->Update();
				TPaveStats *tps_pull_Phi_pion_mass = (TPaveStats*)hist_pull_Phi_pion_mass->FindObject("stats");
				TPaveStats *tps_pull_Phi_true_mass = (TPaveStats*)hist_pull_Phi_true_mass->FindObject("stats");
				tps_pull_Phi_pion_mass->SetTextColor(2); tps_pull_Phi_pion_mass->SetLineColor(2);
				tps_pull_Phi_true_mass->SetTextColor(4); tps_pull_Phi_true_mass->SetLineColor(4);
				tps_pull_Phi_pion_mass->SetX1NDC(0.72); tps_pull_Phi_pion_mass->SetX2NDC(0.88); tps_pull_Phi_pion_mass->SetY1NDC(0.70); tps_pull_Phi_pion_mass->SetY2NDC(0.9);
				X1 = tps_pull_Phi_pion_mass->GetX1NDC(); X2 = tps_pull_Phi_pion_mass->GetX2NDC(); Y1 = tps_pull_Phi_pion_mass->GetY1NDC(); Y2 = tps_pull_Phi_pion_mass->GetY2NDC();
				tps_pull_Phi_true_mass->SetX1NDC(1-X2+0.1); tps_pull_Phi_true_mass->SetX2NDC(1-X1+0.1); tps_pull_Phi_true_mass->SetY1NDC(Y1); tps_pull_Phi_true_mass->SetY2NDC(Y2);
				tps_pull_Phi_pion_mass->Draw("same");
				tps_pull_Phi_true_mass->Draw("same");
				TLegend *leg_pull_Phi=new TLegend(X1 , 2 * Y1 - Y2 , X2 , Y1);  deletionPool.push_back(leg_pull_Phi);
				leg_pull_Phi->SetTextSize(TextSize);
				leg_pull_Phi->SetNColumns(2);
				leg_pull_Phi->SetHeader(header_par,"C");
				leg_pull_Phi->AddEntry("",header_r3D,"");
				leg_pull_Phi->AddEntry("",header_r2D,"");
				leg_pull_Phi->AddEntry(hist_pull_Phi_pion_mass,"#pi","l");
				leg_pull_Phi->AddEntry(hist_pull_Phi_true_mass,particle_type,"l");
				leg_pull_Phi->Draw("same");
				can_pull_Phi->Update();
				can_pull_Phi->SaveAs((plot_dir+"Pulls/"+file_init[par_iter]+"_pull_Phi_mom_"+to_string(mom[mom_iter])+"_Angle_"+to_string(angle[angle_iter])+".pdf").c_str());
//				can_pull_Phi->SaveAs((plot_dir+"Pulls/"+file_init[par_iter]+"_pull_Phi_mom_"+to_string(mom[mom_iter])+"_Angle_"+to_string(angle[angle_iter])+".C").c_str());

				TCanvas *can_pull_Omega = new TCanvas("can_pull_Omega", "", 1600,1200);  deletionPool.push_back(can_pull_Omega);
				hist_pull_Omega_true_mass->Draw(); fit_min=hist_pull_Omega_true_mass->GetMean()-2; fit_max=hist_pull_Omega_true_mass->GetMean()+2;
				hist_pull_Omega_true_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_Omega_true_mass->GetFunction("gaus")->SetLineColor(4); hist_pull_Omega_true_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_Omega_true_mass->GetFunction("gaus")->SetLineWidth(1);
				hist_pull_Omega_pion_mass->Draw("sames"); fit_min=hist_pull_Omega_pion_mass->GetMean()-2; fit_max=hist_pull_Omega_pion_mass->GetMean()+2;
				hist_pull_Omega_pion_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_Omega_pion_mass->GetFunction("gaus")->SetLineColor(2); hist_pull_Omega_pion_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_Omega_pion_mass->GetFunction("gaus")->SetLineWidth(1);
				Omega_true_mass_Mean[angle_iter] = charge[par_iter] * hist_pull_Omega_true_mass->GetFunction("gaus")->GetParameter(1); Omega_true_mass_Mean_Err[angle_iter] = hist_pull_Omega_true_mass->GetFunction("gaus")->GetParError(1);
				Omega_true_mass_Sigma[angle_iter] = hist_pull_Omega_true_mass->GetFunction("gaus")->GetParameter(2); Omega_true_mass_Sigma_Err[angle_iter] = hist_pull_Omega_true_mass->GetFunction("gaus")->GetParError(2);
				Omega_pion_mass_Mean[angle_iter] = charge[par_iter] * hist_pull_Omega_pion_mass->GetFunction("gaus")->GetParameter(1); Omega_pion_mass_Mean_Err[angle_iter] = hist_pull_Omega_pion_mass->GetFunction("gaus")->GetParError(1);
				Omega_pion_mass_Sigma[angle_iter] = hist_pull_Omega_pion_mass->GetFunction("gaus")->GetParameter(2); Omega_pion_mass_Sigma_Err[angle_iter] = hist_pull_Omega_pion_mass->GetFunction("gaus")->GetParError(2);
				y_max = 1.2 * hist_pull_Omega_true_mass->GetMaximum();
				hist_pull_Omega_true_mass->GetYaxis()->SetRangeUser(0, y_max);
				TLine *l_n1_Omega = new TLine(-1,0,-1,y_max); l_n1_Omega->SetLineColor(1); l_n1_Omega->SetLineStyle(3); l_n1_Omega->SetLineWidth(1);  deletionPool.push_back(l_n1_Omega);
				TLine *l_p1_Omega = new TLine(1,0,1,y_max); l_p1_Omega->SetLineColor(1); l_p1_Omega->SetLineStyle(3); l_p1_Omega->SetLineWidth(1);  deletionPool.push_back(l_p1_Omega);
				TLine *l_0_Omega = new TLine(0,0,0,y_max); l_0_Omega->SetLineColor(1); l_0_Omega->SetLineStyle(3); l_0_Omega->SetLineWidth(1);  deletionPool.push_back(l_0_Omega);

				l_n1_Omega->Draw("same");
				l_p1_Omega->Draw("same");
				l_0_Omega->Draw("same");

				hist_pull_Omega_true_mass->GetXaxis()->SetRangeUser(pull_min,pull_max);

				gPad->Update();
				TPaveStats *tps_pull_Omega_pion_mass = (TPaveStats*)hist_pull_Omega_pion_mass->FindObject("stats");
				TPaveStats *tps_pull_Omega_true_mass = (TPaveStats*)hist_pull_Omega_true_mass->FindObject("stats");
				tps_pull_Omega_pion_mass->SetTextColor(2); tps_pull_Omega_pion_mass->SetLineColor(2);
				tps_pull_Omega_true_mass->SetTextColor(4); tps_pull_Omega_true_mass->SetLineColor(4);
				tps_pull_Omega_pion_mass->SetX1NDC(0.72); tps_pull_Omega_pion_mass->SetX2NDC(0.88); tps_pull_Omega_pion_mass->SetY1NDC(0.70); tps_pull_Omega_pion_mass->SetY2NDC(0.9);
				X1 = tps_pull_Omega_pion_mass->GetX1NDC(); X2 = tps_pull_Omega_pion_mass->GetX2NDC(); Y1 = tps_pull_Omega_pion_mass->GetY1NDC(); Y2 = tps_pull_Omega_pion_mass->GetY2NDC();
				tps_pull_Omega_true_mass->SetX1NDC(1-X2+0.1); tps_pull_Omega_true_mass->SetX2NDC(1-X1+0.1); tps_pull_Omega_true_mass->SetY1NDC(Y1); tps_pull_Omega_true_mass->SetY2NDC(Y2);
				tps_pull_Omega_pion_mass->Draw("same");
				tps_pull_Omega_true_mass->Draw("same");
				TLegend *leg_pull_Omega=new TLegend(X1 , 2 * Y1 - Y2 , X2 , Y1); deletionPool.push_back(leg_pull_Omega);
				leg_pull_Omega->SetTextSize(TextSize);
				leg_pull_Omega->SetNColumns(2);
				leg_pull_Omega->SetHeader(header_par,"C");
				leg_pull_Omega->AddEntry("",header_r3D,"");
				leg_pull_Omega->AddEntry("",header_r2D,"");
				leg_pull_Omega->AddEntry(hist_pull_Omega_pion_mass,"#pi","l");
				leg_pull_Omega->AddEntry(hist_pull_Omega_true_mass,particle_type,"l");
				leg_pull_Omega->Draw("same");
				can_pull_Omega->Update();
				can_pull_Omega->SaveAs((plot_dir+"Pulls/"+file_init[par_iter]+"_pull_Omega_mom_"+to_string(mom[mom_iter])+"_Angle_"+to_string(angle[angle_iter])+".pdf").c_str());
//				can_pull_Omega->SaveAs((plot_dir+"Pulls/"+file_init[par_iter]+"_pull_Omega_mom_"+to_string(mom[mom_iter])+"_Angle_"+to_string(angle[angle_iter])+".C").c_str());

				TCanvas *can_pull_tanLambda = new TCanvas("can_pull_tanLambda", "", 1600,1200); deletionPool.push_back(can_pull_tanLambda);
				hist_pull_tanLambda_true_mass->Draw(); fit_min=hist_pull_tanLambda_true_mass->GetMean()-2; fit_max=hist_pull_tanLambda_true_mass->GetMean()+2;
				hist_pull_tanLambda_true_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_tanLambda_true_mass->GetFunction("gaus")->SetLineColor(4); hist_pull_tanLambda_true_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_tanLambda_true_mass->GetFunction("gaus")->SetLineWidth(1);
				hist_pull_tanLambda_pion_mass->Draw("sames"); fit_min=hist_pull_tanLambda_pion_mass->GetMean()-2; fit_max=hist_pull_tanLambda_pion_mass->GetMean()+2;
				hist_pull_tanLambda_pion_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_tanLambda_pion_mass->GetFunction("gaus")->SetLineColor(2); hist_pull_tanLambda_pion_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_tanLambda_pion_mass->GetFunction("gaus")->SetLineWidth(1);
				tanLambda_true_mass_Mean[angle_iter] = hist_pull_tanLambda_true_mass->GetFunction("gaus")->GetParameter(1); tanLambda_true_mass_Mean_Err[angle_iter] = hist_pull_tanLambda_true_mass->GetFunction("gaus")->GetParError(1);
				tanLambda_true_mass_Sigma[angle_iter] = hist_pull_tanLambda_true_mass->GetFunction("gaus")->GetParameter(2); tanLambda_true_mass_Sigma_Err[angle_iter] = hist_pull_tanLambda_true_mass->GetFunction("gaus")->GetParError(2);
				tanLambda_pion_mass_Mean[angle_iter] = hist_pull_tanLambda_pion_mass->GetFunction("gaus")->GetParameter(1); tanLambda_pion_mass_Mean_Err[angle_iter] = hist_pull_tanLambda_pion_mass->GetFunction("gaus")->GetParError(1);
				tanLambda_pion_mass_Sigma[angle_iter] = hist_pull_tanLambda_pion_mass->GetFunction("gaus")->GetParameter(2); tanLambda_pion_mass_Sigma_Err[angle_iter] = hist_pull_tanLambda_pion_mass->GetFunction("gaus")->GetParError(2);
				y_max = 1.2 * hist_pull_tanLambda_true_mass->GetMaximum();
				hist_pull_tanLambda_true_mass->GetYaxis()->SetRangeUser(0, y_max);
				TLine *l_n1_tanLambda = new TLine(-1,0,-1,y_max); l_n1_tanLambda->SetLineColor(1); l_n1_tanLambda->SetLineStyle(3); l_n1_tanLambda->SetLineWidth(1); deletionPool.push_back(l_n1_tanLambda);
				TLine *l_p1_tanLambda = new TLine(1,0,1,y_max); l_p1_tanLambda->SetLineColor(1); l_p1_tanLambda->SetLineStyle(3); l_p1_tanLambda->SetLineWidth(1); deletionPool.push_back(l_p1_tanLambda);
				TLine *l_0_tanLambda = new TLine(0,0,0,y_max); l_0_tanLambda->SetLineColor(1); l_0_tanLambda->SetLineStyle(3); l_0_tanLambda->SetLineWidth(1); deletionPool.push_back(l_0_tanLambda);

				l_n1_tanLambda->Draw("same");
				l_p1_tanLambda->Draw("same");
				l_0_tanLambda->Draw("same");

				hist_pull_tanLambda_true_mass->GetXaxis()->SetRangeUser(pull_min,pull_max);

				gPad->Update();
				TPaveStats *tps_pull_tanLambda_pion_mass = (TPaveStats*)hist_pull_tanLambda_pion_mass->FindObject("stats");
				TPaveStats *tps_pull_tanLambda_true_mass = (TPaveStats*)hist_pull_tanLambda_true_mass->FindObject("stats");
				tps_pull_tanLambda_pion_mass->SetTextColor(2); tps_pull_tanLambda_pion_mass->SetLineColor(2);
				tps_pull_tanLambda_true_mass->SetTextColor(4); tps_pull_tanLambda_true_mass->SetLineColor(4);
				tps_pull_tanLambda_pion_mass->SetX1NDC(0.72); tps_pull_tanLambda_pion_mass->SetX2NDC(0.88); tps_pull_tanLambda_pion_mass->SetY1NDC(0.70); tps_pull_tanLambda_pion_mass->SetY2NDC(0.9);
				X1 = tps_pull_tanLambda_pion_mass->GetX1NDC(); X2 = tps_pull_tanLambda_pion_mass->GetX2NDC(); Y1 = tps_pull_tanLambda_pion_mass->GetY1NDC(); Y2 = tps_pull_tanLambda_pion_mass->GetY2NDC();
				tps_pull_tanLambda_true_mass->SetX1NDC(1-X2+0.1); tps_pull_tanLambda_true_mass->SetX2NDC(1-X1+0.1); tps_pull_tanLambda_true_mass->SetY1NDC(Y1); tps_pull_tanLambda_true_mass->SetY2NDC(Y2);
				tps_pull_tanLambda_pion_mass->Draw("same");
				tps_pull_tanLambda_true_mass->Draw("same");
				TLegend *leg_pull_tanLambda=new TLegend(X1 , 2 * Y1 - Y2 , X2 , Y1); deletionPool.push_back(leg_pull_tanLambda);
				leg_pull_tanLambda->SetTextSize(TextSize);
				leg_pull_tanLambda->SetNColumns(2);
				leg_pull_tanLambda->SetHeader(header_par,"C");
				leg_pull_tanLambda->AddEntry("",header_r3D,"");
				leg_pull_tanLambda->AddEntry("",header_r2D,"");
				leg_pull_tanLambda->AddEntry(hist_pull_tanLambda_pion_mass,"#pi","l");
				leg_pull_tanLambda->AddEntry(hist_pull_tanLambda_true_mass,particle_type,"l");
				leg_pull_tanLambda->Draw("same");
				can_pull_tanLambda->Update();
				can_pull_tanLambda->SaveAs((plot_dir+"Pulls/"+file_init[par_iter]+"_pull_tanLambda_mom_"+to_string(mom[mom_iter])+"_Angle_"+to_string(angle[angle_iter])+".pdf").c_str());
//				can_pull_tanLambda->SaveAs((plot_dir+"Pulls/"+file_init[par_iter]+"_pull_tanLambda_mom_"+to_string(mom[mom_iter])+"_Angle_"+to_string(angle[angle_iter])+".C").c_str());

				TCanvas *can_pull_z0 = new TCanvas("can_pull_z0", "", 1600,1200); deletionPool.push_back(can_pull_z0);
				hist_pull_z0_true_mass->Draw(); fit_min=hist_pull_z0_true_mass->GetMean()-2; fit_max=hist_pull_z0_true_mass->GetMean()+2;
				hist_pull_z0_true_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_z0_true_mass->GetFunction("gaus")->SetLineColor(4); hist_pull_z0_true_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_z0_true_mass->GetFunction("gaus")->SetLineWidth(1);
				hist_pull_z0_pion_mass->Draw("sames"); fit_min=hist_pull_z0_pion_mass->GetMean()-2; fit_max=hist_pull_z0_pion_mass->GetMean()+2;
				hist_pull_z0_pion_mass->Fit("gaus","","",fit_min,fit_max); hist_pull_z0_pion_mass->GetFunction("gaus")->SetLineColor(2); hist_pull_z0_pion_mass->GetFunction("gaus")->SetLineStyle(2); hist_pull_z0_pion_mass->GetFunction("gaus")->SetLineWidth(1);
				z0_true_mass_Mean[angle_iter] = hist_pull_z0_true_mass->GetFunction("gaus")->GetParameter(1); z0_true_mass_Mean_Err[angle_iter] = hist_pull_z0_true_mass->GetFunction("gaus")->GetParError(1);
				z0_true_mass_Sigma[angle_iter] = hist_pull_z0_true_mass->GetFunction("gaus")->GetParameter(2); z0_true_mass_Sigma_Err[angle_iter] = hist_pull_z0_true_mass->GetFunction("gaus")->GetParError(2);
				z0_pion_mass_Mean[angle_iter] = hist_pull_z0_pion_mass->GetFunction("gaus")->GetParameter(1); z0_pion_mass_Mean_Err[angle_iter] = hist_pull_z0_pion_mass->GetFunction("gaus")->GetParError(1);
				z0_pion_mass_Sigma[angle_iter] = hist_pull_z0_pion_mass->GetFunction("gaus")->GetParameter(2); z0_pion_mass_Sigma_Err[angle_iter] = hist_pull_z0_pion_mass->GetFunction("gaus")->GetParError(2);
				y_max = 1.2 * hist_pull_z0_true_mass->GetMaximum();
				hist_pull_z0_true_mass->GetYaxis()->SetRangeUser(0, y_max);
				TLine *l_n1_z0 = new TLine(-1,0,-1,y_max); l_n1_z0->SetLineColor(1); l_n1_z0->SetLineStyle(3); l_n1_z0->SetLineWidth(1); deletionPool.push_back(l_n1_z0);
				TLine *l_p1_z0 = new TLine(1,0,1,y_max); l_p1_z0->SetLineColor(1); l_p1_z0->SetLineStyle(3); l_p1_z0->SetLineWidth(1); deletionPool.push_back(l_p1_z0);
				TLine *l_0_z0 = new TLine(0,0,0,y_max); l_0_z0->SetLineColor(1); l_0_z0->SetLineStyle(3); l_0_z0->SetLineWidth(1); deletionPool.push_back(l_0_z0);
				l_n1_z0->Draw("same");
				l_p1_z0->Draw("same");
				l_0_z0->Draw("same");
				hist_pull_z0_true_mass->GetXaxis()->SetRangeUser(pull_min,pull_max);
				gPad->Update();
				TPaveStats *tps_pull_z0_pion_mass = (TPaveStats*)hist_pull_z0_pion_mass->FindObject("stats");
				TPaveStats *tps_pull_z0_true_mass = (TPaveStats*)hist_pull_z0_true_mass->FindObject("stats");
				tps_pull_z0_pion_mass->SetTextColor(2); tps_pull_z0_pion_mass->SetLineColor(2);
				tps_pull_z0_true_mass->SetTextColor(4); tps_pull_z0_true_mass->SetLineColor(4);
				tps_pull_z0_pion_mass->SetX1NDC(0.72); tps_pull_z0_pion_mass->SetX2NDC(0.88); tps_pull_z0_pion_mass->SetY1NDC(0.70); tps_pull_z0_pion_mass->SetY2NDC(0.9);
				X1 = tps_pull_z0_pion_mass->GetX1NDC(); X2 = tps_pull_z0_pion_mass->GetX2NDC(); Y1 = tps_pull_z0_pion_mass->GetY1NDC(); Y2 = tps_pull_z0_pion_mass->GetY2NDC();
				tps_pull_z0_true_mass->SetX1NDC(1-X2+0.1); tps_pull_z0_true_mass->SetX2NDC(1-X1+0.1); tps_pull_z0_true_mass->SetY1NDC(Y1); tps_pull_z0_true_mass->SetY2NDC(Y2);
				tps_pull_z0_pion_mass->Draw("same");
				tps_pull_z0_true_mass->Draw("same");
				TLegend *leg_pull_z0=new TLegend(X1 , 2 * Y1 - Y2 , X2 , Y1); deletionPool.push_back(leg_pull_z0);
				leg_pull_z0->SetTextSize(TextSize);
				leg_pull_z0->SetNColumns(2);
				leg_pull_z0->SetHeader(header_par,"C");
				leg_pull_z0->AddEntry("",header_r3D,"");
				leg_pull_z0->AddEntry("",header_r2D,"");
				leg_pull_z0->AddEntry(hist_pull_z0_pion_mass,"#pi","l");
				leg_pull_z0->AddEntry(hist_pull_z0_true_mass,particle_type,"l");
				leg_pull_z0->Draw("same");
				can_pull_z0->Update();
				can_pull_z0->SaveAs((plot_dir+"Pulls/"+file_init[par_iter]+"_pull_z0_mom_"+to_string(mom[mom_iter])+"_Angle_"+to_string(angle[angle_iter])+".pdf").c_str());
//				can_pull_z0->SaveAs((plot_dir+"Pulls/"+file_init[par_iter]+"_pull_z0_mom_"+to_string(mom[mom_iter])+"_Angle_"+to_string(angle[angle_iter])+".C").c_str());

				for (std::vector<TObject*>::iterator iter = deletionPool.begin(), endIter = deletionPool.end() ; endIter != iter ; ++iter)
					delete *iter;

			}

		}
		graph_d0_Mean_true_mass[mom_iter] = new TGraphErrors(angle.size(), angles, d0_true_mass_Mean, 0, d0_true_mass_Mean_Err);
		graph_d0_Mean_true_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_d0_Mean_true_mass[mom_iter]->SetLineStyle(1);
		graph_d0_Mean_true_mass[mom_iter]->SetLineWidth(1);
		graph_d0_Mean_true_mass[mom_iter]->SetMarkerSize(3);
		graph_d0_Mean_true_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_d0_Mean_true_mass[mom_iter]->SetMarkerStyle(marker_code[mom_iter]);
		multi_d0_Mean->Add(graph_d0_Mean_true_mass[mom_iter]);
		legend_d0_Mean->AddEntry(graph_d0_Mean_true_mass[mom_iter], true_particle, "epl");

		graph_d0_Sigma_true_mass[mom_iter] = new TGraphErrors(angle.size(), angles, d0_true_mass_Sigma, 0, d0_true_mass_Sigma_Err);
		graph_d0_Sigma_true_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_d0_Sigma_true_mass[mom_iter]->SetLineStyle(1);
		graph_d0_Sigma_true_mass[mom_iter]->SetLineWidth(1);
		graph_d0_Sigma_true_mass[mom_iter]->SetMarkerSize(3);
		graph_d0_Sigma_true_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_d0_Sigma_true_mass[mom_iter]->SetMarkerStyle(marker_code[mom_iter]);
		multi_d0_Sigma->Add(graph_d0_Sigma_true_mass[mom_iter]);
		legend_d0_Sigma->AddEntry(graph_d0_Sigma_true_mass[mom_iter], true_particle, "epl");

		graph_Phi_Mean_true_mass[mom_iter] = new TGraphErrors(angle.size(), angles, Phi_true_mass_Mean, 0, Phi_true_mass_Mean_Err);
		graph_Phi_Mean_true_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_Phi_Mean_true_mass[mom_iter]->SetLineStyle(1);
		graph_Phi_Mean_true_mass[mom_iter]->SetLineWidth(1);
		graph_Phi_Mean_true_mass[mom_iter]->SetMarkerSize(3);
		graph_Phi_Mean_true_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_Phi_Mean_true_mass[mom_iter]->SetMarkerStyle(marker_code[mom_iter]);
		multi_Phi_Mean->Add(graph_Phi_Mean_true_mass[mom_iter]);
		legend_Phi_Mean->AddEntry(graph_Phi_Mean_true_mass[mom_iter], true_particle, "epl");

		graph_Phi_Sigma_true_mass[mom_iter] = new TGraphErrors(angle.size(), angles, Phi_true_mass_Sigma, 0, Phi_true_mass_Sigma_Err);
		graph_Phi_Sigma_true_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_Phi_Sigma_true_mass[mom_iter]->SetLineStyle(1);
		graph_Phi_Sigma_true_mass[mom_iter]->SetLineWidth(1);
		graph_Phi_Sigma_true_mass[mom_iter]->SetMarkerSize(3);
		graph_Phi_Sigma_true_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_Phi_Sigma_true_mass[mom_iter]->SetMarkerStyle(marker_code[mom_iter]);
		multi_Phi_Sigma->Add(graph_Phi_Sigma_true_mass[mom_iter]);
		legend_Phi_Sigma->AddEntry(graph_Phi_Sigma_true_mass[mom_iter], true_particle, "epl");

		graph_Omega_Mean_true_mass[mom_iter] = new TGraphErrors(angle.size(), angles, Omega_true_mass_Mean, 0, Omega_true_mass_Mean_Err);
		graph_Omega_Mean_true_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_Omega_Mean_true_mass[mom_iter]->SetLineStyle(1);
		graph_Omega_Mean_true_mass[mom_iter]->SetLineWidth(1);
		graph_Omega_Mean_true_mass[mom_iter]->SetMarkerSize(3);
		graph_Omega_Mean_true_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_Omega_Mean_true_mass[mom_iter]->SetMarkerStyle(marker_code[mom_iter]);
		multi_Omega_Mean->Add(graph_Omega_Mean_true_mass[mom_iter]);
		legend_Omega_Mean->AddEntry(graph_Omega_Mean_true_mass[mom_iter], true_particle, "epl");

		graph_Omega_Sigma_true_mass[mom_iter] = new TGraphErrors(angle.size(), angles, Omega_true_mass_Sigma, 0, Omega_true_mass_Sigma_Err);
		graph_Omega_Sigma_true_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_Omega_Sigma_true_mass[mom_iter]->SetLineStyle(1);
		graph_Omega_Sigma_true_mass[mom_iter]->SetLineWidth(1);
		graph_Omega_Sigma_true_mass[mom_iter]->SetMarkerSize(3);
		graph_Omega_Sigma_true_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_Omega_Sigma_true_mass[mom_iter]->SetMarkerStyle(marker_code[mom_iter]);
		multi_Omega_Sigma->Add(graph_Omega_Sigma_true_mass[mom_iter]);
		legend_Omega_Sigma->AddEntry(graph_Omega_Sigma_true_mass[mom_iter], true_particle, "epl");

		graph_tanLambda_Mean_true_mass[mom_iter] = new TGraphErrors(angle.size(), angles, tanLambda_true_mass_Mean, 0, tanLambda_true_mass_Mean_Err);
		graph_tanLambda_Mean_true_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_tanLambda_Mean_true_mass[mom_iter]->SetLineStyle(1);
		graph_tanLambda_Mean_true_mass[mom_iter]->SetLineWidth(1);
		graph_tanLambda_Mean_true_mass[mom_iter]->SetMarkerSize(3);
		graph_tanLambda_Mean_true_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_tanLambda_Mean_true_mass[mom_iter]->SetMarkerStyle(marker_code[mom_iter]);
		multi_tanLambda_Mean->Add(graph_tanLambda_Mean_true_mass[mom_iter]);
		legend_tanLambda_Mean->AddEntry(graph_tanLambda_Mean_true_mass[mom_iter], true_particle, "epl");

		graph_tanLambda_Sigma_true_mass[mom_iter] = new TGraphErrors(angle.size(), angles, tanLambda_true_mass_Sigma, 0, tanLambda_true_mass_Sigma_Err);
		graph_tanLambda_Sigma_true_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_tanLambda_Sigma_true_mass[mom_iter]->SetLineStyle(1);
		graph_tanLambda_Sigma_true_mass[mom_iter]->SetLineWidth(1);
		graph_tanLambda_Sigma_true_mass[mom_iter]->SetMarkerSize(3);
		graph_tanLambda_Sigma_true_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_tanLambda_Sigma_true_mass[mom_iter]->SetMarkerStyle(marker_code[mom_iter]);
		multi_tanLambda_Sigma->Add(graph_tanLambda_Sigma_true_mass[mom_iter]);
		legend_tanLambda_Sigma->AddEntry(graph_tanLambda_Sigma_true_mass[mom_iter], true_particle, "epl");

		graph_z0_Mean_true_mass[mom_iter] = new TGraphErrors(angle.size(), angles, z0_true_mass_Mean, 0, z0_true_mass_Mean_Err);
		graph_z0_Mean_true_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_z0_Mean_true_mass[mom_iter]->SetLineStyle(1);
		graph_z0_Mean_true_mass[mom_iter]->SetLineWidth(1);
		graph_z0_Mean_true_mass[mom_iter]->SetMarkerSize(3);
		graph_z0_Mean_true_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_z0_Mean_true_mass[mom_iter]->SetMarkerStyle(marker_code[mom_iter]);
		multi_z0_Mean->Add(graph_z0_Mean_true_mass[mom_iter]);
		legend_z0_Mean->AddEntry(graph_z0_Mean_true_mass[mom_iter], true_particle, "epl");

		graph_z0_Sigma_true_mass[mom_iter] = new TGraphErrors(angle.size(), angles, z0_true_mass_Sigma, 0, z0_true_mass_Sigma_Err);
		graph_z0_Sigma_true_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_z0_Sigma_true_mass[mom_iter]->SetLineStyle(1);
		graph_z0_Sigma_true_mass[mom_iter]->SetLineWidth(1);
		graph_z0_Sigma_true_mass[mom_iter]->SetMarkerSize(3);
		graph_z0_Sigma_true_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_z0_Sigma_true_mass[mom_iter]->SetMarkerStyle(marker_code[mom_iter]);
		multi_z0_Sigma->Add(graph_z0_Sigma_true_mass[mom_iter]);
		legend_z0_Sigma->AddEntry(graph_z0_Sigma_true_mass[mom_iter], true_particle, "epl");


		graph_d0_Mean_pion_mass[mom_iter] = new TGraphErrors(angle.size(), angles, d0_pion_mass_Mean, 0, d0_pion_mass_Mean_Err);
		graph_d0_Mean_pion_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_d0_Mean_pion_mass[mom_iter]->SetLineStyle(7);
		graph_d0_Mean_pion_mass[mom_iter]->SetLineWidth(1);
		graph_d0_Mean_pion_mass[mom_iter]->SetMarkerSize(3);
		graph_d0_Mean_pion_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_d0_Mean_pion_mass[mom_iter]->SetMarkerStyle(marker_code_pion[mom_iter]);
		multi_d0_Mean->Add(graph_d0_Mean_pion_mass[mom_iter]);
		legend_d0_Mean->AddEntry(graph_d0_Mean_pion_mass[mom_iter], pion_particle, "epl");
		graph_d0_Sigma_pion_mass[mom_iter] = new TGraphErrors(angle.size(), angles, d0_pion_mass_Sigma, 0, d0_pion_mass_Sigma_Err);
		graph_d0_Sigma_pion_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_d0_Sigma_pion_mass[mom_iter]->SetLineStyle(7);
		graph_d0_Sigma_pion_mass[mom_iter]->SetLineWidth(1);
		graph_d0_Sigma_pion_mass[mom_iter]->SetMarkerSize(3);
		graph_d0_Sigma_pion_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_d0_Sigma_pion_mass[mom_iter]->SetMarkerStyle(marker_code_pion[mom_iter]);
		multi_d0_Sigma->Add(graph_d0_Sigma_pion_mass[mom_iter]);
		legend_d0_Sigma->AddEntry(graph_d0_Sigma_pion_mass[mom_iter], pion_particle, "epl");

		graph_Phi_Mean_pion_mass[mom_iter] = new TGraphErrors(angle.size(), angles, Phi_pion_mass_Mean, 0, Phi_pion_mass_Mean_Err);
		graph_Phi_Mean_pion_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_Phi_Mean_pion_mass[mom_iter]->SetLineStyle(7);
		graph_Phi_Mean_pion_mass[mom_iter]->SetLineWidth(1);
		graph_Phi_Mean_pion_mass[mom_iter]->SetMarkerSize(3);
		graph_Phi_Mean_pion_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_Phi_Mean_pion_mass[mom_iter]->SetMarkerStyle(marker_code_pion[mom_iter]);
		multi_Phi_Mean->Add(graph_Phi_Mean_pion_mass[mom_iter]);
		legend_Phi_Mean->AddEntry(graph_Phi_Mean_pion_mass[mom_iter], pion_particle, "epl");

		graph_Phi_Sigma_pion_mass[mom_iter] = new TGraphErrors(angle.size(), angles, Phi_pion_mass_Sigma, 0, Phi_pion_mass_Sigma_Err);
		graph_Phi_Sigma_pion_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_Phi_Sigma_pion_mass[mom_iter]->SetLineStyle(7);
		graph_Phi_Sigma_pion_mass[mom_iter]->SetLineWidth(1);
		graph_Phi_Sigma_pion_mass[mom_iter]->SetMarkerSize(3);
		graph_Phi_Sigma_pion_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_Phi_Sigma_pion_mass[mom_iter]->SetMarkerStyle(marker_code_pion[mom_iter]);
		multi_Phi_Sigma->Add(graph_Phi_Sigma_pion_mass[mom_iter]);
		legend_Phi_Sigma->AddEntry(graph_Phi_Sigma_pion_mass[mom_iter], pion_particle, "epl");

		graph_Omega_Mean_pion_mass[mom_iter] = new TGraphErrors(angle.size(), angles, Omega_pion_mass_Mean, 0, Omega_pion_mass_Mean_Err);
		graph_Omega_Mean_pion_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_Omega_Mean_pion_mass[mom_iter]->SetLineStyle(7);
		graph_Omega_Mean_pion_mass[mom_iter]->SetLineWidth(1);
		graph_Omega_Mean_pion_mass[mom_iter]->SetMarkerSize(3);
		graph_Omega_Mean_pion_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_Omega_Mean_pion_mass[mom_iter]->SetMarkerStyle(marker_code_pion[mom_iter]);
		multi_Omega_Mean->Add(graph_Omega_Mean_pion_mass[mom_iter]);
		legend_Omega_Mean->AddEntry(graph_Omega_Mean_pion_mass[mom_iter], pion_particle, "epl");

		graph_Omega_Sigma_pion_mass[mom_iter] = new TGraphErrors(angle.size(), angles, Omega_pion_mass_Sigma, 0, Omega_pion_mass_Sigma_Err);
		graph_Omega_Sigma_pion_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_Omega_Sigma_pion_mass[mom_iter]->SetLineStyle(7);
		graph_Omega_Sigma_pion_mass[mom_iter]->SetLineWidth(1);
		graph_Omega_Sigma_pion_mass[mom_iter]->SetMarkerSize(3);
		graph_Omega_Sigma_pion_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_Omega_Sigma_pion_mass[mom_iter]->SetMarkerStyle(marker_code_pion[mom_iter]);
		multi_Omega_Sigma->Add(graph_Omega_Sigma_pion_mass[mom_iter]);
		legend_Omega_Sigma->AddEntry(graph_Omega_Sigma_pion_mass[mom_iter], pion_particle, "epl");

		graph_tanLambda_Mean_pion_mass[mom_iter] = new TGraphErrors(angle.size(), angles, tanLambda_pion_mass_Mean, 0, tanLambda_pion_mass_Mean_Err);
		graph_tanLambda_Mean_pion_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_tanLambda_Mean_pion_mass[mom_iter]->SetLineStyle(7);
		graph_tanLambda_Mean_pion_mass[mom_iter]->SetLineWidth(1);
		graph_tanLambda_Mean_pion_mass[mom_iter]->SetMarkerSize(3);
		graph_tanLambda_Mean_pion_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_tanLambda_Mean_pion_mass[mom_iter]->SetMarkerStyle(marker_code_pion[mom_iter]);
		multi_tanLambda_Mean->Add(graph_tanLambda_Mean_pion_mass[mom_iter]);
		legend_tanLambda_Mean->AddEntry(graph_tanLambda_Mean_pion_mass[mom_iter], pion_particle, "epl");

		graph_tanLambda_Sigma_pion_mass[mom_iter] = new TGraphErrors(angle.size(), angles, tanLambda_pion_mass_Sigma, 0, tanLambda_pion_mass_Sigma_Err);
		graph_tanLambda_Sigma_pion_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_tanLambda_Sigma_pion_mass[mom_iter]->SetLineStyle(7);
		graph_tanLambda_Sigma_pion_mass[mom_iter]->SetLineWidth(1);
		graph_tanLambda_Sigma_pion_mass[mom_iter]->SetMarkerSize(3);
		graph_tanLambda_Sigma_pion_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_tanLambda_Sigma_pion_mass[mom_iter]->SetMarkerStyle(marker_code_pion[mom_iter]);
		multi_tanLambda_Sigma->Add(graph_tanLambda_Sigma_pion_mass[mom_iter]);
		legend_tanLambda_Sigma->AddEntry(graph_tanLambda_Sigma_pion_mass[mom_iter], pion_particle, "epl");

		graph_z0_Mean_pion_mass[mom_iter] = new TGraphErrors(angle.size(), angles, z0_pion_mass_Mean, 0, z0_pion_mass_Mean_Err);
		graph_z0_Mean_pion_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_z0_Mean_pion_mass[mom_iter]->SetLineStyle(7);
		graph_z0_Mean_pion_mass[mom_iter]->SetLineWidth(1);
		graph_z0_Mean_pion_mass[mom_iter]->SetMarkerSize(3);
		graph_z0_Mean_pion_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_z0_Mean_pion_mass[mom_iter]->SetMarkerStyle(marker_code_pion[mom_iter]);
		multi_z0_Mean->Add(graph_z0_Mean_pion_mass[mom_iter]);
		legend_z0_Mean->AddEntry(graph_z0_Mean_pion_mass[mom_iter], pion_particle, "epl");

		graph_z0_Sigma_pion_mass[mom_iter] = new TGraphErrors(angle.size(), angles, z0_pion_mass_Sigma, 0, z0_pion_mass_Sigma_Err);
		graph_z0_Sigma_pion_mass[mom_iter]->SetLineColor(color_code[mom_iter]);
		graph_z0_Sigma_pion_mass[mom_iter]->SetLineStyle(7);
		graph_z0_Sigma_pion_mass[mom_iter]->SetLineWidth(1);
		graph_z0_Sigma_pion_mass[mom_iter]->SetMarkerSize(3);
		graph_z0_Sigma_pion_mass[mom_iter]->SetMarkerColor(color_code[mom_iter]);
		graph_z0_Sigma_pion_mass[mom_iter]->SetMarkerStyle(marker_code_pion[mom_iter]);
		multi_z0_Sigma->Add(graph_z0_Sigma_pion_mass[mom_iter]);
		legend_z0_Sigma->AddEntry(graph_z0_Sigma_pion_mass[mom_iter], pion_particle, "epl");

	}

	TCanvas *can_d0_Mean = new TCanvas("can_d0_Mean", "", 1600,1200);
	multi_d0_Mean->Draw("APL");
	multi_d0_Mean->GetXaxis()->SetTitle("#theta [deg]");
	multi_d0_Mean->GetYaxis()->SetTitle("#mu");
	multi_d0_Mean->GetYaxis()->SetRangeUser(d0_Mean_min, d0_Mean_max);
	legend_d0_Mean->SetHeader(header_d0_Mean);
	legend_d0_Mean->SetNColumns(2);
	legend_d0_Mean->Draw("same");
	can_d0_Mean->SaveAs((plot_dir+"Mean_Sigma/d0_Mean_.pdf").c_str());
	delete legend_d0_Mean; delete multi_d0_Mean; delete can_d0_Mean;
	TCanvas *can_d0_Sigma = new TCanvas("can_d0_Sigma", "", 1600,1200);
	multi_d0_Sigma->Draw("APL");
	multi_d0_Sigma->GetXaxis()->SetTitle("#theta [deg]");
	multi_d0_Sigma->GetYaxis()->SetTitle("#sigma");
	multi_d0_Sigma->GetYaxis()->SetRangeUser(d0_Sigma_min, d0_Sigma_max);
	legend_d0_Sigma->SetHeader(header_d0_Sigma);
	legend_d0_Sigma->SetNColumns(2);
	legend_d0_Sigma->Draw("same");
	can_d0_Sigma->SaveAs((plot_dir+"Mean_Sigma/d0_Sigma_.pdf").c_str());
	delete legend_d0_Sigma; delete multi_d0_Sigma; delete can_d0_Sigma;

	TCanvas *can_Phi_Mean = new TCanvas("can_Phi_Mean", "", 1600,1200);
	multi_Phi_Mean->Draw("APL");
	multi_Phi_Mean->GetXaxis()->SetTitle("#theta [deg]");
	multi_Phi_Mean->GetYaxis()->SetTitle("#mu");
	multi_Phi_Mean->GetYaxis()->SetRangeUser(Phi_Mean_min, Phi_Mean_max);
	legend_Phi_Mean->SetHeader(header_Phi_Mean);
	legend_Phi_Mean->SetNColumns(2);
	legend_Phi_Mean->Draw("same");
	can_Phi_Mean->SaveAs((plot_dir+"Mean_Sigma/Phi_Mean_.pdf").c_str());
	delete legend_Phi_Mean; delete multi_Phi_Mean; delete can_Phi_Mean;
	TCanvas *can_Phi_Sigma = new TCanvas("can_Phi_Sigma", "", 1600,1200);
	multi_Phi_Sigma->Draw("APL");
	multi_Phi_Sigma->GetXaxis()->SetTitle("#theta [deg]");
	multi_Phi_Sigma->GetYaxis()->SetTitle("#sigma");
	multi_Phi_Sigma->GetYaxis()->SetRangeUser(Phi_Sigma_min, Phi_Sigma_max);
	legend_Phi_Sigma->SetHeader(header_Phi_Sigma);
	legend_Phi_Sigma->SetNColumns(2);
	legend_Phi_Sigma->Draw("same");
	can_Phi_Sigma->SaveAs((plot_dir+"Mean_Sigma/Phi_Sigma_.pdf").c_str());
	delete legend_Phi_Sigma; delete multi_Phi_Sigma; delete can_Phi_Sigma;

	TCanvas *can_Omega_Mean = new TCanvas("can_Omega_Mean", "", 1600,1200);
	multi_Omega_Mean->Draw("APL");
	multi_Omega_Mean->GetXaxis()->SetTitle("#theta [deg]");
	multi_Omega_Mean->GetYaxis()->SetTitle("#mu");
	multi_Omega_Mean->GetYaxis()->SetRangeUser(Omega_Mean_min, Omega_Mean_max);
	legend_Omega_Mean->SetHeader(header_Omega_Mean);
	legend_Omega_Mean->SetNColumns(2);
	legend_Omega_Mean->Draw("same");
	can_Omega_Mean->SaveAs((plot_dir+"Mean_Sigma/Omega_Mean_.pdf").c_str());
	delete legend_Omega_Mean; delete multi_Omega_Mean; delete can_Omega_Mean;
	TCanvas *can_Omega_Sigma = new TCanvas("can_Omega_Sigma", "", 1600,1200);
	multi_Omega_Sigma->Draw("APL");
	multi_Omega_Sigma->GetXaxis()->SetTitle("#theta [deg]");
	multi_Omega_Sigma->GetYaxis()->SetTitle("#sigma");
	multi_Omega_Sigma->GetYaxis()->SetRangeUser(Omega_Sigma_min, Omega_Sigma_max);
	legend_Omega_Sigma->SetHeader(header_Omega_Sigma);
	legend_Omega_Sigma->SetNColumns(2);
	legend_Omega_Sigma->Draw("same");
	can_Omega_Sigma->SaveAs((plot_dir+"Mean_Sigma/Omega_Sigma_.pdf").c_str());
	delete legend_Omega_Sigma; delete multi_Omega_Sigma; delete can_Omega_Sigma;

	TCanvas *can_tanLambda_Mean = new TCanvas("can_tanLambda_Mean", "", 1600,1200);
	multi_tanLambda_Mean->Draw("APL");
	multi_tanLambda_Mean->GetXaxis()->SetTitle("#theta [deg]");
	multi_tanLambda_Mean->GetYaxis()->SetTitle("#mu");
	multi_tanLambda_Mean->GetYaxis()->SetRangeUser(tanLambda_Mean_min, tanLambda_Mean_max);
	legend_tanLambda_Mean->SetHeader(header_tanLambda_Mean);
	legend_tanLambda_Mean->SetNColumns(2);
	legend_tanLambda_Mean->Draw("same");
	can_tanLambda_Mean->SaveAs((plot_dir+"Mean_Sigma/tanLambda_Mean_.pdf").c_str());
	delete legend_tanLambda_Mean; delete multi_tanLambda_Mean; delete can_tanLambda_Mean;
	TCanvas *can_tanLambda_Sigma = new TCanvas("can_tanLambda_Sigma", "", 1600,1200);
	multi_tanLambda_Sigma->Draw("APL");
	multi_tanLambda_Sigma->GetXaxis()->SetTitle("#theta [deg]");
	multi_tanLambda_Sigma->GetYaxis()->SetTitle("#sigma");
	multi_tanLambda_Sigma->GetYaxis()->SetRangeUser(tanLambda_Sigma_min, tanLambda_Sigma_max);
	legend_tanLambda_Sigma->SetHeader(header_tanLambda_Sigma);
	legend_tanLambda_Sigma->SetNColumns(2);
	legend_tanLambda_Sigma->Draw("same");
	can_tanLambda_Sigma->SaveAs((plot_dir+"Mean_Sigma/tanLambda_Sigma_.pdf").c_str());
	delete legend_tanLambda_Sigma; delete multi_tanLambda_Sigma; delete can_tanLambda_Sigma;

	TCanvas *can_z0_Mean = new TCanvas("can_z0_Mean", "", 1600,1200);
	multi_z0_Mean->Draw("APL");
	multi_z0_Mean->GetXaxis()->SetTitle("#theta [deg]");
	multi_z0_Mean->GetYaxis()->SetTitle("#mu");
	multi_z0_Mean->GetYaxis()->SetRangeUser(z0_Mean_min, z0_Mean_max);
	legend_z0_Mean->SetHeader(header_z0_Mean);
	legend_z0_Mean->SetNColumns(2);
	legend_z0_Mean->Draw("same");
	can_z0_Mean->SaveAs((plot_dir+"Mean_Sigma/z0_Mean_.pdf").c_str());
	delete legend_z0_Mean; delete multi_z0_Mean; delete can_z0_Mean;
	TCanvas *can_z0_Sigma = new TCanvas("can_z0_Sigma", "", 1600,1200);
	multi_z0_Sigma->Draw("APL");
	multi_z0_Sigma->GetXaxis()->SetTitle("#theta [deg]");
	multi_z0_Sigma->GetYaxis()->SetTitle("#sigma");
	multi_z0_Sigma->GetYaxis()->SetRangeUser(z0_Sigma_min, z0_Sigma_max);
	legend_z0_Sigma->SetHeader(header_z0_Sigma);
	legend_z0_Sigma->SetNColumns(2);
	legend_z0_Sigma->Draw("same");
	can_z0_Sigma->SaveAs((plot_dir+"Mean_Sigma/z0_Sigma_.pdf").c_str());
	delete legend_z0_Sigma; delete multi_z0_Sigma; delete can_z0_Sigma;

}
