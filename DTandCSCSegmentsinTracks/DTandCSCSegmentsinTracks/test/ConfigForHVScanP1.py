# The following comments couldn't be translated into the new config version:

#keep the logging output to a nice level

import FWCore.ParameterSet.Config as cms

process = cms.Process("OwnParticles")



process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.CSCGeometry.cscGeometry_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")
process.load("DQMServices.Components.MEtoEDMConverter_cfi")
process.load("DQMServices.Core.DQM_cfg")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = 'MC_31X_V1::All'


process.load("MuonTools.StandardSequences.RecoStandAloneMuon_cff")

# have stareco use hlt digis
process.load("MuonTools.Configuration.HltMuonDigis_cff")
# have stareco use hlt segments (1)
process.load("MuonTools.Configuration.HltMuonSegments_cff")
# keep stareco from using rpcs
process.load("MuonTools.Configuration.StandAloneNoRpc_cff")





process.GlobalTag.globaltag = 'GR_P_V32::All'#START50_V14::All'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/0255BB88-1981-E111-9A55-003048D2C16E.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/12B8A00A-1C81-E111-8DD5-E0CB4E55365D.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/26BE7DB6-0F81-E111-A2FF-0025901D6288.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/28BE4FB1-1381-E111-89C9-003048D2BC42.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/2CB301BC-1281-E111-8A76-0030486780B4.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/2E70BC4D-2081-E111-BC95-485B3977172C.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/38A074CD-1281-E111-AADE-003048F11CF0.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/3C1E4EFA-1681-E111-8F38-0025B32034EA.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/46BB8A0E-1581-E111-862A-485B3977172C.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/48996B09-1381-E111-88ED-0025901D5D80.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/4A37F0E7-1E81-E111-B67D-001D09F29619.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/5EC0BEF8-1581-E111-B2A0-0025901D624E.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/68C7526E-1481-E111-9EF3-5404A63886B0.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/8C4C26D0-1781-E111-802F-003048D2BB90.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/989388E1-1981-E111-838B-001D09F23D1D.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/9E1EEA3E-1081-E111-A4D8-0025B32034EA.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/9E44F64C-1B81-E111-B317-001D09F24399.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/A49D2221-1181-E111-A534-003048D2C16E.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/A66223B2-2181-E111-8D23-BCAEC5329720.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/A87F8301-2181-E111-B7D4-BCAEC5364C93.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/B0587414-2881-E111-8832-001D09F23174.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/B0A5D54A-1681-E111-BE93-003048D2BBF0.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/BE232B20-1E81-E111-B951-003048F024DE.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/C2CE1D8C-1A81-E111-B297-001D09F2512C.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/DA89094F-2081-E111-8A00-BCAEC518FF40.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/DE004CEB-1181-E111-92EA-BCAEC518FF5F.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/F2273F66-1D81-E111-9044-003048F024FE.root',
  'rfio:/castor/cern.ch/cms/store/data/Run2012A/RPCMonitor/RAW/v1/000/190/661/F69ECAF8-1581-E111-ACAD-0025901D627C.root'
    )
)


import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = '/afs/cern.ch/user/j/jgomezca/CMSSW_5_2_3_patch3/src/DTandCSCSegmentsinTracks/DTandCSCSegmentsinTracks/test/hvScan2012_P1.json').getVLuminosityBlockRange()


process.dTandCSCSegmentsinTracks = cms.EDProducer("DTandCSCSegmentsinTracks",
                                                  cscSegments = cms.InputTag("hltCscSegments"),
                                                  dt4DSegments = cms.InputTag("hltDt4DSegments"),
                                                  tracks = cms.InputTag("standAloneMuons","UpdatedAtVtx")
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
    rpcRecHits = cms.InputTag("hltRpcRecHits"),



    rpcDTPoints = cms.InputTag("rpcPointProducer","RPCDTExtrapolatedPoints"),
    rpcCSCPoints = cms.InputTag("rpcPointProducer","RPCCSCExtrapolatedPoints"),

    EffSaveRootFile = cms.untracked.bool(True),
    EffRootFileName = cms.untracked.string('/tmp/jgomezca/hvscanP1.root'),
    EffSaveRootFileEventsInterval = cms.untracked.int32(100)
)

process.normfilter = cms.EDFilter("HLTHighLevel",
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    HLTPaths = cms.vstring("AlCa_RPCMuonNormalisation*"),
    eventSetupPathsKey = cms.string(''),
    andOr = cms.bool(True),
    throw = cms.bool(True)
)

process.load("TriggerFilter.TriggerFilter.triggerFilter_cfi")



process.p = cms.Path(process.normfilter*process.triggerFilter*process.muonstandalonereco*process.dTandCSCSegmentsinTracks*process.rpcPointProducer*process.museg)

process.DQM.collectorHost = ''
process.DQM.collectorPort = 9090
process.DQM.debug = False


