#pragma once
class Researcher;
class research_center
{
	char* name;
	Researcher* researchers;

public:
	research_center(const char* name);
	~research_center();
	const char* getName() const;
	void print() const;
};

