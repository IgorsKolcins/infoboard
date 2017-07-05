#pragma once

class IWidget
{
	
protected:

    float updateTime; 
	int id;
	
public:

	virtual ~IWidget() {}
	virtual void update() = 0;
	virtual void render() = 0;
	void setId(int id) { this->id = id; }
	float getUpdateTime() { return this->updateTime; }
};
