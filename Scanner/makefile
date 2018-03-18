# Definition der Variablen
HEADERDIR = includes
SRCDIR = src
OBJDIR = objs
BINDIRTEST = debug
AUTOMATDIR = ../Automat
BUFFERDIR = ../Buffer
SYMBOLTABLEDIR = ../Symboltable
GPP_ARGS = 

# hier alle Object Files eintragen, ausser das File mit der Mainmethode
# darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Scanner.o \
	$(OBJDIR)/Information.o \
	$(OBJDIR)/Token.o
	

	
# linken der Object-files 
makeTestScanner:  $(OBJS) ScannerTest

$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
	@echo "g++ $*.cpp"
	g++ $(GPP_ARGS) -g3 -std=gnu++0x  -w -c  -o $@  $<

ScannerTest:  $(SRCDIR)/TestScanner.cpp $(HEADERDIR)/Scanner.h
	g++ $(GPP_ARGS) -g3 -std=gnu++0x -w -c src/TestScanner.cpp -o $(BINDIRTEST)/TestScanner.o
	g++ $(GPP_ARGS) -g3 -std=gnu++0x -w $(BINDIRTEST)/TestScanner.o $(OBJDIR)/*.o $(AUTOMATDIR)/$(OBJDIR)/*.o $(BUFFERDIR)/$(OBJDIR)/*.o $(SYMBOLTABLEDIR)/$(OBJDIR)/*.o -o $(BINDIRTEST)/ScannerTest  

# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu erstellen
cleanScanner: 
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*
	$(MAKE) makeTestScanner



ScannerTarget: src/Scanner.cpp includes/Scanner.h
	g++ $(GPP_ARGS) -g3  -std=gnu++0x  -c -w $(SRCDIR)/Scanner.cpp     -o $(OBJDIR)/Scanner.o 
	g++ $(GPP_ARGS) -g3  -std=gnu++0x  -c -w $(SRCDIR)/Information.cpp      -o $(OBJDIR)/Information.o
	g++ $(GPP_ARGS) -g3  -std=gnu++0x  -c -w $(SRCDIR)/Token.cpp       -o $(OBJDIR)/Token.o
	

ScannerOBJTarget:  
	$(MAKE) ScannerTarget
