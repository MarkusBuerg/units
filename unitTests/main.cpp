#include <units.h>
#include <gtest/gtest.h>
#include <chrono>
#include <string>
#include <type_traits>
#include <array>

using namespace units;
using namespace units::length;
using namespace units::mass;
using namespace units::angle;
using namespace units::time;
using namespace units::frequency;
using namespace units::area;
using namespace units::velocity;
using namespace units::angular_velocity;
using namespace units::temperature;
using namespace units::luminous_intensity;
using namespace units::solid_angle;
using namespace units::frequency;
using namespace units::acceleration;
using namespace units::pressure;
using namespace units::charge;
using namespace units::energy;
using namespace units::power;
using namespace units::voltage;
using namespace units::capacitance;
using namespace units::impedance;
using namespace units::conductance;
using namespace units::magnetic_flux;
using namespace units::magnetic_field_strength;
using namespace units::inductance;
using namespace units::luminous_flux;
using namespace units::illuminance;
using namespace units::radiation;
using namespace units::torque;
using namespace units::volume;
using namespace units::density;
using namespace units::concentration;
using namespace units::data;
using namespace units::data_transfer_rate;
using namespace units::literals;

namespace {

	class TypeTraits : public ::testing::Test {
	protected:

		TypeTraits() {};
		virtual ~TypeTraits() {};
		void SetUp() override {};
		void TearDown() override {};
	};

	class STDTypeTraits : public ::testing::Test
	{
	protected:

		STDTypeTraits() {};
		virtual ~STDTypeTraits() {};
		void SetUp() override {};
		void TearDown() override {};
	};

	class UnitManipulators : public ::testing::Test {
	protected:

		UnitManipulators() {};
		virtual ~UnitManipulators() {};
		void SetUp() override {};
		void TearDown() override {};
	};

	class UnitContainer : public ::testing::Test {
	protected:

		UnitContainer() {};
		virtual ~UnitContainer() {};
		void SetUp() override {};
		void TearDown() override {};
	};

	class UnitConversion : public ::testing::Test {
	protected:

		UnitConversion() {};
		virtual ~UnitConversion() {};
		void SetUp() override {};
		void TearDown() override {};
	};

	class UnitMath : public ::testing::Test {
	protected:

		UnitMath() {};
		virtual ~UnitMath() {};
		void SetUp() override {};
		void TearDown() override {};
	};

	class CompileTimeArithmetic : public ::testing::Test {
	protected:

		CompileTimeArithmetic() {};
		virtual ~CompileTimeArithmetic() {};
		void SetUp() override {};
		void TearDown() override {};
	};

	class Constexpr : public ::testing::Test {
	protected:

		Constexpr() {};
		virtual ~Constexpr() {};
		void SetUp() override {};
		void TearDown() override {};
	};

	class CaseStudies : public ::testing::Test {
	protected:

		CaseStudies() {};
		virtual ~CaseStudies() {};
		void SetUp() override {};
		void TearDown() override {};
	};
}

TEST_F(TypeTraits, isRatio)
{
	EXPECT_TRUE(traits::is_ratio_v<std::ratio<1>>);
	EXPECT_FALSE(traits::is_ratio_v<double>);
}

TEST_F(TypeTraits, ratio_sqrt)
{
	using rt2 = ratio_sqrt<std::ratio<2>>;
	EXPECT_LT(std::abs(std::sqrt(2 / (double)1) - rt2::num / (double)rt2::den), 5e-9);

	using rt4 = ratio_sqrt<std::ratio<4>>;
	EXPECT_LT(std::abs(std::sqrt(4 / (double)1) - rt4::num / (double)rt4::den), 5e-9);

	using rt10 = ratio_sqrt<std::ratio<10>>;
	EXPECT_LT(std::abs(std::sqrt(10 / (double)1) - rt10::num / (double)rt10::den), 5e-9);

	using rt30 = ratio_sqrt<std::ratio<30>>;
	EXPECT_LT(std::abs(std::sqrt(30 / (double)1) - rt30::num / (double)rt30::den), 5e-9);

	using rt61 = ratio_sqrt<std::ratio<61>>;
	EXPECT_LT(std::abs(std::sqrt(61 / (double)1) - rt61::num / (double)rt61::den), 5e-9);

	using rt100 = ratio_sqrt<std::ratio<100>>;
	EXPECT_LT(std::abs(std::sqrt(100 / (double)1) - rt100::num / (double)rt100::den), 5e-9);

	using rt1000 = ratio_sqrt<std::ratio<1000>>;
	EXPECT_LT(std::abs(std::sqrt(1000 / (double)1) - rt1000::num / (double)rt1000::den), 5e-9);

	using rt10000 = ratio_sqrt<std::ratio<10000>>;
	EXPECT_LT(std::abs(std::sqrt(10000 / (double)1) - rt10000::num / (double)rt10000::den), 5e-9);
}

TEST_F(TypeTraits, is_unit_conversion)
{
	EXPECT_FALSE(traits::is_unit_conversion_v<std::ratio<1>>);
	EXPECT_FALSE(traits::is_unit_conversion_v<double>);
	EXPECT_TRUE(traits::is_unit_conversion_v<meters>);
	EXPECT_TRUE(traits::is_unit_conversion_v<feet>);
	EXPECT_TRUE(traits::is_unit_conversion_v<degrees_squared>);
	EXPECT_FALSE(traits::is_unit_conversion_v<meter_t>);
}

TEST_F(TypeTraits, is_unit_t)
{
	EXPECT_FALSE(traits::is_unit_v<std::ratio<1>>);
	EXPECT_FALSE(traits::is_unit_v<double>);
	EXPECT_FALSE(traits::is_unit_v<meters>);
	EXPECT_FALSE(traits::is_unit_v<feet>);
	EXPECT_FALSE(traits::is_unit_v<degrees_squared>);
	EXPECT_TRUE(traits::is_unit_v<meter_t>);
}

TEST_F(TypeTraits, unit_conversion_traits)
{
	EXPECT_TRUE((std::is_same_v<void, traits::unit_conversion_traits<double>::conversion_ratio>));
	EXPECT_FALSE((std::is_same_v<void, traits::unit_conversion_traits<meters>::conversion_ratio>));
}

TEST_F(TypeTraits, unit_traits)
{
	EXPECT_TRUE((std::is_same_v<void, traits::unit_traits<double>::underlying_type>));
	EXPECT_TRUE((std::is_same_v<UNIT_LIB_DEFAULT_TYPE, traits::unit_traits<meter_t>::underlying_type>));
	EXPECT_TRUE((std::is_same_v<void, traits::unit_traits<double>::value_type>));
	EXPECT_TRUE((std::is_same_v<UNIT_LIB_DEFAULT_TYPE, traits::unit_traits<meter_t>::value_type>));
}

TEST_F(TypeTraits, is_convertible_unit)
{
	EXPECT_TRUE((traits::is_convertible_unit_conversion_v<meters, meters>));
	EXPECT_TRUE((traits::is_convertible_unit_conversion_v<meters, astronicalUnits>));
	EXPECT_TRUE((traits::is_convertible_unit_conversion_v<meters, parsecs>));

	EXPECT_TRUE((traits::is_convertible_unit_conversion_v<meters, meters>));
	EXPECT_TRUE((traits::is_convertible_unit_conversion_v<astronicalUnits, meters>));
	EXPECT_TRUE((traits::is_convertible_unit_conversion_v<parsecs, meters>));
	EXPECT_TRUE((traits::is_convertible_unit_conversion_v<years, weeks>));

	EXPECT_FALSE((traits::is_convertible_unit_conversion_v<meters, seconds>));
	EXPECT_FALSE((traits::is_convertible_unit_conversion_v<seconds, meters>));
	EXPECT_FALSE((traits::is_convertible_unit_conversion_v<years, meters>));
}

TEST_F(TypeTraits, inverse)
{
	double test;

	using htz = inverse<seconds>;
	bool shouldBeTrue = std::is_same_v<htz, hertz>;
	EXPECT_TRUE(shouldBeTrue);

	test = convert<unit<inverse<fahrenheit>>>(unit<inverse<celsius>>(1.0))();
	EXPECT_NEAR(5.0 / 9.0, test, 5.0e-5);

	test = convert<unit<inverse<fahrenheit>>>(unit<inverse<kelvin>>(6.0))();
	EXPECT_NEAR(10.0 / 3.0, test, 5.0e-5);
}

TEST_F(TypeTraits, dimension_of)
{
	using dim = traits::dimension_of_t<years>;

	EXPECT_TRUE((std::is_same_v<dim, dimension::time>));
	EXPECT_FALSE((std::is_same_v<dim, dimension::length>));
	EXPECT_FALSE((std::is_same_v<dim, units::time::days>));

	using dim2 = typename traits::unit_conversion_traits<typename traits::unit_traits<decltype(meters_per_second_t(5)) > ::unit_conversion > ::dimension_type;

	EXPECT_TRUE((std::is_same_v<dim2, dimension::velocity>));
	EXPECT_FALSE((std::is_same_v<dim2, dimension::time>));
	EXPECT_FALSE((std::is_same_v<dim2, units::velocity::mph>));
}

TEST_F(TypeTraits, has_linear_scale)
{
	EXPECT_TRUE((traits::has_linear_scale_v<dimensionless>));
	EXPECT_TRUE((traits::has_linear_scale_v<meter_t>));
	EXPECT_TRUE((traits::has_linear_scale_v<foot_t>));
	EXPECT_TRUE((traits::has_linear_scale_v<watt_t, dimensionless>));
	EXPECT_TRUE((traits::has_linear_scale_v<dimensionless, meter_t>));
	EXPECT_TRUE((traits::has_linear_scale_v<meters_per_second_t>));
	EXPECT_FALSE((traits::has_linear_scale_v<dB_t>));
	EXPECT_FALSE((traits::has_linear_scale_v<dB_t, meters_per_second_t>));
}

TEST_F(TypeTraits, has_decibel_scale)
{
	EXPECT_FALSE((traits::has_decibel_scale_v<dimensionless>));
	EXPECT_FALSE((traits::has_decibel_scale_v<meter_t>));
	EXPECT_FALSE((traits::has_decibel_scale_v<foot_t>));
	EXPECT_TRUE((traits::has_decibel_scale_v<dB_t>));
	EXPECT_TRUE((traits::has_decibel_scale_v<dBW_t>));

	EXPECT_TRUE((traits::has_decibel_scale_v<dBW_t, dB_t>));
	EXPECT_TRUE((traits::has_decibel_scale_v<dBW_t, dBm_t>));
	EXPECT_TRUE((traits::has_decibel_scale_v<dB_t, dB_t>));
	EXPECT_TRUE((traits::has_decibel_scale_v<dB_t, dB_t, dB_t>));
	EXPECT_FALSE((traits::has_decibel_scale_v<dB_t, dB_t, meter_t>));
	EXPECT_FALSE((traits::has_decibel_scale_v<meter_t, dB_t>));
}

TEST_F(TypeTraits, has_same_scale)
{
	EXPECT_TRUE((traits::has_same_scale_v<dimensionless, dimensionless>));
	EXPECT_TRUE((traits::has_same_scale_v<dB_t, dBW_t>));
	EXPECT_FALSE((traits::has_same_scale_v<dB_t, dimensionless>));

 	EXPECT_TRUE((traits::has_same_scale_v<dB_t, dBW_t, dBW_t>));
 	EXPECT_FALSE((traits::has_same_scale_v<dB_t, dBW_t, meter_t>));
}

TEST_F(TypeTraits, is_dimensionless_unit)
{
	EXPECT_TRUE((traits::is_dimensionless_unit_v<dimensionless>));
	EXPECT_TRUE((traits::is_dimensionless_unit_v<const dimensionless>));
	EXPECT_TRUE((traits::is_dimensionless_unit_v<const dimensionless&>));
	EXPECT_TRUE((traits::is_dimensionless_unit_v<dimensionless>));
	EXPECT_TRUE((traits::is_dimensionless_unit_v<dB_t>));
	EXPECT_TRUE((traits::is_dimensionless_unit_v<dB_t, dimensionless>));
	EXPECT_TRUE((traits::is_dimensionless_unit_v<ppm_t>));
	EXPECT_FALSE((traits::is_dimensionless_unit_v<meter_t>));
	EXPECT_FALSE((traits::is_dimensionless_unit_v<dBW_t>));
	EXPECT_FALSE((traits::is_dimensionless_unit_v<dBW_t, dimensionless>));
}

TEST_F(TypeTraits, is_length_unit)
{
	EXPECT_TRUE((traits::is_length_unit_v<meter>));
	EXPECT_TRUE((traits::is_length_unit_v<cubit>));
	EXPECT_FALSE((traits::is_length_unit_v<year>));
	EXPECT_FALSE((traits::is_length_unit_v<double>));

	EXPECT_TRUE((traits::is_length_unit_v<meter_t>));
	EXPECT_TRUE((traits::is_length_unit_v<const meter_t>));
	EXPECT_TRUE((traits::is_length_unit_v<const meter_t&>));
	EXPECT_TRUE((traits::is_length_unit_v<cubit_t>));
	EXPECT_FALSE((traits::is_length_unit_v<year_t>));
	EXPECT_TRUE((traits::is_length_unit_v<meter_t, cubit_t>));
	EXPECT_FALSE((traits::is_length_unit_v<meter_t, year_t>));
}

TEST_F(TypeTraits, is_mass_unit)
{

	EXPECT_TRUE((traits::is_mass_unit_v<kilogram>));
	EXPECT_TRUE((traits::is_mass_unit_v<stone>));
	EXPECT_FALSE((traits::is_mass_unit_v<meter>));
	EXPECT_FALSE((traits::is_mass_unit_v<double>));

	EXPECT_TRUE((traits::is_mass_unit_v<kilogram_t>));
	EXPECT_TRUE((traits::is_mass_unit_v<const kilogram_t>));
	EXPECT_TRUE((traits::is_mass_unit_v<const kilogram_t&>));
	EXPECT_TRUE((traits::is_mass_unit_v<stone_t>));
	EXPECT_FALSE((traits::is_mass_unit_v<meter_t>));
	EXPECT_TRUE((traits::is_mass_unit_v<kilogram_t, stone_t>));
	EXPECT_FALSE((traits::is_mass_unit_v<kilogram_t, meter_t>));
}


TEST_F(TypeTraits, is_time_unit)
{

	EXPECT_TRUE((traits::is_time_unit_v<second>));
	EXPECT_TRUE((traits::is_time_unit_v<year>));
	EXPECT_FALSE((traits::is_time_unit_v<meter>));
	EXPECT_FALSE((traits::is_time_unit_v<double>));

	EXPECT_TRUE((traits::is_time_unit_v<second_t>));
	EXPECT_TRUE((traits::is_time_unit_v<const second_t>));
	EXPECT_TRUE((traits::is_time_unit_v<const second_t&>));
	EXPECT_TRUE((traits::is_time_unit_v<year_t>));
	EXPECT_FALSE((traits::is_time_unit_v<meter_t>));
	EXPECT_TRUE((traits::is_time_unit_v<second_t, year_t>));
	EXPECT_FALSE((traits::is_time_unit_v<second_t, meter_t>));
}

TEST_F(TypeTraits, is_angle_unit)
{

	EXPECT_TRUE((traits::is_angle_unit_v<angle::radian>));
	EXPECT_TRUE((traits::is_angle_unit_v<angle::degree>));
	EXPECT_FALSE((traits::is_angle_unit_v<watt>));
	EXPECT_FALSE((traits::is_angle_unit_v<double>));

	EXPECT_TRUE((traits::is_angle_unit_v<angle::radian_t>));
	EXPECT_TRUE((traits::is_angle_unit_v<const angle::radian_t>));
	EXPECT_TRUE((traits::is_angle_unit_v<const angle::radian_t&>));
	EXPECT_TRUE((traits::is_angle_unit_v<angle::degree_t>));
	EXPECT_FALSE((traits::is_angle_unit_v<watt_t>));
	EXPECT_TRUE((traits::is_angle_unit_v<angle::radian_t, angle::degree_t>));
	EXPECT_FALSE((traits::is_angle_unit_v<angle::radian_t, watt_t>));
}

TEST_F(TypeTraits, is_current_unit)
{

	EXPECT_TRUE((traits::is_current_unit_v<current::ampere>));
	EXPECT_FALSE((traits::is_current_unit_v<volt>));
	EXPECT_FALSE((traits::is_current_unit_v<double>));

	EXPECT_TRUE((traits::is_current_unit_v<current::ampere_t>));
	EXPECT_TRUE((traits::is_current_unit_v<const current::ampere_t>));
	EXPECT_TRUE((traits::is_current_unit_v<const current::ampere_t&>));
	EXPECT_FALSE((traits::is_current_unit_v<volt_t>));
	EXPECT_TRUE((traits::is_current_unit_v<current::ampere_t, current::milliampere_t>));
	EXPECT_FALSE((traits::is_current_unit_v<current::ampere_t, volt_t>));
}

TEST_F(TypeTraits, is_temperature_unit)
{

	EXPECT_TRUE((traits::is_temperature_unit_v<fahrenheit>));
	EXPECT_TRUE((traits::is_temperature_unit_v<kelvin>));
	EXPECT_FALSE((traits::is_temperature_unit_v<cubit>));
	EXPECT_FALSE((traits::is_temperature_unit_v<double>));

	EXPECT_TRUE((traits::is_temperature_unit_v<fahrenheit_t>));
	EXPECT_TRUE((traits::is_temperature_unit_v<const fahrenheit_t>));
	EXPECT_TRUE((traits::is_temperature_unit_v<const fahrenheit_t&>));
	EXPECT_TRUE((traits::is_temperature_unit_v<kelvin_t>));
	EXPECT_FALSE((traits::is_temperature_unit_v<cubit_t>));
	EXPECT_TRUE((traits::is_temperature_unit_v<fahrenheit_t, kelvin_t>));
	EXPECT_FALSE((traits::is_temperature_unit_v<cubit_t, fahrenheit_t>));
}

TEST_F(TypeTraits, is_substance_unit)
{

	EXPECT_TRUE((traits::is_substance_unit_v<substance::mol>));
	EXPECT_FALSE((traits::is_substance_unit_v<year>));
	EXPECT_FALSE((traits::is_substance_unit_v<double>));

	EXPECT_TRUE((traits::is_substance_unit_v<substance::mole_t>));
	EXPECT_TRUE((traits::is_substance_unit_v<const substance::mole_t>));
	EXPECT_TRUE((traits::is_substance_unit_v<const substance::mole_t&>));
	EXPECT_FALSE((traits::is_substance_unit_v<year_t>));
	EXPECT_TRUE((traits::is_substance_unit_v<substance::mole_t, substance::mole_t>));
	EXPECT_FALSE((traits::is_substance_unit_v<year_t, substance::mole_t>));
}

TEST_F(TypeTraits, is_luminous_intensity_unit)
{

	EXPECT_TRUE((traits::is_luminous_intensity_unit_v<candela>));
	EXPECT_FALSE((traits::is_luminous_intensity_unit_v<units::radiation::rad>));
	EXPECT_FALSE((traits::is_luminous_intensity_unit_v<double>));

	EXPECT_TRUE((traits::is_luminous_intensity_unit_v<candela_t>));
	EXPECT_TRUE((traits::is_luminous_intensity_unit_v<const candela_t>));
	EXPECT_TRUE((traits::is_luminous_intensity_unit_v<const candela_t&>));
	EXPECT_FALSE((traits::is_luminous_intensity_unit_v<rad_t>));
	EXPECT_TRUE((traits::is_luminous_intensity_unit_v<candela_t, candela_t>));
	EXPECT_FALSE((traits::is_luminous_intensity_unit_v<rad_t, candela_t>));
}

TEST_F(TypeTraits, is_solid_angle_unit)
{

	EXPECT_TRUE((traits::is_solid_angle_unit_v<steradian>));
	EXPECT_TRUE((traits::is_solid_angle_unit_v<degree_squared>));
	EXPECT_FALSE((traits::is_solid_angle_unit_v<angle::degree>));
	EXPECT_FALSE((traits::is_solid_angle_unit_v<double>));

	EXPECT_TRUE((traits::is_solid_angle_unit_v<steradian_t>));
	EXPECT_TRUE((traits::is_solid_angle_unit_v<const steradian_t>));
	EXPECT_TRUE((traits::is_solid_angle_unit_v<const degree_squared_t&>));
	EXPECT_FALSE((traits::is_solid_angle_unit_v<angle::degree_t>));
	EXPECT_TRUE((traits::is_solid_angle_unit_v<degree_squared_t, steradian_t>));
	EXPECT_FALSE((traits::is_solid_angle_unit_v<angle::degree_t, steradian_t>));
}

TEST_F(TypeTraits, is_frequency_unit)
{

	EXPECT_TRUE((traits::is_frequency_unit_v<hertz>));
	EXPECT_FALSE((traits::is_frequency_unit_v<second>));
	EXPECT_FALSE((traits::is_frequency_unit_v<double>));

	EXPECT_TRUE((traits::is_frequency_unit_v<hertz_t>));
	EXPECT_TRUE((traits::is_frequency_unit_v<const hertz_t>));
	EXPECT_TRUE((traits::is_frequency_unit_v<const hertz_t&>));
	EXPECT_FALSE((traits::is_frequency_unit_v<second_t>));
	EXPECT_TRUE((traits::is_frequency_unit_v<const hertz_t&, gigahertz_t>));
	EXPECT_FALSE((traits::is_frequency_unit_v<second_t, hertz_t>));
}

TEST_F(TypeTraits, is_velocity_unit)
{

	EXPECT_TRUE((traits::is_velocity_unit_v<meters_per_second>));
	EXPECT_TRUE((traits::is_velocity_unit_v<miles_per_hour>));
	EXPECT_FALSE((traits::is_velocity_unit_v<meters_per_second_squared>));
	EXPECT_FALSE((traits::is_velocity_unit_v<double>));

	EXPECT_TRUE((traits::is_velocity_unit_v<meters_per_second_t>));
	EXPECT_TRUE((traits::is_velocity_unit_v<const meters_per_second_t>));
	EXPECT_TRUE((traits::is_velocity_unit_v<const meters_per_second_t&>));
	EXPECT_TRUE((traits::is_velocity_unit_v<miles_per_hour_t>));
	EXPECT_FALSE((traits::is_velocity_unit_v<meters_per_second_squared_t>));
	EXPECT_TRUE((traits::is_velocity_unit_v<miles_per_hour_t, meters_per_second_t>));
	EXPECT_FALSE((traits::is_velocity_unit_v<meters_per_second_squared_t, meters_per_second_t>));
}

TEST_F(TypeTraits, is_acceleration_unit)
{
	EXPECT_TRUE((traits::is_acceleration_unit_v<meters_per_second_squared>));
	EXPECT_TRUE((traits::is_acceleration_unit_v<acceleration::standard_gravity>));
	EXPECT_FALSE((traits::is_acceleration_unit_v<inch>));
	EXPECT_FALSE((traits::is_acceleration_unit_v<double>));

	EXPECT_TRUE((traits::is_acceleration_unit_v<meters_per_second_squared_t>));
	EXPECT_TRUE((traits::is_acceleration_unit_v<const meters_per_second_squared_t>));
	EXPECT_TRUE((traits::is_acceleration_unit_v<const meters_per_second_squared_t&>));
	EXPECT_TRUE((traits::is_acceleration_unit_v<standard_gravity_t>));
	EXPECT_FALSE((traits::is_acceleration_unit_v<inch_t>));
	EXPECT_TRUE((traits::is_acceleration_unit_v<standard_gravity_t, meters_per_second_squared_t>));
	EXPECT_FALSE((traits::is_acceleration_unit_v<inch_t, meters_per_second_squared_t>));
}

TEST_F(TypeTraits, is_force_unit)
{

	EXPECT_TRUE((traits::is_force_unit_v<units::force::newton>));
	EXPECT_TRUE((traits::is_force_unit_v<units::force::dynes>));
	EXPECT_FALSE((traits::is_force_unit_v<meter>));
	EXPECT_FALSE((traits::is_force_unit_v<double>));

	EXPECT_TRUE((traits::is_force_unit_v<units::force::newton_t>));
	EXPECT_TRUE((traits::is_force_unit_v<const units::force::newton_t>));
	EXPECT_TRUE((traits::is_force_unit_v<const units::force::newton_t&>));
	EXPECT_TRUE((traits::is_force_unit_v<units::force::dyne_t>));
	EXPECT_FALSE((traits::is_force_unit_v<watt_t>));
	EXPECT_TRUE((traits::is_force_unit_v<units::force::dyne_t, units::force::newton_t>));
	EXPECT_FALSE((traits::is_force_unit_v<watt_t, units::force::newton_t>));
}

TEST_F(TypeTraits, is_pressure_unit)
{
	EXPECT_TRUE((traits::is_pressure_unit_v<pressure::pascals>));
	EXPECT_TRUE((traits::is_pressure_unit_v<atmosphere>));
	EXPECT_FALSE((traits::is_pressure_unit_v<year>));
	EXPECT_FALSE((traits::is_pressure_unit_v<double>));

	EXPECT_TRUE((traits::is_pressure_unit_v<pascal_t>));
	EXPECT_TRUE((traits::is_pressure_unit_v<const pascal_t>));
	EXPECT_TRUE((traits::is_pressure_unit_v<const pascal_t&>));
	EXPECT_TRUE((traits::is_pressure_unit_v<atmosphere_t>));
	EXPECT_FALSE((traits::is_pressure_unit_v<year_t>));
	EXPECT_TRUE((traits::is_pressure_unit_v<atmosphere_t, pressure::pascal_t>));
	EXPECT_FALSE((traits::is_pressure_unit_v<year_t, pressure::pascal_t>));
}

TEST_F(TypeTraits, is_charge_unit)
{
	EXPECT_TRUE((traits::is_charge_unit_v<coulomb>));
	EXPECT_FALSE((traits::is_charge_unit_v<watt>));
	EXPECT_FALSE((traits::is_charge_unit_v<double>));

	EXPECT_TRUE((traits::is_charge_unit_v<coulomb_t>));
	EXPECT_TRUE((traits::is_charge_unit_v<const coulomb_t>));
	EXPECT_TRUE((traits::is_charge_unit_v<const coulomb_t&>));
	EXPECT_FALSE((traits::is_charge_unit_v<watt_t>));
	EXPECT_TRUE((traits::is_charge_unit_v<const coulomb_t&, coulomb_t>));
	EXPECT_FALSE((traits::is_charge_unit_v<watt_t, coulomb_t>));
}

TEST_F(TypeTraits, is_energy_unit)
{
	EXPECT_TRUE((traits::is_energy_unit_v<joule>));
	EXPECT_TRUE((traits::is_energy_unit_v<calorie>));
	EXPECT_FALSE((traits::is_energy_unit_v<watt>));
	EXPECT_FALSE((traits::is_energy_unit_v<double>));

	EXPECT_TRUE((traits::is_energy_unit_v<joule_t>));
	EXPECT_TRUE((traits::is_energy_unit_v<const joule_t>));
	EXPECT_TRUE((traits::is_energy_unit_v<const joule_t&>));
	EXPECT_TRUE((traits::is_energy_unit_v<calorie_t>));
	EXPECT_FALSE((traits::is_energy_unit_v<watt_t>));
	EXPECT_TRUE((traits::is_energy_unit_v<calorie_t, joule_t>));
	EXPECT_FALSE((traits::is_energy_unit_v<watt_t, joule_t>));
}

TEST_F(TypeTraits, is_power_unit)
{
	EXPECT_TRUE((traits::is_power_unit_v<watt>));
	EXPECT_FALSE((traits::is_power_unit_v<henry>));
	EXPECT_FALSE((traits::is_power_unit_v<double>));

	EXPECT_TRUE((traits::is_power_unit_v<watt_t>));
	EXPECT_TRUE((traits::is_power_unit_v<const watt_t>));
	EXPECT_TRUE((traits::is_power_unit_v<const watt_t&>));
	EXPECT_FALSE((traits::is_power_unit_v<henry_t>));
	EXPECT_TRUE((traits::is_power_unit_v<const watt_t&, watt_t>));
	EXPECT_FALSE((traits::is_power_unit_v<henry_t, watt_t>));
}

TEST_F(TypeTraits, is_voltage_unit)
{
	EXPECT_TRUE((traits::is_voltage_unit_v<volt>));
	EXPECT_FALSE((traits::is_voltage_unit_v<henry>));
	EXPECT_FALSE((traits::is_voltage_unit_v<double>));

	EXPECT_TRUE((traits::is_voltage_unit_v<volt_t>));
	EXPECT_TRUE((traits::is_voltage_unit_v<const volt_t>));
	EXPECT_TRUE((traits::is_voltage_unit_v<const volt_t&>));
	EXPECT_FALSE((traits::is_voltage_unit_v<henry_t>));
	EXPECT_TRUE((traits::is_voltage_unit_v<const volt_t&, volt_t>));
	EXPECT_FALSE((traits::is_voltage_unit_v<henry_t, volt_t>));
}

TEST_F(TypeTraits, is_capacitance_unit)
{
	EXPECT_TRUE((traits::is_capacitance_unit_v<farad>));
	EXPECT_FALSE((traits::is_capacitance_unit_v<ohm>));
	EXPECT_FALSE((traits::is_capacitance_unit_v<double>));

	EXPECT_TRUE((traits::is_capacitance_unit_v<farad_t>));
	EXPECT_TRUE((traits::is_capacitance_unit_v<const farad_t>));
	EXPECT_TRUE((traits::is_capacitance_unit_v<const farad_t&>));
	EXPECT_FALSE((traits::is_capacitance_unit_v<ohm_t>));
	EXPECT_TRUE((traits::is_capacitance_unit_v<const farad_t&, millifarad_t>));
	EXPECT_FALSE((traits::is_capacitance_unit_v<ohm_t, farad_t>));
}

TEST_F(TypeTraits, is_impedance_unit)
{

	EXPECT_TRUE((traits::is_impedance_unit_v<ohm>));
	EXPECT_FALSE((traits::is_impedance_unit_v<farad>));
	EXPECT_FALSE((traits::is_impedance_unit_v<double>));

	EXPECT_TRUE((traits::is_impedance_unit_v<ohm_t>));
	EXPECT_TRUE((traits::is_impedance_unit_v<const ohm_t>));
	EXPECT_TRUE((traits::is_impedance_unit_v<const ohm_t&>));
	EXPECT_FALSE((traits::is_impedance_unit_v<farad_t>));
	EXPECT_TRUE((traits::is_impedance_unit_v<const ohm_t&, milliohm_t>));
	EXPECT_FALSE((traits::is_impedance_unit_v<farad_t, ohm_t>));
}

TEST_F(TypeTraits, is_conductance_unit)
{
	EXPECT_TRUE((traits::is_conductance_unit_v<siemens>));
	EXPECT_FALSE((traits::is_conductance_unit_v<volt>));
	EXPECT_FALSE((traits::is_conductance_unit_v<double>));

	EXPECT_TRUE((traits::is_conductance_unit_v<siemens_t>));
	EXPECT_TRUE((traits::is_conductance_unit_v<const siemens_t>));
	EXPECT_TRUE((traits::is_conductance_unit_v<const siemens_t&>));
	EXPECT_FALSE((traits::is_conductance_unit_v<volt_t>));
	EXPECT_TRUE((traits::is_conductance_unit_v<const siemens_t&, millisiemens_t>));
	EXPECT_FALSE((traits::is_conductance_unit_v<volt_t, siemens_t>));
}

TEST_F(TypeTraits, is_magnetic_flux_unit)
{
	EXPECT_TRUE((traits::is_magnetic_flux_unit_v<weber>));
	EXPECT_TRUE((traits::is_magnetic_flux_unit_v<maxwell>));
	EXPECT_FALSE((traits::is_magnetic_flux_unit_v<inch>));
	EXPECT_FALSE((traits::is_magnetic_flux_unit_v<double>));

	EXPECT_TRUE((traits::is_magnetic_flux_unit_v<weber_t>));
	EXPECT_TRUE((traits::is_magnetic_flux_unit_v<const weber_t>));
	EXPECT_TRUE((traits::is_magnetic_flux_unit_v<const weber_t&>));
	EXPECT_TRUE((traits::is_magnetic_flux_unit_v<maxwell_t>));
	EXPECT_FALSE((traits::is_magnetic_flux_unit_v<inch_t>));
	EXPECT_TRUE((traits::is_magnetic_flux_unit_v<maxwell_t, weber_t>));
	EXPECT_FALSE((traits::is_magnetic_flux_unit_v<inch_t, weber_t>));
}

TEST_F(TypeTraits, is_magnetic_field_strength_unit)
{

	EXPECT_TRUE((traits::is_magnetic_field_strength_unit_v<units::magnetic_field_strength::tesla>));
	EXPECT_TRUE((traits::is_magnetic_field_strength_unit_v<gauss>));
	EXPECT_FALSE((traits::is_magnetic_field_strength_unit_v<volt>));
	EXPECT_FALSE((traits::is_magnetic_field_strength_unit_v<double>));

	EXPECT_TRUE((traits::is_magnetic_field_strength_unit_v<tesla_t>));
	EXPECT_TRUE((traits::is_magnetic_field_strength_unit_v<const tesla_t>));
	EXPECT_TRUE((traits::is_magnetic_field_strength_unit_v<const tesla_t&>));
	EXPECT_TRUE((traits::is_magnetic_field_strength_unit_v<gauss_t>));
	EXPECT_FALSE((traits::is_magnetic_field_strength_unit_v<volt_t>));
	EXPECT_TRUE((traits::is_magnetic_field_strength_unit_v<gauss_t, tesla_t>));
	EXPECT_FALSE((traits::is_magnetic_field_strength_unit_v<volt_t, tesla_t>));
}

TEST_F(TypeTraits, is_inductance_unit)
{

	EXPECT_TRUE((traits::is_inductance_unit_v<henry>));
	EXPECT_FALSE((traits::is_inductance_unit_v<farad>));
	EXPECT_FALSE((traits::is_inductance_unit_v<double>));

	EXPECT_TRUE((traits::is_inductance_unit_v<henry_t>));
	EXPECT_TRUE((traits::is_inductance_unit_v<const henry_t>));
	EXPECT_TRUE((traits::is_inductance_unit_v<const henry_t&>));
	EXPECT_FALSE((traits::is_inductance_unit_v<farad_t>));
	EXPECT_TRUE((traits::is_inductance_unit_v<const henry_t&, millihenry_t>));
	EXPECT_FALSE((traits::is_inductance_unit_v<farad_t, henry_t>));
}

TEST_F(TypeTraits, is_luminous_flux_unit)
{

	EXPECT_TRUE((traits::is_luminous_flux_unit_v<lumen>));
	EXPECT_FALSE((traits::is_luminous_flux_unit_v<pound>));
	EXPECT_FALSE((traits::is_luminous_flux_unit_v<double>));

	EXPECT_TRUE((traits::is_luminous_flux_unit_v<lumen_t>));
	EXPECT_TRUE((traits::is_luminous_flux_unit_v<const lumen_t>));
	EXPECT_TRUE((traits::is_luminous_flux_unit_v<const lumen_t&>));
	EXPECT_FALSE((traits::is_luminous_flux_unit_v<pound_t>));
	EXPECT_TRUE((traits::is_luminous_flux_unit_v<const lumen_t&, millilumen_t>));
	EXPECT_FALSE((traits::is_luminous_flux_unit_v<pound_t, lumen_t>));
}

TEST_F(TypeTraits, is_illuminance_unit)
{

	EXPECT_TRUE((traits::is_illuminance_unit_v<illuminance::footcandle>));
	EXPECT_TRUE((traits::is_illuminance_unit_v<illuminance::lux>));
	EXPECT_FALSE((traits::is_illuminance_unit_v<meter>));
	EXPECT_FALSE((traits::is_illuminance_unit_v<double>));

	EXPECT_TRUE((traits::is_illuminance_unit_v<footcandle_t>));
	EXPECT_TRUE((traits::is_illuminance_unit_v<const footcandle_t>));
	EXPECT_TRUE((traits::is_illuminance_unit_v<const footcandle_t&>));
	EXPECT_TRUE((traits::is_illuminance_unit_v<lux_t>));
	EXPECT_FALSE((traits::is_illuminance_unit_v<meter_t>));
	EXPECT_TRUE((traits::is_illuminance_unit_v<lux_t, footcandle_t>));
	EXPECT_FALSE((traits::is_illuminance_unit_v<meter_t, footcandle_t>));
}

TEST_F(TypeTraits, is_radioactivity_unit)
{

	EXPECT_TRUE((traits::is_radioactivity_unit_v<sievert>));
	EXPECT_FALSE((traits::is_radioactivity_unit_v<year>));
	EXPECT_FALSE((traits::is_radioactivity_unit_v<double>));

	EXPECT_TRUE((traits::is_radioactivity_unit_v<sievert>));
	EXPECT_TRUE((traits::is_radioactivity_unit_v<const sievert>));
	EXPECT_TRUE((traits::is_radioactivity_unit_v<const sievert&>));
	EXPECT_FALSE((traits::is_radioactivity_unit_v<year_t>));
	EXPECT_TRUE((traits::is_radioactivity_unit_v<const sievert&, millisievert>));
	EXPECT_FALSE((traits::is_radioactivity_unit_v<year_t, sievert>));
}

TEST_F(TypeTraits, is_torque_unit)
{
	EXPECT_TRUE((traits::is_torque_unit_v<torque::newton_meter>));
	EXPECT_TRUE((traits::is_torque_unit_v<torque::foot_pound>));
	EXPECT_FALSE((traits::is_torque_unit_v<volume::cubic_meter>));
	EXPECT_FALSE((traits::is_torque_unit_v<double>));

	EXPECT_TRUE((traits::is_torque_unit_v<torque::newton_meter_t>));
	EXPECT_TRUE((traits::is_torque_unit_v<const torque::newton_meter_t>));
	EXPECT_TRUE((traits::is_torque_unit_v<const torque::newton_meter_t&>));
	EXPECT_TRUE((traits::is_torque_unit_v<torque::foot_pound_t>));
	EXPECT_FALSE((traits::is_torque_unit_v<volume::cubic_meter_t>));
	EXPECT_TRUE((traits::is_torque_unit_v<torque::foot_pound_t, torque::newton_meter_t>));
	EXPECT_FALSE((traits::is_torque_unit_v<volume::cubic_meter_t, torque::newton_meter_t>));
}

TEST_F(TypeTraits, is_area_unit)
{

	EXPECT_TRUE((traits::is_area_unit_v<square_meter>));
	EXPECT_TRUE((traits::is_area_unit_v<hectare>));
	EXPECT_FALSE((traits::is_area_unit_v<astronicalUnit>));
	EXPECT_FALSE((traits::is_area_unit_v<double>));

	EXPECT_TRUE((traits::is_area_unit_v<square_meter_t>));
	EXPECT_TRUE((traits::is_area_unit_v<const square_meter_t>));
	EXPECT_TRUE((traits::is_area_unit_v<const square_meter_t&>));
	EXPECT_TRUE((traits::is_area_unit_v<hectare_t>));
	EXPECT_FALSE((traits::is_area_unit_v<astronicalUnit_t>));
	EXPECT_TRUE((traits::is_area_unit_v<hectare_t, square_meter_t>));
	EXPECT_FALSE((traits::is_area_unit_v<astronicalUnit_t, square_meter_t>));
}

TEST_F(TypeTraits, is_volume_unit)
{
	EXPECT_TRUE((traits::is_volume_unit_v<cubic_meter>));
	EXPECT_TRUE((traits::is_volume_unit_v<cubic_foot>));
	EXPECT_FALSE((traits::is_volume_unit_v<square_feet>));
	EXPECT_FALSE((traits::is_volume_unit_v<double>));

	EXPECT_TRUE((traits::is_volume_unit_v<cubic_meter_t>));
	EXPECT_TRUE((traits::is_volume_unit_v<const cubic_meter_t>));
	EXPECT_TRUE((traits::is_volume_unit_v<const cubic_meter_t&>));
	EXPECT_TRUE((traits::is_volume_unit_v<cubic_inch_t>));
	EXPECT_FALSE((traits::is_volume_unit_v<foot_t>));
	EXPECT_TRUE((traits::is_volume_unit_v<cubic_inch_t, cubic_meter_t>));
	EXPECT_FALSE((traits::is_volume_unit_v<foot_t, cubic_meter_t>));
}

TEST_F(TypeTraits, is_density_unit)
{
	EXPECT_TRUE((traits::is_density_unit_v<kilograms_per_cubic_meter>));
	EXPECT_TRUE((traits::is_density_unit_v<ounces_per_cubic_foot>));
	EXPECT_FALSE((traits::is_density_unit_v<year>));
	EXPECT_FALSE((traits::is_density_unit_v<double>));

	EXPECT_TRUE((traits::is_density_unit_v<kilograms_per_cubic_meter_t>));
	EXPECT_TRUE((traits::is_density_unit_v<const kilograms_per_cubic_meter_t>));
	EXPECT_TRUE((traits::is_density_unit_v<const kilograms_per_cubic_meter_t&>));
	EXPECT_TRUE((traits::is_density_unit_v<ounces_per_cubic_foot_t>));
	EXPECT_FALSE((traits::is_density_unit_v<year_t>));
	EXPECT_TRUE((traits::is_density_unit_v<ounces_per_cubic_foot_t, kilograms_per_cubic_meter_t>));
	EXPECT_FALSE((traits::is_density_unit_v<year_t, kilograms_per_cubic_meter_t>));
}

TEST_F(TypeTraits, is_data_unit)
{
	EXPECT_TRUE((traits::is_data_unit_v<bit>));
	EXPECT_TRUE((traits::is_data_unit_v<byte>));
	EXPECT_TRUE((traits::is_data_unit_v<exabit>));
	EXPECT_TRUE((traits::is_data_unit_v<exabyte>));
	EXPECT_FALSE((traits::is_data_unit_v<year>));
	EXPECT_FALSE((traits::is_data_unit_v<double>));

	EXPECT_TRUE((traits::is_data_unit_v<bit_t>));
	EXPECT_TRUE((traits::is_data_unit_v<const bit_t>));
	EXPECT_TRUE((traits::is_data_unit_v<const bit_t&>));
	EXPECT_TRUE((traits::is_data_unit_v<byte_t>));
	EXPECT_FALSE((traits::is_data_unit_v<year_t>));
	EXPECT_TRUE((traits::is_data_unit_v<bit_t, byte_t>));
	EXPECT_FALSE((traits::is_data_unit_v<year_t, byte_t>));
}

TEST_F(TypeTraits, is_data_transfer_rate_unit)
{
	EXPECT_TRUE((traits::is_data_transfer_rate_unit_v<Gbps>));
	EXPECT_TRUE((traits::is_data_transfer_rate_unit_v<GBps>));
	EXPECT_FALSE((traits::is_data_transfer_rate_unit_v<year>));
	EXPECT_FALSE((traits::is_data_transfer_rate_unit_v<double>));

	EXPECT_TRUE((traits::is_data_transfer_rate_unit_v<gigabits_per_second_t>));
	EXPECT_TRUE((traits::is_data_transfer_rate_unit_v<const gigabytes_per_second_t>));
	EXPECT_TRUE((traits::is_data_transfer_rate_unit_v<const gigabytes_per_second_t&>));
	EXPECT_TRUE((traits::is_data_transfer_rate_unit_v<gigabytes_per_second_t>));
	EXPECT_FALSE((traits::is_data_transfer_rate_unit_v<year_t>));
	EXPECT_TRUE((traits::is_data_transfer_rate_unit_v<gigabits_per_second_t, gigabytes_per_second_t>));
	EXPECT_FALSE((traits::is_data_transfer_rate_unit_v<year_t, gigabytes_per_second_t>));
}

TEST_F(STDTypeTraits, std_is_convertible_v)
{

}

TEST_F(UnitManipulators, squared)
{
	double test;

	test = convert<unit<square_feet>>(unit<squared<meters>>(0.092903))();
	EXPECT_NEAR(0.99999956944, test, 5.0e-12);

	using dimensionless_2 = squared<units::dimensionless_unit>;	// this is actually nonsensical, and should also result in a dimensionless.
	bool isSame = std::is_same_v<typename std::decay<dimensionless>::type, typename std::decay<unit<dimensionless_2>>::type>;
	EXPECT_TRUE(isSame);
}

TEST_F(UnitManipulators, cubed)
{
	double test;

	test = convert<unit<cubic_feet>>(unit<cubed<meters>>(0.0283168))();
	EXPECT_NEAR(0.999998354619, test, 5.0e-13);
}

TEST_F(UnitManipulators, square_root)
{
	double test;

	test = convert<meter_t>(unit<square_root<square_kilometer>>(1.0))();
	EXPECT_TRUE((traits::is_convertible_unit_v<typename std::decay<square_root<square_kilometer>>::type, kilometer>));
	EXPECT_NEAR(1000.0, test, 5.0e-13);
}

TEST_F(UnitManipulators, compound_unit)
{
	using acceleration1 = unit_conversion<std::ratio<1>, dimension::acceleration>;
	using acceleration2 = compound_unit_conversion<meters, inverse<seconds>, inverse<seconds>>;
	using acceleration3 = unit_conversion<std::ratio<1>, make_dimension<dimension::length, std::ratio<1>, dimension::time, std::ratio<-2>>>;
	using acceleration4 = compound_unit_conversion<meters, inverse<squared<seconds>>>;
	using acceleration5 = compound_unit_conversion<meters, squared<inverse<seconds>>>;

	bool areSame12 = std::is_same_v<acceleration1, acceleration2>;
	bool areSame23 = std::is_same_v<acceleration2, acceleration3>;
	bool areSame34 = std::is_same_v<acceleration3, acceleration4>;
	bool areSame45 = std::is_same_v<acceleration4, acceleration5>;

	EXPECT_TRUE(areSame12);
	EXPECT_TRUE(areSame23);
	EXPECT_TRUE(areSame34);
	EXPECT_TRUE(areSame45);

	// test that thing with translations still compile
	using arbitrary1 = compound_unit_conversion<meters, inverse<celsius>>;
	using arbitrary2 = compound_unit_conversion<meters, celsius>;
	using arbitrary3 = compound_unit_conversion<arbitrary1, arbitrary2>;
	EXPECT_TRUE((std::is_same_v<square_meters, arbitrary3>));
}

TEST_F(UnitManipulators, dimensionalAnalysis)
{
	// these look like 'compound units', but the dimensional analysis can be REALLY handy if the
	// unit types aren't know (i.e. they themselves are template parameters), as you can get the resulting unit of the
	// operation.

	using velocity = units::detail::unit_divide<meters, second>;
	bool shouldBeTrue = std::is_same_v<meters_per_second, velocity>;
	EXPECT_TRUE(shouldBeTrue);

	using acceleration1 = unit_conversion<std::ratio<1>, dimension::acceleration>;
	using acceleration2 = units::detail::unit_divide<meters, units::detail::unit_multiply<seconds, seconds>>;
	shouldBeTrue = std::is_same_v<acceleration1, acceleration2>;
	EXPECT_TRUE(shouldBeTrue);
}

TEST_F(UnitContainer, trivial)
{
	EXPECT_TRUE((std::is_trivial_v<meter_t>));
	EXPECT_TRUE((std::is_trivially_assignable_v<meter_t, meter_t>));
	EXPECT_TRUE((std::is_trivially_constructible_v<meter_t>));
	EXPECT_TRUE((std::is_trivially_copy_assignable_v<meter_t>));
	EXPECT_TRUE((std::is_trivially_copy_constructible_v<meter_t>));
	EXPECT_TRUE((std::is_trivially_copyable_v<meter_t>));
	EXPECT_TRUE((std::is_trivially_default_constructible_v<meter_t>));
	EXPECT_TRUE((std::is_trivially_destructible_v<meter_t>));
	EXPECT_TRUE((std::is_trivially_move_assignable_v<meter_t>));
	EXPECT_TRUE((std::is_trivially_move_constructible_v<meter_t>));

	EXPECT_TRUE((std::is_trivial_v<dB_t>));
	EXPECT_TRUE((std::is_trivially_assignable_v<dB_t, dB_t>));
	EXPECT_TRUE((std::is_trivially_constructible_v<dB_t>));
	EXPECT_TRUE((std::is_trivially_copy_assignable_v<dB_t>));
	EXPECT_TRUE((std::is_trivially_copy_constructible_v<dB_t>));
	EXPECT_TRUE((std::is_trivially_copyable_v<dB_t>));
	EXPECT_TRUE((std::is_trivially_default_constructible_v<dB_t>));
	EXPECT_TRUE((std::is_trivially_destructible_v<dB_t>));
	EXPECT_TRUE((std::is_trivially_move_assignable_v<dB_t>));
	EXPECT_TRUE((std::is_trivially_move_constructible_v<dB_t>));
}

TEST_F(UnitContainer, has_value_member)
{
	EXPECT_TRUE((traits::has_value_member_v<linear_scale<double>, double>));
	EXPECT_FALSE((traits::has_value_member_v<meter, double>));
}

TEST_F(UnitContainer, constructionFromArithmeticType)
{
	meter_t a_m(1.0);
	EXPECT_EQ(1.0, a_m());

	meter_t b_m(1);
	EXPECT_EQ(1, b_m());

	unit<meters, int> c_m(1);
	static_assert(std::is_same_v<int, decltype(c_m())>);
	EXPECT_EQ(1, c_m());

	dimensionless a_dim(1.0);
	EXPECT_EQ(1.0, a_dim());

	dimensionless b_dim(1);
	EXPECT_EQ(1, b_dim());

	unit<dimensionless_unit, int> c_dim(1);
	static_assert(std::is_same_v<int, decltype(c_dim())>);
	EXPECT_EQ(1, c_dim());
}

TEST_F(UnitContainer, constructionFromUnitContainer)
{
	unit<meters, int> a_m(1);

	unit<meters, int> b_m(a_m);
	EXPECT_EQ(1, b_m());

	unit<millimeters, int> a_mm(b_m);
	EXPECT_EQ(1000, a_mm());

	meter_t c_m(b_m);
	EXPECT_EQ(1.0, c_m());

	meter_t d_m(a_mm);
	EXPECT_EQ(1.0, d_m());

	meter_t e_m(unit<kilometers, int>(1));
	EXPECT_EQ(1000.0, e_m());
}

TEST_F(UnitContainer, make_unit)
{
	auto dist = units::make_unit<meter_t>(5);
	EXPECT_EQ(meter_t(5), dist);
}

TEST_F(UnitContainer, unitTypeAddition)
{
	// units
	meter_t a_m(1.0), c_m;
	foot_t b_ft(3.28084);

	double d = convert<meter_t>(b_ft)();
	EXPECT_NEAR(1.0, d, 5.0e-5);

	c_m = a_m + b_ft;
	EXPECT_NEAR(2.0, c_m(), 5.0e-5);

	c_m = b_ft + meter_t(3);
	EXPECT_NEAR(4.0, c_m(), 5.0e-5);

	auto e_ft = b_ft + meter_t(3);
	EXPECT_NEAR(13.12336, e_ft(), 5.0e-6);

	// dimensionless
	dimensionless sresult = dimensionless(1.0) + dimensionless(1.0);
	EXPECT_NEAR(2.0, sresult, 5.0e-6);

	sresult = dimensionless(1.0) + 1.0;
	EXPECT_NEAR(2.0, sresult, 5.0e-6);

	sresult = 1.0 + dimensionless(1.0);
	EXPECT_NEAR(2.0, sresult, 5.0e-6);

	d = dimensionless(1.0) + dimensionless(1.0);
	EXPECT_NEAR(2.0, d, 5.0e-6);

	d = dimensionless(1.0) + 1.0;
	EXPECT_NEAR(2.0, d, 5.0e-6);

	d = 1.0 + dimensionless(1.0);
	EXPECT_NEAR(2.0, d, 5.0e-6);
}

TEST_F(UnitContainer, unitTypeUnaryAddition)
{
	meter_t a_m(1.0);

	EXPECT_EQ(++a_m, meter_t(2));
	EXPECT_EQ(a_m++, meter_t(2));
	EXPECT_EQ(a_m, meter_t(3));
	EXPECT_EQ(+a_m, meter_t(3));
	EXPECT_EQ(a_m, meter_t(3));

	dBW_t b_dBW(1.0);

	EXPECT_EQ(++b_dBW, dBW_t(2));
	EXPECT_EQ(b_dBW++, dBW_t(2));
	EXPECT_EQ(b_dBW, dBW_t(3));
	EXPECT_EQ(+b_dBW, dBW_t(3));
	EXPECT_EQ(b_dBW, dBW_t(3));
}

TEST_F(UnitContainer, unitTypeSubtraction)
{
	meter_t a_m(1.0), c_m;
	foot_t b_ft(3.28084);

	c_m = a_m - b_ft;
	EXPECT_NEAR(0.0, c_m(), 5.0e-5);

	c_m = b_ft - meter_t(1);
	EXPECT_NEAR(0.0, c_m(), 5.0e-5);

	auto e_ft = b_ft - meter_t(1);
	EXPECT_NEAR(0.0, e_ft(), 5.0e-6);

	dimensionless sresult = dimensionless(1.0) - dimensionless(1.0);
	EXPECT_NEAR(0.0, sresult, 5.0e-6);

	sresult = dimensionless(1.0) - 1.0;
	EXPECT_NEAR(0.0, sresult, 5.0e-6);

	sresult = 1.0 - dimensionless(1.0);
	EXPECT_NEAR(0.0, sresult, 5.0e-6);

	double d = dimensionless(1.0) - dimensionless(1.0);
	EXPECT_NEAR(0.0, d, 5.0e-6);

	d = dimensionless(1.0) - 1.0;
	EXPECT_NEAR(0.0, d, 5.0e-6);

	d = 1.0 - dimensionless(1.0);
	EXPECT_NEAR(0.0, d, 5.0e-6);
}

TEST_F(UnitContainer, unitTypeUnarySubtraction)
{
	meter_t a_m(4.0);

	EXPECT_EQ(--a_m, meter_t(3));
	EXPECT_EQ(a_m--, meter_t(3));
	EXPECT_EQ(a_m, meter_t(2));
	EXPECT_EQ(-a_m, meter_t(-2));
	EXPECT_EQ(a_m, meter_t(2));

	dBW_t b_dBW(4.0);

	EXPECT_EQ(--b_dBW, dBW_t(3));
	EXPECT_EQ(b_dBW--, dBW_t(3));
	EXPECT_EQ(b_dBW, dBW_t(2));
	EXPECT_EQ(-b_dBW, dBW_t(-2));
	EXPECT_EQ(b_dBW, dBW_t(2));
}

TEST_F(UnitContainer, unitTypeMultiplication)
{
	meter_t a_m(1.0), b_m(2.0);
	foot_t a_ft(3.28084);

	auto c_m2 = a_m * b_m;
	EXPECT_NEAR(2.0, c_m2(), 5.0e-5);

	c_m2 = b_m * meter_t(2);
	EXPECT_NEAR(4.0, c_m2(), 5.0e-5);

	c_m2 = b_m *a_ft;
	EXPECT_NEAR(2.0, c_m2(), 5.0e-5);

	auto c_m = b_m * 2.0;
	EXPECT_NEAR(4.0, c_m(), 5.0e-5);

	c_m = 2.0 * b_m;
	EXPECT_NEAR(4.0, c_m(), 5.0e-5);

	double convert = dimensionless(3.14);
	EXPECT_NEAR(3.14, convert, 5.0e-5);

	dimensionless sresult = dimensionless(5.0) * dimensionless(4.0);
	EXPECT_NEAR(20.0, sresult(), 5.0e-5);

	sresult = dimensionless(5.0) * 4.0;
	EXPECT_NEAR(20.0, sresult(), 5.0e-5);

	sresult = 4.0 * dimensionless(5.0);
	EXPECT_NEAR(20.0, sresult(), 5.0e-5);

	double result = dimensionless(5.0) * dimensionless(4.0);
	EXPECT_NEAR(20.0, result, 5.0e-5);

	result = dimensionless(5.0) * 4.0;
	EXPECT_NEAR(20.0, result, 5.0e-5);

	result = 4.0 * dimensionless(5.0);
	EXPECT_NEAR(20.0, result, 5.0e-5);
}

TEST_F(UnitContainer, unitTypeMixedUnitMultiplication)
{
	meter_t a_m(1.0);
	foot_t b_ft(3.28084);
	unit<inverse<meter>> i_m(2.0);

	// resultant unit is square of leftmost unit
	auto c_m2 = a_m * b_ft;
	EXPECT_NEAR(1.0, c_m2(), 5.0e-5);

	auto c_ft2 = b_ft * a_m;
	EXPECT_NEAR(10.7639111056, c_ft2(), 5.0e-7);

	// you can get whatever (compatible) type you want if you ask explicitly
	square_meter_t d_m2 = b_ft * a_m;
	EXPECT_NEAR(1.0, d_m2(), 5.0e-5);

	// a unit times a sclar ends up with the same units.
	meter_t e_m = a_m * dimensionless(3.0);
	EXPECT_NEAR(3.0, e_m(), 5.0e-5);

	e_m = dimensionless(4.0) * a_m;
	EXPECT_NEAR(4.0, e_m(), 5.0e-5);

	// unit times its inverse results in a dimensionless
	dimensionless s = a_m * i_m;
	EXPECT_NEAR(2.0, s, 5.0e-5);

	c_m2 = b_ft * meter_t(2);
	EXPECT_NEAR(2.0, c_m2(), 5.0e-5);

	auto e_ft2 = b_ft * meter_t(3);
	EXPECT_NEAR(32.2917333168, e_ft2(), 5.0e-6);

	auto mps = meter_t(10.0) * unit<inverse<seconds>>(1.0);
	EXPECT_EQ(mps, meters_per_second_t(10));
}

TEST_F(UnitContainer, unitTypedimensionlessMultiplication)
{
	meter_t a_m(1.0);
	foot_t b_ft(3.28084);

	auto result_m = dimensionless(3.0) * a_m;
	EXPECT_NEAR(3.0, result_m(), 5.0e-5);

	result_m = a_m * dimensionless(4.0);
	EXPECT_NEAR(4.0, result_m(), 5.0e-5);

	result_m = 3.0 * a_m;
	EXPECT_NEAR(3.0, result_m(), 5.0e-5);

	result_m = a_m * 4.0;
	EXPECT_NEAR(4.0, result_m(), 5.0e-5);

	bool isSame = std::is_same_v<decltype(result_m), meter_t>;
	EXPECT_TRUE(isSame);
}

TEST_F(UnitContainer, unitTypeDivision)
{
	meter_t a_m(1.0), b_m(2.0);
	foot_t a_ft(3.28084);
	second_t a_sec(10.0);
	bool isSame;

	auto c = a_m / a_ft;
	EXPECT_NEAR(1.0, c, 5.0e-5);
	isSame = std::is_same_v<decltype(c), dimensionless>;
	EXPECT_TRUE(isSame);

	c = a_m / b_m;
	EXPECT_NEAR(0.5, c, 5.0e-5);
	isSame = std::is_same_v<decltype(c), dimensionless>;
	EXPECT_TRUE(isSame);

	c = a_ft / a_m;
	EXPECT_NEAR(1.0, c, 5.0e-5);
	isSame = std::is_same_v<decltype(c), dimensionless>;
	EXPECT_TRUE(isSame);

	c = dimensionless(1.0) / 2.0;
	EXPECT_NEAR(0.5, c, 5.0e-5);
	isSame = std::is_same_v<decltype(c), dimensionless>;
	EXPECT_TRUE(isSame);

	c = 1.0 / dimensionless(2.0);
	EXPECT_NEAR(0.5, c, 5.0e-5);
	isSame = std::is_same_v<decltype(c), dimensionless>;
	EXPECT_TRUE(isSame);

	double d = dimensionless(1.0) / 2.0;
	EXPECT_NEAR(0.5, d, 5.0e-5);

	auto e = a_m / a_sec;
	EXPECT_NEAR(0.1, e(), 5.0e-5);
	isSame = std::is_same_v<decltype(e), meters_per_second_t>;
	EXPECT_TRUE(isSame);

	auto f = a_m / 8.0;
	EXPECT_NEAR(0.125, f(), 5.0e-5);
	isSame = std::is_same_v<decltype(f), meter_t>;
	EXPECT_TRUE(isSame);

	auto g = 4.0 / b_m;
	EXPECT_NEAR(2.0, g(), 5.0e-5);
	isSame = std::is_same_v<decltype(g), unit<inverse<meters>>>;
	EXPECT_TRUE(isSame);

	auto mph = mile_t(60.0) / hour_t(1.0);
	meters_per_second_t mps = mph;
	EXPECT_NEAR(26.8224, mps(), 5.0e-5);

	auto h = 10_rad / 2_rad;
	EXPECT_NEAR(5, h, 5.0e-5);
	isSame = std::is_same_v<decltype(h), dimensionless>;
	EXPECT_TRUE(isSame);

	auto i = (3_N * 2_m) / 6_J;
	EXPECT_NEAR(1, i, 5.0e-5);
	isSame = std::is_same_v<decltype(i), dimensionless>;
	EXPECT_TRUE(isSame);
}

TEST_F(UnitContainer, compoundAssignmentAddition)
{
	// units
	meter_t a(0.0);
	a += meter_t(1.0);

	EXPECT_EQ(meter_t(1.0), a);

	a += foot_t(meter_t(1));

	EXPECT_EQ(meter_t(2.0), a);

	// dimensionlesss
	dimensionless b(0);
	b += dimensionless(1.0);

	EXPECT_EQ(dimensionless(1.0), b);

	b += 1;

	EXPECT_EQ(dimensionless(2.0), b);
}

TEST_F(UnitContainer, compoundAssignmentSubtraction)
{
	// units
	meter_t a(2.0);
	a -= meter_t(1.0);

	EXPECT_EQ(meter_t(1.0), a);

	a -= foot_t(meter_t(1));

	EXPECT_EQ(meter_t(0.0), a);

	// dimensionlesss
	dimensionless b(2);
	b -= dimensionless(1.0);

	EXPECT_EQ(dimensionless(1.0), b);

	b -= 1;

	EXPECT_EQ(dimensionless(0), b);
}

TEST_F(UnitContainer, compoundAssignmentMultiplication)
{
	// units
	meter_t a(2.0);
	a *= dimensionless(2.0);

	EXPECT_EQ(meter_t(4.0), a);

	a *= 2.0;

	EXPECT_EQ(meter_t(8.0), a);

	// dimensionlesss
	dimensionless b(2);
	b *= dimensionless(2.0);

	EXPECT_EQ(dimensionless(4.0), b);

	b *= 2;

	EXPECT_EQ(dimensionless(8.0), b);
}

TEST_F(UnitContainer, compoundAssignmentDivision)
{
	// units
	meter_t a(8.0);
	a /= dimensionless(2.0);

	EXPECT_EQ(meter_t(4.0), a);

	a /= 2.0;

	EXPECT_EQ(meter_t(2.0), a);

	// dimensionlesss
	dimensionless b(8);
	b /= dimensionless(2.0);

	EXPECT_EQ(dimensionless(4.0), b);

	b /= 2;

	EXPECT_EQ(dimensionless(2.0), b);
}

TEST_F(UnitContainer, dimensionlessTypeImplicitConversion)
{
	double test = dimensionless(3.0);
	EXPECT_DOUBLE_EQ(3.0, test);

	dimensionless testS = 3.0;
	EXPECT_DOUBLE_EQ(3.0, testS);


	dimensionless test3(ppm_t(10));
	EXPECT_DOUBLE_EQ(0.00001, test3);

	dimensionless test4;
	test4 = ppm_t(1);
	EXPECT_DOUBLE_EQ(0.000001, test4);
}

TEST_F(UnitContainer, valueMethod)
{
	double test = meter_t(3.0).to<double>();
	EXPECT_DOUBLE_EQ(3.0, test);

	auto test2 = meter_t(4.0).value();
	EXPECT_DOUBLE_EQ(4.0, test2);
	EXPECT_TRUE((std::is_same_v<decltype(test2), double>));
}

TEST_F(UnitContainer, convertMethod)
{
	double test = meter_t(3.0).convert<feet>().to<double>();
	EXPECT_NEAR(9.84252, test, 5.0e-6);
}

#ifndef UNIT_LIB_DISABLE_IOSTREAM
TEST_F(UnitContainer, cout)
{
	testing::internal::CaptureStdout();
	std::cout << meters_per_second_t(5);
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("5 mps", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << degree_t(349.87);
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("349.87 deg", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << meter_t(1.0);
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("1 m", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << dB_t(31.0);
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("31 dB", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << volt_t(21.79);
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("21.79 V", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << dBW_t(12.0);
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("12 dBW", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << dBm_t(120.0);
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("120 dBm", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << miles_per_hour_t(72.1);
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("72.1 mph", output.c_str());

	// undefined unit
	testing::internal::CaptureStdout();
	std::cout << pow<4>(meter_t(2));
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("16 m^4", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << pow<3>(foot_t(2));
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("8 cu_ft", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << std::setprecision(9) << pow<4>(foot_t(2));
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("0.138095597 m^4", output.c_str());

	// constants
	testing::internal::CaptureStdout();
	std::cout << std::setprecision(8) << constants::k_B;
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("1.3806485e-23 m^2 kg K^-1 s^-2", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << std::setprecision(9) << constants::mu_B;
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("9.27400999e-24 A m^2", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << std::setprecision(7) << constants::sigma;
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("5.670367e-08 kg K^-4 s^-3", output.c_str());
}

TEST_F(UnitContainer, to_string)
{
	foot_t a(3.5);
	EXPECT_STREQ("3.5 ft", units::length::to_string(a).c_str());

	meter_t b(8);
	EXPECT_STREQ("8 m", units::length::to_string(b).c_str());
}

TEST_F(UnitContainer, to_string_locale)
{
	struct lconv * lc;
	
	// German locale
#if defined(_MSC_VER)
	setlocale(LC_ALL, "de-DE");
#else	
	EXPECT_STREQ("de_DE.utf8",setlocale(LC_ALL, "de_DE.utf8"));
#endif

	lc = localeconv();
	char point_de = *lc->decimal_point;
	EXPECT_EQ(point_de, ',');

	kilometer_t de = 2_km;
	EXPECT_STREQ("2 km", units::length::to_string(de).c_str());
	
	de = 2.5_km;
	EXPECT_STREQ("2,5 km", units::length::to_string(de).c_str());

	// US locale
#if defined(_MSC_VER)
	setlocale(LC_ALL, "en-US");
#else
	EXPECT_STREQ("en_US.utf8",setlocale(LC_ALL, "en_US.utf8"));
#endif

	lc = localeconv();
	char point_us = *lc->decimal_point;
	EXPECT_EQ(point_us, '.');

	mile_t us = 2_mi;
	EXPECT_STREQ("2 mi", units::length::to_string(us).c_str());

	us = 2.5_mi;
	EXPECT_STREQ("2.5 mi", units::length::to_string(us).c_str());
}

TEST_F(UnitContainer, nameAndAbbreviation)
{
	foot_t a(3.5);
	EXPECT_STREQ("ft", units::abbreviation(a));
	EXPECT_STREQ("ft", a.abbreviation());
	EXPECT_STREQ("foot", a.name());

	meter_t b(8);
	EXPECT_STREQ("m", units::abbreviation(b));
	EXPECT_STREQ("m", b.abbreviation());
	EXPECT_STREQ("meter", b.name());
}
#endif

TEST_F(UnitContainer, negative)
{
	meter_t a(5.3);
	meter_t b(-5.3);
	EXPECT_NEAR(a.to<double>(), -b.to<double>(), 5.0e-320);
	EXPECT_NEAR(b.to<double>(), -a.to<double>(), 5.0e-320);

	dB_t c(2.87);
	dB_t d(-2.87);
	EXPECT_NEAR(c.to<double>(), -d.to<double>(), 5.0e-320);
	EXPECT_NEAR(d.to<double>(), -c.to<double>(), 5.0e-320);

	ppm_t e = -1 * ppm_t(10);
	EXPECT_EQ(e, -ppm_t(10));
	EXPECT_NEAR(-0.00001, e, 5.0e-10);
}

TEST_F(UnitContainer, concentration)
{
	ppb_t a(ppm_t(1));
	EXPECT_EQ(ppb_t(1000), a);
	EXPECT_EQ(0.000001, a);
	EXPECT_EQ(0.000001, a.to<double>());

	dimensionless b(ppm_t(1));
	EXPECT_EQ(0.000001, b);

	dimensionless c = ppb_t(1);
	EXPECT_EQ(0.000000001, c);
}

TEST_F(UnitContainer, dBConversion)
{
	dBW_t a_dbw(23.1);
	watt_t a_w = a_dbw;
	dBm_t a_dbm = a_dbw;

	EXPECT_NEAR(204.173794, a_w(), 5.0e-7);
	EXPECT_NEAR(53.1, a_dbm(), 5.0e-7);

	milliwatt_t b_mw(100000.0);
	watt_t b_w = b_mw;
	dBm_t b_dbm = b_mw;
	dBW_t b_dbw = b_mw;

	EXPECT_NEAR(100.0, b_w(), 5.0e-7);
	EXPECT_NEAR(50.0, b_dbm(), 5.0e-7);
	EXPECT_NEAR(20.0, b_dbw(), 5.0e-7);
}

TEST_F(UnitContainer, dBAddition)
{
	bool isSame;

	auto result_dbw = dBW_t(10.0) + dB_t(30.0);
	EXPECT_NEAR(40.0, result_dbw(), 5.0e-5);
	result_dbw = dB_t(12.0) + dBW_t(30.0);
	EXPECT_NEAR(42.0, result_dbw(), 5.0e-5);
	isSame = std::is_same_v<decltype(result_dbw), dBW_t>;
	EXPECT_TRUE(isSame);

	auto result_dbm = dB_t(30.0) + dBm_t(20.0);
	EXPECT_NEAR(50.0, result_dbm(), 5.0e-5);

	// adding dBW to dBW is something you probably shouldn't do, but let's see if it works...
	auto result_dBW2 = dBW_t(10.0) + dBm_t(40.0);
	EXPECT_NEAR(20.0, result_dBW2(), 5.0e-5);
	isSame = std::is_same_v<decltype(result_dBW2), unit<squared<watts>, double, decibel_scale>>;
	EXPECT_TRUE(isSame);
}

TEST_F(UnitContainer, dBSubtraction)
{
	bool isSame;

	auto result_dbw = dBW_t(10.0) - dB_t(30.0);
	EXPECT_NEAR(-20.0, result_dbw(), 5.0e-5);
	isSame = std::is_same_v<decltype(result_dbw), dBW_t>;
	EXPECT_TRUE(isSame);

	auto result_dbm = dBm_t(100.0) - dB_t(30.0);
	EXPECT_NEAR(70.0, result_dbm(), 5.0e-5);
	isSame = std::is_same_v<decltype(result_dbm), dBm_t>;
	EXPECT_TRUE(isSame);

	auto result_db = dBW_t(100.0) - dBW_t(80.0);
	EXPECT_NEAR(20.0, result_db(), 5.0e-5);
	isSame = std::is_same_v<decltype(result_db), dB_t>;
	EXPECT_TRUE(isSame);

	result_db = dB_t(100.0) - dB_t(80.0);
	EXPECT_NEAR(20.0, result_db(), 5.0e-5);
	isSame = std::is_same_v<decltype(result_db), dB_t>;
	EXPECT_TRUE(isSame);
}

TEST_F(UnitContainer, unit_cast)
{
	meter_t		test1(5.7);
	hectare_t	test2(16);

	double		dResult1 = 5.7;

	double		dResult2 = 16;
	int			iResult2 = 16;

	EXPECT_EQ(dResult1, unit_cast<double>(test1));
	EXPECT_EQ(dResult2, unit_cast<double>(test2));
	EXPECT_EQ(iResult2, unit_cast<int>(test2));

	EXPECT_TRUE((std::is_same_v<double, decltype(unit_cast<double>(test1))>));
	EXPECT_TRUE((std::is_same_v<int, decltype(unit_cast<int>(test2))>));
}

// literal syntax is only supported in GCC 4.7+ and MSVC2015+
TEST_F(UnitContainer, literals)
{
	// basic functionality testing
	EXPECT_TRUE((std::is_same_v<decltype(16.2_m), meter_t>));
	EXPECT_TRUE(meter_t(16.2) == 16.2_m);
	EXPECT_TRUE(meter_t(16) == 16_m);

	EXPECT_TRUE((std::is_same_v<decltype(11.2_ft), foot_t>));
	EXPECT_TRUE(foot_t(11.2) == 11.2_ft);
	EXPECT_TRUE(foot_t(11) == 11_ft);

	// auto using literal syntax
	auto x = 10.0_m;
	EXPECT_TRUE((std::is_same_v<decltype(x), meter_t>));
	EXPECT_TRUE(meter_t(10) == x);

	// conversion using literal syntax
	foot_t y = 0.3048_m;
	EXPECT_TRUE(1_ft == y);

	// Pythagorean theorem
	meter_t a = 3_m;
	meter_t b = 4_m;
	meter_t c = sqrt(pow<2>(a) + pow<2>(b));
	EXPECT_TRUE(c == 5_m);
}

TEST_F(UnitConversion, length)
{
	double test;
	test = convert<nanometer_t>(0.000000001_m)();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<micrometer_t>(meter_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<millimeter_t>(meter_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<centimeter_t>(meter_t(0.01))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<kilometer_t>(meter_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<meter_t>(meter_t(1.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<foot_t>(meter_t(0.3048))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<mile_t>(meter_t(1609.344))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<inch_t>(meter_t(0.0254))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<nauticalMile_t>(meter_t(1852.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<astronicalUnit_t>(meter_t(149597870700.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<lightyear_t>(meter_t(9460730472580800.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<parsec_t>(meter_t(3.08567758e16))();
	EXPECT_NEAR(1.0, test, 5.0e7);

	test = convert<foot_t>(foot_t(6.3))();
	EXPECT_NEAR(6.3, test, 5.0e-5);
	test = convert<inch_t>(foot_t(6.0))();
	EXPECT_NEAR(72.0, test, 5.0e-5);
	test = convert<foot_t>(inch_t(6.0))();
	EXPECT_NEAR(0.5, test, 5.0e-5);
	test = convert<foot_t>(meter_t(1.0))();
	EXPECT_NEAR(3.28084, test, 5.0e-5);
	test = convert<nauticalMile_t>(mile_t(6.3))();
	EXPECT_NEAR(5.47455, test, 5.0e-6);
	test = convert<meter_t>(mile_t(11.0))();
	EXPECT_NEAR(17702.8, test, 5.0e-2);
	test = convert<chain_t>(meter_t(1.0))();
	EXPECT_NEAR(0.0497097, test, 5.0e-7);

//	dimensionless b = 5_rad;
}

TEST_F(UnitConversion, mass)
{
	double test;

	test = convert<gram_t>(kilogram_t(1.0e-3))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<microgram_t>(kilogram_t(1.0e-9))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<milligram_t>(kilogram_t(1.0e-6))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<kilogram_t>(kilogram_t(1.0))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<metric_ton_t>(kilogram_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<pound_t>(kilogram_t(0.453592))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<long_ton_t>(kilogram_t(1016.05))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<short_ton_t>(kilogram_t(907.185))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<mass::ounce_t>(kilogram_t(0.0283495))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<carat_t>(kilogram_t(0.0002))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<kilogram_t>(slug_t(1.0))();
	EXPECT_NEAR(14.593903, test, 5.0e-7);

	test = convert<carat_t>(pound_t(6.3))();
	EXPECT_NEAR(14288.2, test, 5.0e-2);
}

TEST_F(UnitConversion, time)
{
	double result = 0;
	double daysPerYear = 365;
	double hoursPerDay = 24;
	double minsPerHour = 60;
	double secsPerMin = 60;
	double daysPerWeek = 7;

	result = 2 * daysPerYear * hoursPerDay * minsPerHour * secsPerMin *
		(1 / minsPerHour) * (1 / secsPerMin) * (1 / hoursPerDay) * (1 / daysPerWeek);
	EXPECT_NEAR(104.286, result, 5.0e-4);

	year_t twoYears(2.0);
	week_t twoYearsInWeeks = twoYears;
	EXPECT_NEAR(week_t(104.286).to<double>(), twoYearsInWeeks.to<double>(), 5.0e-4);

	double test;



	test = convert<second_t>(second_t(1.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<nanosecond_t>(second_t(1.0e-9))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<microsecond_t>(second_t(1.0e-6))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<millisecond_t>(second_t(1.0e-3))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<minute_t>(second_t(60.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<hour_t>(second_t(3600.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<day_t>(second_t(86400.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<week_t>(second_t(604800.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<year_t>(second_t(3.154e7))();
	EXPECT_NEAR(1.0, test, 5.0e3);

	test = convert<week_t>(year_t(2.0))();
	EXPECT_NEAR(104.2857142857143, test, 5.0e-14);
	test = convert<minute_t>(hour_t(4.0))();
	EXPECT_NEAR(240.0, test, 5.0e-14);
	test = convert<day_t>(julian_year_t(1.0))();
	EXPECT_NEAR(365.25, test, 5.0e-14);
	test = convert<day_t>(gregorian_year_t(1.0))();
	EXPECT_NEAR(365.2425, test, 5.0e-14);

}

TEST_F(UnitConversion, angle)
{
	angle::degree_t quarterCircleDeg(90.0);
	angle::radian_t quarterCircleRad = quarterCircleDeg;
	EXPECT_NEAR(angle::radian_t(constants::detail::PI_VAL / 2.0).to<double>(), quarterCircleRad.to<double>(), 5.0e-12);

	double test;

	test = convert<angle::radian_t>(angle::radian_t(1.0))();
	EXPECT_NEAR(1.0, test, 5.0e-20);
	test = convert<angle::milliradian_t>(angle::radian_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-4);
	test = convert<angle::degree_t>(angle::radian_t(0.0174533))();
	EXPECT_NEAR(1.0, test, 5.0e-7);
	test = convert<angle::arcminute_t>(angle::radian_t(0.000290888))();
	EXPECT_NEAR(0.99999928265913, test, 5.0e-8);
	test = convert<angle::arcsecond_t>(angle::radian_t(4.8481e-6))();
	EXPECT_NEAR(0.999992407, test, 5.0e-10);
	test = convert<angle::turn_t>(angle::radian_t(6.28319))();
	EXPECT_NEAR(1.0, test, 5.0e-6);
	test = convert<angle::gradian_t>(angle::radian_t(0.015708))();
	EXPECT_NEAR(1.0, test, 5.0e-6);

	test = convert<angle::radian_t>(angle::radian_t(2.1))();
	EXPECT_NEAR(2.1, test, 5.0e-6);
	test = convert<angle::gradian_t>(angle::arcsecond_t(2.1))();
	EXPECT_NEAR(0.000648148, test, 5.0e-6);
	test = convert<angle::degree_t>(angle::radian_t(constants::detail::PI_VAL))();
	EXPECT_NEAR(180.0, test, 5.0e-6);
	test = convert<angle::radian_t>(angle::degree_t(90.0))();
	EXPECT_NEAR(constants::detail::PI_VAL / 2, test, 5.0e-6);
}

TEST_F(UnitConversion, current)
{
	double test;

	test = convert<current::milliampere_t>(current::ampere_t(2.1))();
	EXPECT_NEAR(2100.0, test, 5.0e-6);
}

TEST_F(UnitConversion, temperature)
{
	// temp conversion are weird/hard since they involve translations AND scaling.
	double test;

	test = convert<kelvin_t>(kelvin_t(72.0))();
	EXPECT_NEAR(72.0, test, 5.0e-5);
	test = convert<fahrenheit_t>(fahrenheit_t(72.0))();
	EXPECT_NEAR(72.0, test, 5.0e-5);
	test = convert<fahrenheit_t>(kelvin_t(300.0))();
	EXPECT_NEAR(80.33, test, 5.0e-5);
	test = convert<kelvin_t>(fahrenheit_t(451.0))();
	EXPECT_NEAR(505.928, test, 5.0e-4);
	test = convert<celsius_t>(kelvin_t(300.0))();
	EXPECT_NEAR(26.85, test, 5.0e-3);
	test = convert<kelvin_t>(celsius_t(451.0))();
	EXPECT_NEAR(724.15, test, 5.0e-3);
	test = convert<celsius_t>(fahrenheit_t(72.0))();
	EXPECT_NEAR(22.2222, test, 5.0e-5);
	test = convert<fahrenheit_t>(celsius_t(100.0))();
	EXPECT_NEAR(212.0, test, 5.0e-5);
	test = convert<celsius_t>(fahrenheit_t(32.0))();
	EXPECT_NEAR(0.0, test, 5.0e-5);
	test = convert<fahrenheit_t>(celsius_t(0.0))();
	EXPECT_NEAR(32.0, test, 5.0e-5);
	test = convert<kelvin_t>(rankine_t(100.0))();
	EXPECT_NEAR(55.5556, test, 5.0e-5);
	test = convert<rankine_t>(kelvin_t(100.0))();
	EXPECT_NEAR(180.0, test, 5.0e-5);
	test = convert<rankine_t>(fahrenheit_t(100.0))();
	EXPECT_NEAR(559.67, test, 5.0e-5);
	test = convert<fahrenheit_t>(rankine_t(72.0))();
	EXPECT_NEAR(-387.67, test, 5.0e-5);
	test = convert<kelvin_t>(reaumur_t(100.0))();
	EXPECT_NEAR(398.0, test, 5.0e-1);
	test = convert<celsius_t>(reaumur_t(80.0))();
	EXPECT_NEAR(100.0, test, 5.0e-5);
	test = convert<reaumur_t>(celsius_t(212.0))();
	EXPECT_NEAR(169.6, test, 5.0e-2);
	test = convert<fahrenheit_t>(reaumur_t(80.0))();
	EXPECT_NEAR(212.0, test, 5.0e-5);
	test = convert<reaumur_t>(fahrenheit_t(37.0))();
	EXPECT_NEAR(2.222, test, 5.0e-3);
}

TEST_F(UnitConversion, luminous_intensity)
{
	double test;

	test = convert<millicandela_t>(candela_t(72.0))();
	EXPECT_NEAR(72000.0, test, 5.0e-5);
	test = convert<candela_t>(millicandela_t(376.0))();
	EXPECT_NEAR(0.376, test, 5.0e-5);
}

TEST_F(UnitConversion, solid_angle)
{
	double test;
	bool same;

	same = std::is_same_v<traits::dimension_of_t<steradians>, traits::dimension_of_t<degrees_squared>>;
	EXPECT_TRUE(same);

	test = convert<steradian_t>(steradian_t(72.0))();
	EXPECT_NEAR(72.0, test, 5.0e-5);
	test = convert<degree_squared_t>(steradian_t(1.0))();
	EXPECT_NEAR(3282.8, test, 5.0e-2);
	test = convert<spat_t>(steradian_t(8.0))();
	EXPECT_NEAR(0.636619772367582, test, 5.0e-14);
	test = convert<steradian_t>(degree_squared_t(3282.8))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<degree_squared_t>(degree_squared_t(72.0))();
	EXPECT_NEAR(72.0, test, 5.0e-5);
	test = convert<spat_t>(degree_squared_t(3282.8))();
	EXPECT_NEAR(1.0 / (4 * constants::detail::PI_VAL), test, 5.0e-5);
	test = convert<steradian_t>(spat_t(1.0 / (4 * constants::detail::PI_VAL)))();
	EXPECT_NEAR(1.0, test, 5.0e-14);
	test = convert<degree_squared_t>(spat_t(1.0 / (4 * constants::detail::PI_VAL)))();
	EXPECT_NEAR(3282.8, test, 5.0e-2);
	test = convert<spat_t>(spat_t(72.0))();
	EXPECT_NEAR(72.0, test, 5.0e-5);
}

TEST_F(UnitConversion, frequency)
{
	double test;

	test = convert<kilohertz_t>(hertz_t(63000.0))();
	EXPECT_NEAR(63.0, test, 5.0e-5);
	test = convert<hertz_t>(hertz_t(6.3))();
	EXPECT_NEAR(6.3, test, 5.0e-5);
	test = convert<hertz_t>(kilohertz_t(5.0))();
	EXPECT_NEAR(5000.0, test, 5.0e-5);
	test = convert<hertz_t>(megahertz_t(1.0))();
	EXPECT_NEAR(1.0e6, test, 5.0e-5);
}

TEST_F(UnitConversion, velocity)
{
	double test;
	bool same;

	same = std::is_same_v<meters_per_second, unit_conversion<std::ratio<1>, dimension::velocity>>;
	EXPECT_TRUE(same);
	same = traits::is_convertible_unit_v<miles_per_hour, meters_per_second>;
	EXPECT_TRUE(same);

	test = convert<miles_per_hour_t>(meters_per_second_t(1250.0))();
	EXPECT_NEAR(2796.17, test, 5.0e-3);
	test = convert<kilometers_per_hour_t>(feet_per_second_t(2796.17))();
	EXPECT_NEAR(3068.181418, test, 5.0e-7);
	test = convert<miles_per_hour_t>(knot_t(600.0))();
	EXPECT_NEAR(690.468, test, 5.0e-4);
	test = convert<feet_per_second_t>(miles_per_hour_t(120.0))();
	EXPECT_NEAR(176.0, test, 5.0e-5);
	test = convert<meters_per_second_t>(feet_per_second_t(10.0))();
	EXPECT_NEAR(3.048, test, 5.0e-5);
}

TEST_F(UnitConversion, angular_velocity)
{
	double test;
	bool same;

	same = std::is_same_v<radians_per_second, unit_conversion<std::ratio<1>, dimension::angular_velocity>>;
	EXPECT_TRUE(same);
	same = traits::is_convertible_unit_v<rpm, radians_per_second>;
	EXPECT_TRUE(same);

	test = convert<milliarcseconds_per_year_t>(radians_per_second_t(1.0))();
	EXPECT_NEAR(6.504e15, test, 1.0e12);
	test = convert<radians_per_second_t>(degrees_per_second_t(1.0))();
	EXPECT_NEAR(0.0174533, test, 5.0e-8);
	test = convert<radians_per_second_t>(revolutions_per_minute_t(1.0))();
	EXPECT_NEAR(0.10471975512, test, 5.0e-13);
	test = convert<radians_per_second_t>(milliarcseconds_per_year_t(1.0))();
	EXPECT_NEAR(1.537e-16, test, 5.0e-20);
}

TEST_F(UnitConversion, acceleration)
{
	double test;

	test = convert<meters_per_second_squared_t>(standard_gravity_t(1.0))();
	EXPECT_NEAR(9.80665, test, 5.0e-10);
}

TEST_F(UnitConversion, force)
{
	double test;

	test = convert<units::force::newton_t>(units::force::newton_t(1.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<units::force::pound_t>(units::force::newton_t(6.3))();
	EXPECT_NEAR(1.4163, test, 5.0e-5);
	test = convert<units::force::dyne_t>(units::force::newton_t(5.0))();
	EXPECT_NEAR(500000.0, test, 5.0e-5);
	test = convert<units::force::poundal_t>(units::force::newton_t(2.1))();
	EXPECT_NEAR(15.1893, test, 5.0e-5);
	test = convert<units::force::kilopond_t>(units::force::newton_t(173.0))();
	EXPECT_NEAR(17.6411, test, 5.0e-5);
	test = convert<units::force::kilopond_t>(units::force::poundal_t(21.879))();
	EXPECT_NEAR(0.308451933, test, 5.0e-10);
}

TEST_F(UnitConversion, area)
{
	double test;

	test = convert<acre_t>(hectare_t(6.3))();
	EXPECT_NEAR(15.5676, test, 5.0e-5);
	test = convert<square_kilometer_t>(square_mile_t(10.0))();
	EXPECT_NEAR(25.8999, test, 5.0e-5);
	test = convert<square_meter_t>(square_inch_t(4.0))();
	EXPECT_NEAR(0.00258064, test, 5.0e-9);
	test = convert<square_foot_t>(acre_t(5.0))();
	EXPECT_NEAR(217800.0, test, 5.0e-5);
	test = convert<square_foot_t>(square_meter_t(1.0))();
	EXPECT_NEAR(10.7639, test, 5.0e-5);
}

TEST_F(UnitConversion, pressure)
{
	double test;

	test = convert<torr_t>(pascal_t(1.0))();
	EXPECT_NEAR(0.00750062, test, 5.0e-5);
	test = convert<pounds_per_square_inch_t>(bar_t(2.2))();
	EXPECT_NEAR(31.9083, test, 5.0e-5);
	test = convert<bar_t>(atmosphere_t(4.0))();
	EXPECT_NEAR(4.053, test, 5.0e-5);
	test = convert<pascal_t>(torr_t(800.0))();
	EXPECT_NEAR(106657.89474, test, 5.0e-5);
	test = convert<atmosphere_t>(pounds_per_square_inch_t(38.0))();
	EXPECT_NEAR(2.58575, test, 5.0e-5);
	test = convert<pascal_t>(pounds_per_square_inch_t(1.0))();
	EXPECT_NEAR(6894.76, test, 5.0e-3);
	test = convert<bar_t>(pascal_t(0.25))();
	EXPECT_NEAR(2.5e-6, test, 5.0e-5);
	test = convert<atmosphere_t>(torr_t(9.0))();
	EXPECT_NEAR(0.0118421, test, 5.0e-8);
	test = convert<torr_t>(bar_t(12.0))();
	EXPECT_NEAR(9000.74, test, 5.0e-3);
	test = convert<pounds_per_square_inch_t>(atmosphere_t(1.0))();
	EXPECT_NEAR(14.6959, test, 5.0e-5);
}

TEST_F(UnitConversion, charge)
{
	double test;

	test = convert<ampere_hour_t>(coulomb_t(4.0))();
	EXPECT_NEAR(0.00111111, test, 5.0e-9);
	test = convert<coulomb_t>(ampere_hour_t(1.0))();
	EXPECT_NEAR(3600.0, test, 5.0e-6);
}

TEST_F(UnitConversion, energy)
{
	double test;

	test = convert<calorie_t>(joule_t(8000.000464))();
	EXPECT_NEAR(1912.046, test, 5.0e-4);
	test = convert<joule_t>(therm_t(12.0))();
	EXPECT_NEAR(1.266e+9, test, 5.0e5);
	test = convert<watt_hour_t>(megajoule_t(100.0))();
	EXPECT_NEAR(27777.778, test, 5.0e-4);
	test = convert<megajoule_t>(kilocalorie_t(56.0))();
	EXPECT_NEAR(0.234304, test, 5.0e-7);
	test = convert<therm_t>(kilojoule_t(56.0))();
	EXPECT_NEAR(0.000530904, test, 5.0e-5);
	test = convert<kilojoule_t>(british_thermal_unit_t(18.56399995447))();
	EXPECT_NEAR(19.5860568, test, 5.0e-5);
	test = convert<energy::foot_pound_t>(calorie_t(18.56399995447))();
	EXPECT_NEAR(57.28776190423856, test, 5.0e-5);
	test = convert<calorie_t>(megajoule_t(1.0))();
	EXPECT_NEAR(239006.0, test, 5.0e-1);
	test = convert<kilowatt_hour_t>(kilocalorie_t(2.0))();
	EXPECT_NEAR(0.00232444, test, 5.0e-9);
	test = convert<kilocalorie_t>(therm_t(0.1))();
	EXPECT_NEAR(2521.04, test, 5.0e-3);
	test = convert<megajoule_t>(watt_hour_t(67.0))();
	EXPECT_NEAR(0.2412, test, 5.0e-5);
	test = convert<watt_hour_t>(british_thermal_unit_t(100.0))();
	EXPECT_NEAR(29.3071, test, 5.0e-5);
	test = convert<british_thermal_unit_t>(calorie_t(100.0))();
	EXPECT_NEAR(0.396567, test, 5.0e-5);
}

TEST_F(UnitConversion, power)
{
	double test;

	test = convert<watt_t>(unit<compound_unit_conversion<energy::foot_pounds, inverse<seconds>>>(550.0))();
	EXPECT_NEAR(745.7, test, 5.0e-2);
	test = convert<gigawatt_t>(watt_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-4);
	test = convert<watt_t>(microwatt_t(200000.0))();
	EXPECT_NEAR(0.2, test, 5.0e-4);
	test = convert<watt_t>(horsepower_t(100.0))();
	EXPECT_NEAR(74570.0, test, 5.0e-1);
	test = convert<megawatt_t>(horsepower_t(5.0))();
	EXPECT_NEAR(0.0037284994, test, 5.0e-7);
	test = convert<horsepower_t>(kilowatt_t(232.0))();
	EXPECT_NEAR(311.117, test, 5.0e-4);
	test = convert<horsepower_t>(milliwatt_t(1001.0))();
	EXPECT_NEAR(0.001342363, test, 5.0e-9);
}

TEST_F(UnitConversion, voltage)
{
	double test;

	test = convert<millivolt_t>(volt_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<volt_t>(picovolt_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<volt_t>(nanovolt_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<volt_t>(microvolt_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<volt_t>(millivolt_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<volt_t>(kilovolt_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<volt_t>(megavolt_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<volt_t>(gigavolt_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<volt_t>(statvolt_t(299.792458))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<statvolt_t>(millivolt_t(1000.0))();
	EXPECT_NEAR(299.792458, test, 5.0e-5);
	test = convert<nanovolt_t>(abvolt_t(0.1))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<abvolt_t>(microvolt_t(0.01))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
}

TEST_F(UnitConversion, capacitance)
{
	double test;

	test = convert<millifarad_t>(farad_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<farad_t>(picofarad_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<farad_t>(nanofarad_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<farad_t>(microfarad_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<farad_t>(millifarad_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<farad_t>(kilofarad_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<farad_t>(megafarad_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<farad_t>(gigafarad_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
}

TEST_F(UnitConversion, impedance)
{
	double test;

	test = convert<milliohm_t>(ohm_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<ohm_t>(picoohm_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<ohm_t>(nanoohm_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<ohm_t>(microohm_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<ohm_t>(milliohm_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<ohm_t>(kiloohm_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<ohm_t>(megaohm_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<ohm_t>(gigaohm_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
}

TEST_F(UnitConversion, conductance)
{
	double test;

	test = convert<millisiemens_t>(siemens_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<siemens_t>(picosiemens_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<siemens_t>(nanosiemens_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<siemens_t>(microsiemens_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<siemens_t>(millisiemens_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<siemens_t>(kilosiemens_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<siemens_t>(megasiemens_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<siemens_t>(gigasiemens_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
}

TEST_F(UnitConversion, magnetic_flux)
{
	double test;

	test = convert<milliweber_t>(weber_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<weber_t>(picoweber_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<weber_t>(nanoweber_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<weber_t>(microweber_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<weber_t>(milliweber_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<weber_t>(kiloweber_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<weber_t>(megaweber_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<weber_t>(gigaweber_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<weber_t>(maxwell_t(100000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<maxwell_t>(nanoweber_t(10.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
}

TEST_F(UnitConversion, magnetic_field_strength)
{
	double test;

	test = convert<millitesla_t>(tesla_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<tesla_t>(picotesla_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<tesla_t>(nanotesla_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<tesla_t>(microtesla_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<tesla_t>(millitesla_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<tesla_t>(kilotesla_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<tesla_t>(megatesla_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<tesla_t>(gigatesla_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<tesla_t>(gauss_t(10000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<gauss_t>(nanotesla_t(100000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
}

TEST_F(UnitConversion, inductance)
{
	double test;

	test = convert<millihenry_t>(henry_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<henry_t>(picohenry_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<henry_t>(nanohenry_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<henry_t>(microhenry_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<henry_t>(millihenry_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<henry_t>(kilohenry_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<henry_t>(megahenry_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<henry_t>(gigahenry_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
}

TEST_F(UnitConversion, luminous_flux)
{
	double test;

	test = convert<millilumen_t>(lumen_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<lumen_t>(picolumen_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lumen_t>(nanolumen_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lumen_t>(microlumen_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lumen_t>(millilumen_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lumen_t>(kilolumen_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lumen_t>(megalumen_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lumen_t>(gigalumen_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
}

TEST_F(UnitConversion, illuminance)
{
	double test;

	test = convert<millilux_t>(lux_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<lux_t>(picolux_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lux_t>(nanolux_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lux_t>(microlux_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lux_t>(millilux_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lux_t>(kilolux_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lux_t>(megalux_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lux_t>(gigalux_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);

// 	test = convert<lux_t>(footcandle_t(0.092903))();
// 	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<lumens_per_square_inch_t>(lux_t(1550.0031000062))();
	EXPECT_NEAR(1.0, test, 5.0e-13);
	test = convert<lux_t>(phot_t(0.0001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
}

TEST_F(UnitConversion, radiation)
{
	double test;

	test = convert<millibecquerel_t>(becquerel_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<becquerel_t>(picobecquerel_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<becquerel_t>(nanobecquerel_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<becquerel_t>(microbecquerel_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<becquerel_t>(millibecquerel_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<becquerel_t>(kilobecquerel_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<becquerel_t>(megabecquerel_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<becquerel_t>(gigabecquerel_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);

	test = convert<milligray_t>(gray_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<gray_t>(picogray_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<gray_t>(nanogray_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<gray_t>(microgray_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<gray_t>(milligray_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<gray_t>(kilogray_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<gray_t>(megagray_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<gray_t>(gigagray_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);

	test = convert<millisievert_t>(sievert_t(10.0))();
	EXPECT_NEAR(10000.0, test, 5.0e-5);
	test = convert<sievert_t>(picosievert_t(1000000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<sievert_t>(nanosievert_t(1000000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<sievert_t>(microsievert_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<sievert_t>(millisievert_t(1000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<sievert_t>(kilosievert_t(0.001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<sievert_t>(megasievert_t(0.000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<sievert_t>(gigasievert_t(0.000000001))();
	EXPECT_NEAR(1.0, test, 5.0e-5);

	test = convert<curie_t>(becquerel_t(37.0e9))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<rutherford_t>(becquerel_t(1000000.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<gray_t>(rad_t(100.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
}

TEST_F(UnitConversion, torque)
{
	double test;

	test = convert<newton_meter_t>(torque::foot_pound_t(1.0))();
	EXPECT_NEAR(1.355817948, test, 5.0e-5);
	test = convert<newton_meter_t>(inch_pound_t(1.0))();
	EXPECT_NEAR(0.112984829, test, 5.0e-5);
	test = convert<newton_meter_t>(foot_poundal_t(1.0))();
	EXPECT_NEAR(4.214011009e-2, test, 5.0e-5);
	test = convert<newton_meter_t>(meter_kilogram_t(1.0))();
	EXPECT_NEAR(9.80665, test, 5.0e-5);
	test = convert<meter_kilogram_t>(inch_pound_t(86.79616930855788))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<inch_pound_t>(foot_poundal_t(2.681170713))();
	EXPECT_NEAR(1.0, test, 5.0e-5);

}

TEST_F(UnitConversion, volume)
{
	double test;

	test = convert<cubic_meter_t>(cubic_meter_t(1.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<cubic_meter_t>(cubic_millimeter_t(1.0))();
	EXPECT_NEAR(1.0e-9, test, 5.0e-5);
	test = convert<cubic_meter_t>(cubic_kilometer_t(1.0))();
	EXPECT_NEAR(1.0e9, test, 5.0e-5);
	test = convert<cubic_meter_t>(liter_t(1.0))();
	EXPECT_NEAR(0.001, test, 5.0e-5);
	test = convert<cubic_meter_t>(milliliter_t(1.0))();
	EXPECT_NEAR(1.0e-6, test, 5.0e-5);
	test = convert<cubic_meter_t>(cubic_inch_t(1.0))();
	EXPECT_NEAR(1.6387e-5, test, 5.0e-10);
	test = convert<cubic_meter_t>(cubic_foot_t(1.0))();
	EXPECT_NEAR(0.0283168, test, 5.0e-8);
	test = convert<cubic_meter_t>(cubic_yard_t(1.0))();
	EXPECT_NEAR(0.764555, test, 5.0e-7);
	test = convert<cubic_meter_t>(cubic_mile_t(1.0))();
	EXPECT_NEAR(4.168e+9, test, 5.0e5);
	test = convert<cubic_meter_t>(gallon_t(1.0))();
	EXPECT_NEAR(0.00378541, test, 5.0e-8);
	test = convert<cubic_meter_t>(quart_t(1.0))();
	EXPECT_NEAR(0.000946353, test, 5.0e-10);
	test = convert<cubic_meter_t>(pint_t(1.0))();
	EXPECT_NEAR(0.000473176, test, 5.0e-10);
	test = convert<cubic_meter_t>(cup_t(1.0))();
	EXPECT_NEAR(0.00024, test, 5.0e-6);
	test = convert<cubic_meter_t>(volume::fluid_ounce_t(1.0))();
	EXPECT_NEAR(2.9574e-5, test, 5.0e-5);
	test = convert<cubic_meter_t>(barrel_t(1.0))();
	EXPECT_NEAR(0.158987294928, test, 5.0e-13);
	test = convert<cubic_meter_t>(bushel_t(1.0))();
	EXPECT_NEAR(0.0352391, test, 5.0e-8);
	test = convert<cubic_meter_t>(cord_t(1.0))();
	EXPECT_NEAR(3.62456, test, 5.0e-6);
	test = convert<cubic_meter_t>(cubic_fathom_t(1.0))();
	EXPECT_NEAR(6.11644, test, 5.0e-6);
	test = convert<cubic_meter_t>(tablespoon_t(1.0))();
	EXPECT_NEAR(1.4787e-5, test, 5.0e-10);
	test = convert<cubic_meter_t>(teaspoon_t(1.0))();
	EXPECT_NEAR(4.9289e-6, test, 5.0e-11);
	test = convert<cubic_meter_t>(pinch_t(1.0))();
	EXPECT_NEAR(616.11519921875e-9, test, 5.0e-20);
	test = convert<cubic_meter_t>(dash_t(1.0))();
	EXPECT_NEAR(308.057599609375e-9, test, 5.0e-20);
	test = convert<cubic_meter_t>(drop_t(1.0))();
	EXPECT_NEAR(82.14869322916e-9, test, 5.0e-9);
	test = convert<cubic_meter_t>(fifth_t(1.0))();
	EXPECT_NEAR(0.00075708236, test, 5.0e-12);
	test = convert<cubic_meter_t>(dram_t(1.0))();
	EXPECT_NEAR(3.69669e-6, test, 5.0e-12);
	test = convert<cubic_meter_t>(gill_t(1.0))();
	EXPECT_NEAR(0.000118294, test, 5.0e-10);
	test = convert<cubic_meter_t>(peck_t(1.0))();
	EXPECT_NEAR(0.00880977, test, 5.0e-9);
	test = convert<cubic_meter_t>(sack_t(9.4591978))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<cubic_meter_t>(shot_t(1.0))();
	EXPECT_NEAR(4.43603e-5, test, 5.0e-11);
	test = convert<cubic_meter_t>(strike_t(1.0))();
	EXPECT_NEAR(0.07047814033376, test, 5.0e-5);
	test = convert<milliliter_t>(volume::fluid_ounce_t(1.0))();
	EXPECT_NEAR(29.5735, test, 5.0e-5);
}

TEST_F(UnitConversion, density)
{
	double test;

	test = convert<kilograms_per_cubic_meter_t>(kilograms_per_cubic_meter_t(1.0))();
	EXPECT_NEAR(1.0, test, 5.0e-5);
	test = convert<kilograms_per_cubic_meter_t>(grams_per_milliliter_t(1.0))();
	EXPECT_NEAR(1000.0, test, 5.0e-5);
	test = convert<kilograms_per_cubic_meter_t>(kilograms_per_liter_t(1.0))();
	EXPECT_NEAR(1000.0, test, 5.0e-5);
	test = convert<kilograms_per_cubic_meter_t>(ounces_per_cubic_foot_t(1.0))();
	EXPECT_NEAR(1.001153961, test, 5.0e-10);
	test = convert<kilograms_per_cubic_meter_t>(ounces_per_cubic_inch_t(1.0))();
	EXPECT_NEAR(1.729994044e3, test, 5.0e-7);
	test = convert<kilograms_per_cubic_meter_t>(ounces_per_gallon_t(1.0))();
	EXPECT_NEAR(7.489151707, test, 5.0e-10);
	test = convert<kilograms_per_cubic_meter_t>(pounds_per_cubic_foot_t(1.0))();
	EXPECT_NEAR(16.01846337, test, 5.0e-9);
	test = convert<kilograms_per_cubic_meter_t>(pounds_per_cubic_inch_t(1.0))();
	EXPECT_NEAR(2.767990471e4, test, 5.0e-6);
	test = convert<kilograms_per_cubic_meter_t>(pounds_per_gallon_t(1.0))();
	EXPECT_NEAR(119.8264273, test, 5.0e-8);
	test = convert<kilograms_per_cubic_meter_t>(slugs_per_cubic_foot_t(1.0))();
	EXPECT_NEAR(515.3788184, test, 5.0e-6);
}

TEST_F(UnitConversion, concentration)
{
	double test;

	test = ppm_t(1.0);
	EXPECT_NEAR(1.0e-6, test, 5.0e-12);
	test = ppb_t(1.0);
	EXPECT_NEAR(1.0e-9, test, 5.0e-12);
	test = ppt_t(1.0);
	EXPECT_NEAR(1.0e-12, test, 5.0e-12);
	test = percent_t(18.0);
	EXPECT_NEAR(0.18, test, 5.0e-12);
}

TEST_F(UnitConversion, data)
{
	EXPECT_EQ(8, (convert<bit_t>(byte_t(1))()));

	EXPECT_EQ(1000, (convert<byte_t>(kilobyte_t(1))()));
	EXPECT_EQ(1000, (convert<kilobyte_t>(megabyte_t(1))()));
	EXPECT_EQ(1000, (convert<megabyte_t>(gigabyte_t(1))()));
	EXPECT_EQ(1000, (convert<gigabyte_t>(terabyte_t(1))()));
	EXPECT_EQ(1000, (convert<terabyte_t>(petabyte_t(1))()));
	EXPECT_EQ(1000, (convert<petabyte_t>(exabyte_t(1))()));

	EXPECT_EQ(1024, (convert<byte_t>(kibibyte_t(1))()));
	EXPECT_EQ(1024, (convert<kibibyte_t>(mebibyte_t(1))()));
	EXPECT_EQ(1024, (convert<mebibyte_t>(gibibyte_t(1))()));
	EXPECT_EQ(1024, (convert<gibibyte_t>(tebibyte_t(1))()));
	EXPECT_EQ(1024, (convert<tebibyte_t>(pebibyte_t(1))()));
	EXPECT_EQ(1024, (convert<pebibyte_t>(exbibyte_t(1))()));

	EXPECT_EQ(93750000, (convert<kibibit_t>(gigabyte_t(12))()));

	EXPECT_EQ(1000, (convert<bit_t>(kilobit_t(1))()));
	EXPECT_EQ(1000, (convert<kilobit_t>(megabit_t(1))()));
	EXPECT_EQ(1000, (convert<megabit_t>(gigabit_t(1))()));
	EXPECT_EQ(1000, (convert<gigabit_t>(terabit_t(1))()));
	EXPECT_EQ(1000, (convert<terabit_t>(petabit_t(1))()));
	EXPECT_EQ(1000, (convert<petabit_t>(exabit_t(1))()));

	EXPECT_EQ(1024, (convert<bit_t>(kibibit_t(1))()));
	EXPECT_EQ(1024, (convert<kibibit_t>(mebibit_t(1))()));
	EXPECT_EQ(1024, (convert<mebibit_t>(gibibit_t(1))()));
	EXPECT_EQ(1024, (convert<gibibit_t>(tebibit_t(1))()));
	EXPECT_EQ(1024, (convert<tebibit_t>(pebibit_t(1))()));
	EXPECT_EQ(1024, (convert<pebibit_t>(exbibit_t(1))()));

	// Source: https://en.wikipedia.org/wiki/Binary_prefix
	EXPECT_NEAR(percent_t(2.4), kibibyte_t(1) / kilobyte_t(1) - 1, 0.005);
	EXPECT_NEAR(percent_t(4.9), mebibyte_t(1) / megabyte_t(1) - 1, 0.005);
	EXPECT_NEAR(percent_t(7.4), gibibyte_t(1) / gigabyte_t(1) - 1, 0.005);
	EXPECT_NEAR(percent_t(10.0), tebibyte_t(1) / terabyte_t(1) - 1, 0.005);
	EXPECT_NEAR(percent_t(12.6), pebibyte_t(1) / petabyte_t(1) - 1, 0.005);
	EXPECT_NEAR(percent_t(15.3), exbibyte_t(1) / exabyte_t(1) - 1, 0.005);
}

TEST_F(UnitConversion, data_transfer_rate)
{
	EXPECT_EQ(8, (convert<bits_per_second_t>(bytes_per_second_t(1))()));

	EXPECT_EQ(1000, (convert<bytes_per_second_t>(kilobytes_per_second_t(1))()));
	EXPECT_EQ(1000, (convert<kilobytes_per_second_t>(megabytes_per_second_t(1))()));
	EXPECT_EQ(1000, (convert<megabytes_per_second_t>(gigabytes_per_second_t(1))()));
	EXPECT_EQ(1000, (convert<gigabytes_per_second_t>(terabytes_per_second_t(1))()));
	EXPECT_EQ(1000, (convert<terabytes_per_second_t>(petabytes_per_second_t(1))()));
	EXPECT_EQ(1000, (convert<petabytes_per_second_t>(exabytes_per_second_t(1))()));

	EXPECT_EQ(1024, (convert<bytes_per_second_t>(kibibytes_per_second_t(1))()));
	EXPECT_EQ(1024, (convert<kibibytes_per_second_t>(mebibytes_per_second_t(1))()));
	EXPECT_EQ(1024, (convert<mebibytes_per_second_t>(gibibytes_per_second_t(1))()));
	EXPECT_EQ(1024, (convert<gibibytes_per_second_t>(tebibytes_per_second_t(1))()));
	EXPECT_EQ(1024, (convert<tebibytes_per_second_t>(pebibytes_per_second_t(1))()));
	EXPECT_EQ(1024, (convert<pebibytes_per_second_t>(exbibytes_per_second_t(1))()));

	EXPECT_EQ(93750000, (convert<kibibits_per_second_t>(gigabytes_per_second_t(12))()));

	EXPECT_EQ(1000, (convert<bits_per_second_t>(kilobits_per_second_t(1))()));
	EXPECT_EQ(1000, (convert<kilobits_per_second_t>(megabits_per_second_t(1))()));
	EXPECT_EQ(1000, (convert<megabits_per_second_t>(gigabits_per_second_t(1))()));
	EXPECT_EQ(1000, (convert<gigabits_per_second_t>(terabits_per_second_t(1))()));
	EXPECT_EQ(1000, (convert<terabits_per_second_t>(petabits_per_second_t(1))()));
	EXPECT_EQ(1000, (convert<petabits_per_second_t>(exabits_per_second_t(1))()));

	EXPECT_EQ(1024, (convert<bits_per_second_t>(kibibits_per_second_t(1))()));
	EXPECT_EQ(1024, (convert<kibibits_per_second_t>(mebibits_per_second_t(1))()));
	EXPECT_EQ(1024, (convert<mebibits_per_second_t>(gibibits_per_second_t(1))()));
	EXPECT_EQ(1024, (convert<gibibits_per_second_t>(tebibits_per_second_t(1))()));
	EXPECT_EQ(1024, (convert<tebibits_per_second_t>(pebibits_per_second_t(1))()));
	EXPECT_EQ(1024, (convert<pebibits_per_second_t>(exbibits_per_second_t(1))()));

	// Source: https://en.wikipedia.org/wiki/Binary_prefix
	EXPECT_NEAR(percent_t(2.4), kibibytes_per_second_t(1) / kilobytes_per_second_t(1) - 1, 0.005);
	EXPECT_NEAR(percent_t(4.9), mebibytes_per_second_t(1) / megabytes_per_second_t(1) - 1, 0.005);
	EXPECT_NEAR(percent_t(7.4), gibibytes_per_second_t(1) / gigabytes_per_second_t(1) - 1, 0.005);
	EXPECT_NEAR(percent_t(10.0), tebibytes_per_second_t(1) / terabytes_per_second_t(1) - 1, 0.005);
	EXPECT_NEAR(percent_t(12.6), pebibytes_per_second_t(1) / petabytes_per_second_t(1) - 1, 0.005);
	EXPECT_NEAR(percent_t(15.3), exbibytes_per_second_t(1) / exabytes_per_second_t(1) - 1, 0.005);
}

TEST_F(UnitConversion, pi)
{
	EXPECT_TRUE(units::traits::is_dimensionless_unit_v<decltype(constants::pi)>);
	EXPECT_TRUE(units::traits::is_dimensionless_unit_v<constants::PI>);

	// implicit conversion/arithmetic
	EXPECT_NEAR(3.14159, constants::pi, 5.0e-6);
	EXPECT_NEAR(6.28318531, (2 * constants::pi), 5.0e-9);
	EXPECT_NEAR(6.28318531, (constants::pi + constants::pi), 5.0e-9);
	EXPECT_NEAR(0.0, (constants::pi - constants::pi), 5.0e-9);
	EXPECT_NEAR(31.00627668, pow<3>(constants::pi), 5.0e-10);
	EXPECT_NEAR(0.0322515344, (1.0 / pow<3>(constants::pi)), 5.0e-11);
	EXPECT_TRUE(constants::detail::PI_VAL == constants::pi);
	EXPECT_TRUE(1.0 != constants::pi);
	EXPECT_TRUE(4.0 > constants::pi);
	EXPECT_TRUE(3.0 < constants::pi);
	EXPECT_TRUE(constants::pi > 3.0);
	EXPECT_TRUE(constants::pi < 4.0);

	// explicit conversion
	EXPECT_NEAR(3.14159, constants::pi.to<double>(), 5.0e-6);

	// auto multiplication
	EXPECT_TRUE((std::is_same_v<meter_t, decltype(constants::pi * meter_t(1))>));
	EXPECT_TRUE((std::is_same_v<meter_t, decltype(meter_t(1) * constants::pi)>));

	EXPECT_NEAR(constants::detail::PI_VAL, (constants::pi * meter_t(1)).to<double>(), 5.0e-10);
	EXPECT_NEAR(constants::detail::PI_VAL, (meter_t(1) * constants::pi).to<double>(), 5.0e-10);

	// explicit multiplication
	meter_t a = constants::pi * meter_t(1);
	meter_t b = meter_t(1) * constants::pi;

	EXPECT_NEAR(constants::detail::PI_VAL, a.to<double>(), 5.0e-10);
	EXPECT_NEAR(constants::detail::PI_VAL, b.to<double>(), 5.0e-10);

	// auto division
	EXPECT_TRUE((std::is_same_v<hertz_t, decltype(constants::pi / second_t(1))>));
	EXPECT_TRUE((std::is_same_v<second_t, decltype(second_t(1) / constants::pi)>));

	EXPECT_NEAR(constants::detail::PI_VAL, (constants::pi / second_t(1)).to<double>(), 5.0e-10);
	EXPECT_NEAR(1.0 / constants::detail::PI_VAL, (second_t(1) / constants::pi).to<double>(), 5.0e-10);

	// explicit
	hertz_t c = constants::pi / second_t(1);
	second_t d = second_t(1) / constants::pi;

	EXPECT_NEAR(constants::detail::PI_VAL, c.to<double>(), 5.0e-10);
	EXPECT_NEAR(1.0 / constants::detail::PI_VAL, d.to<double>(), 5.0e-10);
}

TEST_F(UnitConversion, constants)
{
	// Source: NIST "2014 CODATA recommended values" 
	EXPECT_NEAR(299792458, constants::c(), 5.0e-9);
	EXPECT_NEAR(6.67408e-11, constants::G(), 5.0e-17);
	EXPECT_NEAR(6.626070040e-34, constants::h(), 5.0e-44);
	EXPECT_NEAR(1.2566370614e-6, constants::mu0(), 5.0e-17);
	EXPECT_NEAR(8.854187817e-12, constants::epsilon0(), 5.0e-21);
	EXPECT_NEAR(376.73031346177, constants::Z0(), 5.0e-12); 
	EXPECT_NEAR(8987551787.3681764, constants::k_e(), 5.0e-6);
	EXPECT_NEAR(1.6021766208e-19, constants::e(), 5.0e-29);
	EXPECT_NEAR(9.10938356e-31, constants::m_e(), 5.0e-40);
	EXPECT_NEAR(1.672621898e-27, constants::m_p(), 5.0e-37);
	EXPECT_NEAR(9.274009994e-24, constants::mu_B(), 5.0e-32);
	EXPECT_NEAR(6.022140857e23, constants::N_A(), 5.0e14);
	EXPECT_NEAR(8.3144598, constants::R(), 5.0e-8);
	EXPECT_NEAR(1.38064852e-23, constants::k_B(), 5.0e-31);
	EXPECT_NEAR(96485.33289, constants::F(), 5.0e-5);
	EXPECT_NEAR(5.670367e-8, constants::sigma(), 5.0e-14);
}

TEST_F(UnitConversion, std_chrono)
{
	nanosecond_t a = std::chrono::nanoseconds(10);
	EXPECT_EQ(nanosecond_t(10), a);
	microsecond_t b = std::chrono::microseconds(10);
	EXPECT_EQ(microsecond_t(10), b);
	millisecond_t c = std::chrono::milliseconds(10);
	EXPECT_EQ(millisecond_t(10), c);
	second_t d = std::chrono::seconds(1);
	EXPECT_EQ(second_t(1), d);
	minute_t e = std::chrono::minutes(120);
	EXPECT_EQ(minute_t(120), e);
	hour_t f = std::chrono::hours(2);
	EXPECT_EQ(hour_t(2), f);

	std::chrono::nanoseconds g = nanosecond_t(100);
	EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(g).count(), 100);
	std::chrono::nanoseconds h = microsecond_t(2);
	EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(h).count(), 2000);
	std::chrono::nanoseconds i = millisecond_t(1);
	EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(i).count(), 1000000);
	std::chrono::nanoseconds j = second_t(1);
	EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(j).count(), 1000000000);
	std::chrono::nanoseconds k = minute_t(1);
	EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(k).count(), 60000000000);
	std::chrono::nanoseconds l = hour_t(1);
	EXPECT_EQ(std::chrono::duration_cast<std::chrono::nanoseconds>(l).count(), 3600000000000);
}

TEST_F(UnitConversion, squaredTemperature)
{
	using squared_celsius = units::compound_unit_conversion<squared<celsius>>;
	using squared_celsius_t = units::unit<squared_celsius>;
	const squared_celsius_t right(100);
	const celsius_t rootRight = sqrt(right);
	EXPECT_EQ(celsius_t(10), rootRight);
}

TEST_F(UnitMath, min)
{
	meter_t a(1);
	meter_t b(2);
	foot_t c(1);
	EXPECT_EQ(c, units::min(a, c));
}

TEST_F(UnitMath, max)
{
	meter_t a(1);
	meter_t b(2);
	foot_t c(1);
	EXPECT_EQ(a, max(a, c));
}

TEST_F(UnitMath, cos)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<dimensionless>::type, typename std::decay<decltype(cos(angle::radian_t(0)))>::type>));
	EXPECT_NEAR(dimensionless(-0.41614683654), cos(angle::radian_t(2)), 5.0e-11);
	EXPECT_NEAR(dimensionless(-0.70710678118), cos(angle::degree_t(135)), 5.0e-11);
}

TEST_F(UnitMath, sin)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<dimensionless>::type, typename std::decay<decltype(sin(angle::radian_t(0)))>::type>));
	EXPECT_NEAR(dimensionless(0.90929742682), sin(angle::radian_t(2)), 5.0e-11);
	EXPECT_NEAR(dimensionless(0.70710678118), sin(angle::degree_t(135)), 5.0e-11);
}

TEST_F(UnitMath, tan)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<dimensionless>::type, typename std::decay<decltype(tan(angle::radian_t(0)))>::type>));
	EXPECT_NEAR(dimensionless(-2.18503986326), tan(angle::radian_t(2)), 5.0e-11);
	EXPECT_NEAR(dimensionless(-1.0), tan(angle::degree_t(135)), 5.0e-11);
}

TEST_F(UnitMath, acos)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<angle::radian_t>::type, typename std::decay<decltype(acos(dimensionless(0)))>::type>));
	EXPECT_NEAR(angle::radian_t(2).to<double>(), acos(dimensionless(-0.41614683654)).to<double>(), 5.0e-11);
	EXPECT_NEAR(angle::degree_t(135).to<double>(), angle::degree_t(acos(dimensionless(-0.70710678118654752440084436210485))).to<double>(), 5.0e-12);
}

TEST_F(UnitMath, asin)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<angle::radian_t>::type, typename std::decay<decltype(asin(dimensionless(0)))>::type>));
	EXPECT_NEAR(angle::radian_t(1.14159265).to<double>(), asin(dimensionless(0.90929742682)).to<double>(), 5.0e-9);
	EXPECT_NEAR(angle::degree_t(45).to<double>(), angle::degree_t(asin(dimensionless(0.70710678118654752440084436210485))).to<double>(), 5.0e-12);
}

TEST_F(UnitMath, atan)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<angle::radian_t>::type, typename std::decay<decltype(atan(dimensionless(0)))>::type>));
	EXPECT_NEAR(angle::radian_t(-1.14159265).to<double>(), atan(dimensionless(-2.18503986326)).to<double>(), 5.0e-9);
	EXPECT_NEAR(angle::degree_t(-45).to<double>(), angle::degree_t(atan(dimensionless(-1.0))).to<double>(), 5.0e-12);
}

TEST_F(UnitMath, atan2)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<angle::radian_t>::type, typename std::decay<decltype(atan2(dimensionless(1), dimensionless(1)))>::type>));
	EXPECT_NEAR(angle::radian_t(constants::detail::PI_VAL / 4).to<double>(), atan2(dimensionless(2), dimensionless(2)).to<double>(), 5.0e-12);
	EXPECT_NEAR(angle::degree_t(45).to<double>(), angle::degree_t(atan2(dimensionless(2), dimensionless(2))).to<double>(), 5.0e-12);

	EXPECT_TRUE((std::is_same_v<typename std::decay<angle::radian_t>::type, typename std::decay<decltype(atan2(dimensionless(1), dimensionless(1)))>::type>));
	EXPECT_NEAR(angle::radian_t(constants::detail::PI_VAL / 6).to<double>(), atan2(dimensionless(1), sqrt(dimensionless(3))).to<double>(), 5.0e-12);
	EXPECT_NEAR(angle::degree_t(30).to<double>(), angle::degree_t(atan2(dimensionless(1), sqrt(dimensionless(3)))).to<double>(), 5.0e-12);
}

TEST_F(UnitMath, cosh)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<dimensionless>::type, typename std::decay<decltype(cosh(angle::radian_t(0)))>::type>));
	EXPECT_NEAR(dimensionless(3.76219569108), cosh(angle::radian_t(2)), 5.0e-11);
	EXPECT_NEAR(dimensionless(5.32275215), cosh(angle::degree_t(135)), 5.0e-9);
}

TEST_F(UnitMath, sinh)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<dimensionless>::type, typename std::decay<decltype(sinh(angle::radian_t(0)))>::type>));
	EXPECT_NEAR(dimensionless(3.62686040785), sinh(angle::radian_t(2)), 5.0e-11);
	EXPECT_NEAR(dimensionless(5.22797192), sinh(angle::degree_t(135)), 5.0e-9);
}

TEST_F(UnitMath, tanh)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<dimensionless>::type, typename std::decay<decltype(tanh(angle::radian_t(0)))>::type>));
	EXPECT_NEAR(dimensionless(0.96402758007), tanh(angle::radian_t(2)), 5.0e-11);
	EXPECT_NEAR(dimensionless(0.98219338), tanh(angle::degree_t(135)), 5.0e-11);
}

TEST_F(UnitMath, acosh)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<angle::radian_t>::type, typename std::decay<decltype(acosh(dimensionless(0)))>::type>));
	EXPECT_NEAR(angle::radian_t(1.316957896924817).to<double>(), acosh(dimensionless(2.0)).to<double>(), 5.0e-11);
	EXPECT_NEAR(angle::degree_t(75.456129290216893).to<double>(), angle::degree_t(acosh(dimensionless(2.0))).to<double>(), 5.0e-12);
}

TEST_F(UnitMath, asinh)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<angle::radian_t>::type, typename std::decay<decltype(asinh(dimensionless(0)))>::type>));
	EXPECT_NEAR(angle::radian_t(1.443635475178810).to<double>(), asinh(dimensionless(2)).to<double>(), 5.0e-9);
	EXPECT_NEAR(angle::degree_t(82.714219883108939).to<double>(), angle::degree_t(asinh(dimensionless(2))).to<double>(), 5.0e-12);
}

TEST_F(UnitMath, atanh)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<angle::radian_t>::type, typename std::decay<decltype(atanh(dimensionless(0)))>::type>));
	EXPECT_NEAR(angle::radian_t(0.549306144334055).to<double>(), atanh(dimensionless(0.5)).to<double>(), 5.0e-9);
	EXPECT_NEAR(angle::degree_t(31.472923730945389).to<double>(), angle::degree_t(atanh(dimensionless(0.5))).to<double>(), 5.0e-12);
}

TEST_F(UnitMath, exp)
{
	double val = 10.0;
	EXPECT_EQ(std::exp(val), exp(dimensionless(val)));
}

TEST_F(UnitMath, log)
{
	double val = 100.0;
	EXPECT_EQ(std::log(val), log(dimensionless(val)));
}

TEST_F(UnitMath, log10)
{
	double val = 100.0;
	EXPECT_EQ(std::log10(val), log10(dimensionless(val)));
}

TEST_F(UnitMath, modf)
{
	double val = 100.0;
	double modfr1;
	dimensionless modfr2;
	EXPECT_EQ(std::modf(val, &modfr1), modf(dimensionless(val), &modfr2));
	EXPECT_EQ(modfr1, modfr2);
}

TEST_F(UnitMath, exp2)
{
	double val = 10.0;
	EXPECT_EQ(std::exp2(val), exp2(dimensionless(val)));
}

TEST_F(UnitMath, expm1)
{
	double val = 10.0;
	EXPECT_EQ(std::expm1(val), expm1(dimensionless(val)));
}

TEST_F(UnitMath, log1p)
{
	double val = 10.0;
	EXPECT_EQ(std::log1p(val), log1p(dimensionless(val)));
}

TEST_F(UnitMath, log2)
{
	double val = 10.0;
	EXPECT_EQ(std::log2(val), log2(dimensionless(val)));
}

TEST_F(UnitMath, pow)
{
	bool isSame;
	meter_t value(10.0);

	auto sq = pow<2>(value);
	EXPECT_NEAR(100.0, sq(), 5.0e-2);
	isSame = std::is_same_v<decltype(sq), square_meter_t>;
	EXPECT_TRUE(isSame);

	auto cube = pow<3>(value);
	EXPECT_NEAR(1000.0, cube(), 5.0e-2);
	isSame = std::is_same_v<decltype(cube), unit<cubed<meter>>>;
	EXPECT_TRUE(isSame);

	auto fourth = pow<4>(value);
	EXPECT_NEAR(10000.0, fourth(), 5.0e-2);
	isSame = std::is_same_v<decltype(fourth), unit<compound_unit_conversion<squared<meter>, squared<meter>>>>;
	EXPECT_TRUE(isSame);
}

TEST_F(UnitMath, sqrt)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<meter_t>::type, typename std::decay<decltype(sqrt(square_meter_t(4.0)))>::type>));
	EXPECT_NEAR(meter_t(2.0).to<double>(), sqrt(square_meter_t(4.0)).to<double>(), 5.0e-9);

	EXPECT_TRUE((std::is_same_v<typename std::decay<angle::radian_t>::type, typename std::decay<decltype(sqrt(steradian_t(16.0)))>::type>));
	EXPECT_NEAR(angle::radian_t(4.0).to<double>(), sqrt(steradian_t(16.0)).to<double>(), 5.0e-9);

	EXPECT_TRUE((std::is_convertible_v<typename std::decay<foot_t>::type, typename std::decay<decltype(sqrt(square_foot_t(10.0)))>::type>));

	// for rational conversion (i.e. no integral root) let's check a bunch of different ways this could go wrong
	foot_t resultFt = sqrt(square_foot_t(10.0));
	EXPECT_NEAR(foot_t(3.16227766017).to<double>(), sqrt(square_foot_t(10.0)).to<double>(), 5.0e-9);
	EXPECT_NEAR(foot_t(3.16227766017).to<double>(), resultFt.to<double>(), 5.0e-9);
	EXPECT_EQ(resultFt, sqrt(square_foot_t(10.0)));
}

TEST_F(UnitMath, hypot)
{
	EXPECT_TRUE((std::is_same_v<typename std::decay<meter_t>::type, typename std::decay<decltype(hypot(meter_t(3.0), meter_t(4.0)))>::type>));
	EXPECT_NEAR(meter_t(5.0).to<double>(), (hypot(meter_t(3.0), meter_t(4.0))).to<double>(), 5.0e-9);

	EXPECT_TRUE((std::is_same_v<typename std::decay<foot_t>::type, typename std::decay<decltype(hypot(foot_t(3.0), meter_t(1.2192)))>::type>));
	EXPECT_NEAR(foot_t(5.0).to<double>(), (hypot(foot_t(3.0), meter_t(1.2192))).to<double>(), 5.0e-9);
}

TEST_F(UnitMath, ceil)
{
	double val = 101.1;
	EXPECT_EQ(ceil(val), ceil(meter_t(val)).to<double>());
	EXPECT_TRUE((std::is_same_v<typename std::decay<meter_t>::type, typename std::decay<decltype(ceil(meter_t(val)))>::type>));
}

TEST_F(UnitMath, floor)
{
	double val = 101.1;
	EXPECT_EQ(floor(val), floor(dimensionless(val)));
}

TEST_F(UnitMath, fmod)
{
	EXPECT_EQ(fmod(100.0, 101.2), fmod(meter_t(100.0), meter_t(101.2)).to<double>());
}

TEST_F(UnitMath, trunc)
{
	double val = 101.1;
	EXPECT_EQ(trunc(val), trunc(dimensionless(val)));
}

TEST_F(UnitMath, round)
{
	double val = 101.1;
	EXPECT_EQ(round(val), round(dimensionless(val)));
}

TEST_F(UnitMath, copysign)
{
	double sign = -1;
	meter_t val(5.0);
	EXPECT_EQ(meter_t(-5.0), copysign(val, sign));
	EXPECT_EQ(meter_t(-5.0), copysign(val, angle::radian_t(sign)));
}

TEST_F(UnitMath, fdim)
{
	EXPECT_EQ(meter_t(0.0), fdim(meter_t(8.0), meter_t(10.0)));
	EXPECT_EQ(meter_t(2.0), fdim(meter_t(10.0), meter_t(8.0)));
	EXPECT_NEAR(meter_t(9.3904).to<double>(), fdim(meter_t(10.0), foot_t(2.0)).to<double>(), 5.0e-320);	// not sure why they aren't comparing exactly equal, but clearly they are.
}

TEST_F(UnitMath, fmin)
{
	EXPECT_EQ(meter_t(8.0), fmin(meter_t(8.0), meter_t(10.0)));
	EXPECT_EQ(meter_t(8.0), fmin(meter_t(10.0), meter_t(8.0)));
	EXPECT_EQ(foot_t(2.0), fmin(meter_t(10.0), foot_t(2.0)));
}

TEST_F(UnitMath, fmax)
{
	EXPECT_EQ(meter_t(10.0), fmax(meter_t(8.0), meter_t(10.0)));
	EXPECT_EQ(meter_t(10.0), fmax(meter_t(10.0), meter_t(8.0)));
	EXPECT_EQ(meter_t(10.0), fmax(meter_t(10.0), foot_t(2.0)));
}

TEST_F(UnitMath, fabs)
{
	EXPECT_EQ(meter_t(10.0), fabs(meter_t(-10.0)));
	EXPECT_EQ(meter_t(10.0), fabs(meter_t(10.0)));
}

TEST_F(UnitMath, abs)
{
	EXPECT_EQ(meter_t(10.0), abs(meter_t(-10.0)));
	EXPECT_EQ(meter_t(10.0), abs(meter_t(10.0)));
}

TEST_F(UnitMath, fma)
{
	meter_t x(2.0);
	meter_t y(3.0);
	square_meter_t z(1.0);
	EXPECT_EQ(square_meter_t(7.0), (units::fma(x, y, z)));
}

// Constexpr
TEST_F(Constexpr, construction)
{
	constexpr meter_t result0(0);
	constexpr auto result1 = make_unit<meter_t>(1);
	constexpr auto result2 = meter_t(2);
	
	EXPECT_EQ(meter_t(0), result0);
	EXPECT_EQ(meter_t(1), result1);
	EXPECT_EQ(meter_t(2), result2);

	EXPECT_TRUE(noexcept(meter_t(0)));
	EXPECT_TRUE(noexcept(make_unit<meter_t>(1)));
}

TEST_F(Constexpr, constants)
{
	EXPECT_TRUE(noexcept(constants::c()));
	EXPECT_TRUE(noexcept(constants::G()));
	EXPECT_TRUE(noexcept(constants::h()));
	EXPECT_TRUE(noexcept(constants::mu0()));
	EXPECT_TRUE(noexcept(constants::epsilon0()));
	EXPECT_TRUE(noexcept(constants::Z0()));
	EXPECT_TRUE(noexcept(constants::k_e()));
	EXPECT_TRUE(noexcept(constants::e()));
	EXPECT_TRUE(noexcept(constants::m_e()));
	EXPECT_TRUE(noexcept(constants::m_p()));
	EXPECT_TRUE(noexcept(constants::mu_B()));
	EXPECT_TRUE(noexcept(constants::N_A()));
	EXPECT_TRUE(noexcept(constants::R()));
	EXPECT_TRUE(noexcept(constants::k_B()));
	EXPECT_TRUE(noexcept(constants::F()));
	EXPECT_TRUE(noexcept(constants::sigma()));
}

TEST_F(Constexpr, arithmetic)
{
	constexpr auto result0(1_m + 1_m);
	constexpr auto result1(1_m - 1_m);
	constexpr auto result2(1_m * 1_m);
	constexpr auto result3(1_m / 1_m);
	constexpr auto result4(meter_t(1) + meter_t(1));
	constexpr auto result5(meter_t(1) - meter_t(1));
	constexpr auto result6(meter_t(1) * meter_t(1));
	constexpr auto result7(meter_t(1) / meter_t(1));
	constexpr auto result8(pow<2>(meter_t(2)));
	constexpr auto result9 = pow<3>(2_m);
	constexpr auto result10 = 2_m * 2_m;

	EXPECT_TRUE(noexcept(1_m + 1_m));
	EXPECT_TRUE(noexcept(1_m - 1_m));
	EXPECT_TRUE(noexcept(1_m * 1_m));
	EXPECT_TRUE(noexcept(1_m / 1_m));
	EXPECT_TRUE(noexcept(meter_t(1) + meter_t(1)));
	EXPECT_TRUE(noexcept(meter_t(1) - meter_t(1)));
	EXPECT_TRUE(noexcept(meter_t(1) * meter_t(1)));
	EXPECT_TRUE(noexcept(meter_t(1) / meter_t(1)));
	EXPECT_TRUE(noexcept(pow<2>(meter_t(2))));
	EXPECT_TRUE(noexcept(pow<3>(2_m)));
	EXPECT_TRUE(noexcept(2_m * 2_m));
	
	meter_t m{ 42 };
	EXPECT_TRUE(noexcept(+m));
	EXPECT_TRUE(noexcept(-m));
	EXPECT_TRUE(noexcept(++m));
	EXPECT_TRUE(noexcept(--m));
	EXPECT_TRUE(noexcept(m++));
	EXPECT_TRUE(noexcept(m--));

	EXPECT_EQ(8_cu_m, result9);
	EXPECT_EQ(4_sq_m, result10);
}

TEST_F(Constexpr, assignment)
{
	auto testConstexpr = []() constexpr noexcept
	{
		meter_t m{ 42 };
		+m;
		-m;
		++m;
		--m;
		m++;
		m--;
		m += 2_m;
		m -= 2_m;
		m *= 2;
		m /= 2;
		return m;
	};

	constexpr auto m = testConstexpr();
}

TEST_F(Constexpr, realtional)
{
	constexpr bool equalityTrue = (1_m == 1_m);
	constexpr bool equalityFalse = (1_m == 2_m);
	constexpr bool lessThanTrue = (1_m < 2_m);
	constexpr bool lessThanFalse = (1_m < 1_m);
	constexpr bool lessThanEqualTrue1 = (1_m <= 1_m);
	constexpr bool lessThanEqualTrue2 = (1_m <= 2_m);
	constexpr bool lessThanEqualFalse = (1_m < 0_m);
	constexpr bool greaterThanTrue = (2_m > 1_m);
	constexpr bool greaterThanFalse = (2_m > 2_m);
	constexpr bool greaterThanEqualTrue1 = (2_m >= 1_m);
	constexpr bool greaterThanEqualTrue2 = (2_m >= 2_m);
	constexpr bool greaterThanEqualFalse = (2_m > 3_m);

	EXPECT_TRUE(equalityTrue);
	EXPECT_TRUE(lessThanTrue);
	EXPECT_TRUE(lessThanEqualTrue1);
	EXPECT_TRUE(lessThanEqualTrue2);
	EXPECT_TRUE(greaterThanTrue);
	EXPECT_TRUE(greaterThanEqualTrue1);
	EXPECT_TRUE(greaterThanEqualTrue2);
	EXPECT_FALSE(equalityFalse);
	EXPECT_FALSE(lessThanFalse);
	EXPECT_FALSE(lessThanEqualFalse);
	EXPECT_FALSE(greaterThanFalse);
	EXPECT_FALSE(greaterThanEqualFalse);
}

TEST_F(Constexpr, stdArray)
{
	constexpr std::array<meter_t, 5> arr{{0_m, 1_m, 2_m, 3_m, 4_m}};
	constexpr bool equal = (arr[3] == 3_m);
	EXPECT_TRUE(equal);
}

TEST_F(CaseStudies, radarRangeEquation)
{
	watt_t				P_t;				// transmit power
	dimensionless		G;					// gain
	meter_t				lambda;				// wavelength
	square_meter_t		sigma;				// radar cross section
	meter_t				R;					// range
	kelvin_t			T_s;				// system noise temp
	hertz_t				B_n;				// bandwidth
	dimensionless		L;					// loss

	P_t = megawatt_t(1.4);
	G = dB_t(33.0);
	lambda = constants::c / megahertz_t(2800);
	sigma = square_meter_t(1.0);
	R = meter_t(111000.0);
	T_s = kelvin_t(950.0);
	B_n = megahertz_t(1.67);
	L = dB_t(8.0);

	dimensionless SNR = (P_t * pow<2>(G) * pow<2>(lambda) * sigma) /
		(pow<3>(4 * constants::pi) * pow<4>(R) * constants::k_B * T_s * B_n * L);

	EXPECT_NEAR(1.535, SNR(), 5.0e-4);
}

TEST_F(CaseStudies, rightTriangle)
{
	constexpr auto a = 3_m;
	constexpr auto b = 4_m;
	constexpr auto c = sqrt(pow<2>(a) + pow<2>(b));
	EXPECT_EQ(5_m, c);
}

TEST_F(CaseStudies, selfDefinedUnits)
{
	using liters_per_second = decltype(1_L / 1_s);
	using gallons_per_minute = decltype(1_gal / 1_min);

	liters_per_second lps(5);
	gallons_per_minute gpm = lps;

	EXPECT_NEAR(79.2516157, gpm.to<double>(), 0.5e-7);

	testing::internal::CaptureStdout();
	std::cout << lps;
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("0.005 m^3 s^-1", output.c_str());

	testing::internal::CaptureStdout();
	std::cout << gpm;
	output = testing::internal::GetCapturedStdout();
	EXPECT_STREQ("0.005 m^3 s^-1", output.c_str());
}

int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
