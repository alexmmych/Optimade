#pragma once

/**********************************************************************************************/
/*                                                                                            */
/* This class reads a blender .obj file and parses it for information for the Graphics class. */
/*                                                                                            */
/**********************************************************************************************/

class ModelReader {
private:

	int coorAmount;  //Amount of the x,y and z ROWS.
	int matrixSize;  //The size the vector should be, this number is equal to the amount of rows there are in total.

	std::smatch stringMatch;  //The smatch parameter used in order to determine if ModelReader operations have been done before.
	std::fstream fileReader;  //The fstream used to read and change the file.
	const std::sregex_iterator regEnd;

	std::string readerText;  //String which is used to confirm if this operation has been done before.
	std::string totalText;  //String which is used in order to change the obj file.
	std::string coorString;  //String which contains the coordinates of the 3D object.

public: 
	ModelReader(std::string fileName);

	std::vector<std::vector<float>> GatherMatrix();

	std::vector<std::vector<float>> posVector; //The variable returned in the GatherMatrix() function, contains x, y and z "v" rows.

	static constexpr int vectorSize = 3;
};