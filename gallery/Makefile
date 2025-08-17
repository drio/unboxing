UNBOXING = ../unboxing
WIDTH ?= 4000
HEIGHT ?= 4000
ITERATIONS ?= 10000000
COUNT ?= 1

# Generate all possible targets
PALETTES = 0 1 2 3 4 5 6 7
INDICES = $(shell seq 1 $(COUNT))
IMAGES = $(foreach p,$(PALETTES),$(foreach i,$(INDICES),palette_$(p)_$(i).png))

.PHONY: all clean generate-index

all: $(IMAGES) generate-index

palette_%.png:
	$(eval PARTS := $(subst _, ,$*))
	$(eval PALETTE := $(word 1,$(PARTS)))
	$(UNBOXING) -p $(PALETTE) -w $(WIDTH) -h $(HEIGHT) -i $(ITERATIONS) -o $@

generate-index:
	./generate_index.py

rsync:
	rsync -avz -e ssh --delete --progress * atom:/data/data/unboxing

clean:
	rm -f palette_*.png index.html 
