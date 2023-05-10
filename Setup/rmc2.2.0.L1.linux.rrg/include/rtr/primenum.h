/*
//
//|---------------------------------------------------------------
//|                Copyright (C) 1997 Reuters,                  --
//|                                                             --
//|         1400 Kensington Road, Oak Brook, IL. 60521          --
//|                                                             --
//| All rights reserved. Duplication or distribution prohibited --
//|---------------------------------------------------------------
//
//  author:        Robert Bonaguro
//  created:       May 9, 1997
//  version:       1.0
//
//  description:
//		Find Prime Numbers
//
//	keywords:
//		Prime Number, Prime
//
//	int rtr_find_prime_num(number)
//		- Find the first prime number which is greater than or equal
//		- to the input number. If input is less than or equal to 1
//		- then routine returns prime number 2.
//
*/


#ifndef __rtr_primenum_h
#define __rtr_primenum_h

#if 1
extern int rtr_find_prime_num(int number);
#else
extern int rtr_find_prime_num();
#endif

#endif
