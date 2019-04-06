run:
	g++ -w -lboost_system main.cpp Tokenizer.cpp astBuilder.cpp Statement.cpp Node.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -std=c++17 && ./a.out
test:
	g++ -DNDEBUG -lboost_system test.cpp `llvm-config --cxxflags --ldflags  --system-libs --libs core` -std=c++17 && ./a.out

