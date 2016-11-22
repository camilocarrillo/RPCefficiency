import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('file:/afs/cern.ch/work/f/federica/RPC/CMSSW_8_0_1/src/DQM/RPCMonitorModule/test/parallel/FedeTest.root')
                            
                            #'/store/data/Run2016E/RPCMonitor/RAW/v2/000/277/420/00000/04EEBC38-B052-E611-972D-02163E013587.root')
                            )

process.maxEvents = cms.untracked.PSet(
	input=cms.untracked.int32(100)
)

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_PostLS1_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.GlobalTag.globaltag = "80X_dataRun2_Express_v1"

process.load("Configuration.StandardSequences.Reconstruction_cff")
from Configuration.StandardSequences.Reconstruction_cff import *

process.load("STASkim.ProducerTest.standAloneTiming_cff")
from STASkim.ProducerTest.standAloneTiming_cff import *

process.muonAnalyzer = cms.EDAnalyzer("MuonTimingValidator",
  #TKtracks = cms.untracked.InputTag("generalTracks"),
  #STAtracks = cms.untracked.InputTag("standAloneMuons"),
  Muons = cms.untracked.InputTag("standAloneMuons"),
  TKtracks = cms.untracked.InputTag("standAloneMuons"),
  nbins = cms.int32(60),
  PtresMax = cms.double(2000.0),
  CombinedTiming = cms.untracked.InputTag("muontiming","combined"),
  DtTiming = cms.untracked.InputTag("muontiming","dt"),
  CscTiming = cms.untracked.InputTag("muontiming","csc"),
  simPtMin = cms.double(5.0),
  PtresMin = cms.double(-1000.0),
  PtCut = cms.double(1.0),
  etaMax = cms.double(2.4),
  etaMin = cms.double(0.0),
  PlotScale = cms.double(1.0),
  DTcut  = cms.int32(8),
  CSCcut = cms.int32(4),
  open = cms.string('recreate'),
  out = cms.string('test_timing.root')
)

#process.prefer("GlobalTag")
#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Prompt_v9', '')

#process.p = cms.Path(standAloneTiming)

process.p = cms.Path(staRegular)
process.mutest = cms.Path(process.muonAnalyzer)

#process.schedule = cms.Schedule(process.p,process.mutest)	
process.schedule = cms.Schedule(process.mutest)
