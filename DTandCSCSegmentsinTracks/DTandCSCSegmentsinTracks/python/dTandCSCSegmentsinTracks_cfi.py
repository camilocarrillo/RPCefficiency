import FWCore.ParameterSet.Config as cms

dTandCSCSegmentsinTracks = cms.EDProducer("DTandCSCSegmentsinTracks",
                                          cscSegments = cms.InputTag("hltCscSegments"),
                                          dt4DSegments = cms.InputTag('dt4DSegments'),
                                          tracks = cms.InputTag("standAloneMuons","UpdatedAtVtx"),
                                          MuonTimeMapLabel = cms.InputTag("staUpdAtVtx", "combined"),
                                          #MuonRpcTimeMapLabel = cms.InputTag("staRegular", "rpc"),
                                          timingCutValue = cms.untracked.double(10),
                                          timingErrorCutValue = cms.untracked.double(1),
                                          ptCutValue = cms.untracked.double(5),
                                          )
