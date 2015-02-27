# Global informations
ROOT = /opt/local/bin/root
ROOT_OPTIONS = -q -l

# Name of programs used :
CT_C = Histo.C
TT_C = Trace.C
AT_C = Analysis.C

trace:
	@$(ROOT) $(ROOT_OPTIONS) '$(TT_C)'

analysis:
	@$(ROOT) $(ROOT_OPTIONS) '$(AT_C)(6)'

g4:
	$(MAKE) -sC SiSD-Build
	@cd SiSD-Build ; ./SiSD

clean:
	@$(RM) ~* core/ *.in *linkdef.h *dict.cxx *.so *.d
