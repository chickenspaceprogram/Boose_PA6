#include <stdlib.h>
#include <time.h>

/**
* Function name: seed_rand
* Date created: 2024-09-25
* Date last modified: 2024-09-25
* Description: Seeds the random number generator with the current time.
* Inputs: none
* Outputs: none
*/
void seed_rand(void);

/**
 * Function name: randint
 * Date created: 2024-11-03
 * Date last modified: 2024-11-03
 * Description: Returns a random number between `min` and `max`, inclusive.
 * Inputs: 
 * `min` : The minimum number to be returned.
 * `max` : The maximum number to be returned.
 * Outputs: The random number.
 */
int randint(int min, int max);