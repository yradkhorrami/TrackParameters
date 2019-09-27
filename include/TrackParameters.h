#ifndef MyTrackParameters_h
#define MyTrackParameters_h 1

#include <marlin/Processor.h>
#include <marlin/Global.h>
#include <marlinutil/HelixClass.h>
#include <marlinutil/GeometryUtil.h>
#include "UTIL/LCRelationNavigator.h"
#include "UTIL/LCIterator.h"
#include "UTIL/Operators.h"
#include <UTIL/BitField64.h>
#include "UTIL/LCTrackerConf.h"
#include <UTIL/ILDConf.h>
#include <UTIL/BitSet32.h>

#include "EVENT/LCStrVec.h"
#include <EVENT/MCParticle.h>
#include <EVENT/Track.h>
#include "IMPL/LCCollectionVec.h"
#include "marlin/Processor.h"
#include "lcio.h"
#include <string>
#include <vector>
#include <math.h>
//#include "CalibrationHelper.h"

#include <set>
#include <vector>

class TFile;
class TH1F;
class TTree;

using namespace lcio ;
using namespace marlin ;

class MyTrackParameters : public Processor {

 public:

  virtual Processor*  newProcessor() { return new MyTrackParameters ; }


  MyTrackParameters() ;

  /** Called at the begin of the job before anything is read.
   * Use to initialize the processor, e.g. book histograms.
   */
  virtual void init() ;

  /** Called for every run.
   */
  virtual void processRunHeader( lcio::LCRunHeader *pLCRunHeader ) ;

  /** Called for every event - the working horse.
   */
  virtual void processEvent( EVENT::LCEvent *pLCEvent ) ;


  virtual void check( EVENT::LCEvent *pLCEvent ) ;

private:

  void Clear();

  void ExtractCollections(EVENT::LCEvent *pLCEvent);
  void FindTrackParameters(EVENT::LCEvent *pLCEvent);

//  void FindTrackParametersAll(EVENT::LCEvent *pLCEvent);


//  void CalculateVisible4Momentum();

  /** Called after data processing for clean up.
   */
virtual void end() ;


 protected:

  /** Input collection name.
   */
	typedef std::vector<float>			FloatVector;
	typedef std::vector<int>			IntVector;


	int						m_nRun{} ;
	int						m_nEvt{} ;
	int						m_nRunSum{};
	int						m_nEvtSum{};


	std::string					m_MarlinTrkTracks{};
	std::string					m_MarlinTrkTracksPION{};
	std::string					m_MarlinTrkTracksKAON{};
	std::string					m_MarlinTrkTracksPROTON{};
	std::string					m_MarlinTrkTracksELECTRON{};
	std::string					m_MarlinTrkTracksMUON{};
	std::string					m_TrackMCParticleRelCol{};
	std::string					m_MCParticleTrackRelCol{};
	std::string					m_mcParticleCollection{};
	std::string					m_col_mcp{};
	std::string					m_rootFile{};

	float						_bField = 0.0;

	IntVector					m_trk_pdg{};
	IntVector					m_trk_genStat{};
	FloatVector					m_highest_weight{};
	FloatVector					m_trk_charge{};
	FloatVector					m_vertex_radius{};
	FloatVector					m_mcp_momentum{};
	FloatVector					m_mcp_d0{};
	FloatVector					m_rec_d0_pion_mass{};
	FloatVector					m_rec_d0_true_mass{};
	FloatVector					m_mcp_Omega{};
	FloatVector					m_rec_Omega_pion_mass{};
	FloatVector					m_rec_Omega_true_mass{};
	FloatVector					m_mcp_Phi{};
	FloatVector					m_rec_Phi_pion_mass{};
	FloatVector					m_rec_Phi_true_mass{};
	FloatVector					m_mcp_tanLambda{};
	FloatVector					m_rec_tanLambda_pion_mass{};
	FloatVector					m_rec_tanLambda_true_mass{};
	FloatVector					m_mcp_z0{};
	FloatVector					m_rec_z0_pion_mass{};
	FloatVector					m_rec_z0_true_mass{};
	FloatVector					m_residual_d0_pion_mass{};
	FloatVector					m_residual_Omega_pion_mass{};
	FloatVector					m_residual_Phi_pion_mass{};
	FloatVector					m_residual_tanLambda_pion_mass{};
	FloatVector					m_residual_z0_pion_mass{};
	FloatVector					m_uncertainty_d0_pion_mass{};
	FloatVector					m_uncertainty_Omega_pion_mass{};
	FloatVector					m_uncertainty_Phi_pion_mass{};
	FloatVector					m_uncertainty_tanLambda_pion_mass{};
	FloatVector					m_uncertainty_z0_pion_mass{};
	FloatVector					m_pull_d0_pion_mass{};
	FloatVector					m_pull_Omega_pion_mass{};
	FloatVector					m_pull_Phi_pion_mass{};
	FloatVector					m_pull_tanLambda_pion_mass{};
	FloatVector					m_pull_z0_pion_mass{};

	FloatVector					m_residual_d0_true_mass{};
	FloatVector					m_residual_Omega_true_mass{};
	FloatVector					m_residual_Phi_true_mass{};
	FloatVector					m_residual_tanLambda_true_mass{};
	FloatVector					m_residual_z0_true_mass{};
	FloatVector					m_uncertainty_d0_true_mass{};
	FloatVector					m_uncertainty_Omega_true_mass{};
	FloatVector					m_uncertainty_Phi_true_mass{};
	FloatVector					m_uncertainty_tanLambda_true_mass{};
	FloatVector					m_uncertainty_z0_true_mass{};
	FloatVector					m_pull_d0_true_mass{};
	FloatVector					m_pull_Omega_true_mass{};
	FloatVector					m_pull_Phi_true_mass{};
	FloatVector					m_pull_tanLambda_true_mass{};
	FloatVector					m_pull_z0_true_mass{};

	IntVector					m_ndf{};
	FloatVector					m_chi2{};
	FloatVector					m_chi2_ndf{};


	TFile						*m_pTFile{};
	TTree						*m_pTTree{};
	TH1F						*m_hPfoEnergySum{};
	TH1F						*m_hPfoEnergySumL7A{};

} ;

#endif
