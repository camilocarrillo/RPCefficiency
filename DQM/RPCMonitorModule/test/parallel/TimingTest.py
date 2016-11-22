

import FWCore.ParameterSet.Config as cms
process = cms.Process("OwnParticles")
#process = cms.Process("RECO")

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
   fileNames = cms.untracked.vstring(#'/store/data/Run2016E/RPCMonitor/RAW/v2/000/277/420/00000/04EEBC38-B052-E611-972D-02163E013587.root')
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/10BEC880-5F32-E611-872C-02163E0142BA.root',
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/1CA7B675-5F32-E611-A757-02163E013754.root',
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/26CCB6A5-5F32-E611-9D5D-02163E01411D.root',
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/320E2670-5F32-E611-A3D1-02163E01368B.root',
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/48195061-5F32-E611-AC8E-02163E01399A.root',
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/5E7C9769-5F32-E611-8F64-02163E0123FA.root',
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/98B32665-5932-E611-95DA-02163E011E30.root',
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/A0AC405D-5F32-E611-BAB5-02163E011B04.root',
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/B02EB961-5F32-E611-9A41-02163E0123D6.root',
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/BAE8B262-5F32-E611-A498-02163E01388F.root',
        '/store/data/Run2016B/RPCMonitor/RAW/v2/000/275/059/00000/FEF3866C-5F32-E611-9E3E-02163E012B20.root')

)

process.dTandCSCSegmentsinTracks = cms.EDProducer("DTandCSCSegmentsinTracks",
                                                  cscSegments = cms.untracked.InputTag("hltCscSegments"),
                                                  dt4DSegments = cms.untracked.InputTag("hltDt4DSegments"),
                                                  tracks = cms.untracked.InputTag("standAloneMuons",""),
                                                  MuonTimeMapLabel = cms.InputTag("staRegular", "combined"),
                                                  ptCutValue = cms.untracked.double(5),
                                                  timingCutValue = cms.untracked.double(10),
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
    timingCutValue = cms.untracked.double(10.),

    incldt = cms.untracked.bool(True),
    incldtMB4 = cms.untracked.bool(True),
    inclcsc = cms.untracked.bool(True),

    debug = cms.untracked.bool(False),
    inves = cms.untracked.bool(True),
    
    DuplicationCorrection = cms.untracked.int32(1),

    manualalignment = cms.untracked.bool(False),
    AliFileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/endcap/CMSSW_3_0_0_pre10/src/DQM/RPCMonitorModule/data/Alignment69912.dat'),

    rangestrips = cms.untracked.double(4.),

    cscSegments = cms.untracked.InputTag('hltCscSegments'),
    dt4DSegments = cms.untracked.InputTag('hltDt4DSegments'),
    rpcRecHits = cms.untracked.InputTag("hltRpcRecHits"),



    rpcDTPoints = cms.untracked.InputTag("rpcPointProducer","RPCDTExtrapolatedPoints"),
    rpcCSCPoints = cms.untracked.InputTag("rpcPointProducer","RPCCSCExtrapolatedPoints"),

    EffSaveRootFile = cms.untracked.bool(True),
    EffRootFileName = cms.untracked.string('output.root'),
    #EffRootFileName = cms.untracked.string('/tmp/federica/eff04EEBC38-B052-E611-972D-02163E013587.root'),
    #EffRootFileName = cms.untracked.string('/tmp/federica/Filtered_effRun2016B_275059.root'),
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

#federica
#process.out = cms.OutputModule("PoolOutputModule",
 #                              fileName = cms.untracked.string("FedeTest.root"))


process.p = cms.Path(process.normfilter*process.muonstandalonereco*process.standAloneTiming*process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)
#process.e = cms.EndPath(process.out)



f = file('outfile', 'w')
f.write(process.dumpPython())
f.close()
