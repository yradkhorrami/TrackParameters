#include "TrackParameters.h"
#include <iostream>

#include <EVENT/LCCollection.h>
#include <EVENT/LCFloatVec.h>
#include <EVENT/LCObject.h>
#include <EVENT/MCParticle.h>
#include <EVENT/LCParameters.h>
#include <marlinutil/GeometryUtil.h>
#include <UTIL/LCRelationNavigator.h>

// ----- include for verbosity dependend logging ---------
#include "marlin/VerbosityLevels.h"

#ifdef MARLIN_USE_AIDA
#include <marlin/AIDAProcessor.h>
#include <AIDA/IHistogramFactory.h>
#include <AIDA/ICloud1D.h>
//#include <AIDA/IHistogram1D.h>
#endif // MARLIN_USE_AIDA

#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"

using namespace lcio ;
using namespace marlin ;

MyTrackParameters aTrackParameters;

MyTrackParameters::MyTrackParameters() :
	Processor("TrackParameters"),
	m_nRun(0),
	m_nEvt(0),
	m_nRunSum(0),
	m_nEvtSum(0),

	m_trk_pdg{},
	m_trk_charge{},
	m_trk_genStat{},
	m_highest_weight{},
	m_mcp_momentum{},
	m_mcp_d0{},
	m_rec_d0_pion_mass{},
	m_rec_d0_true_mass{},
	m_mcp_Omega{},
	m_rec_Omega_pion_mass{},
	m_rec_Omega_true_mass{},
	m_mcp_Phi{},
	m_rec_Phi_pion_mass{},
	m_rec_Phi_true_mass{},
	m_mcp_tanLambda{},
	m_rec_tanLambda_pion_mass{},
	m_rec_tanLambda_true_mass{},
	m_mcp_z0{},
	m_rec_z0_pion_mass{},
	m_rec_z0_true_mass{},
	m_residual_d0_pion_mass{},
	m_residual_Omega_pion_mass{},
	m_residual_Phi_pion_mass{},
	m_residual_tanLambda_pion_mass{},
	m_residual_z0_pion_mass{},
	m_uncertainty_d0_pion_mass{},
	m_uncertainty_Omega_pion_mass{},
	m_uncertainty_Phi_pion_mass{},
	m_uncertainty_tanLambda_pion_mass{},
	m_uncertainty_z0_pion_mass{},
	m_pull_d0_pion_mass{},
	m_pull_Omega_pion_mass{},
	m_pull_Phi_pion_mass{},
	m_pull_tanLambda_pion_mass{},
	m_pull_z0_pion_mass{},

	m_residual_d0_true_mass{},
	m_residual_Omega_true_mass{},
	m_residual_Phi_true_mass{},
	m_residual_tanLambda_true_mass{},
	m_residual_z0_true_mass{},
	m_uncertainty_d0_true_mass{},
	m_uncertainty_Omega_true_mass{},
	m_uncertainty_Phi_true_mass{},
	m_uncertainty_tanLambda_true_mass{},
	m_uncertainty_z0_true_mass{},
	m_pull_d0_true_mass{},
	m_pull_Omega_true_mass{},
	m_pull_Phi_true_mass{},
	m_pull_tanLambda_true_mass{},
	m_pull_z0_true_mass{},

	m_ndf{},
	m_chi2{},
	m_chi2_ndf{},


	m_pTFile(NULL),
	m_pTTree(NULL)


{

    // modify processor description
    _description = "MyTrackParameters finds Track parameters regarding different mass hypothesis" ;


    // register steering parameters: name, description, class-variable, default value
	registerInputCollection(LCIO::MCPARTICLE,
					"MCParticleCollection" ,
					"Name of the MCParticle collection"  ,
					m_mcParticleCollection,
					std::string("MCParticle")
					);

	registerInputCollection(LCIO::LCRELATION,
					"MarlinTrkTracksMCTruthLink" ,
					"Name of the Track-MCParticle Relations collection for input tracks"  ,
					m_TrackMCParticleRelCol ,
					std::string("MarlinTrkTracksMCTruthLink")
					);

	registerInputCollection(LCIO::LCRELATION,
					"MCTruthMarlinTrkTracksLink" ,
					"Name of the MCParticle-Track Relations collection for input MCParticles"  ,
					m_MCParticleTrackRelCol ,
					std::string("MCTruthMarlinTrkTracksLink")
					);

	registerOutputCollection(LCIO::MCPARTICLE,
					"MCParticleCollectionVector" ,
					"Name of the MCParticle collection for Kaons"  ,
					m_col_mcp,
					std::string("MCParticleCollectionVector")
					);

	registerInputCollection( LCIO::TRACK,
          				"MarlinTrkTracksCollection" ,
          				"Name of the MarlinTrkTracks collection"  ,
          				m_MarlinTrkTracks,
          				std::string("MarlinTrkTracks")
    					);

	registerInputCollection( LCIO::TRACK,
          				"MarlinTrkTracksCollectionPion" ,
          				"Name of the MarlinTrkTracks collection"  ,
          				m_MarlinTrkTracksPION,
          				std::string("MarlinTrkTracksPion")
    					);

	registerInputCollection( LCIO::TRACK,
          				"MarlinTrkTracksCollectionMuon" ,
          				"Name of the MarlinTrkTracks collection"  ,
          				m_MarlinTrkTracksMUON,
          				std::string("MarlinTrkTracksMuon")
    					);

	registerInputCollection( LCIO::TRACK,
          				"MarlinTrkTracksCollectionKaon" ,
          				"Name of the MarlinTrkTracks collection"  ,
          				m_MarlinTrkTracksKAON,
          				std::string("MarlinTrkTracksKaon")
    					);

	registerInputCollection( LCIO::TRACK,
          				"MarlinTrkTracksCollectionProton" ,
          				"Name of the MarlinTrkTracks collection"  ,
          				m_MarlinTrkTracksPROTON,
          				std::string("MarlinTrkTracksProton")
    					);

	registerInputCollection( LCIO::TRACK,
          				"MarlinTrkTracksCollectionElectron" ,
          				"Name of the MarlinTrkTracks collection"  ,
          				m_MarlinTrkTracksELECTRON,
          				std::string("MarlinTrkTracksElectron")
    					);

	registerProcessorParameter("RootFile",
					"Name of the output root file",
					m_rootFile,
					std::string("TrackParameters.root")
					);
/*
	registerInputCollection(LCIO::MCPARTICLE,
					"MCParticleCollectionKaon" ,
					"Name of the MCParticle collection for Kaons"  ,
					m_col_Kaon_mcp,
					std::string("mcpKaon")
					);

	registerInputCollection(LCIO::MCPARTICLE,
					"MCParticleCollectionPion" ,
					"Name of the MCParticle collection for Pions"  ,
					m_col_Pion_mcp,
					std::string("mcpPion")
					);

	registerInputCollection(LCIO::MCPARTICLE,
					"MCParticleCollectionMuon" ,
					"Name of the MCParticle collection for Muons"  ,
					m_col_Muon_mcp,
					std::string("mcpMuon")
					);

	registerInputCollection(LCIO::MCPARTICLE,
					"MCParticleCollectionProton" ,
					"Name of the MCParticle collection for Protons"  ,
					m_col_Proton_mcp,
					std::string("mcpProton")
					);

	registerInputCollection(LCIO::MCPARTICLE,
					"MCParticleCollectionElectron" ,
					"Name of the MCParticle collection for Electrons"  ,
					m_col_Electron_mcp,
					std::string("mcpElectron")
					);
*/
}



void MyTrackParameters::init()
{

    streamlog_out(DEBUG) << "   init called  " << std::endl ;

    // usually a good idea to
    printParameters() ;

	m_nRun = 0 ;
	m_nEvt = 0 ;
	m_nRunSum = 0;
	m_nEvtSum = 0;
	_bField = 3.5;// MarlinUtil::getBzAtOrigin();
	streamlog_out(DEBUG) << "   _bField=  "<<_bField  << std::endl ;

	this->Clear();

	m_pTFile = new TFile(m_rootFile.c_str(), "recreate");
	m_pTTree = new TTree("TrackParameters", "TrackParameters");
	m_pTTree->SetDirectory(m_pTFile);
	m_pTTree->Branch("run", &m_nRun, "run/I");
	m_pTTree->Branch("event", &m_nEvt, "event/I");

	m_pTTree->Branch("track_PDG", &m_trk_pdg);
	m_pTTree->Branch("trk_GeneratorStatus", &m_trk_genStat);
	m_pTTree->Branch("highest_weight", &m_highest_weight);
	m_pTTree->Branch("track_charge", &m_trk_charge);
	m_pTTree->Branch("mcp_momentum", &m_mcp_momentum);
	m_pTTree->Branch("mcp_d0", &m_mcp_d0);
	m_pTTree->Branch("rec_d0_pion_mass", &m_rec_d0_pion_mass);
	m_pTTree->Branch("rec_d0_true_mass", &m_rec_d0_true_mass);
	m_pTTree->Branch("mcp_Omega", &m_mcp_Omega);
	m_pTTree->Branch("rec_Omega_pion_mass", &m_rec_Omega_pion_mass);
	m_pTTree->Branch("rec_Omega_true_mass", &m_rec_Omega_true_mass);
	m_pTTree->Branch("mcp_Phi", &m_mcp_Phi);
	m_pTTree->Branch("rec_Phi_pion_mass", &m_rec_Phi_pion_mass);
	m_pTTree->Branch("rec_Phi_true_mass", &m_rec_Phi_true_mass);
	m_pTTree->Branch("mcp_tanLambda", &m_mcp_tanLambda);
	m_pTTree->Branch("rec_tanLambda_pion_mass", &m_rec_tanLambda_pion_mass);
	m_pTTree->Branch("rec_tanLambda_true_mass", &m_rec_tanLambda_true_mass);
	m_pTTree->Branch("mcp_z0", &m_mcp_z0);
	m_pTTree->Branch("rec_z0_pion_mass", &m_rec_z0_pion_mass);
	m_pTTree->Branch("rec_z0_true_mass", &m_rec_z0_true_mass);
	m_pTTree->Branch("residual_d0_pion_mass", &m_residual_d0_pion_mass);
	m_pTTree->Branch("residual_Omega_pion_mass", &m_residual_Omega_pion_mass);
	m_pTTree->Branch("residual_Phi_pion_mass", &m_residual_Phi_pion_mass);
	m_pTTree->Branch("residual_tanLambda_pion_mass", &m_residual_tanLambda_pion_mass);
	m_pTTree->Branch("residual_z0_pion_mass", &m_residual_z0_pion_mass);
	m_pTTree->Branch("uncertainty_d0_pion_mass", &m_uncertainty_d0_pion_mass);
	m_pTTree->Branch("uncertainty_Omega_pion_mass", &m_uncertainty_Omega_pion_mass);
	m_pTTree->Branch("uncertainty_Phi_pion_mass", &m_uncertainty_Phi_pion_mass);
	m_pTTree->Branch("uncertainty_tanLambda_pion_mass", &m_uncertainty_tanLambda_pion_mass);
	m_pTTree->Branch("uncertainty_z0_pion_mass", &m_uncertainty_z0_pion_mass);
	m_pTTree->Branch("pull_d0_pion_mass", &m_pull_d0_pion_mass);
	m_pTTree->Branch("pull_Omega_pion_mass", &m_pull_Omega_pion_mass);
	m_pTTree->Branch("pull_Phi_pion_mass", &m_pull_Phi_pion_mass);
	m_pTTree->Branch("pull_tanLambda_pion_mass", &m_pull_tanLambda_pion_mass);
	m_pTTree->Branch("pull_z0_pion_mass", &m_pull_z0_pion_mass);
	m_pTTree->Branch("residual_d0_true_mass", &m_residual_d0_true_mass);
	m_pTTree->Branch("residual_Omega_true_mass", &m_residual_Omega_true_mass);
	m_pTTree->Branch("residual_Phi_true_mass", &m_residual_Phi_true_mass);
	m_pTTree->Branch("residual_tanLambda_true_mass", &m_residual_tanLambda_true_mass);
	m_pTTree->Branch("residual_z0_true_mass", &m_residual_z0_true_mass);
	m_pTTree->Branch("uncertainty_d0_true_mass", &m_uncertainty_d0_true_mass);
	m_pTTree->Branch("uncertainty_Omega_true_mass", &m_uncertainty_Omega_true_mass);
	m_pTTree->Branch("uncertainty_Phi_true_mass", &m_uncertainty_Phi_true_mass);
	m_pTTree->Branch("uncertainty_tanLambda_true_mass", &m_uncertainty_tanLambda_true_mass);
	m_pTTree->Branch("uncertainty_z0_true_mass", &m_uncertainty_z0_true_mass);
	m_pTTree->Branch("pull_d0_true_mass", &m_pull_d0_true_mass);
	m_pTTree->Branch("pull_Omega_true_mass", &m_pull_Omega_true_mass);
	m_pTTree->Branch("pull_Phi_true_mass", &m_pull_Phi_true_mass);
	m_pTTree->Branch("pull_tanLambda_true_mass", &m_pull_tanLambda_true_mass);
	m_pTTree->Branch("pull_z0_true_mass", &m_pull_z0_true_mass);
	m_pTTree->Branch("NDF", &m_ndf);
	m_pTTree->Branch("CHI2", &m_chi2);
	m_pTTree->Branch("CHI2_NDF", &m_chi2_ndf);

}


void MyTrackParameters::processRunHeader( LCRunHeader *pLCRunHeader)
{
	m_nRun = 0;
	m_nEvt = 0;
	++m_nRunSum;
}



void MyTrackParameters::processEvent( LCEvent *pLCEvent )
{

	m_nRun = pLCEvent->getRunNumber();
	m_nEvt = pLCEvent->getEventNumber();

	++m_nEvtSum;

	if ((m_nEvtSum % 100) == 0)
         std::cout << " processed events: " << m_nEvtSum << std::endl;

    // New reco particle collection for the semi-leptonic decays

	this->Clear();
	this->ExtractCollections(pLCEvent);
	this->FindTrackParameters(pLCEvent);
	m_pTTree->Fill();
}



void MyTrackParameters::check( LCEvent *pLCEvent )
{
    // nothing to check here - could be used to fill checkplots in reconstruction processor
}


void MyTrackParameters::end()
{

	m_pTFile->cd();
	m_pTTree->Write();

	m_pTFile->Close();
	delete m_pTFile;

    //   std::cout << "MySLDecayFinder::end()  " << name()
    // 	    << " processed " << _nEvt << " events in " << _nRun << " runs "
    // 	    << std::endl ;

}

void MyTrackParameters::Clear()
{

	m_trk_pdg.clear();
	m_trk_charge.clear();
	m_trk_genStat.clear();
	m_highest_weight.clear();
	m_mcp_momentum.clear();

	m_mcp_d0.clear();
	m_rec_d0_pion_mass.clear();
	m_rec_d0_true_mass.clear();

	m_mcp_Omega.clear();
	m_rec_Omega_pion_mass.clear();
	m_rec_Omega_true_mass.clear();

	m_mcp_Phi.clear();
	m_rec_Phi_pion_mass.clear();
	m_rec_Phi_true_mass.clear();

	m_mcp_tanLambda.clear();
	m_rec_tanLambda_pion_mass.clear();
	m_rec_tanLambda_true_mass.clear();

	m_mcp_z0.clear();
	m_rec_z0_pion_mass.clear();
	m_rec_z0_true_mass.clear();

	m_residual_d0_pion_mass.clear();
	m_residual_Omega_pion_mass.clear();
	m_residual_Phi_pion_mass.clear();
	m_residual_tanLambda_pion_mass.clear();
	m_residual_z0_pion_mass.clear();
	m_uncertainty_d0_pion_mass.clear();
	m_uncertainty_Omega_pion_mass.clear();
	m_uncertainty_Phi_pion_mass.clear();
	m_uncertainty_tanLambda_pion_mass.clear();
	m_uncertainty_z0_pion_mass.clear();
	m_pull_d0_pion_mass.clear();
	m_pull_Omega_pion_mass.clear();
	m_pull_Phi_pion_mass.clear();
	m_pull_tanLambda_pion_mass.clear();
	m_pull_z0_pion_mass.clear();

	m_residual_d0_true_mass.clear();
	m_residual_Omega_true_mass.clear();
	m_residual_Phi_true_mass.clear();
	m_residual_tanLambda_true_mass.clear();
	m_residual_z0_true_mass.clear();
	m_uncertainty_d0_true_mass.clear();
	m_uncertainty_Omega_true_mass.clear();
	m_uncertainty_Phi_true_mass.clear();
	m_uncertainty_tanLambda_true_mass.clear();
	m_uncertainty_z0_true_mass.clear();
	m_pull_d0_true_mass.clear();
	m_pull_Omega_true_mass.clear();
	m_pull_Phi_true_mass.clear();
	m_pull_tanLambda_true_mass.clear();
	m_pull_z0_true_mass.clear();

	m_ndf.clear();
	m_chi2.clear();
	m_chi2_ndf.clear();

}

void MyTrackParameters::ExtractCollections(EVENT::LCEvent *pLCEvent)
{
	try
     {
     	const EVENT::LCCollection *pLCCollectionPion = pLCEvent->getCollection(m_MarlinTrkTracksPION);

     	for (unsigned int i = 0, nElements = pLCCollectionPion->getNumberOfElements(); i < nElements; ++i)
		{
			Track *pionTrack = dynamic_cast<EVENT::Track*>(pLCCollectionPion->getElementAt(i));

			if (NULL == pionTrack)
			throw EVENT::Exception("Collection type mismatch");

//			if (!pMCParticle->getParents().empty())
//				continue;

		}
	}
     catch (...)
     {
		streamlog_out(WARNING) << "Could not extract track collection for using pion mass " << std::endl;
     }
}


void MyTrackParameters::FindTrackParameters(EVENT::LCEvent *pLCEvent)
{
	try
	{
		const EVENT::LCCollection *mcpCollection = pLCEvent->getCollection(m_mcParticleCollection);
		const EVENT::LCCollection *trkCollection = pLCEvent->getCollection(m_MarlinTrkTracks);
		const EVENT::LCCollection *trkCollectionPion = pLCEvent->getCollection(m_MarlinTrkTracksPION);
		const EVENT::LCCollection *trkCollectionKaon = pLCEvent->getCollection(m_MarlinTrkTracksKAON);
		const EVENT::LCCollection *trkCollectionMuon = pLCEvent->getCollection(m_MarlinTrkTracksMUON);
		const EVENT::LCCollection *trkCollectionElectron = pLCEvent->getCollection(m_MarlinTrkTracksELECTRON);
		const EVENT::LCCollection *trkCollectionProton = pLCEvent->getCollection(m_MarlinTrkTracksPROTON);
		const EVENT::LCCollection *relCollection = pLCEvent->getCollection(m_TrackMCParticleRelCol);

		LCRelationNavigator mc2trackNav(pLCEvent->getCollection( m_TrackMCParticleRelCol ));
		streamlog_out(DEBUG) << " got mc2trackNav from " << mc2trackNav.getFromType() << " to " << mc2trackNav.getToType() << std::endl;

		for (unsigned int i = 0, ntrks = trkCollection->getNumberOfElements(); i < ntrks; ++i)
		{
			auto origTrack = dynamic_cast<EVENT::Track*>(trkCollection->getElementAt(i));
			Track *trueTrack;// = dynamic_cast<EVENT::Track*>(trkCollection->getElementAt(i));
			const EVENT::LCObjectVec& mcpvec = mc2trackNav.getRelatedToObjects(origTrack);
			const EVENT::FloatVec&  trackweightvec = mc2trackNav.getRelatedToWeights(origTrack);

			double maxweight = 0.;
			int imcpmax = 0;
			for ( unsigned int imcp = 0; imcp < mcpvec.size(); imcp++ )
			{
				if ( trackweightvec.at(imcp) > maxweight )
				{
					maxweight = trackweightvec.at(imcp);
					imcpmax = imcp;
				}
			}
			m_highest_weight.push_back(maxweight);
			streamlog_out(DEBUG) << " ===> MCParticle with max weight for track " << i << " is " << imcpmax << std::endl ;
			MCParticle *mcpLinked = (MCParticle *) mcpvec.at(imcpmax);
			m_trk_genStat.push_back(mcpLinked->getGeneratorStatus());
			int trk_PDG = mcpLinked->getPDG();
			m_trk_pdg.push_back(trk_PDG);
			float trk_charge = mcpLinked->getCharge();
			m_trk_charge.push_back(trk_charge);
			streamlog_out(DEBUG) << " ===> PDG Code of MCParticle with max weight for track " << i << " is " << mcpLinked->getPDG() << std::endl ;
			HelixClass helix;
			float pos[3] ;
			pos[0] = mcpLinked->getVertex()[0] ;
			pos[1] = mcpLinked->getVertex()[1] ;
			pos[2] = mcpLinked->getVertex()[2] ;
			float mom[3] ;
			mom[0] = mcpLinked->getMomentum()[0] ;
			mom[1] = mcpLinked->getMomentum()[1] ;
			mom[2] = mcpLinked->getMomentum()[2] ;


			gear::Vector3D p2( mcpLinked->getMomentum()[0], mcpLinked->getMomentum()[1], mcpLinked->getMomentum()[2] );
			float q = mcpLinked->getCharge() ;
			helix.Initialize_VP( pos , mom, q,  _bField ) ;
			float momentum = std::sqrt(pow(mom[0],2)+pow(mom[1],2)+pow(mom[2],2));
			m_mcp_momentum.push_back(momentum);

			double d0mcp = helix.getD0() ;
			double ommcp = helix.getOmega() ;
			double phmcp = helix.getPhi0() ;
			double tLmcp = helix.getTanLambda() ;
			double z0mcp = helix.getZ0() ;

			m_mcp_d0.push_back(d0mcp);
			m_mcp_Omega.push_back(ommcp);
			m_mcp_Phi.push_back(phmcp);
			m_mcp_tanLambda.push_back(tLmcp);
			m_mcp_z0.push_back(z0mcp);

			if (std::abs(trk_PDG) == 11)
			{
				trueTrack = dynamic_cast<EVENT::Track*>(trkCollectionElectron->getElementAt(i));
			}
			else if (std::abs(trk_PDG) == 13)
			{
				trueTrack = dynamic_cast<EVENT::Track*>(trkCollectionMuon->getElementAt(i));
			}
			else if (std::abs(trk_PDG) == 321)
			{
				trueTrack = dynamic_cast<EVENT::Track*>(trkCollectionKaon->getElementAt(i));
			}
			else if (std::abs(trk_PDG) == 2212)
			{
				trueTrack = dynamic_cast<EVENT::Track*>(trkCollectionProton->getElementAt(i));
			}
			else
			{
				trueTrack = dynamic_cast<EVENT::Track*>(trkCollection->getElementAt(i));
			}

			float rec_d0_pion_mass = origTrack->getD0();
			float rec_Omega_pion_mass = origTrack->getOmega();
			float rec_Phi_pion_mass = origTrack->getPhi();
			float rec_tanLambda_pion_mass = origTrack->getTanLambda();
			float rec_z0_pion_mass = origTrack->getZ0();
			m_rec_d0_pion_mass.push_back(rec_d0_pion_mass);
			m_rec_Omega_pion_mass.push_back(rec_Omega_pion_mass);
			m_rec_Phi_pion_mass.push_back(rec_Phi_pion_mass);
			m_rec_tanLambda_pion_mass.push_back(rec_tanLambda_pion_mass);
			m_rec_z0_pion_mass.push_back(rec_z0_pion_mass);

			float rec_d0_true_mass = trueTrack->getD0();
			float rec_Omega_true_mass = trueTrack->getOmega();
			float rec_Phi_true_mass = trueTrack->getPhi();
			float rec_tanLambda_true_mass = trueTrack->getTanLambda();
			float rec_z0_true_mass = trueTrack->getZ0();
			m_rec_d0_true_mass.push_back(rec_d0_true_mass);
			m_rec_Omega_true_mass.push_back(rec_Omega_true_mass);
			m_rec_Phi_true_mass.push_back(rec_Phi_true_mass);
			m_rec_tanLambda_true_mass.push_back(rec_tanLambda_true_mass);
			m_rec_z0_true_mass.push_back(rec_z0_true_mass);

			float residual_d0_pion_mass = rec_d0_pion_mass - d0mcp;
			float residual_Omega_pion_mass = rec_Omega_pion_mass - ommcp;
			float residual_Phi_pion_mass = rec_Phi_pion_mass - phmcp;
			float residual_tanLambda_pion_mass = rec_tanLambda_pion_mass - tLmcp;
			float residual_z0_pion_mass = rec_z0_pion_mass - z0mcp;
			m_residual_d0_pion_mass.push_back(residual_d0_pion_mass);
			m_residual_Omega_pion_mass.push_back(residual_Omega_pion_mass);
			m_residual_Phi_pion_mass.push_back(residual_Phi_pion_mass);
			m_residual_tanLambda_pion_mass.push_back(residual_tanLambda_pion_mass);
			m_residual_z0_pion_mass.push_back(residual_z0_pion_mass);

			float residual_d0_true_mass = rec_d0_true_mass - d0mcp;
			float residual_Omega_true_mass = rec_Omega_true_mass - ommcp;
			float residual_Phi_true_mass = rec_Phi_true_mass - phmcp;
			float residual_tanLambda_true_mass = rec_tanLambda_true_mass - tLmcp;
			float residual_z0_true_mass = rec_z0_true_mass - z0mcp;
			m_residual_d0_true_mass.push_back(residual_d0_true_mass);
			m_residual_Omega_true_mass.push_back(residual_Omega_true_mass);
			m_residual_Phi_true_mass.push_back(residual_Phi_true_mass);
			m_residual_tanLambda_true_mass.push_back(residual_tanLambda_true_mass);
			m_residual_z0_true_mass.push_back(residual_z0_true_mass);

			float uncertainty_d0_pion_mass = sqrt(origTrack->getCovMatrix()[0]);
			float uncertainty_Omega_pion_mass = sqrt(origTrack->getCovMatrix()[5]);
			float uncertainty_Phi_pion_mass = sqrt(origTrack->getCovMatrix()[2]);
			float uncertainty_tanLambda_pion_mass = sqrt(origTrack->getCovMatrix()[14]);
			float uncertainty_z0_pion_mass = sqrt(origTrack->getCovMatrix()[9]);
			m_uncertainty_d0_pion_mass.push_back(uncertainty_d0_pion_mass);
			m_uncertainty_Omega_pion_mass.push_back(uncertainty_Omega_pion_mass);
			m_uncertainty_Phi_pion_mass.push_back(uncertainty_Phi_pion_mass);
			m_uncertainty_tanLambda_pion_mass.push_back(uncertainty_tanLambda_pion_mass);
			m_uncertainty_z0_pion_mass.push_back(uncertainty_z0_pion_mass);

			float uncertainty_d0_true_mass = sqrt(trueTrack->getCovMatrix()[0]);
			float uncertainty_Omega_true_mass = sqrt(trueTrack->getCovMatrix()[5]);
			float uncertainty_Phi_true_mass = sqrt(trueTrack->getCovMatrix()[2]);
			float uncertainty_tanLambda_true_mass = sqrt(trueTrack->getCovMatrix()[14]);
			float uncertainty_z0_true_mass = sqrt(trueTrack->getCovMatrix()[9]);
			m_uncertainty_d0_true_mass.push_back(uncertainty_d0_true_mass);
			m_uncertainty_Omega_true_mass.push_back(uncertainty_Omega_true_mass);
			m_uncertainty_Phi_true_mass.push_back(uncertainty_Phi_true_mass);
			m_uncertainty_tanLambda_true_mass.push_back(uncertainty_tanLambda_true_mass);
			m_uncertainty_z0_true_mass.push_back(uncertainty_z0_true_mass);

			float pull_d0_pion_mass = residual_d0_pion_mass / uncertainty_d0_pion_mass;
			float pull_Omega_pion_mass = residual_Omega_pion_mass / uncertainty_Omega_pion_mass;
			float pull_Phi_pion_mass = residual_Phi_pion_mass / uncertainty_Phi_pion_mass;
			float pull_tanLambda_pion_mass = residual_tanLambda_pion_mass / uncertainty_tanLambda_pion_mass;
			float pull_z0_pion_mass = residual_z0_pion_mass / uncertainty_z0_pion_mass;
			m_pull_d0_pion_mass.push_back(pull_d0_pion_mass);
			m_pull_Omega_pion_mass.push_back(pull_Omega_pion_mass);
			m_pull_Phi_pion_mass.push_back(pull_Phi_pion_mass);
			m_pull_tanLambda_pion_mass.push_back(pull_tanLambda_pion_mass);
			m_pull_z0_pion_mass.push_back(pull_z0_pion_mass);

			float pull_d0_true_mass = residual_d0_true_mass / uncertainty_d0_true_mass;
			float pull_Omega_true_mass = residual_Omega_true_mass / uncertainty_Omega_true_mass;
			float pull_Phi_true_mass = residual_Phi_true_mass / uncertainty_Phi_true_mass;
			float pull_tanLambda_true_mass = residual_tanLambda_true_mass / uncertainty_tanLambda_true_mass;
			float pull_z0_true_mass = residual_z0_true_mass / uncertainty_z0_true_mass;
			m_pull_d0_true_mass.push_back(pull_d0_true_mass);
			m_pull_Omega_true_mass.push_back(pull_Omega_true_mass);
			m_pull_Phi_true_mass.push_back(pull_Phi_true_mass);
			m_pull_tanLambda_true_mass.push_back(pull_tanLambda_true_mass);
			m_pull_z0_true_mass.push_back(pull_z0_true_mass);

			m_chi2.push_back(trueTrack->getChi2());
			m_ndf.push_back(trueTrack->getNdf());
			if (trueTrack->getNdf()!=0)
			{
				m_chi2_ndf.push_back(trueTrack->getChi2()/trueTrack->getNdf());
			}
		}
	}
     catch (...)
     {
		streamlog_out(WARNING) << "Could not extract track collection for using pion mass " << std::endl;
     }
}
