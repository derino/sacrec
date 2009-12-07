
subdirs = 	src 	\
		tests

.PHONY: all
all: $(subdirs)
	list='$(subdirs)'; for subdir in $$list; do \
	echo "Making all in $$subdir"; \
	(cd $$subdir && $(MAKE) all)  \
	done;

.PHONY: clean
clean: $(subdirs)
	list='$(subdirs)'; for subdir in $$list; do \
	echo "Making clean in $$subdir"; \
	(cd $$subdir && $(MAKE) clean)  \
	done;
