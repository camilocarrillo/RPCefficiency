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
    fileName = cms.untracked.string('/tmp/carrillo/eff277420.root'),
    fileOut = cms.untracked.string('/tmp/carrillo/seceff277420.root'),

    BlackListFile = cms.untracked.string('/afs/cern.ch/user/c/carrillo/RPC/blacklist/blacklist_23may.dat'),

    debug = cms.untracked.bool(True),

    makehtml = cms.untracked.bool(False),
    prodimages = cms.untracked.bool(False),

    statistics = cms.untracked.bool(True),

    threshold = cms.untracked.double(50.0),

    barrel = cms.untracked.bool(True),
    endcap = cms.untracked.bool(True)
)

process.p = cms.Path(process.demo)
