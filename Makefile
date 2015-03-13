all:
	g++ `pkg-config --cflags --libs opencv` Translate.cpp -o Translate
	g++ `pkg-config --cflags --libs opencv` Affine.cpp -o Affine
	g++ `pkg-config --cflags --libs opencv` Escale.cpp -o Escale
	g++ `pkg-config --cflags --libs opencv` Perspective.cpp -o Perspective
	g++ `pkg-config --cflags --libs opencv` Rotate.cpp -o Rotate

