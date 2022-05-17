TARGET=particle
CXX=g++ -std=c++11
DEBUG=-g
OPT=-O0
WARN=-Wall
SFML=-lsfml-graphics -lsfml-window -lsfml-system
OPENGL=-lGL
CXXFLAGS=$(DEBUG) $(OPT) $(WARN) $(SFML) $(OPENGL)
LD=g++
OBJS= main.o particles.o imgui.o imgui_draw.o imgui-SFML.o imgui_tables.o imgui_widgets.o
all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CXXFLAGS)
	@rm *.o
	@./$(TARGET)

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp -o main.o

particles.o: particles.cpp
	$(CXX) -c $(CXXFLAGS) particles.cpp -o particles.o

imgui.o: include/imgui.cpp
	$(CXX) -c $(DEBUG) $(OPT) include/imgui.cpp -o imgui.o

imgui_draw.o: include/imgui_draw.cpp
	$(CXX) -c $(DEBUG) $(OPT) include/imgui_draw.cpp -o imgui_draw.o

imgui-SFML.o: include/imgui-SFML.cpp
	$(CXX) -c $(DEBUG) $(OPT) include/imgui-SFML.cpp -o imgui-SFML.o

imgui_tables.o: include/imgui_tables.cpp
	$(CXX) -c $(DEBUG) $(OPT) include/imgui_tables.cpp -o imgui_tables.o

imgui_widgets.o: include/imgui_widgets.cpp
	$(CXX) -c $(DEBUG) $(OPT) include/imgui_widgets.cpp -o imgui_widgets.o

