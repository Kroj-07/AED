/*procedimiento sift_down(A, n, i)
mientras verdadero hacer
m ← i
si 2i+1 < n y A[2i+1] < A[m] entonces m ← 2i+1
si 2i+2 < n y A[2i+2] < A[m] entonces m ← 2i+2
si m = i entonces retornar
intercambiar A[i], A[m]
i ← m
*/

#pragma once
#include <bits/stdc++.h>


template <typename T, typename Cmp