# Notes:
# $< - Name of first prereq: So for utils.o, this resolves to utils.cpp
#
#

DEBUG = 1       # Comment out to compile optimized without debug symbols

CFLAGS = `pkg-config --cflags --libs opencv`  -std=c++11

MYLIBS = utils.o HsvRange.o Contour.o InclusionTester.o ShapeMatcher.o
MYPROGS = vidcap edge-detect-contour-explorer tape-detector tape-detector-live polygon-explorer-yellow yellow-tote-detector yellow-tote-detector-live

## Set Debug ##
ifdef DEBUG
CFLAGS += -g
else
CFLAGS += -O2
endif

all: $(MYLIBS) $(MYPROGS)

clean:
	rm -f $(MYLIBS)
	rm -f $(MYPROGS) 

##### Libraries #####
utils.o: utils.cpp
	g++ -c $<  $(CFLAGS)

HsvRange.o: HsvRange.cpp
	g++ -c $<  $(CFLAGS)
	
Contour.o: Contour.cpp Contour.h utils.o HsvRange.o
	g++ -c $< $(CFLAGS)

InclusionTester.o: InclusionTester.cpp InclusionTester.h utils.o Contour.o
	g++ -c $< $(CFLAGS)
	
ShapeMatcher.o: ShapeMatcher.cpp ShapeMatcher.h utils.o Contour.o InclusionTester.o
	g++ -c $< $(CFLAGS)

##### Programs #####

vidcap: vidcap.cpp
	g++ $< -o $@ $(CFLAGS)

edge-detect-contour-explorer: edge-detect-contour-explorer.cpp $(MYLIBS)
	g++ $< $(MYLIBS) -o $@ $(CFLAGS)

tape-detector: tape-detector.cpp $(MYLIBS)
	g++ $< $(MYLIBS) -o $@ $(CFLAGS)

tape-detector-live: tape-detector-live.cpp $(MYLIBS)
	g++ $< $(MYLIBS) -o $@ $(CFLAGS)

yellow-tote-detector: yellow-tote-detector.cpp $(MYLIBS)
	g++ $< $(MYLIBS) -o $@ $(CFLAGS)

yellow-tote-detector-live: yellow-tote-detector-live.cpp $(MYLIBS)
	g++ $< $(MYLIBS) -o $@ $(CFLAGS)

polygon-explorer-yellow: polygon-explorer-yellow.cpp $(MYLIBS)
	g++ $< -o $@ $(MYLIBS) $(CFLAGS)


