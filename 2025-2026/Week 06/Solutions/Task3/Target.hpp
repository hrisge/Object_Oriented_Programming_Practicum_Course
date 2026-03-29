#pragma once

enum class TargetType {
	HUMAN,
	PLANT,
	CAT,
	_SIZE
};

class Target {
	int health;
	int weight;
	int height;
	TargetType type;
public:
	Target();
	int getHealth() const;
	void setHealth(int health);
	int getWeight() const;
	void setWeight(int weight);
	int getHeight() const;
	void setHeight(int height);
	TargetType getType() const;
	void setType(TargetType type);
};