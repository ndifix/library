LibName = Math
OutDir = ../../Build/
Target = $(OutDir)$(LibName).a

Source =\
Bigint.cpp\
Calculus.cpp\
Complex.cpp\
DiffEq.cpp\
Matrix.cpp\
Quoziente.cpp\
ellipse.cpp\
math.cpp
Object = $(Source:.cpp=.o)

all: $(Target)
	rm $(Object)

$(Target): $(Object)
	ar rcs $(Target) $(Object)

$(Object): $(Source)
	g++ -c $^
