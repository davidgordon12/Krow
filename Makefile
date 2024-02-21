SOURCE_FILES := src/*.c

build:
	mkdir -p target
	gcc $(SOURCE_FILES) -o target/krow -lraylib
