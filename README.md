g++ -std=c++17 -lboost_system main.cpp Tokenizer.cpp astBuilder.cpp Statement.cpp Node.cpp && `llvm-config --xccflags --ldflags --system-libs --libs core ` ./a.out
