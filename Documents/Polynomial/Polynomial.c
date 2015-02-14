/*
 * Polynomial.h
 *
 *  A proper Polynomial object P is required to satisfy the following
 *  conditions:
 *
 *    1.  P.Coeff points to an array of dimension P.Degree + 1.
 *    2.  P.Coeff[k] is the coefficient of x^k , for k = 0 to P.Degree.
 */

#include "Polynomial.h"
#include <stdlib.h>
#include <math.h>

void cleanUp(Polynomial* const Target);

/**
 * Initializes *P as described below.
 *
 * Pre:  P points to an uninitialized Polynomial object,
 *       C != NULL,
 *       C[i] initialized for i = 0:D
 * Post: if true is returned:
 *          P->Degree == D,
 *          P->Coeff != C (array is duplicated, not linked),
 *          P->Coeff[i] == C[i] for i = 0:D
 * Returns: false if *P cannot be correctly initialized, true otherwise
 */
bool Polynomial_Set(Polynomial* const P, const uint8_t D, const int32_t* const C)
{
	if (D < 1)
	{
		return false;
	}
	else
	{
		P->Degree = D;
		P->Coeff = malloc((D + 1) * sizeof(int32_t));
		
		for (int i = 0; i <= D; i++)
		{
			P->Coeff[i] = C[i];
		}
		return true;
	}
}

/**
 * Initializes *Target from *Source as described below.
 *
 * Pre:  Target points to a proper Polynomial object,
 *       Source points to a proper Polynomial object
 * Post: if true is returned:
 *          Target->Degree == Source->Degree,
 *          Target->Coeff != Source->Coeff,
 *          Target->Coeff[i] == Source->Coeff[i] for i = 0:Source->Degree
 * Returns: false if *Target cannot be correctly initialized, true otherwise
 */
bool Polynomial_Copy(Polynomial* const Target, const Polynomial* const Source)
{
	return Polynomial_Set(Target, Source->Degree, Source->Coeff);
}

/**
 * Compares two polynomials.
 *
 * Pre:  Left points to a proper Polynomial object,
 *       Right points to a proper Polynomial object
 * Returns: true if Left and Right have the same coefficients, false otherwise
 */
bool Polynomial_Equals(const Polynomial* const Left, const Polynomial* const Right)
{
	if (Left->Degree == Right->Degree)
	{
		for (int i = 0; i <= Left->Degree; i ++)
		{
			if (Left->Coeff[i] != Right->Coeff[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;	
}

/**
 * Computes value of polynomial at X.
 *
 * Pre:  P points to a proper Polynomial object
 * Returns: value of P(X); 0 if cannot be evaluated
 */
int32_t Polynomial_EvaluateAt(const Polynomial* const P, const int32_t X)
{
	int sum = 0;
		for (int i = 0; i <= P->Degree; i++)
		{
			
			sum += P->Coeff[i] * (X * i);
		}
	return sum;
}

/**
 * Initializes *Scaled to represent K times *Source
 *
 * Pre:  Scaled points to a proper Polynomial object,
 *       Source points to a proper Polynomial object,
 *       Source != Target
 * Post: if true is returned:
 *          Scaled->Degree == Source->Degree,
 *          Scaled->Coeff  != Source->Coeff,
 *          Scaled->Coeff[i] == K * Source->Coeff[i] for i = 0:Scaled->Degree
 * Returns: false if *Scaled cannot be correctly initialized, true otherwise
 */
bool Polynomial_Scale(Polynomial* const Scaled, const Polynomial* const Source, const int32_t K)
{
	bool init = Polynomial_Set(Scaled, Source->Degree, Source->Coeff);
	if (init)
	{
		for (int i = 0; i <= Scaled->Degree; i++)
		{
			Scaled->Coeff[i] = Source->Coeff[i] * K;
		}
		return true;
	}
	return false;
}

/**
 * Initializes *Sum to equal *Left + *Right.
 *
 * Pre:  Sum points to a proper Polynomial object,
 *       Left points to a proper Polynomial object,
 *       Right points to a proper Polynomial object,
 *       Sum != Left,
 *       Sum != Right
 * Post: if true is returned:
 *          Sum->Degree == max(Left->Degree, Right->Degree),
 *          Sum->Coeff[i] == Left->Coeff[i] + Right->Coeff[i] 
 *             with proper allowance for the case that 
 *             Left->Degree != Right->Degree
 * Returns: false if *Sum cannot be correctly initialized, true otherwise
 */
bool Polynomial_Add(Polynomial* const Sum, const Polynomial* const Left, const Polynomial* const Right)
{
	int lMax = Left->Degree;
	int rMax = Right->Degree;
	bool init = false;
	if (lMax >= rMax)
	{
		init = Polynomial_Set(Sum, Left->Degree, Left->Coeff);
		if (init)
		{
			for (int i = 0; i <= Right->Degree; i++)
			{
				Sum->Coeff[i] = Left->Coeff[i] + Right->Coeff[i];
			}
			cleanUp(Sum);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		init = Polynomial_Set(Sum, Right->Degree, Right->Coeff);
		if (init)
		{
			for (int i = 0; i <= Left->Degree; i++)
			{
				Sum->Coeff[i] = Left->Coeff[i] + Right->Coeff[i];
			}
			cleanUp(Sum);
			return true;
		}
		else
		{
			return false;
		}
	}
	
}


/**
 * Initializes *Diff to equal *Left - *Right.
 *
 * Pre:  Diff points to a proper Polynomial object,
 *       Left points to a proper Polynomial object,
 *       Right points to a proper Polynomial object,
 *       Diff != Left,
 *       Diff != Right
 * Post: if true is returned:
 *          Diff->Degree is set correctly,
 *          Diff->Coeff[i] == Left->Coeff[i] - Right->Coeff[i] 
 *             with proper allowance for the case that 
 *             Left->Degree != Right->Degree
 * Returns: false if *Diff cannot be correctly initialized, true otherwise
 */
bool Polynomial_Subtract(Polynomial* const Diff, const Polynomial* const Left, const Polynomial* const Right)
{
	int lMax = Left->Degree;
	int rMax = Right->Degree;
	bool init = false;
	if (lMax >= rMax)
	{
		init = Polynomial_Set(Diff, Left->Degree, Left->Coeff);
		if (init)
		{
			for (int i = 0; i <= Right->Degree; i++)
			{
				Diff->Coeff[i] = Left->Coeff[i] - Right->Coeff[i];
			}
			cleanUp(Diff);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		init = Polynomial_Set(Diff, Right->Degree, Right->Coeff);
		if (init)
		{
			for (int i = 0; i <= Left->Degree; i++)
			{
				Diff->Coeff[i] = Left->Coeff[i] - Right->Coeff[i];
			}
			cleanUp(Diff);
			return true;
		}
		else
		{
			return false;
		}
	}
}

void cleanUp(Polynomial* const Target)
{
	int count = 0;
	for (int i = 0; i <= Target->Degree; i++)
	{
		if (Target->Coeff[i] == 0)
		{
			count++;
			for (int j = i; j < Target->Degree; j++)
			{
				Target->Coeff[j] = Target->Coeff[j + 1];
			}
			Target->Degree--;
		}
	}
	Target->Coeff = realloc(Target->Coeff, Target->Degree * sizeof(int32_t));
}

/**
 * Initializes *Diff to equal *Left - *Right.
 *
 * Pre:  Prod points to a proper Polynomial object,
 *       Left points to a proper Polynomial object,
 *       Right points to a proper Polynomial object,
 *       Prod != Left,
 *       Prod != Right
 * Post: if true is returned:
 *          Prod->Degree is set correctly,
 *          Prod->Coeff[i] == correct coefficient of x^i in Left * Right
 * Returns: false if *Prod cannot be correctly initialized, true otherwise
 */
bool Polynomial_Multiply(Polynomial* const Prod, const Polynomial* const Left, const Polynomial* const Right)
{
	int lMax = Left->Degree;
	int rMax = Right->Degree;
	bool init = false;
	if (lMax >= rMax)
	{
		init = Polynomial_Set(Prod, Left->Degree, Left->Coeff);
		if (init)
		{
			for (int i = 0; i <= Right->Degree; i++)
			{
				Prod->Coeff[i] = Left->Coeff[i] * Right->Coeff[i];
			}
			
		}
		else
		{
			return false;
		}
	}
	else
	{
		init = Polynomial_Set(Prod, Right->Degree, Right->Coeff);
		if (init)
		{
			for (int i = 0; i <= Left->Degree; i++)
			{
				Prod->Coeff[i] = Left->Coeff[i] * Right->Coeff[i];
			}
			
		}
		else
		{
			return false;
		}
	}
}

/**
 * Computes the first derivative of Source.
 *
 * Pre:  Target points to a proper Polynomial object,
 *       Source points to a proper Polynomial object,
 *       Target != Source
 * Post: Target->Degree is set correctly
 *       Target->Coeff[i] == i-th coefficient of Source'
 *
 * Returns: false if Source' cannot be correctly initialized, true otherwise
 */
bool Polynomial_Differentiate(Polynomial* const Target, const Polynomial* const Source)
{
	bool init = Polynomial_Set(Target, Source->Degree, Source->Coeff);
	if (init)
	{		
		for (int i = 0; i <= Target->Degree; i++)
		{
			Target->Coeff[i] = Target->Coeff[i] * i;
		}
		Target->Coeff = realloc(Target->Coeff, Target->Degree * sizeof(int32_t));
		return true;
	}
}

/**
 * Reset P to represent zero polynomial.
 *
 * Pre:  P points to a Polynomial object
 * Post: P->Degree == 0
 *       P->Coeff is set appropriately
 */
bool Polynomial_Zero(Polynomial* const P)
{
	P->Degree = 0;
	P->Coeff = realloc(P->Coeff, sizeof(int32_t));
	P->Coeff[0] = 0;
	return true;
}

