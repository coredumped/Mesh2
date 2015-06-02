program cases;

uses crt;

LABEL SELECCION;
VAR
   colores :byte;
   menu : char;
   funcionA, funcionB, funcionC, funcionD, funcionE, funcionF : char;
   decisionA, decisionB, decisionC  : char;
   cont1, cont2 : word;

PROCEDURE SUMA;
LABEL
    RE1=1443;
    RE2=$1FF2;
    RE3=$27F8;
    RE4=$1A2652;
    RE5=$EE5E4;

VAR
    RS1, RS2, RS3, RS4, RS5 : integer;

BEGIN
    clrscr;
    textmode(C80);
    window(1,1,80,25);textbackground(0); clrscr;
    textbackground(3);textcolor (0);
    window(17,3,65,12);clrscr;
    gotoxy(12,3); writeln('    INTRODUCCION ');
    gotoxy(6,6);writeln('LA SUMA HEXADECIMAL ES UNA OPERACION');
    gotoxy(6,7);writeln('DONDE SE REALIZA LA ADICION UTILIZANDO');
    gotoxy(6,8);writeln('NUMEROS ENTEROS Y LETRAS QUE VAN DE UN');
    gotoxy(6,9);writeln('RANGO DE LA "A" HASTA LA "F",Y LAS CUA-');
    gotoxy(6,10); writeln('LES TIENEN UN VALOR ENTERO Y EL RESUL-');
    gotoxy(6,11);writeln('     TADO ESTA DADO EN LETRAS Y NUMEROS.');
    textbackground(15);
    window(17,14,65,20);clrscr;
    gotoxy(6,15);writeln('                   OBJETIVO');
    gotoxy(6,17);writeln('     APRENDER AL RESOLVER PROBLEMAS EN ESTE');
    gotoxy(6,18);writeln('     SISTEMA, UTILIZANDO CORRECTAMENTE LAS' );
    gotoxy(6,19);writeln('     REGLAS E INDICACIONES PARA LOGRAR ASI');
    gotoxy(6,20);writeln('     EL DOMINIO DEL TEMA');
    gotoxy(19,21);writeln( '              ฏฏ PRESIONE ENTER ฎฎ');
    readln;
    (*PROCEDIMIENTOS PARA RESOLVER UNA SUMA HEXADECIMAL*);
    clrscr;window (1,1,80,25);textbackground(0);clrscr;
    textcolor(10);clrscr;
    window(1,1,80,25);
    gotoxy(16,2);writeln(#3,'PROCEDIMIENTO PARA RESOLVER UNA SUMA HEXADECIMAL',#3);
    gotoxy(3,5);writeln('1. PRIMERO SE SUMAN LAS DOS PRIMERAS CANTIDADES YA SEAN NUMEROS O LETRAS MAS');
    gotoxy(6,6);writeln('HACIA LA DERECHA.');
    gotoxy(3,8);writeln('2. SI EL RESULTADO DE SUMAR LAS DOS PRIMERAS CANT. ES MAYOR QUE 16 SE DEBE ');
    gotoxy(6,9);writeln( 'DIVIDIR, EL RESIDUO SE COLOCA DEBAJO Y EL COCIENTE SE LLEVA PARA LUEGO ');
    gotoxy(6,10);writeln('SUMARLO CON LAS CANTIDADES SIGUIENTES.');
    gotoxy(3,12);writeln('3. SI EL RESULTADO ES MENOR QUE 16 SE COLOCA SU RESPECTIVO VALOR YA SEA EN ');
    gotoxy(6,13);writeln('NUMEROS O LETRAS.');
    gotoxy(35,15);writeln (#1,'EJEMPLO',#1);
    gotoxy(9,17);writeln('1  1     1 '); gotoxy(25,17); writeln( #174#174, 'ESTOS SON LOS RESIDUOS QUE SE LLEVAN');
    gotoxy(10,18);writeln('  8  4  3  A ');gotoxy(25,18); writeln('SUMA ESTAS DOS CANTIDADES ASI:  A+A = 20');
    gotoxy(10,19);writeln('  D  C  2  A ');gotoxy(25,19); writeln('EL RESULTADO QUE SE OBTIENE ES MAYOR QUE 16 ENTONCES ');
    gotoxy(9,20);writeln(' ____________ ');gotoxy(25,20); writeln('SE DIVIDE ENTRE 16 ASI : 20/16 = 1 ESTE EL EL COCIENTE ');
    gotoxy(9,21);writeln('1  6  0  6  4 ');gotoxy(25,21); writeln('EL RESIDUO ES 4.');
    gotoxy(9,23);writeln('LAS CANTIDADES QUE SE LLEVAN SE SUMAN CON LAS OTRAS SIGUIENTES Y SE');
    gotoxy(9,24);writeln('EFECTUA LA MISMA OPERACION.');
    gotoxy(50,25);writeln(#175#175,'PRESIONE ENTER ', #175#175);
    readln;clrscr; window (1,1,80,25);textbackground (1);clrscr;

    CONT1 := 0;
    clrscr; (*PROBLEMAS PARA QUE EL USUARIO RESUELVA*)
    gotoxy(23,2);writeln(#15,'PROBLEMAS DE SUMA HEXADECIMAL',#15);
    gotoxy(12,3);writeln(#15,'A LOS SIGUIENTES PROBLEMAS COLOCA SOLO TU RESPUESTA',#15);
    gotoxy(10,5);writeln('9  9  9 ');
    gotoxy(10,6);writeln('A  A  A ');
    gotoxy(9,7);writeln('---------');
    gotoxy(11,8);readln(RS1);

       IF RS1 = RE1
       THEN
	    writeln(#15,'TU RESPUESTA ES CORRECTA',#15)
       ELSE
            writeln(#15,'TU RESPUESTA ES INCORRECTA, LA RESPUESTA ES = ' ,RE1 ,#15);
            CONT1 := CONT1 + 1;

       readln;
   gotoxy(10,12);writeln('4  7  9');
   gotoxy(10,13);writeln('5  A  D');
   gotoxy(10,14);writeln('B  C  D');
   gotoxy(9,15);writeln('________');
   gotoxy(10,16); readln(RS2);
       IF RS2 = RE2
       THEN
           writeln(#15,'TU RESPUESTA ES CORRECTA', #15)
       ELSE
           writeln(#15,'TU RESPUESTA ES INCORRECTA, LA RESPUESTA ES = ', '1FF2' ,#15);
           CONT1 := CONT1 + 1; 


       readln;

  gotoxy(10,18);writeln('A  B  C');
  gotoxy(10,19);writeln('F  D  A');
  gotoxy(10,20);writeln('A  E  D');
  gotoxy(10,21);writeln('4  7  5');
  gotoxy(8,22);writeln('________');
  gotoxy(10,23); readln(RS3);
       IF RS3 = RE3
       THEN
	    writeln(#15,'TU RESPUESTA ES CORRECTA',#15)
       ELSE

       writeln(#15,'TU RESPUESTA ES INCORRECTA, LA RESPUESTA ES = 2FF8',  #15);
       CONT1 := CONT1 + 1;
  readln;

  clrscr;
  gotoxy(10,4);writeln('E  5  6  9  8');
  gotoxy(10,5);writeln('   F  F  F  E');
  gotoxy(10,6);writeln('A  B  C  D  C');
  gotoxy(9,7);writeln('_______________');
  gotoxy(12,8);readln(RS4);
       IF RS4 = RE4
       THEN
            writeln(#15,'TU RESPUESTA ES CORRECTA',#15)
       ELSE
            writeln(#15,'TU RESPUESTA ES INCORRECTA, LA RESPUESTA ES = 1A2652' , #15);
            CONT1 := CONT1 + 1;

  gotoxy(10,10);writeln('E  C  6  A  8');
  gotoxy(10,11);writeln('   1  F  3  C');
  gotoxy(9,12);writeln ('______________');
  gotoxy(15,13);readln(RS5);
       IF RS5 = RE5
       THEN
       writeln(#15,'TU RESPUESTA ES CORRECTA',#15)
       ELSE
       writeln(#15,'TU RESPUESTA ES INCORRECTA, LA RESPUESTA ES = EE5E4  ' ,#15);
       CONT1 := CONT1 + 1;

 gotoxy(25,24);writeln('         REGRESA PRONTO');
 readln
 END;

PROCEDURE RESTA;
LABEL retroceso,final,continuacion;

VAR
resp1, resp2, resp3, resp4, resp5 : string[10];
respuestas : array[1..6] of string;
decision : char;

{Impresion de los Objetivos en la Pantalla}
PROCEDURE objetivos;
BEGIN
clrscr; textbackground(0); clrscr;
textbackground(1); textcolor(11);
window(13,5,70,23);
writeln('ึฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤท');
writeln('บ   Objetivo.                                        บ');
writeln('บ                                                    บ');
writeln('บ      El Objetivo que YO  tengo con hacer   este    บ');
writeln('บ   programa, es enseคarle a USTED, como  se hace    บ');
writeln('บ   una Resta Hexagecimal.                           บ');
writeln('บ                                                    บ');
writeln('บ      La Resta Hexagecimal,  es  muy   sencilla     บ');
writeln('บ   espero que USTED, pueda agradarle mi Programa    บ');
writeln('บ   que con tanto esfuerzo hice...                   บ');
writeln('บ                                                    บ');
writeln('ำฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฝ');
readln;
END;

{impresion de los Pasos a seguir}
PROCEDURE pasos;
BEGIN
clrscr; textbackground(0); clrscr;
textbackground(1); textcolor(11);
window(7,4,80,25);
writeln('ึฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤท');
writeln('บ   Pasos:                                                       บ');
writeln('บ                                                                บ');
writeln('บ   1.  Reste las letras, o lo numeros,  dependiendo  del caso   บ');
writeln('บ                                                                บ');
writeln('บ   2.  Si el Numero que esta arriba es menor, que el de abajo   บ');
writeln('บ     entonces, quitele 1 al anterior, y sumele 16 al que  los   บ');
writeln('บ     necesita.                                                  บ');
writeln('บ                                                                บ');
writeln('บ   3.  Si la resta da mayor que 10, entonces USTED debe poner   บ');
writeln('บ     en vez del numero entero,  se  pone  la  correspondiente   บ');
writeln('บ     letra del abecedario.                                      บ');
writeln('บ                                                                บ');
writeln('บ   4.  Presione CTRL + PAUSE, para interumpir la ejecucion.     บ');
writeln('บ                                                                บ');
writeln('บ   5.  Asegurese de que escriba las letras en MAYUSCULA.        บ');
writeln('บ                                                                บ');
writeln('ำฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฝ');
readln;
END;

{Impresion de Error}
PROCEDURE error;
BEGIN
textbackground(0);clrscr;
textcolor(11); textbackground(1);
window(61,1,80,4);
writeln('ึฤฤฤฤฤฤฤฤฤฤฤฤฤฤท');
writeln('บ  !! Error !! บ');
writeln('ำฤฤฤฤฤฤฤฤฤฤฤฤฤฤฝ');
CONT2 := CONT2 + 1;
readln;
END;

{Impresion del Primer Problema}
PROCEDURE operacion1;
BEGIN
textbackground(0); clrscr;textbackground(1);
textcolor(11);window(10,5,23,9);
writeln('ึฤฤฤฤฤฤฤฤฤฤท');
writeln('บ   BF44   บ');
writeln('บ - AC59   บ');
writeln('ำฤฤฤฤฤฤฤฤฤฤฝ');
END;

{Impresion del Segundo Problema}
PROCEDURE operacion2;
BEGIN
clrscr;
textbackground(0); clrscr;
textbackground(1);textcolor(11);
window(50,5,63,9);
writeln('ึฤฤฤฤฤฤฤฤฤฤฤท');
writeln('บ   D3777   บ');
writeln('บ -  16FC   บ');
writeln('ำฤฤฤฤฤฤฤฤฤฤฤฝ');
END;

{impresion del Tercer Problema}
PROCEDURE operacion3;
BEGIN
clrscr;textbackground(0); clrscr;
textbackground(1);textcolor(11);
window(34,10,47,15);
writeln('ึฤฤฤฤฤฤฤฤฤฤฤท');
writeln('บ   E5698   บ');
writeln('บ -  FFFE   บ');
writeln('ำฤฤฤฤฤฤฤฤฤฤฤฝ');
END;

{impresion del Cuarto Problema}
PROCEDURE operacion4;
BEGIN
clrscr;textbackground(0); clrscr;
textbackground(1);textcolor(11);
window(10,18,23,24);
writeln('ึฤฤฤฤฤฤฤฤฤฤฤท');
writeln('บ   EBAD8A  บ');
writeln('บ -  ABE9C  บ');
writeln('ำฤฤฤฤฤฤฤฤฤฤฤฝ');
END;

{impresion del Quinto Problema}
PROCEDURE operacion5;
BEGIN
clrscr;textbackground(0); clrscr;
textbackground(1);textcolor(11);
window(48,18,63,24);
writeln('ึฤฤฤฤฤฤฤฤฤฤฤฤฤท');
writeln('บ   E9ABCD5   บ');
writeln('บ -  FBCDEF   บ');
writeln('ำฤฤฤฤฤฤฤฤฤฤฤฤฤฝ');
END;

PROCEDURE fin;
BEGIN
clrscr;
textbackground(0);
clrscr;
textbackground(1);
textcolor(11);
window(13,8,80,25);
writeln('ึฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤท');
writeln('บ                                                   บ');
writeln('บ                     (  • ข  )                     บ');
writeln('บ                    (  ฤฤฤฤฤ  )                    บ');
writeln('บ    ฤฤฤฤฤฤ()()()ฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤ()()()ฤฤฤฤฤ     บ');
writeln('บ                                                   บ');
writeln('บ    Ya que has contestado Todo Bien solo quiero    บ');
writeln('บ    decir que te Felicito, por  Lograrlo,  pero    บ');
writeln('บ    No quiere decir que se  acabo,  todavia  te    บ');
writeln('บ    falta Bastante...                              บ');
writeln('บ                                                   บ');
writeln('ำฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฝ');
readln;
END;


{Controlador de los procedimientos, o Programa maestro}

{turbo;universidad;presentacion;pasos;operacion1;operacion2;
operacion3;operacion4;operacion5;fin;}
BEGIN

{respuestas}

respuestas[1] := '12DB';
respuestas[2] := 'D207B';
respuestas[3] := 'F5692';
respuestas[4] := 'C0EEEE';
respuestas[5] := 'E9EEFEF';

{ejecucion de los Subprocedimientos}
window(1,1,80,25);
objetivos;
pasos;

retroceso:
clrscr; textbackground(0);
clrscr;
textcolor(11); textbackground(1);
window(18,5,70,25);
writeln('ึฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤท');
writeln('บ                                        บ');
writeln('บ       Û฿Ü฿Û ÜÛÛÛÜ      Ü     Ü         บ');
writeln('บ       Û Û Û Û฿   ฿      Û     Û        บ');
writeln('บ       Û Ü Û ÛÛÜÜ  Û ÛÛ   Û Û   Û       บ');
writeln('บ       Û   Û ÛÜ   Ü฿ Û Û  Û Û   Û       บ');
writeln('บ          Û  ฿ÛÛÛ฿   Û  Û Û ÛÜ ÜÛ       บ');
writeln('บ         ฿           Û   ÛÛ  ฿฿฿        บ');
writeln('บ                                        บ');
writeln('บ    Realice su seleccion:               บ');
writeln('บ                                        บ');
writeln('บ    (S). Para Salir                     บ');
writeln('บ    (C). Continuar con el Programa      บ');
writeln('บ                                        บ');
writeln('บ                                        บ');
writeln('ำฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฝ');

decision := readkey;
IF (decision = 'S') or (decision = 's') THEN
   BEGIN
       goto final;
   END;


    IF (decision = 'C') or (decision = 'c') THEN
       BEGIN
	    goto continuacion;
       END

       else
       BEGIN
            goto retroceso;
       END;

continuacion:

pasos;
CONT2 := 0;
writeln('Introduzca la Respuesta');
operacion1;
readln(resp1);
IF resp1 <> respuestas[1] THEN
BEGIN
error;
goto retroceso;
END

	else
	BEGIN
	clrscr;
        writeln('Introduzca la Respuesta');
        operacion2;
        readln(resp2);
	END;

	    IF resp2 <> respuestas[2] THEN
	    BEGIN
            error;
	    goto retroceso;
	    END

                 else
		 BEGIN
                 clrscr;
                 writeln('Introduzca la Respuesta');
                 operacion3;
                 readln(resp3);
		 END;

		     IF resp3 <> respuestas[3] THEN
		     BEGIN
		     error;
                     goto retroceso;
		     END
			  else
			  BEGIN
                          clrscr;
                          writeln('Introduzca la Respuesta');
                          operacion4;
                          readln(resp4);
			  END;

		 IF resp4 <> respuestas[4] THEN
		 BEGIN
                 error;
                 goto retroceso
		 END
            else
	    BEGIN
            clrscr;
            writeln('Introduzca la Respuesta');
	    operacion5;
	    readln(resp5);
	    END;

IF resp5 <> respuestas[5] THEN
BEGIN
error;
goto retroceso;
END

else
BEGIN
fin;
final :
       clrscr;
       window (1,1,80,25);textbackground (0);
       clrscr;
END;
END;

PROCEDURE DIVISION;
LABEL             (* SE DECLARAN LOS RESULTADOS DE LOS PROBLEMAS COMO CONSTANTES *)
     x1 = 132;      y1 = 116;
     x2 =$14D;      y2 =$2D7;
     x3 = 303;      y3 = 16;
     x4 = 322;      y4 = 17;
     x5 = 321;      y5 = 106;

VAR               (* TIPO DE RESPUESTAS QUE HA DE CONTESTAR EL USUARIO *)
   r1, r2, r3, r4 ,r5, resp1, resp2, resp3, resp4, resp5 : integer;
                                                 colores : byte;
                                                       c : word;
    BEGIN
    clrscr;        (* VISUALIZACION DE LOS OBJETIVOS QUE SE DESEAN LOGRAR *)
    window (1,1,80,25); textbackground (0);
    clrscr;window (3,10,12,58);textbackground (1);
    textcolor (14);gotoxy (12,5); writeln ('ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป');
                   gotoxy (12,6); writeln ('บ                     *** OBJETIVOS ***                    บ');
                   gotoxy (12,7); writeln ('บ                                                          บ');
                   gotoxy (12,8); writeln ('บ     ESTE PROGRAMA, FUE CREADO CON EL PROPOSITO DE AYU-   บ');
                   gotoxy (12,9); writeln ('บ     DARLE AL USUARIO, A COMPRENDER MAS ACERCA DE LAS     บ');
                   gotoxy (12,10);writeln ('บ     OPERACIONES MATEMATICAS QUE PUEDE REALIZAR EL COM-   บ');
                   gotoxy (12,11);writeln ('บ     PUTADOR INTERNAMENTE.  EN ESTE CASO, NOS HEMOS       บ');
                   gotoxy (12,12);writeln ('บ     PREOCUPADO POR HACER ENFASIS EN LO QUE SE REFIERE A  บ');
                   gotoxy (12,13);writeln ('บ     LA DIVISION HEXAGESIMAL.                             บ');
		   gotoxy (12,14);writeln ('บ                                                          บ');
		   gotoxy (12,15);write   ('ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ');
    readln;

    clrscr;        (* SE INICIA EL PROGRAMA.  EXPLICACION DEL MISMO *)
    window (1,1,80,25); textbackground (0);
    clrscr; textcolor (15);
    gotoxy (22,1); writeln ('ษอออออออออออออออออออออออออออออออออออออออป');
    gotoxy (22,2); writeln ('บ    PASOS PARA RESOLVER LA DIVISION    บ');
    gotoxy (22,3); writeln ('บ              HEXAGESIMAL              บ');
    gotoxy (22,4); writeln ('ศอออออออออออออออออออออออออออออออออออออออผ');
    gotoxy (5,6); writeln ('1.-  Se separa de izquierda a derecha tantos digitos en el dividendo como ');
    gotoxy (10,7);writeln ('digitos tenga el divisor.'); readln;
    gotoxy (5,9); writeln ('2.-  Si el numero de dividir esta fuera de los digitos del sistema hexa-');
    gotoxy (10,10);writeln ('gesimal se convierte a su equivalente en decimal (conversion de hexa-');
    gotoxy (10,11);writeln ('gesimal a decimal), de lo contrario se procede a dividir como de cos-');
    gotoxy (10,12);writeln ('tumbre.');readln;
    gotoxy (5,14); writeln ('3.-  El equivalente decimal (pto. 2) se divide entre el valor decimal');
    gotoxy (10,15);writeln ('del divisor.');readln;
    gotoxy (5,17); writeln ('4.-  El resultado (cociente del pto. 3) se multiplica por el valor de-');
    gotoxy (10,18);writeln ('cimal del divisor.'); readln;
    gotoxy (5,20); writeln ('5.-  El resultado se convierte a hexagesimal y despues se le resta.');readln;
    gotoxy (5,22); writeln ('6.-  Luego se continua el ciclo de pasos hasta terminar la division.');
    readln;

    clrscr;        (* SE VISUALIZA UN EJEMPLO PARA MAYOR COMPRENSION DEL PROGRAMA *)
    gotoxy (32,1); writeln ('Û฿฿฿฿฿฿฿฿฿฿฿฿฿฿฿Û');
    gotoxy (32,2); writeln ('Û    EJEMPLO    Û');
    gotoxy (32,3); writeln ('ÛÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÛ');
    gotoxy (1,5);  writeln ('1.       F 4 1 / B =                 F es un digito del sistema hexagesimal');
    gotoxy (1,6);  writeln ('                                     por consiguiente:       1 x B = B ');readln;
    gotoxy (1,8);  writeln ('         F 4 1 / B = 1                        F = 14   ');
    gotoxy (1,9);  writeln ('         B                                  - B = 11   ');
    gotoxy (1,10); writeln ('       -----                                ---------- ');
    gotoxy (1,11); writeln ('         4                                         4   ');
    gotoxy (1,12); writeln ('                                     Continuamos dividiendo.');readln;
    gotoxy (1,14); writeln ('2.       F 4 1 / B = 1               Se baja el siguiente numero (4).');
    gotoxy (1,15); writeln ('         B');
    gotoxy (1,16); writeln ('       -----');readln;
    gotoxy (1,17); writeln ('         44                          44 esta fuera de los digitos del sis-');
    gotoxy (1,18); writeln ('                                     tema hexagesimal, tendremos entonces');
    gotoxy (1,19); writeln ('                                     que convertirlo a un numero decimal:');readln;
    gotoxy (1,21); writeln ('                                             4 x 1  =  4');
    gotoxy (1,22); writeln ('                                             4 x 16 = 64');
    gotoxy (1,23); writeln ('                                                    ------');
    gotoxy (1,24); writeln ('                                                      68  [equivalente binario]');readln;clrscr;
    gotoxy (1,3);  writeln ('3. Se divide:');
    gotoxy (1,4);  writeln ('         68 / B = 6');readln;
    gotoxy (1,5);  writeln ('         66');
    gotoxy (1,6);  writeln ('        ----');
    gotoxy (1,7);  writeln ('          2');readln;
    gotoxy (1,9);  writeln ('4.       F 4 1 / B = 16              Se multiplica    6 x B = 66');
    gotoxy (1,10); writeln ('         B');
    gotoxy (1,11); writeln ('        ---                          66 se convirte a hexagesimal.');readln;
    gotoxy (1,12); writeln ('         44 ');
    gotoxy (1,13); writeln ('         42                          Siendo 42 si equivalente hexagesimal.');
    gotoxy (1,14); writeln ('        ----');readln;
    gotoxy (1,15); writeln ('          21                         Se baja el siguiente numero y se repiten');
    gotoxy (1,16); writeln ('                                     los pasos 2, 3 y 4 hasta terminar la ');
    gotoxy (1,17); writeln ('                                     division.');readln;
    gotoxy (1,19); writeln ('          ----------------------------------------------------------');
    gotoxy (1,20); writeln ('           LA RESPUESTA DE ESTE EJEMPLO SERIA:      F 4 1 / B = 163');
    gotoxy (1,21); writeln ('          ----------------------------------------------------------');
    readln;

    clrscr;        (* SEGUNDA ADVERTENCIA PARA EL USUARIO *)
    window (1,1,80,25); textbackground (0);
    clrscr;window (3,10,12,58);textbackground (4);
    textcolor (14);gotoxy (12,5); writeln ('ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป');
                   gotoxy (12,6); writeln ('บ                    *** ADVERTENCIA ***                   บ');
		   gotoxy (12,7); writeln ('บ                                                          บ');
                   gotoxy (12,8); writeln ('บ     A CONTINUACION TE PRESENTARE UNA SERIE DE PROBLEMAS  บ');
                   gotoxy (12,9); writeln ('บ     DE PRACTICA QUE TE AYUDARAN A COMPRENDER DE MANERA   บ');
		   gotoxy (12,10);writeln ('บ     MAS FACIL LO QUE ANTERIORMENTE SE TE HA EXPLICADO.   บ');
                   gotoxy (12,11);writeln ('บ     PROCURA CONTESTAR AQUELLAS RESPUESTAS QUE NECESITEN  บ');
                   gotoxy (12,12);writeln ('บ     DE LETRAS, ANTECEDIENDO A LAS MISMAS, EL SIGNO "$".  บ');
                   gotoxy (12,13);writeln ('บ                                                          บ');
                   gotoxy (12,14);writeln ('บ                        ฎฎ GRACIAS ฏฏ                     บ');
                   gotoxy (12,15);write   ('ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ');
    readln;

    clrscr;        (* SE LE OFRECEN DOS OPCIONES DE PRACTICA PARA DESARROLLAR *)
    window (1,1,80,25); textbackground (0);
    clrscr;
    textbackground (3); window (25,8,58,17);
    clrscr;
    textcolor(15); writeln (' ');
                   writeln (' ');
                   writeln ('            SELECCION            ');
                   writeln ('                                 ');
		   writeln ('   ESCRIBE 1 O 2 PARA ESCOGER    ');
		   writeln ('   LA PRACTICA QUE DESEAS:       ');
                   writeln ('                                 ');
		   write   ('         TU ESCOGES LA: ');
                   readln (C);

                   (* DESARROLLO DE LAS OPCIONES QUE PUEDE SELECCIONAR EL USUARIO *)
    IF C = 1 THEN
       BEGIN
            window (1,1,80,25); textbackground (0);

                   (* PRESENTACION DE LA OPCION 1 PARA POSTERIOR DESARROLLO *)
	    clrscr;
            textcolor (15);
            gotoxy (27,1); writeln ('ษอออออออออออออออออออออออออป');
            gotoxy (27,2); writeln ('บ      PRACTICA Nง 1      บ');
            gotoxy (27,3); writeln ('ศอออออออออออออออออออออออออผ');
            gotoxy (5,5);  writeln ('Resuelve las siguientes operaciones y coloca unicamente tu respuesta:');

                   (* DETALLE DE INSTRUCCIONES PARA LA EJECUCION DE LA COMPARACION DE RESPUESTAS *)

            gotoxy (5,7);  write ('1.  A C 5 / 9 = '); readln (r1);

			   IF x1 = r1 THEN
			       BEGIN
				    gotoxy (40,7);writeln ('Tu respuesta es CORRECTA.')
			       END
                           else
			       BEGIN
                                    gotoxy (40,7);writeln ('Tu respuesta es INCORRECTA.');
                                    gotoxy (40,8);writeln ('La respuesta correcta es 132.')
				END;

             gotoxy (5,10); write ('2.  3 E 7 / 3 = '); readln (r2);

			   IF x2 = r2 THEN
			       BEGIN
                                    gotoxy (40,10);writeln ('Tu respuesta es CORRECTA.')
			       END
                           else
			       BEGIN
                                    gotoxy (40,10);writeln ('Tu respuesta es INCORRECTA.');
                                    gotoxy (40,11);writeln ('La respuesta correcta es 14D.')
			       END;

	     gotoxy (5,13); write ('3.  C 1 2 / 4 = '); readln (r3);

			    IF x3 = r3 THEN
			       BEGIN
                                    gotoxy (40,13);writeln ('Tu respuesta es CORRECTA.')
			       END
                            else
				BEGIN
                                     gotoxy (40,13);writeln ('Tu respuesta es INCORRECTA.');
                                     gotoxy (40,14);writeln ('La respuesta correcta es 303.')
				END;

	     gotoxy (5,16); write ('4.  F B 0 / 5 = '); readln (r4);

			    IF x4 = r4 THEN
				BEGIN
                                     gotoxy (40,16);writeln ('Tu respuesta es CORRECTA.')
				END
                            else
				BEGIN
				     gotoxy (40,16);writeln ('Tu respuesta es INCORRECTA.');
                                     gotoxy (40,17);writeln ('La respuesta correcta es 322.')
				END;

             gotoxy (5,19); write ('5.  F A 5 / 5 = '); readln (r5);

			    IF x5 = r5 THEN
				BEGIN
                                     gotoxy (40,19);writeln ('Tu respuesta es CORRECTA.')
				END
                            else
				 BEGIN
                                      gotoxy (40,19);writeln ('Tu respuesta es INCORRECTA.');
                                      gotoxy (40,20);writeln ('La respuesta correcta es 321.')
				 END;
       readln; END;

                    (* PRESENTACION DE LAS OPCIONES QUE PUDO SELECCIONAR EL USUARIO *)
       IF C = 2 THEN
       BEGIN
                    (* PRESENTACION DE LA OPCION 2 PARA POSTERIOR DESARROLLO *)
             clrscr;
             window (1,1,80,25); textbackground (0);
             clrscr;
             textcolor (15);
	     gotoxy (27,1); writeln ('ษอออออออออออออออออออออออออป');
	     gotoxy (27,2); writeln ('บ      PRACTICA Nง 2      บ');
             gotoxy (27,3); writeln ('ศอออออออออออออออออออออออออผ');
	     gotoxy (5,5);  writeln ('Resuelve las siguientes operaciones y coloca unicamente tu respuesta:');

                       (* DETALLE DE INSTRUCCIONES PARA LA COMPARACION DE RESPUESTAS *)

             gotoxy (5,7);  write ('1.  C 5 2 / B = '); readln (resp1);

			    IF y1 = resp1 THEN
				 BEGIN
                                      gotoxy (40,7);writeln ('Tu respuesta es CORRECTA.')
				 END
                            else
				 BEGIN
                                      gotoxy (40,7);writeln ('Tu respuesta es INCORRECTA.');
                                      gotoxy (40,8);writeln ('La respuesta correcta es 116.')
				 END;

             gotoxy (5,10); write ('2.  5 A E / 2 = '); readln (resp2);

			    IF y2 = resp2 THEN
				  BEGIN
                                       gotoxy (40,10);writeln ('Tu respuesta es CORRECTA.')
				  END
			    else
				  BEGIN
                                       gotoxy (40,10);writeln ('Tu respuesta es INCORRECTA.');
                                       gotoxy (40,11);writeln ('La respuesta correcta es 2D7.')
				  END;

             gotoxy (5,13); write ('3.   D C / A = '); readln (resp3);

			    IF y3 = resp3 THEN
				  BEGIN
                                       gotoxy (40,13);writeln ('Tu respuesta es CORRECTA.')
				  END
                            else
				  BEGIN
                                       gotoxy (40,13);writeln ('Tu respuesta es INCORRECTA.');
                                       gotoxy (40,14);writeln ('La respuesta correcta es 16.')
				  END;

             gotoxy (5,16); write ('4.  8 A / 6 = '); readln (resp4);

			    IF y4 = resp4 THEN
				   BEGIN
                                        gotoxy (40,16);writeln ('Tu respuesta es CORRECTA.')
				   END
                            else
				   BEGIN
                                        gotoxy (40,16);writeln ('Tu respuesta es INCORRECTA.');
                                        gotoxy (40,17);writeln ('La respuesta correcta es 17.')
				   END;

             gotoxy (5,19); write ('5.  1 5 3 C / F = '); readln (resp5);

			    IF y5 = resp5 THEN
				   BEGIN
                                        gotoxy (40,19);writeln ('Tu respuesta es CORRECTA.')
				   END
                            else
				   BEGIN
                                        gotoxy (40,19);writeln ('Tu respuesta es INCORRECTA.');
                                        gotoxy (40,20);writeln ('La respuesta correcta es 106.')
				   END;
             readln;
END;
END;

LABEL MAINMENU;
BEGIN
    clrscr;         (* SE LE SEฅALA AL USUARIO EL TIPO DE LENGUAJE UTILIZADO *)
    textcolor (1); gotoxy (12,6); writeln ('ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป');
                   gotoxy (12,7); writeln ('บ                                                          บ');
                   gotoxy (12,8); writeln ('บ                                                          บ');
                   gotoxy (12,9); writeln ('บ         ฺหอหอหฟ ฺห   หฟ ฺหอออหฟ ฺหออหฟ  ฺหอออหฟ          บ');
    textcolor (11);gotoxy (12,10);writeln ('บ            บ    ณบ   บณ ณฬออหสู ณฬออสหฟ ณบ   บณ          บ');
                   gotoxy (12,11);writeln ('บ            ส    ภสอออสู ภส  ศอู ภสอออสู ภสอออสู          บ');
		   gotoxy (12,12);writeln ('บ       ฺหอออหฟ ฺหอออหฟ ฺหอออหฟ ฺหอออหฟ ฺหอออหฟ ฺห         บ');
                   gotoxy (12,13);writeln ('บ       ณฬอออสู รฮอออฮด ภสอออหฟ ณบ      รฮอออฮด ณบ         บ');
    textcolor (15);gotoxy (12,14);writeln ('บ       ภส      ภส   สู ภสอออสู ภสอออสู ภส   สู ภสอออสู    บ');
                   gotoxy (12,15);writeln ('บ                                            VERSION 6.0   บ');
                   gotoxy (12,16);write   ('ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ');
                   readln;

                   clrscr;       (* PRESENTACION DEL PROGRAMA PARA EL USUARIO *)
                   window (1,1,80,25); textbackground (0);textcolor (15);
                   clrscr; gotoxy (22,24); writeln('  [ Presione "ENTER" para continuar ]');
                   asm
		   mov ax,$0100
		   mov cx,$2607
                   int $10
		   END;
                   repeat
                         colores := random(15);
                         textcolor(colores);
                                   gotoxy (12,9); writeln ('  ฿Û  Û฿ Û฿฿Û ฿Û฿    ฿฿Ü       ฿฿Ü  Û฿฿Û฿฿Û  ฿Û฿ Û฿฿Û  Û฿฿Û ');
                                   gotoxy (12,10);writeln ('   ÛÜÜÛ  Û  Û  Û    ÛÜÜÛ      ÛÜÜÛ  Û  Û  Û   Û  Û ÜÜÜ Û  Û ');
                                   gotoxy (12,11);writeln ('   Û  Û  Û  Û  Û  Ü Û  Û      Û  Û  Û  Û  Û   Û  Û  Û  Û  Û ');
                                   gotoxy (12,12);writeln ('  ฿฿  ฿฿ ฿฿฿฿ ฿฿฿฿฿ ฿  ฿      ฿  ฿ ฿฿ ฿฿฿ ฿฿ ฿฿฿ ฿฿฿฿  ฿฿฿฿ ');

		   textcolor(15);
                   until keypressed;readln;

                   clrscr;
                   textbackground(0);
                   clrscr;
                   window(3,4,80,25);
                   textcolor(15); textbackground(3);
		   writeln('ึฤาฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤาฤท');
                   writeln('บฤฝ                                                                     ำฤถ');
                   writeln('บ   ฿Û฿ ฿Û฿฿Û  Û฿Û฿Û ฿Û฿฿Û  Û฿฿Û ฿Û฿฿Û ฿Û  Û฿ Û฿฿Û Û฿฿Û ฿Û฿ Û฿฿Û ฿Û฿฿Û    บ');
                   writeln('บ    Û   Û  Û    Û    Û฿Û   Û  Û  Û  Û  Û  Û  Û    Û     Û  Û  Û  Û  Û    บ');
                   writeln('บ    Û   Û  Û    Û    Û ฿Û  Û  Û  Û  Û  Û  Û  Û  Ü Û  Ü  Û  Û  Û  Û  Û    บ');
		   writeln('บ   ฿฿฿ ฿฿  ฿฿  ฿฿฿  ฿฿  ฿฿ ฿฿฿฿ ฿฿฿฿฿  ฿฿฿฿  ฿฿฿฿ ฿฿฿฿ ฿฿฿ ฿฿฿฿ ฿฿  ฿฿   บ');
                   writeln('บ                                                                         บ');
                   writeln('บ       Este programa contiene,  las operaciones  basicas  del  sistema   บ');
                   writeln('บ   HEXADECIMAL, que son: Suma, Resta, Multiplicacion y Division.         บ');
                   writeln('บ                                                                         บ');
                   writeln('บ       Se presentara un menu, que permite escoger la operacion matema-   บ');
                   writeln('บ   tica deseada,  unicamente pulse  la  tecla que se le presente en la   บ');
                   writeln('บ   pantalla, en cada una de las alternativas, se presentara una intro-   บ');
                   writeln('บ   duccion, objetivo, reglas, ejemplos y problemas  de  practica  para   บ');
		   writeln('บ   resolver.                                                             บ');
                   writeln('บ                                                                         บ');
                   writeln('บ                                  atte:                                  บ');
                   writeln('วฤท                                       Los Programadores...          ึฤบ');
                   writeln('ำฤะฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤะฤฝ');
                   readln;

                   clrscr;
                   textbackground(0);
                   clrscr;
                   window(6,4,80,25);
		   textcolor(15); textbackground(3);
		   writeln('ึฤาฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤาฤท');
                   writeln('วฤฝ                                                              ำฤถ');
		   writeln('บ        Û฿฿Û ฿Û฿฿Û   ฿Û฿ ฿Û฿฿Û Û฿Û฿Û ฿Û฿ ฿Û  Û฿ Û฿฿Û Û฿฿Û         บ');
                   writeln('บ        Û  Û  ÛÜÜÛ    Û   ÛÜÜ    Û    Û   Û  Û  Û  Û ÛÜÜÜ         บ');
                   writeln('บ        Û  Û  Û  Û Û  Û   Û  Ü   Û    Û   Û  Û  Û  Û    Û         บ');
                   writeln('บ        ฿฿฿฿  ฿฿฿฿ ฿฿฿฿  ฿฿฿฿฿  ฿฿฿  ฿฿฿   ฿฿   ฿฿฿฿ ฿฿฿฿         บ');
                   writeln('บ                                                                  บ');
                   writeln('บ          El Objetivo que tenemos nosotros con este TUTOR         บ');
                   writeln('บ       es de enseคarle  a  USTED  como  usuario,  todo lo         บ');
                   writeln('บ       referente a las Operaciones Hexadecimales.                 บ');
                   writeln('บ                                                                  บ');
		   writeln('บ          Este TUTOR, le  brinda  problemas  de  practica         บ');
                   writeln('บ       para que usted, se desenvuelva con las operaciones         บ');
                   writeln('บ       HexaDecimales.                                             บ');
                   writeln('บ                                                                  บ');
                   writeln('บ          Esperamos que sea de su completo agrado...              บ');
                   writeln('บ                                                                  บ');
                   writeln('บ                                Los Programadores...              บ');
                   writeln('วฤท                                                              ึฤถ');
		   writeln('ำฤะฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤะฤฝ');
                   goto SELECCION;
SELECCION:
           clrscr;
           textbackground(0); clrscr;
	   textcolor (5); gotoxy (13,3); writeln('        ฺฤฤ   ฺฤฤ ฺฤฤฤฤฤฤ ฺฤฤฤ  ฺฤฤ ฺฤฤ   ฺฤฤ        ');
                          gotoxy (13,4); writeln('        ฺฤฤฤ ฺฤฤฤ ฺฤฤ     ฺฤฤฺฤ ฺฤฤ ฺฤฤ   ฺฤฤ        ');
           textcolor (14);gotoxy (13,5); writeln('        ฺฤฤ ฺ ฺฤฤ ฺฤฤฤฤ   ฺฤฤ ฺฤฺฤฤ ฺฤฤ   ฺฤฤ        ');
                          gotoxy (13,6); writeln('        ฺฤฤ   ฺฤฤ ฺฤฤ     ฺฤฤ  ฺฤฤฤ ฺฤฤ   ฺฤฤ        ');
           textcolor (1); gotoxy (13,7); writeln('        ฺฤฤ   ฺฤฤ ฺฤฤฤฤฤฤ ฺฤฤ   ฺฤฤ  ฺฤฤฤฤฤฤ         ');
           textcolor (15);gotoxy (13,11);writeln('ึฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤท');
                          gotoxy (13,12);writeln('บ                                                     บ');
                          gotoxy (13,13);writeln('บ        S) Suma HexaDecimal.                         บ');
                          gotoxy (13,14);writeln('บ        R) Resta HexaDecimal.                        บ');
			  gotoxy (13,15);writeln('บ        M) Multiplicaciขn Hexadecimal.               บ');
                          gotoxy (13,16);writeln('บ        D) Divicion HexaDecimal.                     บ');
                          gotoxy (13,17);writeln('บ        Q) Salir de Programa                         บ');
                          gotoxy (13,18);writeln('บ                                                     บ');
                          gotoxy (13,19);writeln('ำฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฤฝ');

MAINMENU:
menu := readkey;
case Menu of

'S','s':
	BEGIN
	    clrscr;
	    SUMA;
	    goto SELECCION
	END;
'R','r':
	BEGIN
	     clrscr;
	     RESTA;
	     goto SELECCION
	END;

'M','m':
	BEGIN
	     clrscr;
	     window (1,1,80,25); textbackground (0);
    clrscr;window (3,10,12,58);textbackground (4);
    textcolor (14);gotoxy (12,5); writeln ('ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป');
		   gotoxy (12,6); writeln ('บ                    *** ADVERTENCIA ***                   บ');
		   gotoxy (12,7); writeln ('บ                                                          บ');
		   gotoxy (12,8); writeln ('บ   POR MOTIVOS DE FUERZA MAYOR AJENA A NOSOTROS Y FUERA   บ');
		   gotoxy (12,9); writeln ('บ   DEL ALCANCE DE NUESTRAS MANOS, NO SE PUDO INCLUIR      บ');
		   gotoxy (12,10);writeln ('บ   ESTA OPERACION, YA QUE LA MANERA EN QUE SE HIZO ES     บ');
		   gotoxy (12,11);writeln ('บ   UN POCO DIFICIL PARA INCLUIRLO.  PARA RESPALDAR LO     บ');
		   gotoxy (12,12);writeln ('บ   DICHO ANTERIORMENTE SE INCLUYE FUERA DE ESTE PROGRA-   บ');
		   gotoxy (12,13);writeln ('บ   MA BAJO EL NOMBRE DE IBBON.PAS...                      บ');
		   gotoxy (12,14);writeln ('บ                                                          บ');
		   gotoxy (12,15);writeln ('บ                        ฎฎ GRACIAS ฏฏ                     บ');
		   gotoxy (12,16);write   ('ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ');
    readln;
	     goto SELECCION
	END;

'D','d':
	BEGIN
	     clrscr;
	     DIVISION;
	     goto SELECCION
	 END;

'Q','q':exit

else
 goto MAINMENU
END
END.
