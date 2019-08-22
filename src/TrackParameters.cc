#include "TrackParameters.h"
#include <iostream>

#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/LCParameters.h>

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

TrackParameters aTrackParameters;

MySLDecayFinder::MySLDecayFinder() :
	Processor("SLDecayFinder"),
	m_nRun(0),
	m_nEvt(0),
	m_nRunSum(0),
	m_nEvtSum(0),
	m_pTFile(NULL),
	m_pTTree(NULL)


{

    // modify processor description
    _description = "MySLDecayFinder finds semi-leptonic decays inside jets" ;


    // register steering parameters: name, description, class-variable, default value
	registerInputCollection( LCIO::MCPARTICLE,
          				"MCParticleCollection" ,
          				"Name of the MCParticle collection"  ,
          				m_mcParticleCollection,
          				std::string("MCParticle")
    					);

	registerProcessorParameter(	"RootFile",
							"Name of the output root file",
							m_rootFile,
							std::string("MySLDecayFinder.root")
							);

	registerProcessorParameter(	"n_BSLD",
							"Number of B-Hadron SemiLeptonic Deacys",
							m_nSLDecayBHad,
							int(0)
							);

}



void MySLDecayFinder::init()
{

    streamlog_out(DEBUG) << "   init called  " << std::endl ;

    // usually a good idea to
    printParameters() ;

	m_nRun = 0 ;
	m_nEvt = 0 ;
	m_nRunSum = 0;
	m_nEvtSum = 0;
	this->Clear();

	m_pTFile = new TFile(m_rootFile.c_str(), "recreate");
	m_pTTree = new TTree("SLDAnalysisTree", "SLDAnalysisTree");
	m_pTTree->SetDirectory(m_pTFile);
	m_pTTree->Branch("run", &m_nRun, "run/I");
	m_pTTree->Branch("event", &m_nEvt, "event/I");

}


void MySLDecayFinder::processRunHeader( LCRunHeader *pLCRunHeader)
{
	m_nRun = 0;
     m_nEvt = 0;
     ++m_nRunSum;

//    m_nRun++ ;
}



void MySLDecayFinder::processEvent( LCEvent *pLCEvent )
{

	m_nRun = pLCEvent->getRunNumber();
     m_nEvt = pLCEvent->getEventNumber();
     ++m_nEvtSum;

	if ((m_nEvtSum % 100) == 0)
         std::cout << " processed events: " << m_nEvtSum << std::endl;

    // New reco particle collection for the semi-leptonic decays

	this->Clear();
	this->ExtractCollections(pLCEvent);
	this->FindSLDecays(pLCEvent);
//	this->CalculateVisible4Momentum();
	m_pTTree->Fill();
}

void MySLDecayFinder::check( LCEvent *pLCEvent )
{
    // nothing to check here - could be used to fill checkplots in reconstruction processor
}


void MySLDecayFinder::end()
{

	m_pTFile->cd();
     m_pTTree->Write();
	m_pTFile->Close();
     delete m_pTFile;

    //   std::cout << "MySLDecayFinder::end()  " << name()
    // 	    << " processed " << _nEvt << " events in " << _nRun << " runs "
    // 	    << std::endl ;

}

void MySLDecayFinder::Clear()
{

	m_EnergyCOM = 0.f;
	m_nSLDecayTotal = 0;
	m_nSLDecayBHad = 0;
	m_nSLDecayCHad = 0;
	m_Hadron_E = 0;
	m_Hadron_px = 0;
	m_Hadron_py = 0;
	m_Hadron_pz = 0;
	m_E_vis = 0;
	m_px_vis = 0;
	m_py_vis = 0;
	m_pz_vis = 0;
	m_SLD_vertex_x = 0;
	m_SLD_vertex_y = 0;
	m_SLD_vertex_z = 0;
	m_mcEnergyELep = 0.f;
//	m_mcEnergyELep.clear();
//	m_mcUnstableParent.clear();
//	m_mcDaughtersVector.clear();
	m_mcEnergyENu = 0.f;
	m_Hadron_mass = 0.f;
	m_Mass_vis = 0.f;
	m_mcNu_px = 0.f;
	m_mcNu_py = 0.f;
	m_mcNu_pz = 0.f;


//	m_mcDaughtersVector.clear();

}

void MySLDecayFinder::ExtractCollections(EVENT::LCEvent *pLCEvent)
{
	try
     {
     	const EVENT::LCCollection *pLCCollection = pLCEvent->getCollection(m_mcParticleCollection);

     	for (unsigned int i = 0, nElements = pLCCollection->getNumberOfElements(); i < nElements; ++i)
		{
			const EVENT::MCParticle *pMCParticle = dynamic_cast<EVENT::MCParticle*>(pLCCollection->getElementAt(i));

			if (NULL == pMCParticle)
			throw EVENT::Exception("Collection type mismatch");

			if (!pMCParticle->getParents().empty())
				continue;

		}
	}
     catch (...)
     {
		streamlog_out(WARNING) << "Could not extract mc particle collection " << m_mcParticleCollection << std::endl;
     }
}


