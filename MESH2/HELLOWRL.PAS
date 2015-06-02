program HelloWorld;

uses crt, strings;
var msg : array[0..50] of char;

procedure EnableBlink(color : integer);
BEGIN
 textcolor(color + BLINK);
END;

procedure DisableBlink;
BEGIN
 textcolor(7);
END;

procedure center(col, row : integer; txt : array of char);
var
 x : integer;
BEGIN
 x := col - (StrLen(msg) div 2);
 GotoXY(x, row);
 WRITELN(mSg);
END;

procedure HideCursor;
BEGIN
 ASM
  mov ax, $0100
  mov cx, $2607
  int $10
 END
END;

BEGIN
 clrscr;
 HideCursor;
 EnableBlink(7);
 strcopy(msg, 'Hello world, this my first "Turbo Pascal 7.0" program');
 center(40, 12, msg);
 strcopy(msg, 'Written by Juan V. Guerrero');
 center(40, 13, msg);
 DisableBlink;
{ delay(1250);}
END.
