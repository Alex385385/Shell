main : 
	gcc -Wno-format -o part1.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic