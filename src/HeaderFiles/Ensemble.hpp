#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP

#include <iostream>
#include <cstdlib>

using namespace std;

const int MAXCARD = 10e3;

/**
 * @brief Represents a fixed-size set of integers with basic operations.
 *
 * Used to manage collections of grid coordinates or other integer-based IDs.
 */
struct Ensemble {
public:
  /// Default constructor. Initializes an empty set.
  Ensemble();

  /// Returns true if the set is empty.
  bool estVide() const;

  /// Returns the number of elements in the set.
  int cardinal() const;

  /// Gets the value at position `o` in the internal array.
  int getPosition(int o) const;

  /// Adds an element `o` to the set.
  void ajoute(int o);

  /// Randomly selects and removes an element from the set. Returns its value.
  int tire();

  /// Sets the element at index `i` to value `o`.
  void setValue(int i, int o);

  /// Removes the element at index `i`.
  void erase(int i);

  /// Fills the set with `amount` repetitions of `value`.
  void set(int value, int amount);

  /// Clears the set (removes all elements).
  void clear();

  /// Stream output operator for printing the set.
  std::ostream& operator<<(std::ostream& out);

  /// Access operator for reading element at index `i`.
  int operator[](int i) const;

private:
  int t[MAXCARD]; ///< Internal storage array.
  int card;       ///< Current number of elements in the set.
};

#endif
