#ifndef NDIFIX_EXECMD
#define NDIFIX_EXECMD

#include <iostream>
#include <string>
#include <vector>
namespace ndifix{
	// ターミナルでコマンドを実行する
	int ExecuteCmd(std::string arg) {
		int ret = system(arg.c_str());
		return ret;
	}

	void ExecuteCmds(std::vector<std::string> args) {
		for(auto arg:args) {
			ExecuteCmd(arg);
		}
	}
}

#endif
