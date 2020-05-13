 

#include "../HeaderFiles/pch.h"
#include "../HeaderFiles/ModelReaderHeader.h"


ModelReader::ModelReader(std::string fileName) {

	readerText = "#Changed by ModelReader\n";  //The string which is added in the beginning.

	std::string getText;  //Temporary string made for reading the file.

	std::regex regComment("#Changed by ModelReader");  //This regex checks to see if the operations below have been done already.

	std::regex regV("v(?![1-9])");  //Finds all "v" except the starting one which expresses the version of blender.
	std::regex regVt("vt");  //Finds first of "vt".
	std::regex regVn("vn");  //Finds first of "vn".
	std::regex regF("(?!ff)f");  //Finds all of the "f" except the ones belonging to the command "usemtl off".
	std::regex regSingleF("\nf");  //Finds the first of single "f".
	std::regex regMtl("usemtl");  //Finds the "usemtl" command in order to add a new line to it.

	std::regex regCoor("[^v](-?[0-9]\.[0-9]{6} ?){3}");  //Finds all of the x,y and z coordinates needed to render the model. (-?\d\.\d{6})
	std::regex regDelete("\n-?[0-9]\.[0-9]{6}\n");  //Regex to replace faulty matches with nothing.

	
	try {
		fileReader.open(fileName, std::fstream::in);  //Opens the file for reading.
	}
	catch (std::ios_base::failure & e) {
		std::cerr << "Error: Exception, specified file not found.\n";
	}

	//Reads the file.
	while (!fileReader.eof()) {
		getline(fileReader, getText);

		totalText.append(getText);  //The file contents are inside totalText now.
	
	}


	fileReader.close();   //The fstream is closed.

	//Replace the file.

	std::regex_search(totalText, stringMatch, regComment);

	if (stringMatch.empty() == true) { //Searches if a comment is present to determine if this operation has been done before.

		fileReader.open(fileName, std::fstream::out | std::fstream::trunc);  //It is opened once again for output.

		totalText = std::regex_replace(totalText, regV, "\nv");
		totalText = std::regex_replace(totalText, regVt, "\nvt", std::regex_constants::format_first_only);  //Only adds a newline before the first occurence.
		totalText = std::regex_replace(totalText, regVn, "\nvn", std::regex_constants::format_first_only);  //Only adds a newline before the first occurence.
		totalText = std::regex_replace(totalText, regMtl, "\n\nusemtl");
		totalText = std::regex_replace(totalText, regF, "\nf");
		totalText = std::regex_replace(totalText, regSingleF, "\n\nf", std::regex_constants::format_first_only);  //Only adds a newline before the first occurence.

		fileReader << readerText << totalText << std::endl;

		fileReader.close();
	}


	//Gather variables

	fileReader.open(fileName, std::fstream::out | std::fstream::app);  //It is opened once again for output. 

	std::sregex_iterator regIterator(totalText.begin(), totalText.end(), regCoor);

	while (regIterator != regEnd) {

		matrixSize += 1;

		for (coorAmount = 0; coorAmount < regIterator->size(); coorAmount++) {
			coorString.append((*regIterator)[coorAmount]);
			coorString.append("\n");
		}
		regIterator++;
	}

	coorString = std::regex_replace(coorString, regDelete, "\n");  //Eliminates faulty parameters because ECMAScript is jank.
	coorString = std::regex_replace(coorString, std::regex(" "), "");  //Eliminates spaces.
}

std::vector<std::vector<float>> ModelReader::GatherMatrix() {

	std::regex regNumber("(-?[0-9]\.[0-9]{6})");
	std::sregex_iterator regIterator(coorString.begin(), coorString.end(), regNumber);

	int tempRow = 0; //The temporary location of each row, it is one because the first row isn't added by an amount of 3.
	int tempLocation = 0;  //The temporary location of each number.

	float tempFloat;

	posVector.resize(vectorSize);

	while (regIterator != regEnd) {
		tempLocation++;

		//Switch statement responsible for storing all values into the vector.

		switch (tempLocation - (3 * (tempRow))) {
		case 1:
			stringMatch = *regIterator;
			tempFloat = std::stof(stringMatch.str());
			posVector[0].push_back(tempFloat);
			break;
		case 2:
			stringMatch = *regIterator;
			tempFloat = std::stof(stringMatch.str());
			posVector[1].push_back(tempFloat);
			break;
		case 3:
			stringMatch = *regIterator;
			tempRow++;
			tempFloat = std::stof(stringMatch.str());
			posVector[2].push_back(tempFloat);

			break;
		}


		regIterator++;
	}

	fileReader << std::endl;

	for (int b = 0; b < vectorSize; b++) {
		for (int i = 0; i < matrixSize; i++)
		{
			fileReader << posVector[b][i];
		}
	}

	return posVector;
}
