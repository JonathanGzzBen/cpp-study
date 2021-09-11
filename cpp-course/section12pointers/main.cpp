/* Section 12
 * Challenge
 *
 * Write a C++ function named apply_all that expects two arrays of integers and
 * their sizes and dynamically allocates a new array of integers whose size is
 * the product of the 2 array sizes
 *
 * The function should loop through the second array and multiple each element
 * across each element of array 1 and store the product in the newly created
 * array.
 *
 * The function should return a pointer to the newly allocated array
 */
#include <iostream>
#include <ostream>

int* apply_all(const int* const arr1, size_t len_arr1, const int* const arr2, size_t len_arr2) {
  int* new_arr = new int[len_arr1 * len_arr2];
  size_t new_arr_index{0};
  for (size_t i{0}; i < len_arr2; i++) {
    for (size_t j{0}; j < len_arr1; j++) {
      new_arr[new_arr_index++] = arr2[i] * arr1[j];
    }
  }
  return new_arr;
}

int main() {
  int arr1[] = {1, 2, 3, 4, 5};
  int arr2[] = {10, 20, 30};
  int* new_arr = apply_all(arr1, 5, arr2, 3);
  std::cout<<"[ ";
  for(size_t i{0}; i < 15; i++) {
      std::cout<<new_arr[i]<< " ";
  }
  std::cout << "]" << std::endl;
  delete [] new_arr;
}
