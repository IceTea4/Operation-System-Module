#include <pthread.h>
#include <stdio.h>
/* sia f-ja vykdys sukurta gija  */
void *inc_x(void *x_void_ptr){
   /* didinti  x iki 100 */
   int *x_ptr = (int *)x_void_ptr;
   while(++(*x_ptr) < 100);
   printf("x padidintas \n");
   /* f-ja turi kazka grazinti- pvz NULL  */
   return NULL;
}
int main(){
   pthread_t inc_x_thread; /* tai kintamasis suristas su sukuriama gija  */
   int x,y;
   printf( "(C) 2013 Nijole Sarafiniene, %s\n", __FILE__ );
   x = 0, y = 0;
   /* pradines  x ir y reiksmes */
   printf("x: %d, y: %d\n", x, y);
   /* sukuriama gija, kuri vykdys  inc_x(&x) */
   if(pthread_create(&inc_x_thread, NULL, inc_x, &x)) {
      fprintf(stderr, "Klaida sukuriant gija \n");
      return 1;
   }
   /* didinamas  y iki 100 0-neje --pagrindineje---gijoje */
   while(++y < 100);
   printf("y padidintas \n");
   /* sulaukt kol baigsis kita gija */
   if(pthread_join(inc_x_thread, NULL)) {
      fprintf(stderr, "Klaida sujungiant gijas \n");
      return 2;
   }
   /* rezultatu isvedimas - x yra  100 nes veike dvi gijos */
   printf("x: %d, y: %d\n", x, y);
   return 0;
}
