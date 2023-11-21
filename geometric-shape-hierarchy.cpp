#include <iostream>
#include <string> 
using namespace std;

// ERRORS
// the NegativeLengthError is thrown when the given length is negative
class NegativeLengthError : public exception
{
public:
	NegativeLengthError(string message) : exception(message.c_str()) {}
};

// the SamePointError is thrown when the given points are the same
class SamePointError : public exception
{
public:
	SamePointError(string message) : exception(message.c_str()) {}

};


// the NotParallelError is thrown when the given lines are not parallel
class NotParallelError : public exception
{
public:
	NotParallelError(string message) : exception(message.c_str()) {}
};


class RightUpperPointError : public exception
{
public:
	RightUpperPointError(string message) : exception(message.c_str()) {}
};

// the LowerBaseError is thorwn when the given base of the trapezoid is not bigger than the top
class LowerBaseError : public exception
{
public:
	LowerBaseError(string message) : exception(message.c_str()) {}
};


class Point
{
protected:
	// POINT CLASS: ATTRIBUTES
	// the atributes are declared as pro
	float xCoordinate = 0, yCoordinate = 0;

public:
	// POINT CLASS: CONSTRUCTORS
	// constructuros are declared inside the class and defined outside the class
	// default constructor
	Point();  

	// parameterized constructor
	Point(float xCoordinateValue, float yCoordinateValue);  

	// copy constructor
	Point(const Point& point); 

	// POINT CLASS: DESTRUCTOR
	// since there are no dynamic attributes, there is nothing to be done in the destructor
	~Point() {}

	//POINT CLASS: OPERATORS
	// the assignment operator has to be overloaded inside the class because it needs access to the this pointer
	Point operator=(Point source)
	{
		this->xCoordinate = source.xCoordinate;
		this->yCoordinate = source.yCoordinate;
		return *this;
	}

	// POINT CLASS: METHODS
	// setters and getters
	void setXCoordinate(float xCoordinate)
	{
		// the this pointer is mandatory when the parameter has the same name as the attribute
		this->xCoordinate = xCoordinate;
	}

	void setYCoordinate(float yCoordinate)
	{
		// the this pointer is mandatory when the parameter has the same name as the attribute
		this->yCoordinate = yCoordinate;
	}

	float getXCoordinate()
	{
		return this->xCoordinate;
	}

	float getYCoodinate()
	{
		return this->yCoordinate;
	}

	// POINT CLASS: FRIEND FUNCTIONS
	friend istream& operator>>(istream& console, Point& point);
	friend ostream& operator<<(ostream& console, Point point);
};

// POINT CLASS: DEFINITIONS
// default constructor: the coordinates are initialized with 0
Point::Point() : xCoordinate(0), yCoordinate(0) {}

// the parameterized constructor: the coordinates are initialized with the given values
Point::Point(float xCoordinateValue, float yCoordinateValue) : xCoordinate(xCoordinateValue), yCoordinate(yCoordinateValue) {}

// the copy constructor: the coordinates are initialized with the coordinates of the given point
Point::Point(const Point& point) : xCoordinate(point.xCoordinate), yCoordinate(point.yCoordinate) {}

istream& operator>>(istream& console, Point& point)
{
	cout << "The X axes coordinate of the point: ";  console >> point.xCoordinate;
	cout << "The Y axes coordinate of the point: ";  console >> point.yCoordinate;
	return console;
}

ostream& operator<<(ostream& console, Point point)
{
	console << "The coordinates of the point are: (" << point.xCoordinate << ", " << point.yCoordinate << ")" << endl;
	return console;
}






class Square
{
protected:
	// SQUARE CLASS: ATTRIBUTES
	// the attributes are declared as protected because they are used in the derived classes
	// in order to define a square, we need the coordinates of the lower left corner and the length of the side
	Point lowerLeftCorner;
	float length = 0;

	// the valid attribute is used to check if the shape is valid or not
	int valid = 1;

public:
	// SQUARE CLASS: CONSTRUCTORS
	// constructors are declared inside the class and defined outside the class

	// default constructor
	Square(); 

	// parameterized constructor
	Square(Point coordinates, float length); 

	// copy constructor
	Square(const Square& object); 

	
	// SQUARE CLASS: DESTRUCTOR
	// since there are no dynamic attributes, there is nothing to be done in the destructor
	~Square() {}

	
	// SQUARE CLASS: OPERATORS
	// the assignment operator has to be overloaded inside the class because it needs access to the this pointer
	Square operator=(Square source)
	{
		this->lowerLeftCorner = source.lowerLeftCorner;
		this->length = source.length;
		return *this;
	}


	// SQUARE CLASS: METHODS
	// the calculateArea method calculates the area of the square with the known formula, length * length
	void calculateArea()
	{
		cout << "The area of the square is " << length * length << endl;
	}

	// the printInfo method prints the information about the shape such as the type of the shape, the coordinates of the lower 
	// left corner and the length of the side
	virtual void printInfo()
	{
		cout << "Shape: square." << endl;

		// to print the information we make use of the overloaded operator<<
		cout << *this;

		cout << endl;
	}


	// SQUARE CLASS: FRIEND FUNCTIONS
	friend istream& operator>>(istream& console, Square& square);
	friend ostream& operator<<(ostream& console, Square square);
};

// SQUARE CLASS: DEFINITIONS
// default constructor: the coordinates of the lower left corner are initialized with the default constructor of the Point class and the length is initialized with 0
Square::Square() : lowerLeftCorner(), length(0) {}

// the parameterized constructor: the coordinates of the lower left corner are initialized with the given values (using the parametrized constructor of the Point class) 
// and the length is initialized with the given value
Square::Square(Point coordinates, float length) : lowerLeftCorner(coordinates), length(length)
{
	// if the length is negative, the square is not valid
	if (length <= 0)
		valid = 0;
}

// the copy constructor: the coordinates of the lower left corner are initialized with the coordinates of the given square and the length is initialized with the length 
// of the given square
Square::Square(const Square& object) : lowerLeftCorner(object.lowerLeftCorner), length(object.length) {}

// the overloaded >> operator is used to read the coordinates of the lower left corner and the length of the side
istream& operator>>(istream& console, Square& square)
{
	// in order to read the coordinates of the lower left corner point we make use of the overloaded >> operator of the Point class
	cout << "The coordinates of the lower left corner point. " << endl; console >> square.lowerLeftCorner;

	cout << "The length of the side: ";
	float sideLength;
	console >> sideLength;

	// the ok varable is used in order to ensure that the given values are valid
	// the loop will be executed until the user enters valid values
	int ok = 1;
	while (ok)
	{
		try
		{
			// if the length is negative, the NegativeLengthError exception is thrown and the user is asked to enter the length again
			// if the length is positive, the length is assigned to the length attribute of the square and ok is set to 0 in order to exit the while loop
			if (sideLength < 0)
				throw NegativeLengthError("The given length is negative!");
			else
			{
				square.length = sideLength;
				ok = 0;
			}
		}
		catch (NegativeLengthError e)
		{
			cout << e.what() << endl << "Introduceti din nou lungimea laturii: ";
			console >> sideLength;
		}
	}

	square.valid = 1;
	return console;
}

// the overloaded << operator is used to print the coordinates of the lower left corner and the length of the side
ostream& operator<<(ostream& console, Square square)
{
	// we make use of the overloaded << operator of the Point class in order to print the coordinates of the lower left corner
	console << "The lower left corner. " << square.lowerLeftCorner << "The length of the side is: " << square.length;
	return console;
}





// the Rectangle class is derived from the Square class, therefore it inherits the attributes and methods of the Square class
// the Rectangle class inherits virtually the Square class because it is the base class for the Parallelogram class (diamond inheritance)
class Rectangle : public virtual Square
{
protected:
	// RECTANGLE CLASS: ATTRIBUTES
	// the attributes are declared as protected because they are used in the derived classes
	// since the rectangle is serived from the square we only need to define the width of the rectangle
	float width = 0;

public:
	// RECTANGLE CLASS: CONSTRUCTORS
	// constructors are declared inside the class and defined outside the class
	// the default consructor
	Rectangle(); 

	// the parameterized constructor
	Rectangle(Point coordinates, float length, float width); 

	// the copy constructor
	Rectangle(const Rectangle& rectangle); 

	// RECTANGLE CLASS: DESTRUCTOR
	// since there are no dynamic attributes, there is nothing to be done in the destructor
	~Rectangle() {}


	// RECTANGLE CLASS: OPERATORS
	// the assignment operator has to be overloaded inside the class because it needs access to the this pointer
	Rectangle operator=(Rectangle source)
	{
		this->lowerLeftCorner = source.lowerLeftCorner;
		this->length = source.length;
		this->width = source.width;
		return *this;
	}

	//RECTANGLE CLASS: METHODS
	// the calculateArea method is an overriden method of the calculateArea method of the Square class
	// the calculateArea method calculates the area of the rectangle with the known formula, length * width
	void calculateArea()
	{
		cout << "The area of the rectangle is " << length * width << endl;
	}

	// the printInfo method is an overriden method of the printInfo method of the Square class
	// the printInfo method prints the information about the shape such as the type of the shape, the coordinates of the lower
	// left corner, the length and the width of the rectangle
	void printInfo()
	{
		cout << "Shape: rectangle." << endl;

		// to print the information we make use of the overloaded operator<<
		cout << *this;
		cout << endl;
	}


	// RECTANGLE CLASS: FRIEND FUNCTIONS
	friend istream& operator>>(istream& consola, Rectangle& dreptunghi);
	friend ostream& operator<<(ostream& consola, Rectangle dreptunghi);
};

// RECTANGLE CLASS: DEFINITIONS
// the default constructor: the coordinates and the length are initialized with the default constructor of the Square class and the width is initialized with 0
Rectangle::Rectangle() : Square(), width(0) {}

// the parameterized constructor: the coordinates and the length are initialized with the given values (using the parametrized constructor of the Square class) 
// and the width is initialized with the given value
Rectangle::Rectangle(Point coordinates, float length, float width)
	: Square(coordinates, length), width(width)
{
	// if the width or the length are negative, the rectangle is not valid
	if (width < 0 || length < 0)
		valid = 0;
}

// the copy constructor: the coordinates and the length are initialized with the coordinates and the length of the given rectangle (using the parametarized 
// constructor of the Square class) and the width is initialized with the width of the given rectangle
Rectangle::Rectangle(const Rectangle& dreptunghi)
	: Square(dreptunghi.lowerLeftCorner, dreptunghi.length), width(dreptunghi.width) {};

// the overloaded >> operator is used to read the coordinates of the lower left corner, the length and the width of the rectangle
istream& operator>>(istream& console, Rectangle& rectangle)
{
	// in order to read the coordinates of the lower left corner point we make use of the overloaded >> operator of the Point class
	cout << "The coordinates of the lower left corner point." << endl; console >> rectangle.lowerLeftCorner;


	cout << "The length of the rectangle: ";
	float length;
	console >> length;

	// the ok varable is used in order to ensure that the given values are valid
	// the loop will be executed until the user enters valid values
	int ok = 1;
	while (ok)
	{
		try
		{
			// if the length is negative, the NegativeLengthError exception is thrown and the user is asked to enter the length again
			// if the length is positive, the length is assigned to the length attribute of the rectangle and ok 
			// is set to 0 in order to exit the while loop
			if (length < 0)
				throw NegativeLengthError("The length is negative!");
			else
			{
				rectangle.length = length;
				ok = 0;
			}
		}
		catch (NegativeLengthError e)
		{
			cout << e.what() << endl << "The length of the rectangle: ";
			console >> length;
		}
	}

	// the same procedure is applied for the width
	cout << "The width of the rectangle: ";
	float width;
	console >> width;

	// the ok variable is set back to 1 since it was set to 0 in the previous while loop
	ok = 1;
	while (ok)
	{
		try
		{
			// if the width is negative, the NegativeLengthError exception is thrown and the user is asked to enter the width again
			// if the width is positive, the width is assigned to the width attribute of the rectangle and ok
			// is set to 0 in order to exit the while loop
			if (width < 0)
				throw NegativeLengthError("The width is negative!");
			else
			{
				rectangle.width = width;
				ok = 0;
			}
		}
		catch (NegativeLengthError e)
		{
			cout << e.what() << endl << "The width of the rectangle: ";
			console >> width;
		}
	}

	return console;
}

// the overloaded << operator is used to print the information about the rectangle
ostream& operator<<(ostream& console, Rectangle rectangle)
{
	// in order to print the coordinates of the lower left corner point we make use of the overloaded << operator of the Point class
	console << "Lower left corner. " << rectangle.lowerLeftCorner;

	// the length and the width are printed
	console << "The length of the rectangle is: " << rectangle.length << endl;
	console << "The width of the rectangle is: " << rectangle.width << endl;
	return console;
}



// the Rhombus class is a derived class of the Square class, therefore it inherits the attributes and the methods of the Square class
// the Rhombus class inherts virtually the Square class since it is the base class for the Parallelogram class (diamond inheritance)
class Rhombus : public virtual Square
{
protected:
	// RHOMBUS CLASS: ATTRIBUTES
	// the attributes are protected since they are used in the derived class
	Point upperRightCorner;

public:
	// RHOMBUS CLASS: CONSTRUCTORS
	// the constructors are declared inside the class and defined outside the class
	// the default constructor
	Rhombus(); 

	// the parameterized constructor
	Rhombus(Point coodonatePunct, float lungimeLatura, Point coordonateCelalaltPunct);

	// the copy constructor
	Rhombus(const Rhombus& romb); 


	// RHOMBUS CLASS: DESTRUCTOR
	// since there are no dynamic attributes, there is nothing to be done in the destructor
	~Rhombus() {}


	// RHOMBUS CLASS: OPERATORS
	// the assignment operator has to be overloaded inside the class because it needs access to the this pointer
	Rhombus operator= (Rhombus source)
	{
		this->lowerLeftCorner = source.lowerLeftCorner;
		this->upperRightCorner = source.upperRightCorner;
		this->length = source.length;
		return *this;
	}


	// RHOMBUS CLASS: METHODS
	// the calculateArea method is declared inside the class and defined outside the class
	void calculateArea();


	// the PrintInfo method is used to print the information about the Rhombus
	void printInfo()
	{
		cout << "Shape: Rhombus." << endl;

		// we make use of the overloaded << operator to print the information about the rhombus
		cout << *this;
		cout << endl;
	}


	// RHOMBUS CLASS: FRIEND FUNCTIONS
	friend istream& operator>>(istream& consola, Rhombus& romb);
	friend ostream& operator<<(ostream& consola, Rhombus romb);
};

// RHOMBUS CLASS: DEFINITIONS 
// the default constructor: the upper right corner is initialized using the default constructor of the Point class
// and the length rest of the attributes are initialized using the default constructor of the Square class
Rhombus::Rhombus() : Square(), upperRightCorner(0, 0) {}

// the parametized constructor: the lower left corner and length are initialized using the parametized constructor of the Square class
// and the upper right corner is initialized using the parametized constructor of the Point class
Rhombus::Rhombus(Point coordinatesLowerLeftCorner, float length, Point coordinatesUpperRightCorner)
	: Square(coordinatesLowerLeftCorner, length), upperRightCorner(coordinatesUpperRightCorner)
{
	// if the length is negative, the Rhombus is not valid
	if (length < 0)
		valid = 0;

	// if the y coordinates of the upper right corner and lower left corner are the same. the Rhombus is not valid
	if (coordinatesUpperRightCorner.getYCoodinate() == coordinatesLowerLeftCorner.getYCoodinate())
		valid = 0;

	// if the x coroinate of the upper right corner is smaller than the x coordinate of the lower left corner, the Rhombus is not valid
	if (coordinatesUpperRightCorner.getXCoordinate() < coordinatesLowerLeftCorner.getXCoordinate())
		valid = 0;
}

// the copy constructor: the lower left corner and length are initialized using the parametized constructor of the Square class
Rhombus::Rhombus(const Rhombus& romb) : Square(romb.lowerLeftCorner, romb.length), upperRightCorner(romb.upperRightCorner) {}

// the calculateArea method is overriden in the Rhombus class
void Rhombus::calculateArea()
{
	// in order to calculate the area of the Rhombus, we need to find the coordinates of the other two points
	Point lowerRightCorner, upperLeftCorner;

	lowerRightCorner.setYCoordinate(lowerLeftCorner.getYCoodinate());
	upperLeftCorner.setYCoordinate(upperRightCorner.getYCoodinate());

	lowerRightCorner.setXCoordinate(lowerLeftCorner.getYCoodinate() + length);
	upperLeftCorner.setXCoordinate(upperRightCorner.getXCoordinate() - length);


	float area = 0;
	area = abs((upperRightCorner.getXCoordinate() * lowerRightCorner.getYCoodinate())
		- (upperRightCorner.getXCoordinate() * lowerLeftCorner.getYCoodinate())
		+ (lowerLeftCorner.getXCoordinate() * upperRightCorner.getYCoodinate())
		- (lowerRightCorner.getXCoordinate() * upperRightCorner.getYCoodinate())
		+ (lowerRightCorner.getXCoordinate() * lowerLeftCorner.getYCoodinate())
		- (lowerLeftCorner.getXCoordinate() * lowerRightCorner.getYCoodinate()));

	cout << "The area of the rhombus is " << area << endl;
}

// the overloaded >> operator is used to read the information about the Rhombus
istream& operator>>(istream& console, Rhombus& rhombus)
{
	// here we make use of the overloaded >> operator of the Square class
	cout << "Coordinates of the lower left corner." << endl; console >> rhombus.lowerLeftCorner;


	cout << "Coordinates of the upper right corner." << endl;
	Point upperRightCorner;
	console >> upperRightCorner;

	// the ok variable is used to check if the input is valid
	// if the input is not valid, the user will be asked to input the coordinates again
	int ok = 1;
	while (ok)
	{
		try
		{
			// if the y coordinate of the upper right corner is the same as the y coordinate of the lower left corner, the Rhombus is not valid
			if (upperRightCorner.getYCoodinate() == rhombus.lowerLeftCorner.getYCoodinate())
			{
				if (upperRightCorner.getXCoordinate() == rhombus.lowerLeftCorner.getXCoordinate())
					throw SamePointError("The same point was given twice!");
				else
					throw NotParallelError("The y axes coordinate for the two points is the same so the sides can't be parallel to one another!");
			}
			else
				// if the x coordinate of the upper right corner is smaller than the x coordinate of the lower left corner, the Rhombus is not valid
				if (upperRightCorner.getXCoordinate() < rhombus.lowerLeftCorner.getXCoordinate())
					throw RightUpperPointError("Wrong coordinates for the upper right corner.");
				else
				{
					// if the input is valid, the upper right corner is set and ok is set to 0 in order to exit the while loop
					rhombus.upperRightCorner = upperRightCorner;
					ok = 0;
				}
		}
		catch (SamePointError e)
		{
			cout << e.what() << endl << "Please enter the coordinates of the point agaian." << endl;
			console >> upperRightCorner;
		}
		catch (NotParallelError e)
		{
			cout << e.what() << endl <<  "Please enter the coordinates of the point agaian." << endl;
			console >> upperRightCorner;
		}
		catch (RightUpperPointError e)
		{
			cout << e.what() << endl <<  "Please enter the coordinates of the point agaian." << endl;
			console >> upperRightCorner;
		}

	}

	cout << "Length: ";
	float length;
	console >> length;

	// the ok variable is used to check if the input is valid so we set it back to 1
	// as long as the input is not valid, the user will be asked to input the length again
	ok = 1;
	while (ok)
	{
		try
		{
			// if the length is negative, the Rhombus is not valid
			if (length < 0)
				throw NegativeLengthError("The length is negative!");
			else
			{
				// if the input is valid, the length is set and ok is set to 0 in order to exit the while loop
				rhombus.length = length;
				ok = 0;
			}
		}
		catch (NegativeLengthError e)
		{

			cout << e.what() << endl << "Please enter the length again: ";
			console >> length;
		}
	}

	return console;
}

// the overloaded << operator is used to print the information about the Rhombus
ostream& operator<<(ostream& console, Rhombus rhombus)
{
	// here we make use of the overloaded << operator of the Point class
	console << "Lower left corner. " << rhombus.lowerLeftCorner;

	// here we make use of the overloaded << operator of the Point class
	console << "Upper right corner. " << rhombus.upperRightCorner;

	console << "Length:  " << rhombus.length;
	return console;
}





// the Parallelogram class inherits from both the Rhombus and the Rectangle class and since they both inherit from the Square class 
// we would have run into the Diamond Problem if we didn't use virtual inheritance
class Parallelogram : public Rhombus, public Rectangle
{
protected:
	// we dont need any other data than the attributes inherited from the Rhombus and the Rectangle class
	// we consider the length to be the side parallel to the x axis and the width to be the other side of the parallelogram
public:
	// PARALLELOGRAM CLASS: CONSTRUCTORS
	// the constructors are declared inside the class and they are defined outside the class
	// the default constructor
	Parallelogram(); 

	// the parametrized constructor
	Parallelogram(Point lowerLeftCorner, Point upperRightCorner, float length, float width);

	// the copy constructor
	Parallelogram(const Parallelogram& paralelogram);
	

	// PARALLELOGRAM CLASS: DESTRUCTOR
	// since we dont have any dynamic data, we don't need to do anything in the destructor
	~Parallelogram() {}


	// PARALLELOGRAM CLASS: OPERATOR OVERLOADING
	// the assignment operator: it needs to be overloaded inside the class since it needs access to the this pointer
	Parallelogram operator= (Parallelogram source)
	{
		this->lowerLeftCorner = source.lowerLeftCorner;
		this->upperRightCorner = source.upperRightCorner;
		this->length = source.length;
		this->width = source.width;
		return *this;
	}

	
	// PARALLELOGRAM CLASS: METHODS
	// the calculateArea method is declared here and defined outside the class
	void calculateArea();

	// the PrintInfo method prints the information about the Parallelogram
	void printInfo()
	{
		cout << "Shape: parallelogram." << endl;

		// here we make use of the overloaded << operator
		cout << *this;
		cout << endl;
	}


	// PARALLELOGRAM CLASS: FRIEND FUNCTIONS
	friend istream& operator>> (istream& consola, Parallelogram& paralelogram);
	friend ostream& operator<< (ostream& consola, Parallelogram paralelogram);
};

// PARALLELOGRAM CLASS: DEFINITIONS 
// the default constructor: the default constructor of the Rhombus and the Rectangle class will be called
Parallelogram::Parallelogram() : Rhombus(), Rectangle() {}

// the parametrized constructor: the parametrized constructor of the Rhombus and the Rectangle class will be called
Parallelogram::Parallelogram(Point lowerLeftCorner, Point upperRightCorner, float length, float width)
	: Rhombus(lowerLeftCorner, length, upperRightCorner), Rectangle(lowerLeftCorner, length, width)
{
	// if the length or the width is negative, the Parallelogram is not valid
	if (length < 0 || width < 0)
		valid = 0;

	// ifthe y coordinate of the lower left corner is equal to the y coordinate of the upper right corner then the Parallelogram is not valid
	// bacuse the sides are not parallel
	if (lowerLeftCorner.getYCoodinate() == upperRightCorner.getYCoodinate())
		valid = 0;

	// if the x coordinate of the lower left corner is smaller than the x coordinate of the upper right corner then the Parallelogram is not valid
	if (upperRightCorner.getXCoordinate() < lowerLeftCorner.getXCoordinate())
		valid = 0;
}

// the copy constructor: the copy constructor of the Rhombus and the Rectangle class will be called
Parallelogram::Parallelogram(const Parallelogram& paralelogram)
	: Rhombus(paralelogram.lowerLeftCorner, paralelogram.length, paralelogram.upperRightCorner), 
	Rectangle(paralelogram.lowerLeftCorner, paralelogram.length, paralelogram.width) {}

// the calculateArea is overridden here
void Parallelogram::calculateArea()
{
	// to calculate the area of the Parallelogram we need to calculate the coordinates of the lower right corner and the upper left corner
	Point lowerRightCorner, upperLeftCorner;

	// the y coodinates are the same as the y coordinate of the lower left corner/ the upper right corner
	lowerRightCorner.setYCoordinate(lowerLeftCorner.getYCoodinate());
	upperLeftCorner.setYCoordinate(upperRightCorner.getYCoodinate());

	// to calculate the x coordinates we need to use the length
	lowerRightCorner.setXCoordinate(lowerLeftCorner.getYCoodinate() + length);
	upperLeftCorner.setXCoordinate(upperRightCorner.getXCoordinate() - length);


	// to caluculate the area we se the formula: A = |x1 * y2 - x2 * y1 + x2 * y3 - x3 * y2 + x3 * y4 - x4 * y3 + x4 * y1 - x1 * y4|
	float area = 0;
	area = abs((upperRightCorner.getXCoordinate() * lowerRightCorner.getYCoodinate()) - (upperRightCorner.getXCoordinate() * lowerLeftCorner.getYCoodinate()) + (lowerLeftCorner.getXCoordinate() * upperRightCorner.getYCoodinate()) - (lowerRightCorner.getXCoordinate() * upperRightCorner.getYCoodinate()) + (lowerRightCorner.getXCoordinate() * lowerLeftCorner.getYCoodinate()) - (lowerLeftCorner.getXCoordinate() * lowerRightCorner.getYCoodinate()));

	cout << "The area of the parallelogram is " << area << endl;
}

// the overloaded operator >> is used to read the information about the Parallelogram from the console
istream& operator>> (istream& console, Parallelogram& parallelogram)
{
	// we make use of the overloaded operator >> from the Point class to read the coordinates of the lower left corner
	cout << "Lower left corner coordinates." << endl; console >> parallelogram.lowerLeftCorner;


	cout << "Upper right corner coordinates." << endl;
	Point upperRightCorner;
	// we make use of the overloaded operator >> from the Point class to read the coordinates of the upper right corner
	console >> upperRightCorner;

	// we check if the coordinates of the upper right corner are valid
	// as long as they are not valid we read them again
	int ok = 1;
	while (ok)
	{
		try
		{
			// if the y coordinate of the upper right corner is equal to the y coordinate of the lower left corner then the parallelogram is not valid
			if (upperRightCorner.getYCoodinate() == parallelogram.lowerLeftCorner.getYCoodinate())
			{
				// if the x coordinate of the upper right corner is equal to the x coordinate of the lower left corner then the user has entered the same point twice
				if (upperRightCorner.getXCoordinate() == parallelogram.lowerLeftCorner.getXCoordinate())
					throw SamePointError("The same point was entered twice!");
				else
					throw NotParallelError("The y coordinates for the two points are the same, so the sides can't be parallel!");
			}
			else
				// if the x coordinate of the upper right corner is smaller than the x coordinate of the lower left corner then the parallelogram is not valid
				if (upperRightCorner.getXCoordinate() < parallelogram.lowerLeftCorner.getXCoordinate())
					throw RightUpperPointError("The upper right corner was entered incorrectly!");
				else
				{
					// if the input is valid we set the upper right corner of the parallelogram and we set ok to 0 to exit the while loop
					parallelogram.upperRightCorner = upperRightCorner;
					ok = 0;
				}
		}
		catch (SamePointError e)
		{
			cout << e.what() << endl << "Please enter the coodinates again!" << endl;
			console >> upperRightCorner;
		}
		catch (NotParallelError e)
		{
			cout << e.what() << endl << "Please enter the coodinates again!" << endl;
			console >> upperRightCorner;
		}
		catch (RightUpperPointError e)
		{
			cout << e.what() << endl << "Please enter the coodinates again!" << endl;
			console >> upperRightCorner;
		}
	}

	// reading the length of the parallelogram from the console
	cout << "Please enter the length of the side parallel to the x axis: ";
	float length;
	console >> length;

	// to check if the length is valid the ok variable is reset to 1
	// while the length is not valid we read it again
	ok = 1;
	while (ok)
	{
		try
		{
			// if the length is negative then the length is not valid
			if (length < 0)
				throw NegativeLengthError("The length is negative!");
			else
			{
				// if the length is valid we set the length of the parallelogram and we set ok to 0 to exit the while loop
				parallelogram.length = length;
				ok = 0;
			}
		}
		catch (NegativeLengthError e)
		{
			cout << e.what() << endl << "Please enter the length again: ";
			console >> length;
		}
	}

	cout << "Please enter the length of the other side of the parallelogram: ";
	float width;
	console >> width;

	// to check if the width is valid the ok variable is reset to 1
	// while the width is not valid we read it again
	ok = 1;
	while (ok)
	{
		try
		{
			// if the width is negative then the width is not valid
			if (width < 0)
				throw NegativeLengthError("The length is negative!");
			else
			{
				// if the width is valid we set the width of the parallelogram and we set ok to 0 to exit the while loop
				parallelogram.width = width;
				ok = 0;
			}
		}
		catch (NegativeLengthError e)
		{
			cout << e.what() << endl << "Please enter the length again: ";
			console >> width;
		}
	}

	return console;
}

// the overloaded operator << is used to print the information about the Parallelogram to the console
ostream& operator<< (ostream& console, Parallelogram parallelogram)
{
	// we make use of the overloaded operator << from the Point class to print the coordinates of the lower left corner and the upper right corner
	console << "The coordinates for the lower left corner. " << parallelogram.lowerLeftCorner;
	console << "The coordinates for the upper right corner. " << parallelogram.upperRightCorner;


    // we print the length and the width of the parallelogram
	console << "The lenth of the side that's parallel to the x axis is " << parallelogram.length << endl 
		<< "The length of the other sise of th parallelogram is " << parallelogram.width;

	return console;
}



// TRAPEZOID CLASS
// the class Trapezoid inherits from the class Parallelogram
class Trapezoid : public Parallelogram
{
protected:
	// we consider the length attribute defined in the parallelogram class to be the long base of the trapezoid
	// and the width attribute to be the length of the non-parallel sides of the trapezoid
	float shortBase = 0;

	static int half;
public:
	// TRAPEZOID CLASS: CONSTRUCTORS
	// the constructors are declared inside the class and they are defined outside the class
	// the default constructor
	Trapezoid(); 

	// the parameterized constructor 
	Trapezoid(Point lowerLeftCorner, Point upperRightConer, float longBase, float lateralSide, float shortBase);

	// the copy constructor
	Trapezoid(const Trapezoid& trapezoid); 

    // TRAPEZOID CLASS: DESTRUCTOR
	// since we dont have any dynamic data, we don't need to do anything in the destructor
	~Trapezoid() {}

	// TRAPEZOID CLASS: OPERATOR OVERLOADING
	// the assignment operator: it needs to be overloaded inside the class since it needs access to the this pointer
	Trapezoid operator=(Trapezoid source)
	{
		this->lowerLeftCorner = source.lowerLeftCorner;
		this->upperRightCorner = source.upperRightCorner;
		this->length = source.length;
		this->width = source.width;
		this->shortBase = source.shortBase;
		return *this;
	}

	// TRAPEZOID CLASS: METHODS
	// the calculateArea is used to calculate the area of the trapezoid and is overridden here
	void calculateArea()
	{
		// we calculate the area of the trapezoid using the formula for the area of a trapezoid: A = (b1 + b2) * h / 2
		// in order to determinate the hight of the trapezoid we use the y coordinates of the lower left corner and the upper right corner
		cout << "The area of the trapezoid is " << ((shortBase + length) * (upperRightCorner.getYCoodinate() - lowerLeftCorner.getYCoodinate())) * half;
	}

	// the printInfo method is used to print the information about the trapezoid to the console and is overridden here
	void printInfo()
	{
		cout << "Shape: trapez" << endl;

		// we make use of the overriden operator << 
		cout << *this;
		cout << endl;
	}

	// TRAPEZOID CLASS: FRIEND FUNCTIONS
	friend istream& operator>>(istream& consola, Trapezoid& trapez);
	friend ostream& operator<<(ostream& consonla, Trapezoid trapez);
};

// TRAPEZOID CLASS: DEFINITIONS
// the default constructor: it calls the parameterized constructor of the Parallelogram class and sets the short base to 0
Trapezoid::Trapezoid() : Parallelogram(Point(0, 0), Point(0, 0), 0, 0), shortBase(0) {}

// the parameterized constructor: it calls the parameterized constructor of the Parallelogram class and sets the shortBase
Trapezoid::Trapezoid(Point lowerLeftCorner, Point upperRightCorner, float longBase, float lateralSide, float shortBase)
	: Parallelogram(lowerLeftCorner, upperRightCorner, longBase, lateralSide), shortBase(shortBase)
{
	// we need to make sure that the given values are valid
	// if the given values for lengths are negative, then the trapezoid is not valid
	if (longBase < 0 || lateralSide < 0 || shortBase < 0)
		valid = 0;

	// if the y axis coordinates for the lower left corner and upper right corner are the same, then the bases can't be 
	// parallel, so the trapezoid is not valid
	if (lowerLeftCorner.getYCoodinate() == upperRightCorner.getYCoodinate())
		valid = 0;

	// if the value given for the length of the short base is bigger than the value given for the length of the long base
	// then the trapezoid is not valid 
	if (shortBase > longBase)
		valid = 0;
}

// the copy constctor: it calls the parameterized constructor of the Parallelogram class and sets the shortBase
Trapezoid::Trapezoid(const Trapezoid& trapezoid)
	: Parallelogram(trapezoid.lowerLeftCorner, trapezoid.upperRightCorner, trapezoid.length, trapezoid.width), shortBase(trapezoid.shortBase) {}

// the overloaded operator >>: reads the information about the trapezoid from the console
istream& operator>>(istream& console, Trapezoid& trapezoid)
{
	// we read the information about the lower left corner from the console making use of the overloaded operator >> from the Point class
	cout << "Lower left corner coordinates." << endl; console >> trapezoid.lowerLeftCorner;

	// we read the information about the upper right corner and we validate it
	cout << "Punctul din dreapta sus." << endl;
	Point upperRightCorner;
	console >> upperRightCorner;

	// the ok variable is used to make sure that the user enters valid information
	// while the user doesn't enter valid information, the program will keep asking for it
	int ok = 1;
	while (ok)
	{
		try
		{
			// if the y axis coordinates for the lower left corner and upper right corner are the same, then the bases can't be
			// parallel, so the trapezoid is not valid
			if (upperRightCorner.getYCoodinate() == trapezoid.lowerLeftCorner.getYCoodinate())
			{
				// if the x axis coordinates for the lower left corner and upper right corner are the same, 
				// then the trapezoid is not valid
				if (upperRightCorner.getXCoordinate() == trapezoid.lowerLeftCorner.getXCoordinate())
					throw SamePointError("You entered the same coordinates twice!");
				else
					throw NotParallelError("The y coordinates for the two points are the same, so the sides can't be parallel!");
			}
			else
			{
				// if the data was introduced correctly, we set the upper right corner of the trapezoid
				// and we exit the while loop
				trapezoid.upperRightCorner = upperRightCorner;
				ok = 0;
			}
		}
		catch (SamePointError e)
		{
			cout << e.what() << endl << "Please enter the coodinates again!" << endl;
			console >> upperRightCorner;
		}
		catch (NotParallelError e)
		{
			cout << e.what() << endl << "Please enter the coodinates again!" << endl;
			console >> upperRightCorner;
		}
	}

	// we read the information about the short base of the trapezoid and we validate it
	cout << "The length of the short base of the trapezoid: ";
	float length;
	console >> length;

	// the ok variable is set back to 1 and while the user doesn't enter valid information, 
	// the program will keep asking for it
	ok = 1;
	while (ok)
	{
		try
		{
			// if the value given for the length of the short base is negative, then the trapezoid is not valid
			if (length < 0)
				throw NegativeLengthError("The length given for the short base is negative!");
			else
			{
				// if the given length is valid, we set the length of the short base of the trapezoid
				// and we exit the while loop
				trapezoid.shortBase = length;
				ok = 0;
			}
		}
		catch (NegativeLengthError e)
		{
			cout << e.what() << endl << "Please enter the length again!" << endl;
			console >> length;
		}
	}

	// we read the length of the log base of the trapezoid and we validate it
	cout << "The length of the long base of the trapezoid: ";
	console >> length;

	// the ok variable is set back to 1 and while the user doesn't enter valid information,
	// the program will keep asking for it
	ok = 1;
	while (ok)
	{
		try
		{
			// if the value given for the length of the long base is negative, then the trapezoid is not valid
			if (length < 0)
				throw NegativeLengthError("The length given for the long base is negative!");
			else
				if (length < trapezoid.shortBase)
					throw LowerBaseError("The length given for the long base is incorrect!");
				else
				{
					// if the given length is valid, we set the length of the long base of the trapezoid
					// and we exit the while loop
					trapezoid.length = length;
					ok = 0;
				}
		}
		catch (NegativeLengthError e)
		{
			cout << e.what() << endl << "Please enter the length again!" << endl;
			console >> length;
		}
		catch (LowerBaseError e)
		{
			cout << e.what() << endl << "Please enter the length again!" << endl;
			console >> length;
		}
	}

	// we read the length of the lateral side of the trapezoid and we validate it
	cout << "The length of the lateral side of the trapezoid: ";
	console >> length;

	// the ok variable is set back to 1 and while the user doesn't enter valid information,
	// the program will keep asking for it
	ok = 1;
	while (ok)
	{
		try
		{
			// if the value given for the length of the lateral side is negative, then the trapezoid is not valid
			if (length < 0)
				throw NegativeLengthError("The length given for the lateral side is negative!");
			else
			{
				// if the given length is valid, we set the length of the lateral side of the trapezoid
				// and we exit the while loop
				trapezoid.width = length;
				ok = 0;
			}
		}
		catch (NegativeLengthError e)
		{
			cout << e.what() << endl << "Please enter the length again!"<< endl;
			console >> length;
		}
	}

	return console;
}

// th overloaded operator <<: prints the information about the trapezoid to the console
ostream& operator<<(ostream& console, Trapezoid trapezoid)
{
	// in order to print the infrmation about the lower left corner and the upper right corner of the trapezoid,
	// we use the overloaded operator << for the Point class
	console << "Lower left corner. " << trapezoid.lowerLeftCorner;
	console << "Upper right corner. " << trapezoid.upperRightCorner;

	// we print the information about the short base, the long base and the lateral side of the trapezoid
	console << "The length of the short base is " << trapezoid.shortBase << endl;
	console << "The length of the long base is " << trapezoid.length << endl;
	console << "The length of the lateral side is " << trapezoid.width << endl;

	return console;
}

// TRAPEZOID CLASS: STATIC VARIABLE
// the static variable half is initialized 
int Trapezoid::half = 1/2;



// SHAPES CLASS
class Shapes
{
	// SHAPES CLASS: PRIVATE VARIABLES
	Square** shapes;
	int numberOfShapes = 0;

public:
	
	// SHAPES CLASS: CONSTRUCTORS
	// the default constructor
	Shapes() : shapes(nullptr), numberOfShapes(0) {} 

	// SHAPES CLASS: DESTRUCTOR
	~Shapes()
	{
		//  if the array of shapes is not empty, we delete it
		if (shapes != nullptr)
			delete[] shapes;
	}

	// SHAPES CLASS: PUBLIC FUNCTIONS
	void readData()
	{
		cout << endl;
		cout << "----------------------------------ENTER DATA----------------------------------" << endl << endl;

		// we read the number of shapes and we validate it
		cout << "Enter the number of shapes: "; cin >> numberOfShapes;

		// the ok variable is set back to 1 and while the user doesn't enter valid information,
		// the program will keep asking for it
		int ok = 1;
		while (ok)
		{
			if (numberOfShapes < 0)
			{
				cout << "The number of shapes cannot be negative!" << endl;
				cout << "Please enter the number of shapes again: "; cin >> numberOfShapes;
			}
			else
				// if the number of shapes is valid, we exit the while loop
				ok = 0;
		}

		// we allocate memory for the array of shapes
		shapes = new Square * [numberOfShapes + 1];

		// for each shape, we read the data
		for (int i = 1; i <= numberOfShapes; i++)
		{
			cout << endl;
			cout << "------------------What kind of shape would you like to enter?--------------------" << endl << endl;
			cout << "Options: " << endl;
			cout << "1 -> square" << endl;
			cout << "2 -> rectangle" << endl;
			cout << "3 -> rhombus" << endl;
			cout << "4 -> parallelogram" << endl;
			cout << "5 -> trapezoid" << endl << endl;
			cout << "-------------------------------------------------------------------------------" << endl << endl;

			// we read the option and we validate it
			int option;
			cout << "Your option: "; cin >> option;

			// the correct variable is set to 1 and while the user doesn't enter valid information,
			// the program will keep asking for it
			int correct = 1;
			while (correct)
			{
				// 1  -> square
				if (option == 1)
				{
					Square x;
					cout << "Chosen shape: square." << endl;

					// we make use of the overloaded operator >> for the Square class to read the data
					cin >> x;

					// we allocate memory for the shape and we set the shape to the square
					shapes[i] = new Square(x);

					// we set the correct variable to 0 in order to exit the while loop
					correct = 0;
				}
				else
					// 2 -> rectangle
					if (option == 2)
					{
						Rectangle x;
						cout << "Chosen shape: rectangle." << endl;

						// we make use of the overloaded operator >> for the Rectangle class to read the data
						cin >> x;
 
						// we allocate memory for the shape and we set the shape to the rectangle
						shapes[i] = new Rectangle(x);

						// we set the correct variable to 0 in order to exit the while loop
						correct = 0;
					}
					else
						// 3 -> rhombus
						if (option == 3)
						{
							Rhombus x;
							cout << "Chosen shape: rhombus." << endl;

							// we make use of the overloaded operator >> for the Rhombus class to read the data
							cin >> x;

							// we allocate memory for the shape and we set the shape to the rhombus
							shapes[i] = new Rhombus(x);

							// we set the correct variable to 0 in order to exit the while loop
							correct = 0;
						}
						else
							// 4 -> parallelogram
							if (option == 4)
							{
								Parallelogram x;
								cout << "Chosen shape: parallelogram." << endl;

								// we make use of the overloaded operator >> for the Parallelogram class to read the data
								cin >> x;

								// we allocate memory for the shape and we set the shape to the parallelogram
								shapes[i] = new Parallelogram(x);

								// we set the correct variable to 0 in order to exit the while loop
								correct = 0;
							}
							else
								// 5 -> trapezoid
								if (option == 5)
								{
									Trapezoid x;
									cout << "Chosen shape: trapezoid." << endl;

									// we make use of the overloaded operator >> for the Trapezoid class to read the data
									cin >> x;

									// we allocate memory for the shape and we set the shape to the trapezoid
									shapes[i] = new Trapezoid(x);

									// we set the correct variable to 0 in order to exit the while loop
									correct = 0;
								}
								// the user didn't enter a valid option
								else
								{
									cout << endl;
									cout << "Inexistent option!";
									cout << "The options are: " << endl;
									cout << "1 -> square" << endl;
									cout << "2 -> rectangle" << endl;
									cout << "3 -> rhombus" << endl;
									cout << "4 -> parallelogram" << endl;
									cout << "5 -> trapezoid" << endl << endl;
									cout << "Your option: "; cin >> option;
								}
			}
		}

	}

	void printData()
	{
		cout << "----------------------------------PRINT DATA----------------------------------" << endl << endl;

		// if there are no shapes, we print a message
		if (numberOfShapes == 0)
			cout << "There are no shapes!";
		else
			// we print the data for each shape
			for (int i = 1; i <= numberOfShapes; i++)
			{
				cout << endl;
				// we make use of the overriden printInfo() function for each shape
				(*shapes[i]).printInfo();
			}

	}

	static void mathJoke();

	// the meniu function is the one that will be called in the main function
	void menu()
	{
		// the menu runs until the user chooses the option to exit
		while (1)
		{
			// we print the menu: the options and the instructions
			cout << endl;
			cout << "----------------------------WELCOME TO THE GEOMETRIC SHAPES MENU----------------------------";
			cout << endl << endl;
			cout << "The options are: " << endl;
			cout << "0 -> add data" << endl;
			cout << "1 -> print data" << endl;
			cout << "2 -> math joke?" << endl;
			cout << "3 -> exit" << endl << endl;
			cout << "-------------------------------------------------------------------------------" << endl << endl;

			// we read the option and we validate it
			int option;
			cout << "Your option: "; cin >> option;

			// to make sure the user enters a valid option, we use a variable that will be set to 1
			// if the user enters an invalid option, then the program will ask the user to enter a valid option
			int correct = 1;
			while (correct)
			{
				switch (option)
				{
				// 0 -> read data
				case 0:
					// the readData() function is called
					readData();
					// the correct variable is set to 0 in order to exit the while loop
					correct = 0;
					break;
				// 1 -> print data
				case 1:
					// the printData() function is called
					printData();
					// the correct variable is set to 0 in order to exit the while loop
					correct = 0;
					break;
				// 2 -> math joke
				case 2:
					// the mathJoke() function is called
					mathJoke();
					// the correct variable is set to 0 in order to exit the while loop
					correct = 0;
					break;
				case 3:
					return;
				default:
					cout << endl;
					cout << "Invalid option. Please enter a valid option! ";
					cout << "The options are: " << endl;
					cout << "0 -> add data" << endl;
					cout << "1 -> print data" << endl;
					cout << "2 -> math joke?" << endl;
					cout << "3 -> exit" << endl << endl;
					cout << "Your option: "; cin >> option;
				}
			}
		}
	}
};

void Shapes::mathJoke()
{
	cout << endl << "------------------------------MATH JOKE!-------------------------------" << endl << endl;
	cout << "Parallel lines have so much in common…" << endl; 
	cout << "It’s a shame that they’ll never meet!" << endl;
}

int main()
{
	Shapes formeGeometrice;
	formeGeometrice.menu();
}

