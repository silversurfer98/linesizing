# a primitive routine to calculate the friction factor 
1. uses 3 point solver --- converges very quickly for colebrook
2. does not contains my math functions -- if ur are integrating mln(float x) the coeff in class and colebrook should be activated a beforehand
3. checked results using standard g as 9.80665   
4. pushed code to production didnt check - memory leak, it shouldn't xD 

5. This site del P is wrong
- [site 1](https://www.tribology-abc.com/calculators/pipeflow_fluid.htm)

6. this site everthing id correct but rounded off
- [site 2](http://www.druckverlust.de/Online-Rechner/dp.php)