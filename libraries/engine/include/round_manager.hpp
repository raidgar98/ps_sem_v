#pragma once

// STL
#include <algorithm>
#include <functional>

// Project includes
#include "../../types.hpp"
#include "../../logger/include/logger.h"

template <class _iterable>
class round_manager : Log<round_manager<_iterable> >
{

	using collection_t = _iterable;
	using iterator_t = decltype(((collection_t *)(nullptr))->begin());
	using win_check = std::function<bool(const collection_t &)>;
	using value_type = typename collection_t::value_type;

public:
	class round_iterator
	{
	public:
		void operator++(int) { *this = mgr.get_it(nm); }
		bool operator!=(const round_iterator &it) { return nm != it.nm; }
		round_manager::value_type &operator*()
		{
			assert(nm >= 0);
			return *std::advance(mgr.players.begin(), nm);
		}
		round_manager::value_type &operator->()
		{
			assert(nm >= 0);
			return *std::advance(mgr.players.begin(), nm);
		}

	private:
		round_iterator(round_manager &_mgr, const number nm) : mgr{_mgr}, nm{nm} {}
		round_manager<_iterable> &mgr;
		number nm;

		friend class round_manager<_iterable>;
	};

	friend class round_iterator;// using value_type = collection::value_type;

	round_iterator begin() const
	{
		return get_it(-2);
	}

	round_iterator end() const
	{
		return get_it(players.size());
	}

	round_manager(collection_t& players, win_check check) : players{ players }, is_win{ check } { assert( players.size() >= 2 ); }

private:
	collection_t &players;
	win_check is_win;

	round_iterator get_it(const number nm) const
	{
		if (is_win(players) or nm == -2)
			return round_iterator(*this, -1);
		else
		{
			if (nm >= players.size() - 1)
				return round_iterator(*this, 0);
			else
				return round_iterator(*this, nm + 1);
		}
	}
};
