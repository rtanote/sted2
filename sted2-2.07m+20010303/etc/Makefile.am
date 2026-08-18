MODULES = deffile/cm64.def deffile/sc55.def deffile/sc55mk2.def deffile/sc88.def
STED_DATAS = sted2.cnf sted2.fon

INSTALL_PATH = @sted_default_path@

EXTRA_DIST = sted2.cnf.in sted2.fon \
	     ${MODULES}
#             deffile/cm64.def \
#             deffile/sc55.def \
#             deffile/sc55mk2.def \
#             deffile/sc88.def

install-data-hook:
	sed -e 's%^#def_path=/etc/sted2/deffile%#def_path=${INSTALL_PATH}/deffile%' \
	    -e 's%^#player=1,timidity .*%#player=0,${bindir}/sted2-play%' \
	    ./sted2.cnf.in > ./sted2.cnf
	$(mkinstalldirs) $(DESTDIR)$(INSTALL_PATH)/deffile
	$(INSTALL_DATA) sted2.cnf $(DESTDIR)$(INSTALL_PATH)/sted2.cnf
	$(INSTALL_DATA) sted2.fon $(DESTDIR)$(INSTALL_PATH)/sted2.fon
	for m in $(MODULES); do \
	  $(INSTALL_DATA) $$m $(DESTDIR)$(INSTALL_PATH)/deffile/`basename $$m` ; \
	done
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	sed -e 's%^STED2_DIR=.*%STED2_DIR=$(INSTALL_PATH)%' \
	    $(top_srcdir)/launchers/sted2 > ./sted2.launcher
	$(INSTALL_PROGRAM) ./sted2.launcher $(DESTDIR)$(bindir)/sted2
	rm -f ./sted2.launcher
	$(INSTALL_PROGRAM) $(top_srcdir)/launchers/sted2-play $(DESTDIR)$(bindir)/sted2-play
	-chgrp audio $(DESTDIR)$(INSTALL_PATH) $(DESTDIR)$(INSTALL_PATH)/sted2.cnf
	-chmod g+w   $(DESTDIR)$(INSTALL_PATH) $(DESTDIR)$(INSTALL_PATH)/sted2.cnf
