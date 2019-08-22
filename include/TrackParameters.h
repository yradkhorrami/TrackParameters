#ifndef MyTrackParameters_h
#define MyTrackParameters_h 1

#include "EVENT/LCStrVec.h"
#include <EVENT/MCParticle.h>
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

class MySLDecayFinder : public Processor {

 public:

  virtual Processor*  newProcessor() { return new MySLDecayFinder ; }


  MySLDecayFinder() ;

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

  void FindSLDecays(EVENT::LCEvent *pLCEvent);

//  void CalculateVisible4Momentum();

  /** Called after data processing for clean up.
   */
virtual void end() ;


 protected:

  /** Input collection name.
   */
	std::string 					_colName{} ;

	int						m_nRun{} ;
	int						m_nEvt{} ;
	int						m_nRunSum{};
	int						m_nEvtSum{};

	std::string					m_mcParticleCollection{};
	std::string					m_rootFile{};
	std::string					m_outcolSLDecays{};
	LCCollectionVec*				m_col_SLDecays{};


	int						m_nSLDecayTotal;
	int						m_nSLDecayBHad;
	int						m_nSLDecayCHad;

	double						m_E_vis;
	double						m_px_vis;
	double						m_Mass_vis;
	double						m_mcNu_px;
	double						m_mcNu_py;
	double						m_mcNu_pz;

	TFile						*m_pTFile{};
	TTree						*m_pTTree{};
	TH1F						*m_hPfoEnergySum{};
	TH1F						*m_hPfoEnergySumL7A{};

} ;

#endif
