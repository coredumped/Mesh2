#include<stdio.h>
#include<conio.h>

#define abs(x) (x < 0)? -x:x

main(){
 char cont;
 int a, b, d1, d2, r, div;
 do{
  clrscr();
  printf("Entre el dividendo a=");
  scanf("%d", &a);
  fflush(stdin);
  printf("Entre el divisor b=");
  scanf("%d", &b);
  fflush(stdin);
  if(b != 0){
   d1 = abs(a);
   d2 = abs(b);
   div = 0;
   r = d1;
   while(!(r < d2)){
    div = div + 1;
    r = r - d2;
   }
   if((a > 0 && b < 0) || (a < 0 && b > 0)) div = -div;
   printf("\nEl cociente es: %d\n", div);
   if(r != 0) printf("La divisi¢n no es exacta, el residuo es: %d\n", r);
   else printf("La divisi¢n fue exacta!!\n");
  }
  else printf("\n\nError - No se puede dividir por cero!!");
  printf("\n\nDesea continuar(s/n)");
  cont = getche();
 }while(cont != 'n' && cont != 'N');
}