#**************************************************************************
#
# (C) Copyright 1999,2020 Refinitiv; All rights reserved
#
#***************************************************************************/

include ../makefile.include

all: build_message prep monitorRoots$(SUF)

clean:
	@echo "===> Cleaning all $(TYPE) simple executables and objects..."
	@rm -f $(OBJ)/mainRoots$(SUF).o $(OBJ)/monitorRoots$(SUF).o $(PROD)/monitorRoots$(SUF);
	@echo "===> Done"

OBJ=.
PROD=.

#
# Build Executables
#

monitorRoots$(SUF): $(OBJ)/mainRoots$(SUF).o $(OBJ)/monitorRoots$(SUF).o
	@echo " "
	@echo "===> Building sample program $@ for $(PLATFORM_COMP)" 
	@echo " "
	rm -f $(PROD)/$@
	$(CC) $(CCOPT_FLAGS) -o $(PROD)/$@ $(HEADER_INCLUDE) -g \
	$(TMPL_REPOSITORY_FLAGS) $(OBJ)/mainRoots$(SUF).o $(OBJ)/monitorRoots$(SUF).o \
	$(RMC_MONITORROOTS_LIBRARY)
	@echo " "
	@echo "===> Finished build for $(PROD)/$@" 
	@echo " "

#
# Build Objects
#

$(OBJ)/monitorRoots$(SUF).o: monitorRoots.C 
	rm -f $@
	$(CC) $(CCOPT_FLAGS) -c $(HEADER_INCLUDE) $(TMPL_REPOSITORY_FLAGS) -g -o $@ monitorRoots.C

$(OBJ)/mainRoots$(SUF).o: mainRoots.C 
	rm -f $@
	$(CC) $(CCOPT_FLAGS) -c $(HEADER_INCLUDE) $(TMPL_REPOSITORY_FLAGS) -g -o $@ mainRoots.C

#
# Utility targets
#

prep: 
	@ if [ "$(RMC_INSTALL_DIR)" = "" ]; then \
		echo " "; \
		echo "   The RMC_INSTALL_DIR make variable is not set! "; \
		echo "   Please set the RMC_INSTALL_DIR variable by running the \"configure\" setup script."; \
		echo " "; \
		exit 1; \
	fi
	@ if [ "$(CC)" = "cc" ]; then \
		echo " "; \
		echo "   The CC make variable is not set! "; \
		echo "   Please set the CC variable by running the \"configure\" setup script."; \
		echo " "; \
		exit 1; \
	fi


ranl : 
	@echo "===>  Running ranlib for dependent libraries..."
	@ if [ "$(RANLIB)" != "" ]; then \
		echo "$(RANLIB) $(RMC_LIBRARY)"; \
		$(RANLIB) $(RMC_LIBRARY); \
		echo "$(RANLIB) $(NOTIFIER_LIBRARY)"; \
		$(RANLIB) $(NOTIFIER_LIBRARY); \
		echo "$(RANLIB) $(DMYTHREAD_LIBRARY)"; \
		$(RANLIB) $(DMYTHREAD_LIBRARY); \
	fi
	@echo "==>  Done"
	@echo " "

dependents_msg:
	@echo " "
	@echo "===> Checking dependent objects..."
	@echo " "

build_message:
	@echo " "
	@echo "===> Starting build for all $(TYPE) Simple examples on platform-compiler $(PLATFORM_COMP)"
	@echo " "

