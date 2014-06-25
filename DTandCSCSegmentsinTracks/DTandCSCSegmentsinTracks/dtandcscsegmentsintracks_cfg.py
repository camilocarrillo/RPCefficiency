import FWCore.ParameterSet.Config as cms

process = cms.Process("TestMuonSegmentsProducer")

process.load("Geometry.MuonCommonData.muonIdealGeometryXML_cfi")
process.load("Geometry.CSCGeometry.cscGeometry_cfi")
process.load("Geometry.DTGeometry.dtGeometry_cfi")
process.load("Geometry.MuonNumbering.muonNumberingInitialization_cfi")

process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.globaltag = "GR_P_V20::All"

process.load("Configuration.StandardSequences.Services_cff")
process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")
process.load("Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100))

process.load("DTandCSCSegmentsinTracks.DTandCSCSegmentsinTracks.dTandCSCSegmentsinTracksMC_cfi")
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('rfio:/castor/cern.ch/user/g/ggeorge/mileva/reco_oldCls/DYToMuMu_M60_RECO_Eta16_oldCLS_1.root')
                            )

process.FEVT = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('/tmp/carrillo/DYToMuMu_M60_RECO_Eta16_oldCLS_1_NewSegments.root')
)

process.p = cms.Path(process.dTandCSCSegmentsinTracks)
process.outpath = cms.EndPath(process.FEVT)


