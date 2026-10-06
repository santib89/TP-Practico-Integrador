CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

FUENTES  = $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJETOS  = $(FUENTES:src/%.cpp=build/%.o)
HEADERS  = $(wildcard include/*.h)

.PHONY: all run pruebas pruebas-asan pruebas-memoria clean

all: refugio

refugio: $(OBJETOS) build/main.o
	$(CXX) $(CXXFLAGS) $^ -o $@

build/%.o: src/%.cpp $(HEADERS)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: refugio
	./refugio

# Compila y ejecuta las pruebas
pruebas: $(FUENTES) pruebas/pruebas.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -g $(FUENTES) pruebas/pruebas.cpp -o pruebas_bin
	./pruebas_bin

# Igual que "pruebas" pero con AddressSanitizer (detecta doble liberacion y uso tras liberar)
pruebas-asan: $(FUENTES) pruebas/pruebas.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -g -fsanitize=address $(FUENTES) pruebas/pruebas.cpp -o pruebas_bin
	./pruebas_bin

# Solo macOS: usa "leaks" para detectar bloques sin liberar al terminar las pruebas
pruebas-memoria: $(FUENTES) pruebas/pruebas.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -g $(FUENTES) pruebas/pruebas.cpp -o pruebas_bin
	leaks --atExit -- ./pruebas_bin

clean:
	rm -rf build refugio pruebas_bin pruebas_bin.dSYM
