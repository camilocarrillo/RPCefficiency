import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")
process.load('Configuration.Geometry.GeometryExtended2015Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2015_cff')

process.load("Geometry.RPCGeometry.rpcGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.source = cms.Source("EmptySource")

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1))

process.MessageLogger = cms.Service("MessageLogger")

process.demo = cms.EDAnalyzer("RPCMonitorEfficiency",
    fileName = cms.untracked.string('/afs/cern.ch/user/c/carrillo/workspace/efficiency/_RPCMonitor_Run2016B-v1_RAW/275059/eff275059.root'),
    fileOut = cms.untracked.string('/afs/cern.ch/user/c/carrillo/workspace/efficiency/_RPCMonitor_Run2016B-v1_RAW/275059/sec275059.root'),

    BlackListFile = cms.untracked.string(''),

    debug = cms.untracked.bool(False),

    makehtml = cms.untracked.bool(False),
    prodimages = cms.untracked.bool(False),

    statistics = cms.untracked.bool(False),

    threshold = cms.untracked.double(50.0),

    barrel = cms.untracked.bool(True),
    endcap = cms.untracked.bool(True)
)

process.p = cms.Path(process.demo)
