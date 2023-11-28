/* code generated with arith_eq_gen.js
* equation: s*s-x1-x2-x3-p*q1+p*offset
* 
* p=0xfffffffffffffffffffffffffffffffffffffffffffffffffffffffefffffc2f
* offset=0x40000000000000000000000000000000000000000000000000000000000000000
*/

#include <stdint.h>
#include "definitions.hpp"
#include "sm/pols_generated/commit_pols.hpp"
#include "goldilocks_base_field.hpp"

USING_PROVER_FORK_NAMESPACE;

Goldilocks::Element eq3 (Goldilocks &fr, ArithCommitPols &p, uint64_t step, uint64_t _o)
{
	switch(step) {
		case 0: 
		return (
		(p.s[0][_o]   * p.s[0][_o]   - 0xfc2f   * p.q1[0][_o] )
		 - p.x1[0][_o]  - p.x2[0][_o]  - p.x3[0][_o] );

		case 1: 
		return (
		(p.s[0][_o]   * p.s[1][_o]   - 0xfc2f   * p.q1[1][_o] ) +
		(p.s[1][_o]   * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[1][_o]  - p.x2[1][_o]  - p.x3[1][_o] );

		case 2: 
		return (
		(p.s[0][_o]   * p.s[2][_o]   - 0xfc2f   * p.q1[2][_o] ) +
		(p.s[1][_o]   * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[2][_o]   * p.s[0][_o]   - 0xfffe   * p.q1[0][_o] )
		 - p.x1[2][_o]  - p.x2[2][_o]  - p.x3[2][_o] );

		case 3: 
		return (
		(p.s[0][_o]   * p.s[3][_o]   - 0xfc2f   * p.q1[3][_o] ) +
		(p.s[1][_o]   * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[2][_o]   * p.s[1][_o]   - 0xfffe   * p.q1[1][_o] ) +
		(p.s[3][_o]   * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[3][_o]  - p.x2[3][_o]  - p.x3[3][_o] );

		case 4: 
		return (
		(p.s[0][_o]   * p.s[4][_o]   - 0xfc2f   * p.q1[4][_o] ) +
		(p.s[1][_o]   * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[2][_o]   * p.s[2][_o]   - 0xfffe   * p.q1[2][_o] ) +
		(p.s[3][_o]   * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[4][_o]   * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[4][_o]  - p.x2[4][_o]  - p.x3[4][_o] );

		case 5: 
		return (
		(p.s[0][_o]   * p.s[5][_o]   - 0xfc2f   * p.q1[5][_o] ) +
		(p.s[1][_o]   * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[2][_o]   * p.s[3][_o]   - 0xfffe   * p.q1[3][_o] ) +
		(p.s[3][_o]   * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[4][_o]   * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[5][_o]   * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[5][_o]  - p.x2[5][_o]  - p.x3[5][_o] );

		case 6: 
		return (
		(p.s[0][_o]   * p.s[6][_o]   - 0xfc2f   * p.q1[6][_o] ) +
		(p.s[1][_o]   * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[2][_o]   * p.s[4][_o]   - 0xfffe   * p.q1[4][_o] ) +
		(p.s[3][_o]   * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[4][_o]   * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[5][_o]   * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[6][_o]   * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[6][_o]  - p.x2[6][_o]  - p.x3[6][_o] );

		case 7: 
		return (
		(p.s[0][_o]   * p.s[7][_o]   - 0xfc2f   * p.q1[7][_o] ) +
		(p.s[1][_o]   * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[2][_o]   * p.s[5][_o]   - 0xfffe   * p.q1[5][_o] ) +
		(p.s[3][_o]   * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[4][_o]   * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[5][_o]   * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[6][_o]   * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[7][_o]   * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[7][_o]  - p.x2[7][_o]  - p.x3[7][_o] );

		case 8: 
		return (
		(p.s[0][_o]   * p.s[8][_o]   - 0xfc2f   * p.q1[8][_o] ) +
		(p.s[1][_o]   * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[2][_o]   * p.s[6][_o]   - 0xfffe   * p.q1[6][_o] ) +
		(p.s[3][_o]   * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[4][_o]   * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[5][_o]   * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[6][_o]   * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[7][_o]   * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[8][_o]   * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[8][_o]  - p.x2[8][_o]  - p.x3[8][_o] );

		case 9: 
		return (
		(p.s[0][_o]   * p.s[9][_o]   - 0xfc2f   * p.q1[9][_o] ) +
		(p.s[1][_o]   * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[2][_o]   * p.s[7][_o]   - 0xfffe   * p.q1[7][_o] ) +
		(p.s[3][_o]   * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[4][_o]   * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[5][_o]   * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[6][_o]   * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[7][_o]   * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[8][_o]   * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[9][_o]   * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[9][_o]  - p.x2[9][_o]  - p.x3[9][_o] );

		case 10: 
		return (
		(p.s[0][_o]   * p.s[10][_o]  - 0xfc2f   * p.q1[10][_o]) +
		(p.s[1][_o]   * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[2][_o]   * p.s[8][_o]   - 0xfffe   * p.q1[8][_o] ) +
		(p.s[3][_o]   * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[4][_o]   * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[5][_o]   * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[6][_o]   * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[7][_o]   * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[8][_o]   * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[9][_o]   * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[10][_o]  * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[10][_o] - p.x2[10][_o] - p.x3[10][_o]);

		case 11: 
		return (
		(p.s[0][_o]   * p.s[11][_o]  - 0xfc2f   * p.q1[11][_o]) +
		(p.s[1][_o]   * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[2][_o]   * p.s[9][_o]   - 0xfffe   * p.q1[9][_o] ) +
		(p.s[3][_o]   * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[4][_o]   * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[5][_o]   * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[6][_o]   * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[7][_o]   * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[8][_o]   * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[9][_o]   * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[10][_o]  * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[11][_o]  * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[11][_o] - p.x2[11][_o] - p.x3[11][_o]);

		case 12: 
		return (
		(p.s[0][_o]   * p.s[12][_o]  - 0xfc2f   * p.q1[12][_o]) +
		(p.s[1][_o]   * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[2][_o]   * p.s[10][_o]  - 0xfffe   * p.q1[10][_o]) +
		(p.s[3][_o]   * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[4][_o]   * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[5][_o]   * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[6][_o]   * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[7][_o]   * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[8][_o]   * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[9][_o]   * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[10][_o]  * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[11][_o]  * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[12][_o]  * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[12][_o] - p.x2[12][_o] - p.x3[12][_o]);

		case 13: 
		return (
		(p.s[0][_o]   * p.s[13][_o]  - 0xfc2f   * p.q1[13][_o]) +
		(p.s[1][_o]   * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[2][_o]   * p.s[11][_o]  - 0xfffe   * p.q1[11][_o]) +
		(p.s[3][_o]   * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[4][_o]   * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[5][_o]   * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[6][_o]   * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[7][_o]   * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[8][_o]   * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[9][_o]   * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[10][_o]  * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[11][_o]  * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[12][_o]  * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[13][_o]  * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[13][_o] - p.x2[13][_o] - p.x3[13][_o]);

		case 14: 
		return (
		(p.s[0][_o]   * p.s[14][_o]  - 0xfc2f   * p.q1[14][_o]) +
		(p.s[1][_o]   * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[2][_o]   * p.s[12][_o]  - 0xfffe   * p.q1[12][_o]) +
		(p.s[3][_o]   * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[4][_o]   * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[5][_o]   * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[6][_o]   * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[7][_o]   * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[8][_o]   * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[9][_o]   * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[10][_o]  * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[11][_o]  * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[12][_o]  * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[13][_o]  * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[14][_o]  * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[14][_o] - p.x2[14][_o] - p.x3[14][_o]);

		case 15: 
		return (
		(p.s[0][_o]   * p.s[15][_o]  - 0xfc2f   * p.q1[15][_o]) +
		(p.s[1][_o]   * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[2][_o]   * p.s[13][_o]  - 0xfffe   * p.q1[13][_o]) +
		(p.s[3][_o]   * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[4][_o]   * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[5][_o]   * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[6][_o]   * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[7][_o]   * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[8][_o]   * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[9][_o]   * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[10][_o]  * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[11][_o]  * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[12][_o]  * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[13][_o]  * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[14][_o]  * p.s[1][_o]   - 0xffff   * p.q1[1][_o] ) +
		(p.s[15][_o]  * p.s[0][_o]   - 0xffff   * p.q1[0][_o] )
		 - p.x1[15][_o] - p.x2[15][_o] - p.x3[15][_o]);

		case 16: 
		return (
		(p.s[1][_o]   * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[2][_o]   * p.s[14][_o]  - 0xfffe   * p.q1[14][_o]) +
		(p.s[3][_o]   * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[4][_o]   * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[5][_o]   * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[6][_o]   * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[7][_o]   * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[8][_o]   * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[9][_o]   * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[10][_o]  * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[11][_o]  * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[12][_o]  * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[13][_o]  * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[14][_o]  * p.s[2][_o]   - 0xffff   * p.q1[2][_o] ) +
		(p.s[15][_o]  * p.s[1][_o]   - 0xffff   * p.q1[1][_o] )
		    + 0x3f0bc );

		case 17: 
		return (
		(p.s[2][_o]   * p.s[15][_o]  - 0xfffe   * p.q1[15][_o]) +
		(p.s[3][_o]   * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[4][_o]   * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[5][_o]   * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[6][_o]   * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[7][_o]   * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[8][_o]   * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[9][_o]   * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[10][_o]  * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[11][_o]  * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[12][_o]  * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[13][_o]  * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[14][_o]  * p.s[3][_o]   - 0xffff   * p.q1[3][_o] ) +
		(p.s[15][_o]  * p.s[2][_o]   - 0xffff   * p.q1[2][_o] )
		    + 0x3fffc );

		case 18: 
		return (
		(p.s[3][_o]   * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[4][_o]   * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[5][_o]   * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[6][_o]   * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[7][_o]   * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[8][_o]   * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[9][_o]   * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[10][_o]  * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[11][_o]  * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[12][_o]  * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[13][_o]  * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[14][_o]  * p.s[4][_o]   - 0xffff   * p.q1[4][_o] ) +
		(p.s[15][_o]  * p.s[3][_o]   - 0xffff   * p.q1[3][_o] )
		    + 0x3fff8 );

		case 19: 
		return (
		(p.s[4][_o]   * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[5][_o]   * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[6][_o]   * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[7][_o]   * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[8][_o]   * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[9][_o]   * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[10][_o]  * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[11][_o]  * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[12][_o]  * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[13][_o]  * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[14][_o]  * p.s[5][_o]   - 0xffff   * p.q1[5][_o] ) +
		(p.s[15][_o]  * p.s[4][_o]   - 0xffff   * p.q1[4][_o] )
		    + 0x3fffc );

		case 20: 
		return (
		(p.s[5][_o]   * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[6][_o]   * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[7][_o]   * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[8][_o]   * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[9][_o]   * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[10][_o]  * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[11][_o]  * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[12][_o]  * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[13][_o]  * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[14][_o]  * p.s[6][_o]   - 0xffff   * p.q1[6][_o] ) +
		(p.s[15][_o]  * p.s[5][_o]   - 0xffff   * p.q1[5][_o] )
		    + 0x3fffc );

		case 21: 
		return (
		(p.s[6][_o]   * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[7][_o]   * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[8][_o]   * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[9][_o]   * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[10][_o]  * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[11][_o]  * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[12][_o]  * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[13][_o]  * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[14][_o]  * p.s[7][_o]   - 0xffff   * p.q1[7][_o] ) +
		(p.s[15][_o]  * p.s[6][_o]   - 0xffff   * p.q1[6][_o] )
		    + 0x3fffc );

		case 22: 
		return (
		(p.s[7][_o]   * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[8][_o]   * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[9][_o]   * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[10][_o]  * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[11][_o]  * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[12][_o]  * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[13][_o]  * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[14][_o]  * p.s[8][_o]   - 0xffff   * p.q1[8][_o] ) +
		(p.s[15][_o]  * p.s[7][_o]   - 0xffff   * p.q1[7][_o] )
		    + 0x3fffc );

		case 23: 
		return (
		(p.s[8][_o]   * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[9][_o]   * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[10][_o]  * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[11][_o]  * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[12][_o]  * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[13][_o]  * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[14][_o]  * p.s[9][_o]   - 0xffff   * p.q1[9][_o] ) +
		(p.s[15][_o]  * p.s[8][_o]   - 0xffff   * p.q1[8][_o] )
		    + 0x3fffc );

		case 24: 
		return (
		(p.s[9][_o]   * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[10][_o]  * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[11][_o]  * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[12][_o]  * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[13][_o]  * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[14][_o]  * p.s[10][_o]  - 0xffff   * p.q1[10][_o]) +
		(p.s[15][_o]  * p.s[9][_o]   - 0xffff   * p.q1[9][_o] )
		    + 0x3fffc );

		case 25: 
		return (
		(p.s[10][_o]  * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[11][_o]  * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[12][_o]  * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[13][_o]  * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[14][_o]  * p.s[11][_o]  - 0xffff   * p.q1[11][_o]) +
		(p.s[15][_o]  * p.s[10][_o]  - 0xffff   * p.q1[10][_o])
		    + 0x3fffc );

		case 26: 
		return (
		(p.s[11][_o]  * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[12][_o]  * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[13][_o]  * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[14][_o]  * p.s[12][_o]  - 0xffff   * p.q1[12][_o]) +
		(p.s[15][_o]  * p.s[11][_o]  - 0xffff   * p.q1[11][_o])
		    + 0x3fffc );

		case 27: 
		return (
		(p.s[12][_o]  * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[13][_o]  * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[14][_o]  * p.s[13][_o]  - 0xffff   * p.q1[13][_o]) +
		(p.s[15][_o]  * p.s[12][_o]  - 0xffff   * p.q1[12][_o])
		    + 0x3fffc );

		case 28: 
		return (
		(p.s[13][_o]  * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[14][_o]  * p.s[14][_o]  - 0xffff   * p.q1[14][_o]) +
		(p.s[15][_o]  * p.s[13][_o]  - 0xffff   * p.q1[13][_o])
		    + 0x3fffc );

		case 29: 
		return (
		(p.s[14][_o]  * p.s[15][_o]  - 0xffff   * p.q1[15][_o]) +
		(p.s[15][_o]  * p.s[14][_o]  - 0xffff   * p.q1[14][_o])
		    + 0x3fffc );

		case 30: 
		return (
		(p.s[15][_o]  * p.s[15][_o]  - 0xffff   * p.q1[15][_o])
		    + 0x3fffc );

		case 31: 
		return fr.fromU64(0x3fffc);
	}
	return fr.zero();
}
