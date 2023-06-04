LibName = Misc
OutDir = ../../Build/
Target = $(OutDir)$(LibName).a

Source =\
SciNum.cpp\
funcs.cpp\
graph.cpp\
modint.cpp\
utility.cpp
Object = $(Source:.cpp=.o)

all: $(Target)
	rm $(Object)

$(Target): $(Object)
	ar rcs $(Target) $(Object)

$(Object): $(Source)
	g++ -c $^
