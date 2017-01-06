.PHONY: clean


AGPfail: src/htslib/libhts.a
	cd src/agp-fail && $(MAKE)

src/htslib/libhts.a:
	cd src/htslib && $(MAKE)

clean:
	rm AGPfail