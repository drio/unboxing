UNBOXING = ../unboxing
WIDTH ?= 4000
HEIGHT ?= 4000
ITERATIONS ?= 10000000
IMAGES = palette_0_red_to_pink.png palette_1_blue_ocean.png palette_2_green_forest.png palette_3_purple_dream.png palette_4_rainbow.png palette_5_r_default.png palette_6_grey.png palette_7_experiment.png

.PHONY: all clean

all: $(IMAGES)

palette_0_red_to_pink.png:
	$(UNBOXING) -p 0 -w $(WIDTH) -h $(HEIGHT) -i $(ITERATIONS) -o $@

palette_1_blue_ocean.png:
	$(UNBOXING) -p 1 -w $(WIDTH) -h $(HEIGHT) -i $(ITERATIONS) -o $@

palette_2_green_forest.png:
	$(UNBOXING) -p 2 -w $(WIDTH) -h $(HEIGHT) -i $(ITERATIONS) -o $@

palette_3_purple_dream.png:
	$(UNBOXING) -p 3 -w $(WIDTH) -h $(HEIGHT) -i $(ITERATIONS) -o $@

palette_4_rainbow.png:
	$(UNBOXING) -p 4 -w $(WIDTH) -h $(HEIGHT) -i $(ITERATIONS) -o $@

palette_5_r_default.png:
	$(UNBOXING) -p 5 -w $(WIDTH) -h $(HEIGHT) -i $(ITERATIONS) -o $@

palette_6_grey.png:
	$(UNBOXING) -p 6 -w $(WIDTH) -h $(HEIGHT) -i $(ITERATIONS) -o $@

palette_7_experiment.png:
	$(UNBOXING) -p 7 -w $(WIDTH) -h $(HEIGHT) -i $(ITERATIONS) -o $@

clean:
	rm -f $(IMAGES)
