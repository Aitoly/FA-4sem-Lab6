#pragma once
class VectorOfShapes
{
public:
	VectorOfShapes();
	~VectorOfShapes();

	bool Load();
	bool Save();
	void Update(int, int, int, int);
	void Draw(HDC&);

	void lButtonDown(int, int);
	void mouseMove(int, int);
	void lButtonUp();

	CircleShape* dblClick(int, int);
	void SettingsShape(CircleShape*, int, int, int, int);

private:
	std::vector<CircleShape*> shapes;
	bool click;
	CircleShape* focusShape;

	double conservationOfMomentum(int, int, double, double);

	void Boom(int);

	
};

