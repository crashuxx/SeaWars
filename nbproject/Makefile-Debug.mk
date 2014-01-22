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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=MinGW-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Entity.o \
	${OBJECTDIR}/src/InputKeyboard.o \
	${OBJECTDIR}/src/entity/Message.o \
	${OBJECTDIR}/src/entity/Ship.o \
	${OBJECTDIR}/src/entity/ShipMenu.o \
	${OBJECTDIR}/src/entity/ShipPlacer.o \
	${OBJECTDIR}/src/entity/ShipSolid.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/output/IndirectConsole.o \
	${OBJECTDIR}/src/output/WindowsConsole.o \
	${OBJECTDIR}/src/world.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/seawars.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/seawars.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/seawars ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Entity.o: src/Entity.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Entity.o src/Entity.cpp

${OBJECTDIR}/src/InputKeyboard.o: src/InputKeyboard.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/InputKeyboard.o src/InputKeyboard.cpp

${OBJECTDIR}/src/entity/Message.o: src/entity/Message.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/entity
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/entity/Message.o src/entity/Message.cpp

${OBJECTDIR}/src/entity/Ship.o: src/entity/Ship.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/entity
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/entity/Ship.o src/entity/Ship.cpp

${OBJECTDIR}/src/entity/ShipMenu.o: src/entity/ShipMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/entity
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/entity/ShipMenu.o src/entity/ShipMenu.cpp

${OBJECTDIR}/src/entity/ShipPlacer.o: src/entity/ShipPlacer.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/entity
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/entity/ShipPlacer.o src/entity/ShipPlacer.cpp

${OBJECTDIR}/src/entity/ShipSolid.o: src/entity/ShipSolid.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/entity
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/entity/ShipSolid.o src/entity/ShipSolid.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/output/IndirectConsole.o: src/output/IndirectConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/output
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/output/IndirectConsole.o src/output/IndirectConsole.cpp

${OBJECTDIR}/src/output/WindowsConsole.o: src/output/WindowsConsole.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/output
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/output/WindowsConsole.o src/output/WindowsConsole.cpp

${OBJECTDIR}/src/world.o: src/world.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/world.o src/world.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/seawars.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
