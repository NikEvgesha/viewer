CXX=g++
3DVIEWEW=front/desktop.cpp front/viewer.cpp back/objparser.cpp

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	OPEN_CMD=xdg-open
	FLAGS_CPP=-std=c++17 -Werror -Wall -Wextra
endif
ifeq ($(UNAME_S),Darwin)
	OPEN_CMD=open
	FLAGS_CPP=-std=c++17 -Werror -Wall -Wextra
endif


BUILD=build
# DESKTOP=3DViewer_v2


all: install run

#----- INSTALL -----
install: clean build_dir 
	cd $(BUILD) && qmake ../3DViewer_v2.pro && make
	@if [ $(UNAME_S) = Linux ]; then \
		cp -R $(BUILD)/3DViewer_v2.pro $(BUILD); \
		echo "\033[32mСоздан build/3DViewer\033[0m"; \
	fi
	@if [ $(UNAME_S) = Darwin ]; then \
		cp -R $(BUILD)/3DViewer_v2.app $(BUILD); \
		echo "\033[32mСоздан build/3DViewer_v2.app\033[0m"; \
	fi

run:
	@if [ "$(UNAME_S)" = "Linux" ]; then \
		./$(BUILD)/3DViewer_v2; \
	fi
	@if [ "$(UNAME_S)" = "Darwin" ]; then \
		$(OPEN_CMD) $(BUILD)/3DViewer_v2.app; \
	fi

#Создание директории BUILD 
build_dir: 
	@if [ ! -d "$(BUILD)" ]; then mkdir -p "$(BUILD)"; echo "\033[95mДиректория build создана\033[0m"; fi

#----- CLEAN -----
clean:
	@rm -rf $(BUILD)
	@rm -rf *.a *.o *.gcno *.gcda s21_tests_with_gcov *.info report qrc*.cpp
	@rm -rf 3DViewer_v2.app 3DViewer
	