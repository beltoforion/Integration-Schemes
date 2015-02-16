#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/IntegratorEuler.o \
	${OBJECTDIR}/ModelMagPend.o \
	${OBJECTDIR}/IntegratorRK3.o \
	${OBJECTDIR}/IntegratorHeun.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/DampedHarmonicOscillator.o \
	${OBJECTDIR}/IntegratorADB4.o \
	${OBJECTDIR}/IIntegrator.o \
	${OBJECTDIR}/IModel.o \
	${OBJECTDIR}/IntegratorEulerImproved.o \
	${OBJECTDIR}/ModelOszillation.o \
	${OBJECTDIR}/IntegratorADB3.o \
	${OBJECTDIR}/SDLWindow.o \
	${OBJECTDIR}/Types.o \
	${OBJECTDIR}/IntegrationWindow.o \
	${OBJECTDIR}/IntegratorADB2.o \
	${OBJECTDIR}/IntegratorRK5.o \
	${OBJECTDIR}/IntegratorADB5.o \
	${OBJECTDIR}/IntegratorRK4.o \
	${OBJECTDIR}/IntegratorRKF4.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-m64 -O3 -ffast-math -fopenmp
CXXFLAGS=-m64 -O3 -ffast-math -fopenmp

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/integration

dist/Release/GNU-Linux-x86/integration: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -lSDL -lSDL_gfx -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/integration ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/IntegratorEuler.o: nbproject/Makefile-${CND_CONF}.mk IntegratorEuler.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorEuler.o IntegratorEuler.cpp

${OBJECTDIR}/ModelMagPend.o: nbproject/Makefile-${CND_CONF}.mk ModelMagPend.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/ModelMagPend.o ModelMagPend.cpp

${OBJECTDIR}/IntegratorRK3.o: nbproject/Makefile-${CND_CONF}.mk IntegratorRK3.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorRK3.o IntegratorRK3.cpp

${OBJECTDIR}/IntegratorHeun.o: nbproject/Makefile-${CND_CONF}.mk IntegratorHeun.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorHeun.o IntegratorHeun.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/DampedHarmonicOscillator.o: nbproject/Makefile-${CND_CONF}.mk DampedHarmonicOscillator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/DampedHarmonicOscillator.o DampedHarmonicOscillator.cpp

${OBJECTDIR}/IntegratorADB4.o: nbproject/Makefile-${CND_CONF}.mk IntegratorADB4.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorADB4.o IntegratorADB4.cpp

${OBJECTDIR}/IIntegrator.o: nbproject/Makefile-${CND_CONF}.mk IIntegrator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IIntegrator.o IIntegrator.cpp

${OBJECTDIR}/IModel.o: nbproject/Makefile-${CND_CONF}.mk IModel.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IModel.o IModel.cpp

${OBJECTDIR}/IntegratorEulerImproved.o: nbproject/Makefile-${CND_CONF}.mk IntegratorEulerImproved.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorEulerImproved.o IntegratorEulerImproved.cpp

${OBJECTDIR}/ModelOszillation.o: nbproject/Makefile-${CND_CONF}.mk ModelOszillation.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/ModelOszillation.o ModelOszillation.cpp

${OBJECTDIR}/IntegratorADB3.o: nbproject/Makefile-${CND_CONF}.mk IntegratorADB3.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorADB3.o IntegratorADB3.cpp

${OBJECTDIR}/SDLWindow.o: nbproject/Makefile-${CND_CONF}.mk SDLWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/SDLWindow.o SDLWindow.cpp

${OBJECTDIR}/Types.o: nbproject/Makefile-${CND_CONF}.mk Types.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/Types.o Types.cpp

${OBJECTDIR}/IntegrationWindow.o: nbproject/Makefile-${CND_CONF}.mk IntegrationWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegrationWindow.o IntegrationWindow.cpp

${OBJECTDIR}/IntegratorADB2.o: nbproject/Makefile-${CND_CONF}.mk IntegratorADB2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorADB2.o IntegratorADB2.cpp

${OBJECTDIR}/IntegratorRK5.o: nbproject/Makefile-${CND_CONF}.mk IntegratorRK5.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorRK5.o IntegratorRK5.cpp

${OBJECTDIR}/IntegratorADB5.o: nbproject/Makefile-${CND_CONF}.mk IntegratorADB5.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorADB5.o IntegratorADB5.cpp

${OBJECTDIR}/IntegratorRK4.o: nbproject/Makefile-${CND_CONF}.mk IntegratorRK4.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorRK4.o IntegratorRK4.cpp

${OBJECTDIR}/IntegratorRKF4.o: nbproject/Makefile-${CND_CONF}.mk IntegratorRKF4.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O3 -w -s -MMD -MP -MF $@.d -o ${OBJECTDIR}/IntegratorRKF4.o IntegratorRKF4.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/integration

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
