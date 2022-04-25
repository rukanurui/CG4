#pragma once
#include <string>

struct Node
{

};

class Model
{
public:
	friend class FbxLoader;

private:
	std::string name;
};
