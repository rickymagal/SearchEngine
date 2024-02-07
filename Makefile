all:
	gcc -o main main.c src/**/*.c -lm -g

st:
	gcc -o main_st main_st.c src/**/*.c -lm -g

dot:
	make all
	valgrind ./main
	circo -Tpng -o graph.png graph.dot
