# 📐 Geometric Class Hierarchy OOP Project

This C++ project was developed as part of an introductory Object-Oriented Programming (OOP) course during the first year studying CS @ Faculty of Mathematics and Computer Science, University of Bucharest. The project focuses on implementing a geometric class hierarchy, showcasing fundamental principles of object-oriented design.

## 🌐 Overview

The project features a hierarchy of geometric classes, each designed to represent specific shapes. These classes include:

- `Point`: Represents a point in a 2D plane with coordinates (x, y).
- `Square`: Defined by a bottom-left point and a side length.
- `Rectangle`: A specialized form of a square with an additional side length.
- `Rhombus`: Formed by specifying the opposite corner point of a square.
- `Parallelogram`: Inherits from `Rectangle` and `Rhombus`.
- `Trapezoid`: Inherits from `Parallelogram`.

The classes adhere to the guidelines set forth in the OOP course, featuring parameterized constructors, destructors, and calculation methods for area. Additionally, the project emphasizes the importance of ensuring valid member data, with constructors verifying the parallelism of sides etc.

## 📋 Project Requirements

### Classes

- **Point (float x, float y):** Represents a 2D point in the plane.

- **Square (Point left_bottom, float side):** Defined by a bottom-left point and a side length.

- **Rectangle (float side2) : Square:** A specialized form of a square with an additional side length.

- **Rhombus (Opposite corner point): Square:** Formed by specifying the opposite corner point of a square.

- **Parallelogram: Rectangle, Rhombus:** Inherits characteristics from both Rectangle and Rhombus.

- **Trapezoid (float base2): Parallelogram:** Inherits from Parallelogram.

### Common Features

- All figures have two sides parallel to the Ox axis.

- Derived classes must include parameterized constructors highlighting the transmission of parameters to the base class constructor.

- Destructors are implemented.

- Member functions include calculation methods for area.

- Valid member data has a value of 1 if the figure is specified correctly.

- Constructors validate the parallelism of the sides.

## 🛠️ Functionalities 

### Calculation Methods

- **Area Calculation:**
  - Access methods in each class to calculate the area of the respective geometric shape.

### Validation

- **Parallelism Check:**
  - Ensure that all shapes maintain the requirement of having two sides parallel to the Ox axis.

- **Data Validity:**
  - Verify the validity of member data. 
 
### Menu

- **Shapes Class Menu:**
  - The `Shapes` class provides a menu for easy interaction with the geometric shapes.
    - Explore options to create different shapes, calculate their areas, and validate their properties.
    - Conveniently navigate the functionalities of the geometric class hierarchy.
