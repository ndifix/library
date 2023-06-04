LibName = Template
OutDir = ../../Build/
Target = $(OutDir)$(LibName).a

Source =\
Matrix.cpp
Object = $(Source:.cpp=.o)

all: $(Target)
	rm $(Object)

$(Target): $(Object)
	ar rcs $(Target) $(Object)

$(Object): $(Source)
	g++ -c $^
