#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

// This header-only Random namespace implements a self-seeding Mersenne Twister.
// Requires C++17 or newer.
// It can be #included into as many code files as needed (The inline keyword avoids ODR violations)
// Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
namespace Random
{
	// Returns a seeded Mersenne Twister
	// Note: we'd prefer to return a std::seed_seq (to initialize a std::mt19937), but std::seed can't be copied, so it can't be returned by value.
	// Instead, we'll create a std::mt19937, seed it, and then return the std::mt19937 (which can be copied).
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	// Here's our global std::mt19937 object.
	// The inline keyword means we only have one global instance for our whole program.
	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}

	// The following function templates can be used to generate random numbers
	// when min and/or max are not type int
	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	// You can ignore these if you don't understand them

	// Generate a random value between [min, max] (inclusive)
	// * min and max have same type
	// * Return value has same type as min and max
	// * Supported types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// Sample call: Random::get(1L, 6L);             // returns long
	// Sample call: Random::get(1u, 6u);             // returns unsigned int
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	// Generate a random value between [min, max] (inclusive)
	// * min and max can have different types
	// * Must explicitly specify return type as template type argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}

	// Generate a random integral value between [min, max] (inclusive)
	// * min and max can have different types
	// * Must explicitly specify return type as template type argument
	// * min and max will be converted to std::common_type_t<decltype(min), decltype(max)>
	// * argument supported types: as long as std::common_type_t<decltype(min), decltype(max)> returns
	// * an integral of types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// * you're good to go
	// * Casting supported types: any type that defines a conversion from integrals
	// * result will be casted to the specified return type
	// Sample Call: Random::getCast<bool>(0ll, 5u);  // returns bool
	template <typename R, typename S, typename T>
	R getCast(S min, T max)
	{
		using commonType = std::common_type_t<S, T, int>; // forces the commonType to either be integral or fail
		return static_cast<R>(get<commonType>(min, max));
	}

	// Generate a random float value between [min, max) (inclusive of min, exclusive of max)
	// * min and max have same type
	// * Return value has same type as min and max
	// * Supported types:
	//      * float, double, long double
	// Sample call: Random::getf(1.0f, 6.0f);             // returns float
	// Sample call: Random::getf(1.0, 6.0);             // returns double
	template <typename T>
	T getf(T min, T max)
	{
		return std::uniform_real_distribution<T>{min, max}(mt);
	}

	// Generate a random float value between [min, max) (inclusive of min, exclusive of max)
	// * min and max can have different types
	// * Must explicitly specify return type as template type argument
	// * min and max will be converted to the return type
	// * Supported types:
	//      * float, double, long double
	// Sample call: Random::getf<float>(0.0, 6.0l);  // returns float
	template <typename R, typename S, typename T>
	R getf(S min, T max)
	{
		return getf<R>(static_cast<R>(min), static_cast<R>(max));
	}

	// Generate a random float value between [min, max) (inclusive of min, exclusive of max)
	// * min and max can have different types
	// * Must explicitly specify return type as template type argument
	// * min and max will be converted to std::common_type_t<decltype(min), decltype(max), double>
	// * result will be casted to the specified return type
	// * Supported types: any types that std::common_type_t<decltype(min), decltype(max), double>
	// * returns for a floating-point number
	// * Casting supported types: any type that defines a conversion from numerical types
	// Sample Call: Random::getfCast<int>(9.7f, 5.0l);  // returns int
	template <typename R, typename S, typename T>
	R getfCast(S min, T max)
	{
		using commonType = std::common_type_t<S, T, double>; // forces the commonType to either be floating-point or fail
		return static_cast<R>(getf<commonType>(min, max));
	}

}
// namespace Random

#endif