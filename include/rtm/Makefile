CXXFLAGS=-I..



all: DataFlowComponentBase ComponentActionInterface DataFlowComponentActionInterface DataFlowComponentInterface ExecutionContextInterface FsmInterface FsmObjectInterface FsmParticipantActionInterface FsmParticipantInterface FsmServiceInterface LightweightRTObjectInterface ModeCapableInterface ModeInterface MultiModeComponentActionInterface PortServiceInterface RTObjectInterface 

.h:
	$(CXX) $(CXXFLAGS) $<
	rm -f $<.gch
	rm -f *~
