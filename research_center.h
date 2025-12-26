#pragma once
class research_center
{
	char* name;
public:
	research_center(const char* name);
	~research_center();
	const char* getName() const;
	void print() const;
};

