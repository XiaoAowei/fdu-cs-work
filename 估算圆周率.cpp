#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*
Sample random points (x, y) uniformly¾ùÔÈµÄ from the square [-1, 1] Ã— [-1, 1].
Let C be the unit circleµ¥Î»Ô² centered at (0, 0) with radius 1.
The probability that a sampled point lies inside C is exactly PI / 4.
ÔÚÕı·½ĞÎ[-1,1]*[-1,1]ÇøÓòËæ»ú²ÉÑù£¨x,y) cÊÇÔ­µãÎªÔ²ĞÄµÄµ¥Î»Ô²£¬Ëæ»úµãÂäÔÚÔ²ÄÚµÄ¸ÅÂÊÊÇËÄ·ÖÖ®pi 
Use Monte Carlo sampling with 'count' points to estimate the value of PI.
Return the estimated value.
Ê¹ÓÃÃÉÌØ¿¨Âå²ÉÑù£¬Ò»¹²Í¶count¸öµã¹ÀËãpi£¬·µ»Ø¹ÀËãÖµ 
*/
double sample_pi(int count) {
  // ¶¨Òåº¯Êı£¬²ÎÊı count ÊÇÈöµãµÄ×Ü´ÎÊı£¬·µ»Ø¹ÀËã³öµÄ ¦Ğ¡£
  int inCircle=0;
  // ¼ÆÊıÆ÷£¬¼ÇÂ¼ÂäÔÚÔ²ÄÚµÄµãµÄÊıÁ¿£¬³õÊ¼Îª 0
  double x,y;
  int i;
  for(i=0;i<count;i++)
  {
  	//count µÄÖµ	ÓÉµ÷ÓÃÕâ¸öº¯ÊıµÄÈË´«½øÀ´
  	x=(double)rand()/RAND_MAX*2.0-1.0;
  	y=(double)rand()/RAND_MAX*2.0-1.0;
  /*	Éú³É x ×ø±ê£º²½Öè	ËµÃ÷
rand() ÊÇ±ê×¼¿âº¯Êı£¬·µ»ØÒ»¸öËæ»úÕûÊı
·¶Î§£º0 µ½ RAND_MAX   RAND_MAX ÊÇ³£Á¿£¬Í¨³£ÊÇ 32767£¨²»Í¬Æ½Ì¨¿ÉÄÜ²»Í¬£©
rand() ¿ÉÄÜ·µ»Ø: 0, 1, 2, ..., 32767
µÚ 2 ²½£º(double)rand() / RAND_MAX
(double)rand() / RAND_MAX
(double)rand()£º°ÑÕûÊıÇ¿ÖÆ×ª³É double£¬±ÜÃâÕûÊı³ı·¨
/ RAND_MAX£º³ıÒÔ×î´óÖµ   ½á¹û·¶Î§£º
0 / 32767        = 0.0
16383 / 32767    ¡Ö 0.5
32767 / 32767    = 1.0
ËùÒÔÕâÒ»²½µÃµ½ 0.0 ~ 1.0 µÄËæ»úĞ¡Êı¡£
 ÎªÊ²Ã´±ØĞëĞ´ (double)
Èç¹ûĞ´³É rand() / RAND_MAX£¬Á½¸ö¶¼ÊÇÕûÊı£¬»á×öÕûÊı³ı·¨£¬½á¹ûÖ»ÓĞ 0 »ò 1£¬¾Í´íÁË¡£
µÚ 3 ²½£º* 2.0
... * 2.0
°Ñ 0.0 ~ 1.0 ·Å´óµ½ 0.0 ~ 2.0£º
0.0 * 2.0 = 0.0
0.5 * 2.0 = 1.0
1.0 * 2.0 = 2.0
µÚ 4 ²½£º- 1.0
... - 1.0
°Ñ 0.0 ~ 2.0 Æ½ÒÆµ½ -1.0 ~ 1.0£º  text
0.0 - 1.0 = -1.0
1.0 - 1.0 =  0.0
2.0 - 1.0 =  1.0
²Ù×÷	×÷ÓÃ
/ RAND_MAX	¹éÒ»»¯µ½ 0 ~ 1
* 2.0	·Å´óµ½ 0 ~ 2
- 1.0	Æ½ÒÆµ½ -1 ~ 1
ÏÈ¹éÒ»»¯ ¡ú ÔÙËõ·Å ¡ú ÔÙÆ½ÒÆ£¬ÕâÊÇ°ÑËæ»úÊıÓ³Éäµ½ÈÎÒâÇø¼ä [a, b] µÄÍ¨ÓÃÌ×Â·¡£

Í¨ÓÃ¹«Ê½£º

text
rand() / RAND_MAX * (b - a) + a
ÕâÀï a = -1, b = 1£¬ËùÒÔÊÇ * 2.0 - 1.0¡£

Ò»¾ä»°×Ü½á
ÕâĞĞ = °Ñ rand() µÄËæ»úÕûÊı£¬¾­¹ı¡°¹éÒ»»¯ ¡ú ·Å´ó ¡ú Æ½ÒÆ¡±£¬±ä³É -1.0 µ½ 1.0 Ö®¼äµÄËæ»úĞ¡Êı£¬×÷ÎªÈöµãµÄ×ø±ê¡£*/


  	if (x*x+y*y<=1.0)
  	{
  		inCircle ++;
	  }
	  //   if (x * x + y * y <= 1.0)
/*ÅĞ¶ÏÕâ¸öµãÊÇ·ñÔÚµ¥Î»Ô²ÄÚ£¨µ½Ô­µã¾àÀë ¡Ü 1£©¡£
x2 + y2 ¡Ü 1 ¡ú ÔÚÔ²ÄÚ
×¢ÒâÓÃ <= ¶ø·Ç <£¬±ß½çËãÔ²ÄÚ£¨Ó°Ïì¼«Ğ¡£©

      inCircle++;
Ô²ÄÚ¼ÆÊı¼ÓÒ»¡£
  double pi_estimate = 4.0 * inCircle / count;
°´¹«Ê½¹ÀËã ¦Ğ£º

text
¦Ğ ¡Ö 4 ¡Á (Ô²ÄÚµãÊı / ×ÜµãÊı)
×¢ÒâÕâÀï 4.0 * inCircle / count£º

4.0 ÊÇ double£¬ËùÒÔÕû¸öÔËËãÊÇ¸¡µãÔËËã

Èç¹ûĞ´³É 4 * inCircle / count£¬»áÏÈËãÕûÊı³ı·¨£¬½á¹û´íÎó

c
  return pi_estimate;
}
·µ»Ø¹ÀËãÖµ¡£

ÎªÊ²Ã´ÕâÑùÄÜ¹ÀËã ¦Ğ£¿
Á¿	Öµ
Õı·½ĞÎÃæ»ı	4
Ô²Ãæ»ı	¦Ğ
Ãæ»ı±È	¦Ğ / 4
µãÊı±È£¨½üËÆ£©	inCircle / count
µãÊıÔ½¶à£¬±ÈÀıÔ½½Ó½üÃæ»ı±È£¬¹ÀËãÔ½×¼¡£

Ğ¡Ï¸½Ú & ¿É¸Ä½øµã
1. count Îª 0 »á³ö´í

c
double pi_estimate = 4.0 * inCircle / count;  // count=0 ¡ú ³ıÒÔ0
¿ÉÒÔ¼Ó¸ö±£»¤£º

c
if (count <= 0) return 0.0;
2. RAND_MAX ×ª»»
RAND_MAX ±¾ÉíÊÇÕûÊı³£Á¿£¬(double)rand() / RAND_MAX ÖĞ RAND_MAX »á×Ô¶¯×ª³É double£¬Ã»ÎÊÌâ¡£

3. ¾«¶È

rand() µÄ·¶Î§ÓĞÏŞ£¨Í¨³£ 32767£©£¬µãÊıºÜ¶àÊ±Ëæ»úĞÔ²»¹»ºÃ

Ïë¸ü×¼¿ÉÒÔÓÃ random() »ò¸üºÃµÄËæ»úÊıÉú³ÉÆ÷

4. ½á¹û²¨¶¯

Ã¿´ÎÔËĞĞ½á¹û¶¼²»Í¬£¬ÕâÊÇËæ»úËã·¨µÄÕı³£ÏÖÏó

count Ô½´ó£¬½á¹ûÔ½ÎÈ¶¨¡¢Ô½½Ó½ü 3.14159...

²âÊÔÊ¾Àı
c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));          // ÓÃÊ±¼ä×öËæ»úÖÖ×Ó
    printf("%f\n", sample_pi(1000000));  // Èö 100 Íò¸öµã
    return 0;
}
µäĞÍÊä³ö£º3.141592 ¸½½üµÄÊı£¬±ÈÈç 3.141356¡¢3.142508 µÈ¡£

Ò»¾ä»°×Ü½á
Õâ¶Î´úÂëÔÚÒ»¸ö 2¡Á2 µÄÕı·½ĞÎÀïËæ»úÈöµã£¬Í³¼ÆÂäÔÚµ¥Î»Ô²ÄÚµÄ±ÈÀı£¬³ËÒÔ 4 À´¹ÀËã ¦Ğ¡ª¡ªÕâ¾ÍÊÇÃÉÌØ¿¨Âå·½·¨£¬µãÔ½¶àÔ½×¼¡£

countÊÇÉ¶
count ÔÚÕâÀïÊÇº¯ÊıµÄÒ»¸ö²ÎÊı£¬±íÊ¾ÒªÈö¶àÉÙ¸öËæ»úµã£¨Ò²¾ÍÊÇÑ­»·¶àÉÙ´Î£©¡£

²ğ¿ª¿´
c
double sample_pi(int count)
²¿·Ö	º¬Òå
int	²ÎÊıÀàĞÍ£ºÕûÊı
count	²ÎÊıÃû£¬¿ÉÒÔ×Ô¼ºÆğ£¨½Ğ n¡¢times¡¢num ¶¼ĞĞ£©
count µÄÖµ	ÓÉµ÷ÓÃÕâ¸öº¯ÊıµÄÈË´«½øÀ´
ËüÔÚº¯ÊıÀïµÄ×÷ÓÃ
c
for (i = 0; i < count; i++)
ÕâĞĞ¾ÍÊÇ£ºÑ­»·Ö´ĞĞ count ´Î£¬Ã¿´ÎÈöÒ»¸öµã¡£

count = 1000 ¡ú Èö 1000 ¸öµã

count = 1000000 ¡ú Èö 100 Íò¸öµã

ÒÔ¼°×îºó£º

c
double pi_estimate = 4.0 * inCircle / count;
ÓÃ count µ±·ÖÄ¸£¬Ëã¡°Ô²ÄÚµãÊıÕ¼×ÜµãÊıµÄ±ÈÀı¡±¡£

Ë­¸øËü¸³Öµ£¿¡ª¡ªµ÷ÓÃµÄÊ±ºò´«
c
int main() {
    double pi = sample_pi(1000000);
    //                     ¡ü
    //              ÕâÀï¾Í°Ñ count Éè³ÉÁË 1000000
    printf("%f\n", pi);
}
ËùÒÔ£º

text
sample_pi(1000000)  ¡ú  count = 1000000
sample_pi(100)      ¡ú  count = 100
sample_pi(50)       ¡ú  count = 50
Àà±ÈÀí½â
°Ñº¯ÊıÏë³ÉÒ»Ì¨»úÆ÷£º

text
        ©°©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©´
ÊäÈë ¡ú  ©¦  sample_pi  ©¦ ¡ú Êä³ö ¦Ğ µÄ¹ÀËãÖµ
 count  ©¸©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¤©¼
ÊäÈë£ºcount£¨Èö¼¸¸öµã£©

Êä³ö£º¹ÀËãµÄ ¦Ğ

Äã¸ø»úÆ÷Î¹µÄ count Ô½´ó£¬ËüËãµÃÔ½×¼£¬µ«»¨µÄÊ±¼äÒ²Ô½¶à¡£

ÎªÊ²Ã´ count Ô½´óÔ½×¼£¿
ÃÉÌØ¿¨Âå·½·¨¿¿´óÊı¶¨ÂÉ£º

count	½á¹û²¨¶¯
10	ºÜ²»×¼£¬¿ÉÄÜËã³ö 2.8 »ò 3.6
1000	²î²»¶à£¬´ó¸Å 3.1 ×óÓÒ
1000000	ºÜ½Ó½ü 3.14159
µãÊıÔ½¶à£¬Ô²ÄÚµãÊı/×ÜµãÊı Ô½½Ó½üÕæÊµµÄÃæ»ı±È ¦Ğ/4¡£

Ò»¾ä»°×Ü½á
count = µ÷ÓÃÕß´«½øÀ´µÄ¡°Èöµã´ÎÊı¡±£¬¾ö¶¨ÁË¹ÀËãµÄ¾«¶ÈºÍ¹¤×÷Á¿£ºÔ½´óÔ½×¼¡¢Ô½Âı£¬Ô½Ğ¡Ô½¿ì¡¢Ô½²»×¼¡£


  }
  double pi_estimate=4.0*inCircle/count;
  return pi_estimate;
}

/**
 * @brief Calculates the confidence interval for a PI estimate given the number
 * of samples and an acceptable failure probability.
 * @param count The total number of Monte Carlo samples.
 * @param failure_prob The maximum acceptable probability that the test will
 * fail due to randomness (e.g., 1e-9).
 * @param lower_bound A pointer to store the calculated acceptable lower bound.
 * @param upper_bound A pointer to store the calculated acceptable upper bound.
 */
void calculate_pi_bounds(long long count, double failure_prob,
                         double* lower_bound, double* upper_bound) {
  if (count <= 0 || failure_prob <= 0.0 || failure_prob >= 1.0) {
    *lower_bound = 1.0;
    *upper_bound = 0.0;
    /*ÏÂ½çÉèÖÃ1.0£¬ÉÏ½çÉèÖÃ0.0*/ 
    return;
  }

  const double true_p = M_PI / 4.0;/*ÀíÂÛÕæÊµ¸ÅÂÊ*/
   
  const double mu = count * true_p;

  const double delta = sqrt((3.0 * log(2.0 / failure_prob)) / mu);

  *lower_bound = M_PI * (1.0 - delta);
  *upper_bound = M_PI * (1.0 + delta);
}

/**
 * @brief Runs a standalone PI estimation test case and verifies the result.
 *
 * @param test_name The name of the test case.
 * @param count The total number of Monte Carlo samples.
 * @param failure_prob The maximum acceptable probability that the test will
 * fail due to randomness.
 */
void run_pi_test_case(const char* test_name, long long count,
                      double failure_prob) {
  printf("--- Running Test Case: %s ---\n", test_name);

  double lower_bound, upper_bound;
  calculate_pi_bounds(count, failure_prob, &lower_bound, &upper_bound);

  printf("Number of samples: %lld\n", count);
  printf("Desired max failure probability: %e\n", failure_prob);
  printf("Calculated acceptable range: [%.8f, %.8f] (Width: %.8f)\n",
         lower_bound, upper_bound, upper_bound - lower_bound);

  double pi_estimate = sample_pi((int)count);
  printf("PI estimate from simulation: %.8f\n", pi_estimate);

  assert(pi_estimate >= lower_bound && "Estimate was too low.");
  assert(pi_estimate <= upper_bound && "Estimate was too high.");

  printf(
      "Passed: The estimate is within the calculated high-confidence "
      "bounds.\n\n");
}

void test_all_pi_scenarios() {
  printf("=============================================\n");
  printf("Running All Pi Estimation Test Scenarios\n");
  printf("=============================================\n\n");

  run_pi_test_case("High Precision", 5000000, 1e-9);

  run_pi_test_case("Medium Precision", 500000, 1e-7);

  run_pi_test_case("Quick / Low Precision", 50000, 0.01);  // 1% çš„å¤±è´¥æ¦‚ç‡
}

int main() {
  test_all_pi_scenarios();
  printf("\nAll tests passed!\n");
  return 0;
}
