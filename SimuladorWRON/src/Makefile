#
# OMNeT++/OMNEST Makefile for wron_simulator
#
# This file was generated with the command:
#  opp_makemake -f --deep --nolink -u CMDENV
#

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -IAnalisis \
    -ICoreRouters \
    -IEdgeRouters \
    -INodoControl \
    -INodoControl/Dynamic_WRON \
    -INodoControl/Dynamic_WRON/RwaAlgorithms \
    -INodoControl/WRON \
    -IPaquetesPropios \
    -IRedes

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc and .msg files
OBJS = \
    $O/Analisis/analisis.o \
    $O/CoreRouters/CoreRouter.o \
    $O/EdgeRouters/EdgeRouter.o \
    $O/NodoControl/Estado.o \
    $O/NodoControl/Dynamic_WRON/Control_Dynamic_RWA.o \
    $O/NodoControl/Dynamic_WRON/Dynamic_WRON_Source.o \
    $O/NodoControl/Dynamic_WRON/RwaAlgorithms/Aur_Exhaustive.o \
    $O/NodoControl/WRON/Crea_matriz.o \
    $O/NodoControl/WRON/Decisor.o \
    $O/NodoControl/WRON/Generar_matriz.o \
    $O/NodoControl/WRON/Guente.o \
    $O/NodoControl/WRON/CalculaDelay.o \
    $O/NodoControl/WRON/Controlrwa.o \
    $O/NodoControl/WRON/MLDAHamilton.o \
    $O/PaquetesPropios/mipaquete_m.o

# Message files
MSGFILES = \
    PaquetesPropios/mipaquete.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target

all: $(OBJS)  Makefile
	@# Do nothing

.PHONY:

.SUFFIXES: .cc

$O/%.o: %.cc
	@mkdir -p $(dir $@)
	$(CXX) -c $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(MSGC) -s _m.cc $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	-rm -rf $O
	-rm -f wron_simulator wron_simulator.exe libwron_simulator.so libwron_simulator.a libwron_simulator.dll libwron_simulator.dylib
	-rm -f ./*_m.cc ./*_m.h
	-rm -f Analisis/*_m.cc Analisis/*_m.h
	-rm -f CoreRouters/*_m.cc CoreRouters/*_m.h
	-rm -f EdgeRouters/*_m.cc EdgeRouters/*_m.h
	-rm -f NodoControl/*_m.cc NodoControl/*_m.h
	-rm -f NodoControl/Dynamic_WRON/*_m.cc NodoControl/Dynamic_WRON/*_m.h
	-rm -f NodoControl/Dynamic_WRON/RwaAlgorithms/*_m.cc NodoControl/Dynamic_WRON/RwaAlgorithms/*_m.h
	-rm -f NodoControl/WRON/*_m.cc NodoControl/WRON/*_m.h
	-rm -f PaquetesPropios/*_m.cc PaquetesPropios/*_m.h
	-rm -f Redes/*_m.cc Redes/*_m.h

cleanall: clean
	-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cc Analisis/*.cc CoreRouters/*.cc EdgeRouters/*.cc NodoControl/*.cc NodoControl/Dynamic_WRON/*.cc NodoControl/Dynamic_WRON/RwaAlgorithms/*.cc NodoControl/WRON/*.cc PaquetesPropios/*.cc Redes/*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/Analisis/analisis.o: Analisis/analisis.cc \
	Analisis/analisis.h
$O/CoreRouters/CoreRouter.o: CoreRouters/CoreRouter.cc \
	CoreRouters/CoreRouter.h
$O/EdgeRouters/EdgeRouter.o: EdgeRouters/EdgeRouter.cc \
	EdgeRouters/EdgeRouter.h
$O/NodoControl/Estado.o: NodoControl/Estado.cc \
	NodoControl/Estado.h
$O/NodoControl/Dynamic_WRON/Control_Dynamic_RWA.o: NodoControl/Dynamic_WRON/Control_Dynamic_RWA.cc \
	PaquetesPropios/mipaquete_m.h \
	NodoControl/Dynamic_WRON/Control_Dynamic_RWA.h \
	NodoControl/Estado.h \
	Analisis/analisis.h
$O/NodoControl/Dynamic_WRON/Dynamic_WRON_Source.o: NodoControl/Dynamic_WRON/Dynamic_WRON_Source.cc \
	NodoControl/Dynamic_WRON/Dynamic_WRON_Source.h \
	PaquetesPropios/mipaquete_m.h
$O/NodoControl/Dynamic_WRON/RwaAlgorithms/Aur_Exhaustive.o: NodoControl/Dynamic_WRON/RwaAlgorithms/Aur_Exhaustive.cc \
	PaquetesPropios/mipaquete_m.h \
	NodoControl/Estado.h \
	NodoControl/Dynamic_WRON/RwaAlgorithms/Aur_Exhastive.h
$O/NodoControl/WRON/Decisor.o: NodoControl/WRON/Decisor.cc \
	NodoControl/WRON/Decisor.h
$O/NodoControl/WRON/MLDAHamilton.o: NodoControl/WRON/MLDAHamilton.cc \
	NodoControl/WRON/MLDAHamilton.h \
	PaquetesPropios/mipaquete_m.h \
	NodoControl/Estado.h
$O/NodoControl/WRON/CalculaDelay.o: NodoControl/WRON/CalculaDelay.cc \
	NodoControl/WRON/CalculaDelay.h
$O/NodoControl/WRON/Controlrwa.o: NodoControl/WRON/Controlrwa.cc \
	NodoControl/WRON/Controlrwa.h \
	PaquetesPropios/mipaquete_m.h
$O/NodoControl/WRON/Crea_matriz.o: NodoControl/WRON/Crea_matriz.cc \
	PaquetesPropios/mipaquete_m.h \
	NodoControl/WRON/Crea_matriz.h
$O/NodoControl/WRON/Guente.o: NodoControl/WRON/Guente.cc \
	NodoControl/WRON/Guente.h
$O/NodoControl/WRON/Generar_matriz.o: NodoControl/WRON/Generar_matriz.cc \
	NodoControl/WRON/Generar_matriz.h \
	PaquetesPropios/mipaquete_m.h
$O/PaquetesPropios/mipaquete_m.o: PaquetesPropios/mipaquete_m.cc \
	PaquetesPropios/mipaquete_m.h

