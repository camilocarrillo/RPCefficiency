

import FWCore.ParameterSet.Config as cms
process = cms.Process("OwnParticles")

process.load("Configuration.StandardSequences.GeometryRecoDB_cff")
process.load("Configuration.StandardSequences.GeometryDB_cff")

#process.load('Configuration.Geometry.GeometryExtended2015Reco_cff')
#process.load('Configuration.Geometry.GeometryExtended2015_cff')
#process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
#process.load("Geometry.CSCGeometry.cscGeometry_cfi")
#process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")
process.load("DQMServices.Components.MEtoEDMConverter_cfi")
process.load("DQMServices.Core.DQM_cfg")
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#from Configuration.AlCa.autoCond import autoCond
#process.GlobalTag.globaltag = autoCond['mc']
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")
process.GlobalTag.globaltag = "80X_dataRun2_Express_v1"


# do Stand Alone Muon reconstruction
# ----------------------------------
# in RPCMonitor files there are     
# - no StandAloneMuons reconstructed
# - only Rechits and Segments are   
#   reconstructed (RecoLocalMuon)   
# ----------------------------------
process.load("MuonTools.StandardSequences.RecoStandAloneMuon_cff")
# have stareco use hlt digis
# (change all input tags in offline reco config to use hlt tags)
process.load("MuonTools.Configuration.HltMuonDigis_cff")
# have stareco use hlt segments (1)
# (change all input tags in offline reco config to use hlt tags)
process.load("MuonTools.Configuration.HltMuonSegments_cff")
# keep stareco from using rpcs
process.load("MuonTools.Configuration.StandAloneNoRpc_cff")
# do we need this?
# process.load("RecoTracker.IterativeTracking.MuonSeededStep_cff")
# process.load("RecoTracker.CkfPattern.GroupedCkfTrajectoryBuilder_cfi")
# import RecoTracker.CkfPattern.GroupedCkfTrajectoryBuilder_cfi         
process.load("RecoTracker.CkfPattern.GroupedCkfTrajectoryBuilder_cff")
#timing producer
process.load("STASkim.ProducerTest.standAloneTiming_cff")



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring('-input-')
)

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/user/c/carrillo/efficiency/CMSSW_9_0_0/src/DQM/RPCMonitorModule/test/parallel/data_collisions17_295340_295655_json.txt').getVLuminosityBlockRange()



process.dTandCSCSegmentsinTracks = cms.EDProducer("DTandCSCSegmentsinTracks",
                                                  cscSegments = cms.untracked.InputTag("hltCscSegments"),
                                                  #dt4DSegments = cms.untracked.InputTag("hltDt4DSegments"),
                                                  dt4DSegments = cms.untracked.InputTag("dt4DSegments"),
                                                  tracks = cms.untracked.InputTag("standAloneMuons",""),
                                                  MuonTimeMapLabel = cms.InputTag("staRegular", "combined"),
                                                  ptCutValue = cms.untracked.double(0),
                                                  timingCutValue = cms.untracked.double(5),
                                                  timingErrorCutValue = cms.untracked.double(1)
                                                  )


process.rpcPointProducer = cms.EDProducer('RPCPointProducer',
  incldt = cms.untracked.bool(True),
  inclcsc = cms.untracked.bool(True),
  incltrack =  cms.untracked.bool(False),

  debug = cms.untracked.bool(False),

  rangestrips = cms.untracked.double(4.),
  rangestripsRB4 = cms.untracked.double(4.),
  MinCosAng = cms.untracked.double(0.85),
  MaxD = cms.untracked.double(80.0),
  MaxDrb4 = cms.untracked.double(150.0),
  ExtrapolatedRegion = cms.untracked.double(0.6), #in stripl/2 in Y and stripw*nstrips/2 in X
  cscSegments = cms.InputTag('dTandCSCSegmentsinTracks','SelectedCscSegments','OwnParticles'),
  dt4DSegments = cms.InputTag('dTandCSCSegmentsinTracks','SelectedDtSegments','OwnParticles'),
  tracks = cms.InputTag("standAloneMuons"),
  TrackTransformer = cms.PSet(
      DoPredictionsOnly = cms.bool(False),
      Fitter = cms.string('KFFitterForRefitInsideOut'),
      TrackerRecHitBuilder = cms.string('WithTrackAngle'),
      Smoother = cms.string('KFSmootherForRefitInsideOut'),
      MuonRecHitBuilder = cms.string('MuonRecHitBuilder'),
      RefitDirection = cms.string('alongMomentum'),
      RefitRPCHits = cms.bool(False),
      Propagator = cms.string('SmartPropagatorAnyRKOpposite')
  )
)

process.museg = cms.EDAnalyzer("MuonSegmentEff",

    MuonCollectionLabel = cms.InputTag("standAloneMuons"),
    MuonTimeMapLabel = cms.InputTag("staRegular", "combined"),
    MuonRpcTimeMapLabel = cms.InputTag("staRegular", "rpc"),
    MuonDtTimeMapLabel = cms.InputTag("staRegular", "dt"),
    MuonCscTimeMapLabel = cms.InputTag("staRegular", "csc"),

    timingCutValue = cms.untracked.double(5.),
    timingErrorCutValue = cms.untracked.double(1.),

    incldt = cms.untracked.bool(True),
    incldtMB4 = cms.untracked.bool(True),
    inclcsc = cms.untracked.bool(True),

    debug = cms.untracked.bool(False),
    inves = cms.untracked.bool(True),
    
    clsCutValue = cms.untracked.int32(3),

    DuplicationCorrection = cms.untracked.int32(1),

    manualalignment = cms.untracked.bool(True),
    AliFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/efficiency/timing/CMSSW_8_0_1/src/DQM/RPCMonitorModule/test/alignment_2016B.dat'),

	
    rangestrips = cms.untracked.double(4.),

    selectedcscSegments = cms.untracked.InputTag('dTandCSCSegmentsinTracks','SelectedCscSegments','OwnParticles'),
    selecteddt4DSegments = cms.untracked.InputTag('dTandCSCSegmentsinTracks','SelectedDtSegments','OwnParticles'),

    cscSegments = cms.untracked.InputTag('hltCscSegments'),
    #dt4DSegments = cms.untracked.InputTag('hltDt4DSegments'),
    dt4DSegments = cms.untracked.InputTag('dt4DSegments'),

    rpcRecHits = cms.untracked.InputTag("hltRpcRecHits"),

    rpcDTPoints = cms.untracked.InputTag("rpcPointProducer","RPCDTExtrapolatedPoints"),
    rpcCSCPoints = cms.untracked.InputTag("rpcPointProducer","RPCCSCExtrapolatedPoints"),

    EffSaveRootFile = cms.untracked.bool(True),
    EffRootFileName = cms.untracked.string('-output-'),
    EffSaveRootFileEventsInterval = cms.untracked.int32(100)
)
process.normfilter = cms.EDFilter("HLTHighLevel",
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    HLTPaths = cms.vstring("AlCa_RPCMuonNormalisation*"),
    eventSetupPathsKey = cms.string(''),
    andOr = cms.bool(True),
    throw = cms.bool(True)
)

process.triggerFilter = cms.EDFilter('TriggerFilter',
                        gtDigis = cms.InputTag('hltGtDigis')
                        #gtDigis = cms.untracked.InputTag('gtDigis')
)


#process.p = cms.Path(process.normfilter*process.triggerFilter*process.muonstandalonereco*process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)#Trigger Filter needs to be updated!!!!!!!!!

#process.p = cms.Path(process.normfilter*process.muonstandalonereco*process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)

#process.p = cms.Path(process.normfilter*process.muonstandalonereco*process.standAloneTiming*process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)

process.p = cms.Path(process.normfilter*process.dtlocalreco*process.muonstandalonereco*process.standAloneTiming*process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)
