CC = clang
CFLAGS = -Wall -std=c99 -I$(HOME)/dev/github.com/raysan5/raylib-5.5/src
LIBS = -L$(HOME)/dev/github.com/raysan5/raylib-5.5/src -lraylib -lm -lpthread -ldl -lrt -lX11
TOOL = unboxing

# WebAssembly build settings
WEB_OUTPUT = web/index.html
RAYLIB_WEB_LIB = $(HOME)/dev/github.com/raysan5/raylib-5.5/build_web/raylib/libraylib.a

.PHONY: clean web web-serve

unboxing: main.c
	$(CC) $(CFLAGS) main.c -o $@ $(LIBS)

# Build WebAssembly version
web: main.c
	mkdir -p web
	emcc main.c $(RAYLIB_WEB_LIB) -o $(WEB_OUTPUT) \
		-Os -Wall \
		-s USE_GLFW=3 \
		-s ASYNCIFY \
		-s TOTAL_MEMORY=67108864 \
		-s FORCE_FILESYSTEM=1 \
		-DPLATFORM_WEB \
		-I $(HOME)/dev/github.com/raysan5/raylib-5.5/src
	cp html/index.html web/

# Serve the web version locally (requires Python)
web-serve: web
	@echo "Starting local server at http://localhost:8787"
	@cd web && python3 -m http.server 8787

clean:
	rm -f $(TOOL)
	rm -rf web/