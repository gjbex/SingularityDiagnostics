IMG = diagnostics.img
DEF = xenial_diagnostics.def
DEST = breniac_adm:/apps/leuven/broadwell/2016a/containers

all: $(IMG)

bootstrap: $(DEF)
	sudo singularity bootstrap $(IMG) $(DEF)

$(IMG): bootstrap
	sudo singularity create --size 2048 $@

clean:
	rm -f $(IMG)

install:
	scp $(IMG) $(DEST)
