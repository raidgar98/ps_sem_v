#pragma once

#pragma GCC diagnostic push 
#pragma GCC diagnostic ignored "-Wnarrowing"

// STL
#include <random>

// Project includes
#include "../../engine/include/area.h"

class init_visitor :
		private Log<init_visitor>,
		public visits<area>
{
	using Log<init_visitor>::get_logger;

public:
	virtual bool visit(area *) override;

private:

	template <typename T>
	T rng(const T _from, const T _to) const
	{
		// check is T a number
		static_assert( std::__or_<std::is_floating_point<T>, std::is_integral<T> >::value );
		static std::random_device _eng;

		const auto __floating_rng = [&](){ return std::uniform_real_distribution<double>{_from, _to}(_eng); };
		const auto __integer_rng = [&](){ return std::uniform_int_distribution<long long int>{_from, _to}(_eng); };

		if (std::is_floating_point<T>::value)
			return static_cast<T>(__floating_rng());
		else
			return static_cast<T>(__integer_rng());
	}

	bool flip_coin() const { return rng<double>(0.0, 1.0) >= 0.5; }

	ship construct_ship( const unumber max_x, const unumber max_y, const std::vector<ship>& ) const;
};

#pragma GCC diagnostic pop
