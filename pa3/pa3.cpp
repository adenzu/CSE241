#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;

struct point{
	public:
		/* @brief	Initialize point at origin (0, 0)
		 */
		point();

		/* @brief		Initialize point at given integer coords
		 * @param	_x	X value of point
		 * @param	_y	Y value of point
		 */
		point(int _x, int _y);

		/* @brief		Initialize point at integer coords in given array
		 * @param	arr	Two elements sized array that consists of new X and Y value of point
		 */
		point(const int arr[2]);

		/* @brief		Sets point's X and Y values to first element and second element of given array, respectively
		 * @param	arr	Two elements sized array that consists of new X and Y value of point
		 */
		void operator=(const int arr[2]);

		/* @brief			Sets point's X and Y values to given point's X and Y values respectively
		 * @param	other	The point whose X and Y values will be inherited
		 */
		void operator=(const point &other);

		/* @brief		Inserts point into output buffer
		 * @param	out	Output buffer
		 * @param	p	Point that will be inserted
		 * @return		Returns given output buffer
		 */
		friend ostream & operator<<(ostream &out, const point &p);
		
		/* @brief		Gets point from input buffer
		 * @param	in	Input buffer
		 * @param	p	Point that will be set
		 * @return		Returns given input buffer
		 */
		friend istream & operator>>(istream &in, point &p);

		/* @brief		Sets X value of point
		 * @param	_x	New X value
		 */
		void SetX(int _x) {x = _x;}

		/* @brief		Sets Y value of point
		 * @param	_y	New Y value
		 */
		void SetY(int _y) {y = _y;}

		/* @brief		Sets X value of point
		 * @param	_x	New X value
		 * @param	_y	New Y value
		 */
		void Set(int _x, int _y) {x = _x; y = _y;}

		/* @brief	Gets X value of point
		 * @return	X value of point
		 */
		int GetX() const {return x;}
		
		/* @brief	Gets Y value of point
		 * @return	Y value of point
		 */
		int GetY() const {return y;}

		/* @brief			Returns writable reference to X or Y
		 * @param	index	0 to get X, 1 to get Y
		 * @return			Reference to X or Y
		 */
		int & operator[](int index);

		/* @brief			Returns const reference to X or Y
		 * @param	index	0 to get X, 1 to get Y
		 * @return			Reference to X or Y
		 */
		const int & operator[](int index) const;

		/*---PA3 functions implemented here---*/

		/* @brief		Returns true if points have same X, Y values
		 * @param	p	Other point
		 * @return		True if points are same, false otherwise
		 */
		bool operator==(const point &p) const;
	private:
		int x;	// X value of point
		int y;	// Y value of point
};

struct pixel{
	public:

		/* @brief		Initializes pixel as black (0, 0, 0)
		 */
		pixel();

		/* @brief		Initializes pixel with values in given array
		 * @param	arr	Array consisting of R, G, and B values for new pixel
		 */ 
		pixel(const int arr[3]);

		/* @brief		Initializes pixel with given R, G, and B values
		 * @param	_r	R value
		 * @param	_g	G value
		 * @param	_b	B value
		 */
		pixel(int _r, int _g, int _b);
		
		/* @brief				Swaps two color channels of the pixel
		 * @param	firstIndex	First channel index to be swapped
		 * @param	secondIndex	Second channel index to be swapped
		 */
		void SwapChannels(int firstIndex, int secondIndex);

		/* @brief		Sets pixel R, G, and B values to values in give array
		 * @param	arr	Array consisting of new R, G, and B values for the pixel
		 */
		void operator=(const int arr[3]);

		/* @brief			Sets pixel R, G, and B values to given pixel's, respectively
		 * @param	other	Point whose R, G, and B values will be inherited
		 */
		void operator=(const pixel &other);

		/* @brief		Inserts pixel into output buffer
		 * @param	out	Output buffer
		 * @param	p	Pixel that will be inserted
		 * @return		Returns given output buffer
		 */
		friend ostream & operator<<(ostream &out, const pixel &p);
		
		/* @brief		Gets pixel from input buffer
		 * @param	in	Input buffer
		 * @param	p	Pixel that will be set
		 * @return		Returns given input buffer
		 */
		friend istream & operator>>(istream &in, pixel &p);

		/* @brief		Sets R value
		 * @param	_r	New R value
		 */
		void SetR(int _r) {r = _r;}

		/* @brief		Sets G value
		 * @param	_g	New G value
		 */
		void SetG(int _g) {g = _g;}

		/* @brief		Sets B value
		 * @param	_b	New B value
		 */
		void SetB(int _b) {b = _b;}

		/* @brief		Sets R, G, and B value
		 * @param	_r	New R value
		 * @param	_g	New G value
		 * @param	_b	New B value
		 */
		void Set(int _r, int _g, int _b) {r = _r; g = _g; b = _b;}

		/* @brief	Returns R value
		 * @return	R value
		 */
		int GetR() const {return r;}

		/* @brief	Returns G value
		 * @return	G value
		 */
		int GetG() const {return g;}

		/* @brief	Returns B value
		 * @return	B value
		 */
		int GetB() const {return b;}

		/* @brief			Returns writable reference to R, G, or B value for 0, 1, or 2 values of index, respectively
		 * @param	index	Index corresponding to R, G, or B value of pixel
		 * @return			Writable reference to R, G, or B value of pixel
		 */
		int & operator[](int index);
		
		/* @brief			Returns const reference to R, G, or B value for 0, 1, or 2 values of index, respectively
		 * @param	index	Index corresponding to R, G, or B value of pixel
		 * @return			Const reference to R, G, or B value of pixel
		 */
		const int & operator[](int index) const; 

		/* @brief			Checks if every value of this pixel is lesser than given one's
		 * @param	other	Compared pixel
		 * @return			True if this pixel's every value is lesser than given one's, respectively, false otherwise
		 */ 
		bool operator<(const pixel &other) const;

		/* @brief			Checks if every value of this pixel is lesser or equal to given one's
		 * @param	other	Compared pixel
		 * @return			True if this pixel's every value is lesser or equal to given one's, respectively, false otherwise
		 */ 
		bool operator<=(const pixel &other) const;

		/* @brief			Checks if any of this pixel's values is greater than given one's
		 * @param	other	Compared pixel
		 * @return			True if any value of this pixel's is greater than given pixel's corresponding value, false otherwise
		 */
		bool operator>(const pixel &other) const;

		/* @brief			Checks if any of this pixel's values is greater or equal given one's
		 * @param	other	Compared pixel
		 * @return			True if any value of this pixel's is greater or equal given pixel's corresponding value, false otherwise
		 */
		bool operator>=(const pixel &other) const;

		/*---PA3 functions implemented here---*/

		/* @brief			Adds pixels, returns sum
		 * @param	other	Other pixel
		 * @return			Sum of pixels
		 */
		pixel operator+(const pixel &other) const;

		/* @brief			Subtracts pixels, returns difference
		 * @param	other	Other pixel
		 * @return			Difference of pixels
		 */
		pixel operator-(const pixel &other) const;

		/* @brief			Sets pixel's values to given value if they are lesser
		 * @param	lower	Lower limit for pixel's values
		 * @return			Pixel after processed
		 */
		pixel & CapValuesLower(int lower);

		/* @brief			Sets pixel's values to given value if they are greater
		 * @param	lower	Upper limit for pixel's values
		 * @return			Pixel after processed
		 */
		pixel & CapValuesUpper(int upper);

		/* @brief			Sets pixel's values to given values if they are lesser or greater respectfully
		 * @param	lower	Lower limit for pixel's values
		 * @param	upper	Upper limit for pixel's values
		 * @return			Pixel after processed
		 */
		pixel & CapValues(int lower, int upper);
	private:
		int r;	// Red value of pixel
		int g;	// Green value of pixel
		int b;	// Blue value of pixel

};

class ppmImage{
	public:
		/* @brief	Initializes with 0 dimensions and 255 as the upper limit for pixel values
		 */
		ppmImage();

		/* @brief			Initializes with values of given ppm image
		 * @param	image	Image whose values will be inherited
		 */
		ppmImage(const ppmImage &image);

		/* @brief				Initializes as in the file with given file name
		 * @param	_fileName	Name of ppm file
		 */
		ppmImage(const string &_fileName);

		/* @brief				Initializes with given dimensions and 255 as the upper limit for pixel values
		 * @param	_dimensions	Point consisting of image's column and row dimensions respectively 
		 */
		ppmImage(const point &_dimensions);

		/* @brief				Initializes with given dimensions and 255 as the upper limit for pixel values
		 * @param	_dimensionX	Column (X) dimension of the image
		 * @param	_dimensionY	Row (Y) dimension of the image
		 */
		ppmImage(int _dimensionX, int _dimensionY);

		/* @brief						Initializes with given dimensions and value for upper limit for pixel values
		 * @param	_dimensions			Point consisting of image's column and row dimensions respectively
		 * @param	_pixelValueLimit	Upper limit for pixels' values
		 */
		ppmImage(const point &_dimensions, int _pixelValueLimit);

		/* @brief						Initializes with given dimensions and value for upper limit for pixel values
		 * @param	_dimensionX			Column (X) dimension of the image
		 * @param	_dimensionY			Row (Y) dimension of the image
		 * @param	_pixelValueLimit	Upper limit for pixels' values
		 */
		ppmImage(int _dimensionX, int _dimensionY, int _pixelValueLimit);

		/* @brief				Reads file with given file name and sets itself as in the read file
		 * @param	_fileName	Name of the file which will be read
		 * @return				1 if read is successful, 0 otherwise
		 */
		int Read(string _fileName);

		/* @brief				Writes itself on file with given file name
		 * @param	_fileName	Name of the file which will be write
		 * @return				1 if write is successful, 0 otherwise
		 */
		int Write(string _filename) const;
		
		/* @brief		Sets dimensions of image to given values
		 * @param	arr	New column and row values
		 */
		void Resize(const int arr[2]);
		
		/* @brief				Sets dimensions of image to given values
		 * @param	_dimensionX	New column (X) dimension of the image
		 * @param	_dimensionY	New row (Y) dimension of the image
		 */
		void Resize(const point &_dimensions);
		
		/* @brief		Sets dimensions of image to given values
		 * @param	arr	New column and row values
		 */
		void Resize(int _dimensionX, int _dimensionY);

		/* @brief	Returns dimensions of image
		 * @return	Dimensions of image as point
		 */
		point Size() const {return dimensions;}

		/* @brief	Returns upper limit for pixel values
		 * @return	Upper limit for pixel values
		 */
		int GetPixelValueLimit() const {return pixelValueLimit;}

		/* @brief						Sets upper limit for pixel values
		 * @param	_pixelValueLimit	New upper limit for pixel values
		 */
		void SetPixelValueLimit(int _pixelValueLimit) {pixelValueLimit = _pixelValueLimit;}

		/* @brief				Swaps color channels of all pixels of image
		 * @param	swapChoice	1 to swap red and green, 2 to swap red and blue, and 3 to swap green and blue
		 * @return				1 if swap is succesfull, 0 otherwise
		 */
		int SwapPixelChannels(int swapChoice);

		/* @brief			Returns writable row of pixels at given index
		 * @param	index	Index of wanted row of pixels
		 * @return			Writable vector of pixels that are treated as row of pixels of image at index
		 */
		vector<pixel> & operator[](int index);
		
		/* @brief			Returns const row of pixels at given index
		 * @param	index	Index of wanted row of pixels
		 * @return			Const vector of pixels that are treated as row of pixels of image at index
		 */
		const vector<pixel> & operator[](int index) const;

		/* @brief			Inherits values of given image
		 * @param	image	Image whose values will be inherited
		 */
		void operator=(const ppmImage &image); 

		/*---PA3 functions implemented here---*/

		/* @brief			Returns sum of images
		 * @param	image	Other image
		 * @return			Sum of images
		 */
		ppmImage operator+(const ppmImage &image);

		/* @brief			Returns difference of images
		 * @param	image	Other image
		 * @return			Difference of images
		 */
		ppmImage operator-(const ppmImage &image);

		/* @brief			Prints image
		 * @param	out		Out stream
		 * @param	image	Printed image
		 * @return			Out stream
		 */
		friend ostream & operator<<(ostream &out, const ppmImage &image);

		/* @brief			Returns pixel value at given index
		 * @param	row		Row value of pixel
		 * @param	column	Column value of pixel
		 * @param	pIndex	Index of value of pixel 1 for R, 2 for G, and 3 for B
		 * @return			R, G, or B value of pixel 
		 */
		int & operator()(int row, int column, int pIndex);

		/* @brief			Returns pixel value at given index
		 * @param	row		Row value of pixel
		 * @param	column	Column value of pixel
		 * @param	pIndex	Index of value of pixel 1 for R, 2 for G, and 3 for B
		 * @return			R, G, or B value of pixel 
		 */
		const int & operator()(int row, int column, int pIndex) const;
	private:
		point dimensions;				// Point consisting of column and row dimensions of the image
		vector<vector<pixel>> pixels;	// Vector consisting of vectors consisting of individiual pixels
		int pixelValueLimit;			// Upper limit for pixel values

		/* @brief	Resizes vector of vectors of pixels and vectors in it to image's dimensions
		*/
		void Resize();
};


int read_ppm(const string source_ppm_file_name, ppmImage &destination_object);
int write_ppm(const string destination_ppm_file_name, const ppmImage &source_object);
//int swap_channels(ppmImage &image_object_to_be_modified, int swap_choice);
//ppmImage single_color(const ppmImage &source, int color_choice);

/*---PA3 test functions implemented here*/

int swap_channels(ppmImage &image_object_to_be_modified, int swap_choice);
ppmImage single_color(const ppmImage &source, int color_choice);
int test_addition(const string filename_image1, const string filename_image2, const string filename_image3);
int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3);
int test_print(const string filename_image1);


#include <cmath>
int main(int argc, char ** argv){

	if(argc > 3 ){	// Execute if and only if there are at least four arguments (executable name, choice number, name of first and second file)

		int choiceNumber;									// Argument number to execute corresponding process
		string ppmFileName1(argv[2]), ppmFileName2(argv[3]);	// File names

		choiceNumber = std::stoi(argv[1]);	// Convert argument to integer 

		ppmImage readPPMImage;		// Image of read file
		ppmImage processedPPMImage;	// Image that is the result of process

		// Execute corresponding process
		switch(choiceNumber){
			case 1:
				if(argc != 5) return 0;
				test_addition(ppmFileName1, ppmFileName2, argv[4]);
				break;
			case 2:
				if(argc != 5) return 0;
				test_subtraction(ppmFileName1, ppmFileName2, argv[4]);
				break;
			case 3:
				read_ppm(ppmFileName1, readPPMImage);
				swap_channels(readPPMImage, 2);
				write_ppm(ppmFileName2, readPPMImage);
				break;
			case 4:
				read_ppm(ppmFileName1, readPPMImage);
				swap_channels(readPPMImage, 3);
				write_ppm(ppmFileName2, readPPMImage);
				break;
			case 5:
				read_ppm(ppmFileName1, readPPMImage);
				processedPPMImage = single_color(readPPMImage, 1);
				write_ppm(ppmFileName2, processedPPMImage);
				break;
			case 6:
				read_ppm(ppmFileName1, readPPMImage);
				processedPPMImage = single_color(readPPMImage, 2);
				write_ppm(ppmFileName2, processedPPMImage);
				break;
			case 7:
				read_ppm(ppmFileName1, readPPMImage);
				processedPPMImage = single_color(readPPMImage, 3);
				write_ppm(ppmFileName2, processedPPMImage);
				break;
			default:
				std::cout << "Invalid choice number!\n";	// Inform if invalid choice number is entered
		}
	}

	return 0;
}



/*--test funcs--*/

int read_ppm(const string source_ppm_file_name, ppmImage &destination_object){
	return destination_object.Read(source_ppm_file_name);	// Execute Read function of the image with given file name
}

int write_ppm(const string destination_ppm_file_name, const ppmImage &source_object){
	return source_object.Write(destination_ppm_file_name);	// Execute Write function of the image with given file name
}

//=====Pre-PA3 Implementations=====
//
// int swap_channels(ppmImage &image_object_to_be_modified, int swap_choice){
// 	return image_object_to_be_modified.SwapPixelChannels(swap_choice);	// Execute SwapPixelChannels function of image with given swap choice
// }

// ppmImage single_color(const ppmImage &source, int color_choice){
	
// 	point dimensions = source.Size();						// Dimensions of the source image
// 	ppmImage copy(dimensions, source.GetPixelValueLimit());	// Initialized as blank image with dimensions and pixel value limit of source image

// 	--color_choice;	// Decrease one since array index starts at 0
// 	for(int i = 0; i < dimensions.GetY(); ++i){						// For every row
// 		for(int j = 0; j < dimensions.GetX(); ++j){					// For every column
// 			copy[i][j][color_choice] = source[i][j][color_choice];	// Set corresponding pixel value to source image's
// 		}
// 	}
	
// 	return copy;	// Return new image
// }

/*---PA3 function re-implementation here---*/

int swap_channels(ppmImage &image_object_to_be_modified, int swap_choice){
	// Execute SwapPixelChannels function of image with given swap choice
	// This function is actually re-implemented using function-call operator due to PA3
	return image_object_to_be_modified.SwapPixelChannels(swap_choice);	
}

ppmImage single_color(const ppmImage &source, int color_choice){
	point dimensions = source.Size();						// Dimensions of the source image
	ppmImage copy(dimensions, source.GetPixelValueLimit());	// Initialized as blank image with dimensions and pixel value limit of source image

	for(int i = 0; i < dimensions.GetY(); ++i){						// For every row
		for(int j = 0; j < dimensions.GetX(); ++j){					// For every column
			copy(i, j, color_choice) = source(i, j, color_choice);	// Set corresponding pixel value to source image's
																	// New function call type implementation due to PA3
		}
	}

	return copy;	// Return new image
}

/*---PA3 new test functions implementation here---*/

int test_addition(const string filename_image1, const string filename_image2, const string filename_image3){
	ppmImage image1(filename_image1), image2(filename_image2);	// Initialize images
	ppmImage sumImage = image1 + image2;						// Sum them
	return write_ppm(filename_image3, sumImage);				// Write sum image
}

int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3){
	ppmImage image1(filename_image1), image2(filename_image2);	// Initialize images
	ppmImage sumImage = image1 - image2;						// Subtract them
	return write_ppm(filename_image3, sumImage);				// Write result image
}

int test_print(const string filename_image1){
	ppmImage image(filename_image1);	// Initialize image
	std::cout << image;					// Print it
	return 1;
}


/*--point--*/

point::point() : point(0, 0)
{
	// blank
}

point::point(int _x, int _y) : x(_x), y(_y)
{
	// blank
}

point::point(const int arr[2]) : point(arr[0], arr[1])
{
	// blank
}

void point::operator=(const int arr[2]){
	x = arr[0];
	y = arr[1]; 
}

void point::operator=(const point &other){
	x = other.x;
	y = other.y;
}

ostream & operator<<(ostream &out, const point &p){
	out << p.x << " " << p.y;	// Insert as "X Y"
	return out;					
}

istream & operator>>(istream &in, point &p){
	in >> p.x >> p.y;	// Get first X value then Y value
	return in;
}

int & point::operator[](int index){
	switch(index){
		case 0:	
			return x;
		case 1:
			return y;
		default:
			// Raise an error if index is other than 0 and 1
			throw "Point index is out of bounds!";
	}
}

const int & point::operator[](int index) const{
	switch(index){
		case 0:
			return x;
		case 1:
			return y;
		default:
			// Raise an error if index is other than 0 and 1
			throw "Point index is out of bounds!";
	}
}

/*---PA3 functions implemented here---*/

bool point::operator==(const point &p) const{
	return x == p.x && y == p.y;
}



/*--pixel--*/

pixel::pixel() : pixel(0, 0, 0)
{
	// blank
}

pixel::pixel(const int arr[3]) : pixel(arr[0], arr[1], arr[2])
{
	// blank
}

pixel::pixel(int _r, int _g, int _b) : r(_r), g(_g), b(_b)
{
	// blank
}

void pixel::SwapChannels(int firstIndex, int secondIndex){
	int temp = (*this)[firstIndex];				// Temporary variable to store pixel value at first index 
	(*this)[firstIndex] = (*this)[secondIndex];	
	(*this)[secondIndex] = temp;
}

void pixel::operator=(const int arr[3]){
	r = arr[0]; 
	g = arr[1]; 
	b = arr[2];
}

void pixel::operator=(const pixel &other){
	r = other.r;
	g = other.g;
	b = other.b;
}

ostream & operator<<(ostream &out, const pixel &p){
	out << p.r << " " << p.g << " " << p.b;	// Insert as "R G B"
	return out;
}

istream & operator>>(istream &in, pixel &p){
	in >> p.r >> p.g >> p.b;	// Get first R then G then B values
	return in;
}

int & pixel::operator[](int index){
	switch(index){
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		default:
			// Raise error if index is other than 0, 1, and 2
			throw "Pixel index is out of bounds!";
	}
}

const int & pixel::operator[](int index) const{
	switch(index){
		case 0:
			return r;
		case 1:
			return g;
		case 2:
			return b;
		default:
			// Raise error if index is other than 0, 1, and 2
			throw "Pixel index is out of bounds!";
	}
}

bool pixel::operator<(const pixel &other) const{
	return r < other.r && g < other.g && b < other.b;
}

bool pixel::operator<=(const pixel &other) const{
	return r <= other.r && g <= other.g && b <= other.b; 
}

bool pixel::operator>(const pixel &other) const{
	return r > other.r || g > other.g || b > other.b;
}

bool pixel::operator>=(const pixel &other) const{
	return r >= other.r || g >= other.g || b >= other.b; 
}

/*---PA3 functions implemented here---*/

pixel pixel::operator+(const pixel &other) const{
	return pixel(r + other.r, g + other.g, b + other.b);
}

pixel pixel::operator-(const pixel &other) const{
	return pixel(r - other.r, g - other.g, b - other.b);
}

pixel & pixel::CapValuesLower(int lower){
	r = r < lower ? lower : r;	// If lower than lower limit than set to limit
	g = g < lower ? lower : g;	// If lower than lower limit than set to limit
	b = b < lower ? lower : b;	// If lower than lower limit than set to limit
	return *this;
}

pixel & pixel::CapValuesUpper(int upper){
	r = r > upper ? upper : r;	// If greater than upper limit than set to limit
	g = g > upper ? upper : g;	// If greater than upper limit than set to limit
	b = b > upper ? upper : b;	// If greater than upper limit than set to limit
	return *this;
}

pixel & pixel::CapValues(int lower, int upper){
	CapValuesLower(lower);
	CapValuesUpper(upper);
	return *this;
}


/*--ppmImage--*/

ppmImage::ppmImage() : ppmImage(point(0, 0), 255)
{
	// blank
}

ppmImage::ppmImage(const ppmImage &image) : ppmImage(image.dimensions, image.pixelValueLimit)
{
	*this = image;	// Use overloaded assignment operator to copy pixel values
}

ppmImage::ppmImage(const string &_fileName) : ppmImage(point(0, 0), 255)
{
	Read(_fileName);	// Read values from file
}

ppmImage::ppmImage(const point &_dimensions) : ppmImage(_dimensions, 255)
{
	// blank
}

ppmImage::ppmImage(int _dimensionX, int _dimensionY) : ppmImage(point(_dimensionX, _dimensionY), 255)
{
	// blank
}

ppmImage::ppmImage(const point &_dimensions, int _pixelValueLimit) 
		: dimensions(_dimensions), pixels(), pixelValueLimit(_pixelValueLimit)
{
	Resize();	// Resize to given dimensions
}

ppmImage::ppmImage(int _dimensionX, int _dimensionY, int _pixelValueLimit) 
		: ppmImage(point(_dimensionX, _dimensionY), _pixelValueLimit)
{
	// blank
}

int ppmImage::Read(string _fileName){
	
	int readSuccesful = 0;		// Is read successfull

	ifstream ppmFile(_fileName);	// Open file

	char charBuffer;	// Character buffer
	int intBuffer;		// Integer Buffer

	ppmFile >> charBuffer;	// Read first character

	if(charBuffer == 'P'){		// Continue only if it's 'P'
		ppmFile >> intBuffer;	// Read first integer

		if(intBuffer == 3){		// Continue only if it's 3
			ppmFile >> dimensions;	// Get dimensions specified in the file
			
			pixels.resize(dimensions.GetY());	// Resize main vector (row vector)

			ppmFile >> pixelValueLimit;	// Get limit for pixel values specified in the file

			pixel white(pixelValueLimit, pixelValueLimit, pixelValueLimit);	// White pixel
			pixel black(0, 0, 0);											// Black pixel
			pixel tempPixel;												// Read pixel

			readSuccesful = 1;	// Set to successful for now

			for(int i = 0; i < dimensions.GetY(); ++i){	// For every row

				pixels[i].resize(dimensions.GetX());	// Resize pixel vector (column vector)

				for(int j = 0; j < dimensions.GetX(); ++j){	// For every column
					ppmFile >> tempPixel;	// Read pixel
					
					// If any of pixel's value is greater than upper limit or lesser than 0 or file is ended before 
					// image is completed
					if(tempPixel > white || black > tempPixel || ppmFile.eof()){
						readSuccesful = 0;	// Read failed
						break;				// Stop
					}
					
					// else read pixel is valid so assign
					pixels[i][j] = tempPixel;
				}

				// If process failed, stop 
				if(!readSuccesful) break;
			}
		}
	}

	ppmFile.close();	// Close the file

	return readSuccesful;
}

int ppmImage::Write(string _filename) const{

	int writeSuccessful = 1;	// Is write successful

	ofstream ppmFile(_filename);	// Open file

	ppmFile << *this;	// This part changed due to PA3

	ppmFile.close();	// Close file

	return writeSuccessful;
}

void ppmImage::Resize(const int arr[2]){
	dimensions = arr;
	Resize();	// Resize to new dimensions
}

void ppmImage::Resize(const point &_dimensions){
	dimensions = _dimensions;
	Resize();	// Resize to new dimensions
}

void ppmImage::Resize(int _dimensionX, int _dimensionY){
	dimensions.Set(_dimensionX, _dimensionY);
	Resize();	// Resize to new dimensions
}

int ppmImage::SwapPixelChannels(int swapChoice){

	int swapSuccesfull = 1;	// Is process successful

	if(swapChoice > 0 && swapChoice < 4){	// Continue only if swap choice is 1, 2, or 3
		for(int i = 0; i < dimensions.GetY(); ++i){		// For every row
			for(int j = 0; j < dimensions.GetX(); ++j){	// For every column

				/* Red		index is 0	// 1 in PA3 implementation
				 * Green 	index is 1	// 2 in PA3 implementation
				 * Blue		index is 2	// 3 in PA3 implementation
				 * 
				 * So to swap red and green, values at indexes 0(1) and 1(2) will be swapped, which is specified with swap choice 1,
				 * 					    for red and blue it is 0(1) and 2(3), 				  which is specified with swap choice 2,
				 * 			      and for green and blue it is 1(2) and 2(3),				  which is specified with swap choice 3
				 * 
				 * So I did the math and found two equations to calculate these indexes and used them instead of condition checking,
				 * because this is faster
				 */
				
				/*=====Pre-PA3 implementation=====*/
				//pixels[i][j].SwapChannels(swapChoice / 3, swapChoice / 2 + 1);

				/*---PA3 implementation here---*/
				int firstChannelIndex = swapChoice / 3 + 1;		// One of the channel's index to be swapped
				int secondChannelIndex = swapChoice / 2 + 2;	// Other's index
				int temp = (*this)(i, j, firstChannelIndex);
				(*this)(i, j, firstChannelIndex) = (*this)(i, j, secondChannelIndex); 
				(*this)(i, j, secondChannelIndex) = temp; 
			}
		}
	}

	return swapSuccesfull;
}

vector<pixel> & ppmImage::operator[](int index){
	return pixels[index];	// Return row of pixels at index
}

const vector<pixel> & ppmImage::operator[](int index) const{
	return pixels[index];	// Return row of pixels at index
}

void ppmImage::operator=(const ppmImage &image){
	Resize(image.dimensions);	// Resize to given image's dimensions
	pixelValueLimit = image.pixelValueLimit;

	for(int i = 0; i < dimensions.GetY(); ++i){		// For every row
		for(int j = 0; j < dimensions.GetX(); ++j){	// For every column
			pixels[i][j] = image[i][j];				// Copy the pixels respectively
		}
	}
}

void ppmImage::Resize(){
	pixels.resize(dimensions.GetY());	// Resize vector of vectors of pixels to new row dimension

	for(int i = 0; i < dimensions.GetY(); ++i)	// For evert vector of pixels
		pixels[i].resize(dimensions.GetX());	// Resize them to new column dimension
}

/*---PA3 functions implemented here---*/

ppmImage ppmImage::operator+(const ppmImage &image){
	ppmImage sumImage;	// Sum of images

	// Add only if dimensions are same
	if(dimensions == image.dimensions){
		sumImage.Resize(dimensions);	// Resize sum image to files' dimensions

		// It is said pixel upper limits will be same but if not set sum image's to greater one
		int pixelMaxValue = pixelValueLimit > image.pixelValueLimit ? pixelValueLimit : image.pixelValueLimit;
		sumImage.SetPixelValueLimit(pixelMaxValue);

		pixel sumPixel;	// Sum of each pixel

		// For every pixel
		for(int i = 0; i < dimensions.GetY(); ++i){
			for(int j = 0; j < dimensions.GetX(); ++j){
				sumPixel = pixels[i][j] + image[i][j];						// Add two corresponding pixels together
				sumImage[i][j] = sumPixel.CapValuesUpper(pixelMaxValue);	// Cap it under the max value, then set sum image's to it
			}
		}
	}

	return sumImage;
}

ppmImage ppmImage::operator-(const ppmImage &image){
	ppmImage differenceImage;	// Resulting image

	// Continue only if sizes are same
	if(dimensions == image.dimensions){
		differenceImage.Resize(dimensions);	// Resize to the correct size

		// It is said pixel upper limits will be same but if not set sum image's to greater one
		int pixelMaxValue = pixelValueLimit > image.pixelValueLimit ? pixelValueLimit : image.pixelValueLimit;
		differenceImage.SetPixelValueLimit(pixelMaxValue);

		pixel differencePixel;	// Difference of each pixel

		// For every pixel
		for(int i = 0; i < dimensions.GetY(); ++i){
			for(int j = 0; j < dimensions.GetX(); ++j){
				differencePixel = pixels[i][j] - image[i][j];				// Subtract pixels
				differenceImage[i][j] = differencePixel.CapValuesLower(0);	// Make sure rgb values are greater than or equal to 0
			}
		}
	}

	return differenceImage;
}

ostream & operator<<(ostream &out, const ppmImage &image){
	// Write header
	out << "P3\n"
		<< image.dimensions << std::endl
		<< image.pixelValueLimit << std::endl;
	
	// Write pixel values
	for(int i = 0; i < image.dimensions.GetY(); ++i){
		for(int j = 0; j < image.dimensions.GetX(); ++j)
			out << image[i][j] << "  ";
		out << std::endl;
	}

	return out;
}

int & ppmImage::operator()(int row, int column, int pIndex){
	return pixels[row][column][pIndex - 1];
}

const int & ppmImage::operator()(int row, int column, int pIndex) const{
	return pixels[row][column][pIndex - 1];
}

