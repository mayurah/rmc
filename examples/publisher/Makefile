#**************************************************************************
#
# (C) Copyright 1999,2020 Refinitiv; All rights reserved
#
#***************************************************************************/

include ../makefile.include

all: build_message prep publisher$(SUF)

clean:
	@echo "===> Cleaning all $(TYPE) simple executables and objects..."
	@rm -f $(OBJ)/main$(SUF).o $(OBJ)/root$(SUF).o $(OBJ)/userList$(SUF).o $(OBJ)/user$(SUF).o $(OBJ)/timedObject$(SUF).o $(OBJ)/envvar$(SUF).o $(OBJ)/sysinfo$(SUF).o $(PROD)/publisher$(SUF);
	@echo "===> Done"

OBJ=.
PROD=.

#
# Build Executables
#

publisher$(SUF): $(OBJ)/main$(SUF).o $(OBJ)/root$(SUF).o $(OBJ)/userList$(SUF).o $(OBJ)/user$(SUF).o $(OBJ)/timedObject$(SUF).o $(OBJ)/envvar$(SUF).o $(OBJ)/sysinfo$(SUF).o
	@echo " "
	@echo "===> Building sample program $@ for $(PLATFORM_COMP)" 
	@echo " "
	rm -f $(PROD)/$@
	$(CC) $(CCOPT_FLAGS) -o $(PROD)/$@ $(HEADER_INCLUDE) -g \
	$(TMPL_REPOSITORY_FLAGS) $(OBJ)/main$(SUF).o $(OBJ)/root$(SUF).o $(OBJ)/userList$(SUF).o $(OBJ)/user$(SUF).o $(OBJ)/timedObject$(SUF).o $(OBJ)/envvar$(SUF).o $(OBJ)/sysinfo$(SUF).o \
	$(RMC_PUBLISHER_LIBRARY)
	@echo " "
	@echo "===> Finished build for $(PROD)/$@" 
	@echo " "

#
# Build Objects
#

$(OBJ)/main$(SUF).o: main.C 
	rm -f $@
	$(CC) $(CCOPT_FLAGS) -c $(HEADER_INCLUDE) $(TMPL_REPOSITORY_FLAGS) -g -o $@ main.C

$(OBJ)/root$(SUF).o: root.C 
	rm -f $@
	$(CC) $(CCOPT_FLAGS) -c $(HEADER_INCLUDE) $(TMPL_REPOSITORY_FLAGS) -g -o $@ root.C

$(OBJ)/userList$(SUF).o: userList.C 
	rm -f $@
	$(CC) $(CCOPT_FLAGS) -c $(HEADER_INCLUDE) $(TMPL_REPOSITORY_FLAGS) -g -o $@ userList.C

$(OBJ)/user$(SUF).o: user.C 
	rm -f $@
	$(CC) $(CCOPT_FLAGS) -c $(HEADER_INCLUDE) $(TMPL_REPOSITORY_FLAGS) -g -o $@ user.C

$(OBJ)/timedObject$(SUF).o: timedObject.C 
	rm -f $@
	$(CC) $(CCOPT_FLAGS) -c $(HEADER_INCLUDE) $(TMPL_REPOSITORY_FLAGS) -g -o $@ timedObject.C

$(OBJ)/envvar$(SUF).o: envvar.C 
	rm -f $@
	$(CC) $(CCOPT_FLAGS) -c $(HEADER_INCLUDE) $(TMPL_REPOSITORY_FLAGS) -g -o $@ envvar.C

$(OBJ)/sysinfo$(SUF).o: sysinfo.C 
	rm -f $@
	$(CC) $(CCOPT_FLAGS) -c $(HEADER_INCLUDE) $(TMPL_REPOSITORY_FLAGS) -g -o $@ sysinfo.C

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

