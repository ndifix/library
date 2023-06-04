LibName = Encrypt
OutDir = ../../Build/
Target = $(OutDir)$(LibName).a

Source =\
base64.cpp
Object = $(Source:.cpp=.o)

all: $(Target)
	rm $(Object)

$(Target): $(Object)
	ar rcs $(Target) $(Object)

$(Object): $(Source)
	g++ -c $^
