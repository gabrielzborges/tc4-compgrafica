all:
	g++ circulo/circulo.cpp circulos/circulos.cpp aviao/aviao.cpp tiro/tiro.cpp tiros/tiros.cpp bomba/bomba.cpp bombas/bombas.cpp tinyxml2.cpp main.cpp -lm -lGL -lGLU -lglut -std=c++11 -o trabalhocg

clean:
	@rm -f *.o *.output trabalhocg