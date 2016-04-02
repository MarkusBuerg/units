# units <a href="https://travis-ci.org/nholthaus/units" target="_blank"><img src="https://travis-ci.org/nholthaus/units.svg?branch=master"/></a> <a href="https://ci.appveyor.com/project/nholthaus/units" target="_blank"><img src="https://ci.appveyor.com/api/projects/status/github/nholthaus/units?svg=true"/></a>
a compile-time, header-only, unit conversion library built on c++14 with no dependencies.

Latest Release - v2.0.0
--------

New features:
 - Compile-time unit arithmetic via `unit_value_t`
 - Unit-enabled ports of most `<cmath>` functions, including c++11 extensions.
 - Square-root manipulators for `unit`, `unit_t`, and `unit_value_t`
 - Improved documentation

Tested on:
 - gcc -4.9
 - msvc2013
 - msvc2015

<a href="https://github.com/nholthaus/units/releases/tag/v2.0.0" target="_blank">Download units v2.0.0</a>

Description
-----------

The library consists of a single file (include/units.h), plus unit tests. To incorporate the library into your project, simply copy the header into a location in your include path. A CMake project is included to build the unit tests and documentation if desired.


Complex, recurively-defined conversions are performed in just 2 floating-point arithmetic instructions:

		year_t twoYears(2.0);
		week_t twoYearsInWeeks = twoYears;
	00007FF7BDB57FF6  xorps       xmm9,xmm9  
	00007FF7BDB57FFA  cvtsi2sd    xmm9,rax  
	00007FF7BDB57FFF  mulsd       xmm9,mmword ptr [__real@4000000000000000 (07FF7BDBB31A0h)]  
	00007FF7BDB58008  divsd       xmm9,mmword ptr [__real@401c000000000000 (07FF7BDBB33C0h)]  
	00007FF7BDB58011  movsd       mmword ptr [rbp+6Fh],xmm9  
		EXPECT_EQ(week_t(104.286), twoYearsInWeeks);
	00007FF7BDB58017  ...

An explanation of the instructions can be found at: http://stackoverflow.com/questions/35103741/what-is-the-purpose-of-xorps-on-the-same-register/35103871#35103871

In the library, the year to week conversion is defined in terms of
years -> days -> hours -> minutes -> seconds -> minutes -> hours -> days -> weeks
but the total conversion ratio is computed at compile-time and the math is optimized to two floating-point operations.

Unit conversions between equivalent types are optimized away completely, and generate no machine code.

Defining new units is simple, as they can be recursively defined as ratio of previously-defined units in a way that mimics natural language and is highly readable:

	namespace time
	{
		using seconds = unit<std::ratio<1>, category::time_unit>;
		using minutes = unit<std::ratio<60>, seconds>;
		using hours = unit<std::ratio<60>, minutes>;
		using days = unit<std::ratio<24>, hours>;
		using weeks = unit<std::ratio<7>, days>;
		using years = unit<std::ratio<365>, days>;
	}

Compound units are defined in a similar manner, with additional helper functions for polynomials:

	using acceleration = compound_unit<meters, inverse<squared<seconds>>>;
	
The preferred method of conversion is implicitly though the use of unit containers, however unit conversion can be accomplished using `units::convert` for arithmetic types:

	double val_in = convert<feet, inches>(1.0);	// val_in == 12.0
	
For type-safe conversion, see the next section.

The unit test file `unitTests/main.cpp` contains example usage of every type, trait, and function contained in the library, and while not exactly user-friendly, can be a valuable resource.

Unit containers
---------------

In addition to providing unit tags to perform conversion, the library also provides container types. Containers are derived from the `unit_t` class, and have the form `[unitname]_t`, e.g. `meter_t`. Containers provide additional advanges over template tag conversions, without any increase in overhead, thanks to the c++ type system.

Unit containers are defined in terms of the units they represent, the underlying type of the container, and an optional non-linear scale (think decibels or richter scale). For example, `meter_t` would be defined: 

   using meter_t = unit_t<length::meter, double, linear_scale>

or simply 

    using meter_t = unit_t<length::meter>

since the underlying type and scale parameters default to `double` and `linear_scale` respectively. Defifining your own units is simple, and the standard SI prefixes, as well as `inverse`, `squared`, and `cubed` templates are provided to make it even easier.

Units of compatible types (e.g length units) can be implicitely converted/assigned to one another. Units (with the exception of dimensionless types) cannot be implicitely converted to/from built-in types. They can be constructed from built-in types, and operator() can be used to retrieve a built-in type value. That said, the user should prefer to operate within the unit type-space as much as is practical. 

Unit containers provide type safety and dimensional analysis for mathematical operations. for instance, the velocity of an object can be calculated:

    auto objectVelocity = meter_t(100.0) / second_t(2.0);

The resulting velocity type will be deduced to be `velocity::meters_per_second` with a value of 50.0. Additionally, if the return type if specified, the type system wll verify that the units are compatible. For example, the following will fail to compile:

    velocity::meters_per_second objectVelocity = square_meter_t(100.0) / second_t(2.0); // Error: cannot convert.`

Unit containers can (and should!) be used to perform implicit conversions:

	second_t a;
	minute_t b(1.0);
	
	a = b;	// a == 60.0

Unsupported arithmetic, or improper return types will result in compiler errors:

	using namespace units::length;
	
	meter_t a_m(1.0), b_m(2.0), c_m;
	foot_t	a_ft(1.0), b_ft(2.0), c_ft;
	
	c_m = a_m + b_m;							// OK. c == 3m
	c_ft = a_m + b_m;							// OK. resulting 3m is converted to ft.
	auto result = a_m * b_ft;					// OK. result is `meter_t` (left-most unit)
	
	c_m = a_m + 5.0;							// Error. can't add scalars to dimensioned units.
	c_m = a_m + scalar_t(5.0);					// Error. can't add scalars to dimensioned units.
	auto result = a_m + square_meter_t(1.0);	// Error. Incompatible units.
	
	auto result = a_m * square_meter_t(1.0);	// OK. units can always be multiplied. Result is `cubed<meter_t>`.
	auto result = a_m * scalar_t(1.0); 			// OK. units can always be multiplied. Result is `meter_t`.
	
`<cmath>` Functions
-------------------

The `units` library include type-safe unit_t container wrappers for almost all of the <cmath> functions, _including_ the c++11 extensions. These functions can be found in the `units::math` namespace. The `units` library versions don't conflict with <cmath>, and it's possible to use both libraries in the same code. 

The overloaded functions ensure that only the proper unit types are accepted into the functions, and that the return value type matches the expected units, all without needing to result to the type-unsafe `toDouble()` member.

In _rare_ cases, the overload resolution for a given type may be ambiguous. If so, simply preprend the function with the fully-qualified `units::math` prefix, e.g.

    meter_t x(2.0);
	meter_t y(3.0);
	square_meter_t z(1.0);
	square_meter_t result;
	
	result = fma(x, y, z);												// Error: ambiguous
	double result = fma(x.toDouble(), y.toDouble(), z.toDouble());		// <cmath> option. Bad. This works, but is type-unsafe and cumbersome!
	result = math::fma(x, y, z);										// units::math option. OK. Simple and type-safe. 
	
Exponentials and Square Roots
-----------------------------

Many functions require units to be raised to some power. This can be accomplished using the `units::math::pow` function:

	using units::math;
	
	square_meter_t m2 = pow<2>(meter_t(5.0));	// m2 == 25.0
		
The only constraint is that the exponential power (given in the template argument) must be known at compile time, so that the type system can deduce the output type. This differs from the `<cmath> pow` implementation, which takes exponent values at runtime.

Square roots are also provided with the `units::math::sqrt` function. Due to the nature of the `sqrt` operation, the units library can often provide exact conversions for square root operations, but _not in every case_. The rest of the time, the `sqrt` unit will be a _rational_approximation_ of the real value. These are guaranteed to be accurate to at least 10 decimal places.

	using units::math;
	
	meter_t m = sqrt(square_meter_t(4.0));		// m == 2.0
	
Compile-time Unit Manipulation
------------------------------


Namespaces
----------

Unit tags and containers are split into separate namespaces to avoid conflicting unit names which represent different physical quantities.

Unit tag and unit_t container definitions are defined in the following namespaces:
 - units::length
 - units::mass
 - units::time
 - units::angle (plane)
 - units::current
 - units::temperature
 - units::substance (amount of, i.e. moles)
 - units::luminous_intensity
 - units::solid_angle
 - units::frequency
 - units::velocity
 - units::angular_velocity
 - units::acceleration
 - units::force
 - units::pressure
 - units::charge
 - units::energy
 - units::power
 - units::voltage
 - units::capacitance
 - units::impedance
 - units::magnetic_flux
 - units::magnetic_field_strength
 - units::inductance
 - units::luminous_flux
 - units::illuminance
 - units::radiation
 - units::torque
 - units::area
 - units::volume
 - units::density
 - units::concentration
 - units::constants (scalar and non-scalar physical constants like Avagadro's number)
 
Mathematical operations like `sin`, `log`, `floor`, etc are defined in the following namespaces:
 - units::math
 
Type traits that you can use to test unit types are defined in the following namespaces:
 - units::traits

Build Instructions
------------------

The library itself consists of a single header (include/units.h), and can be included into your project without being built. 

The unit tests and documentation can be built with CMake. A doxygen installation is required to generate the documentation, and a Tex install is needed if pdf documentation is desired.

To build the tests:

Windows:
 1. Ensure cmake is installed, and that the `bin` directory is in your %PATH% variable, and that a compiler like `Visual Studio 2015 Community Edition` is installed.
 2. clone the repository or download the `.zip` package.
 3. Open a `cmd` terminal and navigate to the source directory.
 4. Type the following commands:
   - `md build`
   - `cd build`
   - `cmake -Wno-dev ..`
   - `cmake --build . --config Release`
 5. The tests will be created in an executable called `unitLibTest.exe` in the folder `build/unitTests/Release`.
   
Linux:
 1. Ensure you are using cmake 3.2 or later. You can verify this with `cmake --version`.
 2. Ensure you are using gcc version 4.9 or greater. You can verify this with `gcc --version`.
 3. clone the repository or download the `.tar.gz` package.
 4. Open a terminal and navigate to the source directory.
 5. Type the following commands:
   - `mkdir build`
   - `cd build`
   - `cmake -Wno-dev ..`
   - `cmake --build . --config Release`
 6. The tests will be created in an executable called `unitLibTest` in the folder `build/unitTests`.

Previous Releases
--------

 - v1.3.0 - Adds ostream support. bug fixes.  Tested with gcc-4.9.2, msvc2013, msvc2015.
 - v1.2.2 - Bug fixes (#1) and namespace cleanup. Tested with msvc2015, gcc 5.2.1
 - v1.2.0 - Adds angular velocity units. Tested with gcc-4.9.2, msvc2013, msvc2015.
 - v1.1.1 - Adds Doxygen and additional type traits. Tested with gcc-4.9.2, msvc2013, msvc2015.
 - v1.0.0 - Initial release. Tested with msvc2015